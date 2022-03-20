// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../../IreneCharacter.h"
#include "MbAIController.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API AMbAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMbAIController();
	virtual void OnPossess(APawn* InPawn) override;

	static const FName SpawnPosKey;
	static const FName PatrolPosKey;

	static const FName PlayerKey;
	static const FName TraceRangeKey;

	static const FName CanMeleeAttackKey;
	static const FName MeleeAttackRangeKey;
	static const FName IsAttackingKey;

	static const FName IsAttackedKey;
	static const FName IsGroggyKey;

	static const FName ReturnKey;

	void Attacked(AIreneCharacter* Player);
private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true))
	float MeleeAttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trace, Meta = (AllowPrivateAccess = true))
	float TraceRange;

};
