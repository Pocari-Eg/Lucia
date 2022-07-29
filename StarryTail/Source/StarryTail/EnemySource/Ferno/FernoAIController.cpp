// Fill out your copyright notice in the Description page of Project Settings.


#include "FernoAIController.h"
#include"Ferno.h"

const FName AFernoAIController::IsCanRangeAttackKey = (TEXT("bCanRangeAttack"));

AFernoAIController::AFernoAIController()
{


	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/Ferno/BB_Ferno"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/Ferno/BT_Ferno"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AFernoAIController::Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback)
{

	//공격 받았을때 애니메이션 실행 
	SetPlayer();


}

void AFernoAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		// 스폰 위치 저장
		auto Ferno = Cast<AFerno>(InPawn);

		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		Blackboard->SetValueAsFloat(MeleeAttackRangeKey, Ferno->GetMeleeAttackRange());
		Blackboard->SetValueAsFloat(TraceRangeKey, Ferno->GetTraceRange());
		if (!RunBehaviorTree(BTAsset))
		{
			STARRYLOG(Warning, TEXT("FernoAIController couldn't run behavior tree."));
		}
	}
}
