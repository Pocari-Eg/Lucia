// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "../STGameInstance.h"

const FName AMonsterAIController::SpawnPosKey = (TEXT("SpawnPos"));
const FName AMonsterAIController::PatrolPosKey = (TEXT("PatrolPos"));

const FName AMonsterAIController::IsFindKey = (TEXT("bIsFind"));
const FName AMonsterAIController::PlayerKey = (TEXT("Player"));
const FName AMonsterAIController::TraceRangeKey = (TEXT("TraceRange"));

const FName AMonsterAIController::MeleeAttackRangeKey = (TEXT("MeleeAttackRange"));
const FName AMonsterAIController::IsInAttackAreaKey = (TEXT("bIsInAttackArea"));
const FName AMonsterAIController::IsAttackingKey = (TEXT("bIsAttacking"));
const FName AMonsterAIController::IsAttackCoolKey = (TEXT("bIsAttackCool"));

const FName AMonsterAIController::IsAttackedKey = (TEXT("bIsAttacked"));
const FName AMonsterAIController::IsGroggyKey = (TEXT("bIsGroggy"));

const FName AMonsterAIController::IsDeadKey = (TEXT("bIsDead"));

const FName AMonsterAIController::ReturnKey = (TEXT("bReturn"));

//state
const FName AMonsterAIController::NormalStateKey = (TEXT("NormalState"));
const FName AMonsterAIController::BattleStateKey = (TEXT("BattleState"));
const FName AMonsterAIController::AttackedStateKey = (TEXT("AttackedState"));
const FName AMonsterAIController::SupportStateKey = (TEXT("SupportState"));

const FName AMonsterAIController::Attack1Key = (TEXT("Attack1Active"));
const FName AMonsterAIController::Attack2Key = (TEXT("Attack2Active"));
const FName AMonsterAIController::Attack3Key = (TEXT("Attack3Active"));


AMonsterAIController::AMonsterAIController()
{

}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}
void AMonsterAIController::Groggy()
{
	SetPlayer();

	Blackboard->SetValueAsBool(IsAttackedKey, true);
	Blackboard->SetValueAsBool(IsGroggyKey, true);
}
void AMonsterAIController::Death()
{
	Blackboard->SetValueAsBool(IsDeadKey, true);
}

void AMonsterAIController::SetPlayer()
{
	if (Blackboard->GetValueAsObject(PlayerKey) != nullptr)
		return;

	auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (GameInstance == nullptr)
	{
		STARRYLOG(Error, TEXT("Not Found STGameInstance"));
	}
	auto Monster = Cast<AMonster>(GetPawn());
	Monster->SetIsBattleState(true);
	Blackboard->SetValueAsObject(PlayerKey, GameInstance->GetPlayer());
}
void AMonsterAIController::SetFind()
{
	auto Monster = Cast<AMonster>(GetPawn());
	Monster->GetMonsterAnimInstance()->PlayWalktoTraceMontage();
	Blackboard->SetValueAsBool(IsFindKey, true);
	SetPlayer();
}
void AMonsterAIController::SetSpawnPos(FVector Position)
{
	Blackboard->SetValueAsVector(SpawnPosKey, Position);
}

void AMonsterAIController::SetInAttackArea(bool Set)
{
	Blackboard->SetValueAsBool(IsInAttackAreaKey, Set);
}

void AMonsterAIController::SetAttackCoolKey(bool Set)
{
	Blackboard->SetValueAsBool(IsAttackCoolKey, Set);
}

void AMonsterAIController::SetNormalState(bool State)
{
	Blackboard->SetValueAsBool(NormalStateKey, State);
}

void AMonsterAIController::SetBattleState(bool State)
{
	Blackboard->SetValueAsBool(BattleStateKey, State);
	SetPlayer();
}

void AMonsterAIController::SetAttackedState(bool State)
{
	Blackboard->SetValueAsBool(AttackedStateKey, State);
}

void AMonsterAIController::SetSupportState(bool State)
{
	Blackboard->SetValueAsBool(SupportStateKey, State);
}

