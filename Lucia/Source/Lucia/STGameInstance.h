// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Lucia.h"
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
class LUCIA_API USTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	AIreneCharacter* GetPlayer();
	EAttributeKeyword GetPlayerAttribute();
	void SetPlayer(AIreneCharacter* IreneCharacter);
	AMonster* GetAttributeEffectMonster();
	void SetAttributeEffectMonster(AMonster* Monster);
	void ResetAttributeEffectMonster();


	FSoundSetting* GetSoundSetting();
	FTransform GetSpawnTransform()const{return SpawnTransform;}
	FVector FirstPosition()const{return FVector(-640,-29532,121);}
	FVector SecondPosition()const{return FVector(-6800,-36560,-170.7);}
	FVector ThirdPosition()const{return FVector(-11200,-33760,60);}
	FVector FourthPosition()const{return FVector(-20050,-42480,70);}
	FRotator FirstRotation()const{return FRotator(0,270, 0);}
	FRotator SecondRotation()const{return FRotator(0,90,0);}
	FRotator ThirdRotation()const{return FRotator(0,180,0);}
	FRotator FourthRotation()const{return FRotator(0,220,0);}

	void SetLocation(FVector Location) {CurrnetLoaction = Location;}
	void SetSpawnTransform(const FTransform Location) {SpawnTransform = Location;}
	
	UFUNCTION(BluePrintCallable)
	FVector GetCurrnetLocation() { return CurrnetLoaction; }

	UFUNCTION(blueprintcallable)
	bool GetIsPlaying() { return bIsPlaying; }
	void SetIsPlaying(bool state) {
		bIsPlaying = state;
	}


	UFUNCTION(blueprintcallable)
	void GameInit();
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
	FTransform SpawnTransform;
	
	bool bIsPlaying;
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
	void InitCurStackMonster();
	void EmptyCurStackMonster();
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

#pragma region BossMonster
private:
	AMonster* CurBossMonster;

	bool bIsVideoPlay;
public:
	void SetCurBossMonster(AMonster* Monster);
	UFUNCTION(BlueprintCallAble)
	void DeleteBossMonster() { CurBossMonster = nullptr;}
	AMonster* GetBoss() { return CurBossMonster; }
	UFUNCTION(BluePrintCallable)
	void BossStart();

	UFUNCTION(BlueprintCallAble)
	void SetbIsVideoPlay(bool state){ bIsVideoPlay = state;}
	UFUNCTION(BlueprintCallAble)
	bool GetbIsVideoPlay(){return bIsVideoPlay;}
#pragma endregion RaidMonster


#pragma region Tutorial
private:
	bool Tutorial[10];
public:
	UFUNCTION(blueprintcallable)
	void SetTutorial(int num, bool State);
	UFUNCTION(blueprintcallable)
	bool GetTutorialState(int num);
	UFUNCTION(blueprintcallable)
	void TutorialInit();

#pragma endregion Tutorial
};
