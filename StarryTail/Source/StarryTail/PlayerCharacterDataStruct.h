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
	
	// 스프링암과 플레이어 간 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FollowCameraZPosition = 400;

	// 카메라 수평필드 오브 뷰
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FieldofView = 90;

public:	
	// 인게임에서 수정 가능한 값들로 수정 후 컴파일 하면 좋음

	// 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP;

	// 이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 1.0f;

	// 이동속도 1당 축으로 0.1이동
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashDistance = 3000.0f;
};
