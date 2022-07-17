﻿// Fill out your copyright notice in the Description page of Project Settings.


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
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_FormTimeDataTable(TEXT("/Game/Math/BP_FormTimeDataTable.BP_FormTimeDataTable"));
	if (DT_FormTimeDataTable.Succeeded())
	{
		FormTimeDataTable = DT_FormTimeDataTable.Object;
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
	SwordAttribute = EAttributeKeyword::e_Fire;
	QuillAttribute = EAttributeKeyword::e_Fire;

	bFollowTarget = false;
	FollowTargetAlpha = 0.0f;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;
	bFollowCameraTarget = false;
	FollowTargetCameraAlpha = 0.0f;
	CameraRot = FRotator::ZeroRotator;
	TargetCameraRot = FRotator::ZeroRotator;

	bUseMP = false;
	bMoveSkip = false;
	bDodgeJumpSkip = false;
	bReAttackSkip = false;
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
	if(SwordAttribute == EAttributeKeyword::e_Fire)
	{
		AttributeName = AttributeName + FString("_F");
	}
	else if(SwordAttribute == EAttributeKeyword::e_Water)
	{
		AttributeName = AttributeName + FString("_W");
	}
	else if(SwordAttribute == EAttributeKeyword::e_Thunder)
	{
		AttributeName = AttributeName + FString("_T");
	}
	return FName(AttributeName);
}
FName UIreneAttackInstance::GetActionAttackDataTableName()
{
	// 스킬 데이터 테이블 이름 받기 위해 현재 속성에 따라 해당하는 이름을 리턴하는 함수
	FName ActionForm = FName("");
	if(SwordAttribute == EAttributeKeyword::e_Fire)
	{
		ActionForm = FName("Skill_F");
	}
	else if(SwordAttribute == EAttributeKeyword::e_Water)
	{
		ActionForm = FName("Skill_W");
	}
	else if(SwordAttribute == EAttributeKeyword::e_Thunder)
	{
		ActionForm = FName("Skill_T");
	}
	return ActionForm;
}

void UIreneAttackInstance::AttackStartComboState()
{
	// 노티파이 NextAttackCheck 도달 시 실행
	Irene->IreneData.CanNextCombo = true;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = FMath::Clamp<int32>(Irene->IreneData.CurrentCombo + 1, 1, Irene->IreneData.MaxCombo);
}
void UIreneAttackInstance::AttackEndComboState()
{
	Irene->IreneData.IsAttacking = false;
	Irene->Weapon->SetGenerateOverlapEvents(false);
	Irene->IreneInput->bUseLeftButton = false;
	bUseMP = false;
	Irene->IreneData.CanNextCombo = false;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = 0;
}
void UIreneAttackInstance::AttackTimeEndState()
{
	// 몽타주가 완전히 끝남
	Irene->IreneData.IsAttacking = false;
	Irene->Weapon->SetGenerateOverlapEvents(false);
	Irene->IreneInput->bUseLeftButton = false;
	Irene->IreneInput->bUseRightButton = false;
	bUseMP = false;
	Irene->IreneData.CanNextCombo = false;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = 0;
	if (!Irene->IreneState->IsDodgeState() && !Irene->IreneState->IsJumpState() && !Irene->IreneState->IsChargeState() && !Irene->IreneState->IsIdleState())
	{
		//STARRYLOG(Error,TEXT("%d,   %d,   %d,   %d"),Irene->IreneInput->MoveKey[0],Irene->IreneInput->MoveKey[1],Irene->IreneInput->MoveKey[2],Irene->IreneInput->MoveKey[3]);
		//Irene->ActionEndChangeMoveState();
		Irene->ChangeStateAndLog(UBattleIdleState::GetInstance());
	}	
}

void UIreneAttackInstance::AttackCheck()
{
	// 노티파이 AttackHitCheck 도달 시 실행
	if (Irene->IreneAnim->GetCurrentActiveMontage())
	{
		Irene->Weapon->SetGenerateOverlapEvents(true);
		Irene->IreneUIManager->AttackSound->SoundPlay2D();
		Irene->IreneUIManager->AttackVoiceSound->SoundPlay2D();
		if(Irene->IreneAnim->GetCurrentActiveMontage())
		{
			// 타겟몬스터가 필요 없는 조건
			if(Irene->IreneAnim->GetCurrentActiveMontage()->GetName() != FString("IreneThunderSkill_Montage")&&
				Irene->IreneAnim->GetCurrentActiveMontage()->GetName() != FString("IreneFireSkill1_Montage")&&
				Irene->IreneAnim->GetCurrentActiveMontage()->GetName() != FString("IreneFireSkill2_Montage"))
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

	// 몬스터 추적 초기화
	bFollowTarget = false;
	FollowTargetAlpha = 0;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;
	bool bResult = false;
	
	TArray<FHitResult> MonsterList;
	FCollisionQueryParams Params(NAME_None, false, Irene);
	bResult = GetWorld()->SweepMultiByChannel(
	MonsterList,
	Irene->GetActorLocation() + (Irene->GetActorForwardVector()*100.0f),
	Irene->GetActorLocation() + (Irene->GetActorForwardVector()*100.0f),
	FRotationMatrix::MakeFromZ(Irene->GetActorForwardVector()).ToQuat(),
	ECollisionChannel::ECC_GameTraceChannel1,
	FCollisionShape::MakeBox(FVector(200, 50, 150)),
	Params);
	
	// 그리기 시작
	#if ENABLE_DRAW_DEBUG
		FVector TraceVec = Irene->GetActorForwardVector();
		FVector Center = Irene->GetActorLocation() + (Irene->GetActorForwardVector()*100.0f);
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;
		DrawDebugBox(GetWorld(), Center, FVector(200, 50, 150), CapsuleRot, DrawColor, false, DebugLifeTime);
	#endif

	// 스킬이면 마나사용으로 취급 (몬스터 데미지 계산에 필요)
	if(Irene->IreneState->IsSkillState())
		bUseMP = true;
	else
		bUseMP = false;

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
				{
					Mob->SetAttackedInfo(bUseMP, 0, EAttackedDirection::Down);
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
	// 현재 속성과 상태를 이용하여 다음 기본공격 상태로 전이 할 수 있는지 확인하는 함수
	if(SwordAttribute == EAttributeKeyword::e_Fire)
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
	if(SwordAttribute == EAttributeKeyword::e_Water)
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
	if(SwordAttribute == EAttributeKeyword::e_Thunder)
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
	// 현재 속성을 이용하여 해당하는 스킬 상태로 전이 할 수 있는지 확인하는 함수
	if(SwordAttribute == EAttributeKeyword::e_Fire)
	{
		if (Irene->IreneState->GetStateToString().Compare(FString("Skill_F_Start")) != 0
			&&Irene->IreneState->GetStateToString().Compare(FString("Skill_F_End")) != 0)
		{
			Irene->ChangeStateAndLog(USkillFireStartState::GetInstance());
		}		
	}
	if(SwordAttribute == EAttributeKeyword::e_Water)
	{
		if (Irene->IreneState->GetStateToString().Compare(FString("Skill_W_Start")) != 0
		&&Irene->IreneState->GetStateToString().Compare(FString("Skill_W_End")) != 0)
		{
			Irene->ChangeStateAndLog(USkillWaterStartState::GetInstance());
		}	
	}
	if(SwordAttribute == EAttributeKeyword::e_Thunder)
	{
		if ((Irene->IreneState->GetStateToString().Compare(FString("Skill_T_Start")) != 0
		&&Irene->IreneState->GetStateToString().Compare(FString("Skill_T_End")) != 0) || bSkillSkip)
		{
			Irene->ChangeStateAndLog(USkillThunderStartState::GetInstance());
		}
	}
}
#pragma endregion State

#pragma region GetSet
FName UIreneAttackInstance::GetAttributeToFormTimeDataTableName() const
{
	// 현재 속성에 따라 FormTimeDataTable에서 사용하는 Name 리턴하는 함수
	switch (SwordAttribute)
	{
	case EAttributeKeyword::e_Fire: return FName("Fire_Form");
	case EAttributeKeyword::e_Water: return FName("Water_Form");
	case EAttributeKeyword::e_Thunder: return FName("Thunder_Form");
	default: return FName("Error GetAttributeToFormTimeDataTableName");
	}
}
#pragma endregion GetSet