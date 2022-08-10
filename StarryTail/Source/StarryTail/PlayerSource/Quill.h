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
	bool IsRightPos;
private:
	UPROPERTY()
	class AIreneCharacter* Irene;
	
	UPROPERTY()
	TArray<UParticleSystem*> BustParticle;
	UPROPERTY()
	TArray<UParticleSystem*> AttackParticle;

	FVector TargetLocation;
	float LifeTime;
	bool Bust;
	
public:	
	void Init(AIreneCharacter* Value);
	
	UFUNCTION()
	void StartBust();
	UFUNCTION()
	void StartAttack();

private:
	AQuill();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetIreneCharacter(AIreneCharacter* Value);
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void LookAtTarget();
	void MoveTarget();
};
