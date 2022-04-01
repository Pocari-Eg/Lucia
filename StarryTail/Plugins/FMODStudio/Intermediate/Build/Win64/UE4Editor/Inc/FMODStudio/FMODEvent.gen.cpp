// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODEvent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODEvent() {}
// Cross Module References
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEvent_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEvent();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAsset();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
// End Cross Module References
	void UFMODEvent::StaticRegisterNativesUFMODEvent()
	{
	}
	UClass* Z_Construct_UClass_UFMODEvent_NoRegister()
	{
		return UFMODEvent::StaticClass();
	}
	struct Z_Construct_UClass_UFMODEvent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODEvent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFMODAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODEvent_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * FMOD Event Asset.\n */" },
		{ "IncludePath", "FMODEvent.h" },
		{ "ModuleRelativePath", "Classes/FMODEvent.h" },
		{ "ToolTip", "FMOD Event Asset." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODEvent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODEvent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODEvent_Statics::ClassParams = {
		&UFMODEvent::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UFMODEvent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODEvent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODEvent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODEvent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODEvent, 245563929);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODEvent>()
	{
		return UFMODEvent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODEvent(Z_Construct_UClass_UFMODEvent, &UFMODEvent::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODEvent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODEvent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
