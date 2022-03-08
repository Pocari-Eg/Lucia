// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef STARRYTAIL_EnemyMagicAttack_generated_h
#error "EnemyMagicAttack.generated.h already included, missing '#pragma once' in EnemyMagicAttack.h"
#endif
#define STARRYTAIL_EnemyMagicAttack_generated_h

#define StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_SPARSE_DATA
#define StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnCollisionOverlap);


#define StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnCollisionOverlap);


#define StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemyMagicAttack(); \
	friend struct Z_Construct_UClass_AEnemyMagicAttack_Statics; \
public: \
	DECLARE_CLASS(AEnemyMagicAttack, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AEnemyMagicAttack)


#define StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_INCLASS \
private: \
	static void StaticRegisterNativesAEnemyMagicAttack(); \
	friend struct Z_Construct_UClass_AEnemyMagicAttack_Statics; \
public: \
	DECLARE_CLASS(AEnemyMagicAttack, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AEnemyMagicAttack)


#define StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AEnemyMagicAttack(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AEnemyMagicAttack) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyMagicAttack); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyMagicAttack); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemyMagicAttack(AEnemyMagicAttack&&); \
	NO_API AEnemyMagicAttack(const AEnemyMagicAttack&); \
public:


#define StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemyMagicAttack(AEnemyMagicAttack&&); \
	NO_API AEnemyMagicAttack(const AEnemyMagicAttack&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyMagicAttack); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyMagicAttack); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemyMagicAttack)


#define StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Player() { return STRUCT_OFFSET(AEnemyMagicAttack, Player); } \
	FORCEINLINE static uint32 __PPO__Speed() { return STRUCT_OFFSET(AEnemyMagicAttack, Speed); }


#define StarryTail_Source_StarryTail_EnemyMagicAttack_h_10_PROLOG
#define StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_SPARSE_DATA \
	StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_RPC_WRAPPERS \
	StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_INCLASS \
	StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_SPARSE_DATA \
	StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_INCLASS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_EnemyMagicAttack_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STARRYTAIL_API UClass* StaticClass<class AEnemyMagicAttack>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID StarryTail_Source_StarryTail_EnemyMagicAttack_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
