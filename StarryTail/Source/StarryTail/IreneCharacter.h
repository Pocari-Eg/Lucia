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
	// 플레이어 컨트롤러
	UPROPERTY(VisibleAnywhere)
	APlayerController* WorldController;

	// 카메라 암과 카메라
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp;

	// 충돌체
	//UPROPERTY(VisibleAnywhere)
	//UBoxComponent* FindMonsterCollsion;
	//UPROPERTY(VisibleAnywhere)
	//UBoxComponent* FindTargetCollsion;

	// 움직임에 사용하는 키 0: 정지, 1: 걷기, 2: 달리기, 3: 걷기 예약키, 4: 달리기 예약키
	UPROPERTY(EditAnywhere)
	TArray<uint8> MoveKey;
	
	// 캐릭터가 사용하는 변수, 상수 값들 있는 구조체
	UPROPERTY(EditAnywhere)
	FPlayerCharacterDataStruct CharacterDataStruct;

	// 캐릭터 상태
	IreneFSM* CharacterState;

	// 구르기 같은 자동이동 방향
	FVector MoveAutoDirection;
	// 자동이동용 핸들
	FTimerHandle MoveAutoWaitHandle;
	// 추락중 구르기 시 빠르게 떨어지는 지 확인
	bool IsFallingRoll;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Weapon;

	UPROPERTY()
	class UIreneAnimInstance* IreneAnim;

	FTimerHandle AttackWaitHandle;

	// 타겟 몬스터 또는 오브젝트
	AActor* TargetMonster;

	//캐릭터 속성
	UPROPERTY(EditAnywhere)
	EAttributeKeyword Attribute;
	//속성 ui
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* AttributeWidget;


	//스탑워치
	//AStopWatch* StopWatch;

	// 로그 출력용
	bool bShowLog;

public:
	// Sets default values for this character's properties
	AIreneCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//속성 반환
	EAttributeKeyword GetAttribute();
	//공격력 반환
	float GetATK();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// 캐릭터 이동 관련 함수
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

	void ActionEndChangeMoveState();

	// 카메라 회전 관련 함수
	void Turn(float Rate);
	void LookUp(float Rate);

	// 마우스 버튼 및 휠
	void LeftButton(float Rate);
	void RightButton();
	void MouseWheel(float Rate);

	// 메인키워드, 보조키워드, 액션키워드
	void MainKeyword();
	void ActionKeyword1();
	void ActionKeyword2();
	void ActionKeyword3();

	// 대쉬
	void DodgeKeyword();

	// 마우스 커서 활성화
	void MouseCursorKeyword();

	// 상태 변화 후 로그 출력
	void ChangeStateAndLog(StateEnum newState);
	
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();

	// 가까운 몬스터 찾기
	void FindNearMonster();

	// 곂침 충돌 처리
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	// 피격
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	//속성 변환
	void AttributeChange();

//스탑워치 
	//void WatchContorl();
	//void WatchReset();


};
