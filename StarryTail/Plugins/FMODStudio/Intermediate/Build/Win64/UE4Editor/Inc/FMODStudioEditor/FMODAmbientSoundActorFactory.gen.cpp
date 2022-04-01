// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudioEditor/Classes/FMODAmbientSoundActorFactory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODAmbientSoundActorFactory() {}
// Cross Module References
	FMODSTUDIOEDITOR_API UClass* Z_Construct_UClass_UFMODAmbientSoundActorFactory_NoRegister();
	FMODSTUDIOEDITOR_API UClass* Z_Construct_UClass_UFMODAmbientSoundActorFactory();
	UNREALED_API UClass* Z_Construct_UClass_UActorFactory();
	UPackage* Z_Construct_UPackage__Script_FMODStudioEditor();
// End Cross Module References
	void UFMODAmbientSoundActorFactory::StaticRegisterNativesUFMODAmbientSoundActorFactory()
	{
	}
	UClass* Z_Construct_UClass_UFMODAmbientSoundActorFactory_NoRegister()
	{
		return UFMODAmbientSoundActorFactory::StaticClass();
	}
	struct Z_Construct_UClass_UFMODAmbientSoundActorFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODAmbientSoundActorFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudioEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAmbientSoundActorFactory_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/** FMOD Ambient Sound Actor Factory.\n*/" },
		{ "HideCategories", "Object Object" },
		{ "IncludePath", "FMODAmbientSoundActorFactory.h" },
		{ "ModuleRelativePath", "Classes/FMODAmbientSoundActorFactory.h" },
		{ "ToolTip", "FMOD Ambient Sound Actor Factory." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODAmbientSoundActorFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODAmbientSoundActorFactory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODAmbientSoundActorFactory_Statics::ClassParams = {
		&UFMODAmbientSoundActorFactory::StaticClass,
		"Editor",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000830ACu,
		METADATA_PARAMS(Z_Construct_UClass_UFMODAmbientSoundActorFactory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAmbientSoundActorFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODAmbientSoundActorFactory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODAmbientSoundActorFactory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODAmbientSoundActorFactory, 2689523854);
	template<> FMODSTUDIOEDITOR_API UClass* StaticClass<UFMODAmbientSoundActorFactory>()
	{
		return UFMODAmbientSoundActorFactory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODAmbientSoundActorFactory(Z_Construct_UClass_UFMODAmbientSoundActorFactory, &UFMODAmbientSoundActorFactory::StaticClass, TEXT("/Script/FMODStudioEditor"), TEXT("UFMODAmbientSoundActorFactory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODAmbientSoundActorFactory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
