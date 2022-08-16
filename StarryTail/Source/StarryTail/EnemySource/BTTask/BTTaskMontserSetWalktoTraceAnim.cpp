// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMontserSetWalktoTraceAnim.h"
#include "../Monster.h"

UBTTaskMontserSetWalktoTraceAnim::UBTTaskMontserSetWalktoTraceAnim()
{
	NodeName = TEXT("SetWalktoTraceAnim");
}
EBTNodeResult::Type UBTTaskMontserSetWalktoTraceAnim::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->GetMonsterAnimInstance()->PlayWalktoTraceMontage();

	return EBTNodeResult::Succeeded;
}

