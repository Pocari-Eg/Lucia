// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBellyfishRush.h"
#include "../Bellyfish.h"
#include "../BellyfishAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
UBTTaskBellyfishRush::UBTTaskBellyfishRush()
{
	NodeName = TEXT("RushAttack");
	bNotifyTick = true;
	RushDistance = 0.0f;
	SkillSetTimer = 0.0f;
}

EBTNodeResult::Type UBTTaskBellyfishRush::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);

	auto Bellyfish = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABellyfishAIController::PlayerKey));


	MoveDir = Player->GetActorLocation() - Bellyfish->GetActorLocation();
	MoveDir.Z = Bellyfish->GetActorLocation().Z;

	NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	NavData = NavSys->GetNavDataForProps(Bellyfish->GetNavAgentPropertiesRef());

	FilterClass = UNavigationQueryFilter::StaticClass();
	QueryFilter = UNavigationQueryFilter::GetQueryFilter(*NavData, FilterClass);



	Bellyfish->RushStart.AddLambda([this]() -> void {
		bIsRush = true;
	
		});

	Bellyfish->RushEnd.AddLambda([this]() -> void {

		RushDistance = 99999999.0f;
		});

	return EBTNodeResult::InProgress;
}

void UBTTaskBellyfishRush::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Bellyfish = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABellyfishAIController::PlayerKey));

	if (RushDistance >= Bellyfish->GetSkillRadius())
	{
		STARRYLOG(Warning, TEXT("Stop"));
		Bellyfish->RushEndFunc();
		

		bIsRush = false;
		RushDistance = 0.0f;
		SkillSetTimer = 0.0f;
		Bellyfish->GetAIController()->OffAttack(3);

		auto ran = FMath::RandRange(1, 100);
		STARRYLOG(Error, TEXT("Attacked Percent : %d"), ran);
		if (ran <=70)
		{
			Bellyfish->GetAIController()->OnAttack(1);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return;
		}
		Bellyfish->GetAIController()->SetAttackCoolKey(true);
		Bellyfish->SetIsAttackCool(true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAttackingKey, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::B_IdleKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	if (SkillSetTimer < Bellyfish->GetSkillSetTime())
	{
		SkillSetTimer += DeltaSeconds;
		if (SkillSetTimer >= Bellyfish->GetSkillSetTime())
		{
			Bellyfish->RushAttack();
			return;
		}
		else {

			MoveDir = Player->GetActorLocation() - Bellyfish->GetActorLocation();
			FVector LookVector = MoveDir;
			LookVector.Z = 0.0f;
			TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
			Bellyfish->SetActorRotation(TargetRot);//FMath::RInterpTo(Bellyfish->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
			DrawDebugLine(GetWorld(), Bellyfish->GetActorLocation(), Bellyfish->GetActorLocation() + (LookVector * Bellyfish->GetSkillRadius()), FColor::Red, false, 0.2f);
			return;
		}
	}

	if (bIsRush==true)
	{
		Bellyfish->SetActorRotation(TargetRot);
		FVector Dir = Bellyfish->GetTransform().GetLocation() + (MoveDir.GetSafeNormal() * Bellyfish->GetRushSpeed());
		//FVector Dir = Bellyfish->GetTransform().GetLocation() + (Mov;

		RushDistance += Bellyfish->GetRushSpeed();
		if (RushDistance < Bellyfish->GetSkillRadius()) {
			Dir.Z = Bellyfish->GetActorLocation().Z;
			Bellyfish->SetActorLocation(Dir);
		}
		return;
	}


	
	
}
