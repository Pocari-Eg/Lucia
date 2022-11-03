// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMoveToSupportRange.h"
#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskMoveToSupportRange::UBTTaskMoveToSupportRange()
{
	NodeName = TEXT("MoveToSupportRange");
	bNotifyTick = true;

	bIsOutSupportRange = false;
	bIsInBattleRange = false;
}

EBTNodeResult::Type UBTTaskMoveToSupportRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;


	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));
	Monster->PlayWalkAnim();

	MoveDistance = FMath::FRandRange(Monster->GetBattleRange(), Monster->GetSupportRange());

	float CurDistance = Monster->GetDistanceTo(Player);
	if (CurDistance > MoveDistance)
	{
		bIsOutSupportRange = true;
	}
  if(CurDistance < MoveDistance){
	  bIsInBattleRange = true;
	}
	
	




	return EBTNodeResult::InProgress;
}

void UBTTaskMoveToSupportRange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));


	if (bIsOutSupportRange)
	{
		Monster->MoveToPlayer(DeltaSeconds);
		if (Monster->GetDistanceTo(Player) <= MoveDistance)
		{
			Monster->GetAIController()->SetIsInSupportRange(true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	if(bIsInBattleRange)
	{
		MoveToPlayerReverse(Monster, Player, DeltaSeconds);
		if (Monster->GetDistanceTo(Player) >= MoveDistance)
		{
			Monster->GetAIController()->SetIsInSupportRange(true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
    }

	
}

void UBTTaskMoveToSupportRange::MoveToPlayerReverse(AMonster* Monster, AIreneCharacter* Player,float DeltaSeconds)
{

	Monster->SetActorLocation(Monster->GetActorLocation() + (Monster->GetActorForwardVector() * Monster->GetMoveSpeed() * DeltaSeconds));


	//2개의 벡터를 a to b 로 회전 하는 행렬 구하기
	FVector ForwardVec = Monster->GetActorForwardVector();
	ForwardVec.Normalize();

	FVector PlayerVec = Player->GetActorLocation() - Monster->GetActorLocation();

	PlayerVec.Normalize();

	FQuat RotationQuat = Math::VectorA2BRotation(ForwardVec, -PlayerVec);

	RotationQuat *= Monster->GetRotateRate();
	RotationQuat.X = 0.0f;
	RotationQuat.Y = 0.0f;
	RotationQuat.W = 1.0f;
	Monster->AddActorWorldRotation(RotationQuat);
}
