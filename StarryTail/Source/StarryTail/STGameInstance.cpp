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
	return EAttributeKeyword::e_Fire;
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


	InitData();
	InitSoundSetting();

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



void USTGameInstance::InitData()
{
	EnemyCount = 0;
	UniqueCount = 0;
	bIsLastWave = false;
	//detect
	bIsPlayerBattleState = false;
	DetectedMonsterCount = 0;

	StateTime = 2;
	CurStateTime = StateTime;

	NextWaveCount = 0;
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

#pragma region Stack
void USTGameInstance::ExplodeCurStackMonster()
{
	if (StackMonster.Num() != 0)
	{
		for(int i=0;i<StackMonster.Num();i++)
		StackMonster[i]->StackExplode();
	}
}

void USTGameInstance::InsertStackMonster(AMonster* Monster)
{
	StackMonster.Add(Monster);
	Monster->StackWidgetOn();

}

void USTGameInstance::DeleteStackMonster(AMonster* Monster)
{
	if (StackMonster.Num() != 0)
	{
		for (int i = 0; i < StackMonster.Num(); i++)
			if (StackMonster[i] == Monster)
			{
				StackMonster.RemoveAt(i);
				Monster->StackWidgetOff();
				return;
			}
	}
}
#pragma endregion

