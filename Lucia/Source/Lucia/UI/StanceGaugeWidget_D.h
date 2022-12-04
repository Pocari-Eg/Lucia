// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StanceGaugeWidget_D.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UStanceGaugeWidget_D : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class UImage* gauge_full;
	UPROPERTY()
	class UImage* gauge_fill;

	UMaterialInstanceDynamic* mat_Progress;
	FTimerHandle AttackCtimeHandle, stopshine;
	float PLUS = 0.0f;

	float targetR, targetG, targetB;
	bool SHINE;

	UPROPERTY(EditAnyWhere)
	FLinearColor idlecolor;
	UPROPERTY(EditAnyWhere)
	FLinearColor fillcolor;
	UPROPERTY(EditAnyWhere)
	FLinearColor fullcolor;

	float Timer, maxTimer;

	class AIreneCharacter* Irene;

public:
	UFUNCTION(BlueprintCallable)
	void eCtime(float Ctime);
	UFUNCTION(BlueprintCallable)
	void ResetStanceGague();

	UFUNCTION(BlueprintCallable)
	void SetCoolTime(float Time);

	void eCtimeflow();

	void BrushSetColor(float _current);

	void SetShine();

	virtual void NativeConstruct() override;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
};
