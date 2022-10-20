// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Swirl.h"
#include "GuidedSwirl.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API AGuidedSwirl : public ASwirl
{
	GENERATED_BODY()
private:


	UPROPERTY(EditAnywhere, Category = Collision, meta = (AllowPrivateAccess = "ture"))
	UCapsuleComponent* GuidedSwirlCore;

	UPROPERTY(EditAnywhere, Category = Info, meta = (AllowPrivateAccess = "ture"))
	float ExplosionRadius;
	UPROPERTY(EditAnywhere, Category = Info, meta = (AllowPrivateAccess = "ture"))
	float ExplosionAtk;
	

	float RotationTimer;
	float RotationTime;
	bool bIsGuidedMove;

	float CollisionTimer;
	float CollisionTime;


	float DestroyTimer;
	bool bIsDestroy;

	FVector ExplosionLocation;

public:
	AGuidedSwirl();
	void InitSwirl(float DamageVal, float SwirlDotDamageVal, float PullForceVal, float CoreSetTimeVal,
		float KeepSwirlTimeVal, float MoveSpeedVal, float SwirlRadiusVal,float ExplosionRadiusVal, float ExplosionAtkVal);
	void SwirlCoreActive(FVector MoveDirectionVal);

	UFUNCTION()
	void GuidedSwirlBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AttackCheck(float Radius, float Hegiht, float Angle, float AttackAxis);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
