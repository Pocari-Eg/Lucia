// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODAnimNotifyPlay.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODAnimNotifyPlay() {}
// Cross Module References
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAnimNotifyPlay_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAnimNotifyPlay();
	ENGINE_API UClass* Z_Construct_UClass_UAnimNotify();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEvent_NoRegister();
// End Cross Module References
	void UFMODAnimNotifyPlay::StaticRegisterNativesUFMODAnimNotifyPlay()
	{
	}
	UClass* Z_Construct_UClass_UFMODAnimNotifyPlay_NoRegister()
	{
		return UFMODAnimNotifyPlay::StaticClass();
	}
	struct Z_Construct_UClass_UFMODAnimNotifyPlay_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bFollow_MetaData[];
#endif
		static void NewProp_bFollow_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bFollow;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AttachName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AttachName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Event_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Event;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAnimNotify,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::Class_MetaDataParams[] = {
		{ "DisplayName", "Play FMOD Event" },
		{ "HideCategories", "Object Object" },
		{ "IncludePath", "FMODAnimNotifyPlay.h" },
		{ "ModuleRelativePath", "Classes/FMODAnimNotifyPlay.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_bFollow_MetaData[] = {
		{ "Category", "FMOD Anim Notify" },
		{ "Comment", "// If this sound should follow its owner\n" },
		{ "ModuleRelativePath", "Classes/FMODAnimNotifyPlay.h" },
		{ "ToolTip", "If this sound should follow its owner" },
	};
#endif
	void Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_bFollow_SetBit(void* Obj)
	{
		((UFMODAnimNotifyPlay*)Obj)->bFollow = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_bFollow = { "bFollow", nullptr, (EPropertyFlags)0x0010000000000011, UE4CodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(UFMODAnimNotifyPlay), &Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_bFollow_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_bFollow_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_bFollow_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_AttachName_MetaData[] = {
		{ "Category", "FMOD Anim Notify" },
		{ "Comment", "// Socket or bone name to attach sound to\n" },
		{ "EditCondition", "bFollow" },
		{ "ModuleRelativePath", "Classes/FMODAnimNotifyPlay.h" },
		{ "ToolTip", "Socket or bone name to attach sound to" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_AttachName = { "AttachName", nullptr, (EPropertyFlags)0x0010000000000011, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODAnimNotifyPlay, AttachName), METADATA_PARAMS(Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_AttachName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_AttachName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_Event_MetaData[] = {
		{ "Category", "FMOD Anim Notify" },
		{ "Comment", "// Sound to Play\n" },
		{ "ModuleRelativePath", "Classes/FMODAnimNotifyPlay.h" },
		{ "ToolTip", "Sound to Play" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODAnimNotifyPlay, Event), Z_Construct_UClass_UFMODEvent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_Event_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_Event_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_bFollow,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_AttachName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::NewProp_Event,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODAnimNotifyPlay>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::ClassParams = {
		&UFMODAnimNotifyPlay::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::PropPointers),
		0,
		0x001120A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODAnimNotifyPlay()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODAnimNotifyPlay_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODAnimNotifyPlay, 3438558098);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODAnimNotifyPlay>()
	{
		return UFMODAnimNotifyPlay::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODAnimNotifyPlay(Z_Construct_UClass_UFMODAnimNotifyPlay, &UFMODAnimNotifyPlay::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODAnimNotifyPlay"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODAnimNotifyPlay);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
