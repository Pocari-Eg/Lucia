// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAIController.h"
#include "BellarusAIController.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API ABellarusAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	static const FName Wing_LKey;
	static const FName Wing_RKey;
	static const FName TailKey;
	static const FName TraceTimeKey;
	static const FName FeatherKey;
	static const FName SwirlKey;

	static const FName TornadoKey;
	static const FName GuidedSwirlKey;

	static const FName CheckKey;
	static const FName TelePortKey;

	static const FName SecondPhaseKey;
public:
	ABellarusAIController();
	void Attack() override;
	void Attacked()override;
	void Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback);


	void AllAttackOff();
#pragma region SET
	void SetWingLKey(bool State);
	void SetWingRKey(bool State);
	void SetTailKey(bool State);
	void SetFeatherKey(bool State);
	void SetSwirlKey(bool State);
	void SetTornadoKey(bool State);
	void SetGuidedSwirlKey(bool State);

	void SetTelePortKey(bool State);

	void SetTraceTime(float Time);
	void SetCheckKey(bool State);
	void SetSecondPhase(bool State);
#pragma endregion SET


#pragma region GET
	bool GetWingLKey();
	bool GetWingRKey();
	bool GetTailKey();
	bool GetFeatherKey();
	bool GetSwirlKey();
	bool GetTornadoKey();
	bool GetGuidedSwirlKey();

	bool GetTelePortKey();
	bool GetCheckKey();
	bool GetSecondPhaseKey();

	float GetTraceTime();
#pragma endregion GET
protected:
	virtual void OnPossess(APawn* InPawn) override;


private:
	int M_Attacked;
	int M_MaxAttacked;
};
