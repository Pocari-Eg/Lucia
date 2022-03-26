// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Struct/FNormalMonsterInfo.h"
#include "./Struct/FAttributeDefence.h"
#include "../StarryTail.h"
#include "MonsterAnimInstance.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

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
	
	UMonsterAnimInstance* GetMonsterAnimInstance() const;

	void OnTrueDamage(float Damage);
	void OnDamage(EAttributeKeyword PlayerMainAttribute, float Damage);

	TArray<FOverlapResult> DetectMonster();

	FDeathDelegate Death;
protected:
	virtual void InitMonsterInfo() {};
	virtual void InitCollision() {};
	virtual void InitMesh() {};
	virtual void InitAnime() {};

	//Function
	void InitDebuffInfo();

	void CalcAttributeDefType();
	void CalcAttributeDebuff(EAttributeKeyword PlayerMainAttribute, float Damage);
	void CalcDamage(EAttributeKeyword PlayerMainAttribute, float Damage);

	//Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		FNormalMonsterInfo MonsterInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		FAttributeDefence AttributeDef;
	UPROPERTY(VisibleAnywhere, Category = Collision, Meta = (AllowPrivateAccess = true))
		class UCapsuleComponent* Collision;
	//애니메이션 리소스 생길 시 변경
	UPROPERTY()
		class UMonsterAnimInstance* MonsterAnimInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestMode, Meta = (AllowPrivateAccess = true))
		bool bTestMode;

	bool bIsAttacking;
	bool bIsAttacked;
	bool bIsGroggy;
	bool bIsDead;
private:

	//Function
	void CalcHp(float Damage);

	void Burn();
	void Flooding();
	void Shock();
	void Explosion();
	void Assemble(EAttributeKeyword PlayerMainAttribute, float Damage);
	void Chain(EAttributeKeyword PlayerMainAttribute, float Damage);

	//Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		float DetectMonsterRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Debuff, Meta = (AllowPrivateAccess = true))
		int BurnStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float BurnCycle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float BurnDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float BurnTime;
	float BurnCycleTimer;
	float BurnTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Debuff, Meta = (AllowPrivateAccess = true))
		int FloodingStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float FloodingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float FloodingDebuffSpeedReductionValue;
	float FloodingTimer;
	float DefaultMoveSpeed;
	float DefaultBattleWalkMoveSpeed;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float ExplosionRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float ExplosionDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float AssembleRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float AssembleTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float AssembleSpeed;
	float AssembleTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float ChainRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAccess = true))
		float ChainTime;
	float ChainTimer;

	FVector AssembleLocation;

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
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
