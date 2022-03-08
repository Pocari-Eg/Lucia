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
#ifdef STARRYTAIL_TestObject_generated_h
#error "TestObject.generated.h already included, missing '#pragma once' in TestObject.h"
#endif
#define STARRYTAIL_TestObject_generated_h

#define StarryTail_Source_StarryTail_TestObject_h_27_SPARSE_DATA
#define StarryTail_Source_StarryTail_TestObject_h_27_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnAttackedOverlap);


#define StarryTail_Source_StarryTail_TestObject_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnAttackedOverlap);


#define StarryTail_Source_StarryTail_TestObject_h_27_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATestObject(); \
	friend struct Z_Construct_UClass_ATestObject_Statics; \
public: \
	DECLARE_CLASS(ATestObject, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(ATestObject)


#define StarryTail_Source_StarryTail_TestObject_h_27_INCLASS \
private: \
	static void StaticRegisterNativesATestObject(); \
	friend struct Z_Construct_UClass_ATestObject_Statics; \
public: \
	DECLARE_CLASS(ATestObject, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StarryTail"), NO_API) \
	DECLARE_SERIALIZER(ATestObject)


#define StarryTail_Source_StarryTail_TestObject_h_27_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATestObject(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATestObject) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATestObject); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATestObject); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATestObject(ATestObject&&); \
	NO_API ATestObject(const ATestObject&); \
public:


#define StarryTail_Source_StarryTail_TestObject_h_27_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATestObject(ATestObject&&); \
	NO_API ATestObject(const ATestObject&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATestObject); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATestObject); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATestObject)


#define StarryTail_Source_StarryTail_TestObject_h_27_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__MaxHP() { return STRUCT_OFFSET(ATestObject, MaxHP); }


#define StarryTail_Source_StarryTail_TestObject_h_24_PROLOG
#define StarryTail_Source_StarryTail_TestObject_h_27_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_TestObject_h_27_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_TestObject_h_27_SPARSE_DATA \
	StarryTail_Source_StarryTail_TestObject_h_27_RPC_WRAPPERS \
	StarryTail_Source_StarryTail_TestObject_h_27_INCLASS \
	StarryTail_Source_StarryTail_TestObject_h_27_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define StarryTail_Source_StarryTail_TestObject_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	StarryTail_Source_StarryTail_TestObject_h_27_PRIVATE_PROPERTY_OFFSET \
	StarryTail_Source_StarryTail_TestObject_h_27_SPARSE_DATA \
	StarryTail_Source_StarryTail_TestObject_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_TestObject_h_27_INCLASS_NO_PURE_DECLS \
	StarryTail_Source_StarryTail_TestObject_h_27_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STARRYTAIL_API UClass* StaticClass<class ATestObject>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID StarryTail_Source_StarryTail_TestObject_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
