// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	void BindObjectHp(class ATestObject* NewObject);
	void UpdateHpWidget(float Hp);
	void UpdateDefWidget(float Def);
	void SetColor(FLinearColor Color);
	void MarkerOnOff();

protected:
	// ������ �ʱ�ȭ
	virtual void NativeOnInitialized() override;
	//���� ������Ʈ
private:

	//���� ������Ʈ
	class ATestObject* CurrentObject;

	//���� �� HP Bar ������
	UPROPERTY()
	class UProgressBar* HPProgressBar;	
	UPROPERTY()
	class UProgressBar* DefProgressBar;
	UPROPERTY()
	class UImage* MarkerImage;
};