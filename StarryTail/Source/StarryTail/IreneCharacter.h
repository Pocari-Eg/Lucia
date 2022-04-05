// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// �߰��ϴ� �κ�
#include "PlayerCharacterDataStruct.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "IreneFSM.h"

//������
#include "StopWatch.h"
#include "UI/IreneAttributeWidget.h"
#include "Components/WidgetComponent.h"
#include "UI/HPBarWidget.h"
#include "SoundManager.h"
#include "IreneCharacter.generated.h"

//�Ӽ� ���� ��������Ʈ
DECLARE_MULTICAST_DELEGATE(FOnAttributeChangeDelegate);

UCLASS()
class STARRYTAIL_API AIreneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//�Ӽ���ȯ ��������Ʈ
	FOnAttributeChangeDelegate FOnAttributeChange;
protected:

private:
#pragma region GetClassOrObject
	// �÷��̾� ��Ʈ�ѷ�
	UPROPERTY(VisibleAnywhere)
	APlayerController* WorldController;

	// �������� Ŀ��
	UPROPERTY(EditAnywhere)
	UCurveFloat* JumpGravityCurve;

	// ī�޶� �ϰ� ī�޶�
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp;

	// ĳ���Ͱ� ����ϴ� ����, ��� ���� �ִ� ����ü
	UPROPERTY(EditAnywhere)
	FPlayerCharacterDataStruct CharacterDataStruct;
	// ĳ���� ����
	IreneFSM* CharacterState;

	// ���� �Ž�
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Weapon;

	// �ִϸ��̼� �ν��Ͻ�
	UPROPERTY()
	class UIreneAnimInstance* IreneAnim;

#pragma endregion GetClassOrObject

#pragma region InputData
	// �����ӿ� ����ϴ� Ű 0: ����, 1: �ȱ�, 2: �޸���, 3: �ȱ� ����Ű, 4: �޸��� ����Ű
	UPROPERTY(EditAnywhere)
	TArray<uint8> MoveKey;

	// ������ ���� �ڵ��̵� ����
	FVector MoveAutoDirection;
	// �ڵ��̵��� �ڵ�
	FTimerHandle MoveAutoWaitHandle;
	// �߶��� ������ �� ������ �������� �� Ȯ��
	bool IsFallingRoll;

	// ���� ���� �Է� ����
	FTimerHandle AttackWaitHandle;

	// ��¡ ������
	bool IsCharging;
	// ��¡ �ð�
	float ChargingTime;

	// ���� �߷� �׷����� ���� Ÿ�̹�
	bool bStartJump;
	// ���� �߷� �׷����� �ð�
	float JumpingTime;
#pragma endregion MoveData

#pragma region AttackData
	// Ÿ�� ���� �Ǵ� ������Ʈ
	AActor* TargetMonster;

	//ĳ���� �Ӽ�
	UPROPERTY(EditAnywhere)
	EAttributeKeyword Attribute;

	// Ÿ�� ���� ����
	bool bFollowTarget;
	// ������ ���� �� 0 ~ 1
	float FollowTargetAlpha;
	// ������ ���� ���� ��ġ
	FVector PlayerPosVec;
	// ������ ���� ��ǥ ��ġ
	FVector TargetPosVec;
#pragma endregion AttackData

#pragma region UI
	//�Ӽ� ui
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* AttributeWidget;
	//Hp Bar ����
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HpBarWidget;

	// �α� ��¿�
	bool bShowLog;
#pragma endregion UI	

#pragma region Sound
	//���� �̺�Ʈ
	UPROPERTY(EditAnywhere, Category = "FMOD")
		class UFMODEvent* AttackEvent;
	UPROPERTY(EditAnywhere, Category = "FMOD")
		class UFMODEvent* WalkEvent;

	//���� 
	SoundManager* WalkSound;
	SoundManager* AttackSound;
#pragma endregion Sound

	//��ž��ġ
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
	//�Ӽ� ��ȯ
	EAttributeKeyword GetAttribute();
	//���ݷ� ��ȯ
	float GetATK();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// ĳ���� �̵� ���� �Լ�
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

	// �Է� ���� �Լ�
#pragma region Input
	// ī�޶� ȸ�� ���� �Լ�
	void Turn(float Rate);
	void LookUp(float Rate);

	// ���콺 ��ư �� ��
	void LeftButton(float Rate);
	void RightButtonPressed();
	void RightButtonReleased();
	void MouseWheel(float Rate);

	// ����Ű���� �Ӽ�����
	void MainKeyword();

	// �뽬
	void DodgeKeyword();

	// ���콺 Ŀ�� Ȱ��ȭ
	void MouseCursorKeyword();
#pragma endregion Input

#pragma region State
	// ���� ��ȭ �� �α� ���
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
	// ����� ���� ã��
	void FindNearMonster();

	// ��ħ �浹 ó��
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	// �ǰ�
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
#pragma endregion Collision

#pragma region Park
	//���� ü�� ���� ��ȯ
	float GetHpRatio();


	//���� ���
	void FootStepSound();
#pragma endregion Park

//��ž��ġ 
	//void WatchContorl();
	//void WatchReset();
};
