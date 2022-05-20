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
	BattleIdle,
	Run_Loop,
	Run_End,
	Sprint_Loop,
	Sprint_End,
	Dodge_F_Start,
	Dodge_F_End,
	Dodge_W_Start,
	Dodge_W_End,
	Dodge_T_Start,
	Dodge_T_End,
	Jump_Start,
	Jump_Loop,
	Jump_End,
	B_Attack_1_F,
	B_Attack_2_F,
	B_Attack_3_F,
	B_Attack_1_W,
	B_Attack_2_W,
	B_Attack_3_W,
	B_Attack_1_T,
	B_Attack_2_T,
	B_Attack_3_T,
	Skill_F_Start,
	Skill_F_End,
	Skill_W_Start,
	Skill_W_End,
	Skill_T_Start,
	Skill_T_End,
	Charge_1,
	Charge_2,
	Form_Change,
	Hit_1,
	Hit_2,
	Death
};

UENUM(BluePrintType)
enum class  EEnemyRank :uint8
{
	e_Common = 0 UMETA(DisplayName = "Common"),
	e_Unique   UMETA(DisplayName = "Unique"),
	e_Raid  UMETA(DisplayName = "Raid"),

};