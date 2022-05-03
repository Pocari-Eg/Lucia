// Fill out your copyright notice in the Description page of Project Settings.


#include "BdAIController.h"
#include "Bouldelith.h"

ABdAIController::ABdAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/Bouldelith/BB_Bouldelith"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/Bouldelith/BT_Bouldelith"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}
void ABdAIController::Attacked()
{

}
void ABdAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		// 스폰 위치 저장
		auto Bouldelith = Cast<ABouldelith>(InPawn);

		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		Blackboard->SetValueAsFloat(MeleeAttackRangeKey, Bouldelith->GetMeleeAttackRange());
		Blackboard->SetValueAsFloat(TraceRangeKey, Bouldelith->GetTraceRange());
		if (!RunBehaviorTree(BTAsset))
		{
			STARRYLOG(Warning, TEXT("MbAIController couldn't run behavior tree."));
		}
	}
}