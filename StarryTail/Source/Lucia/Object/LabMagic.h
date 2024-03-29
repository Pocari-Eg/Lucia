// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Lucia.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../EnemySource/MonsterProjectile.h"
#include "../PlayerSource/IreneCharacter.h"
#include "../PlayerSource/PlayerInstance/IreneInputInstance.h"
#include "../STGameInstance.h"
#include"SpiritPlate.h"
#include "../Sound/SoundManager.h"
#include "LabMagic.generated.h"

UCLASS()
class LUCIA_API ALabMagic : public AActor
{
	GENERATED_BODY()

//var
private:
 
	//Min Var
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Area, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* RootPoint;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Area, Meta = (AllowPrivateAccess = true))
	UBoxComponent* ActiveTrigger;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Area, Meta = (AllowPrivateAccess = true))
	UCapsuleComponent* MagicAOECollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ExplosionSignEffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ExplosionEffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ShockEffectComponent;

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


	TArray<ASpiritPlate*> Use_SpiritPlates;
	//Etc Var
	bool bIsExplosion_Wait_Timer;
	float Explosion_Wait_Timer;

	bool bIsExplosion_SignWait_Timer;
	float Explosion_SignWait_Timer;

	bool bIsExplosion_Timer;
	float Explosion_Timer;
	

	float MagicAOE_Timer;

	TArray<AActor*> AOEInActor;

	ASpiritPlate* CurPlate;

	FVector InitLocation;


	//sound
	class UFMODEvent* ShockWaveEvent;
	class UFMODEvent* SignwaitEvent;
	class UFMODEvent* WaitEvent;
	class UFMODEvent* ExplosionEvent;

	SoundManager* ShockWaveSound;
	SoundManager* SignwaitSound;
	SoundManager* WaitSound;
	SoundManager* ExplosionSound;
public:	
	// Sets default values for this actor's properties
	ALabMagic();

	void StartExplosionSignWait();
	UFUNCTION(BlueprintImplementableEvent)
		void ApplyDamageEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ActiveLabMagic(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void ExplosionSign();
	void StartExplosion();
	void EndExplosion();

	void Explosion(float DeltaTime);

	void AOEAttack();


	void EndLabMagic();
};
