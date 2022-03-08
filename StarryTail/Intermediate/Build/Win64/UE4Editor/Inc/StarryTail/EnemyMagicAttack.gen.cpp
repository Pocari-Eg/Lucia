// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/EnemyMagicAttack.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyMagicAttack() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_AEnemyMagicAttack_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_AEnemyMagicAttack();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
	ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_AIreneCharacter_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AEnemyMagicAttack::execOnCollisionOverlap)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComp);
		P_GET_OBJECT(AActor,Z_Param_OtherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
		P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
		P_GET_UBOOL(Z_Param_bFromSweep);
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnCollisionOverlap(Z_Param_OverlappedComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult);
		P_NATIVE_END;
	}
	void AEnemyMagicAttack::StaticRegisterNativesAEnemyMagicAttack()
	{
		UClass* Class = AEnemyMagicAttack::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnCollisionOverlap", &AEnemyMagicAttack::execOnCollisionOverlap },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics
	{
		struct EnemyMagicAttack_eventOnCollisionOverlap_Parms
		{
			UPrimitiveComponent* OverlappedComp;
			AActor* OtherActor;
			UPrimitiveComponent* OtherComp;
			int32 OtherBodyIndex;
			bool bFromSweep;
			FHitResult SweepResult;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OverlappedComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OverlappedComp;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
		static void NewProp_bFromSweep_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bFromSweep;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SweepResult_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_SweepResult;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OverlappedComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OverlappedComp = { "OverlappedComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(EnemyMagicAttack_eventOnCollisionOverlap_Parms, OverlappedComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OverlappedComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OverlappedComp_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(EnemyMagicAttack_eventOnCollisionOverlap_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(EnemyMagicAttack_eventOnCollisionOverlap_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OtherComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OtherComp_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(EnemyMagicAttack_eventOnCollisionOverlap_Parms, OtherBodyIndex), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_bFromSweep_SetBit(void* Obj)
	{
		((EnemyMagicAttack_eventOnCollisionOverlap_Parms*)Obj)->bFromSweep = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_bFromSweep = { "bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(EnemyMagicAttack_eventOnCollisionOverlap_Parms), &Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_bFromSweep_SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_SweepResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_SweepResult = { "SweepResult", nullptr, (EPropertyFlags)0x0010008008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(EnemyMagicAttack_eventOnCollisionOverlap_Parms, SweepResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_SweepResult_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_SweepResult_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OverlappedComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OtherActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OtherComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_OtherBodyIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_bFromSweep,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::NewProp_SweepResult,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "EnemyMagicAttack.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEnemyMagicAttack, nullptr, "OnCollisionOverlap", nullptr, nullptr, sizeof(EnemyMagicAttack_eventOnCollisionOverlap_Parms), Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AEnemyMagicAttack_NoRegister()
	{
		return AEnemyMagicAttack::StaticClass();
	}
	struct Z_Construct_UClass_AEnemyMagicAttack_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Collision_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Collision;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Player_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Player;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Speed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Speed;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEnemyMagicAttack_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AEnemyMagicAttack_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AEnemyMagicAttack_OnCollisionOverlap, "OnCollisionOverlap" }, // 3552129748
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyMagicAttack_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "EnemyMagicAttack.h" },
		{ "ModuleRelativePath", "EnemyMagicAttack.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Collision_MetaData[] = {
		{ "Category", "Mesh" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "EnemyMagicAttack.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Collision = { "Collision", nullptr, (EPropertyFlags)0x00100000000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEnemyMagicAttack, Collision), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Collision_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Collision_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Player_MetaData[] = {
		{ "Category", "Player" },
		{ "Comment", "// Location ?????? ?????????? ?????\xd8\xba???\n" },
		{ "ModuleRelativePath", "EnemyMagicAttack.h" },
		{ "ToolTip", "Location ?????? ?????????? ?????\xd8\xba???" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Player = { "Player", nullptr, (EPropertyFlags)0x0040000000020001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEnemyMagicAttack, Player), Z_Construct_UClass_AIreneCharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Player_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Player_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Speed_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Speed" },
		{ "ModuleRelativePath", "EnemyMagicAttack.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Speed = { "Speed", nullptr, (EPropertyFlags)0x0040000000000015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEnemyMagicAttack, Speed), METADATA_PARAMS(Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Speed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Speed_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEnemyMagicAttack_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Collision,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Player,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyMagicAttack_Statics::NewProp_Speed,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEnemyMagicAttack_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyMagicAttack>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AEnemyMagicAttack_Statics::ClassParams = {
		&AEnemyMagicAttack::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AEnemyMagicAttack_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyMagicAttack_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AEnemyMagicAttack_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyMagicAttack_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AEnemyMagicAttack()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AEnemyMagicAttack_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AEnemyMagicAttack, 3038571883);
	template<> STARRYTAIL_API UClass* StaticClass<AEnemyMagicAttack>()
	{
		return AEnemyMagicAttack::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AEnemyMagicAttack(Z_Construct_UClass_AEnemyMagicAttack, &AEnemyMagicAttack::StaticClass, TEXT("/Script/StarryTail"), TEXT("AEnemyMagicAttack"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyMagicAttack);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
