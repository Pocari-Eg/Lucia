// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NormalSkillWidget_D.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UNormalSkillWidget_D : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class UImage* skill_count_right;
	UPROPERTY()
	class UImage* skill_count_left;
	UPROPERTY()
	class UImage* skill_cooltime;
	UPROPERTY()
	class UImage* skill_bg;

	UMaterialInstanceDynamic* mat_Progress;
	FTimerHandle AttackCtimeHandle;
	FTimerHandle BGRedHandle;
	float Ctime_n, Ctime_f;

public:
	UFUNCTION(BlueprintCallable)
	void SetAttackCountMinus();
	UFUNCTION(BlueprintCallable)
	void SetAttackCountPlus();

	UFUNCTION(BlueprintCallable)
	void SetAttackCooltime(float Ctime);

	void AttackCtime();
	void BGWhite();
	
};
