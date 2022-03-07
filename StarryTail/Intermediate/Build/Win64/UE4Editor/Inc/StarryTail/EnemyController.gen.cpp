// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/EnemyController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyController() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_AEnemyController_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_AEnemyController();
	AIMODULE_API UClass* Z_Construct_UClass_AAIController();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
	AIMODULE_API UClass* Z_Construct_UClass_UBehaviorTree_NoRegister();
	AIMODULE_API UClass* Z_Construct_UClass_UBlackboardData_NoRegister();
// End Cross Module References
	void AEnemyController::StaticRegisterNativesAEnemyController()
	{
	}
	UClass* Z_Construct_UClass_AEnemyController_NoRegister()
	{
		return AEnemyController::StaticClass();
	}
	struct Z_Construct_UClass_AEnemyController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BTAsset_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BTAsset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BBAsset_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BBAsset;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEnemyController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AAIController,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/*\n ???\xc5\xb8? ???? ????\xc6\xae - RangedAttackEffect\n ?\xd9\xb0\xc5\xb8?, ???\xc5\xb8?, ???? ???? ?? ?\xe6\xb5\xb9\xc3\xbc\n ???????? ???? ??\xc4\xa1 - SpawnPos\n ???\xc5\xb8? ???? \xc8\xbd?? - RangedAttackCount o\n ???\xc5\xb8? ???? ???\xc5\xb8? - RangedAttackRange o\n ?\xd9\xb0\xc5\xb8? ???? ???\xc5\xb8? - MeleeAttackRange o\n */" },
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "EnemyController.h" },
		{ "ModuleRelativePath", "EnemyController.h" },
		{ "ToolTip", "???\xc5\xb8? ???? ????\xc6\xae - RangedAttackEffect\n?\xd9\xb0\xc5\xb8?, ???\xc5\xb8?, ???? ???? ?? ?\xe6\xb5\xb9\xc3\xbc\n???????? ???? ??\xc4\xa1 - SpawnPos\n???\xc5\xb8? ???? \xc8\xbd?? - RangedAttackCount o\n???\xc5\xb8? ???? ???\xc5\xb8? - RangedAttackRange o\n?\xd9\xb0\xc5\xb8? ???? ???\xc5\xb8? - MeleeAttackRange o" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyController_Statics::NewProp_BTAsset_MetaData[] = {
		{ "Comment", "//?\xd8\xb4? ?????????? ??\xc5\xb8?\xd3\xb5??? \xc8\xae?\xce\xb0???\n" },
		{ "ModuleRelativePath", "EnemyController.h" },
		{ "ToolTip", "?\xd8\xb4? ?????????? ??\xc5\xb8?\xd3\xb5??? \xc8\xae?\xce\xb0???" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyController_Statics::NewProp_BTAsset = { "BTAsset", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEnemyController, BTAsset), Z_Construct_UClass_UBehaviorTree_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AEnemyController_Statics::NewProp_BTAsset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyController_Statics::NewProp_BTAsset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyController_Statics::NewProp_BBAsset_MetaData[] = {
		{ "ModuleRelativePath", "EnemyController.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyController_Statics::NewProp_BBAsset = { "BBAsset", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEnemyController, BBAsset), Z_Construct_UClass_UBlackboardData_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AEnemyController_Statics::NewProp_BBAsset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyController_Statics::NewProp_BBAsset_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEnemyController_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyController_Statics::NewProp_BTAsset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyController_Statics::NewProp_BBAsset,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEnemyController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyController>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AEnemyController_Statics::ClassParams = {
		&AEnemyController::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AEnemyController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyController_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AEnemyController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AEnemyController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AEnemyController_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AEnemyController, 1333979196);
	template<> STARRYTAIL_API UClass* StaticClass<AEnemyController>()
	{
		return AEnemyController::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AEnemyController(Z_Construct_UClass_AEnemyController, &AEnemyController::StaticClass, TEXT("/Script/StarryTail"), TEXT("AEnemyController"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
