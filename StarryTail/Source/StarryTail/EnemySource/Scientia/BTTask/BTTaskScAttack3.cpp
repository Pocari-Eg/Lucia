// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScAttack3.h"
#include "../Scientia.h"
#include "../ScAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskScAttack3::UBTTaskScAttack3()
{
	NodeName = TEXT("Attack3");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskScAttack3::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScAIController::PlayerKey));

	Scientia->Attack3();

	Scientia->SetState(TEXT("Attack3"));

	MoveDir = Player->GetActorLocation() - Scientia->GetActorLocation();
	MoveDir.Z = Scientia->GetActorLocation().Z;

	NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	NavData = NavSys->GetNavDataForProps(Scientia->GetNavAgentPropertiesRef());

	FilterClass = UNavigationQueryFilter::StaticClass();
	QueryFilter = UNavigationQueryFilter::GetQueryFilter(*NavData, FilterClass);
	
	Scientia->TurnEnd.Clear();
	Scientia->TurnEnd.AddLambda([this, Scientia, Player]() -> void
		{
			bIsTurn = false;
		});
	Scientia->RushStart.AddLambda([this]() -> void {
			bIsRush = true;
		});
	
	return EBTNodeResult::InProgress;
}
void UBTTaskScAttack3::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsTurn)
		return;

	RushTimer += DeltaSeconds;
	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScAIController::PlayerKey));

	if (RushTimer >= Scientia->GetRushTime())
	{
		Scientia->RushEnd();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttackingKey, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack3Key, false);
		RushTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	if (!bIsRush && !bIsTurn)
	{
		MoveDir = Player->GetActorLocation() - Scientia->GetActorLocation();
		FVector LookVector = MoveDir;
		LookVector.Z = 0.0f;
		FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

		Scientia->SetActorRotation(TargetRot);//FMath::RInterpTo(Scientia->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
		StartLocation = Scientia->GetTransform().GetLocation();
		DrawDebugLine(GetWorld(), Scientia->GetActorLocation(), Scientia->GetActorLocation() + (LookVector * Scientia->GetRushTestRange()), FColor::Red, false, 0.2f);
		return;
	}

	NewLocation = StartLocation + (MoveDir.GetSafeNormal() * Scientia->GetRushTestRange());

	//DrawDebugLine(GetWorld(), Scientia->GetActorLocation(), NewLocation, FColor::Blue, false, 1.0f);
	if (NavData)
	{
		MyAIQuery = FPathFindingQuery(this, *NavData, Scientia->GetActorLocation(), NewLocation, QueryFilter);
		bCanMove = NavSys->TestPathSync(MyAIQuery, EPathFindingMode::Regular);
	}
	
	if (bCanMove)
	{
		FVector Normal = MoveDir.GetSafeNormal();
		Normal.Z = 0.0f;
		FVector Dir = StartLocation + (Normal * Scientia->GetAttack3Speed() * DeltaSeconds);
		StartLocation= StartLocation + (Normal * Scientia->GetAttack3Speed() * DeltaSeconds);
		Dir.Z = Scientia->GetActorLocation().Z;
		Scientia->SetActorLocation(Dir);
	}
	else
	{
		bIsTurn = true;

		Scientia->Turn();
		bIsRush = false;
	}
}