// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/MyAnimInstance.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyAnimInstance() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_UMyAnimInstance_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_UMyAnimInstance();
	ENGINE_API UClass* Z_Construct_UClass_UAnimInstance();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
// End Cross Module References
	void UMyAnimInstance::StaticRegisterNativesUMyAnimInstance()
	{
	}
	UClass* Z_Construct_UClass_UMyAnimInstance_NoRegister()
	{
		return UMyAnimInstance::StaticClass();
	}
	struct Z_Construct_UClass_UMyAnimInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AttackCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_AttackCount;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMyAnimInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAnimInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMyAnimInstance_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "AnimInstance" },
		{ "IncludePath", "MyAnimInstance.h" },
		{ "ModuleRelativePath", "MyAnimInstance.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMyAnimInstance_Statics::NewProp_AttackCount_MetaData[] = {
		{ "Category", "MyAnimInstance" },
		{ "Comment", "// ???? \xc8\xbd??\n" },
		{ "ModuleRelativePath", "MyAnimInstance.h" },
		{ "ToolTip", "???? \xc8\xbd??" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UMyAnimInstance_Statics::NewProp_AttackCount = { "AttackCount", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UMyAnimInstance, AttackCount), nullptr, METADATA_PARAMS(Z_Construct_UClass_UMyAnimInstance_Statics::NewProp_AttackCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UMyAnimInstance_Statics::NewProp_AttackCount_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMyAnimInstance_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMyAnimInstance_Statics::NewProp_AttackCount,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMyAnimInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMyAnimInstance>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UMyAnimInstance_Statics::ClassParams = {
		&UMyAnimInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UMyAnimInstance_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UMyAnimInstance_Statics::PropPointers),
		0,
		0x009000A8u,
		METADATA_PARAMS(Z_Construct_UClass_UMyAnimInstance_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UMyAnimInstance_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UMyAnimInstance()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UMyAnimInstance_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UMyAnimInstance, 2538545060);
	template<> STARRYTAIL_API UClass* StaticClass<UMyAnimInstance>()
	{
		return UMyAnimInstance::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UMyAnimInstance(Z_Construct_UClass_UMyAnimInstance, &UMyAnimInstance::StaticClass, TEXT("/Script/StarryTail"), TEXT("UMyAnimInstance"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMyAnimInstance);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
