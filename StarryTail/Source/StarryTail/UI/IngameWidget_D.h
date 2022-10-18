// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IngameWidget_D.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UIngameWidget_D : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class UUltimateGaugeWidget_D* BP_UltimateGauge;
	UPROPERTY()
	class UNormalSkillWidget_D* BP_NormalSkill;
	UPROPERTY()
	class UStanceGaugeWidget_D* BP_StanceGauge;

	FTimerHandle ULTIMATEhandle;
	bool CanULTIMATE = true;

public:
	UFUNCTION(BlueprintCallable)
	void STANCEGAUGEeCtime(float _ctime);

	UFUNCTION(BlueprintCallable)
	void NORMALAttackCountMinus();
	UFUNCTION(BlueprintCallable)
	void NORMALAttackCountPlus();
	UFUNCTION(BlueprintCallable)
	void NORMALAttackCooltime(float _ctime);

	UFUNCTION(BlueprintCallable)
	void ULTIMATEsetUltimate(float _pErcent);

	void CANULTIMATE() { CanULTIMATE = true; }
	
};
