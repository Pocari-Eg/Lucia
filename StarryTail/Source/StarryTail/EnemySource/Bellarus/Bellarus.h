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
#include "Bellarus.generated.h"

/**
 * 
 */

UCLASS()
class STARRYTAIL_API ABellarus : public AMonster
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
	void TelePortStart();
	void TelePortEnd();

	void ShieldRegening();
	void ShieldRegen();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Swirl)
	int SwirlAttackType;

	void PlaySwirlAnim();
	void SwirlAttack();

	void BasicSwirlAttack();
	void GuidedSwirlAttack();
	void TornadoSwirlAttack();


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

	FMonsterSkillDataTable* GetWingData();
	FMonsterSkillDataTable* GetTailData();
	FMonsterSkillDataTable* GetSwirlData();
	FMonsterSkillDataTable* GetFeatherData();
	FMonsterSkillDataTable* GetTornado();
	FMonsterSkillDataTable* GetGuidedSwirlData();

private:
	void InitMonsterInfo() override;
	void InitCollision() override;
	void InitMesh() override;
	void InitAnime() override;
	void InitBellarusInfo();
	bool AttackCheck(float Radius, float Height, float Angle,float AttackAxis);


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

	TSubclassOf<ASwirl> SwirlClass;
	TSubclassOf<AGuidedSwirl> GuidedSwirlClass;
	TSubclassOf<ATornadoSwirl> ATornadoSwirlClass;
	TSubclassOf<ABF_Projectile> AProjectileClass;
public:


};
