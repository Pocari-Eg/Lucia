// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskFernoRun.h"

#include"../FernoAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../../StarryTail.h"

UBTTaskFernoRun::UBTTaskFernoRun()
{
	NodeName = TEXT("FernoRun");

}

EBTNodeResult::Type UBTTaskFernoRun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

auto  Ferno = Cast<AFerno>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Ferno)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Ferno->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;


	//���� ������ �� ����
	FVector RunDirection = Ferno->GetActorForwardVector().RotateAngleAxis(180.0f, FVector::UpVector);

	//�޺��� �������� Distance��ŭ�� ��ǥ 
	FVector RunPos = Ferno->GetTransform().GetLocation() + (RunDirection.GetSafeNormal() * Ferno->M_Run_Distance);


		// �̵� �Ÿ��� 5m�� �´��� Ȯ�ο�
		if (Ferno->GetTestMode())
			STARRYLOG(Warning, TEXT("Ferno to Run Distance is %.f"), FVector::Distance(Ferno->GetTransform().GetLocation(), RunPos));

		Ferno->GetAIController()->MoveToLocation(RunPos);

		return EBTNodeResult::Succeeded;
}
