// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/IreneCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeIreneCharacter() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_AIreneCharacter_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_AIreneCharacter();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
	STARRYTAIL_API UScriptStruct* Z_Construct_UScriptStruct_FPlayerCharacterDataStruct();
// End Cross Module References
	void AIreneCharacter::StaticRegisterNativesAIreneCharacter()
	{
	}
	UClass* Z_Construct_UClass_AIreneCharacter_NoRegister()
	{
		return AIreneCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AIreneCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterDataStruct_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CharacterDataStruct;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AIreneCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AIreneCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "IreneCharacter.h" },
		{ "ModuleRelativePath", "IreneCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CharacterDataStruct_MetaData[] = {
		{ "Category", "IreneCharacter" },
		{ "Comment", "// \xc4\xb3???\xcd\xb0? ?????\xcf\xb4? ????, ???? ???? ?\xd6\xb4? ????\xc3\xbc\n" },
		{ "ModuleRelativePath", "IreneCharacter.h" },
		{ "ToolTip", "\xc4\xb3???\xcd\xb0? ?????\xcf\xb4? ????, ???? ???? ?\xd6\xb4? ????\xc3\xbc" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CharacterDataStruct = { "CharacterDataStruct", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AIreneCharacter, CharacterDataStruct), Z_Construct_UScriptStruct_FPlayerCharacterDataStruct, METADATA_PARAMS(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CharacterDataStruct_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CharacterDataStruct_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AIreneCharacter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CharacterDataStruct,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AIreneCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AIreneCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AIreneCharacter_Statics::ClassParams = {
		&AIreneCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AIreneCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AIreneCharacter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AIreneCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AIreneCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AIreneCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AIreneCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AIreneCharacter, 693466750);
	template<> STARRYTAIL_API UClass* StaticClass<AIreneCharacter>()
	{
		return AIreneCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AIreneCharacter(Z_Construct_UClass_AIreneCharacter, &AIreneCharacter::StaticClass, TEXT("/Script/StarryTail"), TEXT("AIreneCharacter"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AIreneCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
