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
	// �÷��̾� ��Ʈ�ѷ�
	UPROPERTY(VisibleAnywhere)
	APlayerController* WorldController;

	// ī�޶� �ϰ� ī�޶�
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp;

	// �浹ü
	//UPROPERTY(VisibleAnywhere)
	//UBoxComponent* FindMonsterCollsion;
	//UPROPERTY(VisibleAnywhere)
	//UBoxComponent* FindTargetCollsion;

	// �����ӿ� ����ϴ� Ű 0: ����, 1: �ȱ�, 2: �޸���, 3: �ȱ� ����Ű, 4: �޸��� ����Ű
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

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Weapon;

	UPROPERTY()
	class UIreneAnimInstance* IreneAnim;

	FTimerHandle AttackWaitHandle;

	// Ÿ�� ���� �Ǵ� ������Ʈ
	AActor* TargetMonster;

	//ĳ���� �Ӽ�
	UPROPERTY(EditAnywhere)
	EAttributeKeyword Attribute;
	//�Ӽ� ui
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* AttributeWidget;


	//��ž��ġ
	//AStopWatch* StopWatch;

	// �α� ��¿�
	bool bShowLog;

public:
	// Sets default values for this character's properties
	AIreneCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


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

	void ActionEndChangeMoveState();

	// ī�޶� ȸ�� ���� �Լ�
	void Turn(float Rate);
	void LookUp(float Rate);

	// ���콺 ��ư �� ��
	void LeftButton(float Rate);
	void RightButton();
	void MouseWheel(float Rate);

	// ����Ű����, ����Ű����, �׼�Ű����
	void MainKeyword();
	void ActionKeyword1();
	void ActionKeyword2();
	void ActionKeyword3();

	// �뽬
	void DodgeKeyword();

	// ���콺 Ŀ�� Ȱ��ȭ
	void MouseCursorKeyword();

	// ���� ��ȭ �� �α� ���
	void ChangeStateAndLog(StateEnum newState);
	
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();

	// ����� ���� ã��
	void FindNearMonster();

	// ��ħ �浹 ó��
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	// �ǰ�
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	//�Ӽ� ��ȯ
	void AttributeChange();

//��ž��ġ 
	//void WatchContorl();
	//void WatchReset();


};
