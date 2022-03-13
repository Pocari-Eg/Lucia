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

#include "IreneCharacter.generated.h"

UCLASS()
class STARRYTAIL_API AIreneCharacter : public ACharacter
{
	GENERATED_BODY()

public:	

protected:

private:
	// ī�޶� �ϰ� ī�޶�
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp;

	// �����ӿ� ����ϴ� Ű 0: ����, 1: �ȱ�, 2: �޸���
	UPROPERTY(EditAnywhere)
	TArray<uint8> MoveKey;
	
	// ĳ���Ͱ� ����ϴ� ����, ��� ���� �ִ� ����ü
	UPROPERTY(EditAnywhere)
	FPlayerCharacterDataStruct CharacterDataStruct;

	// ĳ���� ����
	IreneFSM* CharacterState;

	// ������ ���� �ڵ��̵� ����
	FVector MoveAutoDirection;
	// �ڵ��̵��� �ڵ�
	FTimerHandle MoveAutoWaitHandle;
	// �߶��� ������ �� ������ �������� �� Ȯ��
	bool IsFallingRoll;

	// Ű���� ��¿�
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

	// ������ ***************************************
//��ž��ġ
	//AStopWatch* StopWatch;
	//ĳ���� �Ӽ�
	UPROPERTY(EditAnywhere)
	EAttributeKeyword Attribute;
	//�Ӽ� ui
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

	///������ ==================
	//�Ӽ� ��ȯ
	EAttributeKeyword GetAttribute();
	//���ݷ� ��ȯ
	float GetATK();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// ĳ���� �̵� ���� �Լ�
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

	// ī�޶� ȸ�� ���� �Լ�
	void Turn(float Rate);
	void LookUp(float Rate);

	// ���콺 ��Ŭ��
	void LeftButton(float Rate);

	// ����Ű����, ����Ű����, �׼�Ű����
	void MainKeyword();
	void SubKeyword();
	void ActionKeyword1();
	void ActionKeyword2();
	void ActionKeyword3();

	// �뽬
	void DashKeyword();

	// ���� ��ȭ �� �α� ���
	void ChangeStateAndLog(State* newState);
	
	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();

	//������ ============
//��ž��ġ 
	//void WatchContorl();
	//void WatchReset();
	//�Ӽ� ��ȯ
	void AttributeChange();
};
