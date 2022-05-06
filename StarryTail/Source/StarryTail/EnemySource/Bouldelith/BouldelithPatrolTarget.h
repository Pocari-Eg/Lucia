// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../StarryTail.h"
#include "./Struct/FBouldelithDataStruct.h"
#include "BouldelithPatrolTarget.generated.h"

UCLASS()
class STARRYTAIL_API ABouldelithPatrolTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABouldelithPatrolTarget();
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, Meta = (AllowPrivateAccess = true))
		UCapsuleComponent* Collision;
};
