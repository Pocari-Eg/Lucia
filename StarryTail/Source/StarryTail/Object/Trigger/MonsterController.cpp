// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"
#include "../../EnemySource/Monster.h"

// Sets default values
AMonsterController::AMonsterController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BattleChangeTimer = 0.0f;
	BattleChangeTime = 0.0f;
	bIsChange = false;
}

void AMonsterController::SetBattleMonster(AMonster* Monster)
{
	CurBattleMonster = Monster;
	for (int i = 0; i < CurWaveMonster.Num(); i++)
	{
		if (CurWaveMonster[i] == CurBattleMonster) {
			CurBattleMonsterIndex = i;
			CurBattleMonster->SetBattleState();
		}
		else {
			CurWaveMonster[i]->SetSupportState();
		}
	}

	bIsChange = true;
	BattleChangeTimer = 0.0f;
	BattleChangeTime =FMath::RandRange(8, 15);

	STARRYLOG(Error, TEXT("BattleMonster Time : %f"), BattleChangeTime);
}

void AMonsterController::SetCurWaveMonsters(TArray<class AMonster*> WaveMonster)
{
	CurWaveMonster.Empty();
	CurWaveMonster = WaveMonster;
	for (int i = 0; i < CurWaveMonster.Num(); i++)
	{
		CurWaveMonster[i]->SetMonsterContorller (this);
	}
}

void AMonsterController::ChangeBattleMonster()
{
	STARRYLOG(Error, TEXT("Change BattleMonster"));
	bIsChange = false;
	int NewBattleNum;
	do {
		NewBattleNum = FMath::RandRange(0, CurWaveMonster.Num() - 1);
	} while (NewBattleNum == CurBattleMonsterIndex);

	CurBattleMonsterIndex = NewBattleNum;
	for (int i = 0; i < CurWaveMonster.Num(); i++)
	{
		if (i == CurBattleMonsterIndex) {
			CurWaveMonster[i]->SetBattleState();
		}
		else {
			CurWaveMonster[i]->SetSupportState();
		}
	}

}

void AMonsterController::SupportMonsterAttack()
{
}

// Called when the game starts or when spawned
void AMonsterController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsChange) {
		BattleChangeTimer += DeltaTime;
		if (BattleChangeTimer >= BattleChangeTime)
		{
			ChangeBattleMonster();
		}
	}
}

//!IreneAttack->SwordTargetMonster->WasRecentlyRendered()

