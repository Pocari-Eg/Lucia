// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasKB_Check.h"
#include "../BellarusAIController.h"
#include "../Bellarus.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include"../BTService/BTServiceAttackJudge.h"
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

	if (CheckTimer >= 3.0f&& !Cast<ABellarusAIController>(Monster->GetAIController())->GetIsShieldOn()&&
		Cast<ABellarusAIController>(Monster->GetAIController())->GetSecondPhaseKey())
	{
		
		FVector Center = Monster->GetLocation();
		Center -= FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		MeleeAttck(Monster, Center, OwnerComp);
	}




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

void UBTTasKB_Check::MeleeAttck(ABellarus* Bellarus, FVector Center, UBehaviorTreeComponent& OwnerComp)
{
	
bool	InTail = UBTServiceAttackJudge::AttackCheck(Bellarus, Center, Bellarus->GetTailData()->M_Atk_Radius, Bellarus->GetTailData()->M_Atk_Height, Bellarus->GetTailData()->M_Atk_Angle, 180.0f, FColor::Yellow);
bool	InWing_L = UBTServiceAttackJudge::AttackCheck(Bellarus, Center, Bellarus->GetWingData()->M_Atk_Radius, Bellarus->GetWingData()->M_Atk_Height, Bellarus->GetWingData()->M_Atk_Angle, -(Bellarus->GetWingData()->M_Atk_Angle / 2.0f), FColor::Yellow);
bool	InWing_R = UBTServiceAttackJudge::AttackCheck(Bellarus, Center, Bellarus->GetWingData()->M_Atk_Radius, Bellarus->GetWingData()->M_Atk_Height, Bellarus->GetWingData()->M_Atk_Angle, Bellarus->GetWingData()->M_Atk_Angle / 2.0f, FColor::Yellow);


	if (InTail)
	{
		Bellarus->SetBattleState();

		if (InWing_L) {

			auto ran = FMath::RandRange(1, 100);
			if (ran <= 30)
			{
				Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingLKey(true);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

			}
			else {
				Cast<ABellarusAIController>(Bellarus->GetAIController())->SetTailKey(true);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}

		}
		else if (InWing_R) {
			auto ran = FMath::RandRange(1, 100);
			if (ran <= 30)
			{
				Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingRKey(true);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
			else {
				Cast<ABellarusAIController>(Bellarus->GetAIController())->SetTailKey(true);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
		else {
			Cast<ABellarusAIController>(Bellarus->GetAIController())->SetTailKey(true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	else if (InWing_L) {
		Bellarus->SetBattleState();
		Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingLKey(true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	}
	else if (InWing_R) {
		Bellarus->SetBattleState();
		Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingRKey(true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
