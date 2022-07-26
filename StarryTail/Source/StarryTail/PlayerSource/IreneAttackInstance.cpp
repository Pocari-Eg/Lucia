﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneAttackInstance.h"
#include "IreneCharacter.h"
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
	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_FireBuff(TEXT("/Game/Effect/VFX_Irene/Feather/Buff/Ps_Buff_f.Ps_Buff_F"));
	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_WaterBuff(TEXT("/Game/Effect/VFX_Irene/Feather/Buff/Ps_Buff_w.Ps_Buff_W"));
	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_ThunderBuff(TEXT("/Game/Effect/VFX_Irene/Feather/Buff/Ps_Buff_t.Ps_Buff_T"));
	if (PS_FireBuff.Succeeded() && PS_WaterBuff.Succeeded() && PS_ThunderBuff.Succeeded())
	{
		BuffParticle.Add(PS_FireBuff.Object);
		BuffParticle.Add(PS_WaterBuff.Object);
		BuffParticle.Add(PS_ThunderBuff.Object);
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
	SwordTargetMonster = nullptr;
	//초기 속성
	SwordAttribute = EAttributeKeyword::e_Fire;
	QuillAttribute = EAttributeKeyword::e_Water;

	bFollowTarget = false;
	FollowTargetAlpha = 0.0f;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;
	bFollowCameraTarget = false;
	FollowTargetCameraAlpha = 0.0f;
	CameraRot = FRotator::ZeroRotator;
	TargetCameraRot = FRotator::ZeroRotator;

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
		Irene->IreneUIManager->AttackSound->SoundPlay2D();
		Irene->IreneUIManager->AttackVoiceSound->SoundPlay2D();
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
void UIreneAttackInstance::FireQuillStack(const int Value)
{
	if(Value == 0)
		return;
	switch (Value)
	{
	case 1:
		Irene->IreneData.FireQuillStackDmg = 1.2f;
		break;
	case 2:
		Irene->IreneData.FireQuillStackDmg = 1.5f;
		break;
	case 3:
		Irene->IreneData.FireQuillStackDmg = 2.0f;
		break;
	default: break;
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BuffParticle[0],Irene->GetActorLocation());
	GetWorld()->GetTimerManager().SetTimer(FireQuillStackTimerHandle, this, &UIreneAttackInstance::ResetFireQuillStack, 5.0f, false);
}
void UIreneAttackInstance::WaterQuillStack(const int Value)
{
	if(Value == 0)
		return;
	switch (Value)
	{
	case 1:
		Irene->IreneData.Shield = 100;
		break;
	case 2:
		Irene->IreneData.Shield = 200;
		break;
	case 3:
		Irene->IreneData.Shield = 300;
		break;
	default: break;
	}
	Irene->ShieldComp->SetVisibility(true);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BuffParticle[1],Irene->GetActorLocation());
	GetWorld()->GetTimerManager().SetTimer(WaterQuillStackTimerHandle, this, &UIreneAttackInstance::ResetWaterQuillStack, 120.0f, false);
}
void UIreneAttackInstance::ThunderQuillStack(const int Value)
{
	if(Value == 0)
		return;
	switch (Value)
	{
	case 1:
		Irene->IreneData.ThunderQuillStackSpeed = 1.05f;
		break;
	case 2:
		Irene->IreneData.ThunderQuillStackSpeed = 1.10f;
		break;
	case 3:
		Irene->IreneData.ThunderQuillStackSpeed = 1.20f;
		break;
	default: break;
	}
	if(Irene->GetCharacterMovement()->MaxWalkSpeed == Irene->IreneData.RunMaxSpeed ||
		Irene->GetCharacterMovement()->MaxWalkSpeed == Irene->IreneData.SprintMaxSpeed)
	Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->GetCharacterMovement()->MaxWalkSpeed * Irene->IreneData.ThunderQuillStackSpeed;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BuffParticle[2],Irene->GetActorLocation());
	GetWorld()->GetTimerManager().SetTimer(ThunderQuillStackTimerHandle, this, &UIreneAttackInstance::ResetThunderQuillStack, 10.0f, false);
}
void UIreneAttackInstance::ResetFireQuillStack()
{
	GetWorld()->GetTimerManager().ClearTimer(FireQuillStackTimerHandle);	
	Irene->IreneData.FireQuillStackDmg = 1.0f;
}
void UIreneAttackInstance::ResetWaterQuillStack()
{
	GetWorld()->GetTimerManager().ClearTimer(WaterQuillStackTimerHandle);	
	Irene->ShieldComp->SetVisibility(false);
	Irene->IreneData.Shield = 0;
}
void UIreneAttackInstance::ResetThunderQuillStack()
{
	GetWorld()->GetTimerManager().ClearTimer(ThunderQuillStackTimerHandle);
	if(Irene->GetCharacterMovement()->MaxWalkSpeed == Irene->IreneData.RunMaxSpeed * Irene->IreneData.ThunderQuillStackSpeed ||
		Irene->GetCharacterMovement()->MaxWalkSpeed == Irene->IreneData.SprintMaxSpeed * Irene->IreneData.ThunderQuillStackSpeed)
			Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->GetCharacterMovement()->MaxWalkSpeed / Irene->IreneData.ThunderQuillStackSpeed;
	Irene->IreneData.ThunderQuillStackSpeed = 1.0f;
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