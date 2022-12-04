// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WalkPoint.generated.h"

UCLASS()
class LUCIA_API AWalkPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWalkPoint();
private:
	//¸Þ½¬
	UPROPERTY(VisibleAnyWhere, Category = Mesh, meta = (AllowPrivateAccess = "ture"))
		UStaticMeshComponent* Mesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
