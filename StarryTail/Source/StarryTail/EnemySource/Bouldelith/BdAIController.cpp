// Fill out your copyright notice in the Description page of Project Settings.


#include "BdAIController.h"
#include "Bouldelith.h"

const FName ABdAIController::IsBattleIdleKey = (TEXT("bIsBattleIdle"));
const FName ABdAIController::IsBattleWalkKey = (TEXT("bIsBattleWalk"));

const FName ABdAIController::IsWallGroggyKey = (TEXT("bIsWallGroggy"));
const FName ABdAIController::IsBattleRunKey = (TEXT("bIsBattleRun"));
const FName ABdAIController::IsWalkPointKey = (TEXT("WalkPointKey"));

const FName ABdAIController::B_WalkLeftKey = (TEXT("B_WalkLeft"));
const FName ABdAIController::B_WalkRightKey = (TEXT("B_WalkRight"));

const FName ABdAIController::Attack5Key = (TEXT("Attack5Active"));

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
	/*SetPlayer();

	SetStatueKey(false);	Blackboard->SetValueAsBool(IsAttackingKey,false);
	Blackboard->SetValueAsBool(IsAttackCoolKey, false);
	auto Bouldelith = Cast<ABouldelith>(GetPawn());

	Bouldelith->GetBouldelithAnimInstance()->SetbIsState(false);

	if (Bouldelith->GetBouldelithAnimInstance()->GetAttackIsPlaying())
		return;
	if (Bouldelith->GetBouldelithAnimInstance()->GetBackstepIsPlaying())
		return;

	if (Bouldelith->GetBouldelithAnimInstance()->GetBattleRunIsPlaying())
		Bouldelith->SetIsChangeBattleRunStateToAttackedState(true);*/

	Blackboard->SetValueAsBool(IsAttackedKey, true);

	//Bouldelith->GetBouldelithAnimInstance()->PlayAttackedMontage();

	Blackboard->SetValueAsBool(IsAttackingKey, false);
	Blackboard->SetValueAsBool(IsAttackCoolKey, false);
}
void ABdAIController::Broken()
{
	Blackboard->SetValueAsBool(IsAttackedKey, true);
}


void ABdAIController::SetBattleRunKey(bool state)
{
	Blackboard->SetValueAsBool(IsBattleRunKey, state);
}

void ABdAIController::SetWalkPoint(FVector Location)
{
	Blackboard->SetValueAsVector(IsWalkPointKey, Location);
}

void ABdAIController::Attack()
{

}
void ABdAIController::WallGroggy()
{
	Blackboard->SetValueAsBool(IsAttackedKey, true);
	Blackboard->SetValueAsBool(IsWallGroggyKey, true);
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