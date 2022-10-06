// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "../MonsterProjectile.h"
#include "BF_Projectile.generated.h"

UCLASS()
class STARRYTAIL_API ABF_Projectile : public AMonsterProjectile
{
	GENERATED_BODY()
	
//var
public:
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* SkillEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "ture"))
	UParticleSystem* SkillEffect;


private:
	bool bIsFire;
	UPROPERTY(VisibleAnywhere, Category = "Info")
	float Damage;
	UPROPERTY(VisibleAnywhere, Category = "Info")
	float Speed;

	UPROPERTY(VisibleAnywhere, Category = "Info")
	float MaxMoveDistance;
	UPROPERTY(VisibleAnywhere, Category = "Info")
	float MoveDistance;
//func
public:
	// Sets default values for this actor's properties
	ABF_Projectile();

	void SetProjectile(float SetDamage, float SetSpeed,float SetDistance);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/*UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);*/
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
