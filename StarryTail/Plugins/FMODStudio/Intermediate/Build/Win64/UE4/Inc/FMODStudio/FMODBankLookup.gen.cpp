// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Private/FMODBankLookup.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODBankLookup() {}
// Cross Module References
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FFMODLocalizedBankTable();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTableRowBase();
	ENGINE_API UClass* Z_Construct_UClass_UDataTable_NoRegister();
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FFMODLocalizedBankRow();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODBankLookup_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODBankLookup();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References

static_assert(std::is_polymorphic<FFMODLocalizedBankTable>() == std::is_polymorphic<FTableRowBase>(), "USTRUCT FFMODLocalizedBankTable cannot be polymorphic unless super FTableRowBase is polymorphic");

class UScriptStruct* FFMODLocalizedBankTable::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FMODSTUDIO_API uint32 Get_Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FFMODLocalizedBankTable, Z_Construct_UPackage__Script_FMODStudio(), TEXT("FMODLocalizedBankTable"), sizeof(FFMODLocalizedBankTable), Get_Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Hash());
	}
	return Singleton;
}
template<> FMODSTUDIO_API UScriptStruct* StaticStruct<FFMODLocalizedBankTable>()
{
	return FFMODLocalizedBankTable::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FFMODLocalizedBankTable(FFMODLocalizedBankTable::StaticStruct, TEXT("/Script/FMODStudio"), TEXT("FMODLocalizedBankTable"), false, nullptr, nullptr);
static struct FScriptStruct_FMODStudio_StaticRegisterNativesFFMODLocalizedBankTable
{
	FScriptStruct_FMODStudio_StaticRegisterNativesFFMODLocalizedBankTable()
	{
		UScriptStruct::DeferCppStructOps<FFMODLocalizedBankTable>(FName(TEXT("FMODLocalizedBankTable")));
	}
} ScriptStruct_FMODStudio_StaticRegisterNativesFFMODLocalizedBankTable;
	struct Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Banks_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Banks;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/FMODBankLookup.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFMODLocalizedBankTable>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::NewProp_Banks_MetaData[] = {
		{ "Category", "FMOD|Internal|BankLookup" },
		{ "ModuleRelativePath", "Private/FMODBankLookup.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::NewProp_Banks = { "Banks", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFMODLocalizedBankTable, Banks), Z_Construct_UClass_UDataTable_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::NewProp_Banks_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::NewProp_Banks_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::NewProp_Banks,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
		Z_Construct_UScriptStruct_FTableRowBase,
		&NewStructOps,
		"FMODLocalizedBankTable",
		sizeof(FFMODLocalizedBankTable),
		alignof(FFMODLocalizedBankTable),
		Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFMODLocalizedBankTable()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("FMODLocalizedBankTable"), sizeof(FFMODLocalizedBankTable), Get_Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FFMODLocalizedBankTable_Hash() { return 3594093085U; }

static_assert(std::is_polymorphic<FFMODLocalizedBankRow>() == std::is_polymorphic<FTableRowBase>(), "USTRUCT FFMODLocalizedBankRow cannot be polymorphic unless super FTableRowBase is polymorphic");

class UScriptStruct* FFMODLocalizedBankRow::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FMODSTUDIO_API uint32 Get_Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FFMODLocalizedBankRow, Z_Construct_UPackage__Script_FMODStudio(), TEXT("FMODLocalizedBankRow"), sizeof(FFMODLocalizedBankRow), Get_Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Hash());
	}
	return Singleton;
}
template<> FMODSTUDIO_API UScriptStruct* StaticStruct<FFMODLocalizedBankRow>()
{
	return FFMODLocalizedBankRow::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FFMODLocalizedBankRow(FFMODLocalizedBankRow::StaticStruct, TEXT("/Script/FMODStudio"), TEXT("FMODLocalizedBankRow"), false, nullptr, nullptr);
static struct FScriptStruct_FMODStudio_StaticRegisterNativesFFMODLocalizedBankRow
{
	FScriptStruct_FMODStudio_StaticRegisterNativesFFMODLocalizedBankRow()
	{
		UScriptStruct::DeferCppStructOps<FFMODLocalizedBankRow>(FName(TEXT("FMODLocalizedBankRow")));
	}
} ScriptStruct_FMODStudio_StaticRegisterNativesFFMODLocalizedBankRow;
	struct Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Path_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Path;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/FMODBankLookup.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFMODLocalizedBankRow>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::NewProp_Path_MetaData[] = {
		{ "Category", "FMOD|Internal|BankLookup" },
		{ "ModuleRelativePath", "Private/FMODBankLookup.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFMODLocalizedBankRow, Path), METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::NewProp_Path_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::NewProp_Path_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::NewProp_Path,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
		Z_Construct_UScriptStruct_FTableRowBase,
		&NewStructOps,
		"FMODLocalizedBankRow",
		sizeof(FFMODLocalizedBankRow),
		alignof(FFMODLocalizedBankRow),
		Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFMODLocalizedBankRow()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("FMODLocalizedBankRow"), sizeof(FFMODLocalizedBankRow), Get_Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FFMODLocalizedBankRow_Hash() { return 111509871U; }
	void UFMODBankLookup::StaticRegisterNativesUFMODBankLookup()
	{
	}
	UClass* Z_Construct_UClass_UFMODBankLookup_NoRegister()
	{
		return UFMODBankLookup::StaticClass();
	}
	struct Z_Construct_UClass_UFMODBankLookup_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DataTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_DataTable;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MasterBankPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_MasterBankPath;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MasterAssetsBankPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_MasterAssetsBankPath;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MasterStringsBankPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_MasterStringsBankPath;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODBankLookup_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODBankLookup_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "FMODBankLookup.h" },
		{ "ModuleRelativePath", "Private/FMODBankLookup.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_DataTable_MetaData[] = {
		{ "Category", "FMOD|Internal|BankLookup" },
		{ "ModuleRelativePath", "Private/FMODBankLookup.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_DataTable = { "DataTable", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODBankLookup, DataTable), Z_Construct_UClass_UDataTable_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_DataTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_DataTable_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterBankPath_MetaData[] = {
		{ "Category", "FMOD|Internal|BankLookup" },
		{ "ModuleRelativePath", "Private/FMODBankLookup.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterBankPath = { "MasterBankPath", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODBankLookup, MasterBankPath), METADATA_PARAMS(Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterBankPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterBankPath_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterAssetsBankPath_MetaData[] = {
		{ "Category", "FMOD|Internal|BankLookup" },
		{ "ModuleRelativePath", "Private/FMODBankLookup.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterAssetsBankPath = { "MasterAssetsBankPath", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODBankLookup, MasterAssetsBankPath), METADATA_PARAMS(Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterAssetsBankPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterAssetsBankPath_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterStringsBankPath_MetaData[] = {
		{ "Category", "FMOD|Internal|BankLookup" },
		{ "ModuleRelativePath", "Private/FMODBankLookup.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterStringsBankPath = { "MasterStringsBankPath", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODBankLookup, MasterStringsBankPath), METADATA_PARAMS(Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterStringsBankPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterStringsBankPath_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFMODBankLookup_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_DataTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterBankPath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterAssetsBankPath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODBankLookup_Statics::NewProp_MasterStringsBankPath,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODBankLookup_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODBankLookup>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODBankLookup_Statics::ClassParams = {
		&UFMODBankLookup::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UFMODBankLookup_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UFMODBankLookup_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFMODBankLookup_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODBankLookup_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODBankLookup()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODBankLookup_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODBankLookup, 1976824998);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODBankLookup>()
	{
		return UFMODBankLookup::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODBankLookup(Z_Construct_UClass_UFMODBankLookup, &UFMODBankLookup::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODBankLookup"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODBankLookup);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
