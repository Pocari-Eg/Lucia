// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODSettings() {}
// Cross Module References
	FMODSTUDIO_API UEnum* Z_Construct_UEnum_FMODStudio_EFMODSpeakerMode();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
	FMODSTUDIO_API UEnum* Z_Construct_UEnum_FMODStudio_EFMODLogging();
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FFMODProjectLocale();
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FCustomPoolSizes();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODSettings_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODSettings();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FDirectoryPath();
// End Cross Module References
	static UEnum* EFMODSpeakerMode_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_FMODStudio_EFMODSpeakerMode, Z_Construct_UPackage__Script_FMODStudio(), TEXT("EFMODSpeakerMode"));
		}
		return Singleton;
	}
	template<> FMODSTUDIO_API UEnum* StaticEnum<EFMODSpeakerMode::Type>()
	{
		return EFMODSpeakerMode_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EFMODSpeakerMode(EFMODSpeakerMode_StaticEnum, TEXT("/Script/FMODStudio"), TEXT("EFMODSpeakerMode"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_FMODStudio_EFMODSpeakerMode_Hash() { return 3527063458U; }
	UEnum* Z_Construct_UEnum_FMODStudio_EFMODSpeakerMode()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EFMODSpeakerMode"), 0, Get_Z_Construct_UEnum_FMODStudio_EFMODSpeakerMode_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EFMODSpeakerMode::Stereo", (int64)EFMODSpeakerMode::Stereo },
				{ "EFMODSpeakerMode::Surround_5_1", (int64)EFMODSpeakerMode::Surround_5_1 },
				{ "EFMODSpeakerMode::Surround_7_1", (int64)EFMODSpeakerMode::Surround_7_1 },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "ModuleRelativePath", "Classes/FMODSettings.h" },
				{ "Stereo.Comment", "// The speakers are stereo\n" },
				{ "Stereo.Name", "EFMODSpeakerMode::Stereo" },
				{ "Stereo.ToolTip", "The speakers are stereo" },
				{ "Surround_5_1.Comment", "// 5.1 speaker setup\n" },
				{ "Surround_5_1.Name", "EFMODSpeakerMode::Surround_5_1" },
				{ "Surround_5_1.ToolTip", "5.1 speaker setup" },
				{ "Surround_7_1.Comment", "// 7.1 speaker setup\n" },
				{ "Surround_7_1.Name", "EFMODSpeakerMode::Surround_7_1" },
				{ "Surround_7_1.ToolTip", "7.1 speaker setup" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_FMODStudio,
				nullptr,
				"EFMODSpeakerMode",
				"EFMODSpeakerMode::Type",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Namespaced,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* EFMODLogging_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_FMODStudio_EFMODLogging, Z_Construct_UPackage__Script_FMODStudio(), TEXT("EFMODLogging"));
		}
		return Singleton;
	}
	template<> FMODSTUDIO_API UEnum* StaticEnum<EFMODLogging>()
	{
		return EFMODLogging_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EFMODLogging(EFMODLogging_StaticEnum, TEXT("/Script/FMODStudio"), TEXT("EFMODLogging"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_FMODStudio_EFMODLogging_Hash() { return 3818620986U; }
	UEnum* Z_Construct_UEnum_FMODStudio_EFMODLogging()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EFMODLogging"), 0, Get_Z_Construct_UEnum_FMODStudio_EFMODLogging_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "LEVEL_NONE", (int64)LEVEL_NONE },
				{ "LEVEL_ERROR", (int64)LEVEL_ERROR },
				{ "LEVEL_WARNING", (int64)LEVEL_WARNING },
				{ "LEVEL_LOG", (int64)LEVEL_LOG },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "LEVEL_ERROR.Name", "LEVEL_ERROR" },
				{ "LEVEL_LOG.Name", "LEVEL_LOG" },
				{ "LEVEL_NONE.Name", "LEVEL_NONE" },
				{ "LEVEL_WARNING.Name", "LEVEL_WARNING" },
				{ "ModuleRelativePath", "Classes/FMODSettings.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_FMODStudio,
				nullptr,
				"EFMODLogging",
				"EFMODLogging",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FFMODProjectLocale::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FMODSTUDIO_API uint32 Get_Z_Construct_UScriptStruct_FFMODProjectLocale_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FFMODProjectLocale, Z_Construct_UPackage__Script_FMODStudio(), TEXT("FMODProjectLocale"), sizeof(FFMODProjectLocale), Get_Z_Construct_UScriptStruct_FFMODProjectLocale_Hash());
	}
	return Singleton;
}
template<> FMODSTUDIO_API UScriptStruct* StaticStruct<FFMODProjectLocale>()
{
	return FFMODProjectLocale::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FFMODProjectLocale(FFMODProjectLocale::StaticStruct, TEXT("/Script/FMODStudio"), TEXT("FMODProjectLocale"), false, nullptr, nullptr);
static struct FScriptStruct_FMODStudio_StaticRegisterNativesFFMODProjectLocale
{
	FScriptStruct_FMODStudio_StaticRegisterNativesFFMODProjectLocale()
	{
		UScriptStruct::DeferCppStructOps<FFMODProjectLocale>(FName(TEXT("FMODProjectLocale")));
	}
} ScriptStruct_FMODStudio_StaticRegisterNativesFFMODProjectLocale;
	struct Z_Construct_UScriptStruct_FFMODProjectLocale_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LocaleName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_LocaleName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LocaleCode_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_LocaleCode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bDefault_MetaData[];
#endif
		static void NewProp_bDefault_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bDefault;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFMODProjectLocale>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_LocaleName_MetaData[] = {
		{ "Category", "Localization" },
		{ "Comment", "/**\n    * Human readable locale name, displayed in Blueprints.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Human readable locale name, displayed in Blueprints." },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_LocaleName = { "LocaleName", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFMODProjectLocale, LocaleName), METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_LocaleName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_LocaleName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_LocaleCode_MetaData[] = {
		{ "Category", "Localization" },
		{ "Comment", "/**\n    * Locale code. Must correspond to project locale codes in FMOD Studio project.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Locale code. Must correspond to project locale codes in FMOD Studio project." },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_LocaleCode = { "LocaleCode", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFMODProjectLocale, LocaleCode), METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_LocaleCode_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_LocaleCode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_bDefault_MetaData[] = {
		{ "Category", "Localization" },
		{ "Comment", "/**\n    * Default locale at startup. Only one locale should be marked as default.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Default locale at startup. Only one locale should be marked as default." },
	};
#endif
	void Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_bDefault_SetBit(void* Obj)
	{
		((FFMODProjectLocale*)Obj)->bDefault = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_bDefault = { "bDefault", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFMODProjectLocale), &Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_bDefault_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_bDefault_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_bDefault_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_LocaleName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_LocaleCode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::NewProp_bDefault,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
		nullptr,
		&NewStructOps,
		"FMODProjectLocale",
		sizeof(FFMODProjectLocale),
		alignof(FFMODProjectLocale),
		Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFMODProjectLocale()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FFMODProjectLocale_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("FMODProjectLocale"), sizeof(FFMODProjectLocale), Get_Z_Construct_UScriptStruct_FFMODProjectLocale_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FFMODProjectLocale_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FFMODProjectLocale_Hash() { return 292888301U; }
class UScriptStruct* FCustomPoolSizes::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FMODSTUDIO_API uint32 Get_Z_Construct_UScriptStruct_FCustomPoolSizes_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FCustomPoolSizes, Z_Construct_UPackage__Script_FMODStudio(), TEXT("CustomPoolSizes"), sizeof(FCustomPoolSizes), Get_Z_Construct_UScriptStruct_FCustomPoolSizes_Hash());
	}
	return Singleton;
}
template<> FMODSTUDIO_API UScriptStruct* StaticStruct<FCustomPoolSizes>()
{
	return FCustomPoolSizes::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FCustomPoolSizes(FCustomPoolSizes::StaticStruct, TEXT("/Script/FMODStudio"), TEXT("CustomPoolSizes"), false, nullptr, nullptr);
static struct FScriptStruct_FMODStudio_StaticRegisterNativesFCustomPoolSizes
{
	FScriptStruct_FMODStudio_StaticRegisterNativesFCustomPoolSizes()
	{
		UScriptStruct::DeferCppStructOps<FCustomPoolSizes>(FName(TEXT("CustomPoolSizes")));
	}
} ScriptStruct_FMODStudio_StaticRegisterNativesFCustomPoolSizes;
	struct Z_Construct_UScriptStruct_FCustomPoolSizes_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Desktop_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Desktop;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Mobile_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Mobile;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PS4_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_PS4;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Switch_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Switch;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_XboxOne_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_XboxOne;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCustomPoolSizes>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Desktop_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Default = 0 (Disabled) units in bytes*/" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Default = 0 (Disabled) units in bytes" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Desktop = { "Desktop", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCustomPoolSizes, Desktop), METADATA_PARAMS(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Desktop_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Desktop_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Mobile_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Default = 0 (Disabled) units in bytes*/" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Default = 0 (Disabled) units in bytes" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Mobile = { "Mobile", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCustomPoolSizes, Mobile), METADATA_PARAMS(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Mobile_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Mobile_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_PS4_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Default = 0 (Disabled) units in bytes*/" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Default = 0 (Disabled) units in bytes" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_PS4 = { "PS4", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCustomPoolSizes, PS4), METADATA_PARAMS(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_PS4_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_PS4_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Switch_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Default = 0 (Disabled) units in bytes*/" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Default = 0 (Disabled) units in bytes" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Switch = { "Switch", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCustomPoolSizes, Switch), METADATA_PARAMS(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Switch_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Switch_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_XboxOne_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Default = 0 (Disabled) units in bytes*/" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Default = 0 (Disabled) units in bytes" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_XboxOne = { "XboxOne", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCustomPoolSizes, XboxOne), METADATA_PARAMS(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_XboxOne_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_XboxOne_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Desktop,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Mobile,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_PS4,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_Switch,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::NewProp_XboxOne,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
		nullptr,
		&NewStructOps,
		"CustomPoolSizes",
		sizeof(FCustomPoolSizes),
		alignof(FCustomPoolSizes),
		Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FCustomPoolSizes()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FCustomPoolSizes_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("CustomPoolSizes"), sizeof(FCustomPoolSizes), Get_Z_Construct_UScriptStruct_FCustomPoolSizes_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FCustomPoolSizes_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FCustomPoolSizes_Hash() { return 2366781117U; }
	void UFMODSettings::StaticRegisterNativesUFMODSettings()
	{
	}
	UClass* Z_Construct_UClass_UFMODSettings_NoRegister()
	{
		return UFMODSettings::StaticClass();
	}
	struct Z_Construct_UClass_UFMODSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bLoadAllBanks_MetaData[];
#endif
		static void NewProp_bLoadAllBanks_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bLoadAllBanks;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bLoadAllSampleData_MetaData[];
#endif
		static void NewProp_bLoadAllSampleData_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bLoadAllSampleData;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableLiveUpdate_MetaData[];
#endif
		static void NewProp_bEnableLiveUpdate_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableLiveUpdate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableEditorLiveUpdate_MetaData[];
#endif
		static void NewProp_bEnableEditorLiveUpdate_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableEditorLiveUpdate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BankOutputDirectory_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_BankOutputDirectory;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OutputFormat_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_OutputFormat;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Locales_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Locales_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Locales;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bVol0Virtual_MetaData[];
#endif
		static void NewProp_bVol0Virtual_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bVol0Virtual;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vol0VirtualLevel_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Vol0VirtualLevel;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SampleRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_SampleRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bMatchHardwareSampleRate_MetaData[];
#endif
		static void NewProp_bMatchHardwareSampleRate_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bMatchHardwareSampleRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RealChannelCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_RealChannelCount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TotalChannelCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TotalChannelCount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DSPBufferLength_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DSPBufferLength;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DSPBufferCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DSPBufferCount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FileBufferSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_FileBufferSize;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StudioUpdatePeriod_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_StudioUpdatePeriod;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InitialOutputDriverName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_InitialOutputDriverName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bLockAllBuses_MetaData[];
#endif
		static void NewProp_bLockAllBuses_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bLockAllBuses;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MemoryPoolSizes_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MemoryPoolSizes;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LiveUpdatePort_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_LiveUpdatePort;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EditorLiveUpdatePort_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_EditorLiveUpdatePort;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ReloadBanksDelay_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReloadBanksDelay;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableMemoryTracking_MetaData[];
#endif
		static void NewProp_bEnableMemoryTracking_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableMemoryTracking;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PluginFiles_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PluginFiles_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_PluginFiles;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ContentBrowserPrefix_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ContentBrowserPrefix;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ForcePlatformName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ForcePlatformName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MasterBankName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_MasterBankName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SkipLoadBankName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_SkipLoadBankName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StudioBankKey_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_StudioBankKey;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WavWriterPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_WavWriterPath;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LoggingLevel_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_LoggingLevel;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OcclusionParameter_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_OcclusionParameter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AmbientVolumeParameter_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AmbientVolumeParameter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AmbientLPFParameter_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AmbientLPFParameter;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "FMODSettings.h" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllBanks_MetaData[] = {
		{ "Category", "Basic" },
		{ "Comment", "/**\n\x09 * Whether to load all banks at startup.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Whether to load all banks at startup." },
	};
#endif
	void Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllBanks_SetBit(void* Obj)
	{
		((UFMODSettings*)Obj)->bLoadAllBanks = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllBanks = { "bLoadAllBanks", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFMODSettings), &Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllBanks_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllBanks_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllBanks_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllSampleData_MetaData[] = {
		{ "Category", "Basic" },
		{ "Comment", "/**\n\x09 * Whether to load all bank sample data into memory at startup.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Whether to load all bank sample data into memory at startup." },
	};
#endif
	void Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllSampleData_SetBit(void* Obj)
	{
		((UFMODSettings*)Obj)->bLoadAllSampleData = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllSampleData = { "bLoadAllSampleData", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFMODSettings), &Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllSampleData_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllSampleData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllSampleData_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableLiveUpdate_MetaData[] = {
		{ "Category", "Basic" },
		{ "Comment", "/**\n\x09 * Enable live update in non-final builds.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Enable live update in non-final builds." },
	};
#endif
	void Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableLiveUpdate_SetBit(void* Obj)
	{
		((UFMODSettings*)Obj)->bEnableLiveUpdate = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableLiveUpdate = { "bEnableLiveUpdate", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFMODSettings), &Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableLiveUpdate_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableLiveUpdate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableLiveUpdate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableEditorLiveUpdate_MetaData[] = {
		{ "Category", "Basic" },
		{ "Comment", "/**\n    * Enable live update in Editor for Auditioning. *Requires Restart*\n    */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Enable live update in Editor for Auditioning. *Requires Restart*" },
	};
#endif
	void Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableEditorLiveUpdate_SetBit(void* Obj)
	{
		((UFMODSettings*)Obj)->bEnableEditorLiveUpdate = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableEditorLiveUpdate = { "bEnableEditorLiveUpdate", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFMODSettings), &Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableEditorLiveUpdate_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableEditorLiveUpdate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableEditorLiveUpdate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_BankOutputDirectory_MetaData[] = {
		{ "Category", "Basic" },
		{ "Comment", "/**\n\x09 * Path to find your studio bank output directory, relative to Content directory.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "RelativeToGameContentDir", "" },
		{ "ToolTip", "Path to find your studio bank output directory, relative to Content directory." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_BankOutputDirectory = { "BankOutputDirectory", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, BankOutputDirectory), Z_Construct_UScriptStruct_FDirectoryPath, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_BankOutputDirectory_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_BankOutputDirectory_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_OutputFormat_MetaData[] = {
		{ "Category", "Basic" },
		{ "Comment", "/** Project Output Format, should match the mode set up for the Studio project. */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Project Output Format, should match the mode set up for the Studio project." },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_OutputFormat = { "OutputFormat", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, OutputFormat), Z_Construct_UEnum_FMODStudio_EFMODSpeakerMode, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_OutputFormat_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_OutputFormat_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_Locales_Inner = { "Locales", nullptr, (EPropertyFlags)0x0000000000004000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFMODProjectLocale, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_Locales_MetaData[] = {
		{ "Category", "Localization" },
		{ "Comment", "/**\n    * Locales for localized banks. These should match the project locales configured in the FMOD Studio project.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Locales for localized banks. These should match the project locales configured in the FMOD Studio project." },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_Locales = { "Locales", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, Locales), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_Locales_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_Locales_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_bVol0Virtual_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09 * Whether to enable vol0virtual, which means voices with low volume will automatically go virtual to save CPU.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Whether to enable vol0virtual, which means voices with low volume will automatically go virtual to save CPU." },
	};
#endif
	void Z_Construct_UClass_UFMODSettings_Statics::NewProp_bVol0Virtual_SetBit(void* Obj)
	{
		((UFMODSettings*)Obj)->bVol0Virtual = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_bVol0Virtual = { "bVol0Virtual", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFMODSettings), &Z_Construct_UClass_UFMODSettings_Statics::NewProp_bVol0Virtual_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bVol0Virtual_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bVol0Virtual_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_Vol0VirtualLevel_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09 * If vol0virtual is enabled, the signal level at which to make channels virtual.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "If vol0virtual is enabled, the signal level at which to make channels virtual." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_Vol0VirtualLevel = { "Vol0VirtualLevel", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, Vol0VirtualLevel), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_Vol0VirtualLevel_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_Vol0VirtualLevel_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_SampleRate_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09 * Sample rate to use, or 0 to match system rate.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Sample rate to use, or 0 to match system rate." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_SampleRate = { "SampleRate", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, SampleRate), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_SampleRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_SampleRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_bMatchHardwareSampleRate_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09* Whether to match hardware sample rate where reasonable (44.1kHz to 48kHz).\n\x09*/" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Whether to match hardware sample rate where reasonable (44.1kHz to 48kHz)." },
	};
#endif
	void Z_Construct_UClass_UFMODSettings_Statics::NewProp_bMatchHardwareSampleRate_SetBit(void* Obj)
	{
		((UFMODSettings*)Obj)->bMatchHardwareSampleRate = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_bMatchHardwareSampleRate = { "bMatchHardwareSampleRate", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFMODSettings), &Z_Construct_UClass_UFMODSettings_Statics::NewProp_bMatchHardwareSampleRate_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bMatchHardwareSampleRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bMatchHardwareSampleRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_RealChannelCount_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09 * Number of actual software voices that can be used at once.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Number of actual software voices that can be used at once." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_RealChannelCount = { "RealChannelCount", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, RealChannelCount), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_RealChannelCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_RealChannelCount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_TotalChannelCount_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09 * Total number of voices available that can be either real or virtual.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Total number of voices available that can be either real or virtual." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_TotalChannelCount = { "TotalChannelCount", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, TotalChannelCount), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_TotalChannelCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_TotalChannelCount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_DSPBufferLength_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09 * DSP mixer buffer length (eg. 512, 1024) or 0 for system default.\n\x09 * When changing the Buffer Length, Buffer Count also needs to be set.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "DSP mixer buffer length (eg. 512, 1024) or 0 for system default.\nWhen changing the Buffer Length, Buffer Count also needs to be set." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_DSPBufferLength = { "DSPBufferLength", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, DSPBufferLength), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_DSPBufferLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_DSPBufferLength_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_DSPBufferCount_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09 * DSP mixer buffer count (eg. 2, 4) or 0 for system default.\n\x09 * When changing the Buffer Count, Buffer Length also needs to be set.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "DSP mixer buffer count (eg. 2, 4) or 0 for system default.\nWhen changing the Buffer Count, Buffer Length also needs to be set." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_DSPBufferCount = { "DSPBufferCount", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, DSPBufferCount), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_DSPBufferCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_DSPBufferCount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_FileBufferSize_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09 * File buffer size in bytes (2048 by default).\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "File buffer size in bytes (2048 by default)." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_FileBufferSize = { "FileBufferSize", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, FileBufferSize), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_FileBufferSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_FileBufferSize_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_StudioUpdatePeriod_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09 * Studio update period in milliseconds, or 0 for default (which means 20ms).\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Studio update period in milliseconds, or 0 for default (which means 20ms)." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_StudioUpdatePeriod = { "StudioUpdatePeriod", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, StudioUpdatePeriod), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_StudioUpdatePeriod_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_StudioUpdatePeriod_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_InitialOutputDriverName_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09 * Output device to choose at system start up, or empty for default.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Output device to choose at system start up, or empty for default." },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_InitialOutputDriverName = { "InitialOutputDriverName", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, InitialOutputDriverName), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_InitialOutputDriverName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_InitialOutputDriverName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLockAllBuses_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/**\n\x09 * Lock all mixer buses at startup, making sure they are created up front.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Lock all mixer buses at startup, making sure they are created up front." },
	};
#endif
	void Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLockAllBuses_SetBit(void* Obj)
	{
		((UFMODSettings*)Obj)->bLockAllBuses = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLockAllBuses = { "bLockAllBuses", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFMODSettings), &Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLockAllBuses_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLockAllBuses_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLockAllBuses_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_MemoryPoolSizes_MetaData[] = {
		{ "Category", "InitSettings" },
		{ "Comment", "/** \n     * Use specified memory pool size for platform, units in bytes. Disabled by default.\n     * FMOD may become unstable if the limit is exceeded!\n     */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Use specified memory pool size for platform, units in bytes. Disabled by default.\nFMOD may become unstable if the limit is exceeded!" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_MemoryPoolSizes = { "MemoryPoolSizes", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, MemoryPoolSizes), Z_Construct_UScriptStruct_FCustomPoolSizes, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_MemoryPoolSizes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_MemoryPoolSizes_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_LiveUpdatePort_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n\x09 * Live update port to use, or 0 for default.\n\x09 */" },
		{ "EditCondition", "bEnableLiveUpdate" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Live update port to use, or 0 for default." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_LiveUpdatePort = { "LiveUpdatePort", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, LiveUpdatePort), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_LiveUpdatePort_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_LiveUpdatePort_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_EditorLiveUpdatePort_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n    * Live update port to use while in editor for auditioning. *Requires Restart*\n    */" },
		{ "EditCondition", "bEnableEditorLiveUpdate" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Live update port to use while in editor for auditioning. *Requires Restart*" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_EditorLiveUpdatePort = { "EditorLiveUpdatePort", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, EditorLiveUpdatePort), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_EditorLiveUpdatePort_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_EditorLiveUpdatePort_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_ReloadBanksDelay_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n    * Delay in seconds before automatically reloading modified banks from disk. This can be extended if building\n    * banks takes a long time and UE4 tries to reload banks before building is completed.\n    * Set to 0 to disable automatic bank reloading.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Delay in seconds before automatically reloading modified banks from disk. This can be extended if building\nbanks takes a long time and UE4 tries to reload banks before building is completed.\nSet to 0 to disable automatic bank reloading." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_ReloadBanksDelay = { "ReloadBanksDelay", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, ReloadBanksDelay), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_ReloadBanksDelay_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_ReloadBanksDelay_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableMemoryTracking_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n    * Enable memory tracking.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Enable memory tracking." },
	};
#endif
	void Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableMemoryTracking_SetBit(void* Obj)
	{
		((UFMODSettings*)Obj)->bEnableMemoryTracking = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableMemoryTracking = { "bEnableMemoryTracking", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFMODSettings), &Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableMemoryTracking_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableMemoryTracking_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableMemoryTracking_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_PluginFiles_Inner = { "PluginFiles", nullptr, (EPropertyFlags)0x0000000000004000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_PluginFiles_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n\x09 * Extra plugin files to load.  \n\x09 * The plugin files should sit alongside the FMOD dynamic libraries in the ThirdParty directory.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Extra plugin files to load.\nThe plugin files should sit alongside the FMOD dynamic libraries in the ThirdParty directory." },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_PluginFiles = { "PluginFiles", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, PluginFiles), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_PluginFiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_PluginFiles_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_ContentBrowserPrefix_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n\x09 * Directory for content to appear in content window. Be careful changing this!\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Directory for content to appear in content window. Be careful changing this!" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_ContentBrowserPrefix = { "ContentBrowserPrefix", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, ContentBrowserPrefix), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_ContentBrowserPrefix_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_ContentBrowserPrefix_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_ForcePlatformName_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n\x09 * Force platform directory name, or leave empty for automatic (Desktop/Mobile/PS4/XBoxOne)\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Force platform directory name, or leave empty for automatic (Desktop/Mobile/PS4/XBoxOne)" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_ForcePlatformName = { "ForcePlatformName", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, ForcePlatformName), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_ForcePlatformName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_ForcePlatformName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_MasterBankName_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n\x09 * Name of master bank.  The default in Studio is \"Master Bank\".\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Name of master bank.  The default in Studio is \"Master Bank\"." },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_MasterBankName = { "MasterBankName", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, MasterBankName), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_MasterBankName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_MasterBankName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_SkipLoadBankName_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n\x09 * Skip bank files of the given name.\n\x09 * Can be used to load all banks except for a certain set, such as localization banks.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Skip bank files of the given name.\nCan be used to load all banks except for a certain set, such as localization banks." },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_SkipLoadBankName = { "SkipLoadBankName", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, SkipLoadBankName), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_SkipLoadBankName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_SkipLoadBankName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_StudioBankKey_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/*\n    * Specify the key for loading sounds from encrypted banks.\n\x09*/" },
		{ "DisplayName", "Encryption Key" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "* Specify the key for loading sounds from encrypted banks." },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_StudioBankKey = { "StudioBankKey", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, StudioBankKey), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_StudioBankKey_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_StudioBankKey_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_WavWriterPath_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n\x09* Force wav writer output, for debugging only.  Setting this will prevent normal sound output!\n\x09*/" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Force wav writer output, for debugging only.  Setting this will prevent normal sound output!" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_WavWriterPath = { "WavWriterPath", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, WavWriterPath), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_WavWriterPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_WavWriterPath_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_LoggingLevel_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/*\n    * Specify the logging level to use in a debug/development build.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "* Specify the logging level to use in a debug/development build." },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_LoggingLevel = { "LoggingLevel", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, LoggingLevel), Z_Construct_UEnum_FMODStudio_EFMODLogging, METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_LoggingLevel_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_LoggingLevel_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_OcclusionParameter_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n    * Name of the parameter used in Studio to control Occlusion effects.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Name of the parameter used in Studio to control Occlusion effects." },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_OcclusionParameter = { "OcclusionParameter", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, OcclusionParameter), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_OcclusionParameter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_OcclusionParameter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_AmbientVolumeParameter_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n    * Name of the parameter used in Studio to control Ambient volume.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Name of the parameter used in Studio to control Ambient volume." },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_AmbientVolumeParameter = { "AmbientVolumeParameter", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, AmbientVolumeParameter), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_AmbientVolumeParameter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_AmbientVolumeParameter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODSettings_Statics::NewProp_AmbientLPFParameter_MetaData[] = {
		{ "Category", "Advanced" },
		{ "Comment", "/**\n    * Name of the parameter used in Studio to control Ambient LPF effects.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODSettings.h" },
		{ "ToolTip", "Name of the parameter used in Studio to control Ambient LPF effects." },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODSettings_Statics::NewProp_AmbientLPFParameter = { "AmbientLPFParameter", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODSettings, AmbientLPFParameter), METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::NewProp_AmbientLPFParameter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::NewProp_AmbientLPFParameter_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFMODSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllBanks,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLoadAllSampleData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableLiveUpdate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableEditorLiveUpdate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_BankOutputDirectory,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_OutputFormat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_Locales_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_Locales,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_bVol0Virtual,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_Vol0VirtualLevel,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_SampleRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_bMatchHardwareSampleRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_RealChannelCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_TotalChannelCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_DSPBufferLength,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_DSPBufferCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_FileBufferSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_StudioUpdatePeriod,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_InitialOutputDriverName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_bLockAllBuses,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_MemoryPoolSizes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_LiveUpdatePort,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_EditorLiveUpdatePort,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_ReloadBanksDelay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_bEnableMemoryTracking,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_PluginFiles_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_PluginFiles,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_ContentBrowserPrefix,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_ForcePlatformName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_MasterBankName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_SkipLoadBankName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_StudioBankKey,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_WavWriterPath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_LoggingLevel,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_OcclusionParameter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_AmbientVolumeParameter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODSettings_Statics::NewProp_AmbientLPFParameter,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODSettings_Statics::ClassParams = {
		&UFMODSettings::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UFMODSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::PropPointers),
		0,
		0x001000A6u,
		METADATA_PARAMS(Z_Construct_UClass_UFMODSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODSettings, 4228141306);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODSettings>()
	{
		return UFMODSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODSettings(Z_Construct_UClass_UFMODSettings, &UFMODSettings::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
