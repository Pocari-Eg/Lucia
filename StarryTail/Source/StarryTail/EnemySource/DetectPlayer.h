// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DetectPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UDetectPlayer : public UBTService
{
	GENERATED_BODY()
	
public:
	UDetectPlayer();

protected:
	//���� ���� �÷��̾ �ִ��� �����ϴ� �Լ�
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
