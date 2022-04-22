// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbRotateToTarget.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "../Morbit.h"
#include "../MbAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../../STGameInstance.h"
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

	auto GameInstance = Cast<USTGameInstance>(Morbit->GetGameInstance());
	if (nullptr == GameInstance)
		return EBTNodeResult::Failed;

	FVector LookVector = GameInstance->GetPlayer()->GetActorLocation() - Morbit->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	
	Morbit->SetActorRotation(FMath::RInterpTo(Morbit->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}