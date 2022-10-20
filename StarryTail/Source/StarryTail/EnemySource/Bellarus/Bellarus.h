// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "BellarusAIController.h"
#include"BellarusAnimInstance.h"
#include "Swirls/Swirl.h"
#include "Swirls/GuidedSwirl.h"
#include "Swirls/TornadoSwirl.h"
#include "FBellarusDataStruct.h"
#include "Bellarus.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FRushEndDelegate);
DECLARE_MULTICAST_DELEGATE(FRushStartDelegate);

UCLASS()
class STARRYTAIL_API ABellarus : public AMonster
{
	GENERATED_BODY()

//Function 
public:
	ABellarus();

	UBellarusAnimInstance* GetBellarusAnimInstance() const;

	void Attack();
	void Wing_L();
	void Wing_R();
	void Tail();

	void BasicSwirlAttack();
	void GuidedSwirlAttack();
	void TornadoSwirlAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Swirl)
	int SwirlAttackType;
	void SwirlAttack();

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


private:
	void InitMonsterInfo() override;
	void InitCollision() override;
	void InitMesh() override;
	void InitAnime() override;
	void InitBellarusInfo();
	bool AttackCheck(float Radius, float Hegiht, float Angle,float AttackAxis);

//Variable
	//Variable
	UPROPERTY()
		class UBellarusAnimInstance* BellarusAnimInstance;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BellarusInfo, Meta = (AllowPrivateAccess = true))
	FBellarusDataStruct BellarusInfo;

	TSubclassOf<ASwirl> SwirlClass;
	TSubclassOf<AGuidedSwirl> GuidedSwirlClass;
	TSubclassOf<ATornadoSwirl> ATornadoSwirlClass;
public:


};
