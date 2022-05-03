// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "BdAnimInstance.h"
#include "BouldelithPatrolTarget.h"
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

	void Walk();
	void BattleRun();

	UBdAnimInstance* GetBouldelithAnimInstance() const;
	void AddBattleRunSpeed(float Value);
	float GetBattleRunSpeed();
	void ResetBattleRunSpeed();
	TArray<ABouldelithPatrolTarget*> GetPatrolList();
	ABouldelithPatrolTarget* GetUsePatrol();
	void SetUsePatrol(ABouldelithPatrolTarget* PatrolTarget);

	
	//Var
private:
	//Function
	
	//Var
	UBdAnimInstance* BdAnimInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PatrolList, Meta = (AllowPrivateAccess = true))
		TArray<ABouldelithPatrolTarget*> PatrolList;
	ABouldelithPatrolTarget* UsePatrol;

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
