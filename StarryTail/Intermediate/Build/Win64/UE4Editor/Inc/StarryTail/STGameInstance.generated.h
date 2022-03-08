// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STARRYTAIL_STGameInstance_generated_h
#error "STGameInstance.generated.h already included, missing '#pragma once' in STGameInstance.h"
#endif
#define STARRYTAIL_STGameInstance_generated_h

#define StarryTail_Source_StarryTail_STGameInstance_h_17_SPARSE_DATA
#define StarryTail_Source_StarryTail_STGameInstance_h_17_RPC_WRAPPERS
#define StarryTail_Source_StarryTail_STGameInstance_h_17_RPC_WRAPPERS_NO_PURE_DECLS
#define StarryTail_Source_StarryTail_STGameInstance_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSTGameInstance(); \
	friend struct Z_Construct_UClass_USTGameInstance_Statics; \
public: \
	DECLARE_CLASS(USTGameInstance, UGameInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(USTGameInstance)


#define StarryTail_Source_StarryTail_STGameInstance_h_17_INCLASS \
private: \
	static void StaticRegisterNativesUSTGameInstance(); \
	friend struct Z_Construct_UClass_USTGameInstance_Statics; \
public: \
	DECLARE_CLASS(USTGameInstance, UGameInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(USTGameInstance)


#define StarryTail_Source_StarryTail_STGameInstance_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USTGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USTGameInstance) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USTGameInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USTGameInstance); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USTGameInstance(USTGameInstance&&); \
	NO_API USTGameInstance(const USTGameInstance&); \
public:


#define StarryTail_Source_StarryTail_STGameInstance_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USTGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USTGameInstance(USTGameInstance&&); \
	NO_API USTGameInstance(const USTGameInstance&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USTGameInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USTGameInstance); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USTGameInstance)


#define StarryTail_Source_StarryTail_STGameInstance_h_17_PRIVATE_PROPERTY_OFFSET
#define StarryTail_Source_StarryTail_STGameInstance_h_14_PROLOG
#define StarryTail_Source_StarryTail_STGameInstance_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_STGameInstance_h_17_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_STGameInstance_h_17_SPARSE_DATA \
	StarryTail_Source_StarryTail_STGameInstance_h_17_RPC_WRAPPERS \
	StarryTail_Source_StarryTail_STGameInstance_h_17_INCLASS \
	StarryTail_Source_StarryTail_STGameInstance_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define StarryTail_Source_StarryTail_STGameInstance_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_STGameInstance_h_17_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_STGameInstance_h_17_SPARSE_DATA \
	StarryTail_Source_StarryTail_STGameInstance_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_STGameInstance_h_17_INCLASS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_STGameInstance_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STARRYTAIL_API UClass* StaticClass<class USTGameInstance>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID StarryTail_Source_StarryTail_STGameInstance_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
