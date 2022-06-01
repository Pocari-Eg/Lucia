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
	//�Ӽ� ���� ������
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

	// Object ���͸� ���ε� �ҋ� ��� 
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
	// ������ �ʱ�ȭ
	virtual void NativeOnInitialized() override;
	//���� ������Ʈ
private:

	//���� ������Ʈ
	class AScientia* CurrentScientia;

	//���� �� HP Bar ������
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
