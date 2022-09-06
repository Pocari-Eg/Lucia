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

	// Orgin�� �߽������� �������� 600�� �� �ȿ��� ���� ��ǥ ����
	if (NavSystem->GetRandomPointInNavigableRadius(Origin,Monster->GetPatrolArea(), NextPatrol))
	{
		float MoveRange = FMath::RandRange(4.0f, 6.0f);
		// ��ǥ�� ���ϴ� ���� ���͸� ���ϰ�
		FVector MoveDirection = NextPatrol.Location - Monster->GetTransform().GetLocation();
		// ���� ���ͷ� 5m ������ ��ġ
		FVector PatrolPos = Monster->GetTransform().GetLocation() + (MoveDirection.GetSafeNormal() * MoveRange * 100.0f);

		// �̵� �Ÿ��� 5m�� �´��� Ȯ�ο�
		if (Monster->GetTestMode())
		STARRYLOG(Warning, TEXT("Morbit to PatrolPos Distance is %.f"), FVector::Distance(Monster->GetTransform().GetLocation(), PatrolPos));

		// ������ ��ġ�� ����
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMonsterAIController::PatrolPosKey, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}
