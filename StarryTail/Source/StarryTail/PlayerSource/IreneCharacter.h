// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// 추가하는 부분
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../StarryTail.h"
#include "PlayerCharacterDataStruct.h"

//박찬영
//#include "StopWatch.h"
//#include "Components/WidgetComponent.h"

#include "IreneCharacter.generated.h"

//속성 변경 델리데이트
DECLARE_MULTICAST_DELEGATE(FOnAttributeChangeDelegate);


UCLASS()
class STARRYTAIL_API AIreneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//속성변환 델리게이트
	FOnAttributeChangeDelegate FOnAttributeChange;
protected:

public:
#pragma region GetClassOrObject
	// 플레이어 컨트롤러
	UPROPERTY()
	APlayerController* WorldController;

	// 점프증력 커브
	UPROPERTY()
	UCurveFloat* JumpGravityCurve;

	// 카메라 암과 카메라
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp;

	UPROPERTY()
	class UIreneAnimInstance* IreneAnim;
	UPROPERTY()
	class UIreneAttackInstance* IreneAttack;
	UPROPERTY()
	class UIreneInputInstance* IreneInput;

	// 캐릭터가 사용하는 변수, 상수 값들 있는 구조체
	UPROPERTY(EditAnywhere)
	FPlayerCharacterDataStruct IreneData;
	UPROPERTY()
	class UIreneUIManager* IreneUIManager;
	UPROPERTY()
	class UIreneFSM* IreneState;

	//회복 구조체
	UPROPERTY(EditAnywhere,Category=HpRecorvery)
	FPlayerRecoveryDataStruct HpRecoveryData;

	UPROPERTY(EditAnywhere,Category=FireRecorvery)
	FPlayerFireRecoveryDataStruct FireRecoveryData;
	UPROPERTY(EditAnywhere,Category=WaterRecorvery)
	FPlayerWaterRecoveryDataStruct WaterRecoveryData;
	UPROPERTY(EditAnywhere,Category=ElectricRecorvery)
	FPlayerElectricRecoveryDataStruct ElectricRecoveryData;
	
	// 무기 매쉬
	UPROPERTY()
	USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnywhere)
	TArray<UCurveFloat*> CameraShakeCurve;
#pragma endregion GetClassOrObject

	//스탑워치
	//AStopWatch* StopWatch;
public:
#pragma region Setting
	// Sets default values for this character's properties
	AIreneCharacter();

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion Setting

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called when our Actor is destroyed during Gameplay.
	virtual void Destroyed() override;

	//Call Game mode class to Restart Player Character.
	void CallRestartPlayer();

public:

#pragma region State
	// 상태 변화 후 로그 출력
	void ChangeStateAndLog(class IState* NewState);
	void ActionEndChangeMoveState();
	FName GetAnimName();
#pragma endregion State
	
#pragma region Collision
	// 가까운 몬스터 찾기
	void FindNearMonster();

	// 겹침 충돌 처리
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(UPrimitiveComponent *MyComp, AActor *Other, UPrimitiveComponent *OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult &Hit) override;

	// 피격
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
#pragma endregion Collision

#pragma region HitFeel
	public:
	UFUNCTION(BlueprintImplementableEvent)
	void HitStopEvent();

	UPROPERTY(BluePrintReadWrite)
	bool CameraShakeOn;

	UPROPERTY(BluePrintReadWrite)
	bool IsTimeStopping;
#pragma endregion HitFeel
//스탑워치 
	//void WatchControl();
	//void WatchReset();
	FPlayerCharacterDataStruct* GetDataStruct(){return &IreneData;}
};
