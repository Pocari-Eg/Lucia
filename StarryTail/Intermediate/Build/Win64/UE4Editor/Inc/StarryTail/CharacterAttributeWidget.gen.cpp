// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/UI/CharacterAttributeWidget.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCharacterAttributeWidget() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_UCharacterAttributeWidget_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_UCharacterAttributeWidget();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
	STARRYTAIL_API UEnum* Z_Construct_UEnum_StarryTail_EAttributeKeyword();
// End Cross Module References
	void UCharacterAttributeWidget::StaticRegisterNativesUCharacterAttributeWidget()
	{
	}
	UClass* Z_Construct_UClass_UCharacterAttributeWidget_NoRegister()
	{
		return UCharacterAttributeWidget::StaticClass();
	}
	struct Z_Construct_UClass_UCharacterAttributeWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_CurrentAttribute_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentAttribute_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_CurrentAttribute;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCharacterAttributeWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterAttributeWidget_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "UI/CharacterAttributeWidget.h" },
		{ "ModuleRelativePath", "UI/CharacterAttributeWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCharacterAttributeWidget_Statics::NewProp_CurrentAttribute_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterAttributeWidget_Statics::NewProp_CurrentAttribute_MetaData[] = {
		{ "Category", "CharacterAttributeWidget" },
		{ "ModuleRelativePath", "UI/CharacterAttributeWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCharacterAttributeWidget_Statics::NewProp_CurrentAttribute = { "CurrentAttribute", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCharacterAttributeWidget, CurrentAttribute), Z_Construct_UEnum_StarryTail_EAttributeKeyword, METADATA_PARAMS(Z_Construct_UClass_UCharacterAttributeWidget_Statics::NewProp_CurrentAttribute_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAttributeWidget_Statics::NewProp_CurrentAttribute_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCharacterAttributeWidget_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterAttributeWidget_Statics::NewProp_CurrentAttribute_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterAttributeWidget_Statics::NewProp_CurrentAttribute,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCharacterAttributeWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCharacterAttributeWidget>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCharacterAttributeWidget_Statics::ClassParams = {
		&UCharacterAttributeWidget::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCharacterAttributeWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAttributeWidget_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCharacterAttributeWidget_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAttributeWidget_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCharacterAttributeWidget()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCharacterAttributeWidget_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCharacterAttributeWidget, 2987716962);
	template<> STARRYTAIL_API UClass* StaticClass<UCharacterAttributeWidget>()
	{
		return UCharacterAttributeWidget::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCharacterAttributeWidget(Z_Construct_UClass_UCharacterAttributeWidget, &UCharacterAttributeWidget::StaticClass, TEXT("/Script/StarryTail"), TEXT("UCharacterAttributeWidget"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCharacterAttributeWidget);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
