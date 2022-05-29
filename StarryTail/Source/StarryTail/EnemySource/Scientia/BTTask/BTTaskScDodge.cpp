// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScDodge.h"
#include "../Scientia.h"
#include "../ScAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


UBTTaskScDodge::UBTTaskScDodge()
{
	NodeName = TEXT("Dodge");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskScDodge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScAIController::PlayerKey));

	Scientia->Dodge();

	Scientia->SetState(TEXT("Dodge"));

	bIsDodge = true;

	MoveDir = (Scientia->GetLocation() - Player->GetActorLocation());

	NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	NavData = NavSys->GetNavDataForProps(Scientia->GetNavAgentPropertiesRef());

	FilterClass = UNavigationQueryFilter::StaticClass();
	QueryFilter = UNavigationQueryFilter::GetQueryFilter(*NavData, FilterClass);

	NewLocation = Scientia->GetActorLocation() + (MoveDir.GetSafeNormal() * Scientia->GetDodgeSpeed());
	NewLocation.Z = Scientia->GetActorLocation().Z;

	FVector LookVector = MoveDir * -1;
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	Scientia->SetActorRotation(TargetRot);

	Scientia->DodgeEnd.AddLambda([this]() -> void {
		bIsDodge = false;
		});

	// Scientia->SetActorLocation(FMath::VInterpTo(Scientia->GetActorLocation(), NewLocation, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::InProgress;
}
void UBTTaskScDodge::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());

	if (NavData)
	{
		MyAIQuery = FPathFindingQuery(this, *NavData, Scientia->GetActorLocation(), Scientia->GetTransform().GetLocation() + (MoveDir.GetSafeNormal() * 300), QueryFilter);
		bCanMove = NavSys->TestPathSync(MyAIQuery, EPathFindingMode::Regular);
	}
	if (bCanMove)
	{		Scientia->SetActorLocation(FMath::VInterpTo(Scientia->GetActorLocation(), NewLocation, GetWorld()->GetDeltaSeconds(), 4.0f));
	}
	if (!bIsDodge)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsDodgeKey, false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
