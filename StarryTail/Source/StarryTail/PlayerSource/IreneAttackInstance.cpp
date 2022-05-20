// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneAttackInstance.h"
#include "IreneCharacter.h"
#include "IreneInputInstance.h"
#include "IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneUIManager.h"

#include "DrawDebugHelpers.h"
#include "../STGameInstance.h"
#include "Kismet/GameplayStatics.h"


UIreneAttackInstance::UIreneAttackInstance()
{
	// 데이터 테이블
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_AttackDataTable(TEXT("/Game/Math/BP_AttackDataTable.BP_AttackDataTable"));
	if (DT_AttackDataTable.Succeeded())
	{
		AttackDataTable = DT_AttackDataTable.Object;
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
void UIreneAttackInstance::InitMemberVariable()
{
	TargetMonster = nullptr;
	//초기 속성
	Attribute = EAttributeKeyword::e_Fire;
	
	bFollowTarget = false;
	FollowTargetAlpha = 0.0f;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;
	bFollowCameraTarget = false;
	FollowTargetCameraAlpha = 0.0f;
	CameraRot = FRotator::ZeroRotator;
	TargetCameraRot = FRotator::ZeroRotator;

	bUseMP = false;
}
#pragma region Attack
float UIreneAttackInstance::GetATK()const
{
	return Irene->IreneData.Strength;
}

int UIreneAttackInstance::GetAttackDirection()
{
	// 0 == Right to Left
	// 1 == Left to Right
	// 2 == Down to Up
	// 3 == Up to Down
	
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack1"))
	{
		return 0;
	}
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack2"))
	{
		return 1;
	}
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack3"))
	{
		return 0;
	}
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack4"))
	{
		return 1;
	}
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack5"))
	{
		return 3;
	}

	return 0;
}
FName UIreneAttackInstance::GetBasicAttackDataTableName()
{
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
	if(Attribute == EAttributeKeyword::e_Fire)
	{
		AttributeName = AttributeName + FString("_F");
	}
	else if(Attribute == EAttributeKeyword::e_Water)
	{
		AttributeName = AttributeName + FString("_W");
	}
	else if(Attribute == EAttributeKeyword::e_Thunder)
	{
		AttributeName = AttributeName + FString("_T");
	}
	return FName(AttributeName);
}
FName UIreneAttackInstance::GetActionAttackDataTableName()
{
	FName ActionForm = FName("");
	if(Attribute == EAttributeKeyword::e_Fire)
	{
		ActionForm = FName("ActionKeyword_1_F");
	}
	else if(Attribute == EAttributeKeyword::e_Water)
	{
		ActionForm = FName("ActionKeyword_1_W");
	}
	else if(Attribute == EAttributeKeyword::e_Thunder)
	{
		ActionForm = FName("ActionKeyword_1_T");
	}
	return ActionForm;
}

void UIreneAttackInstance::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Irene->IreneData.IsAttacking = false;
	AttackEndComboState();
}
void UIreneAttackInstance::AttackStartComboState()
{
	Irene->IreneData.CanNextCombo = true;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = FMath::Clamp<int32>(Irene->IreneData.CurrentCombo + 1, 1, Irene->IreneData.MaxCombo);
}
void UIreneAttackInstance::AttackEndComboState()
{
	Irene->Weapon->SetGenerateOverlapEvents(false);
	Irene->IreneInput->bUseLeftButton = false;
	Irene->IreneInput->bUseRightButton = false;
	bUseMP = false;
	Irene->IreneData.CanNextCombo = false;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = 0;
	if (Irene->IreneState->GetStateToString().Compare(FString("Dodge")) != 0)
		Irene->ActionEndChangeMoveState();
}

void UIreneAttackInstance::AttackCheck()
{
	if (Irene->IreneAnim->GetCurrentActiveMontage())
	{
		Irene->Weapon->SetGenerateOverlapEvents(true);
		Irene->IreneUIManager->AttackSound->SoundPlay2D();

		if(Irene->IreneAnim->GetCurrentActiveMontage())
		{
			if(Irene->IreneAnim->GetCurrentActiveMontage()->GetName() != FString("IreneThunderSkill_Montage")&&
				Irene->IreneAnim->GetCurrentActiveMontage()->GetName() != FString("IreneFireSkill_Montage"))
			{
				Irene->FindNearMonster();
			}
			else
			{
				SetUseMP(true);
				DoAttack();
			}
		}
	}
}
void UIreneAttackInstance::AttackStopCheck()
{
	Irene->IsTimeStopping = false;
	Irene->Weapon->SetGenerateOverlapEvents(false);
}
void UIreneAttackInstance::DoAttack()
{
	// 몬스터 추적 초기화
	bFollowTarget = false;
	FollowTargetAlpha = 0;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;
	bool bResult = false;
	
	TArray<FHitResult> MonsterList;
	if(Attribute == EAttributeKeyword::e_Fire)
	{
		if(Irene->IreneInput->bUseLeftButton)
		{
			FCollisionQueryParams Params(NAME_None, false, Irene);
			bResult = GetWorld()->SweepMultiByChannel(
				MonsterList,
				Irene->GetActorLocation(),
				Irene->GetActorLocation(),
				FRotationMatrix::MakeFromZ(Irene->GetActorForwardVector() * Irene->IreneData.AttackRange).ToQuat(),
				ECollisionChannel::ECC_GameTraceChannel1,
				FCollisionShape::MakeBox(FVector(200, 50, 150)),
				Params);
		}
		if(Irene->IreneInput->bUseRightButton)
		{
			FCollisionQueryParams Params(NAME_None, false, Irene);
			bResult = GetWorld()->SweepMultiByChannel(
				MonsterList,
				Irene->GetActorLocation(),
				Irene->GetActorLocation(),
				FRotationMatrix::MakeFromZ(Irene->GetActorForwardVector() * Irene->IreneData.AttackRange).ToQuat(),
				ECollisionChannel::ECC_GameTraceChannel1,
				FCollisionShape::MakeBox(FVector(400, 50, 400)),
				Params);
		}
	}
	if(Attribute == EAttributeKeyword::e_Water)
	{
		if(Irene->IreneInput->bUseLeftButton)
		{
			FCollisionQueryParams Params(NAME_None, false, Irene);
			bResult = GetWorld()->SweepMultiByChannel(
				MonsterList,
				TargetMonster->GetActorLocation(),
				TargetMonster->GetActorLocation(),
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel1,
				FCollisionShape::MakeSphere(50.0f),
				Params);
		}
		if(Irene->IreneInput->bUseRightButton)
		{
			FCollisionQueryParams Params(NAME_None, false, Irene);
			bResult = GetWorld()->SweepMultiByChannel(
				MonsterList,
				FVector(TargetMonster->GetActorLocation().X,TargetMonster->GetActorLocation().Y,TargetMonster->GetActorLocation().Z-200),
				FVector(TargetMonster->GetActorLocation().X,TargetMonster->GetActorLocation().Y,TargetMonster->GetActorLocation().Z-200),
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel1,
				FCollisionShape::MakeSphere(500.0f),
				Params);			
		}
	}
	if(Attribute == EAttributeKeyword::e_Thunder)
	{
		if(Irene->IreneInput->bUseLeftButton)
		{
			FCollisionQueryParams Params(NAME_None, false, Irene);
			bResult = GetWorld()->SweepMultiByChannel(
				MonsterList,
				Irene->GetActorLocation(),
				Irene->GetActorLocation() + Irene->GetActorForwardVector() * Irene->IreneData.AttackRange,
				FRotationMatrix::MakeFromZ(Irene->GetActorForwardVector() * Irene->IreneData.AttackRange).ToQuat(),
				ECollisionChannel::ECC_GameTraceChannel1,
				FCollisionShape::MakeCapsule(Irene->IreneData.AttackRadius,Irene->IreneData.AttackRange * 0.5f),
				Params);
		}
		if(Irene->IreneInput->bUseRightButton)
		{
			FCollisionQueryParams Params(NAME_None, false, Irene);
			bResult = GetWorld()->SweepMultiByChannel(
				MonsterList,
				CurrentPosVec,
				NowPosVec,
				FRotationMatrix::MakeFromZ(Irene->GetActorForwardVector() * Irene->IreneData.AttackRange).ToQuat(),
				ECollisionChannel::ECC_GameTraceChannel1,
				FCollisionShape::MakeCapsule(Irene->IreneData.AttackRadius,Irene->IreneData.AttackRange * 0.5f),
				Params);
		}
	}

	#if ENABLE_DRAW_DEBUG
	if(Attribute == EAttributeKeyword::e_Fire)
	{
		if(Irene->IreneInput->bUseLeftButton)
		{
			FVector TraceVec = Irene->GetActorForwardVector() * 150;
			FVector Center = Irene->GetActorLocation() + TraceVec + (Irene->GetActorForwardVector()*-50.0f);
			FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
			FColor DrawColor = bResult ? FColor::Green : FColor::Red;
			float DebugLifeTime = 5.0f;
			DrawDebugBox(GetWorld(), Center, FVector(200, 50, 150), CapsuleRot, DrawColor, false, DebugLifeTime);
		}
		if(Irene->IreneInput->bUseRightButton)
		{
			FVector TraceVec = Irene->GetActorForwardVector() * 150;
			FVector Center = Irene->GetActorLocation();
			FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
			FColor DrawColor = bResult ? FColor::Green : FColor::Red;
			float DebugLifeTime = 5.0f;
			DrawDebugBox(GetWorld(), Center, FVector(400, 50, 400), CapsuleRot, DrawColor, false, DebugLifeTime);
		}
	}
	if(Attribute == EAttributeKeyword::e_Water)
	{
		if(Irene->IreneInput->bUseLeftButton)
		{
			FVector Center = FVector(TargetMonster->GetActorLocation().X,TargetMonster->GetActorLocation().Y,TargetMonster->GetActorLocation().Z-200);
			FColor DrawColor = bResult ? FColor::Green : FColor::Red;
			float DebugLifeTime = 5.0f;
			DrawDebugSphere(GetWorld(), Center, 50.0f, 10, DrawColor, false, DebugLifeTime);
		}
		
		if(Irene->IreneInput->bUseRightButton)
		{
			FVector Center = FVector(TargetMonster->GetActorLocation().X,TargetMonster->GetActorLocation().Y,TargetMonster->GetActorLocation().Z-200);
			FColor DrawColor = bResult ? FColor::Green : FColor::Red;
			float DebugLifeTime = 5.0f;
			DrawDebugSphere(GetWorld(), Center, 500.0f, 20, DrawColor, false, DebugLifeTime);
		}
	}
	if(Attribute == EAttributeKeyword::e_Thunder)
	{
		FVector TraceVec = Irene->GetActorForwardVector() * Irene->IreneData.AttackRange;
		FVector Center = Irene->GetActorLocation() + TraceVec * 0.5f;
		float HalfHeight = Irene->IreneData.AttackRange * 0.5f + Irene->IreneData.AttackRadius;
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;
		if(Irene->IreneInput->bUseLeftButton)
		{
			DrawDebugCapsule(GetWorld(),
				Center,
				HalfHeight,
				Irene->IreneData.AttackRadius,
				CapsuleRot,
				DrawColor,
				false,
				DebugLifeTime);
		}
		if(Irene->IreneInput->bUseRightButton)
		{
			DrawDebugCapsule(GetWorld(),
				CurrentPosVec + Irene->GetActorForwardVector()*300*0.5f,
				300,
				Irene->IreneData.AttackRadius,
				CapsuleRot,
				DrawColor,
				false,
				DebugLifeTime);
		}
	}
	#endif
	
	if(Irene->IreneState->IsSkillState())
		bUseMP = true;
	else
		bUseMP = false;
	
	for (FHitResult Monster : MonsterList)
	{
		if (bResult)
		{
			if (Monster.Actor.IsValid())
			{
				FDamageEvent DamageEvent;

				auto Mob = Cast<AMonster>(Monster.Actor);
				if (Mob != nullptr)
				{
					Mob->SetAttackedInfo(bUseMP, 0, (EAttackedDirection)GetAttackDirection());
				}
				UGameplayStatics::ApplyDamage(Monster.Actor.Get(), Irene->IreneData.Strength, nullptr, Irene, nullptr);
			}
		}
	}
	if (bResult)
		Irene->CameraShakeOn = true;
	
	//속성공격 기준 몬스터 할당해제
	if (bResult)
	{
		auto STGameInstance = Cast<USTGameInstance>(Irene->GetGameInstance());
		if (STGameInstance->GetAttributeEffectMonster() != nullptr)
		{
			STGameInstance->ResetAttributeEffectMonster();
		}
	}
}
#pragma endregion Attack

#pragma region State
void UIreneAttackInstance::SetAttackState()const
{
	if(Attribute == EAttributeKeyword::e_Fire)
	{
		if (Irene->IreneAnim->GetCurrentActiveMontage() == nullptr
		&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_1_F")) != 0 && Irene->IreneState->GetStateToString().Compare(FString("B_Attack_3_F")) != 0)
		{
			Irene->ChangeStateAndLog(UBasicAttack1FireState::GetInstance());
		}
		else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack2")
		&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_2_F")) != 0)
		{
			Irene->ChangeStateAndLog(UBasicAttack2FireState::GetInstance());
		}
		else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack3")
		&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_3_F")) != 0)
		{
			Irene->ChangeStateAndLog(UBasicAttack3FireState::GetInstance());
		}
	}
	if(Attribute == EAttributeKeyword::e_Water)
	{
		if (Irene->IreneAnim->GetCurrentActiveMontage() == nullptr
		&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_1_W")) != 0 && Irene->IreneState->GetStateToString().Compare(FString("B_Attack_3_W")))
		{
			Irene->ChangeStateAndLog(UBasicAttack1WaterState::GetInstance());
		}
		else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack2")
		&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_2_W")) != 0)
		{
			Irene->ChangeStateAndLog(UBasicAttack2WaterState::GetInstance());
		}
		else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack3")
		&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_3_W")) != 0)
		{
			Irene->ChangeStateAndLog(UBasicAttack3WaterState::GetInstance());
		}
	}
	if(Attribute == EAttributeKeyword::e_Thunder)
	{
		if (Irene->IreneAnim->GetCurrentActiveMontage() == nullptr
		&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_1_T")) != 0 && Irene->IreneState->GetStateToString().Compare(FString("B_Attack_3_T")))
		{
			Irene->ChangeStateAndLog(UBasicAttack1ThunderState::GetInstance());
		}
		else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack2")
		&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_2_T")) != 0)
		{
			Irene->ChangeStateAndLog(UBasicAttack2ThunderState::GetInstance());
		}
		else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack3")
		&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_3_T")) != 0)
		{
			Irene->ChangeStateAndLog(UBasicAttack3ThunderState::GetInstance());
		}
	}
}
void UIreneAttackInstance::SetSkillState()const
{
	if(Attribute == EAttributeKeyword::e_Fire)
	{
		if (Irene->IreneState->GetStateToString().Compare(FString("Skill_F_Start")) != 0
			&&Irene->IreneState->GetStateToString().Compare(FString("Skill_F_End")) != 0)
		{
			Irene->ChangeStateAndLog(USkillFireStartState::GetInstance());
		}		
	}
	if(Attribute == EAttributeKeyword::e_Water)
	{
		if (Irene->IreneState->GetStateToString().Compare(FString("Skill_W_Start")) != 0
		&&Irene->IreneState->GetStateToString().Compare(FString("Skill_W_End")) != 0)
		{
			Irene->ChangeStateAndLog(USkillWaterStartState::GetInstance());
		}	
	}
	if(Attribute == EAttributeKeyword::e_Thunder)
	{
		if (Irene->IreneState->GetStateToString().Compare(FString("Skill_T_Start")) != 0
		&&Irene->IreneState->GetStateToString().Compare(FString("Skill_T_End")) != 0)
		{
			Irene->ChangeStateAndLog(USkillThunderStartState::GetInstance());
		}
	}
}

#pragma endregion State
