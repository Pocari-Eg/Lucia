// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include"../../SoundManager.h"
#include "Morbit.generated.h"

UCLASS()
class STARRYTAIL_API AMorbit : public AMonster
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMorbit();

	float GetViewAngle();
	float GetViewRange();

	bool GetTestMode();

	void Walk();
	void BattleWalk();
	void Attack();

	void AttackCheck();



private:
	//Function
	UFUNCTION(BlueprintCallable)
		void InitMorbitInfo();

	void InitMorbitMaterial();
	void InitOccupationAI();
	//Variable
public:
	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
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
