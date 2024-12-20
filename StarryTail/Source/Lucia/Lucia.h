// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "Math.h"

DECLARE_LOG_CATEGORY_EXTERN(Lucia, Log, All);
#define STARRYLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define STARRYLOG_S(Verbosity) UE_LOG(Lucia, Verbosity, TEXT("%s"), *STARRYLOG_CALLINFO)
#define STARRYLOG(Verbosity, Format, ...) UE_LOG(Lucia, Verbosity, TEXT("%s %s"), *STARRYLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

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

UENUM(BlueprintType)
enum class EStateEnum : uint8
{
	Idle = 0,
	BattleIdle,
	Run_Loop,
	Run_End,
	Sprint_Loop,
	Sprint_End,
	Dodge_Start,
	Dodge_End,
	Jump_Start,
	Jump_Loop,
	Jump_End,
	B_Attack_1,
	B_Attack_2,
	B_Attack_3,
	Sword_Skill_1,
	Sword_Skill_2,
	Spirit_Skill,
	Ultimate_Attack,
	Form_Change,
	Hit_1,
	Hit_2,
	KnockBack,
	Death
};
UENUM(BlueprintType)
enum class EHeliosStateEnum : uint8
{
	Idle = 0,
	RunLoop,
	DodgeStart,
	Shield,
	FormChange,
	FormChangeNormal,
	Stun,
	Death
};

UENUM(BluePrintType)
enum class  EEnemyRank :uint8
{
	e_Common = 0 UMETA(DisplayName = "Common"),
	e_Unique   UMETA(DisplayName = "Unique"),
	e_Raid  UMETA(DisplayName = "Raid"),

};

UENUM(BluePrintType)
enum class  EDialogState :uint8
{
	e_Disable = 0 UMETA(DisplayName = "Disable"),
	e_Set   UMETA(DisplayName = "Set"),
	e_Playing   UMETA(DisplayName = "Playing"),
	e_Complete   UMETA(DisplayName = "Complete")
};

UENUM(BluePrintType)
enum class  EShieldType :uint8
{
	General = 0 UMETA(DisplayName = "General"),
	Special UMETA(DisplayName = "Special"),
};

UENUM(BluePrintType)
enum class  EMonsterState :uint8
{
	Normal = 0 UMETA(DisplayName = "Normal"),
	Battle UMETA(DisplayName = "Battle"),
	Support  UMETA(DisplayName = "Support"),
};

UENUM(BluePrintType)
enum class  ESoundStyle :uint8
{
	e_Bgm = 0 UMETA(DisplayName = "BGM"),
	e_Amb UMETA(DisplayName = "AMB"),
	e_Sfx  UMETA(DisplayName = "SFX")
};

UENUM(BluePrintType)
enum class  EState :uint8
{
	e_MainHall,
	e_Library,
	e_Orgranism
};