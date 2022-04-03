// Fill out your copyright notice in the Description page of Project Settings.

#include "MbAIController.h"
#include "Morbit.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

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
void AMbAIController::SetMilitantAI()
{
	BTAsset = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/AI/Morbit/Occupation/BT_MorbitMilitant"), NULL, LOAD_None, NULL);
	if (!RunBehaviorTree(BTAsset))
	{
		STARRYLOG(Warning, TEXT("MbAIController couldn't run behavior tree."));
	}
}
void AMbAIController::SetDefensiveAI()
{

}