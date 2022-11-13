// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskFeather.h"
#include "../Bellarus.h"
#include "../BellarusAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "../../../STGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskFeather::UBTTaskFeather()
{
	NodeName = TEXT("FeatherATTACK");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskFeather::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bellarus = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());

	auto GameInstance = Cast<USTGameInstance>(Bellarus->GetGameInstance());
	if (nullptr == GameInstance)
		return EBTNodeResult::Failed;


	FVector LookVector = GameInstance->GetPlayer()->GetActorLocation() - Bellarus->GetLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Bellarus->SetActorRotation(FMath::RInterpTo(Bellarus->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));


	Bellarus->PlayFeatherAnim();
	Bellarus->GetAIController()->StopMovement();
	bIsAttacking = true;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);
	Bellarus->AttackEnd.AddLambda([this]() -> void { bIsAttacking = false; });



	return EBTNodeResult::InProgress;
}
void UBTTaskFeather::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (!bIsAttacking)
	{
	
		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);

		Cast<ABellarusAIController>(Monster->GetAIController())->AllAttackOff();
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);


		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}