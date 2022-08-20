// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerSource/PlayerInstance/IreneAttackInstance.h"
#include "PlayerSource/IreneCharacter.h"

AIreneCharacter* USTGameInstance::GetPlayer()
{
	return Player;
}
EAttributeKeyword USTGameInstance::GetPlayerAttribute()
{
	return Player->IreneAttack->GetQuillAttribute();
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


void USTGameInstance::Init()
{

	Super::Init();
	//점령 컨텐츠
	/*IsFirstOccupied = false;
	EnemyCount = 0;
	EnemyMaxCount = 20;*/

	EnemyCount = 0;
	UniqueCount = 0;
	bIsLastWave = false;
	InitSoundSetting();

	//detect
	bIsPlayerBattleState = false;
	DetectedMonsterCount = 0;

	 StateTime=2;
	 CurStateTime = StateTime;
}

void USTGameInstance::InitSoundSetting()
{
	
	SoundSettingData.BGM_Mute = false;
	SoundSettingData.BGM_Volume = 1.0f;
	SoundSettingData.SFX_Mute = false;
	SoundSettingData.SFX_Volume = 1.0f;
}

void USTGameInstance::AddEnemyCount(EEnemyRank Rank)
{
	switch (Rank)
	{
	case EEnemyRank::e_Common:
		EnemyCount++;
		break;
	case EEnemyRank::e_Unique:
		EnemyCount++;
		UniqueCount++;
		break;
	case EEnemyRank::e_Raid:
		break;
	default:
		break;
	}

}

void USTGameInstance::SubEnemyCount(EEnemyRank Rank)
{
	switch (Rank)
	{
	case EEnemyRank::e_Common:
		EnemyCount--;
		break;
	case EEnemyRank::e_Unique:
		EnemyCount--;
		UniqueCount--;
		break;
	case EEnemyRank::e_Raid:
		break;
	default:
		break;
	}
	STARRYLOG(Warning, TEXT("Current EnemyCount : %d"), EnemyCount);

	if (bIsLastWave)
	{
		if (EnemyCount <= 0 && UniqueCount <= 0)
		{
			WaveStart.Broadcast();
	   }
	}
	else
	{
		if (EnemyCount <= NextWaveCount&&UniqueCount<=0)
		{
			WaveStart.Broadcast();
		}
	}
}

void USTGameInstance::SetNextWaveCount(int32 count)
{
	
	NextWaveCount = count;
	STARRYLOG(Warning, TEXT("NextWaveCount : %d"), NextWaveCount);
}

void USTGameInstance::SetLastWave(bool State)
{
	bIsLastWave = State;
}

bool USTGameInstance::IsLastWave()
{
	return bIsLastWave;
}

void USTGameInstance::AddDetectedMonster()
{
	if (DetectedMonsterCount == 0)
	{
		//플레이어 카메라 줌 아웃 이벤트
		//캐릭터 대치상태 변경
		GetWorld()->GetTimerManager().ClearTimer(StateChangeTimer);
		DetectedMonsterCount++;
		if (!bIsPlayerBattleState)
		{
			bIsPlayerBattleState = true;
			Player->CameraOutEvent();
			STARRYLOG(Error, TEXT("Battle State On"));
		}
		
	}
	else
	{
		DetectedMonsterCount++;
	}

}

void USTGameInstance::SubDetectedMonster()
{
	if (DetectedMonsterCount > 0)
	{
		DetectedMonsterCount--;
	}

	if (DetectedMonsterCount == 0) {
		//캐릭터 대치상태 변경
		STARRYLOG(Error, TEXT("Battle State Count"));
		CurStateTime = StateTime;
		GetWorld()->GetTimerManager().SetTimer(StateChangeTimer, this, &USTGameInstance::CountStateTimer, 1.0f, true, 0.0f);
	}
}

bool USTGameInstance::GetPlayerBattleState()
{
	return bIsPlayerBattleState;
}

void USTGameInstance::CountStateTimer()
{
	if (CurStateTime <= 0)
	{
		ChangeState();
	}
	else {
		CurStateTime--;
	}
}

void USTGameInstance::ChangeState()
{
	Player->CameraInEvent();
	bIsPlayerBattleState = false;
	STARRYLOG(Error, TEXT("Battle State Off"));
	GetWorld()->GetTimerManager().ClearTimer(StateChangeTimer);
	CurStateTime = StateTime;
}

FSoundSetting* USTGameInstance::GetSoundSetting()
{
	return &SoundSettingData;
}

#pragma region Occupy
/*
void USTGameInstance::OnFirstOccupy()
{
	if (IsFirstOccupied == false)
	{
		IsFirstOccupied = true;
		SpawnTime = UKismetMathLibrary::RandomIntegerInRange(0, 5);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USTGameInstance::SpawnTimeCheck, 1.0f, true, 0.0f);
	}
	else {
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
{
	EnemyCount++;
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
*/
#pragma endregion

