// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "BellyfishAIController.h"
#include"BellyfishAnimInstance.h"
#include"BF_MagicAttack.h"
#include"BellyfishInfo.h"
#include"BF_Projectile.h"
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

	void Attack();
	void RushAttack();

	void PlayFireAnim();
	void ProjectileAttack();

	void Skill_Setting();
	void Skill_Set();
	void PlayRunAnim();
	void Skill_Attack();
	void Skill_AttackEnd();

	bool IntersectionCheck();

	bool RushRouteCheck();
	void RushEndFunc();
	
	void DestroyMagicAttack();

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	void PossessedBy(AController* NewController) override;

	void PostInitializeComponents() override;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	FName FireSocketName;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Test, Meta = (AllowPrivateAccess = true))
	float RushTestRange;

	
public:
	FRushEndDelegate RushEnd;
	FRushStartDelegate RushStart;

	// 카메라 위치에서의 총구 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meteor)
		UBoxComponent* ProjectileFirePos;
	// 스폰시킬 프로젝타일 클래스
	UPROPERTY(EditDefaultsOnly, Category = Meteor)
		TSubclassOf<class ABF_Projectile> ProjectileClass;
};
