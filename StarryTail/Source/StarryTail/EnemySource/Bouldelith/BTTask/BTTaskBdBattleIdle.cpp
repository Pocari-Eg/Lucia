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

	////È¸Àü
	//auto GameInstance = Cast<USTGameInstance>(Bouldelith->GetGameInstance());
	//FVector LookVector = GameInstance->GetPlayer()->GetActorLocation() - Bouldelith->GetLocation();
	//LookVector.Z = 0.0f;
	//FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	//Bouldelith->SetActorRotation(FMath::RInterpTo(Bouldelith->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 5.0f));


	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(ABdAIController::IsShieldOnKey) == true) {

		if (Bouldelith->GetDistanceTo(Instance->GetPlayer()) >= Bouldelith->GetPlayerMaxDistance())
		{

			Bouldelith->SetBattleRunState(true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	else {

		auto ran = FMath::RandRange(1, 100);
		STARRYLOG(Error, TEXT("Percent : %d"), ran);
		if (ran <= 70)
		{
			
			ran = FMath::RandRange(1, 100);
			if (ran <= 20)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::B_WalkLeftKey, true);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::B_WalkRightKey, false);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return;
			}

			ran = FMath::RandRange(1, 100);
			if (ran <= 20)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::B_WalkRightKey, true);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::B_WalkLeftKey, false);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return;
			}
			return;
		}


	}

	

}