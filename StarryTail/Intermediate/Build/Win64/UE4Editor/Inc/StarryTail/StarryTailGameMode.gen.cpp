// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/StarryTailGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStarryTailGameMode() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_AStarryTailGameMode_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_AStarryTailGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
// End Cross Module References
	void AStarryTailGameMode::StaticRegisterNativesAStarryTailGameMode()
	{
	}
	UClass* Z_Construct_UClass_AStarryTailGameMode_NoRegister()
	{
		return AStarryTailGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AStarryTailGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AStarryTailGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStarryTailGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "StarryTailGameMode.h" },
		{ "ModuleRelativePath", "StarryTailGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AStarryTailGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AStarryTailGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AStarryTailGameMode_Statics::ClassParams = {
		&AStarryTailGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AStarryTailGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AStarryTailGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AStarryTailGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AStarryTailGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AStarryTailGameMode, 2000931356);
	template<> STARRYTAIL_API UClass* StaticClass<AStarryTailGameMode>()
	{
		return AStarryTailGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AStarryTailGameMode(Z_Construct_UClass_AStarryTailGameMode, &AStarryTailGameMode::StaticClass, TEXT("/Script/StarryTail"), TEXT("AStarryTailGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AStarryTailGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
