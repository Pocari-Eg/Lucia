// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Quill.generated.h"

enum class EAttributeKeyword : uint8;

UCLASS()
class STARRYTAIL_API AQuill : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY()
	AActor* Target;

	EAttributeKeyword Attribute;

	float MoveSpeed;
	float Distance;
	float Strength;
private:
	float LifeTime;
	
public:	
	AQuill();
	
protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
public:	
	virtual void Tick(float DeltaTime) override;

};
