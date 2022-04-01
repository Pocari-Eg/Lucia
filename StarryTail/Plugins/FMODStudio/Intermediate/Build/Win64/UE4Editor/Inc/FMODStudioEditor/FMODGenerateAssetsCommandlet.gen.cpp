// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudioEditor/Classes/FMODGenerateAssetsCommandlet.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODGenerateAssetsCommandlet() {}
// Cross Module References
	FMODSTUDIOEDITOR_API UClass* Z_Construct_UClass_UFMODGenerateAssetsCommandlet_NoRegister();
	FMODSTUDIOEDITOR_API UClass* Z_Construct_UClass_UFMODGenerateAssetsCommandlet();
	ENGINE_API UClass* Z_Construct_UClass_UCommandlet();
	UPackage* Z_Construct_UPackage__Script_FMODStudioEditor();
// End Cross Module References
	void UFMODGenerateAssetsCommandlet::StaticRegisterNativesUFMODGenerateAssetsCommandlet()
	{
	}
	UClass* Z_Construct_UClass_UFMODGenerateAssetsCommandlet_NoRegister()
	{
		return UFMODGenerateAssetsCommandlet::StaticClass();
	}
	struct Z_Construct_UClass_UFMODGenerateAssetsCommandlet_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODGenerateAssetsCommandlet_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCommandlet,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudioEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODGenerateAssetsCommandlet_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "FMODGenerateAssetsCommandlet.h" },
		{ "ModuleRelativePath", "Classes/FMODGenerateAssetsCommandlet.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODGenerateAssetsCommandlet_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODGenerateAssetsCommandlet>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODGenerateAssetsCommandlet_Statics::ClassParams = {
		&UFMODGenerateAssetsCommandlet::StaticClass,
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
		0x000000A8u,
		METADATA_PARAMS(Z_Construct_UClass_UFMODGenerateAssetsCommandlet_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODGenerateAssetsCommandlet_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODGenerateAssetsCommandlet()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODGenerateAssetsCommandlet_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODGenerateAssetsCommandlet, 777480226);
	template<> FMODSTUDIOEDITOR_API UClass* StaticClass<UFMODGenerateAssetsCommandlet>()
	{
		return UFMODGenerateAssetsCommandlet::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODGenerateAssetsCommandlet(Z_Construct_UClass_UFMODGenerateAssetsCommandlet, &UFMODGenerateAssetsCommandlet::StaticClass, TEXT("/Script/FMODStudioEditor"), TEXT("UFMODGenerateAssetsCommandlet"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODGenerateAssetsCommandlet);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
