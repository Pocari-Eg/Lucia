// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbMilitantBattleWalk.h"
#include "../MbAIController.h"
#include "../../../IreneCharacter.h"
#include "../Morbit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskMbMilitantBattleWalk::UBTTaskMbMilitantBattleWalk()
{
	NodeName = TEXT("MilitantBattleWalk");
}

EBTNodeResult::Type UBTTaskMbMilitantBattleWalk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Morbit = Cast<AMorbit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Morbit)
		return EBTNodeResult::Failed;

	Morbit->BattleWalk();

	auto MbAIController = Cast<AMbAIController>(Morbit->GetController());
	if (nullptr == MbAIController)
		return EBTNodeResult::Failed;

	if (!Morbit->GetMonsterAnimInstance()->GetBattleWalkIsPlaying())
	{
		MbAIController->SetPlayer();
		Morbit->GetMonsterAnimInstance()->PlayBattleWalkMontage();
	}

	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMbAIController::PlayerKey));
	if (nullptr == Player)
		return EBTNodeResult::Failed;

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Morbit->GetController(), Player->GetActorLocation());

	if (Morbit->GetDistanceToPlayer() <= OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AMbAIController::MeleeAttackRangeKey))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::CanMeleeAttackKey, true);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Succeeded;
}