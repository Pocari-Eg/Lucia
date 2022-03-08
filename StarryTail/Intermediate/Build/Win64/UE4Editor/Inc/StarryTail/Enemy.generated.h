// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UAnimMontage;
#ifdef STARRYTAIL_Enemy_generated_h
#error "Enemy.generated.h already included, missing '#pragma once' in Enemy.h"
#endif
#define STARRYTAIL_Enemy_generated_h

#define StarryTail_Source_StarryTail_Enemy_h_14_SPARSE_DATA
#define StarryTail_Source_StarryTail_Enemy_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnAttackMontageEnded);


#define StarryTail_Source_StarryTail_Enemy_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnAttackMontageEnded);


#define StarryTail_Source_StarryTail_Enemy_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemy(); \
	friend struct Z_Construct_UClass_AEnemy_Statics; \
public: \
	DECLARE_CLASS(AEnemy, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AEnemy)


#define StarryTail_Source_StarryTail_Enemy_h_14_INCLASS \
private: \
	static void StaticRegisterNativesAEnemy(); \
	friend struct Z_Construct_UClass_AEnemy_Statics; \
public: \
	DECLARE_CLASS(AEnemy, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AEnemy)


#define StarryTail_Source_StarryTail_Enemy_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AEnemy(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AEnemy) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemy); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemy); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemy(AEnemy&&); \
	NO_API AEnemy(const AEnemy&); \
public:


#define StarryTail_Source_StarryTail_Enemy_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemy(AEnemy&&); \
	NO_API AEnemy(const AEnemy&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemy); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemy); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemy)


#define StarryTail_Source_StarryTail_Enemy_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__bIsAttacking() { return STRUCT_OFFSET(AEnemy, bIsAttacking); } \
	FORCEINLINE static uint32 __PPO__EnemyAnimInstance() { return STRUCT_OFFSET(AEnemy, EnemyAnimInstance); }


#define StarryTail_Source_StarryTail_Enemy_h_11_PROLOG
#define StarryTail_Source_StarryTail_Enemy_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_Enemy_h_14_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_Enemy_h_14_SPARSE_DATA \
	StarryTail_Source_StarryTail_Enemy_h_14_RPC_WRAPPERS \
	StarryTail_Source_StarryTail_Enemy_h_14_INCLASS \
	StarryTail_Source_StarryTail_Enemy_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define StarryTail_Source_StarryTail_Enemy_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_Enemy_h_14_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_Enemy_h_14_SPARSE_DATA \
	StarryTail_Source_StarryTail_Enemy_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_Enemy_h_14_INCLASS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_Enemy_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STARRYTAIL_API UClass* StaticClass<class AEnemy>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID StarryTail_Source_StarryTail_Enemy_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
