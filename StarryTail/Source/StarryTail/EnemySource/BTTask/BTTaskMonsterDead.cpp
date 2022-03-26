// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMonsterDead.h"
#include "../Monster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMonsterDead::UBTTaskMonsterDead()
{
	NodeName = TEXT("Dead");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskMonsterDead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Morbit = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Morbit)
		return EBTNodeResult::Failed;

	bIsLive = true;
	Morbit->Death.AddLambda([this]() -> void { bIsLive = false; });

	return EBTNodeResult::InProgress;
}
void UBTTaskMonsterDead::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsLive)
	{
		OwnerComp.GetAIOwner()->GetPawn()->Destroy();
	}
}