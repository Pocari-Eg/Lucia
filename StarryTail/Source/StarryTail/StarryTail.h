// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
UENUM(BluePrintType)
enum class  EAttributeKeyword :uint8
{
	e_None = 0 UMETA(DisplayName = "NONE"),
	e_Fire   UMETA(DisplayName = "FIRE"),
	e_Water  UMETA(DisplayName = "WATER"),
	e_Thunder  UMETA(DisplayName = "THUNDER")
};

UENUM(BluePrintType)
enum class  WatchState :uint8 // Ÿ�̸��� ���¸� ��Ÿ���� ����ü
{
	e_Reset = 0 UMETA(DisplayName = "RESET"),
	e_Pause  UMETA(DisplayName = "PAUSE"),
	e_Play UMETA(DisplayName = "PLAY")

};