// Fill out your copyright notice in the Description page of Project Settings.


#include "BellarusAIController.h"
#include "Bellarus.h"


const FName ABellarusAIController::Wing_LKey = (TEXT("Wing_L"));
const FName ABellarusAIController::Wing_RKey = (TEXT("Wing_R"));
const FName ABellarusAIController::TailKey = (TEXT("Tail"));
const FName ABellarusAIController::FeatherKey = (TEXT("Feather"));
const FName ABellarusAIController::SwirlKey = (TEXT("Swirl"));
const FName ABellarusAIController::TornadoKey = (TEXT("Tornado"));
const FName ABellarusAIController::GuidedSwirlKey = (TEXT("GuidedSwirl"));

const FName ABellarusAIController::TelePortKey = (TEXT("Teleport"));
const FName ABellarusAIController::CheckKey = (TEXT("Check"));
const FName ABellarusAIController::SecondPhaseKey = (TEXT("SecondPhase"));

const FName ABellarusAIController::TraceTimeKey = (TEXT("TraceTime"));
ABellarusAIController::ABellarusAIController()
{

	
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/Bellarus/BB_Bellarus"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/Bellarus/BT_Bellarus"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}



}

void ABellarusAIController::Attack()
{
	auto Bellarus = Cast<ABellarus>(GetPawn());
	Bellarus->Attack();
	StopMovement();
	
}

void ABellarusAIController::Attacked()
{

	Blackboard->SetValueAsBool(IsAttackedKey, true);
	Blackboard->SetValueAsBool(IsAttackingKey,false);
	Blackboard->SetValueAsBool(IsAttackCoolKey, false);
}

void ABellarusAIController::Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback)
{

	//공격 받았을때 애니메이션 실행 
	SetPlayer();


}
#pragma region SET
void ABellarusAIController::AllAttackOff()
{
	SetWingLKey(false);
	SetWingRKey(false);
	SetTailKey(false);
	SetFeatherKey(false);
	SetSwirlKey(false);
	SetTelePortKey(false);
	SetTornadoKey(false);
	SetGuidedSwirlKey(false);
}
void ABellarusAIController::SetWingLKey(bool State)
{
	Blackboard->SetValueAsBool(Wing_LKey, State);
}

void ABellarusAIController::SetWingRKey(bool State)
{
	Blackboard->SetValueAsBool(Wing_RKey, State);
}

void ABellarusAIController::SetTailKey(bool State)
{
	Blackboard->SetValueAsBool(TailKey, State);
}
void ABellarusAIController::SetFeatherKey(bool State)
{
	Blackboard->SetValueAsBool(FeatherKey, State);

}
void ABellarusAIController::SetSwirlKey(bool State)
{
	Blackboard->SetValueAsBool(SwirlKey, State);

}
void ABellarusAIController::SetTornadoKey(bool State)
{
	Blackboard->SetValueAsBool(TornadoKey, State);
}
void ABellarusAIController::SetGuidedSwirlKey(bool State)
{
	Blackboard->SetValueAsBool(GuidedSwirlKey, State);
}
void ABellarusAIController::SetTelePortKey(bool State)
{
	Blackboard->SetValueAsBool(TelePortKey, State);
}
void ABellarusAIController::SetCheckKey(bool State)
{
	Blackboard->SetValueAsBool(CheckKey, State);
}
void ABellarusAIController::SetTraceTime(float Time)
{
	Blackboard->SetValueAsFloat(TraceTimeKey, Time);
}
void ABellarusAIController::SetSecondPhase(bool State)
{
	Blackboard->SetValueAsBool(SecondPhaseKey, State);
}
#pragma endregion SET


#pragma region GET
bool ABellarusAIController::GetWingLKey()
{
	return Blackboard->GetValueAsBool(Wing_LKey);
}
bool ABellarusAIController::GetWingRKey()
{
	return Blackboard->GetValueAsBool(Wing_RKey);
}
bool ABellarusAIController::GetTailKey()
{
	return Blackboard->GetValueAsBool(TailKey);
}
bool ABellarusAIController::GetFeatherKey()
{
	return Blackboard->GetValueAsBool(FeatherKey);
}
bool ABellarusAIController::GetSwirlKey()
{
	return Blackboard->GetValueAsBool(SwirlKey);
}
bool ABellarusAIController::GetTornadoKey()
{
	return Blackboard->GetValueAsBool(TornadoKey);
}
bool ABellarusAIController::GetGuidedSwirlKey()
{
	return Blackboard->GetValueAsBool(GuidedSwirlKey);
}
bool ABellarusAIController::GetTelePortKey()
{
	return Blackboard->GetValueAsBool(TelePortKey);
}
bool ABellarusAIController::GetCheckKey()
{
	return Blackboard->GetValueAsBool(CheckKey);
}
bool ABellarusAIController::GetSecondPhaseKey()
{
	 return Blackboard->GetValueAsBool(SecondPhaseKey);
}
float ABellarusAIController::GetTraceTime()
{
	return 	Blackboard->GetValueAsFloat(TraceTimeKey);
}
#pragma endregion GET
void ABellarusAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		// 스폰 위치 저장
		auto Bellarus = Cast<ABellarus>(InPawn);

		M_MaxAttacked = Bellarus->GetMaxAttacked();
		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		Blackboard->SetValueAsFloat(TraceRangeKey, Bellarus->GetTraceRange());
		if (!RunBehaviorTree(BTAsset))
		{
			STARRYLOG(Warning, TEXT("BellarusAIController couldn't run behavior tree."));
		}
	}
}


