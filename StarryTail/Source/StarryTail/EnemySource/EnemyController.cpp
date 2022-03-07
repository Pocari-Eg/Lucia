// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AEnemyController::PlayerKey(TEXT("Player"));
const FName AEnemyController::RangedAttackCountKey(TEXT("RangedAttackCount"));
const FName AEnemyController::CanRangedAttackKey(TEXT("bCanRangedAttack"));
const FName AEnemyController::CanMeleeAttackKey(TEXT("bCanMeleeAttack"));
const float AEnemyController::RangedAttackRange = 500.0f;
const float AEnemyController::MeleeAttackRange = 100.0f;
int AEnemyController::RangedAttackCount = 0;
bool AEnemyController::bCanRangedAttack = false;
bool AEnemyController::bCanMeleeAttack = false;

AEnemyController::AEnemyController()
{
	AEnemyController::RangedAttackCount = 0;
	AEnemyController::bCanRangedAttack = false;
	AEnemyController::bCanMeleeAttack = false;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_Enemy"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_Enemy"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	if (UseBlackboard(BBAsset, Blackboard))
	{
		if (!RunBehaviorTree(BTAsset))
		{

		}
	}
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}