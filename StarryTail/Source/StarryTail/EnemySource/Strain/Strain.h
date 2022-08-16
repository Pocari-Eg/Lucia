// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "StrainAIController.h"
#include"StrainAnimInstance.h"
#include"ST_MagicAttack.h"
#include "Strain.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API AStrain : public AMonster
{
	GENERATED_BODY()

//Function 
public:
	AStrain();

	UStrainAnimInstance* GetStrainAnimInstance() const;

	void Walk();
	void Attack();
	void Skill_Setting();
	void Skill_Set();
	void PlayRunAnim();
	void Skill_Attack();
	void Skill_AttackEnd();

	bool IntersectionCheck();
protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	void PossessedBy(AController* NewController) override;

	void PostInitializeComponents() override;
public:
	// Called every frame
	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	float GetFlyDistance();
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
		class UStrainAnimInstance* StrainAnimInstance;
public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Run_Distance; 
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Run_Time;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Attacked_Time;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float M_MaxFlyDistance;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* Magic_CircleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "ture"))
		UParticleSystem* Magic_Circle;
	TSubclassOf<AST_MagicAttack> MagicAttackClass;
	AST_MagicAttack* MagicAttack;
	bool IsSkillSet;
	bool IsSkillAttack;

	bool IsCloseOtherAttack;

	float IntersectionTimer;
	float SkillSetTimer;
	float SkillAttackTimer;

	FVector AttackPosition;

	float TotalFlyDistance;

	float M_Fly_Distance;


};
