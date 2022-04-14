// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Struct/FNormalMonsterInfo.h"
#include "./Struct/FAttributeDefence.h"
#include "./Struct/FAttributeDebuff.h"
#include "./Struct/FAttackedInfo.h"
#include "./Struct/FMonsterEffectData.h"
#include "../StarryTail.h"
#include "MonsterAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FDeathDelegate);

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
	TArray<EAttributeKeyword> GetMainAttributeDef() const;

	UMonsterAnimInstance* GetMonsterAnimInstance() const;

	void SetAttackedInfo(bool bIsUseMana, float Mana);

	void OnTrueDamage(float Damage);
	void OnDamage(EAttributeKeyword PlayerMainAttribute, float Damage);

	void AddDebuffStack(EAttributeKeyword Attribute);

	TArray<FOverlapResult> DetectMonster(float DetectRange);

	void ResetDef();

	void OffShockDebuffEffect();
	void OffIsAttacked();

	FAttackEndDelegate AttackEnd;
	FDeathDelegate Death;

	UFUNCTION(BlueprintImplementableEvent)
	void  HitStopEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void  MonsterDeadEvent();

protected:
	virtual void InitMonsterInfo() {};
	virtual void InitCollision() {};
	virtual void InitMesh() {};
	virtual void InitAnime() {};

	//Function
	void InitDebuffInfo();
	void InitAttackedInfo();

	void CalcAttributeDefType();
	void CalcAttributeDebuff(EAttributeKeyword PlayerMainAttribute, float Damage);
	void CalcDef();
	float CalcNormalAttackDamage(float Damage);
	float CalcManaAttackDamage(float Damage);

	void PrintHitEffect(FVector AttackedPosition);

	//Variable

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		FNormalMonsterInfo MonsterInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		FAttributeDefence AttributeDef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAcess = true))
		FAttributeDebuff MonsterAttributeDebuff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		FMonsterEffectData MonsterEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* HitEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* BurnEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* FloodingEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* ShockEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* TransitionEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* AssembleEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* GroggyEffectComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackedInfo, Meta = (AllowPrivateAccess = true))
		FAttackedInfo AttackedInfo;
	//박찬영 UI
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* HpBarWidget;
	//
	UPROPERTY()
		class UMonsterAnimInstance* MonsterAnimInstance;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestMode, Meta = (AllowPrivateAccess = true))
		bool bTestMode;

	bool bIsAttacking;
	bool bIsAttacked;
	bool bIsGroggy;
	bool bIsDead;

#pragma region Sound
	//사운드 이벤트
	UPROPERTY(EditAnywhere, Category = "FMOD")
		class UFMODEvent* HitEvent;
	//사운드 
	SoundManager* HitSound;
	FTransform SoundTransform;
#pragma endregion Sound
private:
	//Function
	void CalcHp(float Damage);
	void CalcCurrentDebuffAttribute(EAttributeKeyword AttackedAttribute);
	float CalcBurnDamage(float Damage);

	bool CheckPlayerIsBehindMonster();
	void RotationToPlayerDirection();

	void InitEffect();
	void SetEffect();

	void Burn();
	void Flooding();
	void Shock();
	void DebuffTransition(EAttributeKeyword AttackedAttribute, float Damage);
	void Assemble();
	void Chain(EAttributeKeyword PlayerMainAttribute, float Damage);

	void SetDebuff(EAttributeKeyword AttackedAttribute, float Damage);

	void SetActive();
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	//Variable
	FVector AssembleLocation;
	FVector KnockBackDir;
	float KnockBackTime;
	AMonsterAIController* MonsterAIController;

	bool bIsBurn;
	bool bIsFlooding;
	bool bIsShock;
	bool bIsAssemble;
	bool bIsChain;
//Virtual Function
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void PostInitializeComponents() override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
