// Fill out your copyright notice in the Description page of Project Settings.

#include "MbAIController.h"
#include "Morbit.h"

AMbAIController::AMbAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/Morbit/BB_Morbit"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/Morbit/BT_Morbit"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

}

void AMbAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		// 스폰 위치 저장
		auto Morbit = Cast<AMorbit>(InPawn);

		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		Blackboard->SetValueAsFloat(MeleeAttackRangeKey, Morbit->GetMeleeAttackRange());
		Blackboard->SetValueAsFloat(TraceRangeKey, Morbit->GetTraceRange());
		if (!RunBehaviorTree(BTAsset))
		{
			STARRYLOG(Warning, TEXT("MbAIController couldn't run behavior tree."));
		}
	}
}
void AMbAIController::Attacked()
{

}
void AMbAIController::Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback)
{
	if (AttackedPower == EAttackedPower::Halved && !bIsKnockback)
	{
		STARRYLOG(Log, TEXT("1"));
		return;
	}

	SetPlayer();

	auto Morbit = Cast<AMorbit>(GetPawn());

	bIsPlayerUseMana = bIsKnockback;

	if (Morbit != nullptr)
	{
		if (!Morbit->GetMorbitAnimInstance()->GetAttackIsPlaying())
		{
			Blackboard->SetValueAsBool(IsAttackedKey, true);
			if (!bIsPlayerUseMana)
			{
				if (AttackedPower == EAttackedPower::Normal || AttackedPower == EAttackedPower::Critical)
				{
					if (AttackedDirection == EAttackedDirection::Left)
						Morbit->GetMorbitAnimInstance()->PlayAttackedRightMontage();
					else if (AttackedDirection == EAttackedDirection::Right)
						Morbit->GetMorbitAnimInstance()->PlayAttackedLeftMontage();
				}
			}
			else
			{
				if (AttackedPower == EAttackedPower::Normal || AttackedPower == EAttackedPower::Critical)
				{
					if (AttackedDirection == EAttackedDirection::Left)
						Morbit->GetMorbitAnimInstance()->PlayAttackedCriticalRightMontage();
					else if (AttackedDirection == EAttackedDirection::Right)
						Morbit->GetMorbitAnimInstance()->PlayAttackedCriticalLeftMontage();
					else if (AttackedDirection == EAttackedDirection::Up || AttackedDirection == EAttackedDirection::Down)
						Morbit->GetMorbitAnimInstance()->PlayRollingMontage();
				}
			}
		}
		else
		{
			if (bIsPlayerUseMana)
			{
				Blackboard->SetValueAsBool(IsAttackingKey, false);
				Morbit->GetMorbitAnimInstance()->AttackEnd;
				if (AttackedDirection == EAttackedDirection::Left)
					Morbit->GetMorbitAnimInstance()->PlayAttackedCriticalRightMontage();
				else if (AttackedDirection == EAttackedDirection::Right)
					Morbit->GetMorbitAnimInstance()->PlayAttackedCriticalLeftMontage();
				else if (AttackedDirection == EAttackedDirection::Up || AttackedDirection == EAttackedDirection::Down)
					Morbit->GetMorbitAnimInstance()->PlayRollingMontage();
				Blackboard->SetValueAsBool(IsAttackedKey, true);
			}
		}
	}
}