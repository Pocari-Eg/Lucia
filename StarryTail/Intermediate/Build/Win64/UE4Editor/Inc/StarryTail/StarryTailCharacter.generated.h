// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STARRYTAIL_StarryTailCharacter_generated_h
#error "StarryTailCharacter.generated.h already included, missing '#pragma once' in StarryTailCharacter.h"
#endif
#define STARRYTAIL_StarryTailCharacter_generated_h

#define StarryTail_Source_StarryTail_StarryTailCharacter_h_12_SPARSE_DATA
#define StarryTail_Source_StarryTail_StarryTailCharacter_h_12_RPC_WRAPPERS
#define StarryTail_Source_StarryTail_StarryTailCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define StarryTail_Source_StarryTail_StarryTailCharacter_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAStarryTailCharacter(); \
	friend struct Z_Construct_UClass_AStarryTailCharacter_Statics; \
public: \
	DECLARE_CLASS(AStarryTailCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AStarryTailCharacter)


#define StarryTail_Source_StarryTail_StarryTailCharacter_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAStarryTailCharacter(); \
	friend struct Z_Construct_UClass_AStarryTailCharacter_Statics; \
public: \
	DECLARE_CLASS(AStarryTailCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AStarryTailCharacter)


#define StarryTail_Source_StarryTail_StarryTailCharacter_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AStarryTailCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AStarryTailCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStarryTailCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStarryTailCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AStarryTailCharacter(AStarryTailCharacter&&); \
	NO_API AStarryTailCharacter(const AStarryTailCharacter&); \
public:


#define StarryTail_Source_StarryTail_StarryTailCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AStarryTailCharacter(AStarryTailCharacter&&); \
	NO_API AStarryTailCharacter(const AStarryTailCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStarryTailCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStarryTailCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AStarryTailCharacter)


#define StarryTail_Source_StarryTail_StarryTailCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(AStarryTailCharacter, CameraBoom); } \
	FORCEINLINE static uint32 __PPO__FollowCamera() { return STRUCT_OFFSET(AStarryTailCharacter, FollowCamera); }


#define StarryTail_Source_StarryTail_StarryTailCharacter_h_9_PROLOG
#define StarryTail_Source_StarryTail_StarryTailCharacter_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_StarryTailCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_StarryTailCharacter_h_12_SPARSE_DATA \
	StarryTail_Source_StarryTail_StarryTailCharacter_h_12_RPC_WRAPPERS \
	StarryTail_Source_StarryTail_StarryTailCharacter_h_12_INCLASS \
	StarryTail_Source_StarryTail_StarryTailCharacter_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define StarryTail_Source_StarryTail_StarryTailCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_StarryTailCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_StarryTailCharacter_h_12_SPARSE_DATA \
	StarryTail_Source_StarryTail_StarryTailCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_StarryTailCharacter_h_12_INCLASS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_StarryTailCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STARRYTAIL_API UClass* StaticClass<class AStarryTailCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID StarryTail_Source_StarryTail_StarryTailCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
