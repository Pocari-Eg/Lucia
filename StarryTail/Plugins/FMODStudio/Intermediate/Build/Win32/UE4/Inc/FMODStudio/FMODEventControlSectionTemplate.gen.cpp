// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Private/Sequencer/FMODEventControlSectionTemplate.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODEventControlSectionTemplate() {}
// Cross Module References
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
	MOVIESCENE_API UScriptStruct* Z_Construct_UScriptStruct_FMovieSceneEvalTemplate();
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FFMODEventControlChannel();
// End Cross Module References

static_assert(std::is_polymorphic<FFMODEventControlSectionTemplate>() == std::is_polymorphic<FMovieSceneEvalTemplate>(), "USTRUCT FFMODEventControlSectionTemplate cannot be polymorphic unless super FMovieSceneEvalTemplate is polymorphic");

class UScriptStruct* FFMODEventControlSectionTemplate::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FMODSTUDIO_API uint32 Get_Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate, Z_Construct_UPackage__Script_FMODStudio(), TEXT("FMODEventControlSectionTemplate"), sizeof(FFMODEventControlSectionTemplate), Get_Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Hash());
	}
	return Singleton;
}
template<> FMODSTUDIO_API UScriptStruct* StaticStruct<FFMODEventControlSectionTemplate>()
{
	return FFMODEventControlSectionTemplate::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FFMODEventControlSectionTemplate(FFMODEventControlSectionTemplate::StaticStruct, TEXT("/Script/FMODStudio"), TEXT("FMODEventControlSectionTemplate"), false, nullptr, nullptr);
static struct FScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventControlSectionTemplate
{
	FScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventControlSectionTemplate()
	{
		UScriptStruct::DeferCppStructOps<FFMODEventControlSectionTemplate>(FName(TEXT("FMODEventControlSectionTemplate")));
	}
} ScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventControlSectionTemplate;
	struct Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ControlKeys_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ControlKeys;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/Sequencer/FMODEventControlSectionTemplate.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFMODEventControlSectionTemplate>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::NewProp_ControlKeys_MetaData[] = {
		{ "ModuleRelativePath", "Private/Sequencer/FMODEventControlSectionTemplate.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::NewProp_ControlKeys = { "ControlKeys", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFMODEventControlSectionTemplate, ControlKeys), Z_Construct_UScriptStruct_FFMODEventControlChannel, METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::NewProp_ControlKeys_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::NewProp_ControlKeys_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::NewProp_ControlKeys,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
		Z_Construct_UScriptStruct_FMovieSceneEvalTemplate,
		&NewStructOps,
		"FMODEventControlSectionTemplate",
		sizeof(FFMODEventControlSectionTemplate),
		alignof(FFMODEventControlSectionTemplate),
		Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000005),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("FMODEventControlSectionTemplate"), sizeof(FFMODEventControlSectionTemplate), Get_Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FFMODEventControlSectionTemplate_Hash() { return 648489761U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
