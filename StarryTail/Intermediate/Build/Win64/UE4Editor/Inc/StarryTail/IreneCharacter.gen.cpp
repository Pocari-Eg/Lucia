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
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	STARRYTAIL_API UScriptStruct* Z_Construct_UScriptStruct_FPlayerCharacterDataStruct();
	ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
	STARRYTAIL_API UEnum* Z_Construct_UEnum_StarryTail_EAttributeKeyword();
	UMG_API UClass* Z_Construct_UClass_UWidgetComponent_NoRegister();
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SpringArmComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SpringArmComp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CameraComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CameraComp;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_MoveKey_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MoveKey_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_MoveKey;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterDataStruct_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CharacterDataStruct;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Weapon_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Weapon;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Type;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AttributeWidget_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AttributeWidget;
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AIreneCharacter_Statics::NewProp_SpringArmComp_MetaData[] = {
		{ "Category", "IreneCharacter" },
		{ "Comment", "// \xc4\xab?\xde\xb6? ?\xcf\xb0? \xc4\xab?\xde\xb6?\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "IreneCharacter.h" },
		{ "ToolTip", "\xc4\xab?\xde\xb6? ?\xcf\xb0? \xc4\xab?\xde\xb6?" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIreneCharacter_Statics::NewProp_SpringArmComp = { "SpringArmComp", nullptr, (EPropertyFlags)0x0040000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AIreneCharacter, SpringArmComp), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_SpringArmComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_SpringArmComp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CameraComp_MetaData[] = {
		{ "Category", "IreneCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "IreneCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CameraComp = { "CameraComp", nullptr, (EPropertyFlags)0x0040000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AIreneCharacter, CameraComp), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CameraComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CameraComp_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_AIreneCharacter_Statics::NewProp_MoveKey_Inner = { "MoveKey", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AIreneCharacter_Statics::NewProp_MoveKey_MetaData[] = {
		{ "Category", "IreneCharacter" },
		{ "Comment", "// ?????\xd3\xbf? ?????\xcf\xb4? \xc5\xb0 0: ????, 1: ?\xc8\xb1?, 2: ?\xde\xb8???\n" },
		{ "ModuleRelativePath", "IreneCharacter.h" },
		{ "ToolTip", "?????\xd3\xbf? ?????\xcf\xb4? \xc5\xb0 0: ????, 1: ?\xc8\xb1?, 2: ?\xde\xb8???" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AIreneCharacter_Statics::NewProp_MoveKey = { "MoveKey", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AIreneCharacter, MoveKey), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_MoveKey_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_MoveKey_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CharacterDataStruct_MetaData[] = {
		{ "Category", "IreneCharacter" },
		{ "Comment", "// \xc4\xb3???\xcd\xb0? ?????\xcf\xb4? ????, ???? ???? ?\xd6\xb4? ????\xc3\xbc\n" },
		{ "ModuleRelativePath", "IreneCharacter.h" },
		{ "ToolTip", "\xc4\xb3???\xcd\xb0? ?????\xcf\xb4? ????, ???? ???? ?\xd6\xb4? ????\xc3\xbc" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CharacterDataStruct = { "CharacterDataStruct", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AIreneCharacter, CharacterDataStruct), Z_Construct_UScriptStruct_FPlayerCharacterDataStruct, METADATA_PARAMS(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CharacterDataStruct_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CharacterDataStruct_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Weapon_MetaData[] = {
		{ "Category", "IreneCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "IreneCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Weapon = { "Weapon", nullptr, (EPropertyFlags)0x0040000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AIreneCharacter, Weapon), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Weapon_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Weapon_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Type_MetaData[] = {
		{ "Category", "IreneCharacter" },
		{ "Comment", "//\xc4\xb3???? ?\xd3\xbc?\n" },
		{ "ModuleRelativePath", "IreneCharacter.h" },
		{ "ToolTip", "\xc4\xb3???? ?\xd3\xbc?" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AIreneCharacter, Type), Z_Construct_UEnum_StarryTail_EAttributeKeyword, METADATA_PARAMS(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Type_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Type_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AIreneCharacter_Statics::NewProp_AttributeWidget_MetaData[] = {
		{ "Category", "UI" },
		{ "Comment", "//?\xd3\xbc? ui\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "IreneCharacter.h" },
		{ "ToolTip", "?\xd3\xbc? ui" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIreneCharacter_Statics::NewProp_AttributeWidget = { "AttributeWidget", nullptr, (EPropertyFlags)0x00400000000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AIreneCharacter, AttributeWidget), Z_Construct_UClass_UWidgetComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_AttributeWidget_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AIreneCharacter_Statics::NewProp_AttributeWidget_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AIreneCharacter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIreneCharacter_Statics::NewProp_SpringArmComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CameraComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIreneCharacter_Statics::NewProp_MoveKey_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIreneCharacter_Statics::NewProp_MoveKey,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIreneCharacter_Statics::NewProp_CharacterDataStruct,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Weapon,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Type_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIreneCharacter_Statics::NewProp_Type,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIreneCharacter_Statics::NewProp_AttributeWidget,
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
	IMPLEMENT_CLASS(AIreneCharacter, 4234497134);
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
