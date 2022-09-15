// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMonsterSetTraceAnim.h"
#include "../Monster.h"
UBTTaskMonsterSetTraceAnim::UBTTaskMonsterSetTraceAnim()
{
	NodeName = TEXT("SetTraceAnim");
}
EBTNodeResult::Type UBTTaskMonsterSetTraceAnim::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->GetMonsterAnimInstance()->PlayBattleWalkMontage();

	return EBTNodeResult::Succeeded;
}
