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
	
	// �������ϰ� �÷��̾� �� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FollowCameraZPosition = 400;

	// ī�޶� �����ʵ� ���� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FieldofView = 90;

public:	
	// �ΰ��ӿ��� ���� ������ ����� ���� �� ������ �ϸ� ����

	// ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP;

	// �̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 1.0f;

	// �̵��ӵ� 1�� ������ 0.1�̵�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashDistance = 3000.0f;
};
