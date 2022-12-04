// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Swirl.h"
#include"Tornado.h"
#include "TornadoSwirl.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API ATornadoSwirl : public ASwirl
{
	GENERATED_BODY()
private:


	UPROPERTY(EditAnywhere, Category = Collision, meta = (AllowPrivateAccess = "ture"))
	UCapsuleComponent* TornadoSwirlCore;


	float RotationTimer;
	float RotationTime;
	bool bIsTornadoSwirlMove;

	//Tornado

	float  ToDamage;
	float  To_Dot_Damage;
	float  ToPull_Force;
	float  ToMoveSpeed;
	float  ToRadius;
	float  ToCoreSetTime;
	float  ToKeepSwirlTime;
	float  ToDotDamageTime;


	FVector SpawnLocation;

	TSubclassOf<ATornado> ATornadoClass;

public:
	ATornadoSwirl();
	void InitSwirl(float DamageVal, float SwirlDotDamageVal, float PullForceVal, float CoreSetTimeVal,
		float KeepSwirlTimeVal, float MoveSpeedVal, float SwirlRadiusVal);
	void SwirlCoreActive(FVector MoveDirectionVal);

	UFUNCTION()
	void TornadoSwirlBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitTornade(float DamageVal, float SwirlDotDamageVal, float PullForceVal, float CoreSetTimeVal,
		float KeepSwirlTimeVal, float MoveSpeedVal, float SwirlRadiusVal);
	void SpawnTornado();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
