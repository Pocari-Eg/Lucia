// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScBattleWalk.h"
#include "../ScAIController.h"
#include "../Scientia.h"

UBTTaskScBattleWalk::UBTTaskScBattleWalk()
{
	NodeName = TEXT("BattleWalk");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskScBattleWalk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
	Scientia->BattleWalk();

	WaitTimer = 0.0f;
	WaitTime = FMath::RandRange(1.f, 3.f);

	return EBTNodeResult::InProgress;
}
void UBTTaskScBattleWalk::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	WaitTimer += DeltaSeconds;

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScAIController::PlayerKey));

	FVector LookVector = Player->GetActorLocation() - Scientia->GetLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	if (WaitTimer >= WaitTime)
	{
		float Distance = Scientia->GetDistanceToPlayer();

		if (Distance < 1000)
		{
			// Attack2
		}
		else if (Distance >= 1000 && Distance < 2000)
		{
			// Attack3
		}
		else if (Distance >= 2000)
		{
			// Attack1
		}
	}
}