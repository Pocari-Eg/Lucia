// Fill out your copyright notice in the Description page of Project Settings.


#include "BellarusAIController.h"
#include "Bellarus.h"

ABellarusAIController::ABellarusAIController()
{

	
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/Bellarus/BB_Bellarus"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/Bellarus/BT_Bellarus"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

}

void ABellarusAIController::Attack()
{
	auto Bellarus = Cast<ABellarus>(GetPawn());
	Bellarus->Attack();
	StopMovement();
	
}

void ABellarusAIController::Attacked()
{

	Blackboard->SetValueAsBool(IsAttackedKey, true);

}

void ABellarusAIController::Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback)
{

	//공격 받았을때 애니메이션 실행 
	SetPlayer();


}

void ABellarusAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		// 스폰 위치 저장
		auto Bellarus = Cast<ABellarus>(InPawn);

		M_MaxAttacked = Bellarus->GetMaxAttacked();
		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		Blackboard->SetValueAsFloat(TraceRangeKey, Bellarus->GetTraceRange());
		if (!RunBehaviorTree(BTAsset))
		{
			STARRYLOG(Warning, TEXT("BellarusAIController couldn't run behavior tree."));
		}
	}
}


