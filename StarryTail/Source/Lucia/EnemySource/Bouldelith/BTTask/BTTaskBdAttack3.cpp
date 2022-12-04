// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdAttack3.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../STGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBdAttack3::UBTTaskBdAttack3()
{
	NodeName = TEXT("Attack3");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdAttack3::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());


	auto GameInstance = Cast<USTGameInstance>(Bouldelith->GetGameInstance());
	FVector LookVector = GameInstance->GetPlayer()->GetActorLocation() - Bouldelith->GetLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Bouldelith->SetActorRotation(FMath::RInterpTo(Bouldelith->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));

	Bouldelith->Attack3();

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);

	bIsAttacking = true;
	Bouldelith->Attack3End.AddLambda([this]() -> void { bIsAttacking = false; });
	return EBTNodeResult::InProgress;
}
void UBTTaskBdAttack3::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (!bIsAttacking)
	{

	
		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);
		Monster->GetAIController()->OffAttack(3);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}