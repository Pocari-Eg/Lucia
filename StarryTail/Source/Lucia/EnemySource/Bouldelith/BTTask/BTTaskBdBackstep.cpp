// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdBackstep.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include"../../MonsterAIController.h"
#include"../../../STGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBdBackstep::UBTTaskBdBackstep()
{
	NodeName = TEXT("Backstep");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdBackstep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->Backstep();
	Bouldelith->SetIsUseBackstep(true);

	bBackstep = true;
	Bouldelith->BackstepEnd.AddLambda([this]() -> void { bBackstep = false; });

	return EBTNodeResult::InProgress;
}
void UBTTaskBdBackstep::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bBackstep)
	{

		auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
		auto Instance = Cast<USTGameInstance>(Bouldelith->GetGameInstance());

		if (Bouldelith->GetDistanceTo(Instance->GetPlayer()) > Bouldelith->GetAttack3Distance())
		{
			auto ran = FMath::RandRange(1, 100);
			if (ran <= 70)
			{
				Bouldelith->GetAIController()->OnAttack(3);
			}
			else {
				Bouldelith->GetAIController()->OnAttack(4);
			}
		}
		else {
			auto ran = FMath::RandRange(1, 100);
			if (ran <= 70)
			{
				Bouldelith->GetAIController()->OnAttack(4);
			}
			else {
				Bouldelith->GetAIController()->OnAttack(3);
			}
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsBackStepOnKey,false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}