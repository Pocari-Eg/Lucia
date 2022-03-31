// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IreneCharacter.h"
#include "./EnemySource/Monster.h"
#include "STGameInstance.generated.h"

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
private:
	AIreneCharacter* Player;
	AMonster* AttributeEffectMonster; //�Ӽ� ȿ���� �߻���ų ����
};
