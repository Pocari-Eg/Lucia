// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "Blueprint/UserWidget.h"

#include "HPBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Object ���͸� ���ε� �ҋ� ��� 
	void BindMonster(class AMonster* NewMonster);
	void UpdateHpWidget();
	void UpdateDefWidget();

	void SetColor(FLinearColor Color);

	void MarkerOn();

	void MarkerOff();
protected:
	// ������ �ʱ�ȭ
	virtual void NativeOnInitialized() override;
	//���� ������Ʈ
private:

	//���� ������Ʈ
	class AMonster* CurrentMonster;

	//���� �� HP Bar ������
	UPROPERTY()
	class UProgressBar* HPProgressBar;	
	UPROPERTY()
	class UProgressBar* DefProgressBar;
	UPROPERTY()
	class UImage* HPLine;
	UPROPERTY()
	class UImage* DefLine;
	UPROPERTY()
	class UImage* MarkerImage;
};