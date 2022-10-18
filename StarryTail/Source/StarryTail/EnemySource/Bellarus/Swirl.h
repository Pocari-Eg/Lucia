// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Swirl.generated.h"

UCLASS()
class STARRYTAIL_API ASwirl : public AActor
{
	GENERATED_BODY()
private:
	//var
	UPROPERTY(EditAnywhere, Category = Root, meta = (AllowPrivateAccess = "ture"))
	UStaticMeshComponent* RootPoint;

	UPROPERTY(EditAnywhere, Category = Collision, meta = (AllowPrivateAccess = "ture"))
	UCapsuleComponent* Swirl_Pull_Range;
	UPROPERTY(EditAnywhere, Category = Collision, meta = (AllowPrivateAccess = "ture"))
	UCapsuleComponent* Swirl_Core;

	UPROPERTY(EditAnywhere, Category = Effect, meta = (AllowPrivateAccess = "ture"))
	UParticleSystemComponent* Swirl_Core_Effect;
	UPROPERTY(EditAnywhere, Category = Effect, meta = (AllowPrivateAccess = "ture"))
	UParticleSystemComponent* Swirl_Pull_Range_Effect;

	float Damage;
	float Swirl_Dot_Damage;
	float Pull_Force;
	
	float MoveSpeed;
	

	float SwirlRadius;

	float CoreSetTime;
	float CoreSetTimer;

	float KeepSwirlTime;
	float KeepSwirlTimer;

	float DotDamageTimer;
	float DotDamageTime;

	bool bIsOnDotDamage;
	bool bIsOnSwirlCore;
	bool SwirlKeepcheck;

	bool bIsOnCorePull;

	class AIreneCharacter* Irene;
//func
public:	
	// Sets default values for this actor's properties
	ASwirl();

	void InitSwirl(float DamageVal,float SwirlDotDamageVal,float PullForceVal,float CoreSetTimeVal,
		float KeepSwirlTime,float MoveSpeedVal,float SwirlRadiusVal);

	void SwirlCoreActive();
	void SwirlPullRangeActive();
	void SwirlDestroy();

	bool GetbIsOnDotDamage();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SwirlCoreBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void SwirlCoreEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void  SwirlPullRangeBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void  SwirlPullRangeEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
