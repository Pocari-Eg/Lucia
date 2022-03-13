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

UCLASS()
class STARRYTAIL_API AIreneCharacter : public ACharacter
{
	GENERATED_BODY()

public:	

protected:

private:
	// 카메라 암과 카메라
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
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

	// 키워드 출력용
	uint8 MainKeywordType;
	uint8 SubKeywordType;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;


	UPROPERTY()
	class UIreneAnimInstance* IreneAnim;

	FTimerHandle AttackWaitHandle;

	// 박찬영 ***************************************
//스탑워치
	//AStopWatch* StopWatch;
	//캐릭터 속성
	UPROPERTY(EditAnywhere)
	EAttributeKeyword Attribute;
	//속성 ui
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* AttributeWidget;

public:
	// Sets default values for this character's properties
	AIreneCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	///박찬영 ==================
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

	// 카메라 회전 관련 함수
	void Turn(float Rate);
	void LookUp(float Rate);

	// 마우스 좌클릭
	void LeftButton(float Rate);

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
	
	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();

	//박찬영 ============
//스탑워치 
	//void WatchContorl();
	//void WatchReset();
	//속성 변환
	void AttributeChange();
};
