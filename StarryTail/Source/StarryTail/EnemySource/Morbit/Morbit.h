// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "Morbit.generated.h"

DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FAttackedEndDelegate);

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
	void BattleIdle();
	void Attack();

	FAttackEndDelegate AttackEnd;
	FAttackedEndDelegate AttackedEnd;
private:
	//override Function
	void InitMonsterInfo() override;
	void InitCollision() override;
	void InitMesh() override;
	void InitAnime() override;

	//Function
	UFUNCTION()
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		virtual void OnAttackedMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		virtual void OnAttacked(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// void CalcDamage(EAttributeKeyword PlayerAttribute, float Damage);
	
	//Variable

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void PostInitializeComponents() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
