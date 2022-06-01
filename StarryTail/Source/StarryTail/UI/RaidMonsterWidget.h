// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "Blueprint/UserWidget.h"
#include "../EnemySource/Scientia/Scientia.h"
#include "RaidMonsterWidget.generated.h"

/**
 * 
 */

USTRUCT()
struct FAttributeIcon
{
	GENERATED_BODY()
	//속성 관련 데이터
	UPROPERTY()
	class UImage* Standard;
	UPROPERTY()
	class UImage* Break;


};
UCLASS()
class STARRYTAIL_API URaidMonsterWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	// Object 엑터를 바인드 할떄 사용 
	void BindScientia(class AScientia* NewScientiaB);

	void UpdateHp();


	void UpdateFireDef();
	void UpdateWaterDef();
	void UpdateThunderDef();
	void UpdateAttribute();

	void BreakAttributeBarrier();

private:
	bool CheckDefWidget();
protected:
	// 위젯을 초기화
	virtual void NativeOnInitialized() override;
	//위젯 업데이트
private:

	//현재 오브젝트
	class AScientia* CurrentScientia;

	//위젯 안 HP Bar 데이터
	UPROPERTY()
		class UProgressBar* HPProgressBar;
	UPROPERTY()
		class UProgressBar* FireDefBar;
	UPROPERTY()
		class UProgressBar* WaterDefBar;
	UPROPERTY()
		class UProgressBar* ThunderDefBar;

	FAttributeIcon Fire;
	FAttributeIcon Water;
	FAttributeIcon Thunder;



};
