// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasKB_Check.h"
#include "../BellarusAIController.h"
#include "../Bellarus.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTasKB_Check::UBTTasKB_Check()
{
	NodeName = TEXT("B_Check");
	bNotifyTick = true;
	CheckTimer = 0.0f;


}
EBTNodeResult::Type UBTTasKB_Check::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	MoveDirection = Monster->GetActorLocation() - Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey))->GetActorLocation();

	MoveDirection.Normalize();
	FVector MoveLocation = MoveDirection * 600.0f;
	MoveLocation.Z = Monster->GetActorLocation().Z;
	Monster->GetAIController()->StopMovement();
	Monster->GetAIController()->MoveToLocation(MoveLocation);

	return EBTNodeResult::InProgress;
}

void UBTTasKB_Check::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster) {
		Monster->GetAIController()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	CheckTimer += DeltaSeconds;
	if (CheckTimer >= Monster->GetCheckTime())
	{
		Monster->GetAIController()->StopMovement();

		auto ran = FMath::RandRange(0, 2);
		switch (ran)
		{
		case 0:
			Cast<ABellarusAIController>(Monster->GetAIController())->SetWingLKey(true);
			break;
		case 1:
			Cast<ABellarusAIController>(Monster->GetAIController())->SetWingRKey(true);
			break;
		case 2:
			Cast<ABellarusAIController>(Monster->GetAIController())->SetTailKey(true);
			break;
		default:
			break;
		}

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}


	if (Monster->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Moving)
	{

		FVector MoveLocation = MoveDirection * 600.0f;
		MoveLocation.Z = Monster->GetActorLocation().Z;
		Monster->GetAIController()->MoveToLocation(MoveLocation);
	}



}
