// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STARRYTAIL_IreneAnimInstance_generated_h
#error "IreneAnimInstance.generated.h already included, missing '#pragma once' in IreneAnimInstance.h"
#endif
#define STARRYTAIL_IreneAnimInstance_generated_h

#define StarryTail_Source_StarryTail_IreneAnimInstance_h_20_SPARSE_DATA
#define StarryTail_Source_StarryTail_IreneAnimInstance_h_20_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execAnimNotify_AttackEndCheck); \
	DECLARE_FUNCTION(execAnimNotify_NextAttackCheck); \
	DECLARE_FUNCTION(execAnimNotify_AttackHitCheck);


#define StarryTail_Source_StarryTail_IreneAnimInstance_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execAnimNotify_AttackEndCheck); \
	DECLARE_FUNCTION(execAnimNotify_NextAttackCheck); \
	DECLARE_FUNCTION(execAnimNotify_AttackHitCheck);


#define StarryTail_Source_StarryTail_IreneAnimInstance_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUIreneAnimInstance(); \
	friend struct Z_Construct_UClass_UIreneAnimInstance_Statics; \
public: \
	DECLARE_CLASS(UIreneAnimInstance, UAnimInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(UIreneAnimInstance)


#define StarryTail_Source_StarryTail_IreneAnimInstance_h_20_INCLASS \
private: \
	static void StaticRegisterNativesUIreneAnimInstance(); \
	friend struct Z_Construct_UClass_UIreneAnimInstance_Statics; \
public: \
	DECLARE_CLASS(UIreneAnimInstance, UAnimInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(UIreneAnimInstance)


#define StarryTail_Source_StarryTail_IreneAnimInstance_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UIreneAnimInstance(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UIreneAnimInstance) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UIreneAnimInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UIreneAnimInstance); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UIreneAnimInstance(UIreneAnimInstance&&); \
	NO_API UIreneAnimInstance(const UIreneAnimInstance&); \
public:


#define StarryTail_Source_StarryTail_IreneAnimInstance_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UIreneAnimInstance(UIreneAnimInstance&&); \
	NO_API UIreneAnimInstance(const UIreneAnimInstance&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UIreneAnimInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UIreneAnimInstance); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UIreneAnimInstance)


#define StarryTail_Source_StarryTail_IreneAnimInstance_h_20_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CurrentPawnSpeed() { return STRUCT_OFFSET(UIreneAnimInstance, CurrentPawnSpeed); } \
	FORCEINLINE static uint32 __PPO__IsInAir() { return STRUCT_OFFSET(UIreneAnimInstance, IsInAir); } \
	FORCEINLINE static uint32 __PPO__AttackMontage() { return STRUCT_OFFSET(UIreneAnimInstance, AttackMontage); }


#define StarryTail_Source_StarryTail_IreneAnimInstance_h_17_PROLOG
#define StarryTail_Source_StarryTail_IreneAnimInstance_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_IreneAnimInstance_h_20_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_IreneAnimInstance_h_20_SPARSE_DATA \
	StarryTail_Source_StarryTail_IreneAnimInstance_h_20_RPC_WRAPPERS \
	StarryTail_Source_StarryTail_IreneAnimInstance_h_20_INCLASS \
	StarryTail_Source_StarryTail_IreneAnimInstance_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define StarryTail_Source_StarryTail_IreneAnimInstance_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_IreneAnimInstance_h_20_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_IreneAnimInstance_h_20_SPARSE_DATA \
	StarryTail_Source_StarryTail_IreneAnimInstance_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_IreneAnimInstance_h_20_INCLASS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_IreneAnimInstance_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STARRYTAIL_API UClass* StaticClass<class UIreneAnimInstance>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID StarryTail_Source_StarryTail_IreneAnimInstance_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
