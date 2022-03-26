// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMonsterSetDetectAnimation.h"
#include "../Monster.h"

UBTTaskMonsterSetDetectAnimation::UBTTaskMonsterSetDetectAnimation()
{
	NodeName = TEXT("SetDetectAnimation");
}
EBTNodeResult::Type UBTTaskMonsterSetDetectAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->GetMonsterAnimInstance()->PlayDetectMontage();

	return EBTNodeResult::Succeeded;
}
