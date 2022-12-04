// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbFindPatrolPos.h"
#include "../MbAIController.h"
#include "../Morbit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "../../../Lucia.h"

UBTTaskMbFindPatrolPos::UBTTaskMbFindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTaskMbFindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Morbit = Cast<AMorbit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Morbit)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Morbit->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AMbAIController::SpawnPosKey);
	FNavLocation NextPatrol;
	
	// Orgin을 중심점으로 반지름이 600인 원 안에서 랜덤 좌표 생성
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, 600.0f, NextPatrol))
	{
		float MoveRange = FMath::RandRange(4.0f, 6.0f);

		// 좌표로 향하는 방향 벡터를 구하고
		FVector MoveDirection = NextPatrol.Location - Morbit->GetTransform().GetLocation();
		// 방향 벡터로 5m 떨어진 위치
		FVector PatrolPos = Morbit->GetTransform().GetLocation() + (MoveDirection.GetSafeNormal() * MoveRange * 100.0f);
		
		// 이동 거리가 5m가 맞는지 확인용
		if(Morbit->GetTestMode())
			STARRYLOG(Warning, TEXT("Morbit to PatrolPos Distance is %.f"), FVector::Distance(Morbit->GetTransform().GetLocation(), PatrolPos));

		// 구해진 위치를 저장
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMbAIController::PatrolPosKey, PatrolPos);
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}
