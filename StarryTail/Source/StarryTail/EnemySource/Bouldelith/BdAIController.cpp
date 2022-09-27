// Fill out your copyright notice in the Description page of Project Settings.


#include "BdAIController.h"
#include "Bouldelith.h"

const FName ABdAIController::IsBattleIdleKey = (TEXT("bIsBattleIdle"));
const FName ABdAIController::IsBattleWalkKey = (TEXT("bIsBattleWalk"));

const FName ABdAIController::IsBackstepKey = (TEXT("bIsBackstep"));


const FName ABdAIController::IsBrokenKey = (TEXT("bIsBroken"));
const FName ABdAIController::IsWallGroggyKey = (TEXT("bIsWallGroggy"));
const FName ABdAIController::IsStatueStateKey = (TEXT("StatueState"));


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
	SetPlayer();

	auto Bouldelith = Cast<ABouldelith>(GetPawn());

	if (Bouldelith->GetBouldelithAnimInstance()->GetAttackIsPlaying())
		return;
	if (Bouldelith->GetBouldelithAnimInstance()->GetBackstepIsPlaying())
		return;

	if (Bouldelith->GetBouldelithAnimInstance()->GetBattleRunIsPlaying())
		Bouldelith->SetIsChangeBattleRunStateToAttackedState(true);

	Blackboard->SetValueAsBool(IsAttackedKey, true);

	Bouldelith->GetBouldelithAnimInstance()->PlayAttackedMontage();
}
void ABdAIController::Broken()
{
	Blackboard->SetValueAsBool(IsAttackedKey, true);
	Blackboard->SetValueAsBool(IsBrokenKey, true);
}

void ABdAIController::SetStatueKey(bool state)
{
	Blackboard->SetValueAsBool(IsStatueStateKey, state);
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