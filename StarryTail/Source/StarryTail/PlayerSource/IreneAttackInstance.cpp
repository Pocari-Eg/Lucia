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
	UseMP = 0.0f;
}

float UIreneAttackInstance::GetATK()
{
	return Irene->IreneData.Strength;
}
EAttributeKeyword UIreneAttackInstance::GetAttribute()
{
	return Attribute;
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
	UseMP = 0.0f;
	Irene->IreneData.CanNextCombo = false;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = 0;
	Irene->IreneUIManager->AttackSoundParameter = 0.0f;
	Irene->IreneUIManager->AttackSound->SetParameter("Attributes", Irene->IreneUIManager->AttackSoundParameter);
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

	TArray<FHitResult> MonsterList;
	FCollisionQueryParams Params(NAME_None, false, Irene);
	bool bResult = GetWorld()->SweepMultiByChannel(
		MonsterList,
		Irene->GetActorLocation(),
		Irene->GetActorLocation() + Irene->GetActorForwardVector() * Irene->IreneData.AttackRange,
		FRotationMatrix::MakeFromZ(Irene->GetActorForwardVector() * Irene->IreneData.AttackRange).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(50.0f),
		Params);

	#if ENABLE_DRAW_DEBUG
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
					Mob->SetAttackedInfo(bUseMP, UseMP);
				}
				UGameplayStatics::ApplyDamage(Monster.Actor.Get(), Irene->IreneData.Strength, nullptr, Irene, nullptr);
			}
		}
	}

	// 마나 회복
	if (bUseMP == false && UseMP != 0.0f)
	{
		Irene->IreneData.CurrentMP += UseMP;

		if (Irene->IreneData.CurrentMP > Irene->IreneData.MaxMP)
			Irene->IreneData.CurrentMP = Irene->IreneData.MaxMP;

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