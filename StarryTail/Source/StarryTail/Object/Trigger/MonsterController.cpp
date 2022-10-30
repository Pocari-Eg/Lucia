// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"
#include "../../EnemySource/Monster.h"

// Sets default values
AMonsterController::AMonsterController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMonsterController::SetBattleMonster(AMonster* Monster)
{
	CurBattleMonster = Monster;
	for (int i = 0; i < CurWaveMonster.Num(); i++)
	{
		if (CurWaveMonster[i] == CurBattleMonster) {
			CurBattleMonsterIndex = i;
			CurBattleMonster->SetBattleState();
			break;
		}
		else {
			CurWaveMonster[i]->SetSupportState();
		}
	}
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

// Called when the game starts or when spawned
void AMonsterController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

