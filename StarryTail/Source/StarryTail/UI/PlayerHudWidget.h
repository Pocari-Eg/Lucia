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
	// Player ���ε� �ҋ� ��� 
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
	// ������ �ʱ�ȭ
	virtual void NativeOnInitialized() override;
	//���� ������Ʈ
private:

	//���� ������Ʈ
	class AIreneCharacter* CurrentIrene;
	//���� �� HP Bar ������
	UPROPERTY()
		class UProgressBar* HPProgressBar;
	UPROPERTY()
		class UProgressBar* MPProgressBar;	
};
