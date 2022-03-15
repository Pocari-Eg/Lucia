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
	// 코드에서 건들여 줘야하는 값들로 수정 후 컴파일 무조건 필요
	// 즉시 수정(인게임 수정) 필요하면 IreneCharacter.cpp의 Tick함수에 주석처리("//") 해둔것을 활성화 시키고 컴파일 후 플레이하면 됨
	
	// 스프링암과 플레이어 간 기본 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FollowCameraZPosition = 200;

	// 카메라 수평필드 오브 뷰
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FieldofView = 105;

public:	
	// 인게임에서 수정 가능한 값들로 수정 후 컴파일 하면 좋음
	
	// 무적상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInvincibility;

	//공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ATK;

	// 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP;

	// 이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 1.0f;

	// 점프 거리 반대 힘
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpDistance = 27000.0f;

	// 마우스 휠 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseWheelSpeed = 10.0f;
};
