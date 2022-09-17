// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBellyfishProjectile.h"

UBTTaskBellyfishProjectile::UBTTaskBellyfishProjectile()
{
	NodeName = TEXT("Attack2");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBellyfishProjectile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bellyfish = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bellyfish)
		return EBTNodeResult::Failed;


	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);




	bIsAttacking = true;
	Bellyfish->AttackEnd.AddLambda([this]() -> void { bIsAttacking = false; });



	return EBTNodeResult::InProgress;
}

void UBTTaskBellyfishProjectile::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	auto Bellyfish = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABellyfishAIController::PlayerKey));

	if (SkillSetTimer < Bellyfish->GetSkillSetTime())
	{
		SkillSetTimer += DeltaSeconds;
		if (SkillSetTimer >= Bellyfish->GetSkillSetTime())
		{
			Bellyfish->PlayFireAnim();
		
			return;
		}
		else {
			FVector LookVector = Player->GetActorLocation() - Bellyfish->GetActorLocation();
			LookVector.Z = 0.0f;
			FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
			Bellyfish->SetActorRotation(TargetRot);//FMath::RInterpTo(Bellyfish->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
			DrawDebugLine(GetWorld(), Bellyfish->GetActorLocation(), Bellyfish->GetActorLocation() + (LookVector * Bellyfish->GetSkillRadius()), FColor::Red, false, 0.2f);
			return;
		}
	}

	if (!bIsAttacking)
	{
		SkillSetTimer = 0.0f;
		auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
		if (nullptr == Monster) {
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}


		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);
		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);
		Monster->GetAIController()->OffAttack(2);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::B_IdleKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	}
}
