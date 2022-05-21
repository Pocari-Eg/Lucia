// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StarryTail.h"
#include "Engine/GameInstance.h"
#include "./EnemySource/Monster.h"
 
#include "STGameInstance.generated.h"

class AIreneCharacter;

DECLARE_MULTICAST_DELEGATE(FOnWaveDelegate);


//사운드 세팅 정보 저장
USTRUCT()
struct FSoundSetting
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere, Category = "Volume")
	float BGM_Volume;
	UPROPERTY(EditAnywhere, Category = "State")
	bool BGM_Mute;
	UPROPERTY(EditAnywhere, Category = "Volume")
	float SFX_Volume;
	UPROPERTY(EditAnywhere, Category = "State")
	bool SFX_Mute;

};

//김재섭
//싱글톤과 비슷하게구현가능, 나중에 확인
/**
 * 
 */
UCLASS()
class STARRYTAIL_API USTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	AIreneCharacter* GetPlayer();
	void SetPlayer(AIreneCharacter* IreneCharacter);
	AMonster* GetAttributeEffectMonster();
	void SetAttributeEffectMonster(AMonster* Monster);
	void ResetAttributeEffectMonster();


	FSoundSetting* GetSoundSetting();

protected:
	virtual void Init()override;

private:
	void InitSoundSetting();

	
private:
	UPROPERTY()
	AIreneCharacter* Player;
	UPROPERTY()
	AMonster* AttributeEffectMonster; //속성 효과를 발생시킬 몬스터

	UPROPERTY()
	FSoundSetting SoundSettingData;


#pragma region MonsterSpawn

public:
	FOnWaveDelegate WaveStart;
private:
    int32 UniqueCount;
	int32 EnemyCount;
	int32 NextWaveCount;

	bool bIsLastWave;
public:
	void AddEnemyCount(EEnemyRank Rank);
	void SubEnemyCount(EEnemyRank Rank);

	void SetNextWaveCount(int32 count);

	void SetLastWave(bool State);
	bool IsLastWave();
private:

#pragma endregion


#pragma region Occupy
/*
	//점령 컨텐츠
	bool IsFirstOccupied;
	int32 SpawnTime;



public:
	//점령 컨텐츠
	void OnFirstOccupy();
	void SpawnTimeCheck();
	bool GetFirstOccupied() { return IsFirstOccupied; }

	void AddEnemyCount();
	void DeleteEnemyCount();
	// Timer
	FTimerHandle TimerHandle;

	FOnSpawnDelegate OnEnemySpawn;
	*/
#pragma endregion


#pragma region DetectedMonster
private:
	bool bIsPlayerBattleState;
	int32 DetectedMonsterCount;
public:
	void AddDetectedMonster();
	void SubDetectedMonster();
	bool GetPlayerBattleState();
#pragma endregion DetectedMonster
};
