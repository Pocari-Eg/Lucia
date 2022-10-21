// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// �߰��ϴ� �κ�
#include "PlayerInstance/IreneAttackInstance.h"
#include "PlayerInstance/IreneSoundInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../StarryTail.h"
#include"../Object/SpiritPlate.h"
#include "PlayerCharacterDataStruct.h"
#include "Chaos/Vector.h"

//������
//#include "StopWatch.h"
//#include "Components/WidgetComponent.h"

#include "IreneCharacter.generated.h"

//Ingame ���� ��������Ʈ

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInGameBattleDelegate, int32, _FUNC, float, _CTIME);

UCLASS()
class STARRYTAIL_API AIreneCharacter : public ACharacter
{
	GENERATED_BODY()

public:

protected:

#pragma region GetClassOrObject
public:
	// �÷��̾� ��Ʈ�ѷ�
	UPROPERTY()
	APlayerController* WorldController;

	// ī�޶� �ϰ� ī�޶�
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Camera)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Camera)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Pet)
	USpringArmComponent* PetSpringArmComp;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Pet)
	USkeletalMeshComponent* PetMesh;
	
	UPROPERTY(BlueprintReadWrite)
	class UIreneAnimInstance* IreneAnim;
	UPROPERTY()
	class UIreneAttackInstance* IreneAttack;
	UPROPERTY(BluePrintReadOnly)
	class UIreneInputInstance* IreneInput;
	UPROPERTY(BluePrintReadOnly)
	class UIreneSoundInstance* IreneSound;

	// InGame ���� �������Ʈ
	UPROPERTY(EditAnyWhere)
	TSubclassOf<class UUserWidget> InGame_C;
	UPROPERTY(BlueprintReadWrite)
	class UUserWidget* makeIngameWidget;

	UPROPERTY(BlueprintAssignable)
	FInGameBattleDelegate FInGameBattle;

	// ���� �������Ʈ
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> IreneSpiritOrigin;
	UPROPERTY(EditAnywhere)
	class AIreneSpirit* IreneSpirit;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ShieldParticleSystemComponent;
	
	UPROPERTY()
	class USTGameInstance* STGameInstance;

	// ĳ���Ͱ� ����ϴ� ����, ��� ���� �ִ� ����ü
	UPROPERTY(EditAnywhere, BluePrintReadOnly)
	FPlayerCharacterDataStruct IreneData;
	UPROPERTY(BluePrintReadOnly)
	class UIreneUIManager* IreneUIManager;
	UPROPERTY()
	class UIreneFSM* IreneState;

	//ȸ�� ����ü
	UPROPERTY(EditAnywhere,Category=HpRecorvery)
	FPlayerRecoveryDataStruct HpRecoveryData;
	
	// ���� �Ž�
	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* Weapon;
	UPROPERTY()
	USkeletalMesh* WeaponMesh;

	UPROPERTY(EditAnywhere)
	TArray<UCurveVector*> CameraShakeCurve;
	UPROPERTY(EditAnywhere)
	TArray<UCurveFloat*> CameraLagCurve;
	UPROPERTY(EditAnywhere)
	UCurveVector* SkillCamera;
	
	UPROPERTY()
	TMap<AActor*, float>ActorAngleMap;

	bool bInputStop;
	bool bIsSpiritStance;
private:
	FTimerHandle FixedUpdateCameraShakeTimer;
	FTimerHandle FixedUpdateCameraLagTimer;

	// ī�޶� ����ũ�� ����� Ŀ��
	UPROPERTY()
	UCurveVector* UseShakeCurve;
	// ī�޶� ���� ����� Ŀ��
	UPROPERTY()
	UCurveFloat* UseLagCurve;
	
	//float CameraLagTime;
	//float LastLagTime;
#pragma endregion GetClassOrObject

	//��ž��ġ
	//AStopWatch* StopWatch;
	
#pragma region Setting
public:
	// Sets default values for this character's properties
	AIreneCharacter();

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TargetReset()const;
	
	UFUNCTION(BlueprintImplementableEvent)
	void WeaponVisible(bool Value);

	UFUNCTION(BlueprintImplementableEvent)
	void LevelRestartEvent();


#pragma endregion Setting
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region State
public:
	// ���� ��ȭ �� �α� ���
	void ChangeStateAndLog(class IState* NewState)const;
	UFUNCTION(BlueprintCallable)
	void ActionEndChangeMoveState(bool RunToSprint = false)const;	
#pragma endregion State
	
#pragma region Collision
public:
	// ����� ���� ã��
	void FindNearMonster()const;
	TTuple<FVector, FVector, FVector> SetCameraStartTargetPosition(const FVector BoxSize, const FVector StartPosition)const;
	TTuple<TArray<FHitResult>, FCollisionQueryParams, bool> StartPositionFindNearMonster(const FVector BoxSize, const FVector StartPosition, const FVector TargetPosition, const float LifeTime = 0.0f)const;

	void NearMonsterAnalysis(const TArray<FHitResult> MonsterList, const FCollisionQueryParams Params, const bool bResult, const float Far, const bool UltimateAttack = false)const;
	void SetAttackNearMonster(const FHitResult RayHit, float& NearPosition, const float FindNearTarget)const;

	void FollowTargetPosition();

	UFUNCTION(BluePrintCallable)
	AActor* TargetMonster(){return IreneAttack->SwordTargetMonster;}
	
	// ��ħ �浹 ó��
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(UPrimitiveComponent *MyComp, AActor *Other, UPrimitiveComponent *OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult &Hit) override;

	// �ǰ�
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
	void SetHP(float DamageAmount);
#pragma endregion Collision

#pragma region Battle
	public:
	UFUNCTION(BlueprintImplementableEvent)
	void HitStopEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void RadialBlurEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void CameraOutEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void CameraInEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void RaidBattleEvent();
	
	UFUNCTION(BlueprintImplementableEvent)
	void PerfectDodgeStart();
	UFUNCTION(BlueprintImplementableEvent)
	void PerfectDodgeTimeEnd();
	UFUNCTION(BlueprintImplementableEvent)
    void PerfectDodgeAttackEnd();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateTailEvent();
	
	UFUNCTION(BluePrintCallable, Category = "CameraRoation")
	float BattleCameraRotation(UPARAM(ref) float& Angle);

	void OnRadialBlur();

	bool bIsRadialBlurOn;

	void LastAttackCameraShake(const float DeltaTime);
	void SetUseShakeCurve(UCurveVector* Curve);
	//void DoCameraLagCurve(const float DeltaTime);
	void SetUseCameraLag(UCurveFloat* Curve);
	
	UPROPERTY(BluePrintReadWrite)
	bool CameraShakeOn;

	UPROPERTY(BluePrintReadWrite)
	bool IsTimeStopping;

	void PlayerKnockBack(FVector In_KnockBackDir, float In_KnockBackPower);
	FVector KnockBackDir;
	float KnockBackTimer;
	float KnockBackTime;
	float KnockBackPower;
	bool bIsKnockBack;

#pragma endregion Battle

#pragma region UIManager
	UFUNCTION(BlueprintImplementableEvent)
	void PlayFadeOutEvent();

	UFUNCTION(BluePrintCallable)
	void PlayFadeOutAnimation();

	UFUNCTION(BluePrintCallable)
	void PlayFadeInAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void InitComplete();

	void SetIreneDialog();

	UFUNCTION(BluePrintCallable)
	void SetBattleCamera();
	UFUNCTION(BluePrintCallable)
	void SetRaidBattleCamera();
	UFUNCTION(BluePrintCallable)
	void SetFirstLevel(bool isFirst);


	void SpawnPet(ASpiritPlate* Target);
	void VisiblePet();
#pragma endregion UIManager


//��ž��ġ 
	FPlayerCharacterDataStruct* GetDataStruct(){return &IreneData;}
	//void SetCameraLagTime(const float Value){CameraLagTime = Value;}
	//void SetLastLagTime(const float Value){LastLagTime = Value;}
};
