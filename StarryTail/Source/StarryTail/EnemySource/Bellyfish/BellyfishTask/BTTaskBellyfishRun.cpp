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


	//현재 몬스터의 뒷 벡터
	FVector RunDirection = Bellyfish->GetActorForwardVector().RotateAngleAxis(180.0f, FVector::UpVector);

	//뒷벡터 방향으로 Distance만큼의 좌표 
	FVector RunPos = Bellyfish->GetTransform().GetLocation() + (RunDirection.GetSafeNormal() * Bellyfish->M_Run_Distance);

	Bellyfish->PlayRunAnim();
		// 이동 거리가 5m가 맞는지 확인용
		if (Bellyfish->GetTestMode())
			STARRYLOG(Warning, TEXT("Bellyfish to Run Distance is %.f"), FVector::Distance(Bellyfish->GetTransform().GetLocation(), RunPos));

		Bellyfish->GetAIController()->MoveToLocation(RunPos);

		return EBTNodeResult::Succeeded;
}
