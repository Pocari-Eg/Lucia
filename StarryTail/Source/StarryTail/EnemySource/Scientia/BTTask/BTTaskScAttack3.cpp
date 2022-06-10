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

	MoveDir = Player->GetActorLocation() - Scientia->GetLocation();

	NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	NavData = NavSys->GetNavDataForProps(Scientia->GetNavAgentPropertiesRef());

	FilterClass = UNavigationQueryFilter::StaticClass();
	QueryFilter = UNavigationQueryFilter::GetQueryFilter(*NavData, FilterClass);
	
	TurnCoolTimer = 1;

	Scientia->TurnEnd.Clear();
	Scientia->TurnEnd.AddLambda([this, Scientia, Player]() -> void
		{
			MoveDir = Player->GetActorLocation() - Scientia->GetLocation();
			bIsTurn = false;
		});
	Scientia->RushStart.AddLambda([this, Player, Scientia]() -> void {
			MoveDir = Player->GetActorLocation() - Scientia->GetLocation();
			bIsRush = true;
		});
	
	return EBTNodeResult::InProgress;
}
void UBTTaskScAttack3::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsTurn)
		return;

	TurnCoolTimer -= DeltaSeconds;
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

	if (!bIsRush)
		return;

	NewLocation = Scientia->GetTransform().GetLocation() + (MoveDir.GetSafeNormal() * 300);
	
	if (NavData)
	{
		MyAIQuery = FPathFindingQuery(this, *NavData, Scientia->GetActorLocation(), NewLocation, QueryFilter);
		bCanMove = NavSys->TestPathSync(MyAIQuery, EPathFindingMode::Regular);
	}
	
	if (bCanMove)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Scientia->GetController(), Scientia->GetTransform().GetLocation() + MoveDir.GetSafeNormal() * 300);
	}
	else if(TurnCoolTimer <= 0.0f)
	{
		TurnCoolTimer = 1;
		bIsTurn = true;

		Scientia->Turn();
		bIsRush = false;
	}
}