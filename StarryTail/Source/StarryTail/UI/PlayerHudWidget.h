// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../IreneCharacter.h"
#include "PlayerHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// Player 바인드 할떄 사용 
	void BindCharacter(class AIreneCharacter* NewIrene);
	void UpdateHp();
	void UpdateMp();

	UFUNCTION(BlueprintImplementableEvent)
	void  FireAttributesOn();
	UFUNCTION(BlueprintImplementableEvent)
	void  WaterAttributesOn();
	UFUNCTION(BlueprintImplementableEvent)
	void  ThunderAttributesOn();
protected:
	// 위젯을 초기화
	virtual void NativeOnInitialized() override;
	//위젯 업데이트
private:

	//현재 오브젝트
	class AIreneCharacter* CurrentIrene;
	//위젯 안 HP Bar 데이터
	UPROPERTY()
		class UProgressBar* HPProgressBar;
	UPROPERTY()
		class UProgressBar* MPProgressBar;	
};
