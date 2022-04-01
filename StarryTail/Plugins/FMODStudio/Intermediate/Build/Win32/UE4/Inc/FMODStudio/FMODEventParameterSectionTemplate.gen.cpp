// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Private/Sequencer/FMODEventParameterSectionTemplate.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODEventParameterSectionTemplate() {}
// Cross Module References
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
	MOVIESCENETRACKS_API UScriptStruct* Z_Construct_UScriptStruct_FMovieSceneParameterSectionTemplate();
// End Cross Module References

static_assert(std::is_polymorphic<FFMODEventParameterSectionTemplate>() == std::is_polymorphic<FMovieSceneParameterSectionTemplate>(), "USTRUCT FFMODEventParameterSectionTemplate cannot be polymorphic unless super FMovieSceneParameterSectionTemplate is polymorphic");

class UScriptStruct* FFMODEventParameterSectionTemplate::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FMODSTUDIO_API uint32 Get_Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate, Z_Construct_UPackage__Script_FMODStudio(), TEXT("FMODEventParameterSectionTemplate"), sizeof(FFMODEventParameterSectionTemplate), Get_Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Hash());
	}
	return Singleton;
}
template<> FMODSTUDIO_API UScriptStruct* StaticStruct<FFMODEventParameterSectionTemplate>()
{
	return FFMODEventParameterSectionTemplate::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FFMODEventParameterSectionTemplate(FFMODEventParameterSectionTemplate::StaticStruct, TEXT("/Script/FMODStudio"), TEXT("FMODEventParameterSectionTemplate"), false, nullptr, nullptr);
static struct FScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventParameterSectionTemplate
{
	FScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventParameterSectionTemplate()
	{
		UScriptStruct::DeferCppStructOps<FFMODEventParameterSectionTemplate>(FName(TEXT("FMODEventParameterSectionTemplate")));
	}
} ScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventParameterSectionTemplate;
	struct Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/Sequencer/FMODEventParameterSectionTemplate.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFMODEventParameterSectionTemplate>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
		Z_Construct_UScriptStruct_FMovieSceneParameterSectionTemplate,
		&NewStructOps,
		"FMODEventParameterSectionTemplate",
		sizeof(FFMODEventParameterSectionTemplate),
		alignof(FFMODEventParameterSectionTemplate),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000005),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("FMODEventParameterSectionTemplate"), sizeof(FFMODEventParameterSectionTemplate), Get_Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FFMODEventParameterSectionTemplate_Hash() { return 3530684157U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
