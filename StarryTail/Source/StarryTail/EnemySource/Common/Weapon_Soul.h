// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../StarryTail.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "../MonsterProjectile.h"
#include "../../PlayerSource/PlayerCharacterDataStruct.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Weapon_Soul.generated.h"

UCLASS()
class STARRYTAIL_API AWeapon_Soul : public  AMonsterProjectile
{
	GENERATED_BODY()

//var
public:
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;


	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent * ProjectileMovementComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FQuat RotationQuat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RealRotation;
private:
	bool IsMoveOn;
	bool IsHitGround;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	FWeaponSoul Info;

public:	
	// Sets default values for this actor's properties
	AWeapon_Soul();

	void SetValue(FWeaponSoul* SetValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& ShootDirection);

};
