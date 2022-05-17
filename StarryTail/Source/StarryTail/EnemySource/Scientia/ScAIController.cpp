// Fill out your copyright notice in the Description page of Project Settings.


#include "ScAIController.h"
#include "Scientia.h"

const FName AScAIController::IsChangeKey = (TEXT("bIsChange"));
const FName AScAIController::IsBattleWalkKey = (TEXT("bIsBattleWalk"));

AScAIController::AScAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/Scientia/BB_Scientia"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/Scientia/BT_Scientia"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}
void AScAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		// 스폰 위치 저장
		auto Scientia = Cast<AScientia>(InPawn);

		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		Blackboard->SetValueAsFloat(MeleeAttackRangeKey, Scientia->GetMeleeAttackRange());
		Blackboard->SetValueAsFloat(TraceRangeKey, Scientia->GetTraceRange());
		if (!RunBehaviorTree(BTAsset))
		{
			STARRYLOG(Warning, TEXT("MbAIController couldn't run behavior tree."));
		}
	}
}