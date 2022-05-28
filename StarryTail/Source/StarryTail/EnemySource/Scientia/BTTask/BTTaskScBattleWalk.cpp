// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScBattleWalk.h"
#include "../ScAIController.h"
#include "../Scientia.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

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

	Scientia->SetState(TEXT("BattleWalk"));

	MoveRandom = FMath::RandRange(0, 1);

	if (MoveRandom)
	{
		DirValue = 1;
	}
	else
	{
		DirValue = -1;
	}

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

	FVector LookVector = Player->GetActorLocation() - Scientia->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	Scientia->SetActorRotation(FMath::RInterpTo(Scientia->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	const FRotator YawRotation(0, TargetRot.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	Scientia->SetActorLocation(Scientia->GetActorLocation() - ((DirValue * Direction) * Scientia->GetBattleWalkSpeed() * DeltaSeconds));
	
	if (WaitTimer >= WaitTime)
	{
		float Distance = Scientia->GetDistanceToPlayer();

		if (Distance < 1000)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsBattleWalkKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack2Key, true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttackingKey, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		else if (Distance >= 1000 && Distance < 2000)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsBattleWalkKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack3Key, true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttackingKey, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		else if (Distance >= 2000)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsBattleWalkKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack1Key, true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttackingKey, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	
}
