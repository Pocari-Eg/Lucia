// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Private/FMODAssetLookup.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODAssetLookup() {}
// Cross Module References
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FFMODAssetLookupRow();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTableRowBase();
// End Cross Module References

static_assert(std::is_polymorphic<FFMODAssetLookupRow>() == std::is_polymorphic<FTableRowBase>(), "USTRUCT FFMODAssetLookupRow cannot be polymorphic unless super FTableRowBase is polymorphic");

class UScriptStruct* FFMODAssetLookupRow::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FMODSTUDIO_API uint32 Get_Z_Construct_UScriptStruct_FFMODAssetLookupRow_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FFMODAssetLookupRow, Z_Construct_UPackage__Script_FMODStudio(), TEXT("FMODAssetLookupRow"), sizeof(FFMODAssetLookupRow), Get_Z_Construct_UScriptStruct_FFMODAssetLookupRow_Hash());
	}
	return Singleton;
}
template<> FMODSTUDIO_API UScriptStruct* StaticStruct<FFMODAssetLookupRow>()
{
	return FFMODAssetLookupRow::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FFMODAssetLookupRow(FFMODAssetLookupRow::StaticStruct, TEXT("/Script/FMODStudio"), TEXT("FMODAssetLookupRow"), false, nullptr, nullptr);
static struct FScriptStruct_FMODStudio_StaticRegisterNativesFFMODAssetLookupRow
{
	FScriptStruct_FMODStudio_StaticRegisterNativesFFMODAssetLookupRow()
	{
		UScriptStruct::DeferCppStructOps<FFMODAssetLookupRow>(FName(TEXT("FMODAssetLookupRow")));
	}
} ScriptStruct_FMODStudio_StaticRegisterNativesFFMODAssetLookupRow;
	struct Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PackageName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PackageName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AssetName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AssetName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/FMODAssetLookup.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFMODAssetLookupRow>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::NewProp_PackageName_MetaData[] = {
		{ "Category", "FMOD|Internal|AssetLookup" },
		{ "ModuleRelativePath", "Private/FMODAssetLookup.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::NewProp_PackageName = { "PackageName", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFMODAssetLookupRow, PackageName), METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::NewProp_PackageName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::NewProp_PackageName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::NewProp_AssetName_MetaData[] = {
		{ "Category", "FMOD|Internal|AssetLookup" },
		{ "ModuleRelativePath", "Private/FMODAssetLookup.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::NewProp_AssetName = { "AssetName", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFMODAssetLookupRow, AssetName), METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::NewProp_AssetName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::NewProp_AssetName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::NewProp_PackageName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::NewProp_AssetName,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
		Z_Construct_UScriptStruct_FTableRowBase,
		&NewStructOps,
		"FMODAssetLookupRow",
		sizeof(FFMODAssetLookupRow),
		alignof(FFMODAssetLookupRow),
		Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFMODAssetLookupRow()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FFMODAssetLookupRow_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("FMODAssetLookupRow"), sizeof(FFMODAssetLookupRow), Get_Z_Construct_UScriptStruct_FFMODAssetLookupRow_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FFMODAssetLookupRow_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FFMODAssetLookupRow_Hash() { return 2888135102U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
