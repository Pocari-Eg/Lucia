// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterController.generated.h"

UCLASS()
class STARRYTAIL_API AMonsterController : public AActor
{
	GENERATED_BODY()

private:
	TArray<class AMonster*> CurWaveMonster;
	
	class AMonster* CurBattleMonster;


	bool bIsChange;
	float BattleChangeTimer;
	float BattleChangeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	float MinBattleChangeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	float MaxBattleChangeTime;
public:	
	// Sets default values for this actor's properties
	AMonsterController();

	void SetCloseMonster();
	void SetBattleMonster(class AMonster* Monster);
	void SetCurWaveMonsters(TArray<class AMonster*> WaveMonster);

	void ChangeBattleMonster();
	void SupportMonsterAttack();

	void BattleMonsterDelete();
	void SupportMonsterDelete(class AMonster* DeleteMonster);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
