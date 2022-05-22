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

	MoveDir = Player->GetActorLocation() - Scientia->GetLocation();

	NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	NavData = NavSys->GetNavDataForProps(Scientia->GetNavAgentPropertiesRef());

	FilterClass = UNavigationQueryFilter::StaticClass();
	QueryFilter = UNavigationQueryFilter::GetQueryFilter(*NavData, FilterClass);

	RushTimer = 0.0f;
	
	return EBTNodeResult::InProgress;
}
void UBTTaskScAttack3::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	RushTimer += DeltaSeconds;
	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScAIController::PlayerKey));

	if (RushTimer >= Scientia->GetRushTime())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttackingKey, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack3Key, false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	NewLocation = Scientia->GetTransform().GetLocation() + (MoveDir.GetSafeNormal() * Scientia->GetAttack3Speed() * DeltaSeconds);
	
	if (NavData)
	{
		
		MyAIQuery = FPathFindingQuery(this, *NavData, Scientia->GetActorLocation(), NewLocation, QueryFilter);
		bCanMove = NavSys->TestPathSync(MyAIQuery, EPathFindingMode::Regular);
	}
	
	if (bCanMove)
	{
		// Scientia->SetActorLocation(NewLocation);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Scientia->GetController(), Scientia->GetTransform().GetLocation() + MoveDir.GetSafeNormal() * Scientia->GetAttack3Speed());
	}
	else
	{
		STARRYLOG(Log, TEXT("2"));
	}
}
