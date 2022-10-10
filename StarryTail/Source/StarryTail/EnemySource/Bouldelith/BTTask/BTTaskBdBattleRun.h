// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "BTTaskBdBattleRun.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskBdBattleRun : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskBdBattleRun();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	void Attack4Trace(class AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center);

	float AttackInterverTimer;
};
