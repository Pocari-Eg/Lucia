// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODBank.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODBank() {}
// Cross Module References
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODBank_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODBank();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAsset();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
// End Cross Module References
	void UFMODBank::StaticRegisterNativesUFMODBank()
	{
	}
	UClass* Z_Construct_UClass_UFMODBank_NoRegister()
	{
		return UFMODBank::StaticClass();
	}
	struct Z_Construct_UClass_UFMODBank_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODBank_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFMODAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODBank_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * FMOD Bank Asset.\n */" },
		{ "IncludePath", "FMODBank.h" },
		{ "ModuleRelativePath", "Classes/FMODBank.h" },
		{ "ToolTip", "FMOD Bank Asset." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODBank_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODBank>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODBank_Statics::ClassParams = {
		&UFMODBank::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UFMODBank_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODBank_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODBank()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODBank_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODBank, 161593090);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODBank>()
	{
		return UFMODBank::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODBank(Z_Construct_UClass_UFMODBank, &UFMODBank::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODBank"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODBank);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
