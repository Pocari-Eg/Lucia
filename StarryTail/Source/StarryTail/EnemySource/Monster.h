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


#include "Common/Weapon_Soul.h"

#include "Monster.generated.h"

DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FAttackedEndDelegate);
DECLARE_MULTICAST_DELEGATE(FDeathDelegate);

DECLARE_MULTICAST_DELEGATE(FOnHpDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBarrierDelegate);
DECLARE_MULTICAST_DELEGATE(FOnSwordAttributeChangeDelegate);

DECLARE_MULTICAST_DELEGATE(FDodgeTimeSwitch);


UCLASS()
class STARRYTAIL_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

	
	 void Attack();



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
	void InitPerfectDodgeNotify();

	//FSM
	void SetBattleState();
	void SetNormalState();
	void SetSupportState();

	void DropWeaponSoul();




//delegete========================================================
	FAttackEndDelegate AttackEnd;
	FAttackedEndDelegate AttackedEnd;
	FDeathDelegate Death;

	FOnHpDelegate OnHpChanged;
	FOnBarrierDelegate OnBarrierChanged;
	FOnSwordAttributeChangeDelegate AttributeChange;

	FDodgeTimeSwitch DodgeTimeOn;
	FDodgeTimeSwitch DodgeTimeOff;
protected:
	//Function========================================================
	void InitAttackedInfo();
	void InitEffect();
	UFUNCTION(BlueprintCallable)
		void InitMonsterAttribute();
	UFUNCTION(BlueprintCallable)
	EAttributeKeyword GetMonsterAttribute() const { return MonsterInfo.MonsterAttribute; }
	void CalcHp(float Damage);
	float CalcNormalAttackDamage(float Damage);
	void CalcManaShield(float Damage);

	float CalcManaShieldDamage(float Damage);

	void PrintHitEffect(FVector AttackedPosition, AActor* Actor);

	void Attacked();

	FMonsterDataTable* GetMontserData(int32 num);
	FMonsterSkillDataTable* GetMontserSkillData(int32 num);



	void InitAttack1Data();
	void InitAttack2Data();
	void InitAttack3Data();
	void InitAttack4Data();


//Variable========================================================
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

	UPROPERTY()
	UDataTable* MonsterDataTable;
	UPROPERTY()
	UDataTable* MonsterSkillDataTable;




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

	bool bIsDodgeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	class AEnemySpawnPoint* MonsterControl;

	EMontserState CurState;

	TSubclassOf<AWeapon_Soul> Weapon_SoulClass;

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
	
	FVector KnocbackLocation;

	float ShowUITimer;
	bool bShowUI;
	bool bIsBattleState;

	//스폰 으로 생성된 몬스터인지;
	bool bIsSpawnEnemy;

	bool bIsAttackCool;

	float AttackCoolTimer;
	float AttackCoolTime;
	
	bool bIsDodgeOn;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Get Function========================================================
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
	float GetPatrolArea() const;
	float GetMaxFollowTime() const;
	int GetMaxAttacked() const;
	int GetMonsterAtkType() const;
	float GetAttackCoolTime() const;
	UMonsterAnimInstance* GetMonsterAnimInstance()const;
	bool GetIsAttackCool()const;
	float GetAttackPercent() const;
	int GetPlayerEnergy() const;
	int GetManaShieldCount() const;
	EMontserState GetState()const;
	float GetSupportPatrolRadius() const;
	float GetAttackedTime() const;

	//M_Skill_Atk ========================================================
	float GetAtkAngle() const;
	float GetAtkRange() const;
	float GetAtkHeight() const;
	bool GetIsManaShieldActive() const;
	float GetSkillRadius() const;


	FAttackRange GetAttack1Range()const;
	FAttackRange GetAttack2Range()const;
	FAttackRange GetAttack3Range()const;
	FAttackRange GetAttack4Range()const;
	//set========================================================
	void SetIsAttackCool(bool Cool);
	void SetMonsterContorl(class AEnemySpawnPoint* Object);

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


	virtual void IsDodgeTimeOn() {};
	virtual void IsDodgeTimeOff() {};

	void PerfectDodgeOff();
	void PerfectDodgeOn();
	//object
	virtual void HitCheck(AIreneCharacter* Irene) {};
};
