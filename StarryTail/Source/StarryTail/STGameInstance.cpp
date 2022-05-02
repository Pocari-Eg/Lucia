// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerSource/IreneCharacter.h"

AIreneCharacter* USTGameInstance::GetPlayer()
{
	return Player;
}
void USTGameInstance::SetPlayer(AIreneCharacter* IreneCharacter)
{
	Player = IreneCharacter;
	if (Player == nullptr)
		STARRYLOG(Log, TEXT("Failed SetPlayer"));
	STARRYLOG(Log, TEXT("SetPlayer Complete : %s"), *Player->GetName());
}
#pragma region MonsterDebuff
AMonster* USTGameInstance::GetAttributeEffectMonster()
{
	return AttributeEffectMonster;
}
void USTGameInstance::SetAttributeEffectMonster(AMonster* Monster)
{
	AttributeEffectMonster = Monster;
	if (AttributeEffectMonster == nullptr)
		STARRYLOG(Log, TEXT("Failed SetAttributeEffectMonster"));
}
void USTGameInstance::ResetAttributeEffectMonster()
{
	AttributeEffectMonster = nullptr;
}
#pragma endregion

#pragma region Occupy
void USTGameInstance::OnFirstOccupy()
{
	if (IsFirstOccupied == false)
	{
		IsFirstOccupied = true;
		SpawnTime = UKismetMathLibrary::RandomIntegerInRange(0, 5);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USTGameInstance::SpawnTimeCheck, 1.0f, true, 0.0f);
	}
	else{
	}
}

void USTGameInstance::SpawnTimeCheck()
{
	STARRYLOG(Error, TEXT("SpawnTime : %d"), SpawnTime);
	
	if (SpawnTime > 0)
	{
		SpawnTime--;
	}
	else {
		OnEnemySpawn.Broadcast();
	}
}
void USTGameInstance::AddEnemyCount()
{	EnemyCount++;
	if (EnemyCount >= EnemyMaxCount)
	{
		STARRYLOG(Warning, TEXT("EnemyCountMax"));
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	
	}
	else {
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		SpawnTime = UKismetMathLibrary::RandomIntegerInRange(10, 30);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USTGameInstance::SpawnTimeCheck, 1.0f, true, 0.0f);

	}
}
void USTGameInstance::DeleteEnemyCount()
{
	if (EnemyCount > 0)
	{
		EnemyCount--;
		if (EnemyCount == EnemyMaxCount - 1)
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			SpawnTime = UKismetMathLibrary::RandomIntegerInRange(10, 30);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USTGameInstance::SpawnTimeCheck, 1.0f, true, 0.0f);
		}
		else {

		}
	}
}
#pragma endregion
void USTGameInstance::Init()
{
	IsFirstOccupied = false;
	EnemyCount = 0;
	EnemyMaxCount = 20;
}