// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// 추가하는 부분
#include "PlayerInstance/IreneAttackInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../StarryTail.h"
#include "PlayerCharacterDataStruct.h"
#include "Chaos/Vector.h"

//박찬영
//#include "StopWatch.h"
//#include "Components/WidgetComponent.h"

#include "IreneCharacter.generated.h"

//속성 변경 델리데이트
DECLARE_MULTICAST_DELEGATE(FOnSwordAttributeChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnQuillAttributeChangeDelegate);

UCLASS()
class STARRYTAIL_API AIreneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//속성변환 델리게이트
	FOnSwordAttributeChangeDelegate FOnSwordAttributeChange;
	FOnQuillAttributeChangeDelegate FOnQuillAttributeChange;

protected:

#pragma region GetClassOrObject
public:
	// 플레이어 컨트롤러
	UPROPERTY()
	APlayerController* WorldController;

	// 카메라 암과 카메라
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Camera)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Camera)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ShieldComp;
	
	UPROPERTY(BlueprintReadWrite)
	class UIreneAnimInstance* IreneAnim;
	UPROPERTY()
	class UIreneAttackInstance* IreneAttack;
	UPROPERTY(BluePrintReadOnly)
	class UIreneInputInstance* IreneInput;
	UPROPERTY()
	class USTGameInstance* STGameInstance;

	// 캐릭터가 사용하는 변수, 상수 값들 있는 구조체
	UPROPERTY(EditAnywhere, BluePrintReadOnly)
	FPlayerCharacterDataStruct IreneData;
	UPROPERTY(BluePrintReadOnly)
	class UIreneUIManager* IreneUIManager;
	UPROPERTY()
	class UIreneFSM* IreneState;

	//회복 구조체
	UPROPERTY(EditAnywhere,Category=HpRecorvery)
	FPlayerRecoveryDataStruct HpRecoveryData;
	
	// 무기 매쉬
	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* Weapon;
	UPROPERTY()
	USkeletalMesh* WeaponMesh;

	UPROPERTY(EditAnywhere)
	TArray<UCurveVector*> CameraShakeCurve;
	UPROPERTY(EditAnywhere)
	TArray<UCurveFloat*> CameraLagCurve;
	
	UPROPERTY()
	TMap<AActor*, float>ActorAngleMap;
private:
	FTimerHandle FixedUpdateCameraShakeTimer;
	FTimerHandle FixedUpdateCameraLagTimer;

	// 카메라 쉐이크에 사용할 커브
	UPROPERTY()
	UCurveVector* UseShakeCurve;
	// 카메라 렉에 사용할 커브
	UPROPERTY()
	UCurveFloat* UseLagCurve;

	//float CameraLagTime;
	//float LastLagTime;
#pragma endregion GetClassOrObject

	//스탑워치
	//AStopWatch* StopWatch;
	
#pragma region Setting
public:
	// Sets default values for this character's properties
	AIreneCharacter();

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TargetReset()const;
	
	UFUNCTION(BlueprintCallable)
	EAttributeKeyword GetQuillAttribute() {return IreneAttack->GetQuillAttribute();}
	
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
	// 상태 변화 후 로그 출력
	void ChangeStateAndLog(class IState* NewState)const;
	UFUNCTION(BlueprintCallable)
	void ActionEndChangeMoveState(bool RunToSprint = false)const;	
#pragma endregion State
	
#pragma region Collision
public:
	// 가까운 몬스터 찾기
	void FindNearMonster()const;
	TTuple<FVector, FVector, FVector> SetCameraStartTargetPosition(const FVector BoxSize, const FVector StartPosition)const;
	TTuple<TArray<FHitResult>, FCollisionQueryParams, bool> StartPositionFindNearMonster(const FVector BoxSize, const FVector StartPosition, const FVector TargetPosition, const float LifeTime = 5.0f)const;

	void NearMonsterAnalysis(const TArray<FHitResult> MonsterList, const FCollisionQueryParams Params, const bool bResult, const float Far)const;
	void SetAttackNearMonster(const FHitResult RayHit, float& NearPosition, const float FindNearTarget)const;

	void FollowTargetPosition();
	
	// 겹침 충돌 처리
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(UPrimitiveComponent *MyComp, AActor *Other, UPrimitiveComponent *OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult &Hit) override;

	// 피격
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
	void SetHP(float DamageAmount);
#pragma endregion Collision

#pragma region HitFeel
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
#pragma endregion HitFeel

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
#pragma endregion UIManager
//스탑워치 
	//void WatchControl();
	//void WatchReset();
	FPlayerCharacterDataStruct* GetDataStruct(){return &IreneData;}
	//void SetCameraLagTime(const float Value){CameraLagTime = Value;}
	//void SetLastLagTime(const float Value){LastLagTime = Value;}
};
