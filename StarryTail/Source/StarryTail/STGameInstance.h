// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IreneCharacter.h"
#include "STGameInstance.generated.h"

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
private:
	AIreneCharacter* Player;
};
