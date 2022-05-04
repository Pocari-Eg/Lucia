// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceBdCheckAnrMobState.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"

UBTServiceBdCheckAnrMobState::UBTServiceBdCheckAnrMobState()
{
	NodeName = TEXT("CheckAnrMobState");
	Interval = 0.2f;
}
void UBTServiceBdCheckAnrMobState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	TArray<FOverlapResult> AnotherMonsterList = Bouldelith->DetectMonster(Bouldelith->GetAnotherMonsterStateCheckRange());
	if (AnotherMonsterList.Num() != 0)
	{
		for (auto const& AnotherMonster : AnotherMonsterList)
		{
			auto Mob = Cast<AMonster>(AnotherMonster.GetActor());
			if (Mob == nullptr)
				continue;

			if (Mob->GetIsBattleState())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsFindKey, true);

				for (auto const& AnrMonster : AnotherMonsterList)
				{
					auto Monster = Cast<AMonster>(AnrMonster.GetActor());
					if (Monster == nullptr)
						continue;

					auto AnotherMonsterAIController = Cast<AMonsterAIController>(Mob->GetController());
					if (AnotherMonsterAIController == nullptr)
						continue;

					AnotherMonsterAIController->SetFind();
				}
				return;
			}
		}
	}
}