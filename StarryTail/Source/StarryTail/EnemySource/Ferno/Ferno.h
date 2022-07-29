// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "FernoAIController.h"
#include"FernoAnimInstance.h"

#include "Ferno.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API AFerno : public AMonster
{
	GENERATED_BODY()

//Function 
public:
	AFerno();

	UFernoAnimInstance* GetFernoAnimInstance() const;

	void Walk();
	void RangeAttack();
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


//Variable
	//Variable
	UPROPERTY()
		class UFernoAnimInstance* FernoAnimInstance;

};
