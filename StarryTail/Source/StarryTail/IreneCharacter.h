// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// 추가하는 부분
#include "PlayerCharacterDataStruct.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "IreneFSM.h"

//박찬영
#include "StopWatch.h"
#include "UI/IreneAttributeWidget.h"
#include "Components/WidgetComponent.h"
#include "UI/HPBarWidget.h"
#include "SoundManager.h"
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

private:
#pragma region GetClassOrObject
	// 플레이어 컨트롤러
	UPROPERTY(VisibleAnywhere)
	APlayerController* WorldController;

	// 점프증력 커브
	UPROPERTY(EditAnywhere)
	UCurveFloat* JumpGravityCurve;

	// 카메라 암과 카메라
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp;

	// 캐릭터가 사용하는 변수, 상수 값들 있는 구조체
	UPROPERTY(EditAnywhere)
	FPlayerCharacterDataStruct CharacterDataStruct;
	// 캐릭터 상태
	IreneFSM* CharacterState;

	// 무기 매쉬
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Weapon;

	// 애니메이션 인스턴스
	UPROPERTY()
	class UIreneAnimInstance* IreneAnim;

#pragma endregion GetClassOrObject

#pragma region InputData
	// 움직임에 사용하는 키 0: 정지, 1: 걷기, 2: 달리기, 3: 걷기 예약키, 4: 달리기 예약키
	UPROPERTY(EditAnywhere)
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

#pragma region AttackData
	// 타겟 몬스터 또는 오브젝트
	AActor* TargetMonster;

	//캐릭터 속성
	UPROPERTY(EditAnywhere)
	EAttributeKeyword Attribute;

	// 타켓 추적 유무
	bool bFollowTarget;
	// 보간을 위한 수 0 ~ 1
	float FollowTargetAlpha;
	// 보간을 위한 시작 위치
	FVector PlayerPosVec;
	// 보간을 위한 목표 위치
	FVector TargetPosVec;
#pragma endregion AttackData

#pragma region UI
	//속성 ui
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* AttributeWidget;
	//Hp Bar 위젯
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HpBarWidget;

	// 로그 출력용
	bool bShowLog;
#pragma endregion UI	

#pragma region Sound
	//사운드 이벤트
	UPROPERTY(EditAnywhere, Category = "FMOD")
		class UFMODEvent* AttackEvent;
	UPROPERTY(EditAnywhere, Category = "FMOD")
		class UFMODEvent* WalkEvent;

	//사운드 
	SoundManager* WalkSound;
	SoundManager* AttackSound;
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
	//속성 반환
	EAttributeKeyword GetAttribute();
	//공격력 반환
	float GetATK();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	// 메인키워드 속성변경
	void MainKeyword();

	// 대쉬
	void DodgeKeyword();

	// 마우스 커서 활성화
	void MouseCursorKeyword();
#pragma endregion Input

#pragma region State
	// 상태 변화 후 로그 출력
	void ChangeStateAndLog(State* newState);
	void ActionEndChangeMoveState();
#pragma endregion State

#pragma region Attack
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();
	void DoAttack();
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
	//현재 체력 비율 전환
	float GetHpRatio();


	//사운드 출력
	void FootStepSound();
#pragma endregion Park

//스탑워치 
	//void WatchContorl();
	//void WatchReset();
};
