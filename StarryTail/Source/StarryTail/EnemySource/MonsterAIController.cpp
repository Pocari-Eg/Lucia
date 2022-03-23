// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AMonsterAIController::SpawnPosKey = (TEXT("SpawnPos"));
const FName AMonsterAIController::PatrolPosKey = (TEXT("PatrolPos"));

const FName AMonsterAIController::PlayerKey = (TEXT("Player"));
const FName AMonsterAIController::TraceRangeKey = (TEXT("TraceRange"));

const FName AMonsterAIController::MeleeAttackRangeKey = (TEXT("MeleeAttackRange"));
const FName AMonsterAIController::CanMeleeAttackKey = (TEXT("bCanMeleeAttack"));
const FName AMonsterAIController::IsAttackingKey = (TEXT("bIsAttacking"));

const FName AMonsterAIController::IsAttackedKey = (TEXT("bIsAttacked"));
const FName AMonsterAIController::IsGroggyKey = (TEXT("bIsGroggy"));
const FName AMonsterAIController::IsShockKey = (TEXT("bIsShock"));

const FName AMonsterAIController::ReturnKey = (TEXT("bReturn"));

AMonsterAIController::AMonsterAIController()
{

}
void AMonsterAIController::Init()
{
    
}
void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}
void AMonsterAIController::Attacked(AIreneCharacter* Player)
{
	Blackboard->SetValueAsObject(PlayerKey, Player);

	Blackboard->SetValueAsBool(IsAttackedKey, true);
}
void AMonsterAIController::Groggy(AIreneCharacter* Player)
{
	Blackboard->SetValueAsObject(PlayerKey, Player);

	Blackboard->SetValueAsBool(IsAttackedKey, true);
	Blackboard->SetValueAsBool(IsGroggyKey, true);
}
void AMonsterAIController::Shock(AIreneCharacter* Player)
{
	Blackboard->SetValueAsObject(PlayerKey, Player);

	Blackboard->SetValueAsBool(IsAttackedKey, true);
	Blackboard->SetValueAsBool(IsShockKey, true);
}