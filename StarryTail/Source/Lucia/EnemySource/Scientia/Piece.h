// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../../Lucia.h"
#include "DropFloorEffect.h"
#include"../MonsterProjectile.h"
#include "Piece.generated.h"

UCLASS()
class LUCIA_API APiece : public AMonsterProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiece();

	EAttributeKeyword GetAttribute();

	void StartDrop();

	void SetAttribute(EAttributeKeyword Attribute);
	void SetEffect();
	void SetDamage(float Value);
private:
	void InitCollision();
	void InitMesh();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		EAttributeKeyword PieceAttribute;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, Meta = (AllowPrivateAccess = true))
		UCapsuleComponent* Collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* PieceEffectComponent;

	UPROPERTY(VisibleAnywhere, Category = Projectile, Meta = (AllowPrivateAccess = true))
		class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystem* DropFireEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystem* DropWaterEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystem* DropThunderEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystem* PieceFireEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystem* PieceWaterEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystem* PieceThunderEffect;

	UPROPERTY(VisibleAnywhere, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* DropEffect;

	TSubclassOf<ADropFloorEffect> DropFloorEffectBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		float WaitTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Info, Meta = (AllowPrivateAccess = true))
		int Number;

	float WaitTimer;

	float DeadWaitTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		float DeadWaitTime;

	FVector MoveDir;
	FVector NewLocation;

	bool bIsDrop;
	bool bIsDead;
public:
protected:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:
	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

};
