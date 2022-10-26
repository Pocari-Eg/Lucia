// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskWait.h"
#include "../BellarusAIController.h"
#include "../Bellarus.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../BTService/BTServiceAttackJudge.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
UBTTaskWait::UBTTaskWait()
{
	NodeName = TEXT("Wait");
	bNotifyTick = true;
	Wait = false;
}

EBTNodeResult::Type UBTTaskWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto Bellarus = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());

	Wait = Bellarus->GetSwirlWaitState();
	WaitTimer = 0.0f;

	return EBTNodeResult::InProgress;
}

void UBTTaskWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

		auto Bellarus = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());

		if (!Wait)
		{
			WaitTimer += DeltaSeconds;
			if (WaitTimer >= 0.5f)
			{
				WaitTimer = 0.0f;
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}

		}
		else {

			if (Bellarus->GetSwirlWaitState() == false) {

				if (Cast<ABellarusAIController>(Bellarus->GetAIController())->GetSecondPhaseKey() == true) {
					SecondPhaseAction(Bellarus, OwnerComp);
				}
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}

	
}

void UBTTaskWait::SecondPhaseAction(ABellarus* Monster, UBehaviorTreeComponent& OwnerComp)
{

	FVector Center = Monster->GetLocation();
	Center -= FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	bool FirstJudge = UBTServiceAttackJudge::AttackJudge(Monster, Center, Monster->GetFirstJugdeRadius(), FColor::Green);

	auto Ran = FMath::RandRange(1, 100);
	STARRYLOG(Warning, TEXT("%d"), Ran);
	if (Ran <= 40)
	{
	
		Cast<ABellarusAIController>(Monster->GetAIController())->SetFeatherKey(true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		

	
	}
	 Ran = FMath::RandRange(1, 100);
	if (Ran<=30)
	{
		
		if (Ran <= 50)
		{
			Cast<ABellarusAIController>(Monster->GetAIController())->SetWingRKey(true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}

		
		else 	
		{
			Cast<ABellarusAIController>(Monster->GetAIController())->SetWingLKey(true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
