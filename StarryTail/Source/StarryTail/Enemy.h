// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "./EnemySource/EnemyMagicAttack.h"
#include "Enemy.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class STARRYTAIL_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class EEnemyType
	{
		DEFAULT
	};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetEnemyType(EEnemyType NewEnemyType);
	virtual void PossessedBy(AController* NewController) override;

	//원거리 공격 구현
	void RangedAttack();
	//근거리 공격 구현
	void MeleeAttack();
	//돌진 공격 구현
	void RushAttack();

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	FOnAttackEndDelegate OnAttackEnd;
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool bIsAttacking;
	UPROPERTY()
		class UEnemyAnimInstance* EnemyAnimInstance;

	//추후 수정
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ParticleAsset, meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* ParticleAsset;

	AEnemyMagicAttack* MagicAttack;
	EEnemyType CurrentEnemyType;
};
