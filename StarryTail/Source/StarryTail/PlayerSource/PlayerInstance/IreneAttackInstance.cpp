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



UIreneAttackInstance::UIreneAttackInstance()
{
	// 데이터 테이블
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_AttackDataTable(TEXT("/Game/Math/DT_AttackDataTable.DT_AttackDataTable"));
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_ChargeDataTable(TEXT("/Game/Math/DT_ChargeDataTable.DT_ChargeDataTable"));
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_ElementDataTable(TEXT("/Game/Math/DT_ElementDataTable.DT_ElementDataTable"));
	if (DT_AttackDataTable.Succeeded() && DT_ChargeDataTable.Succeeded() && DT_ElementDataTable.Succeeded())
	{
		AttackDataTable = DT_AttackDataTable.Object;
		ChargeDataTable = DT_ChargeDataTable.Object;
		ElementDataTable = DT_ElementDataTable.Object;
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
void UIreneAttackInstance::SetIsPerfectDodge(const bool Value, const TArray<uint8> PerfectDodgeDir)
{
	IsPerfectDodge = Value;
	Irene->IreneInput->SetIsPerfectDodge(PerfectDodgeDir);
}
void UIreneAttackInstance::InitMemberVariable()
{
	SwordTargetMonster = nullptr;

	bFollowCameraTarget = false;
	FollowTargetCameraAlpha = 0.0f;
	CameraRot = FRotator::ZeroRotator;
	TargetCameraRot = FRotator::ZeroRotator;

	bMoveSkip = false;
	bDodgeJumpSkip = false;
	bSkillSkip = false;
}

#pragma region Attack
float UIreneAttackInstance::GetATK()const
{
	return Irene->IreneData.Strength;
}

FName UIreneAttackInstance::GetBasicAttackDataTableName()
{
	// 기본공격 데이터 테이블 이름 받기 위한 조합 계산 함수
	FString AttributeName = "B_Attack_1";
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack1"))
	{
		AttributeName = "B_Attack_1";
	}
	else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack2"))
	{
		AttributeName = "B_Attack_2";
	}
	else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack3"))
	{
		AttributeName = "B_Attack_3";
	}
	else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack4"))
	{
		AttributeName = "B_Attack_4";
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
		Irene->Weapon->SetGenerateOverlapEvents(true);

		Irene->IreneSound->PlayAttackSound();
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
	
	auto STGameInstance = Cast<USTGameInstance>(Irene->GetGameInstance());
	//if (STGameInstance->GetPlayerBattleState())
	//{
	//	Irene->CameraOutEvent();
	//}
	
	bool bResult = false;

	const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetBasicAttackDataTableName()));
	
	TArray<FHitResult> MonsterList;
	FCollisionQueryParams Params(NAME_None, false, Irene);
	bResult = GetWorld()->SweepMultiByChannel(
	MonsterList,
	Irene->GetActorLocation() + (Irene->GetActorForwardVector()*(AttackTable->Attack_Distance_1-50.0f)),
	Irene->GetActorLocation() + (Irene->GetActorForwardVector()*(AttackTable->Attack_Distance_1-50.0f)),
	FRotationMatrix::MakeFromZ(Irene->GetActorForwardVector()).ToQuat(),
	ECollisionChannel::ECC_GameTraceChannel1,
	FCollisionShape::MakeBox(FVector(200, 50, AttackTable->Attack_Distance_1)),
	Params);
	
	// 그리기 시작
	#if ENABLE_DRAW_DEBUG
		FVector TraceVec = Irene->GetActorForwardVector();
		FVector Center = Irene->GetActorLocation() + (Irene->GetActorForwardVector()*(AttackTable->Attack_Distance_1-50.0f));
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;
		DrawDebugBox(GetWorld(), Center, FVector(200, 50, AttackTable->Attack_Distance_1), CapsuleRot, DrawColor, false, DebugLifeTime);
	#endif

	// 모든 충돌된 액터에 데미지 전송
	for (FHitResult Monster : MonsterList)
	{
		if (bResult)
		{
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
						// 기본 + 몹
						SetGauge(17 + (7 * (MonsterList.Num()-1)));
					}
				}
				else if(Irene->IreneState->IsSkillState())
				{
					if(Mob->GetHp() > 0 && Irene->IreneData.CurrentHP > 0)
					{
						// 기본 + 스킬 + 몹
						SetGauge(17 + 30 + (7 * (MonsterList.Num()-1)));
					}
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
		//auto STGameInstance = Cast<USTGameInstance>(Irene->GetGameInstance());
		if (STGameInstance->GetAttributeEffectMonster() != nullptr)
			STGameInstance->ResetAttributeEffectMonster();
}

void UIreneAttackInstance::SetFireDeBuffStack(const int Value, const float DamageAmount)
{
	FireDeBuffStack = Value;
	FireMonsterDamageAmount = DamageAmount;
	if(!FireDeBuffTickTimerHandle.IsValid())
		GetWorld()->GetTimerManager().SetTimer(FireDeBuffTickTimerHandle, this, &UIreneAttackInstance::LoopFireDeBuff, 5.0f, true);
	GetWorld()->GetTimerManager().SetTimer(FireDeBuffStackTimerHandle, this, &UIreneAttackInstance::ResetFireDeBuffStack, 120.0f, false);
}
void UIreneAttackInstance::SetWaterDeBuffStack(const int Value)
{
	WaterDeBuffStack = Value;
	switch (Value)
	{
	case 1:
		Irene->IreneData.WaterDeBuffSpeed = 0.9f;
		break;
	case 2:
		Irene->IreneData.WaterDeBuffSpeed = 0.85f;
		break;
	case 3:
		Irene->IreneData.WaterDeBuffSpeed = 0.7f;
		break;
	default: break;
	}
	GetWorld()->GetTimerManager().SetTimer(WaterDeBuffStackTimerHandle, this, &UIreneAttackInstance::ResetWaterDeBuffStack, 120.0f, false);
}
void UIreneAttackInstance::SetThunderDeBuffStack(const int Value)
{
	if(!ThunderDeBuffTickTimerHandle.IsValid() || ThunderDeBuffStackTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ThunderDeBuffTickTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(ThunderDeBuffStackTimerHandle);
		ThunderDeBuffStack = Value;
		ThunderSustainTime = ThunderDeBuffStack*10;
		GetWorld()->GetTimerManager().SetTimer(ThunderDeBuffTickTimerHandle, this, &UIreneAttackInstance::OverSustainTime, ThunderSustainTime, false);
	}
}
void UIreneAttackInstance::LoopFireDeBuff()const
{
	if(FireMonsterDamageAmount != 0)
		Irene->SetHP(FireMonsterDamageAmount/2);
}
void UIreneAttackInstance::ResetFireDeBuffStack()
{
	GetWorld()->GetTimerManager().ClearTimer(FireDeBuffTickTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(FireDeBuffStackTimerHandle);
	FireDeBuffStack = 0;
	FireMonsterDamageAmount = 0;
}
void UIreneAttackInstance::ResetWaterDeBuffStack()
{
	GetWorld()->GetTimerManager().ClearTimer(WaterDeBuffStackTimerHandle);
	WaterDeBuffStack = 0;
	Irene->IreneData.WaterDeBuffSpeed = 1;
}
void UIreneAttackInstance::ResetThunderDeBuffStack()
{
	GetWorld()->GetTimerManager().ClearTimer(ThunderDeBuffStackTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(ThunderDeBuffTickTimerHandle);
	ThunderDeBuffStack = 0;
	ThunderSustainTime = 0;
}
void UIreneAttackInstance::OverSustainTime()
{
	ThunderSustainTime = 0;
	GetWorld()->GetTimerManager().SetTimer(ThunderDeBuffStackTimerHandle, this, &UIreneAttackInstance::ResetThunderDeBuffStack, 30.0f, false);
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
	if (Irene->IreneState->GetStateToString().Compare(FString("Skill_Start")) != 0
		&&Irene->IreneState->GetStateToString().Compare(FString("Skill_End")) != 0)
	{
		Irene->ChangeStateAndLog(USkillStartState::GetInstance());
	}
}
#pragma endregion State

#pragma region GetSet
void UIreneAttackInstance::SetGauge(float Value)
{
	if(Irene->IreneData.CurrentHP > 0 && Irene->Weapon->SkeletalMesh == Irene->WeaponMeshArray[0])
	{
		Irene->IreneData.CurrentGauge += Value;
		if(Irene->IreneData.CurrentGauge > Irene->IreneData.MaxGauge)
			Irene->IreneData.CurrentGauge = Irene->IreneData.MaxGauge;
	}
}

#pragma endregion GetSet