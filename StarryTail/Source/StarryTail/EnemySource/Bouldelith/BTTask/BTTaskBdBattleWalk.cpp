// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdBattleWalk.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBdBattleWalk::UBTTaskBdBattleWalk()
{
	NodeName = TEXT("BattleWalk");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdBattleWalk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->BattleWalk();

	STARRYLOG(Log, TEXT("1"));

	ChangeStateTime = FMath::RandRange(1, 3);
	ChangeStateTimer = 0.0f;

	return EBTNodeResult::InProgress;
}
void UBTTaskBdBattleWalk::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ChangeStateTimer += DeltaSeconds;

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABdAIController::PlayerKey));

	FVector LookVector = Player->GetActorLocation() - Bouldelith->GetLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	Bouldelith->SetActorRotation(FMath::RInterpTo(Bouldelith->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	if (Bouldelith->GetDistanceToPlayer() >= 1000.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleWalkKey, false);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else if (Bouldelith->GetDistanceToPlayer() <= 300.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleWalkKey, false);

		if (Bouldelith->GetIsUseBackstep())
		{
			int Random = FMath::RandRange(0, 1);

			switch (Random)
			{
			case 0:
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsAttack1Key, true);
				break;
			case 1:
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsAttack2Key, true);
				break;
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBackstepKey, true);
		}

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if (ChangeStateTimer >= ChangeStateTime)
	{
		int Random = FMath::RandRange(0, 1);

		switch (Random)
		{
		case 0:
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsAttack1Key, true);
			break;
		case 1:
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsAttack2Key, true);
			break;
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleWalkKey, false);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}