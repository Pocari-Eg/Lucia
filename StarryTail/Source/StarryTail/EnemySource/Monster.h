// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Struct/FNormalMonsterInfo.h"
#include "./Struct/FAttackedInfo.h"
#include "./Struct/FMonsterEffectData.h"
#include "../StarryTail.h"
#include "MonsterAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "MonsterSoundInstance.h"

#include "Monster.generated.h"

DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FAttackedEndDelegate);
DECLARE_MULTICAST_DELEGATE(FDeathDelegate);

DECLARE_MULTICAST_DELEGATE(FOnHpDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBarrierDelegate);
DECLARE_MULTICAST_DELEGATE(FOnSwordAttributeChangeDelegate);
UCLASS()
class STARRYTAIL_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

	//Function
	float GetMeleeAttackRange() const;
	float GetTraceRange() const;
	float GetDetectMonsterRange() const;
	float GetHp() const;
	float GetBattleWalkSpeed() const;
	bool GetTestMode() const;
	float GetViewAngle() const;
	float GetViewRange() const;
	float GetViewHeight() const;
	EAttributeKeyword GetAttribute() const;
	float GetDistanceToPlayer() const;
	FVector GetLocation() const;
	bool GetIsBattleState() const;
	EAttributeKeyword GetBarrierAttribute() const;
	int GetCurQuillStack() const;
	void SetCurQuillStack(const int Value);

	AMonsterAIController* GetAIController() const;

	//현재 체력 비율 전환
	float GetHpRatio();
	//현재 방어막 비율 전환
	float GetDefRatio();
	//속성변환 델리게이트
	void ChangeAttributeDelegate();

	void PlayIdleAnim();
	void PlayDetectAnim();
	void PlayWalkAnim();
	void PlayGroggyAnim();
	void PlayDeathAnim();

	void SetSpawnPos();
	void SetAttackedInfo(bool bIsUseMana, float Mana, EAttackedDirection AttackedDirection);
	void SetIsBattleState(bool Value);

	TArray<FOverlapResult> DetectMonster(float DetectRange);
	TArray<FOverlapResult> DetectPlayer(float DetectRange);
	FVector AngleToDir(float angle);

	void OffShockDebuffEffect();
	void OffIsAttacked();

	void RotationToPlayerDirection();

	FAttackEndDelegate AttackEnd;
	FAttackedEndDelegate AttackedEnd;
	FDeathDelegate Death;

	FOnHpDelegate OnHpChanged;
	FOnBarrierDelegate OnBarrierChanged;
	FOnSwordAttributeChangeDelegate AttributeChange;

	UFUNCTION(BlueprintImplementableEvent)
	void  OnSpawnEffectEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void  HitStopEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void  MonsterDeadEvent();

	//UI
	void MarkerOn();
    void MarkerOff();

	void TargetWidgetOn();
	void TargetWidgetOff();

	//스폰 생성 몬스터 설정
	void SetSpawnEnemy();
	EEnemyRank GetRank();


	UFUNCTION(BlueprintCallable)
	void InitManaShield();
protected:
	//Function
	void InitAttackedInfo();
	void InitEffect();
	UFUNCTION(BlueprintCallable)
		void InitMonsterAttribute();
	UFUNCTION(BlueprintCallable)
	EAttributeKeyword GetMonsterAttribute() const { return MonsterInfo.MonsterAttribute; }
	void CalcHp(float Damage);
	float CalcNormalAttackDamage(float Damage);
	void CalcManaShield(float Damage,EAttributeKeyword AttackAttribute);
	void CalcQuillStack(EAttributeKeyword AttackAttribute);

	void PrintHitEffect(FVector AttackedPosition, AActor* Actor);
	//Variable
	AMonsterAIController* MonsterAIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		FNormalMonsterInfo MonsterInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		FMonsterEffectData MonsterEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* HitEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* BurnEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* FloodingEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* SparkEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* GroggyEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ManaShiledEffectComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackedInfo, Meta = (AllowPrivateAccess = true))
		FAttackedInfo AttackedInfo;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, Meta = (AllowPrivateAccess = true))
	UCapsuleComponent* WidgetPoint;
	//박찬영 UI
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* MonsterWidget;
	//박찬영 UI
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* TargetWidget;

	//사운드
	UPROPERTY(BluePrintReadOnly)
	class UMonsterSoundInstance* SoundInstance;

	UPROPERTY()
		class UMonsterAnimInstance* MonsterAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestMode, Meta = (AllowPrivateAccess = true))
		float KnockBackTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestMode, Meta = (AllowPrivateAccess = true))
		float ShowUITime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestMode, Meta = (AllowPrivateAccess = true))
		bool bTestMode;

	float MaxBarrier;

	bool bIsAttacking;
	bool bIsAttacked;
	bool bIsGroggy;
	bool bIsDead;
	bool bDeadWait;

	bool bIsSpark;
	bool bIsObject;
#pragma region Sound
	FTransform SoundTransform;
#pragma endregion Sound
private:
	//Function
	bool CheckPlayerIsBehindMonster();

	void SetEffect();
	void SetManaShieldEffct();


	void SetActive();
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	//Variable
	FVector AssembleLocation;
	FVector KnockBackDir;
	float KnockBackTimer;

	float DeadWaitTimer;



	bool bIsBurn;
	bool bIsFlooding;


	float ShowUITimer;
	bool bShowUI;
	bool bIsBattleState;

	//스폰 으로 생성된 몬스터인지;
	bool bIsSpawnEnemy;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void InitMonsterInfo() {};
	virtual void InitCollision() {};
	virtual void InitMesh() {};
	virtual void InitAnime() {};
  
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void PostInitializeComponents() override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	//object
	virtual void HitCheck(AIreneCharacter* Irene) {};
};
