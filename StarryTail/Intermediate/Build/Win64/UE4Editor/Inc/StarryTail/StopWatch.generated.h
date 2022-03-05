// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STARRYTAIL_StopWatch_generated_h
#error "StopWatch.generated.h already included, missing '#pragma once' in StopWatch.h"
#endif
#define STARRYTAIL_StopWatch_generated_h

#define StarryTail_Source_StarryTail_StopWatch_h_16_SPARSE_DATA
#define StarryTail_Source_StarryTail_StopWatch_h_16_RPC_WRAPPERS
#define StarryTail_Source_StarryTail_StopWatch_h_16_RPC_WRAPPERS_NO_PURE_DECLS
#define StarryTail_Source_StarryTail_StopWatch_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAStopWatch(); \
	friend struct Z_Construct_UClass_AStopWatch_Statics; \
public: \
	DECLARE_CLASS(AStopWatch, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AStopWatch)


#define StarryTail_Source_StarryTail_StopWatch_h_16_INCLASS \
private: \
	static void StaticRegisterNativesAStopWatch(); \
	friend struct Z_Construct_UClass_AStopWatch_Statics; \
public: \
	DECLARE_CLASS(AStopWatch, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AStopWatch)


#define StarryTail_Source_StarryTail_StopWatch_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AStopWatch(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AStopWatch) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStopWatch); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStopWatch); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AStopWatch(AStopWatch&&); \
	NO_API AStopWatch(const AStopWatch&); \
public:


#define StarryTail_Source_StarryTail_StopWatch_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AStopWatch(AStopWatch&&); \
	NO_API AStopWatch(const AStopWatch&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStopWatch); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStopWatch); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AStopWatch)


#define StarryTail_Source_StarryTail_StopWatch_h_16_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__TimerWidgetClass() { return STRUCT_OFFSET(AStopWatch, TimerWidgetClass); } \
	FORCEINLINE static uint32 __PPO__TimerWidget() { return STRUCT_OFFSET(AStopWatch, TimerWidget); }


#define StarryTail_Source_StarryTail_StopWatch_h_13_PROLOG
#define StarryTail_Source_StarryTail_StopWatch_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_StopWatch_h_16_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_StopWatch_h_16_SPARSE_DATA \
	StarryTail_Source_StarryTail_StopWatch_h_16_RPC_WRAPPERS \
	StarryTail_Source_StarryTail_StopWatch_h_16_INCLASS \
	StarryTail_Source_StarryTail_StopWatch_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define StarryTail_Source_StarryTail_StopWatch_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_StopWatch_h_16_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_StopWatch_h_16_SPARSE_DATA \
	StarryTail_Source_StarryTail_StopWatch_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_StopWatch_h_16_INCLASS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_StopWatch_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STARRYTAIL_API UClass* StaticClass<class AStopWatch>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID StarryTail_Source_StarryTail_StopWatch_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
