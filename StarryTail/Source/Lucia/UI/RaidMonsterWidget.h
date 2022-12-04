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

	// Object 엑터를 바인드 할떄 사용 
	void BindMonster(class AMonster* Monster);

	void UpdateHp();
	void UpdateShield();


protected:
	// 위젯을 초기화
	virtual void NativeConstruct() override;
	//위젯 업데이트
private:

	//현재 오브젝트
	class AMonster* CurrentBoss;

	//위젯 안 HP Bar 데이터
	UPROPERTY()
		class UProgressBar* HPProgressBar;
	UPROPERTY()
		class UProgressBar* ShieldBar;




};
