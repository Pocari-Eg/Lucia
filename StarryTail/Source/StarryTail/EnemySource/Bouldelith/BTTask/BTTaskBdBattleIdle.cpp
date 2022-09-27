// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdBattleIdle.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include"../../../STGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBdBattleIdle::UBTTaskBdBattleIdle()
{
	NodeName = TEXT("BattleIdle");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdBattleIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->BattleIdle();


	return EBTNodeResult::InProgress;
}
void UBTTaskBdBattleIdle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	auto Instance = Cast<USTGameInstance>(Bouldelith->GetGameInstance());

	STARRYLOG(Warning, TEXT("%f"),Bouldelith->GetDistanceTo(Instance->GetPlayer()));
	if (Bouldelith->GetDistanceTo(Instance->GetPlayer()) >= Bouldelith->GetPlayerMaxDistance())
	{

		Bouldelith->SetBattleRunState(true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}