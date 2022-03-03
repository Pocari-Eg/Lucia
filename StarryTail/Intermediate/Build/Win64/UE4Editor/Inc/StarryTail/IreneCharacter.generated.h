// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STARRYTAIL_IreneCharacter_generated_h
#error "IreneCharacter.generated.h already included, missing '#pragma once' in IreneCharacter.h"
#endif
#define STARRYTAIL_IreneCharacter_generated_h

#define StarryTail_Source_StarryTail_IreneCharacter_h_21_SPARSE_DATA
#define StarryTail_Source_StarryTail_IreneCharacter_h_21_RPC_WRAPPERS
#define StarryTail_Source_StarryTail_IreneCharacter_h_21_RPC_WRAPPERS_NO_PURE_DECLS
#define StarryTail_Source_StarryTail_IreneCharacter_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAIreneCharacter(); \
	friend struct Z_Construct_UClass_AIreneCharacter_Statics; \
public: \
	DECLARE_CLASS(AIreneCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AIreneCharacter)


#define StarryTail_Source_StarryTail_IreneCharacter_h_21_INCLASS \
private: \
	static void StaticRegisterNativesAIreneCharacter(); \
	friend struct Z_Construct_UClass_AIreneCharacter_Statics; \
public: \
	DECLARE_CLASS(AIreneCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AIreneCharacter)


#define StarryTail_Source_StarryTail_IreneCharacter_h_21_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AIreneCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AIreneCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AIreneCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AIreneCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AIreneCharacter(AIreneCharacter&&); \
	NO_API AIreneCharacter(const AIreneCharacter&); \
public:


#define StarryTail_Source_StarryTail_IreneCharacter_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AIreneCharacter(AIreneCharacter&&); \
	NO_API AIreneCharacter(const AIreneCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AIreneCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AIreneCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AIreneCharacter)


#define StarryTail_Source_StarryTail_IreneCharacter_h_21_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__SpringArmComp() { return STRUCT_OFFSET(AIreneCharacter, SpringArmComp); } \
	FORCEINLINE static uint32 __PPO__CameraComp() { return STRUCT_OFFSET(AIreneCharacter, CameraComp); } \
	FORCEINLINE static uint32 __PPO__MoveKey() { return STRUCT_OFFSET(AIreneCharacter, MoveKey); } \
	FORCEINLINE static uint32 __PPO__CharacterDataStruct() { return STRUCT_OFFSET(AIreneCharacter, CharacterDataStruct); }


#define StarryTail_Source_StarryTail_IreneCharacter_h_18_PROLOG
#define StarryTail_Source_StarryTail_IreneCharacter_h_21_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_IreneCharacter_h_21_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_IreneCharacter_h_21_SPARSE_DATA \
	StarryTail_Source_StarryTail_IreneCharacter_h_21_RPC_WRAPPERS \
	StarryTail_Source_StarryTail_IreneCharacter_h_21_INCLASS \
	StarryTail_Source_StarryTail_IreneCharacter_h_21_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define StarryTail_Source_StarryTail_IreneCharacter_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_IreneCharacter_h_21_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_IreneCharacter_h_21_SPARSE_DATA \
	StarryTail_Source_StarryTail_IreneCharacter_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_IreneCharacter_h_21_INCLASS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_IreneCharacter_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STARRYTAIL_API UClass* StaticClass<class AIreneCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID StarryTail_Source_StarryTail_IreneCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
