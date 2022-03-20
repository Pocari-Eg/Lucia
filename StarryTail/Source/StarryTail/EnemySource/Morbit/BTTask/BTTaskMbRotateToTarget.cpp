// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbRotateToTarget.h"
#include "../../../IreneCharacter.h"
#include "../Morbit.h"
#include "../MbAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMbRotateToTarget::UBTTaskMbRotateToTarget()
{
	NodeName = TEXT("RotateToTarget");
}
EBTNodeResult::Type UBTTaskMbRotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Morbit = Cast<AMorbit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Morbit)
		return EBTNodeResult::Failed;

	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMbAIController::PlayerKey));
	if (nullptr == Player)
		return EBTNodeResult::Failed;

	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(Morbit->GetActorLocation(), Player->GetActorLocation());
	Morbit->SetActorRotation(FMath::RInterpTo(Morbit->GetActorRotation(), Rotator, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}