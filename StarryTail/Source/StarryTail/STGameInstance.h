// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StarryTail.h"
#include "Engine/GameInstance.h"
#include "IreneCharacter.h"
#include "./EnemySource/Monster.h"
 
#include "STGameInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnSpawnDelegate);

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

#pragma region Occupy
	//점령 컨텐츠
	void OnFirstOccupy();
	void SpawnTimeCheck();
	bool GetFirstOccupied() { return IsFirstOccupied; }

	void AddEnemyCount();
	void DeleteEnemyCount();
	// Timer
	FTimerHandle TimerHandle;

	FOnSpawnDelegate OnEnemySpawn;
#pragma endregion
protected:
	virtual void Init()override;

public:
	int32 EnemyCount;
	int32 EnemyMaxCount;
private:
	AIreneCharacter* Player;
	AMonster* AttributeEffectMonster; //속성 효과를 발생시킬 몬스터

#pragma region Occupy
	//점령 컨텐츠
	bool IsFirstOccupied;
	int32 SpawnTime;
#pragma endregion
};
