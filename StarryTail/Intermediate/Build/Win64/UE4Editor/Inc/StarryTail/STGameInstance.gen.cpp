// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/STGameInstance.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSTGameInstance() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_USTGameInstance_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_USTGameInstance();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
// End Cross Module References
	void USTGameInstance::StaticRegisterNativesUSTGameInstance()
	{
	}
	UClass* Z_Construct_UClass_USTGameInstance_NoRegister()
	{
		return USTGameInstance::StaticClass();
	}
	struct Z_Construct_UClass_USTGameInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USTGameInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USTGameInstance_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "STGameInstance.h" },
		{ "ModuleRelativePath", "STGameInstance.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USTGameInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USTGameInstance>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USTGameInstance_Statics::ClassParams = {
		&USTGameInstance::StaticClass,
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
		0x009000A8u,
		METADATA_PARAMS(Z_Construct_UClass_USTGameInstance_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USTGameInstance_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USTGameInstance()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USTGameInstance_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USTGameInstance, 2839790822);
	template<> STARRYTAIL_API UClass* StaticClass<USTGameInstance>()
	{
		return USTGameInstance::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USTGameInstance(Z_Construct_UClass_USTGameInstance, &USTGameInstance::StaticClass, TEXT("/Script/StarryTail"), TEXT("USTGameInstance"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USTGameInstance);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
