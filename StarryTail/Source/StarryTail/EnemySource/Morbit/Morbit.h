// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include"../../Sound/SoundManager.h"
#include "MorbitAnimInstance.h"
#include "Morbit.generated.h"

UCLASS()
class STARRYTAIL_API AMorbit : public AMonster
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMorbit();

	UMorbitAnimInstance* GetMorbitAnimInstance() const;

	void Walk();
	void BattleWalk();
	void Attack();

	void AttackCheck();

private:
	//Variable
	UPROPERTY()
		class UMorbitAnimInstance* MorbitAnimInstance;
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
	void InitBarrier() override;
};
