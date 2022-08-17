// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../../Starrytail.h"
#include"../MonsterProjectile.h"
#include "Feather.generated.h"

UCLASS()
class STARRYTAIL_API AFeather : public AMonsterProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFeather();

	void SetMoveDir(FVector Direction);
	void SetDamage(float Value);

	void RotatorRight(int Value);
	void RotatorLeft(int Value);
private:
	//Function
	void InitCollision();
	void InitMesh();
	//Var
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, Meta = (AllowPrivateAccess = true))
		class USphereComponent* Collision;
	UPROPERTY(VisibleAnywhere, Category = Projectile, Meta = (AllowPrivateAccess = true))
		class UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* FeatherEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystem* FeatherHitEffect;

	FVector MoveDir;
	FVector NewLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		float DeadWaitTime;

	bool bIsDeadWait;
	float DeadWaitTimer;
protected:
	// Called when the game starts or when spawned
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
