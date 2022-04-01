// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODSnapshotReverb.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODSnapshotReverb() {}
// Cross Module References
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODSnapshotReverb_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODSnapshotReverb();
	ENGINE_API UClass* Z_Construct_UClass_UReverbEffect();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
// End Cross Module References
	void UFMODSnapshotReverb::StaticRegisterNativesUFMODSnapshotReverb()
	{
	}
	UClass* Z_Construct_UClass_UFMODSnapshotReverb_NoRegister()
	{
		return UFMODSnapshotReverb::StaticClass();
	}
	struct Z_Construct_UClass_UFMODSnapshotReverb_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AssetGuid_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_AssetGuid;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODSnapshotReverb_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UReverbEffect,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSnapshotReverb_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * FMOD Event Asset.\n */" },
		{ "HideCategories", "object" },
		{ "IncludePath", "FMODSnapshotReverb.h" },
		{ "ModuleRelativePath", "Classes/FMODSnapshotReverb.h" },
		{ "ToolTip", "FMOD Event Asset." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSnapshotReverb_Statics::NewProp_AssetGuid_MetaData[] = {
		{ "Comment", "/** The unique Guid, which matches the one exported from FMOD Studio */" },
		{ "ModuleRelativePath", "Classes/FMODSnapshotReverb.h" },
		{ "ToolTip", "The unique Guid, which matches the one exported from FMOD Studio" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFMODSnapshotReverb_Statics::NewProp_AssetGuid = { "AssetGuid", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSnapshotReverb, AssetGuid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(Z_Construct_UClass_UFMODSnapshotReverb_Statics::NewProp_AssetGuid_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSnapshotReverb_Statics::NewProp_AssetGuid_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFMODSnapshotReverb_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSnapshotReverb_Statics::NewProp_AssetGuid,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODSnapshotReverb_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODSnapshotReverb>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODSnapshotReverb_Statics::ClassParams = {
		&UFMODSnapshotReverb::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UFMODSnapshotReverb_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSnapshotReverb_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFMODSnapshotReverb_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSnapshotReverb_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODSnapshotReverb()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODSnapshotReverb_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODSnapshotReverb, 2669190339);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODSnapshotReverb>()
	{
		return UFMODSnapshotReverb::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODSnapshotReverb(Z_Construct_UClass_UFMODSnapshotReverb, &UFMODSnapshotReverb::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODSnapshotReverb"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODSnapshotReverb);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
