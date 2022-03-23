// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "Morbit.generated.h"

DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);

DECLARE_MULTICAST_DELEGATE(FAttackedEndDelegate);
DECLARE_MULTICAST_DELEGATE(FGroggyEndDelegate);

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
	FGroggyEndDelegate GroggyEnd;

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
		virtual void OnGroggyMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		virtual void OnAttacked(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


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
};
