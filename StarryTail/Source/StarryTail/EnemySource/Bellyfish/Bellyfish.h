// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "BellyfishAIController.h"
#include"BellyfishAnimInstance.h"
#include"BF_MagicAttack.h"
#include"BellyfishInfo.h"
#include "Bellyfish.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FRushEndDelegate);

DECLARE_MULTICAST_DELEGATE(FRushStartDelegate);
UCLASS()
class STARRYTAIL_API ABellyfish : public AMonster
{
	GENERATED_BODY()

//Function 
public:
	ABellyfish();

	UBellyfishAnimInstance* GetBellyfishAnimInstance() const;

	void Walk();
	void Attack();
	void RushAttack();

	void Skill_Setting();
	void Skill_Set();
	void PlayRunAnim();
	void Skill_Attack();
	void Skill_AttackEnd();

	bool IntersectionCheck();

	bool RushRouteCheck();
	void RushEndFunc();
	

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	void PossessedBy(AController* NewController) override;

	void PostInitializeComponents() override;

	//Function
	//Function
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	// Called every frame
	void Tick(float DeltaTime) override;


	//get 
	UFUNCTION(BlueprintCallable)
	float GetFlyDistance();
	float GetRunDistance();
	float GetAttackedTime();
	float GetRushTime();
	float GetRushTestRange();
	float GetRushSpeed();
	UFUNCTION(BlueprintCallable)
	float GetMaxFlyDistance();
	float GetSkillSetTime();
	//set
	UFUNCTION(BlueprintCallable)
	void SetFlyDistance(float Distance);
private:
	void InitMonsterInfo() override;
	void InitCollision() override;
	void InitMesh() override;
	void InitAnime() override;


	void InitAttack1Data();
	void InitAttack3Data();
//Variable
	//Variable
	UPROPERTY()
		class UBellyfishAnimInstance* BellyfishAnimInstance;
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BellyfishInfo, Meta = (AllowPrivateAccess = true))
		FBellyfishInfo Info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* Magic_CircleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "ture"))
		UParticleSystem* Magic_Circle;
	TSubclassOf<ABF_MagicAttack> MagicAttackClass;
	ABF_MagicAttack* MagicAttack;

	bool IsSkillSet;
	bool IsSkillAttack;

	bool IsCloseOtherAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect,meta = (ClampMin = "0.0", ClampMax = "100.0", AllowPrivateAccess = true))
	float DodgeTimePercent;

	float IntersectionTimer;
	float SkillSetTimer;
	float SkillAttackTimer;

	//Rush
	bool bIsRush;
	bool bIsPlayerRushHit;
	bool bIsWallRushHit;


	bool RushFlyOn;
	bool RushFlyOff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Test, Meta = (AllowPrivateAccess = true))
	float RushTestRange;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo, Meta = (AllowPrivateAccess = true))
	FMonsterSkillInfo Attack1Info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo, Meta = (AllowPrivateAccess = true))
	FMonsterSkillInfo Attack3Info;
public:
	FRushEndDelegate RushEnd;
	FRushStartDelegate RushStart;
};
