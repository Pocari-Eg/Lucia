// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "BdAnimInstance.h"
#include "Bouldelith.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API ABouldelith : public AMonster
{
	GENERATED_BODY()
public:
	//Function
	ABouldelith();

	UBdAnimInstance* GetBouldelithAnimInstance() const;
	void SetBattleRunSpeed(float Value);
	void ResetBattleRunSpeed();
	//Var
private:
	//Function
	
	//Var
	float DefaultBattleRunSpeed;
	float CurrentBattleRunSpeed;
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
