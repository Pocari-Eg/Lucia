// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/EnemyMeleeAttack.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyMeleeAttack() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_UEnemyMeleeAttack_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_UEnemyMeleeAttack();
	AIMODULE_API UClass* Z_Construct_UClass_UBTTaskNode();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
// End Cross Module References
	void UEnemyMeleeAttack::StaticRegisterNativesUEnemyMeleeAttack()
	{
	}
	UClass* Z_Construct_UClass_UEnemyMeleeAttack_NoRegister()
	{
		return UEnemyMeleeAttack::StaticClass();
	}
	struct Z_Construct_UClass_UEnemyMeleeAttack_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UEnemyMeleeAttack_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBTTaskNode,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEnemyMeleeAttack_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "EnemyMeleeAttack.h" },
		{ "ModuleRelativePath", "EnemyMeleeAttack.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UEnemyMeleeAttack_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEnemyMeleeAttack>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UEnemyMeleeAttack_Statics::ClassParams = {
		&UEnemyMeleeAttack::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UEnemyMeleeAttack_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UEnemyMeleeAttack_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UEnemyMeleeAttack()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UEnemyMeleeAttack_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UEnemyMeleeAttack, 3377591321);
	template<> STARRYTAIL_API UClass* StaticClass<UEnemyMeleeAttack>()
	{
		return UEnemyMeleeAttack::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UEnemyMeleeAttack(Z_Construct_UClass_UEnemyMeleeAttack, &UEnemyMeleeAttack::StaticClass, TEXT("/Script/StarryTail"), TEXT("UEnemyMeleeAttack"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UEnemyMeleeAttack);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
