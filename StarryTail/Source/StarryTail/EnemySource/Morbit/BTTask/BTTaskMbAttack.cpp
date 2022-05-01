// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbAttack.h"
#include "../Morbit.h"
#include "../MbAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTaskMbAttack::UBTTaskMbAttack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskMbAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Morbit = Cast<AMorbit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Morbit)
		return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsAttackingKey, true);

	Morbit->Attack();

	bIsAttacking = true;
	Morbit->AttackEnd.AddLambda([this]() -> void { bIsAttacking = false; });

	auto MorbitAnimInstance = Morbit->GetMorbitAnimInstance();
	if (!MorbitAnimInstance->GetAttackIsPlaying())
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}
void UBTTaskMbAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsAttackingKey, false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}