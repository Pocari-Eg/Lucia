// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScAttack2.h"
#include "../Scientia.h"
#include "../ScAIController.h"

UBTTaskScAttack2::UBTTaskScAttack2()
{
	NodeName = TEXT("Attack2");
	bNotifyTick = true;

}
EBTNodeResult::Type UBTTaskScAttack2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScAIController::PlayerKey));

	AttackCount = 0;

	Scientia->Attack2();
	Scientia->SetState(TEXT("Attack2"));

	NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	NavData = NavSys->GetNavDataForProps(Scientia->GetNavAgentPropertiesRef());

	FilterClass = UNavigationQueryFilter::StaticClass();
	QueryFilter = UNavigationQueryFilter::GetQueryFilter(*NavData, FilterClass);

	Scientia->ClawFEnd.Clear();
	Scientia->ClawStart.AddLambda([this]() -> void
		{
			bIsMove = true;
		});
	Scientia->ClawPreStart.AddLambda([this]() -> void {
			bIsClawPre = true;
			STARRYLOG(Log, TEXT("1"));
		});
	Scientia->ClawFEnd.AddLambda([this]() -> void {
			bIsMove = false;
			AttackCount++;
		});
	Scientia->ClawBEnd.AddLambda([this, Scientia]() -> void {
			bIsAttacking = false;
			Scientia->Attack2();
		});
	Scientia->ClawPreEnd.AddLambda([this, Player, Scientia]() -> void {
			bIsClawPre = false;
			bIsAttacking = true;
		});
	
	
	return EBTNodeResult::InProgress;
}
void UBTTaskScAttack2::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
	if (AttackCount == 3)
	{
		if (Scientia->GetClawSuccessedCount() == 0)
		{
			Scientia->PlayStuckAnim();
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsStuckKey, true);
			Scientia->SetState(TEXT("Stuck"));
		}

		Scientia->ResetClawSuccessedCount();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttackingKey, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack2Key, false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	if(bIsClawPre)
	{
		auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScAIController::PlayerKey));

		MoveDir = Player->GetActorLocation() - Scientia->GetLocation();
		FVector LookVector = MoveDir;
		LookVector.Z = 0.0f;
		FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

		Scientia->SetActorRotation(FMath::RInterpTo(Scientia->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
	}
	if(bIsMove)
	{
		NewLocation = Scientia->GetTransform().GetLocation() + (MoveDir.GetSafeNormal() * Scientia->GetAttack2Speed() * DeltaSeconds);

		if (NavData)
		{
			MyAIQuery = FPathFindingQuery(this, *NavData, Scientia->GetActorLocation(), NewLocation, QueryFilter);
			bCanMove = NavSys->TestPathSync(MyAIQuery, EPathFindingMode::Regular);
		}

		if (bCanMove)
		{
			Scientia->SetActorLocation(NewLocation);
		}
	}
}
