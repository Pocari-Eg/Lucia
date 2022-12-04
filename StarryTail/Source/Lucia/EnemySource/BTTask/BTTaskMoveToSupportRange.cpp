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

	float CurDistance = GetDistance(Monster, Player);


	//
	//if (CurDistance > Monster->GetSupportRange())
	//{
	//	bIsOutSupportRange = true;
	//	bIsInBattleRange = false;
	//}
 // if(CurDistance < CurDistance > Monster->GetBattleRange()){
	//  bIsInBattleRange = true;
	//  bIsOutSupportRange = false;
	//}
	
	
	float MinRange = Monster->GetSupportRange();
	float MaxRange = Monster->GetBattleRange();

	MinRange = MinRange+(MinRange * 0.15f);
	MaxRange = MaxRange - (MaxRange * 0.2f);
	  float MoveDistance = FMath::FRandRange(MinRange, MaxRange);

	  //2개의 벡터를 a to b 로 회전 하는 행렬 구하기
	  FVector ForwardVec = Monster->GetActorForwardVector();
	  ForwardVec.Normalize();

	  FVector MoveVector = Monster->GetActorLocation()-Player->GetActorLocation();

	  MoveVector.Normalize();


	  MoveVector.Z = 0.0f;

	  FVector MoveLocation = Player->GetActorLocation() + (MoveVector * MoveDistance);
	  MoveLocation.Z = Monster->GetActorLocation().Z;


	  Monster->GetAIController()->MoveToLocation(MoveLocation);




	return EBTNodeResult::InProgress;
}

void UBTTaskMoveToSupportRange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	//auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));


	if (Monster->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Idle)
	{
		Monster->GetAIController()->StopMovement();
		Monster->GetAIController()->SetIsInSupportRange(true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	//if (bIsOutSupportRange)
	//{
	//	

	//	//Monster->MoveToPlayer(DeltaSeconds);
	//
	//	float Distance = GetDistance(Monster, Player);

	//	if (Distance <= Monster->GetBattleRange())
	//	{
	//		Monster->GetAIController()->StopMovement();
	//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//	}
	//	else {
	//		Monster->GetAIController()->MoveTo(Player);
	//	}

	//	if (Distance <= MoveDistance&&
	//		Distance < Monster->GetSupportRange() &&
	//		Distance > Monster->GetBattleRange())
	//	{
	//		
	//		Monster->GetAIController()->StopMovement();
	//		Monster->GetAIController()->SetIsInSupportRange(true);
	//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//	}
	//}
	//if(bIsInBattleRange)
	//{
	//	float Distance = GetDistance(Monster, Player);
	//	bool bIsClose  = MoveToPlayerReverse(Monster, Player, DeltaSeconds);
	//	if (Distance >= MoveDistance&&
	//		Distance < Monster->GetSupportRange() &&
	//		Distance > Monster->GetBattleRange()|| bIsClose)
	//	{
	//	

	//		Monster->GetAIController()->SetIsInSupportRange(true);
	//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//	}
 //   }

	
}

bool UBTTaskMoveToSupportRange::MoveToPlayerReverse(AMonster* Monster, AIreneCharacter* Player,float DeltaSeconds)
{
bool IsMove =	Monster->SetActorLocation(Monster->GetActorLocation() + (Monster->GetActorForwardVector() * Monster->GetMoveSpeed() * DeltaSeconds),true);
if (IsMove == false) {
	return true;
}


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



	return false;
}

float UBTTaskMoveToSupportRange::GetDistance(AMonster* Monster, AIreneCharacter* player)
{
	FVector PlayerLocation = player->GetActorLocation();
	FVector MonsterLocation = Monster->GetActorLocation();
	MonsterLocation.Z = PlayerLocation.Z;
	float CurDistance = (MonsterLocation - PlayerLocation).Size();

	return CurDistance;
}
