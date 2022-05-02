// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "../STGameInstance.h"

const FName AMonsterAIController::SpawnPosKey = (TEXT("SpawnPos"));
const FName AMonsterAIController::PatrolPosKey = (TEXT("PatrolPos"));

const FName AMonsterAIController::IsFindKey = (TEXT("bIsFind"));
const FName AMonsterAIController::PlayerKey = (TEXT("Player"));
const FName AMonsterAIController::TraceRangeKey = (TEXT("TraceRange"));

const FName AMonsterAIController::MeleeAttackRangeKey = (TEXT("MeleeAttackRange"));
const FName AMonsterAIController::CanMeleeAttackKey = (TEXT("bCanMeleeAttack"));
const FName AMonsterAIController::IsAttackingKey = (TEXT("bIsAttacking"));

const FName AMonsterAIController::IsAttackedKey = (TEXT("bIsAttacked"));
const FName AMonsterAIController::IsGroggyKey = (TEXT("bIsGroggy"));

const FName AMonsterAIController::IsDeadKey = (TEXT("bIsDead"));

const FName AMonsterAIController::ReturnKey = (TEXT("bReturn"));

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

	auto Monster = Cast<AMonster>(GetPawn());
	Monster->PlayGroggyAnim();
}
void AMonsterAIController::Death()
{
	Blackboard->SetValueAsBool(IsDeadKey, true);

	if (Cast<AMorbit>(GetPawn()))
	{
		auto Morbit = Cast<AMorbit>(GetPawn());
		Morbit->GetMorbitAnimInstance()->PlayDeathMontage();
	}
	else if (Cast<ABouldelith>(GetPawn()))
	{
		auto Bouldelith = Cast<ABouldelith>(GetPawn());
		Bouldelith->GetBouldelithAnimInstance()->PlayDeathMontage();
	}
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
	Blackboard->SetValueAsObject(PlayerKey, GameInstance->GetPlayer());
}
void AMonsterAIController::SetFind()
{
	Blackboard->SetValueAsBool(IsFindKey, true);
}
