// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODBus.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODBus() {}
// Cross Module References
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODBus_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODBus();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAsset();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
// End Cross Module References
	void UFMODBus::StaticRegisterNativesUFMODBus()
	{
	}
	UClass* Z_Construct_UClass_UFMODBus_NoRegister()
	{
		return UFMODBus::StaticClass();
	}
	struct Z_Construct_UClass_UFMODBus_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODBus_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFMODAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODBus_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * FMOD Bus Asset.\n */" },
		{ "IncludePath", "FMODBus.h" },
		{ "ModuleRelativePath", "Classes/FMODBus.h" },
		{ "ToolTip", "FMOD Bus Asset." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODBus_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODBus>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODBus_Statics::ClassParams = {
		&UFMODBus::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UFMODBus_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODBus_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODBus()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODBus_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODBus, 284682792);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODBus>()
	{
		return UFMODBus::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODBus(Z_Construct_UClass_UFMODBus, &UFMODBus::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODBus"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODBus);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
