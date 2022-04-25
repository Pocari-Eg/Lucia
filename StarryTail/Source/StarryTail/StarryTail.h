// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(StarryTail, Log, All);
#define STARRYLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define STARRYLOG_S(Verbosity) UE_LOG(StarryTail, Verbosity, TEXT("%s"), *STARRYLOG_CALLINFO)
#define STARRYLOG(Verbosity, Format, ...) UE_LOG(StarryTail, Verbosity, TEXT("%s %s"), *STARRYLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define STARRYCHECK(Expr, ...) {if(!(Expr)) {STARRYLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}

UENUM(BluePrintType)
enum class  EAttributeKeyword :uint8
{
	e_None = 0 UMETA(DisplayName = "NONE"),
	e_Fire   UMETA(DisplayName = "FIRE"),
	e_Water  UMETA(DisplayName = "WATER"),
	e_Thunder  UMETA(DisplayName = "THUNDER")
};

UENUM(BluePrintType)
enum class  WatchState :uint8 // 타이머의 상태를 나타내는 열거체
{
	e_Reset = 0 UMETA(DisplayName = "RESET"),
	e_Pause  UMETA(DisplayName = "PAUSE"),
	e_Play UMETA(DisplayName = "PLAY")

};

UENUM(BluePrintType)
enum class  EAttackedDirection :uint8
{
	Left = 0 UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Up  UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down")
};
UENUM(BluePrintType)
enum class EAttackedPower : uint8
{
	Halved = 0 UMETA(DisplayName = "Halved"),
	Normal UMETA(DisplayName = "Normal"),
	Critical UMETA(DisplayName = "Critical")
};

// 13개
UENUM(BlueprintType)
enum class EStateEnum : uint8
{
	Idle = 0,
	Death,
	Dodge,
	Hit,
	BasicAttack,
	ActionAttack,
	BattleIdle,
	Run,
	Sprint,
	SprintEnd,
	Jump,
	Fall,
	SprintJump
};