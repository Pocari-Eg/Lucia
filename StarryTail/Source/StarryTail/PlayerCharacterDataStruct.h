// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IreneFSM.h"

#include "PlayerCharacterDataStruct.generated.h"


USTRUCT(Atomic, BlueprintType)
struct FPlayerCharacterDataStruct
{
	GENERATED_BODY()

public:
	// �ڵ忡�� �ǵ鿩 ����ϴ� ����� ���� �� ������ ������ �ʿ�
	// ��� ����(�ΰ��� ����) �ʿ��ϸ� IreneCharacter.cpp�� Tick�Լ��� �ּ�ó��("//") �صа��� Ȱ��ȭ ��Ű�� ������ �� �÷����ϸ� ��
	
	// �������ϰ� �÷��̾� �� �⺻ �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FollowCameraZPosition = 550;

	// ī�޶� �����ʵ� ���� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FieldofView = 75;

public:	
	// �ΰ��ӿ��� ���� ������ ����� ���� �� ������ �ϸ� ����
	
	// ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInvincibility;

	//���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ATK;

	// ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP;
	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MP;

	// �̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 1.0f;

	// ���콺 �� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseWheelSpeed = 10.0f;

	// ���콺 ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EDPI = 1.0f;

public:
	// ���� ���� ������
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool IsAttacking;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool IsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 MaxCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRange;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRadius;
};
