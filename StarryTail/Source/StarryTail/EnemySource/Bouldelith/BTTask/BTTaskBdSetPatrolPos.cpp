// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdSetPatrolPos.h"
#include "../BdAIController.h"
#include "../Bouldelith.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "../../../StarryTail.h"

UBTTaskBdSetPatrolPos::UBTTaskBdSetPatrolPos()
{
	NodeName = TEXT("SetPatrolPos");
}

EBTNodeResult::Type UBTTaskBdSetPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (Result == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	auto Morbit = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Morbit)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Morbit->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ABdAIController::SpawnPosKey);
	FNavLocation NextPatrol;

	// Orgin�� �߽������� �������� 600�� �� �ȿ��� ���� ��ǥ ����
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, 600.0f, NextPatrol))
	{
		float MoveRange = FMath::RandRange(4.0f, 6.0f);
		// ��ǥ�� ���ϴ� ���� ���͸� ���ϰ�
		FVector MoveDirection = NextPatrol.Location - Morbit->GetTransform().GetLocation();
		// ���� ���ͷ� 5m ������ ��ġ
		FVector PatrolPos = Morbit->GetTransform().GetLocation() + (MoveDirection.GetSafeNormal() * MoveRange * 100.0f);

		// �̵� �Ÿ��� 5m�� �´��� Ȯ�ο�
		if (Morbit->GetTestMode())
			STARRYLOG(Warning, TEXT("Morbit to PatrolPos Distance is %.f"), FVector::Distance(Morbit->GetTransform().GetLocation(), PatrolPos));

		// ������ ��ġ�� ����
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ABdAIController::PatrolPosKey, PatrolPos);
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}