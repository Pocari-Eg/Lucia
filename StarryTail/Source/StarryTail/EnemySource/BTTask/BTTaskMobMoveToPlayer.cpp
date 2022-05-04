// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobMoveToPlayer.h"
#include "../Monster.h"
#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskMobMoveToPlayer::UBTTaskMobMoveToPlayer()
{
	NodeName = TEXT("MoveToPlayer");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskMobMoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));

	return EBTNodeResult::InProgress;
}
void UBTTaskMobMoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

}
