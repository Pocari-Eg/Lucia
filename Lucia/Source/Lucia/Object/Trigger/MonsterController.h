// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Lucia.h"
#include "GameFramework/Actor.h"
#include "../../Sound/SoundPlayer.h"
#include "MonsterController.generated.h"

UCLASS()
class LUCIA_API AMonsterController : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	EState CurStage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	ASoundPlayer* BgmPlayer;
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

	void PlayBattleBgm();
	void PlayNormalBgm();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
