// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StarryTail.h"
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
#include "UI/CharacterAttributeWidget.h"
#include "Components/WidgetComponent.h"

#include "IreneCharacter.generated.h"



UCLASS()
class STARRYTAIL_API AIreneCharacter : public ACharacter
{
	GENERATED_BODY()

public:	

protected:

private:
	// 카메라 암과 카메라
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;

	// 움직임에 사용하는 키 0: 정지, 1: 걷기, 2: 달리기
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


	// 기본공격용 핸들
	FTimerHandle NormalAttackWaitHandle;
	// 기본종료용 핸들
	FTimerHandle NormalAttackEndWaitHandle;
	// 현재 공격 횟수를 의미하지만 나중에는 애니메이션으로 바꿀 예정
	TQueue<uint8> AttackQueue;
	// 큐에 값을 넣을 수 있는 시간
	bool IsEnqueueTime;
	// 공격 횟수
	uint8 AttackCount;
	uint8 AttackCountAnim;

	// 키워드 출력용
	uint8 MainKeywordType;
	uint8 SubKeywordType;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Weapon;

	// 박찬영 ***************************************
	//스탑워치
	AStopWatch* StopWatch;
	//캐릭터 속성
	UPROPERTY(EditAnywhere)
	EAttributeKeyword Type;
	//속성 ui
	UPROPERTY(VisibleAnywhere,Category=UI)
	class UWidgetComponent* AttributeWidget;

	
public:
	// Sets default values for this character's properties
	AIreneCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	uint8 GetAttackCountAnim() { return AttackCountAnim; }

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

	// 카메라 회전 관련 함수
	void Turn(float Rate);
	void LookUp(float Rate);

	// 마우스 좌클릭
	void LeftButton();
	void StartNormalAttackAnim();

	// 메인키워드, 보조키워드, 액션키워드
	void MainKeyword();
	void SubKeyword();
	void ActionKeyword1();
	void ActionKeyword2();
	void ActionKeyword3();

	// 대쉬
	void DashKeyword();

	// 상태 변화 후 로그 출력
	void ChangeStateAndLog(State* newState);

	//박찬영 ============
	//스탑워치 
	void WatchContorl();
	void WatchReset();
	//속성 변환
	void AttributeChange();
};
