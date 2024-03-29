// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Lucia.h"
#include "Blueprint/UserWidget.h"

#include "MonsterWidget.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UMonsterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int QuillStackCount;
	
public:

	// Object 엑터를 바인드 할떄 사용 
	void BindMonster(class AMonster* NewMonster);
	void UpdateHpWidget();
	void UpdateDefWidget();

	void SetColor(FLinearColor Color);

	void MarkerOn();

	void MarkerOff();

	void SetAttributeUI(bool State);

	UFUNCTION(BlueprintImplementableEvent)
	void  OnBarrierUI();
	UFUNCTION(BlueprintImplementableEvent)
	void ShieldWidgetOff();

	void SetQuillStackCount(const int Num);
protected:
	// 위젯을 초기화
	virtual void NativeConstruct() override;
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

	UPROPERTY()
	class UImage* AttributeImage;
	UPROPERTY()
	class UImage* AttributeLineImage;

};