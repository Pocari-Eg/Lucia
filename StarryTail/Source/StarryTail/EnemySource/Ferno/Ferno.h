// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "FernoAIController.h"
#include"FernoAnimInstance.h"
#include "Meteor.h"
#include "Ferno.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API AFerno : public AMonster
{
	GENERATED_BODY()

//Function 
public:
	AFerno();

	UFernoAnimInstance* GetFernoAnimInstance() const;

	void Walk();
	void RangeAttack();
protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	void PossessedBy(AController* NewController) override;

	void PostInitializeComponents() override;
public:
	// Called every frame
	void Tick(float DeltaTime) override;
private:
	void InitMonsterInfo() override;
	void InitCollision() override;
	void InitMesh() override;
	void InitAnime() override;


//Variable
	//Variable
	UPROPERTY()
		class UFernoAnimInstance* FernoAnimInstance;
public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Run_Distance; 
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Run_Time;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Attacked_Time;

		// 카메라 위치에서의 총구 오프셋
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meteor)
			UBoxComponent* MeteorFirePos;
		// 스폰시킬 프로젝타일 클래스
		UPROPERTY(EditDefaultsOnly, Category = Meteor)
			TSubclassOf<class AMeteor> ProjectileClass;
		UPROPERTY(EditAnywhere, Category = Meteor)
			float Meteor_Speed;
};
