// Fill out your copyright notice in the Description page of Project Settings.


#include "BellyfishAIController.h"
#include "Bellyfish.h"

const FName ABellyfishAIController::IsAfterAttacked = (TEXT("bIsAfterAttacked"));
ABellyfishAIController::ABellyfishAIController()
{

     M_Attacked = 0;

	
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/Bellyfish/BB_Bellyfish"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/Bellyfish/BT_Bellyfish"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}


}

void ABellyfishAIController::Attack()
{
	auto Bellyfish = Cast<ABellyfish>(GetPawn());
	Bellyfish->Attack();
	StopMovement();
	
}

void ABellyfishAIController::Attacked()
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

void ABellyfishAIController::Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback)
{

	//공격 받았을때 애니메이션 실행 
	SetPlayer();


}

void ABellyfishAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		// 스폰 위치 저장
		auto Bellyfish = Cast<ABellyfish>(InPawn);

		M_MaxAttacked = Bellyfish->GetMaxAttacked();
		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		Blackboard->SetValueAsFloat(TraceRangeKey, Bellyfish->GetTraceRange());
		if (!RunBehaviorTree(BTAsset))
		{
			STARRYLOG(Warning, TEXT("BellyfishAIController couldn't run behavior tree."));
		}
	}
}
