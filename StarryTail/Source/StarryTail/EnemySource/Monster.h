// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Struct/FNormalMonsterInfo.h"
#include "./Struct/FAttributeDefence.h"
#include "./Struct/FAttributeDebuff.h"
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
	TArray<EAttributeKeyword> GetMainAttributeDef() const;
	
	UMonsterAnimInstance* GetMonsterAnimInstance() const;

	void OnTrueDamage(float Damage);
	void OnDamage(EAttributeKeyword PlayerMainAttribute, float Damage);

	void AddDebuffStack(EAttributeKeyword Attribute);

	TArray<FOverlapResult> DetectMonster();

	FAttackEndDelegate AttackEnd;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debuff, Meta = (AllowPrivateAcess = true))
		FAttributeDebuff MonsterAttributeDebuff;
	//������ UI
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
private:
	//Function
	void CalcHp(float Damage);
	void CalcCurrentDebuffAttribute(EAttributeKeyword AttackedAttribute);
	void CalcBurnDamage();

	bool CheckPlayerIsBehindMonster();
	void RotationToPlayerDirection();

	void Burn();
	void Flooding();
	void Shock();
	void DebuffTransition(EAttributeKeyword AttackedAttribute, float Damage);
	void Assemble();
	void Chain(EAttributeKeyword PlayerMainAttribute, float Damage);

	void SetDebuff(EAttributeKeyword AttackedAttribute, float Damage);

	void SetActive();
	//Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		float DetectMonsterRange;

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

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
