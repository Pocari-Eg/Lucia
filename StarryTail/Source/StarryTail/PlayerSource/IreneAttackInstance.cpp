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
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_FormDataTable(TEXT("/Game/Math/BP_FormDataTable.BP_FormDataTable"));
	if (DT_FormDataTable.Succeeded())
	{
		FormDataTable = DT_FormDataTable.Object;
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
	Attribute = EAttributeKeyword::e_Fire;
	// FormGauge.Add(GetNameAtFormDataTable(FName("Fire"))->F_Gauge);
	// FormGauge.Add(GetNameAtFormDataTable(FName("Water"))->F_Gauge);
	// FormGauge.Add(GetNameAtFormDataTable(FName("Electric"))->F_Gauge);
	FormGauge.Add(GetNameAtFormTimeDataTable(FName("Fire_Form"))->F_Gauge/100);
	FormGauge.Add(GetNameAtFormTimeDataTable(FName("Water_Form"))->F_Gauge/100);
	FormGauge.Add(GetNameAtFormTimeDataTable(FName("Electric_Form"))->F_Gauge/100);
	
	bFollowTarget = false;
	FollowTargetAlpha = 0.0f;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;
	bFollowCameraTarget = false;
	FollowTargetCameraAlpha = 0.0f;
	CameraRot = FRotator::ZeroRotator;
	TargetCameraRot = FRotator::ZeroRotator;

	bUseMP = false;
	UseMPSize = 0.0f;
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
	int FormType = 0;
	if(Attribute == EAttributeKeyword::e_Fire)
		FormType = 0;
	else if(Attribute == EAttributeKeyword::e_Water)
		FormType = 1;
	else if(Attribute == EAttributeKeyword::e_Thunder)
		FormType = 2;

	Irene->Weapon->SetGenerateOverlapEvents(false);
	Irene->IreneInput->bUseLeftButton = false;
	bUseMP = false;
	UseMPSize = 0.0f;
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

		Irene->FindNearMonster();
	}
}
void UIreneAttackInstance::AttackStopCheck()
{
	Irene->IsTimeStopping = false;
	Irene->Weapon->SetGenerateOverlapEvents(false);
}
void UIreneAttackInstance::DoAttack()
{
	// 나중에 카메라 쉐이크 데이터 사용할 때 사용할 것(사용한다면...)
	//WorldController->ClientStartCameraShake(CameraShakeCurve);	

	// 몬스터 추적 초기화
	bFollowTarget = false;
	FollowTargetAlpha = 0;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;
	bool bResult = false;
	
	TArray<FHitResult> MonsterList;
	if(Attribute == EAttributeKeyword::e_Fire)
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
	if(Attribute == EAttributeKeyword::e_Water)
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
	if(Attribute == EAttributeKeyword::e_Thunder)
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

	#if ENABLE_DRAW_DEBUG
	if(Attribute == EAttributeKeyword::e_Fire)
	{
		FVector TraceVec = Irene->GetActorForwardVector() * 150;
		FVector Center = Irene->GetActorLocation() + TraceVec + (Irene->GetActorForwardVector()*-50.0f);
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		DrawDebugBox(GetWorld(), Center, FVector(200, 50, 150), CapsuleRot, DrawColor, false, DebugLifeTime);
	}
	if(Attribute == EAttributeKeyword::e_Water)
	{
		FVector Center = TargetMonster->GetActorLocation();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		DrawDebugSphere(GetWorld(), Center, 50.0f, 10, DrawColor, false, DebugLifeTime);
	}
	if(Attribute == EAttributeKeyword::e_Thunder)
	{
		FVector TraceVec = Irene->GetActorForwardVector() * Irene->IreneData.AttackRange;
		FVector Center = Irene->GetActorLocation() + TraceVec * 0.5f;
		float HalfHeight = Irene->IreneData.AttackRange * 0.5f + Irene->IreneData.AttackRadius;
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		DrawDebugCapsule(GetWorld(),
			Center,
			HalfHeight,
			Irene->IreneData.AttackRadius,
			CapsuleRot,
			DrawColor,
			false,
			DebugLifeTime);
	}
	#endif

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
					Mob->SetAttackedInfo(bUseMP, UseMPSize, (EAttackedDirection)GetAttackDirection());
				}
				UGameplayStatics::ApplyDamage(Monster.Actor.Get(), Irene->IreneData.Strength, nullptr, Irene, nullptr);
			}
		}
	}

	// 마나 회복
	if (bUseMP == false && UseMPSize == 0.0f)
	{
		if(GetAttribute() == EAttributeKeyword::e_None)
		{
			const float FormGaugeValue = GetNameAtFormTimeDataTable(FName("Fire_Form"))->F_Gauge/100;
			for(int i=0;i<3;i++)
			{
				FormGauge[i] += FormGaugeValue/(GetNameAtFormTimeDataTable(FName("Fire_Form"))->Hit_Gauge_Re/100);
				if(FormGauge[i] > FormGaugeValue)
					FormGauge[i] = FormGaugeValue;
			}
			Irene->IreneAttack->FOnFireGaugeChange.Broadcast();
			Irene->IreneAttack->FOnWaterGaugeChange.Broadcast();
			Irene->IreneAttack->FOnElectricGaugeChange.Broadcast();
		}
		Irene->IreneUIManager->OnMpChanged.Broadcast();
	}

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