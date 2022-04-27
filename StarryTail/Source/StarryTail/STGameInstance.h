// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StarryTail.h"
#include "Engine/GameInstance.h"
#include "./EnemySource/Monster.h"
 
#include "STGameInstance.generated.h"

class AIreneCharacter;

DECLARE_MULTICAST_DELEGATE(FOnSpawnDelegate);

//���缷
//�̱���� ����ϰԱ�������, ���߿� Ȯ��
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
	void AddChainMonster(AMonster* Monster);
	TArray<AMonster*> GetChainMonsterList();
	void ResetChainMonsterList();

#pragma region Occupy
	//���� ������
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
	AMonster* AttributeEffectMonster; //�Ӽ� ȿ���� �߻���ų ����
	TArray<AMonster*> ChainMonsterList; // ü�� ȿ���� �߽��� �Ǵ� ����

#pragma region Occupy
	//���� ������
	bool IsFirstOccupied;
	int32 SpawnTime;
#pragma endregion
	
};
