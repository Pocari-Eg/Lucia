// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "BellarusAIController.h"
#include"BellarusAnimInstance.h"
#include "Swirls/Swirl.h"
#include "Swirls/GuidedSwirl.h"
#include "Swirls/TornadoSwirl.h"
#include"../Bellyfish/BF_Projectile.h"
#include "FBellarusDataStruct.h"
#include "BlSoundInstance.h"
#include "TelePortPoint.h"
#include "Bellarus.generated.h"

/**
 * 
 */

UCLASS()
class LUCIA_API ABellarus : public AMonster
{
	GENERATED_BODY()

//Function 
public:
	ABellarus();

	UBellarusAnimInstance* GetBellarusAnimInstance() const;


	void PlayWingLAnim();
	void Wing_L();

	void PlayWingRAnim();
	void Wing_R();

	void PlayTailAnim();
	void Tail();


	void PlayFeatherAnim();
	void ProjectileAttack();

	void PlayTelePortAnim();


	UFUNCTION(BluePrintCallable)
	void TelePortStart();
	UFUNCTION(BluePrintCallable)
	void TelePortEnd();
	void TelePortAttackCheck();

	void ShieldRegening();
	void ShieldRegen();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Swirl)
	int SwirlAttackType;

	void PlaySwirlAnim();
	void SwirlAttack();

	void BasicSwirlAttack();
	void GuidedSwirlAttack();
	void TornadoSwirlAttack();


	void RunTelePort();
	void CalcTelePort();

	bool bIsInSpawnRadius;

	float OutSpawnRadiusTimer;


	bool ProjectileCheck();

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	void PossessedBy(AController* NewController) override;

	void PostInitializeComponents() override;

public:
	// Called every frame
	void Tick(float DeltaTime) override;

	//get 
	UFUNCTION(BlueprintCallable)
	float GetFlyDistance();
	UFUNCTION(BlueprintCallable)
	float GetMaxFlyDistance();
	//set
	UFUNCTION(BlueprintCallable)
	void SetFlyDistance(float Distance);

	void SetTelePortLocation(FVector Location) { TeleportLocation = Location; }

	float GetFirstJugdeRadius();
	float GetSecondJugdeRadius();
	float GetCalibrationRadius();
	float GetCheckTime();

	void SetSecondPhase();

	void DodgeCheck();

	bool GetSwirlWaitState() { return SwirlWait; }
	void SetSwirlWaiteState(bool State) { SwirlWait = State; }

	FMonsterSkillDataTable* GetWingData();
	FMonsterSkillDataTable* GetTailData();
	FMonsterSkillDataTable* GetSwirlData();
	FMonsterSkillDataTable* GetFeatherData();
	FMonsterSkillDataTable* GetTornado();
	FMonsterSkillDataTable* GetGuidedSwirlData();

	int GetMeleeAttackCount();
	void InitMeleeAttackCount();


	UBlSoundInstance* GetBlSound();


	UFUNCTION(BlueprintImplementableEvent)
	void TelePortStartEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void TelePortEndEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSecondPhaseEvent();
private:
	void InitMonsterInfo() override;
	void InitCollision() override;
	void InitMesh() override;
	void InitAnime() override;
	void InitBellarusInfo();
	bool AttackCheck(float Radius, float Height, float Angle,float AttackAxis);
	void IsDodgeTimeOn() override;
	void IsDodgeTimeOff()override;


	void SwirlDestroy();
	void GuidedSwirlDestory();
	void TornadoSwirlDestroy();


	void AddMeleeAttackCount();


//Variable
	//Variable
	UPROPERTY()
		class UBellarusAnimInstance* BellarusAnimInstance;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BellarusInfo, Meta = (AllowPrivateAccess = true))
	FBellarusDataStruct BellarusInfo;


	bool bIsTeleporting;
	float TelePortTime;
	float TelePortTimer;
	FVector TeleportLocation;


	bool bIsRegening;
	float RegenTime;
	float RegenTimer;

	int IsAttackNum;

	bool SwirlWait;

	bool TornadoWait;
	float SwirlWaitTime;
	float SwirlWaitTimer;
	TSubclassOf<ASwirl> SwirlClass;
	TSubclassOf<AGuidedSwirl> GuidedSwirlClass;
	TSubclassOf<ATornadoSwirl> ATornadoSwirlClass;
	TSubclassOf<ABF_Projectile> AProjectileClass;

	ASwirl* m_CenterSwirl;
	ASwirl* m_RightSwirl;
	ASwirl* m_LeftSwirl;

	int MeleeAttackCount;

	FMonsterSkillDataTable* NewSkillData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TelePort, Meta = (AllowPrivateAccess = true))
	TArray<ATelePortPoint*> TeleportPoint;
	ATelePortPoint* CurTeleportPoint;
public:
	UPROPERTY(BluePrintReadOnly)
	class UBlSoundInstance* BlSoundInstance;

};
