// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbBattleIdle.h"
#include "../Morbit.h"
#include "../MbAIController.h"
#include "../../../IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMbBattleIdle::UBTTaskMbBattleIdle()
{
	NodeName = TEXT("BattleIdle");
}
EBTNodeResult::Type UBTTaskMbBattleIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Morbit = Cast<AMorbit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Morbit)
		return EBTNodeResult::Failed;

	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMbAIController::PlayerKey));
	if (nullptr == Player)
		return EBTNodeResult::Failed;

	if (!Morbit->GetMonsterAnimInstance()->GetBattleIdleIsPlaying() && !Morbit->GetMonsterAnimInstance()->GetAttackIsPlaying())
		Morbit->GetMonsterAnimInstance()->PlayBattleIdleMontage();

	if (Morbit->GetDistanceToPlayer() > OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AMbAIController::MeleeAttackRangeKey))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::CanMeleeAttackKey, false);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Succeeded;
}