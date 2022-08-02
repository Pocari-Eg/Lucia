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


	//현재 몬스터의 뒷 벡터
	FVector RunDirection = Ferno->GetActorForwardVector().RotateAngleAxis(180.0f, FVector::UpVector);

	//뒷벡터 방향으로 Distance만큼의 좌표 
	FVector RunPos = Ferno->GetTransform().GetLocation() + (RunDirection.GetSafeNormal() * Ferno->M_Run_Distance);


		// 이동 거리가 5m가 맞는지 확인용
		if (Ferno->GetTestMode())
			STARRYLOG(Warning, TEXT("Ferno to Run Distance is %.f"), FVector::Distance(Ferno->GetTransform().GetLocation(), RunPos));

		Ferno->GetAIController()->MoveToLocation(RunPos);

		return EBTNodeResult::Succeeded;
}
