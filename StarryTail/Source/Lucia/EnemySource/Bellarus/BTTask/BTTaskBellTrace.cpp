// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBellTrace.h"

#include "../BellarusAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../../STGameInstance.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskBellTrace::UBTTaskBellTrace()
{
	NodeName = TEXT("B_Trace");
	bNotifyTick = true;

}
EBTNodeResult::Type UBTTaskBellTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->GetAIController()->SetPlayer();

	Monster->GetAIController()->StopMovement();


	bIsMove = true;
	return EBTNodeResult::InProgress;
}
void UBTTaskBellTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster) {
		Monster->GetAIController()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));

	//if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsFindKey) == false)
	//{
	//	Cast<ABellarusAIController>(Monster->GetAIController())->SetTraceTime(Cast<ABellarusAIController>(Monster->GetAIController())->GetTraceTime()+ DeltaSeconds);
	//	PlayerFollowTimer += DeltaSeconds;

	//	if (PlayerFollowTimer >= PlayerFollowTime)
	//	{
	//		PlayerFollowTimer = 0.0f;
	//		Monster->GetAIController()->StopMovement();
	//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//	}

	//	if (Cast<ABellarusAIController>(Monster->GetAIController())->GetTraceTime() >= NormalChangeTime)
	//	{
	//		PlayerFollowTimer = 0.0f;
	//		Monster->GetAIController()->StopMovement();
	//		Cast<ABellarusAIController>(Monster->GetAIController())->SetTraceTime(0.0f);
	//		Monster->SetNormalState();
	//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//	}
	//}
	//else {
	//	PlayerFollowTimer = 0.0f;
	//	Cast<ABellarusAIController>(Monster->GetAIController())->SetTraceTime(0.0f);
	//}
	if (bIsMove) {
		Monster->MoveToPlayer(DeltaSeconds);
		if(Monster->GetDistanceTo(Player) < Monster->GetWingData()->M_Atk_Radius)
		{ 
			bIsMove = false;
			Monster->GetAIController()->StopMovement();
			Monster->PlayIdleAnim();
		}
	}
	else {
		Monster->RotationPlayer(DeltaSeconds);
		if (Monster->GetDistanceTo(Player) > Monster->GetWingData()->M_Atk_Radius)
		{
			bIsMove = true;
			Monster->PlayWalkAnim();
		}
	}
}
