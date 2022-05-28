// Fill out your copyright notice in the Description page of Project Settings.


#include "ScAIController.h"
#include "Scientia.h"

const FName AScAIController::IsChangeKey = (TEXT("bIsChange"));
const FName AScAIController::IsBattleWalkKey = (TEXT("bIsBattleWalk"));

const FName AScAIController::IsAttack1Key = (TEXT("bIsAttack1"));
const FName AScAIController::IsAttack2Key = (TEXT("bIsAttack2"));
const FName AScAIController::IsAttack3Key = (TEXT("bIsAttack3"));
const FName AScAIController::IsAttack4Key = (TEXT("bIsAttack4"));

const FName AScAIController::IsStuckKey = (TEXT("bIsStuck"));
const FName AScAIController::IsDodgeKey = (TEXT("bIsDodge"));

const FName AScAIController::IsCrushedKey = (TEXT("bIsCrushed"));
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
void AScAIController::Attacked()
{
	Blackboard->SetValueAsBool(IsAttackingKey, false);
	Blackboard->SetValueAsBool(IsAttack2Key, false);
	Blackboard->SetValueAsBool(IsAttackedKey, true);
}
void AScAIController::Crushed()
{
	Blackboard->SetValueAsBool(IsBattleWalkKey, false);
	Blackboard->SetValueAsBool(IsChangeKey, false);
	Blackboard->SetValueAsBool(IsStuckKey, false);
	Blackboard->SetValueAsBool(IsDodgeKey, false);
	Blackboard->SetValueAsBool(IsAttackingKey, false);
	Blackboard->SetValueAsBool(IsAttack1Key, false);
	Blackboard->SetValueAsBool(IsAttack2Key, false);
	Blackboard->SetValueAsBool(IsAttack3Key, false);
	Blackboard->SetValueAsBool(IsAttack4Key, false);
	Blackboard->SetValueAsBool(IsCrushedKey, true);
}
void AScAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		// ���� ��ġ ����
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