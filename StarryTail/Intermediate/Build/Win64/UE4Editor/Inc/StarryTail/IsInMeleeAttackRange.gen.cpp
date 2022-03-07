// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/EnemySource/IsInMeleeAttackRange.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeIsInMeleeAttackRange() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_UIsInMeleeAttackRange_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_UIsInMeleeAttackRange();
	AIMODULE_API UClass* Z_Construct_UClass_UBTDecorator();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
// End Cross Module References
	void UIsInMeleeAttackRange::StaticRegisterNativesUIsInMeleeAttackRange()
	{
	}
	UClass* Z_Construct_UClass_UIsInMeleeAttackRange_NoRegister()
	{
		return UIsInMeleeAttackRange::StaticClass();
	}
	struct Z_Construct_UClass_UIsInMeleeAttackRange_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UIsInMeleeAttackRange_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBTDecorator,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UIsInMeleeAttackRange_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "EnemySource/IsInMeleeAttackRange.h" },
		{ "ModuleRelativePath", "EnemySource/IsInMeleeAttackRange.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UIsInMeleeAttackRange_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UIsInMeleeAttackRange>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UIsInMeleeAttackRange_Statics::ClassParams = {
		&UIsInMeleeAttackRange::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UIsInMeleeAttackRange_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UIsInMeleeAttackRange_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UIsInMeleeAttackRange()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UIsInMeleeAttackRange_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UIsInMeleeAttackRange, 3845460908);
	template<> STARRYTAIL_API UClass* StaticClass<UIsInMeleeAttackRange>()
	{
		return UIsInMeleeAttackRange::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UIsInMeleeAttackRange(Z_Construct_UClass_UIsInMeleeAttackRange, &UIsInMeleeAttackRange::StaticClass, TEXT("/Script/StarryTail"), TEXT("UIsInMeleeAttackRange"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UIsInMeleeAttackRange);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
