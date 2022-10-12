// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpiritPlate.generated.h"

UCLASS()
class STARRYTAIL_API ASpiritPlate : public AActor
{
	GENERATED_BODY()

//var
private:
 UPROPERTY(VisibleAnyWhere, Category = Mesh, meta = (AllowPrivateAccess = "ture"))
 UStaticMeshComponent* Mesh;
	
public:	
	// Sets default values for this actor's properties
	ASpiritPlate();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
