// Fill out your copyright notice in the Description page of Project Settings.


#include "IsCanRushAttack.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"


UIsCanRushAttack::UIsCanRushAttack()
{
	//비헤이비어 트리 데코레이터 이름 데코레이터 = 조건문
	NodeName = TEXT("CanRushAttack");
}
bool UIsCanRushAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	//블랙보드 변수값 받아오기
	auto RangedAttackCount = OwnerComp.GetBlackboardComponent()->GetValueAsInt(AEnemyController::RangedAttackCountKey);
	
	if (RangedAttackCount < 3)
		return false;

	return true;
}