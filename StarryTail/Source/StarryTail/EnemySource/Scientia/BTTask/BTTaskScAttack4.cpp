// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScAttack4.h"
#include "../Scientia.h"
#include "../ScAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
UBTTaskScAttack4::UBTTaskScAttack4()
{
	NodeName = TEXT("Attack4");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskScAttack4::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());

	Scientia->Attack4();

	bIsDrop = true;

	Scientia->DropEnd.AddLambda([this]() -> void {
		bIsDrop = false;
		});

	return EBTNodeResult::InProgress;
}
void UBTTaskScAttack4::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsDrop)
	{
		auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());

		Scientia->BattleIdle();
		Scientia->GetCharacterMovement()->MaxWalkSpeed = Scientia->GetAttack4Speed();

		bIsDrop = true;
		bIsMove = true;
	}
	if (bIsMove)
	{
		auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
		auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScAIController::PlayerKey));

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Scientia->GetController(), Player->GetActorLocation());

		if (Scientia->GetDistanceToPlayer() < 500.f)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack4Key, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack2Key, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
