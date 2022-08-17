// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SkillSkipNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API USkillSkipNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
	virtual void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) override;
	virtual void BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime) override;
	virtual void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) override;

public:
	USkillSkipNotifyState();

private:
	UPROPERTY()
	class AIreneCharacter* Irene;
};
