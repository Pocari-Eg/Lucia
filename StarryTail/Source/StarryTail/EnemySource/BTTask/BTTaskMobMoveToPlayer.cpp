// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobMoveToPlayer.h"

#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskMobMoveToPlayer::UBTTaskMobMoveToPlayer()
{
	NodeName = TEXT("MoveToPlayer");
	bNotifyTick = true;
	PlayerFollowTime = 5.0f;
	PlayerFollowTimer = 0.0f;


	AttackTime = 0.5f;
	AttackTimer = 0.0f;
}
EBTNodeResult::Type UBTTaskMobMoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	FollowSeconds = 0.0f;
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->GetMonsterAnimInstance()->PlayBattleWalkMontage();
	Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));

	Monster->GetAIController()->StopMovement();


	return EBTNodeResult::InProgress;
}
void UBTTaskMobMoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster) {
		Monster->GetAIController()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	
	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsFindKey) == false)
	{
		PlayerFollowTimer += DeltaSeconds;
		if (PlayerFollowTimer >= PlayerFollowTime)
		{
			PlayerFollowTimer = 0.0f;

			Monster->GetAIController()->StopMovement();
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::B_IdleKey, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	else {
		PlayerFollowTimer = 0.0f;
	}

	Monster->MoveToPlayer(DeltaSeconds);

	if (Monster->GetMonsterAtkType() == 2) {
		if (AttackTimer += DeltaSeconds)
		{
			if (AttackTimer >= AttackTime)
			{
				AttackTimer = 0.0f;
				float distance = Monster->GetDistanceTo(Player);
				if (distance < 1000.0f && distance > Monster->GetAttack3Range().M_Atk_Radius) {
					auto ran = FMath::RandRange(1, 100);
					if (ran <= 15)
					{
						Monster->GetAIController()->OnAttack(1);
						return;
					}
					else if (ran > 15 && ran <= 50)
					{
						Monster->GetAIController()->OnAttack(2);
						return;
					}
					else {

					}
				}
				else if (distance > 1000.0f) {
					Monster->GetAIController()->OnAttack(3);
					return;
				}
			}
		}
	}
	



	/*if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsInAttackAreaKey) == true)
{
	Monster->GetAIController()->StopMovement();
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}*/

	//if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsDeadKey) == true
	//	|| OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackedKey) == true)
	//{		
	//	Monster->GetAIController()->StopMovement();
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//}


	/*if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsInAttackAreaKey) == false)
	{
		FollowSeconds += DeltaSeconds;
		if (FollowSeconds >= Monster->GetMaxFollowTime())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);
			FollowSeconds = 0.0f;
			Monster->GetAIController()->StopMovement();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			
		}
	}*/



}
