// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"
#include"../../STGameInstance.h"
#include "../../EnemySource/Monster.h"

// Sets default values
AMonsterController::AMonsterController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BattleChangeTimer = 0.0f;
	BattleChangeTime = 0.0f;

	MinBattleChangeTime = 8.0f;
	MaxBattleChangeTime = 15.0f;
	bIsChange = false;
}



void AMonsterController::SetCloseMonster()
{
	float MostCloseDistance = 99999;
	int CloseIndex = 0;
	auto instance = Cast<USTGameInstance>(GetGameInstance());
	if (CurWaveMonster.Num() != 0) {
		if (CurWaveMonster.Num() > 1) {
			for (int i = 0; i < CurWaveMonster.Num(); i++)
			{
			
				float Distance = CurWaveMonster[i]->GetDistanceTo(instance->GetPlayer());
				if (Distance <= MostCloseDistance)
				{
					CloseIndex = i;
					MostCloseDistance = Distance;
				}
			}

			SetBattleMonster(CurWaveMonster[CloseIndex]);
		}
		else {
			SetBattleMonster(CurWaveMonster[0]);
		}
	}
	
}

void AMonsterController::SetBattleMonster(AMonster* Monster)
{
	CurBattleMonster = Monster;
	for (int i = 0; i < CurWaveMonster.Num(); i++)
	{
		if (CurWaveMonster[i] == CurBattleMonster) {
			CurBattleMonster->SetBattleState();
		}
		else {
			CurWaveMonster[i]->SetSupportState();
		}
	}

	if (CurWaveMonster.Num() > 1) {
		bIsChange = true;
		BattleChangeTimer = 0.0f;
		BattleChangeTime = FMath::RandRange(MinBattleChangeTime, MaxBattleChangeTime);

	}
	STARRYLOG(Error, TEXT("BattleMonster Time : %f"), BattleChangeTime);
}

void AMonsterController::SetCurWaveMonsters(TArray<class AMonster*> WaveMonster)
{
	CurWaveMonster.Empty();
	CurWaveMonster = WaveMonster;
	for (int i = 0; i < CurWaveMonster.Num(); i++)
	{
		CurWaveMonster[i]->SetMonsterContorller(this);
	}
}

void AMonsterController::ChangeBattleMonster()
{

	if (CurWaveMonster.Num() > 1) {

		STARRYLOG(Error, TEXT("Change BattleMonster"));
		bIsChange = false;
		int NewBattleMonsterIndex;
		do {
			NewBattleMonsterIndex = FMath::RandRange(0, CurWaveMonster.Num() - 1);
		} while (CurWaveMonster[NewBattleMonsterIndex] == CurBattleMonster);

		for (int i = 0; i < CurWaveMonster.Num(); i++)
		{
			if (i == NewBattleMonsterIndex) {
				CurWaveMonster[i]->SetBattleState();
				CurBattleMonster = CurWaveMonster[i];
				if (CurWaveMonster.Num() > 1) {

					bIsChange = true;
					BattleChangeTimer = 0.0f;
					BattleChangeTime = FMath::RandRange(MinBattleChangeTime, MaxBattleChangeTime);

				}
				STARRYLOG(Error, TEXT("BattleMonster Time : %f"), BattleChangeTime);

			}
			else {
				CurWaveMonster[i]->SetSupportState();
				CurWaveMonster[i]->GetAIController()->SetIsInSupportRange(true);

					
			}
		}
	}
}

void AMonsterController::SupportMonsterAttack()
{
	TArray<AMonster*> IsRenderMonster;
	for (int i = 0; i < CurWaveMonster.Num(); i++)
	{
		if (CurWaveMonster[i] != nullptr) {
			if (CurWaveMonster[i] != CurBattleMonster && CurWaveMonster[i]->WasRecentlyRendered() &&
				CurWaveMonster[i]->GetAIController()->GetIsInSupportRange() && !CurWaveMonster[i]->GetIsAttacking() && !CurWaveMonster[i]->GetIsAttackCool())
			{
				IsRenderMonster.Add(CurWaveMonster[i]);
			}
		}
	}
	if (IsRenderMonster.Num() != 0) {
		auto RandomIndex = FMath::RandRange(0, IsRenderMonster.Num()-1);
		IsRenderMonster[RandomIndex]->SupportAttack();
	}
}

void AMonsterController::BattleMonsterDelete()
{
	CurWaveMonster.Remove(CurBattleMonster);
	CurBattleMonster = nullptr;

	for (int i = 0; i < CurWaveMonster.Num(); i++)
	{
		SetCloseMonster();
	}
	bIsChange = false;
	BattleChangeTimer = 0.0f;
}

void AMonsterController::SupportMonsterDelete(AMonster* DeleteMonster)
{
	CurWaveMonster.Remove(DeleteMonster);
}

void AMonsterController::PlayBattleBgm()
{
	if(BgmPlayer!=nullptr)
	BgmPlayer->ChangeBgm(4.0f);
}

void AMonsterController::PlayNormalBgm()
{
	if (BgmPlayer != nullptr) {
		switch (CurStage)
		{
		case EState::e_MainHall:
			BgmPlayer->ChangeBgm(0.0f);
			break;
		case EState::e_Library:
			BgmPlayer->ChangeBgm(1.0f);
			break;
		case EState::e_Orgranism:
			BgmPlayer->ChangeBgm(2.0f);
			break;
		default:
			break;
		}
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
	if (bIsChange&&CurBattleMonster!=nullptr) {
		BattleChangeTimer += DeltaTime;
		if (BattleChangeTimer >= BattleChangeTime)
		{
			ChangeBattleMonster();
		}
	}
}

//!IreneAttack->SwordTargetMonster->WasRecentlyRendered()

