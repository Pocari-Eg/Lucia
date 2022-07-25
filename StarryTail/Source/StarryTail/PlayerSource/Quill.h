// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Quill.generated.h"

enum class EAttributeKeyword : uint8;
class UMaterialInstanceDynamic;

UCLASS()
class STARRYTAIL_API AQuill : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* DynamicMaterial;
	
	UPROPERTY()
	AActor* Target;

	EAttributeKeyword Attribute;

	float MoveSpeed;
	float Distance;
	float Strength;
private:
	float LifeTime;
	float StopTime;
	float BackMoveTime;

	FTimerDelegate ColorTimeDelegate;
public:	
	AQuill();

	UFUNCTION()
	void SetColor();
protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
public:	
	virtual void Tick(float DeltaTime) override;

};
