// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbFindPatrolPos.h"
#include "../MbAIController.h"
#include "../Morbit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "../../../StarryTail.h"

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
	
	// Orgin�� �߽������� �������� 500�� �� �ȿ��� ���� ��ǥ ����
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, 500.0f, NextPatrol))
	{
		// ��ǥ�� ���ϴ� ���� ���͸� ���ϰ�
		FVector MoveDirection = NextPatrol.Location - Morbit->GetTransform().GetLocation();
		// ���� ���ͷ� 5m ������ ��ġ
		FVector PatrolPos = Morbit->GetTransform().GetLocation() + (MoveDirection.GetSafeNormal() * 500.0f);
		
		// �̵� �Ÿ��� 5m�� �´��� Ȯ�ο�
		if(Morbit->GetTestMode())
			STARRYLOG(Warning, TEXT("Morbit to PatrolPos Distance is %.f"), FVector::Distance(Morbit->GetTransform().GetLocation(), PatrolPos));

		// ������ ��ġ�� ����
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMbAIController::PatrolPosKey, PatrolPos);
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}
