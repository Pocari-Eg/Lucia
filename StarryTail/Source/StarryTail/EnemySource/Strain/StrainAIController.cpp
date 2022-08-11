// Fill out your copyright notice in the Description page of Project Settings.


#include "StrainAIController.h"
#include"Strain.h"

const FName AStrainAIController::IsAfterAttacked = (TEXT("bIsAfterAttacked"));
AStrainAIController::AStrainAIController()
{

     M_Attacked = 0;

	
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/Strain/BB_Strain"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/Strain/BT_Strain"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}


}

void AStrainAIController::Attack()
{
	auto Strain = Cast<AStrain>(GetPawn());
	Strain->Skill_Setting();
	StopMovement();
	
}

void AStrainAIController::Attacked()
{
	M_Attacked++;
	if (M_Attacked >= 1 && Blackboard->GetValueAsBool(IsRunKey) == true)
	{
		Blackboard->SetValueAsBool(IsAttackedKey, true);
		M_Attacked = 0;
	}
	else {


	
		if (M_Attacked >= M_MaxAttacked)
		{
			Blackboard->SetValueAsBool(IsAttackedKey, true);
			M_Attacked = 0;

		}

	}
}

void AStrainAIController::Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback)
{

	//공격 받았을때 애니메이션 실행 
	SetPlayer();


}

void AStrainAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		// 스폰 위치 저장
		auto Strain = Cast<AStrain>(InPawn);

		M_MaxAttacked = Strain->GetMaxAttacked();
		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		Blackboard->SetValueAsFloat(TraceRangeKey, Strain->GetTraceRange());
		if (!RunBehaviorTree(BTAsset))
		{
			STARRYLOG(Warning, TEXT("StrainAIController couldn't run behavior tree."));
		}
	}
}
