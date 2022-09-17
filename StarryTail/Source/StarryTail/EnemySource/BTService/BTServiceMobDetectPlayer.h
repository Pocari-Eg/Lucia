// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Components/LineBatchComponent.h"
#include "BTServiceMobDetectPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTServiceMobDetectPlayer : public UBTService
{
	GENERATED_BODY()
public:
	UBTServiceMobDetectPlayer();
	FVector AngleToDir(float angle);
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	

	
};

ULineBatchComponent* GetDebugLineBatcher(const UWorld* InWorld, bool bPersistentLines, float LifeTime, bool bDepthIsForeground);

static float GetDebugLineLifeTime(ULineBatchComponent* LineBatcher, float LifeTime, bool bPersistent);
 void DrawRadial(const UWorld* _InWorld,
	const FMatrix& _TransformMatrix,
	float _Radius,
	float _Angle,
	const FColor& _Color,
	int32 _Segments,
	float _LifeTime,
	bool _bPersistentLines,
	uint8 _DepthPriority,
	float _Thickness);