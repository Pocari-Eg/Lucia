// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

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
void USTGameInstance::AddChainMonster(AMonster* Monster)
{
	ChainMonsterList.Add(Monster);
}
TArray<AMonster*> USTGameInstance::GetChainMonsterList()
{
	return ChainMonsterList;
}
void USTGameInstance::ResetChainMonsterList()
{
	ChainMonsterList.Empty();
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
#pragma region FSM
// UIdleState* USTGameInstance::GetIdleInstance()
// {
// 	static UIdleState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<UIdleState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// UDeathState* USTGameInstance::GetDeathInstance()
// {
// 	static UDeathState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<UDeathState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// UDodgeState* USTGameInstance::GetDodgeInstance()
// {
// 	static UDodgeState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<UDodgeState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// UHitState* USTGameInstance::GetHitInstance()
// {
// 	static UHitState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<UHitState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// UBasicAttackState* USTGameInstance::GetBasicAttackInstance()
// {
// 	static UBasicAttackState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<UBasicAttackState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// UActionAttackState* USTGameInstance::GetActionAttackInstance()
// {
// 	static UActionAttackState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<UActionAttackState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// UBattleIdleState* USTGameInstance::GetBattleIdleInstance()
// {
// 	static UBattleIdleState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<UBattleIdleState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// URunState* USTGameInstance::GetRunInstance()
// {
// 	static URunState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<URunState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// USprintState* USTGameInstance::GetSprintInstance()
// {
// 	static USprintState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<USprintState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// USprintEndState* USTGameInstance::GetSprintEndInstance()
// {
// 	static USprintEndState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<USprintEndState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// UJumpState* USTGameInstance::GetJumpInstance()
// {
// 	static UJumpState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<UJumpState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// UFallState* USTGameInstance::GetFallInstance()
// {
// 	static UFallState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<UFallState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
// USprintJumpState* USTGameInstance::GetSprintJumpInstance()
// {
// 	static USprintJumpState* Instance;
// 	if (Instance == nullptr)
// 	{
// 		Instance = NewObject<USprintJumpState>();
// 		StateValue = Instance;
// 	}
// 	return Instance;
// }
#pragma endregion