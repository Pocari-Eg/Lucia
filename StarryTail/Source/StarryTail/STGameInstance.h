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
	EAttributeKeyword GetPlayerAttribute();
	void SetPlayer(AIreneCharacter* IreneCharacter);
	AMonster* GetAttributeEffectMonster();
	void SetAttributeEffectMonster(AMonster* Monster);
	void ResetAttributeEffectMonster();


	FSoundSetting* GetSoundSetting();


	void SetLocation(FVector Location) {CurrnetLoaction = Location;}

	UFUNCTION(BluePrintCallable)
	FVector GetCurrnetLocation() { return CurrnetLoaction; }

	UFUNCTION(BluePrintCallable)
		void SetFirstTime(const bool value) { bIsFirstTime = value; }
	UFUNCTION(BluePrintCallable)
		bool GetFirstTime() { return bIsFirstTime; }
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

	FVector CurrnetLoaction;

	bool bIsFirstTime;
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


#pragma region Stack
private:
	TArray<AMonster*> StackMonster;

public:
	void ExplodeCurStackMonster();
	void InsertStackMonster(AMonster* Monster);
	void DeleteStackMonster(AMonster* Monster);


#pragma endregion


#pragma region DetectedMonster
private:
	bool bIsPlayerBattleState;
	int32 DetectedMonsterCount;

	int32 StateTime;
	int32 CurStateTime;
	FTimerHandle StateChangeTimer;
public:
	UFUNCTION(BlueprintCallAble)
		void InitData();

	void AddDetectedMonster();
	void SubDetectedMonster();
	bool GetPlayerBattleState();

private:
	void CountStateTimer();
	void ChangeState();
	
#pragma endregion DetectedMonster
};
