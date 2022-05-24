// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "Blueprint/UserWidget.h"
#include "../EnemySource/Monster.h"
#include "RaidMonsterWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API URaidMonsterWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	// Object ���͸� ���ε� �ҋ� ��� 
	void BindMonster(class AMonster* NewMonster);

	void UpdateHp();


	void UpdateFireDef();
	void UpdateWaterDef();
	void UpdateThunderDef();
	void ChangeDefWidget();

private:
	bool CheckDefWidget();
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
		class UProgressBar* FireDefBar;
	UPROPERTY()
		class UProgressBar* WaterDefBar;
	UPROPERTY()
		class UProgressBar* ThunderDefBar;
};
