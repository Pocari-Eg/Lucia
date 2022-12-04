// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Lucia.h"
#include "Blueprint/UserWidget.h"
#include "../EnemySource/Scientia/Scientia.h"
#include "RaidMonsterWidget.generated.h"

/**
 * 
 */

UCLASS()
class LUCIA_API URaidMonsterWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	// Object ���͸� ���ε� �ҋ� ��� 
	void BindMonster(class AMonster* Monster);

	void UpdateHp();
	void UpdateShield();


protected:
	// ������ �ʱ�ȭ
	virtual void NativeConstruct() override;
	//���� ������Ʈ
private:

	//���� ������Ʈ
	class AMonster* CurrentBoss;

	//���� �� HP Bar ������
	UPROPERTY()
		class UProgressBar* HPProgressBar;
	UPROPERTY()
		class UProgressBar* ShieldBar;




};
