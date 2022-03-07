// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/EnemyRangedAttack.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyRangedAttack() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_UEnemyRangedAttack_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_UEnemyRangedAttack();
	AIMODULE_API UClass* Z_Construct_UClass_UBTTaskNode();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
// End Cross Module References
	void UEnemyRangedAttack::StaticRegisterNativesUEnemyRangedAttack()
	{
	}
	UClass* Z_Construct_UClass_UEnemyRangedAttack_NoRegister()
	{
		return UEnemyRangedAttack::StaticClass();
	}
	struct Z_Construct_UClass_UEnemyRangedAttack_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UEnemyRangedAttack_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBTTaskNode,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEnemyRangedAttack_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "EnemyRangedAttack.h" },
		{ "ModuleRelativePath", "EnemyRangedAttack.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UEnemyRangedAttack_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEnemyRangedAttack>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UEnemyRangedAttack_Statics::ClassParams = {
		&UEnemyRangedAttack::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UEnemyRangedAttack_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UEnemyRangedAttack_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UEnemyRangedAttack()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UEnemyRangedAttack_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UEnemyRangedAttack, 1794778114);
	template<> STARRYTAIL_API UClass* StaticClass<UEnemyRangedAttack>()
	{
		return UEnemyRangedAttack::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UEnemyRangedAttack(Z_Construct_UClass_UEnemyRangedAttack, &UEnemyRangedAttack::StaticClass, TEXT("/Script/StarryTail"), TEXT("UEnemyRangedAttack"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UEnemyRangedAttack);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
