// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../EnemySource/MonsterProjectile.h"
#include"SpiritPlate.h"
#include "LabMagic.generated.h"

UCLASS()
class STARRYTAIL_API ALabMagic : public AMonsterProjectile
{
	GENERATED_BODY()

//var
private:
 
	//Min Var
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Area, Meta = (AllowPrivateAccess = true))
	UBoxComponent* MagicAOECollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ExplosionSignEffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	float Explosion_SignWait_Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	float Explosion_Wait_Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	float Explosion_Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	float MagicAOE_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	float MagicAOE_Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	float MagicAOE_Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	float SpiritRecovery_HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	float SpiritRecovery_Gauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	TArray<ASpiritPlate*> SpiritPlates;



	//Etc Var
	bool bIsExplosion_Wait_Timer;
	float Explosion_Wait_Timer;

	bool bIsExplosion_SignWait_Timer;
	float Explosion_SignWait_Timer;

	bool bIsExplosion_Timer;
	float Explosion_Timer;
	

	float MagicAOE_Timer;

	TArray<AActor*> AOEInActor;


	FVector InitLocation;
public:	
	// Sets default values for this actor's properties
	ALabMagic();

	void StartExplosionSignWait();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void ExplosionSign();
	void StartExplosion();
	void EndExplosion();

	void Explosion(float DeltaTime);

	void AOEAttack();
};
