// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/EnemySource/DetectPlayer.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDetectPlayer() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_UDetectPlayer_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_UDetectPlayer();
	AIMODULE_API UClass* Z_Construct_UClass_UBTService();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
// End Cross Module References
	void UDetectPlayer::StaticRegisterNativesUDetectPlayer()
	{
	}
	UClass* Z_Construct_UClass_UDetectPlayer_NoRegister()
	{
		return UDetectPlayer::StaticClass();
	}
	struct Z_Construct_UClass_UDetectPlayer_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UDetectPlayer_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBTService,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDetectPlayer_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "EnemySource/DetectPlayer.h" },
		{ "ModuleRelativePath", "EnemySource/DetectPlayer.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UDetectPlayer_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDetectPlayer>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UDetectPlayer_Statics::ClassParams = {
		&UDetectPlayer::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UDetectPlayer_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UDetectPlayer_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UDetectPlayer()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UDetectPlayer_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UDetectPlayer, 2232199223);
	template<> STARRYTAIL_API UClass* StaticClass<UDetectPlayer>()
	{
		return UDetectPlayer::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UDetectPlayer(Z_Construct_UClass_UDetectPlayer, &UDetectPlayer::StaticClass, TEXT("/Script/StarryTail"), TEXT("UDetectPlayer"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UDetectPlayer);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
