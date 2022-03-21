// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Struct/FNormalMonsterInfo.h"
#include "./Struct/FAttributeDefence.h"
#include "../StarryTail.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class STARRYTAIL_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

	//Function
	float GetMeleeAttackRange();
	float GetTraceRange();
protected:
	//Virtual Function
	UFUNCTION()
		virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted) {};
	UFUNCTION()
		virtual void OnAttackedMontageEnded(UAnimMontage* Montage, bool bInterrupted) {};
	UFUNCTION()
		virtual void OnAttacked(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {};

	virtual void InitMonsterInfo() {};
	virtual void InitCollision() {};
	virtual void InitMesh() {};
	virtual void InitAnime() {};

	//Function
	void CalcAttributeDefType();

	//Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		FNormalMonsterInfo MonsterInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, Meta = (AllowPrivateAccess = true))
		FAttributeDefence AttributeDef;
	UPROPERTY(VisibleAnywhere, Category = Collision, Meta = (AllowPrivateAccess = true))
		class UCapsuleComponent* Collision;
	//�ִϸ��̼� ���ҽ� ���� �� ����
	UPROPERTY()
		class UEnemyAnimInstance* MonsterAnimInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestMode, Meta = (AllowPrivateAccess = true))
		bool bTestMode;

	bool bIsAttacking;
	bool bIsAttacked;
//Virtual Function
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
