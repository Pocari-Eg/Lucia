// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskStrainRun.h"

#include"../StrainAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../../StarryTail.h"

UBTTaskStrainRun::UBTTaskStrainRun()
{
	NodeName = TEXT("StrainRun");

}

EBTNodeResult::Type UBTTaskStrainRun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

auto  Strain = Cast<AStrain>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Strain)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Strain->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;


	//���� ������ �� ����
	FVector RunDirection = Strain->GetActorForwardVector().RotateAngleAxis(180.0f, FVector::UpVector);

	//�޺��� �������� Distance��ŭ�� ��ǥ 
	FVector RunPos = Strain->GetTransform().GetLocation() + (RunDirection.GetSafeNormal() * Strain->M_Run_Distance);

	Strain->PlayRunAnim();
		// �̵� �Ÿ��� 5m�� �´��� Ȯ�ο�
		if (Strain->GetTestMode())
			STARRYLOG(Warning, TEXT("Strain to Run Distance is %.f"), FVector::Distance(Strain->GetTransform().GetLocation(), RunPos));

		Strain->GetAIController()->MoveToLocation(RunPos);

		return EBTNodeResult::Succeeded;
}
