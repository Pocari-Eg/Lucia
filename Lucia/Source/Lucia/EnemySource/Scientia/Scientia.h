// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
#include "./Struct/FScientiaInfo.h"
#include "ScAnimInstance.h"
#include "Feather.h"
#include "Piece.h"
#include "Scientia.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FClawStartDelegate);
DECLARE_MULTICAST_DELEGATE(FClawPreStartDelegate);
DECLARE_MULTICAST_DELEGATE(FClawPreEndDelegate);
DECLARE_MULTICAST_DELEGATE(FClawFEndDelegate);
DECLARE_MULTICAST_DELEGATE(FClawBEndDelegate);
DECLARE_MULTICAST_DELEGATE(FTurnEndDelegate);
DECLARE_MULTICAST_DELEGATE(FChangeEndDelegate);
DECLARE_MULTICAST_DELEGATE(FDodgeEndDelegate);
DECLARE_MULTICAST_DELEGATE(FCrushedEndDelegate);
DECLARE_MULTICAST_DELEGATE(FDropEndDelegate);
DECLARE_MULTICAST_DELEGATE(FAddFeatherEndDelegate);
DECLARE_MULTICAST_DELEGATE(FRushStartDelegate);

DECLARE_MULTICAST_DELEGATE(FOnChangeFireBarrier);
DECLARE_MULTICAST_DELEGATE(FOnChangeWaterBarrier);
DECLARE_MULTICAST_DELEGATE(FOnChangeThunderBarrier);

DECLARE_MULTICAST_DELEGATE(FOnCrushBarrier);
UCLASS()
class LUCIA_API AScientia : public AMonster
{
	GENERATED_BODY()
public:
	AScientia();

	void InitScInfo();

	void Attack1();
	void Attack2();
	void Attack3();
	void Attack4();

	void PlayAttackedBAnimation();
	void PlayAttackedFAnimation();

	void Feather();
	void AddFeatherCount();
	void ResetFeatherCount();

	void ResetClawSuccessedCount();
	void PlayStuckAnim();
	void PlayFeatherPreAnim();
	void PlayClawPreAnim();

	void RushEnd();
	void Turn();

	void BattleIdle();
	void BattleWalk();
	void Change();
	void Dodge();
	void Crushed();
	void ChangeAttribute();

	bool ScAttributeIsPlayerAttributeCounter();
	bool PlayerAttributeIsScAttributeCounter();

	void CalcCurrentBarrier(float Value);
	bool IsBarrierCrushed();

	FString GetState();
	int GetBarrierCount();
	int GetFeatherCount();
	float GetHpPercent();

	float GetFireDefPercent();
	float GetWaterDefPercent();
	float GetThunderDefPercent();

	float GetAttack2Speed();
	float GetAttack3Speed();
	float GetAttack4Speed();
	float GetDodgeSpeed();
	float GetRushTime();
	int GetClawSuccessedCount();
	bool GetIsCanChange();
	bool GetIsRush();
	float GetRushTestRange() { return RushTestRange; }

	void SetState(FString string);
	void SetAttribute(EAttributeKeyword Attribute);

	FScientiaInfo GetScInfo();

	UFUNCTION(BlueprintImplementableEvent)
		void FirstCrushedEvent();
	UFUNCTION(BlueprintImplementableEvent)
		void SecondCrushedEvent();
	UFUNCTION(BlueprintImplementableEvent)
		void ThirdCrushedEvent();
	//Var
	FAddFeatherEndDelegate AddFeatherEnd;
	FAttackEndDelegate Attack1End;
	FClawPreStartDelegate ClawPreStart;
	FClawPreEndDelegate ClawPreEnd;
	FClawFEndDelegate ClawFEnd;
	FClawBEndDelegate ClawBEnd;
	FRushStartDelegate RushStart;
	FClawStartDelegate ClawStart;
	FTurnEndDelegate TurnEnd;
	FChangeEndDelegate ChangeEnd;
	FDodgeEndDelegate DodgeEnd;
	FCrushedEndDelegate CrushedEnd;
	FDropEndDelegate DropEnd;

	//UI
	UFUNCTION(BlueprintCallable)
	void SetMaxBarrierValue();
	FOnChangeFireBarrier OnFireBarrierChanged;
	FOnChangeWaterBarrier OnWaterBarrierChanged;
	FOnChangeThunderBarrier OnThunderBarrierChanged;

	FOnCrushBarrier OnCrushBarrier;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFeather> FeatherBP;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class APiece> PieceBP;
private:
	void SpawnPiece();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScientiaInfo, Meta = (AllowPrivateAccess = true))
		FScientiaInfo ScInfo;



	UScAnimInstance* ScAnimInstance;

	bool IsSetAttribute;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ScientiaInfo, Meta = (AllowPrivateAccess = true))
		bool bIsClaw;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ScientiaInfo, Meta = (AllowPrivateAccess = true))
		bool bIsRush;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ScientiaInfo, Meta = (AllowPrivateAccess = true))
		bool bIsDrop;
	bool bIsPlayerClawHit;
	bool bIsPlayerRushHit;
	bool bIsCanChange;

	float AttributeSettingTimer;
	float ChangeTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Test, Meta = (AllowPrivateAccess = true))
		float RushTestRange;
	float MaxFireDef;
	float MaxWaterDef;
	float MaxThunderDef;
public:
	// Called every frame
	void Tick(float DeltaTime) override;

	
protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	void PossessedBy(AController* NewController) override;

	void PostInitializeComponents() override;
private:
	void InitMonsterInfo() override;
	void InitCollision() override;
	void InitMesh() override;
	void InitAnime() override;
};
