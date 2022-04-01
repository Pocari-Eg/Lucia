// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODSnapshot.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODSnapshot() {}
// Cross Module References
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODSnapshot_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODSnapshot();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEvent();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
// End Cross Module References
	void UFMODSnapshot::StaticRegisterNativesUFMODSnapshot()
	{
	}
	UClass* Z_Construct_UClass_UFMODSnapshot_NoRegister()
	{
		return UFMODSnapshot::StaticClass();
	}
	struct Z_Construct_UClass_UFMODSnapshot_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODSnapshot_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFMODEvent,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSnapshot_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * FMOD Snapshot Asset.\n */" },
		{ "IncludePath", "FMODSnapshot.h" },
		{ "ModuleRelativePath", "Classes/FMODSnapshot.h" },
		{ "ToolTip", "FMOD Snapshot Asset." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODSnapshot_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODSnapshot>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODSnapshot_Statics::ClassParams = {
		&UFMODSnapshot::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UFMODSnapshot_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSnapshot_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODSnapshot()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODSnapshot_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODSnapshot, 3279018205);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODSnapshot>()
	{
		return UFMODSnapshot::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODSnapshot(Z_Construct_UClass_UFMODSnapshot, &UFMODSnapshot::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODSnapshot"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODSnapshot);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
