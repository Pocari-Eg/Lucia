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
DECLARE_MULTICAST_DELEGATE(FBackstepEndDelegate);
DECLARE_MULTICAST_DELEGATE(FAttack1EndDelegate);
DECLARE_MULTICAST_DELEGATE(FAttack2EndDelegate);

UCLASS()
class STARRYTAIL_API ABouldelith : public AMonster
{
	GENERATED_BODY()
public:
	//Function
	ABouldelith();

	void InitBouldelithInfo();

	void Walk();
	void BattleRun();
	void BattleIdle();

	void Attack1();
	void Attack2();

	void Backstep();

	UBdAnimInstance* GetBouldelithAnimInstance() const;

	void AddBattleRunSpeed(float Value);
	void UpgradeBattleRunAnim();
	float GetBattleRunSpeed();
	void ResetBattleRunSpeed();

	TArray<ABouldelithPatrolTarget*> GetPatrolList();
	ABouldelithPatrolTarget* GetUsePatrol();
	void SetUsePatrol(ABouldelithPatrolTarget* PatrolTarget);

	float GetAnotherMonsterStateCheckRange();
	bool GetIsChangeBattleRunStateToAttackedState();

	int GetAttackFailedStack();
	void ResetAttackFailedStack();

	float GetHpPercent();

	bool GetIsUseBackstep();
	void SetIsUseBackstep(bool Value);
	//Var
	FBackstepEndDelegate BackstepEnd;
	FAttack1EndDelegate Attack1End;
	FAttack2EndDelegate Attack2End;
private:
	//Function
	
	//Var
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BouldelithInfo, Meta = (AllowPrivateAccess = true))
		FBouldelithDataStruct BouldelithInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PatrolList, Meta = (AllowPrivateAccess = true))
		TArray<ABouldelithPatrolTarget*> PatrolList;
	ABouldelithPatrolTarget* UsePatrol;
	UBdAnimInstance* BdAnimInstance;

	float BackstepCoolTimer;

	bool bIsChangeBattleRunStateToAttackedState;
	bool bIsUseBackstep;
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
