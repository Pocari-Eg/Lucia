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
#include"Common/MonsterShield.h"


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
	 virtual void SupportAttack();


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
	void PlayBattleWalkAnim();
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
	UFUNCTION(BlueprintImplementableEvent)
	void  ShieldDestroyEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void  PointOff();

	UFUNCTION(BlueprintImplementableEvent)
	void  PointOn();
	//UI
	void MarkerOn();
    void MarkerOff();

	void StackWidgetOn();
	void StackWidgetOff();

	//스폰 생성 몬스터 설정
	void SetSpawnEnemy();
	EEnemyRank GetRank();


	//GroupTrigger 몬스터 설정
	void SetGroup();
	void SetStatue(bool state);

	void InitPerfectDodgeNotify();

	//FSM
	void SetBattleState();
	void SetNormalState();
	void SetSupportState();

	void DropWeaponSoul();


	void DeathCheck();

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
	void CalcHp(float Damage);
	float CalcNormalAttackDamage(float Damage);
	void PrintHitEffect(FVector AttackedPosition, AActor* Actor);

	void Attacked();

	FMonsterDataTable* GetMontserData(int32 num);
	FMonsterSkillDataTable* GetMontserSkillData(int32 num);

	void ShieldDestroyed();

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
		UParticleSystemComponent* GroggyEffectComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackedInfo, Meta = (AllowPrivateAccess = true))
		FAttackedInfo AttackedInfo;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, Meta = (AllowPrivateAccess = true))
	UCapsuleComponent* WidgetPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shield, Meta = (AllowPrivateAccess = true))
	UMonsterShield* MonsterShield;

	//shield
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	UCapsuleComponent* ShieldCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ShiledCrackEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ShiledHitEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ShiledEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	FName ShieldSocketName;
	//박찬영 UI
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* MonsterWidget;
	//박찬영 UI
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = UI)
	class UWidgetComponent* StackWidget;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestMode, Meta = (AllowPrivateAccess = true))
	bool bIsAttacking;
	bool bIsAttacked;
	bool bIsGroggy;
	bool bIsDead;
	bool bDeadWait;


	bool bIsDodgeTime;

	bool bIsDpsCheck;
	float DpsDamage;
	float DpsTime;
	float DpsTimer;

	bool bIsStatueStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
	class AMonsterController* MonsterController;

	EMonsterState CurState;

	TSubclassOf<AWeapon_Soul> Weapon_SoulClass;

	float AttacekdTeleportTimer;

#pragma region Sound
	FTransform SoundTransform;
#pragma endregion Sound
private:
	//Function
	bool CheckPlayerIsBehindMonster();

	void SetEffect();


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
	//
	bool bIsGroupTriggerEnemy;

	float AttackCoolTimer;
	float AttackCoolTime;
	
	bool bIsDodgeOn;

	bool bIsStackOn;


	
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
	EMonsterState GetState()const;
	float GetSupportPatrolRadius() const;
	float GetAttackedTime() const;
	EAttributeKeyword GetAttribute() const;
	float GetAttackTraceInterver() const;
	FNormalMonsterInfo GetMonsterInfo() const;
	bool GetIsAttacking()const;
	//M_Skill_Atk ========================================================
	float GetAtkAngle() const;
	float GetAtkRange() const;
	float GetAtkHeight() const;
	bool GetIsMonsterShieldActive() const;
	float GetSkillRadius() const;
	float GetToPlayerDistance();
	float GetMoveSpeed()const;

	float GetBattleRange()const;
	float GetSupportRange()const;

	float GetRotateRate();


	FAttackRange GetAttack1Range()const;
	FAttackRange GetAttack2Range()const;
	FAttackRange GetAttack3Range()const;
	FAttackRange GetAttack4Range()const;
	//set========================================================
	void SetIsAttackCool(bool Cool);
	void SetMonsterContorller(class AMonsterController* Object);
	void SetDpsCheck(bool state);
	void SetIsAttacking(bool State) { bIsAttacking = State; }
	void InitWalkSpeed();

	//Stack
	UFUNCTION(BlueprintCallable)
	int GetCurStackCount();
	UFUNCTION(BlueprintImplementableEvent)
	void  OnStackCountEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void  ExplodeStackEvent();
	void AddStackCount(int Count);
	void StackExplode();
	UFUNCTION(BlueprintCallable)
	void MaxStackExplode();
	void InitStackCount();
	float CalcStackDamage(int StackCount);

	void MoveToPlayer(float DeltaSeconds);
	void RotationPlayer(float DeltaSeconds);
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
