// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include"../MonsterProjectile.h"
#include "ST_MagicAttack.generated.h"

UCLASS()
class STARRYTAIL_API AST_MagicAttack : public AMonsterProjectile
{
	GENERATED_BODY()


//var
private:
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Meta = (AllowPrivateAccess = true))
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Meta = (AllowPrivateAccess = true))
	USphereComponent* AttackCollision;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Meta = (AllowPrivateAccess = true))
	USphereComponent* IntersectionCollision;
	UPROPERTY(EditAnywhere,BluePrintReadWrite, Meta = (AllowPrivateAccess = true))
	UDecalComponent* Circum;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Meta = (AllowPrivateAccess = true))
	UDecalComponent* Area;

	UMaterial* IndicatorMat;
	UMaterialInstanceDynamic* AreaInstance;
	UMaterialInstanceDynamic* CircumInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* SkillEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "ture"))
		UParticleSystem* SkillEffect;

	float Damage;
//func
public:	
	// Sets default values for this actor's properties
	AST_MagicAttack();

	void SetMagicAttack(float Radius,float DamageVal);
	void PlayIndicator(float Val);
	void EndIndicator();
	void SetActiveAttack();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//충돌 체크
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
