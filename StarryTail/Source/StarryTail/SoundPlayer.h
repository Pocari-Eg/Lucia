// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundManager.h"
#include "SoundPlayer.generated.h"

UCLASS()
class STARRYTAIL_API ASoundPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundPlayer();

#pragma region Sound
	//사운드 이벤트
public:
	UPROPERTY(EditAnyWhere, Category = "SOUND", meta = (ClampMin = "0", ClampMax = "1"))
		float Volume;
	UPROPERTY(EditAnyWhere, Category = "SOUND")
	class UFMODEvent* Event;

	SoundManager* Sound;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(Blueprintcallable,Category="SOUND")
	void PlayBGM();

};
