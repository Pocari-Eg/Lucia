// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODVCA.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODVCA() {}
// Cross Module References
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODVCA_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODVCA();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAsset();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
// End Cross Module References
	void UFMODVCA::StaticRegisterNativesUFMODVCA()
	{
	}
	UClass* Z_Construct_UClass_UFMODVCA_NoRegister()
	{
		return UFMODVCA::StaticClass();
	}
	struct Z_Construct_UClass_UFMODVCA_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODVCA_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFMODAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODVCA_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * FMOD VCA Asset.\n */" },
		{ "IncludePath", "FMODVCA.h" },
		{ "ModuleRelativePath", "Classes/FMODVCA.h" },
		{ "ToolTip", "FMOD VCA Asset." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODVCA_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODVCA>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODVCA_Statics::ClassParams = {
		&UFMODVCA::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UFMODVCA_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODVCA_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODVCA()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODVCA_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODVCA, 887161680);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODVCA>()
	{
		return UFMODVCA::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODVCA(Z_Construct_UClass_UFMODVCA, &UFMODVCA::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODVCA"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODVCA);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
