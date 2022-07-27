// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Quill.generated.h"

enum class EAttributeKeyword : uint8;
class UMaterialInstanceDynamic;

UCLASS()
class STARRYTAIL_API AQuill : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(BlueprintReadWrite)
	AActor* Target;

	EAttributeKeyword Attribute;

	float MoveSpeed;
	float Distance;
	float Strength;
private:
	UPROPERTY()
	TArray<UParticleSystem*> BustParticle;
	UPROPERTY()
	TArray<UParticleSystem*> AttackParticle;
	
	float LifeTime;
	float StopTime;
	float BackMoveTime;
	bool Bust;

public:	
	AQuill();

	UFUNCTION()
	void StartBust();
	UFUNCTION()
	void StartAttack();
protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	void FollowTarget();
	
public:	
	virtual void Tick(float DeltaTime) override;

};
