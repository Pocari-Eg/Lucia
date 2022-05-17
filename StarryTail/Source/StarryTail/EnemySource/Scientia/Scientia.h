// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "./Struct/FScientiaInfo.h"
#include "ScAnimInstance.h"
#include "Scientia.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API AScientia : public AMonster
{
	GENERATED_BODY()
public:
	AScientia();

	void InitScInfo();

	void BattleIdle();
	void BattleWalk();

	bool ScAttributeIsPlayerAttributeCounter();

	FString GetState();
	int GetBarrierCount();
	void SetState(FString string);
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScientiaInfo, Meta = (AllowPrivateAccess = true))
		FScientiaInfo ScInfo;
	FString State;

	UScAnimInstance* ScAnimInstance;

	bool SetAttribute;
	float AttributeSettingTimer;
public:
	// Called every frame
	void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	void PossessedBy(AController* NewController) override;

	void PostInitializeComponents() override;
private:
	void InitMonsterInfo() override;
	void InitCollision() override;
	void InitMesh() override;
	void InitAnime() override;
};
