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
	Monster->PlayBattleWalkAnim();

	MoveDistance = FMath::FRandRange(Monster->GetBattleRange(), Monster->GetSupportRange());

	float CurDistance = Monster->GetDistanceTo(Player);
	if (CurDistance > MoveDistance)
	{
		bIsOutSupportRange = true;
		bIsInBattleRange = false;
	}
  if(CurDistance < MoveDistance){
	  bIsInBattleRange = true;
	  bIsOutSupportRange = false;
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

		if (Monster->GetDistanceTo(Player) <= MoveDistance&& 
			Monster->GetDistanceTo(Player) < Monster->GetSupportRange() &&
			Monster->GetDistanceTo(Player) > Monster->GetBattleRange())
		{
			Monster->GetAIController()->SetIsInSupportRange(true);
			STARRYLOG_S(Error);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	if(bIsInBattleRange)
	{
		MoveToPlayerReverse(Monster, Player, DeltaSeconds);
		if (Monster->GetDistanceTo(Player) >= MoveDistance&& 
			Monster->GetDistanceTo(Player) < Monster->GetSupportRange() &&
			Monster->GetDistanceTo(Player) > Monster->GetBattleRange())
		{
			Monster->GetAIController()->SetIsInSupportRange(true);
			STARRYLOG_S(Error);
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


	PlayerVec.Z = 0.0f;
	PlayerVec = -PlayerVec;

	FQuat RotationQuat = Math::VectorA2BRotation(ForwardVec, PlayerVec);

	RotationQuat *= Monster->GetRotateRate();
	RotationQuat.X = 0.0f;
	RotationQuat.Y = 0.0f;
	RotationQuat.W = 1.0f;
	Monster->AddActorWorldRotation(RotationQuat);

	FVector RotateVec = RotationQuat.RotateVector(ForwardVec);

	UKismetSystemLibrary::DrawDebugArrow(this, Monster->GetActorLocation(), Monster->GetActorLocation() + (PlayerVec * 200), 300.0f, FLinearColor::Red, 0.1f, 3.0f);
	UKismetSystemLibrary::DrawDebugArrow(this, Monster->GetActorLocation(), Monster->GetActorLocation() + (ForwardVec * 200), 300.0f, FLinearColor::Blue, 0.1f, 3.0f);
	UKismetSystemLibrary::DrawDebugArrow(this, Monster->GetActorLocation(), Monster->GetActorLocation() + (RotateVec * 200), 300.0f, FLinearColor::Green, 0.1f, 3.0f);
}
