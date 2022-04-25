// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "../STGameInstance.h"
#include "Monster.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

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
const FName AMonsterAIController::IsShockKey = (TEXT("bIsShock"));

const FName AMonsterAIController::IsDeadKey = (TEXT("bIsDead"));

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
void AMonsterAIController::Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana)
{
	SetPlayer();
	

	auto Monster = Cast<AMonster>(GetPawn());
	if (Monster != nullptr)
	{
		if (!Monster->GetMonsterAnimInstance()->GetAttackIsPlaying())
		{
			if (!bIsPlayerUseMana)
			{
				if (AttackedPower == EAttackedPower::Halved)
				{
					Monster->GetMonsterAnimInstance()->PlayAttackedMontage();
				}
				else if (AttackedPower == EAttackedPower::Normal || AttackedPower == EAttackedPower::Critical)
				{
					if (AttackedDirection == EAttackedDirection::Left)
						Monster->GetMonsterAnimInstance()->PlayAttackedRightMontage();
					else if (AttackedDirection == EAttackedDirection::Right)
						Monster->GetMonsterAnimInstance()->PlayAttackedLeftMontage();
				}
			}
			else
			{
				if (AttackedPower == EAttackedPower::Halved)
				{
					Monster->GetMonsterAnimInstance()->PlayAttackedMontage();
				}
				else if (AttackedPower == EAttackedPower::Normal || AttackedPower == EAttackedPower::Critical)
				{
					if (AttackedDirection == EAttackedDirection::Left)
						Monster->GetMonsterAnimInstance()->PlayAttackedCriticalRightMontage();
					else if (AttackedDirection == EAttackedDirection::Right)
						Monster->GetMonsterAnimInstance()->PlayAttackedCriticalLeftMontage();
					else if (AttackedDirection == EAttackedDirection::Up || AttackedDirection == EAttackedDirection::Down)
						Monster->GetMonsterAnimInstance()->PlayRollingMontage();
				}
			}
		}
	}
	Blackboard->SetValueAsBool(IsAttackedKey, true);
}
void AMonsterAIController::Groggy()
{
	SetPlayer();

	auto Monster = Cast<AMonster>(GetPawn());
	if (Monster != nullptr)
	{
		Monster->GetMonsterAnimInstance()->PlayGroggyMontage();
	}

	Blackboard->SetValueAsBool(IsAttackedKey, true);
	Blackboard->SetValueAsBool(IsGroggyKey, true);
}
void AMonsterAIController::Shock()
{
	auto Monster = Cast<AMonster>(GetPawn());
	if (Monster != nullptr)
	{
		Monster->GetMonsterAnimInstance()->PlayShockMontage();
	}

	Blackboard->SetValueAsBool(IsAttackedKey, true);
	Blackboard->SetValueAsBool(IsShockKey, true);
}
void AMonsterAIController::ShockCancel()
{
	Blackboard->SetValueAsBool(IsAttackedKey, false);
	Blackboard->SetValueAsBool(IsShockKey, false);
}
void AMonsterAIController::Death()
{
	auto Monster = Cast<AMonster>(GetPawn());
	if (Monster != nullptr)
	{
		Monster->GetMonsterAnimInstance()->PlayDeathMontage();
	}

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
	Blackboard->SetValueAsObject(PlayerKey, GameInstance->GetPlayer());
}
void AMonsterAIController::SetFind()
{
	Blackboard->SetValueAsBool(IsFindKey, true);
}