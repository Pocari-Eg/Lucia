// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMonsterSetWalkAnimation.h"
#include "../Monster.h"

UBTTaskMonsterSetWalkAnimation::UBTTaskMonsterSetWalkAnimation()
{
	NodeName = TEXT("SetWalkAnimation");
}
EBTNodeResult::Type UBTTaskMonsterSetWalkAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->PlayWalkAnim();

	return EBTNodeResult::Succeeded;
}