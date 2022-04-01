// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Private/Sequencer/FMODEventControlSection.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODEventControlSection() {}
// Cross Module References
	FMODSTUDIO_API UEnum* Z_Construct_UEnum_FMODStudio_EFMODEventControlKey();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FFMODEventControlChannel();
	MOVIESCENE_API UScriptStruct* Z_Construct_UScriptStruct_FMovieSceneByteChannel();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEventControlSection_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEventControlSection();
	MOVIESCENE_API UClass* Z_Construct_UClass_UMovieSceneSection();
// End Cross Module References
	static UEnum* EFMODEventControlKey_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_FMODStudio_EFMODEventControlKey, Z_Construct_UPackage__Script_FMODStudio(), TEXT("EFMODEventControlKey"));
		}
		return Singleton;
	}
	template<> FMODSTUDIO_API UEnum* StaticEnum<EFMODEventControlKey>()
	{
		return EFMODEventControlKey_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EFMODEventControlKey(EFMODEventControlKey_StaticEnum, TEXT("/Script/FMODStudio"), TEXT("EFMODEventControlKey"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_FMODStudio_EFMODEventControlKey_Hash() { return 3599606607U; }
	UEnum* Z_Construct_UEnum_FMODStudio_EFMODEventControlKey()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EFMODEventControlKey"), 0, Get_Z_Construct_UEnum_FMODStudio_EFMODEventControlKey_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EFMODEventControlKey::Stop", (int64)EFMODEventControlKey::Stop },
				{ "EFMODEventControlKey::Play", (int64)EFMODEventControlKey::Play },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Comment", "/** Defines the types of FMOD event control keys. */" },
				{ "ModuleRelativePath", "Private/Sequencer/FMODEventControlSection.h" },
				{ "Play.Name", "EFMODEventControlKey::Play" },
				{ "Stop.Name", "EFMODEventControlKey::Stop" },
				{ "ToolTip", "Defines the types of FMOD event control keys." },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_FMODStudio,
				nullptr,
				"EFMODEventControlKey",
				"EFMODEventControlKey",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}

static_assert(std::is_polymorphic<FFMODEventControlChannel>() == std::is_polymorphic<FMovieSceneByteChannel>(), "USTRUCT FFMODEventControlChannel cannot be polymorphic unless super FMovieSceneByteChannel is polymorphic");

class UScriptStruct* FFMODEventControlChannel::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FMODSTUDIO_API uint32 Get_Z_Construct_UScriptStruct_FFMODEventControlChannel_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FFMODEventControlChannel, Z_Construct_UPackage__Script_FMODStudio(), TEXT("FMODEventControlChannel"), sizeof(FFMODEventControlChannel), Get_Z_Construct_UScriptStruct_FFMODEventControlChannel_Hash());
	}
	return Singleton;
}
template<> FMODSTUDIO_API UScriptStruct* StaticStruct<FFMODEventControlChannel>()
{
	return FFMODEventControlChannel::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FFMODEventControlChannel(FFMODEventControlChannel::StaticStruct, TEXT("/Script/FMODStudio"), TEXT("FMODEventControlChannel"), false, nullptr, nullptr);
static struct FScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventControlChannel
{
	FScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventControlChannel()
	{
		UScriptStruct::DeferCppStructOps<FFMODEventControlChannel>(FName(TEXT("FMODEventControlChannel")));
	}
} ScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventControlChannel;
	struct Z_Construct_UScriptStruct_FFMODEventControlChannel_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODEventControlChannel_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/Sequencer/FMODEventControlSection.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFMODEventControlChannel_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFMODEventControlChannel>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFMODEventControlChannel_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
		Z_Construct_UScriptStruct_FMovieSceneByteChannel,
		&NewStructOps,
		"FMODEventControlChannel",
		sizeof(FFMODEventControlChannel),
		alignof(FFMODEventControlChannel),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODEventControlChannel_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODEventControlChannel_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFMODEventControlChannel()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FFMODEventControlChannel_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("FMODEventControlChannel"), sizeof(FFMODEventControlChannel), Get_Z_Construct_UScriptStruct_FFMODEventControlChannel_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FFMODEventControlChannel_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FFMODEventControlChannel_Hash() { return 3301280882U; }
	void UFMODEventControlSection::StaticRegisterNativesUFMODEventControlSection()
	{
	}
	UClass* Z_Construct_UClass_UFMODEventControlSection_NoRegister()
	{
		return UFMODEventControlSection::StaticClass();
	}
	struct Z_Construct_UClass_UFMODEventControlSection_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ControlKeys_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ControlKeys;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODEventControlSection_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UMovieSceneSection,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODEventControlSection_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/** FMOD Event control section */" },
		{ "IncludePath", "Sequencer/FMODEventControlSection.h" },
		{ "ModuleRelativePath", "Private/Sequencer/FMODEventControlSection.h" },
		{ "ToolTip", "FMOD Event control section" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODEventControlSection_Statics::NewProp_ControlKeys_MetaData[] = {
		{ "Comment", "/** Channel containing the event control keys */" },
		{ "ModuleRelativePath", "Private/Sequencer/FMODEventControlSection.h" },
		{ "ToolTip", "Channel containing the event control keys" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFMODEventControlSection_Statics::NewProp_ControlKeys = { "ControlKeys", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODEventControlSection, ControlKeys), Z_Construct_UScriptStruct_FFMODEventControlChannel, METADATA_PARAMS(Z_Construct_UClass_UFMODEventControlSection_Statics::NewProp_ControlKeys_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODEventControlSection_Statics::NewProp_ControlKeys_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFMODEventControlSection_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODEventControlSection_Statics::NewProp_ControlKeys,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODEventControlSection_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODEventControlSection>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODEventControlSection_Statics::ClassParams = {
		&UFMODEventControlSection::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UFMODEventControlSection_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UFMODEventControlSection_Statics::PropPointers),
		0,
		0x002800A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFMODEventControlSection_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODEventControlSection_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODEventControlSection()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODEventControlSection_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODEventControlSection, 3062802348);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODEventControlSection>()
	{
		return UFMODEventControlSection::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODEventControlSection(Z_Construct_UClass_UFMODEventControlSection, &UFMODEventControlSection::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODEventControlSection"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODEventControlSection);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
