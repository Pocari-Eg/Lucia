// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMonsterSetIdleAnimation.h"
#include "../Monster.h"

UBTTaskMonsterSetIdleAnimation::UBTTaskMonsterSetIdleAnimation()
{
	NodeName = TEXT("SetIdleAnimation");
}
EBTNodeResult::Type UBTTaskMonsterSetIdleAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->PlayIdleAnim();

	return EBTNodeResult::Succeeded;
}