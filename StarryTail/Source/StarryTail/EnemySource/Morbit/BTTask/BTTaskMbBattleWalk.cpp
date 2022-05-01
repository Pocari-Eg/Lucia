// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbBattleWalk.h"
#include "../MbAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "../Morbit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskMbBattleWalk::UBTTaskMbBattleWalk()
{
	NodeName = TEXT("BattleWalk");
}

EBTNodeResult::Type UBTTaskMbBattleWalk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Morbit = Cast<AMorbit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Morbit)
		return EBTNodeResult::Failed;

	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMbAIController::PlayerKey));
	if (nullptr == Player)
		return EBTNodeResult::Failed;

	Morbit->BattleWalk();

	if (!Morbit->GetMorbitAnimInstance()->GetBattleWalkIsPlaying())
		Morbit->GetMorbitAnimInstance()->PlayBattleWalkMontage();

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Morbit->GetController(), Player->GetActorLocation());

	if (Morbit->GetDistanceToPlayer() <= OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AMbAIController::MeleeAttackRangeKey))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::CanMeleeAttackKey, true);
		return EBTNodeResult::Succeeded;
	}
	if (Morbit->GetDistanceToPlayer() > OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AMbAIController::TraceRangeKey))
	{
		Morbit->Walk();
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMbAIController::PlayerKey, nullptr);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::ReturnKey, true);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Succeeded;
}