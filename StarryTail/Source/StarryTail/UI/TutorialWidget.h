// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialWidget.generated.h"

UENUM(BlueprintType)
enum class EPlayTutorial : uint8
{
	Move, Space, Action, LookAround, None
};

UENUM(BlueprintType)
enum class EPlayTuto : uint8
{
	SPACE, beforAcrossmonster, acrossmonster, acrossmonsterTWO, stepinroom, None
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayTutorial, EPlayTutorial, play);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FstopPlayTutorial, EPlayTutorial, play);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTUTOp, EPlayTuto, play);

UCLASS()
class STARRYTAIL_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BluePrintReadWrite,Category="TUTORIAL")
	FString TutorialNum;

	UPROPERTY(BlueprintAssignable)
	FPlayTutorial Pdelegate;
	UPROPERTY(BlueprintAssignable)
	FstopPlayTutorial Pstopdelegate;
	UPROPERTY(BlueprintAssignable)
	FTUTOp Pinfodelegate;

	UPROPERTY(BlueprintReadWrite)
	bool CompleteLookaround;

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnAnimationEvent();

	void PlayTutorial(FString Num);

	UFUNCTION(BlueprintCallable)
	void tryPlay(EPlayTutorial __play);
	UFUNCTION(BlueprintCallable)
	void trystopPlay(EPlayTutorial __play);
	UFUNCTION(BlueprintCallable)
	void tryTutoInfo(EPlayTuto __play);
};
