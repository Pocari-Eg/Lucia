// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobFindPatrolPos.h"
#include "../MonsterAIController.h"
#include "../Monster.h"
#include"../Bellyfish/Bellyfish.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMobFindPatrolPos::UBTTaskMobFindPatrolPos()
{
    NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTaskMobFindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Monster->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AMonsterAIController::SpawnPosKey);
	FNavLocation NextPatrol;

	// Orgin을 중심점으로 반지름이 600인 원 안에서 랜덤 좌표 생성
	if (NavSystem->GetRandomPointInNavigableRadius(Origin,Monster->GetPatrolArea(), NextPatrol))
	{
		float MoveRange = FMath::RandRange(4.0f, 6.0f);
		// 좌표로 향하는 방향 벡터를 구하고
		FVector MoveDirection = NextPatrol.Location - Monster->GetTransform().GetLocation();
		// 방향 벡터로 5m 떨어진 위치
		FVector PatrolPos = Monster->GetTransform().GetLocation() + (MoveDirection.GetSafeNormal() * MoveRange * 100.0f);

		// 이동 거리가 5m가 맞는지 확인용
		if (Monster->GetTestMode())
		STARRYLOG(Warning, TEXT("Morbit to PatrolPos Distance is %.f"), FVector::Distance(Monster->GetTransform().GetLocation(), PatrolPos));

		// 구해진 위치를 저장
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMonsterAIController::PatrolPosKey, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}
