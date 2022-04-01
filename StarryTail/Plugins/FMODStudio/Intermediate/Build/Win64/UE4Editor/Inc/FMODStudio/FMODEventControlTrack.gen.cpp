// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Private/Sequencer/FMODEventControlTrack.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODEventControlTrack() {}
// Cross Module References
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEventControlTrack_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEventControlTrack();
	MOVIESCENE_API UClass* Z_Construct_UClass_UMovieSceneNameableTrack();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
	MOVIESCENE_API UClass* Z_Construct_UClass_UMovieSceneSection_NoRegister();
	MOVIESCENE_API UClass* Z_Construct_UClass_UMovieSceneTrackTemplateProducer_NoRegister();
// End Cross Module References
	void UFMODEventControlTrack::StaticRegisterNativesUFMODEventControlTrack()
	{
	}
	UClass* Z_Construct_UClass_UFMODEventControlTrack_NoRegister()
	{
		return UFMODEventControlTrack::StaticClass();
	}
	struct Z_Construct_UClass_UFMODEventControlTrack_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ControlSections_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ControlSections_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ControlSections;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODEventControlTrack_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UMovieSceneNameableTrack,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODEventControlTrack_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/** Handles control of an FMOD Event */" },
		{ "IncludePath", "Sequencer/FMODEventControlTrack.h" },
		{ "ModuleRelativePath", "Private/Sequencer/FMODEventControlTrack.h" },
		{ "ToolTip", "Handles control of an FMOD Event" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UFMODEventControlTrack_Statics::NewProp_ControlSections_Inner = { "ControlSections", nullptr, (EPropertyFlags)0x0000000000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UMovieSceneSection_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODEventControlTrack_Statics::NewProp_ControlSections_MetaData[] = {
		{ "Comment", "/** List of all event control sections. */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Private/Sequencer/FMODEventControlTrack.h" },
		{ "ToolTip", "List of all event control sections." },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFMODEventControlTrack_Statics::NewProp_ControlSections = { "ControlSections", nullptr, (EPropertyFlags)0x0040008000000008, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODEventControlTrack, ControlSections), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFMODEventControlTrack_Statics::NewProp_ControlSections_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODEventControlTrack_Statics::NewProp_ControlSections_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFMODEventControlTrack_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODEventControlTrack_Statics::NewProp_ControlSections_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODEventControlTrack_Statics::NewProp_ControlSections,
	};
		const UE4CodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_UFMODEventControlTrack_Statics::InterfaceParams[] = {
			{ Z_Construct_UClass_UMovieSceneTrackTemplateProducer_NoRegister, (int32)VTABLE_OFFSET(UFMODEventControlTrack, IMovieSceneTrackTemplateProducer), false },
		};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODEventControlTrack_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODEventControlTrack>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODEventControlTrack_Statics::ClassParams = {
		&UFMODEventControlTrack::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UFMODEventControlTrack_Statics::PropPointers,
		InterfaceParams,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UFMODEventControlTrack_Statics::PropPointers),
		UE_ARRAY_COUNT(InterfaceParams),
		0x00A800A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFMODEventControlTrack_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODEventControlTrack_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODEventControlTrack()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODEventControlTrack_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODEventControlTrack, 4214021129);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODEventControlTrack>()
	{
		return UFMODEventControlTrack::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODEventControlTrack(Z_Construct_UClass_UFMODEventControlTrack, &UFMODEventControlTrack::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODEventControlTrack"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODEventControlTrack);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
