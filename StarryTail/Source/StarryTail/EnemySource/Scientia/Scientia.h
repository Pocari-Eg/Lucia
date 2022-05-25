// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "./Struct/FScientiaInfo.h"
#include "ScAnimInstance.h"
#include "Feather.h"
#include "Scientia.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FClawStartDelegate);
DECLARE_MULTICAST_DELEGATE(FTurnEndDelegate);
DECLARE_MULTICAST_DELEGATE(FChangeEndDelegate);
DECLARE_MULTICAST_DELEGATE(FDodgeEndDelegate);

UCLASS()
class STARRYTAIL_API AScientia : public AMonster
{
	GENERATED_BODY()
public:
	AScientia();

	void InitScInfo();

	void Attack1();
	void Attack2();
	void Attack3();

	void Feather();
	void AddFeatherCount();
	void ResetFeatherCount();

	void ResetClawSuccessedCount();
	void PlayStuckAnim();

	void RushEnd();
	void Turn();

	void BattleIdle();
	void BattleWalk();
	void Change();
	void Dodge();
	void ChangeAttribute();

	bool ScAttributeIsPlayerAttributeCounter();

	FString GetState();
	int GetBarrierCount();
	int GetFeatherCount();
	float GetHpPercent();
	float GetAttack2Speed();
	float GetAttack3Speed();
	float GetDodgeSpeed();
	float GetRushTime();
	int GetClawSuccessedCount();
	bool GetIsCanChange();
	

	void SetState(FString string);

	//Var
	FAttackEndDelegate Attack1End;
	FAttackEndDelegate Attack2End;
	FClawStartDelegate ClawStart;
	FTurnEndDelegate TurnEnd;
	FChangeEndDelegate ChangeEnd;
	FDodgeEndDelegate DodgeEnd;
private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScientiaInfo, Meta = (AllowPrivateAccess = true))
		FScientiaInfo ScInfo;

	TSubclassOf<AFeather> FeatherBP;

	UScAnimInstance* ScAnimInstance;

	bool SetAttribute;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ScientiaInfo, Meta = (AllowPrivateAccess = true))
		bool bIsClaw;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ScientiaInfo, Meta = (AllowPrivateAccess = true))
		bool bIsRush;
	bool bIsPlayerClawHit;
	bool bIsPlayerRushHit;
	bool bIsCanChange;

	float AttributeSettingTimer;
	float ChangeTimer;
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
