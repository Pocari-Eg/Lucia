// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STARRYTAIL_EnemyController_generated_h
#error "EnemyController.generated.h already included, missing '#pragma once' in EnemyController.h"
#endif
#define STARRYTAIL_EnemyController_generated_h

#define StarryTail_Source_StarryTail_EnemyController_h_20_SPARSE_DATA
#define StarryTail_Source_StarryTail_EnemyController_h_20_RPC_WRAPPERS
#define StarryTail_Source_StarryTail_EnemyController_h_20_RPC_WRAPPERS_NO_PURE_DECLS
#define StarryTail_Source_StarryTail_EnemyController_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemyController(); \
	friend struct Z_Construct_UClass_AEnemyController_Statics; \
public: \
	DECLARE_CLASS(AEnemyController, AAIController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AEnemyController)


#define StarryTail_Source_StarryTail_EnemyController_h_20_INCLASS \
private: \
	static void StaticRegisterNativesAEnemyController(); \
	friend struct Z_Construct_UClass_AEnemyController_Statics; \
public: \
	DECLARE_CLASS(AEnemyController, AAIController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(AEnemyController)


#define StarryTail_Source_StarryTail_EnemyController_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AEnemyController(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AEnemyController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemyController(AEnemyController&&); \
	NO_API AEnemyController(const AEnemyController&); \
public:


#define StarryTail_Source_StarryTail_EnemyController_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemyController(AEnemyController&&); \
	NO_API AEnemyController(const AEnemyController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemyController)


#define StarryTail_Source_StarryTail_EnemyController_h_20_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__BTAsset() { return STRUCT_OFFSET(AEnemyController, BTAsset); } \
	FORCEINLINE static uint32 __PPO__BBAsset() { return STRUCT_OFFSET(AEnemyController, BBAsset); }


#define StarryTail_Source_StarryTail_EnemyController_h_17_PROLOG
#define StarryTail_Source_StarryTail_EnemyController_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_EnemyController_h_20_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_EnemyController_h_20_SPARSE_DATA \
	StarryTail_Source_StarryTail_EnemyController_h_20_RPC_WRAPPERS \
	StarryTail_Source_StarryTail_EnemyController_h_20_INCLASS \
	StarryTail_Source_StarryTail_EnemyController_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define StarryTail_Source_StarryTail_EnemyController_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_EnemyController_h_20_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_EnemyController_h_20_SPARSE_DATA \
	StarryTail_Source_StarryTail_EnemyController_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_EnemyController_h_20_INCLASS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_EnemyController_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STARRYTAIL_API UClass* StaticClass<class AEnemyController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID StarryTail_Source_StarryTail_EnemyController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
