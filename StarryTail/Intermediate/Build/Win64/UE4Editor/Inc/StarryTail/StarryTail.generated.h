// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STARRYTAIL_StarryTail_generated_h
#error "StarryTail.generated.h already included, missing '#pragma once' in StarryTail.h"
#endif
#define STARRYTAIL_StarryTail_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID StarryTail_Source_StarryTail_StarryTail_h


#define FOREACH_ENUM_WATCHSTATE(op) \
	op(WatchState::e_Reset) \
	op(WatchState::e_Pause) \
	op(WatchState::e_Play) 

enum class WatchState : uint8;
template<> STARRYTAIL_API UEnum* StaticEnum<WatchState>();

#define FOREACH_ENUM_EATTRIBUTEKEYWORD(op) \
	op(EAttributeKeyword::e_None) \
	op(EAttributeKeyword::e_Fire) \
	op(EAttributeKeyword::e_Water) \
	op(EAttributeKeyword::e_Thunder) 

enum class EAttributeKeyword : uint8;
template<> STARRYTAIL_API UEnum* StaticEnum<EAttributeKeyword>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
