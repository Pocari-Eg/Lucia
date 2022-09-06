// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBellyfishRun.h"

#include"../BellyfishAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../../StarryTail.h"

UBTTaskBellyfishRun::UBTTaskBellyfishRun()
{
	NodeName = TEXT("BellyfishRun");

}

EBTNodeResult::Type UBTTaskBellyfishRun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

auto  Bellyfish = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bellyfish)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Bellyfish->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;


	//���� ������ �� ����
	FVector RunDirection = Bellyfish->GetActorForwardVector().RotateAngleAxis(180.0f, FVector::UpVector);

	//�޺��� �������� Distance��ŭ�� ��ǥ 
	FVector RunPos = Bellyfish->GetTransform().GetLocation() + (RunDirection.GetSafeNormal() * Bellyfish->M_Run_Distance);

	Bellyfish->PlayRunAnim();
		// �̵� �Ÿ��� 5m�� �´��� Ȯ�ο�
		if (Bellyfish->GetTestMode())
			STARRYLOG(Warning, TEXT("Bellyfish to Run Distance is %.f"), FVector::Distance(Bellyfish->GetTransform().GetLocation(), RunPos));

		Bellyfish->GetAIController()->MoveToLocation(RunPos);

		return EBTNodeResult::Succeeded;
}
