// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../StarryTail.h"
#include "ChainLightning.generated.h"

UCLASS()
class STARRYTAIL_API AChainLightning : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChainLightning();
	void Init();


	void SetDamage(float Value);
	float GetDamage() const;
	void SetMoveSpeed(float Value);
	void AddCount();
private:
	//Function
	void CheckDistance();
	//Var
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess))
		UParticleSystem* LightningEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* LightningEffectComponent;

	TArray<FVector> MoveTargetList;
	FVector MoveDir;
	FVector NewLocation;

	float Damage;
	float MoveSpeed;
	int TargetCount;
	int Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaitTime, Meta = (AllowPrivateAccess = true))
		float DeadWaitTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WaitTime, Meta = (AllowPrivateAccess = true))
		float DeadWaitTimer;

	bool bDead;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
