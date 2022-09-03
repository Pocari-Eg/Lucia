// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../StarryTail.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "../MonsterProjectile.h"
#include "ST_Projectile.generated.h"

UCLASS()
class STARRYTAIL_API AST_Projectile : public  AMonsterProjectile
{
	GENERATED_BODY()

//var
public:
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Info")
		float Speed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FQuat RotationQuat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RealRotation;
private:
	
public:	
	// Sets default values for this actor's properties
	AST_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
