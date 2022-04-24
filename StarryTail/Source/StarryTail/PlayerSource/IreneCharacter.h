// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// 추가하는 부분
#include "PlayerCharacterDataStruct.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "IreneAnimInstance.h"

//박찬영
//#include "StopWatch.h"
#include "Components/WidgetComponent.h"

#include "../SoundManager.h"
#include "IreneCharacter.generated.h"

//속성 변경 델리데이트
DECLARE_MULTICAST_DELEGATE(FOnAttributeChangeDelegate);

DECLARE_MULTICAST_DELEGATE(FOnHpChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMpChangeDelegate);
UCLASS()
class STARRYTAIL_API AIreneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//속성변환 델리게이트
	FOnAttributeChangeDelegate FOnAttributeChange;
protected:

private:
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

	// 캐릭터가 사용하는 변수, 상수 값들 있는 구조체
	UPROPERTY(EditAnywhere)
	FPlayerCharacterDataStruct CharacterDataStruct;
	UPROPERTY()
	UIreneFSM* CharacterState;
	
	// 무기 매쉬
	UPROPERTY()
	USkeletalMeshComponent* Weapon;

	// 애니메이션 인스턴스
	UPROPERTY()
	UIreneAnimInstance* IreneAnim;

	UPROPERTY(EditAnywhere)
	TArray<UCurveFloat*> CameraShakeCurve;

#pragma endregion GetClassOrObject

#pragma region InputData
	// 움직임에 사용하는 키 0: 정지, 1: 걷기, 2: 달리기, 3: 걷기 예약키, 4: 달리기 예약키
	UPROPERTY()
	TArray<uint8> MoveKey;

	// 구르기 같은 자동이동 방향
	FVector MoveAutoDirection;
	// 자동이동용 핸들
	FTimerHandle MoveAutoWaitHandle;
	// 추락중 구르기 시 빠르게 떨어지는 지 확인
	bool IsFallingRoll;

	// 공격 연속 입력 지연
	FTimerHandle AttackWaitHandle;

	// 차징 중인지
	bool IsCharging;
	// 차징 시간
	float ChargingTime;

	// 점프 중력 그래프용 시작 타이밍
	bool bStartJump;
	// 점프 중력 그래프용 시간
	float JumpingTime;
#pragma endregion MoveData

#pragma region Recorvery
public:
	UPROPERTY(EditAnywhere,Category=HpRecorvery)
	FPlayerRecoveryDataStruct HpRecoveryData;
	UPROPERTY(EditAnywhere, Category = HpRecorvery)
	int RemainingRecovry;
private:
	int CurRecoverWaitTime;
	int CurRecoverTime;
	bool bIsCurHpChanged;

	FTimerHandle HpRecorveryTimerHandle;
	FTimerHandle HpRecorveryWaitTimerHandle;
#pragma endregion

#pragma region AttackData
	UPROPERTY()
	// 타겟 몬스터 또는 오브젝트
	AActor* TargetMonster;

	//캐릭터 속성
	UPROPERTY(EditAnywhere)
	EAttributeKeyword Attribute;
	
	UPROPERTY()
	UDataTable* AttackDataTable;

	// 타켓 추적 유무
	bool bFollowTarget;
	// 보간을 위한 수 0 ~ 1
	float FollowTargetAlpha;
	// 보간을 위한 시작 위치
	FVector PlayerPosVec;
	// 보간을 위한 목표 위치
	FVector TargetPosVec;

	// 카메라 쉐이크 시간
	float CameraShakeTime;
	// 타켓 추적 유무
	bool bFollowCameraTarget;
	// 보간을 위한 수 0 ~ 1
	float FollowTargetCameraAlpha;
	// 보간을 위한 시작 위치
	FRotator CameraRot;
	// 보간을 위한 목표 위치
	FRotator TargetCameraRot;
	
	bool bUseLeftButton;
	bool bUseRightButton;
	bool bUseMP;
	float UseMP;
#pragma endregion AttackData

#pragma region UI
	
	// 로그 출력용
	bool bShowLog;

public:
	FOnHpChangeDelegate OnHpChanged;
	FOnMpChangeDelegate OnMpChanged;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = UI)
	TSubclassOf<class UPlayerHudWidget> PlayerHudClass;   // 위젯 클래스 
	UPROPERTY()
	class UPlayerHudWidget* PlayerHud; // 위젯	
#pragma endregion UI	

#pragma region Sound
	//사운드 이벤트
public:
	UPROPERTY(EditAnyWhere,Category="SOUND_VOLUME",meta=(ClampMin="0", ClampMax = "1"))
	float WalkSoundVolume;
private:
	class UFMODEvent* AttackEvent;
	class UFMODEvent* WalkEvent;

	//사운드 
	SoundManager* WalkSound;
	SoundManager* AttackSound;

	float AttackSoundParameter;
#pragma endregion Sound

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
	UFUNCTION(BlueprintCallable)
	//속성 반환
	EAttributeKeyword GetAttribute();

	//공격력 반환
	float GetATK();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called when our Actor is destroyed during Gameplay.
	virtual void Destroyed() override;

	//Call Game mode class to Restart Player Character.
	void CallRestartPlayer();

private:

	// 캐릭터 이동 관련 함수
#pragma region MoveInput
	void MoveForward();
	void MoveRight();
	void MoveStop();
	void MoveAuto();

	void StartJump();
	void StopJump();

	void MovePressedW();
	void MovePressedA();
	void MovePressedS();
	void MovePressedD();
	void MoveDoubleClickW();
	void MoveDoubleClickA();
	void MoveDoubleClickS();
	void MoveDoubleClickD();
	void MoveReleasedW();
	void MoveReleasedA();
	void MoveReleasedS();
	void MoveReleasedD();
#pragma endregion MoveInput

	// 입력 관련 함수
#pragma region Input
	// 카메라 회전 관련 함수
	void Turn(float Rate);
	void LookUp(float Rate);

	// 마우스 버튼 및 휠
	void LeftButton(float Rate);
	void RightButtonPressed();
	void RightButtonReleased();
	void MouseWheel(float Rate);
	void RightButton(float Rate);

	// 메인키워드 속성변경
	void MainKeyword();

	// 대쉬
	void DodgeKeyword();

	// 마우스 커서 활성화
	void MouseCursorKeyword();
#pragma endregion Input

#pragma region State
	// 상태 변화 후 로그 출력
	void ChangeStateAndLog(IState* NewState);
	void ActionEndChangeMoveState();
	FName GetAnimName();
#pragma endregion State

#pragma region Attack
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();
	void AttackStopCheck();
	void DoAttack();

	FAttackDataTable* GetNameAtDataTable(const FName Value) const { if (Value != FName("")) return (AttackDataTable->FindRow<FAttackDataTable>(Value, "")); return nullptr; }

#pragma endregion Attack
	
#pragma region Collision
	// 가까운 몬스터 찾기
	void FindNearMonster();

	// 겹침 충돌 처리
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	// 피격
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
#pragma endregion Collision

#pragma region Park
	public:
	//현재 체력 비율 전환
	float GetHpRatio();
	//현재 마나 비율 전환
	float GetMpRatio();
	//사운드 출력
	void FootStepSound();
#pragma endregion Park


#pragma region HitFeel
	public:
	UFUNCTION(BlueprintImplementableEvent)
	void HitStopEvent();

	UPROPERTY(BluePrintReadWrite)
	bool CameraShakeOn;

	UPROPERTY(BluePrintReadWrite)
	bool GoTargetOn;

	UPROPERTY(BluePrintReadWrite)
	bool IsTimeStopping;
#pragma endregion HitFeel

#pragma region RecoveryFunc
	//회복 대기 관련
	void HPRecoveryWaitStart();
	void HPRecoveryWaiting();
	void HPRecoveryWaitCancel();

	//회복 관련
	void HPRecoveringStart();
	void HPRecovering();
	void HpRecoveringCancel();

	//Hp 확인
	bool IsHpFull();

public:
	//Hp RecoveryBar 
	float GetHpRecoveryRatio();
#pragma endregion
//스탑워치 
	//void WatchControl();
	//void WatchReset();
};
