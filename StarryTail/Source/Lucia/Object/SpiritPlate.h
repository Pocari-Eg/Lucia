// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SpiritPlate.generated.h"

UCLASS()
class LUCIA_API ASpiritPlate : public AActor
{
	GENERATED_BODY()

//var
private:
 UPROPERTY(EditAnywhere, Category = Mesh, meta = (AllowPrivateAccess = "ture"))
 UStaticMeshComponent* Mesh;
 UPROPERTY(EditAnywhere, Category = Mesh, meta = (AllowPrivateAccess = "ture"))
 UCapsuleComponent* SpiritPlateColiision;
 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
 UParticleSystemComponent* PlateEffectComponent;


 float SpiritRecovery_HP;
 float SpiritRecovery_Gauge;

 bool bIsInPlayer;
 float RecoveryTimer;

 float InitHeight;

public:	
	// Sets default values for this actor's properties
	ASpiritPlate();

	
	void SpiritPlateOn();
	void SpiritPlateOff();
	void InitSpiritPlate(float HP,float Gauge);


	UFUNCTION(BlueprintImplementableEvent)
		void PlateOnEvent();
	UFUNCTION(BlueprintImplementableEvent)
		void PlateOffEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetIsInPlayer() { return bIsInPlayer; }

};
