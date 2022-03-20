// Fill out your copyright notice in the Description page of Project Settings.

#include "MbAIController.h"
#include "../../StarryTail.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AMbAIController::SpawnPosKey(TEXT("SpawnPos"));
const FName AMbAIController::PatrolPosKey(TEXT("PatrolPos"));

const FName AMbAIController::PlayerKey(TEXT("Player"));
const FName AMbAIController::TraceRangeKey(TEXT("TraceRange"));

const FName AMbAIController::MeleeAttackRangeKey(TEXT("MeleeAttackRange"));
const FName AMbAIController::CanMeleeAttackKey(TEXT("bCanMeleeAttack"));
const FName AMbAIController::IsAttackingKey(TEXT("bIsAttacking"));

const FName AMbAIController::IsAttackedKey(TEXT("bIsAttacked"));
const FName AMbAIController::IsGroggyKey(TEXT("bIsGroggy"));

const FName AMbAIController::ReturnKey(TEXT("bReturn"));

AMbAIController::AMbAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_Morbit"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_Morbit"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	MeleeAttackRange = 100.0f;
	TraceRange = 1000.0f;

	
}

void AMbAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		// 스폰 위치 저장
		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		Blackboard->SetValueAsFloat(MeleeAttackRangeKey, MeleeAttackRange);
		Blackboard->SetValueAsFloat(TraceRangeKey, TraceRange);
		if (!RunBehaviorTree(BTAsset))
		{
			STARRYLOG(Warning, TEXT("MbAIController couldn't run behavior tree."));
		}
	}
}
void AMbAIController::Attacked(AIreneCharacter* Player)
{
	Blackboard->SetValueAsObject(PlayerKey, Player);

	Blackboard->SetValueAsBool(IsAttackedKey, true);

	int Random = FMath::RandRange(0, 1);

	if (Random == 1)
	{
		Blackboard->SetValueAsBool(IsGroggyKey, true);
	}
}