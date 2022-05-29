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

	// Object 엑터를 바인드 할떄 사용 
	void BindMonster(class AMonster* NewMonster);
	void UpdateHpWidget();
	void UpdateDefWidget();

	void SetColor(FLinearColor Color);

	void MarkerOn();

	void MarkerOff();
protected:
	// 위젯을 초기화
	virtual void NativeOnInitialized() override;
	//위젯 업데이트
private:

	//현재 오브젝트
	class AMonster* CurrentMonster;

	//위젯 안 HP Bar 데이터
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