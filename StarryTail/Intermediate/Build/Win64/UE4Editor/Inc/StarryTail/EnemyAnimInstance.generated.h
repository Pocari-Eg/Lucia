// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STARRYTAIL_EnemyAnimInstance_generated_h
#error "EnemyAnimInstance.generated.h already included, missing '#pragma once' in EnemyAnimInstance.h"
#endif
#define STARRYTAIL_EnemyAnimInstance_generated_h

#define StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_SPARSE_DATA
#define StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_RPC_WRAPPERS
#define StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_RPC_WRAPPERS_NO_PURE_DECLS
#define StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEnemyAnimInstance(); \
	friend struct Z_Construct_UClass_UEnemyAnimInstance_Statics; \
public: \
	DECLARE_CLASS(UEnemyAnimInstance, UAnimInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(UEnemyAnimInstance)


#define StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_INCLASS \
private: \
	static void StaticRegisterNativesUEnemyAnimInstance(); \
	friend struct Z_Construct_UClass_UEnemyAnimInstance_Statics; \
public: \
	DECLARE_CLASS(UEnemyAnimInstance, UAnimInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(UEnemyAnimInstance)


#define StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UEnemyAnimInstance(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UEnemyAnimInstance) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEnemyAnimInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEnemyAnimInstance); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UEnemyAnimInstance(UEnemyAnimInstance&&); \
	NO_API UEnemyAnimInstance(const UEnemyAnimInstance&); \
public:


#define StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UEnemyAnimInstance(UEnemyAnimInstance&&); \
	NO_API UEnemyAnimInstance(const UEnemyAnimInstance&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEnemyAnimInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEnemyAnimInstance); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UEnemyAnimInstance)


#define StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CurrentPawnSpeed() { return STRUCT_OFFSET(UEnemyAnimInstance, CurrentPawnSpeed); } \
	FORCEINLINE static uint32 __PPO__bCanRangedAttack() { return STRUCT_OFFSET(UEnemyAnimInstance, bCanRangedAttack); } \
	FORCEINLINE static uint32 __PPO__RangedAttackCount() { return STRUCT_OFFSET(UEnemyAnimInstance, RangedAttackCount); } \
	FORCEINLINE static uint32 __PPO__bCanMeleeAttack() { return STRUCT_OFFSET(UEnemyAnimInstance, bCanMeleeAttack); } \
	FORCEINLINE static uint32 __PPO__RangedAttackMontage() { return STRUCT_OFFSET(UEnemyAnimInstance, RangedAttackMontage); } \
	FORCEINLINE static uint32 __PPO__MeleeAttackMontage() { return STRUCT_OFFSET(UEnemyAnimInstance, MeleeAttackMontage); } \
	FORCEINLINE static uint32 __PPO__RushAttackMontage() { return STRUCT_OFFSET(UEnemyAnimInstance, RushAttackMontage); }


#define StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_13_PROLOG
#define StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_SPARSE_DATA \
	StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_RPC_WRAPPERS \
	StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_INCLASS \
	StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_SPARSE_DATA \
	StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_INCLASS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STARRYTAIL_API UClass* StaticClass<class UEnemyAnimInstance>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID StarryTail_Source_StarryTail_EnemySource_EnemyAnimInstance_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
