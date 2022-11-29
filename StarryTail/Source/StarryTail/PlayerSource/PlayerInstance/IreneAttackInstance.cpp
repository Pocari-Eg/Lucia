// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneAttackInstance.h"
#include "../IreneCharacter.h"
#include "../PlayerFSM/IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneUIManager.h"
#include "IreneInputInstance.h"

#include "DrawDebugHelpers.h"
#include "../../STGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../PlayerSpirit/IreneSpirit.h"
#include "../PlayerSpirit/IreneSpiritAnimInstance.h"
#include "../../UI/IngameWidget_D.h"

UIreneAttackInstance::UIreneAttackInstance()
{
	// 데이터 테이블
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_AttackDataTable(TEXT("/Game/Math/DT_AttackDataTable.DT_AttackDataTable"));
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_ElementDataTable(TEXT("/Game/Math/DT_ElementDataTable.DT_ElementDataTable"));
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_WeaponGauge(TEXT("/Game/Math/DT_WeaponGauge.DT_WeaponGauge"));
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_WeaponSoul(TEXT("/Game/Math/DT_WeaponSoul.DT_WeaponSoul"));
	if (DT_AttackDataTable.Succeeded() && DT_ElementDataTable.Succeeded() && DT_WeaponGauge.Succeeded() && DT_WeaponSoul.Succeeded())
	{
		AttackDataTable = DT_AttackDataTable.Object;
		ElementDataTable = DT_ElementDataTable.Object;
		WeaponGaugeDataTable = DT_WeaponGauge.Object;
		WeaponSoulDataTable = DT_WeaponSoul.Object;
	}
}

void UIreneAttackInstance::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);
	InitMemberVariable();
}
void UIreneAttackInstance::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}
void UIreneAttackInstance::SetIsPerfectDodge(const bool Value)
{
	IsPerfectDodge = Value;
}
void UIreneAttackInstance::InitMemberVariable()
{
	SwordTargetMonster = nullptr;
	TrueAttackCount = 0;
	
	DamageBeforeTableName = "";

	bFollowCameraTarget = false;
	FollowTargetCameraAlpha = 0.0f;
	CameraRot = FRotator::ZeroRotator;
	TargetCameraRot = FRotator::ZeroRotator;

	bMoveSkip = false;
	bDodgeJumpSkip = false;
	bSkillSkip = false;
	bSkillToAttack = false;
}

#pragma region Attack
float UIreneAttackInstance::GetATK()const
{
	return Irene->IreneData.Strength;
}

FName UIreneAttackInstance::GetBasicAttackDataTableName()
{
	// 기본공격 데이터 테이블 이름 받기 위한 조합 계산 함수
	FString AttributeName = "None";
	if (Irene->IreneState->IsAttackState())
	{
		if (!Irene->bIsSpiritStance)
			AttributeName = "B_Attack_" + FString::FromInt(TrueAttackCount);
		else
			AttributeName = "S_B_Attack_" + FString::FromInt(TrueAttackCount);
		if (AttributeName == "B_Attack_4")
			AttributeName = "B_Attack_3";
		if (AttributeName == "S_B_Attack_4")
			AttributeName = "S_B_Attack_3";
	}
	else if (Irene->IreneState->IsSkillState())
	{
		if (!Irene->bIsSpiritStance)
		{
			if (Irene->IreneState->GetStateToString().Compare("Sword_Skill_1") == 0)
				AttributeName = "Skill_1_1";
			else if (Irene->IreneState->GetStateToString().Compare("Sword_Skill_2") == 0)
				AttributeName = "Skill_1_2";
		}
		else
		{
			AttributeName = "S_Skill_" + FString::FromInt(TrueAttackCount);
			if (AttributeName == "S_Skill_4")
				AttributeName = "S_Skill_3";
		}
	}
	else if (Irene->IreneState->IsDodgeState())
	{
		if(!IsPerfectDodge)
			AttributeName = "Dodge";
		else
			AttributeName = "Perfect_Dodge";
	}

	if(AttributeName == "None" && DamageBeforeTableName != "")
	{
		AttributeName = DamageBeforeTableName;		
	}
	if(AttributeName == "None")
	{
		STARRYLOG(Error,TEXT("%s"),*Irene->IreneState->GetStateToString());
		AttributeName = "B_Attack_1";
	}
	return FName(AttributeName);
}
FName UIreneAttackInstance::GetWeaponGaugeDataTableName()
{
	// 기본공격 데이터 테이블 이름 받기 위한 조합 계산 함수   
	FString AttributeName = "Sword_B_Attack_1";
	if (!Irene->bIsSpiritStance)
		AttributeName = "Sword_B_Attack_" + FString::FromInt(TrueAttackCount);
	if (Irene->IreneState->IsSkillState())
	{
		if (Irene->IreneState->GetStateToString().Compare("Sword_Skill_1") == 0)
			AttributeName = "Sword_Skill_1_1";
		else if (Irene->IreneState->GetStateToString().Compare("Sword_Skill_2") == 0)
			AttributeName = "Sword_Skill_1_2";
	}
	return FName(AttributeName);
}

void UIreneAttackInstance::AttackStartComboState()
{
	// 노티파이 NextAttackCheck 도달 시 실행
	Irene->IreneData.CanNextCombo = false;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = FMath::Clamp<int32>(Irene->IreneData.CurrentCombo + 1, 1, Irene->IreneData.MaxCombo);
}
void UIreneAttackInstance::AttackEndComboState()
{
	Irene->IreneData.IsAttacking = false;
	Irene->Weapon->SetGenerateOverlapEvents(false);
	Irene->IreneData.CanNextCombo = false;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = 0;
}
void UIreneAttackInstance::AttackTimeEndState()
{
	// 몽타주가 완전히 끝남
	Irene->IreneData.IsAttacking = false;
	Irene->Weapon->SetGenerateOverlapEvents(false);
	Irene->IreneData.CanNextCombo = false;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = 0;
	if (!Irene->IreneState->IsDodgeState() && !Irene->IreneState->IsJumpState() && !Irene->IreneState->IsIdleState())
	{
		Irene->ChangeStateAndLog(UBattleIdleState::GetInstance());
	}	
}

void UIreneAttackInstance::AttackCheck()
{
	// 노티파이 AttackHitCheck 도달 시 실행
	if (Irene->IreneAnim->GetCurrentActiveMontage())
	{
		if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack2") && Irene->bIsSpiritStance)
		{
			if(TrueAttackCount == 2)
			{
				TrueAttackCount++;
			}
		}
		Irene->Weapon->SetGenerateOverlapEvents(true);

		if(Irene->IreneAnim->GetCurrentActiveMontage())
			Irene->FindNearMonster();
	}
}
void UIreneAttackInstance::AttackStopCheck()
{
	// 노티파이 AttackStopCheck 도달 시 실행
	Irene->IsTimeStopping = false;
	Irene->Weapon->SetGenerateOverlapEvents(false);
}
void UIreneAttackInstance::DoAttack()
{
	// 실제로 공격을 하는 함수로 위에는 속성에 따른 콜라이더 사용과 아래에는 콜라이더를 보여주는 역할을 하는 코드가 있는 함수
	const auto STGameInstance = Cast<USTGameInstance>(Irene->GetGameInstance());
	//if (STGameInstance->GetPlayerBattleState())
	//{
	//   Irene->CameraOutEvent();
	//}

	bool bResult = false;
	TArray<FHitResult> MonsterList;

	const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetBasicAttackDataTableName()));
	
	if(!Irene->bIsSpiritStance || Irene->IreneState->IsAttackState())
	{
		FVector BoxSize = FVector::ZeroVector;
		if(!Irene->bIsSpiritStance)
			BoxSize = FVector(200, 50, AttackTable->Attack_Distance_1);
		else
			BoxSize = FVector(200, 50, AttackTable->Attack_Distance_1);

		FVector StartPos = Irene->GetActorLocation() + (Irene->GetActorForwardVector()*(AttackTable->Attack_Distance_1-50.0f));
		//StartPos.Z -= Irene->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		
		const FCollisionQueryParams Params(NAME_None, false, Irene);
		bResult = GetWorld()->SweepMultiByChannel(
		MonsterList,
		StartPos,
		StartPos,
		FRotationMatrix::MakeFromZ(Irene->GetActorForwardVector()).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeBox(BoxSize),
		Params);
	
		// 그리기 시작
		#if ENABLE_DRAW_DEBUG
		const FVector TraceVec = Irene->GetActorForwardVector();
		const FVector Center = StartPos;
		const FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		const FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		constexpr float DebugLifeTime = 5.0f;
		DrawDebugBox(GetWorld(), Center, BoxSize, CapsuleRot, DrawColor, false, DebugLifeTime);
		#endif
	}
	StackCount = AttackTable->Stack_Count;
	SendDamage(bResult, MonsterList);
}

void UIreneAttackInstance::SendDamage(bool bResult, TArray<FHitResult> MonsterList)
{
	// 모든 충돌된 액터에 데미지 전송
	for (FHitResult Monster : MonsterList)
	{
		if (bResult)
		{
			const FCollisionQueryParams Params(NAME_None, false, Irene);

			// 리스트결과에 레이케스트 발사(반복)
			FHitResult RayHit;
			bool bLayResult = GetWorld()->LineTraceSingleByChannel(
				RayHit,
				Irene->GetActorLocation(),
				Monster.GetActor()->GetActorLocation(),
				ECollisionChannel::ECC_GameTraceChannel8,
				Params);
			
			if(bLayResult && RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>() == nullptr)
				continue;
			if (bLayResult && RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>() != nullptr)
			{
				//STARRYLOG(Warning,TEXT("%s"), *Monster.GetActor()->GetName());
				const FName RayCollisionProfileName = RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
				const FName EnemyProfile = "Enemy";
				const FName ObjectProfile = "Object";
				if (RayHit.Actor.IsValid() && (RayCollisionProfileName != EnemyProfile && RayCollisionProfileName != ObjectProfile))
					continue;
			}
				
			if (Monster.Actor.IsValid())
			{
				FDamageEvent DamageEvent;

				auto Mob = Cast<AMonster>(Monster.Actor);
				if (Mob != nullptr)
					Mob->SetAttackedInfo(true, 0, EAttackedDirection::Down);
				if(Irene->IreneState->IsAttackState())
				{
					if(Mob->GetHp() > 0 && Irene->IreneData.CurrentHP > 0)
					{
						const TUniquePtr<FWeaponGauge> DataTable = MakeUnique<FWeaponGauge>(*Irene->IreneAttack->GetNameAtWeaponGaugeDataTable(GetWeaponGaugeDataTableName()));
						// 기본 + 몹
						SetGauge(DataTable->Get_W_Gauge + (1 * (MonsterList.Num()-1)));
					}
				}
				else if(Irene->IreneState->IsSkillState())
				{
					if(Mob->GetHp() > 0 && Irene->IreneData.CurrentHP > 0)
					{
						const TUniquePtr<FWeaponGauge> DataTable = MakeUnique<FWeaponGauge>(*Irene->IreneAttack->GetNameAtWeaponGaugeDataTable(GetWeaponGaugeDataTableName()));
						if(!Irene->IreneInput->GetAttackUseSkill())
						{
							// 기본 + 몹
							SetGauge(DataTable->Get_W_Gauge + (1 * (MonsterList.Num()-1)));
						}
						else
						{
							// 기본 + 스킬 + 몹
							SetGauge(DataTable->Get_W_Gauge + DataTable->Get_B_Next + (1 * (MonsterList.Num()-1)));
						}
					}
				}
				if (Irene->bIsSpiritStance)
				{
					Mob->AddStackCount(StackCount);
				}
				UGameplayStatics::ApplyDamage(Monster.Actor.Get(), Irene->IreneData.Strength, nullptr, Irene, nullptr);
			}
		}
	}
	// 충돌한 액터가 있으면 카메라 쉐이크 시작
	if (bResult)
		Irene->CameraShakeOn = true;
	
	//속성공격 기준 몬스터 할당해제
	if (bResult)
	{
		//auto STGameInstance = Cast<USTGameInstance>(Irene->GetGameInstance());
		if (Irene->STGameInstance->GetAttributeEffectMonster() != nullptr)
			Irene->STGameInstance->ResetAttributeEffectMonster();
	}
}
#pragma endregion Attack

#pragma region State
void UIreneAttackInstance::SetAttackState()const
{
	// 현재 상태를 이용하여 다음 기본공격 상태로 전이 할 수 있는지 확인하는 함수
	if (Irene->IreneAnim->GetCurrentActiveMontage() == nullptr
	&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_1")) != 0 && Irene->IreneState->GetStateToString().Compare(FString("B_Attack_3")) != 0)
	{
		Irene->ChangeStateAndLog(UBasicAttack1State::GetInstance());
	}
	else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack2")
	&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_2")) != 0)
	{
		Irene->ChangeStateAndLog(UBasicAttack2State::GetInstance());
	}
	else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack3")
	&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_3")) != 0)
	{
		Irene->ChangeStateAndLog(UBasicAttack3State::GetInstance());
	}
}
void UIreneAttackInstance::SetSkillState()const
{
	// 스킬 상태로 전이 할 수 있는지 확인하는 함수
	if (Irene->IreneState->GetStateToString().Compare(FString("Sword_Skill_1")) != 0
		&& !Irene->bIsSpiritStance && Irene->IreneInput->GetCanUseSecondSwordSkill() == false)
	{
		Irene->ChangeStateAndLog(USwordSkill1::GetInstance());
	}
	else if (Irene->IreneState->GetStateToString().Compare(FString("Sword_Skill_2")) != 0
		&& !Irene->bIsSpiritStance && Irene->IreneInput->GetCanUseSecondSwordSkill() == true)
	{
		Irene->ChangeStateAndLog(USwordSkill2::GetInstance());
	}
	else if (Irene->bIsSpiritStance)
	{
		Irene->ChangeStateAndLog(USpiritSkill::GetInstance());
	}
}
#pragma endregion State

#pragma region GetSet
void UIreneAttackInstance::SetGauge(float Value)
{
	if(Irene->IreneData.CurrentHP > 0 && !Irene->bIsSpiritStance)
	{
		Irene->IreneData.CurrentGauge += Value;
		if(Irene->IreneData.CurrentGauge > Irene->IreneData.MaxGauge)
			Irene->IreneData.CurrentGauge = Irene->IreneData.MaxGauge;
		if(Irene->IreneData.CurrentGauge < 0)
			Irene->IreneData.CurrentGauge = 0;
		// 이쯤에 UI 게이지 수치 변경
		
		auto IngameW = Cast<UIngameWidget_D>(Irene->makeIngameWidget);
		if (IngameW != nullptr)
			IngameW->STANCEGAUGEeCtime(Value);

		Irene->IreneUIManager->UpdateSoul(Irene->IreneData.CurrentGauge, Irene->IreneData.MaxGauge);
	}
}
void UIreneAttackInstance::SetUltimateGauge(float Value)
{
	if(Irene->IreneData.CurrentHP > 0)
	{
		STARRYLOG(Warning, TEXT("%f"), Value);
		STARRYLOG_S(Error);
		Irene->IreneData.CurrentUltimateAttackGauge += Value;
		if(Irene->IreneData.CurrentUltimateAttackGauge > Irene->IreneData.MaxUltimateAttackGauge)
			Irene->IreneData.CurrentUltimateAttackGauge = Irene->IreneData.MaxUltimateAttackGauge;
		if(Irene->IreneData.CurrentUltimateAttackGauge < 0)
			Irene->IreneData.CurrentUltimateAttackGauge = 0;
		// 이쯤에 UI 게이지 수치 변경
	}
}
#pragma endregion GetSet