// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../IreneCharacter.h"
#include "IreneSpirit.generated.h"

UCLASS()
class STARRYTAIL_API AIreneSpirit : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class AIreneCharacter* Irene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Weapon;
	UPROPERTY()
	USkeletalMesh* WeaponMesh;
	
	UPROPERTY(BlueprintReadWrite)
	class UIreneSpiritAnimInstance* IreneSpiritAnim;
private:
	// 소환 이후 캐릭터 보이는 딜레이
	FTimerHandle MeshVisibilityWaitHandle;
	// 소환 이후 캐릭터 보이는 딜레이 쿨타임
	float MeshVisibilityCoolTime;

	// 정령 삭제
	FTimerHandle DestroyWaitHandle;

	// 공격 단계
	int AttackCount;
public:
	AIreneSpirit();

	void AttackCheck();
	void DestroySpiritTimer(float Time);
	void DestroySpirit();
	
	UFUNCTION(BlueprintCallable)
	int GetAttackCount()const{return AttackCount;}
	void SetAttackCount(const int Value){AttackCount = Value;}

	UFUNCTION(BlueprintCallable)
	void SetDestroy()const{Irene->IreneSpirit = nullptr;}
private:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
