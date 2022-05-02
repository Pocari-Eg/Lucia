// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobRotateToTarget.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../STGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMobRotateToTarget::UBTTaskMobRotateToTarget()
{
	NodeName = TEXT("RotateToTarget");
}
EBTNodeResult::Type UBTTaskMobRotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	auto GameInstance = Cast<USTGameInstance>(Monster->GetGameInstance());
	if (nullptr == GameInstance)
		return EBTNodeResult::Failed;

	FVector LookVector = GameInstance->GetPlayer()->GetActorLocation() - Monster->GetLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	
	Monster->SetActorRotation(FMath::RInterpTo(Monster->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}