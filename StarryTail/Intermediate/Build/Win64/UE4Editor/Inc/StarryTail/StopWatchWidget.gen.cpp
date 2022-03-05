// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/UI/StopWatchWidget.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStopWatchWidget() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_UStopWatchWidget_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_UStopWatchWidget();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
	STARRYTAIL_API UEnum* Z_Construct_UEnum_StarryTail_WatchState();
// End Cross Module References
	void UStopWatchWidget::StaticRegisterNativesUStopWatchWidget()
	{
	}
	UClass* Z_Construct_UClass_UStopWatchWidget_NoRegister()
	{
		return UStopWatchWidget::StaticClass();
	}
	struct Z_Construct_UClass_UStopWatchWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TimerMinutes_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TimerMinutes;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TimerSeconds_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TimerSeconds;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_CurrentState_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentState_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_CurrentState;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStopWatchWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStopWatchWidget_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *\n */" },
		{ "IncludePath", "UI/StopWatchWidget.h" },
		{ "ModuleRelativePath", "UI/StopWatchWidget.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_TimerMinutes_MetaData[] = {
		{ "Category", "StopWatchWidget" },
		{ "ModuleRelativePath", "UI/StopWatchWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_TimerMinutes = { "TimerMinutes", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStopWatchWidget, TimerMinutes), METADATA_PARAMS(Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_TimerMinutes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_TimerMinutes_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_TimerSeconds_MetaData[] = {
		{ "Category", "StopWatchWidget" },
		{ "ModuleRelativePath", "UI/StopWatchWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_TimerSeconds = { "TimerSeconds", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStopWatchWidget, TimerSeconds), METADATA_PARAMS(Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_TimerSeconds_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_TimerSeconds_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_CurrentState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_CurrentState_MetaData[] = {
		{ "Category", "StopWatchWidget" },
		{ "ModuleRelativePath", "UI/StopWatchWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_CurrentState = { "CurrentState", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStopWatchWidget, CurrentState), Z_Construct_UEnum_StarryTail_WatchState, METADATA_PARAMS(Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_CurrentState_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_CurrentState_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStopWatchWidget_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_TimerMinutes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_TimerSeconds,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_CurrentState_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStopWatchWidget_Statics::NewProp_CurrentState,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStopWatchWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStopWatchWidget>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStopWatchWidget_Statics::ClassParams = {
		&UStopWatchWidget::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStopWatchWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStopWatchWidget_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStopWatchWidget_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStopWatchWidget_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStopWatchWidget()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStopWatchWidget_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStopWatchWidget, 2966793627);
	template<> STARRYTAIL_API UClass* StaticClass<UStopWatchWidget>()
	{
		return UStopWatchWidget::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStopWatchWidget(Z_Construct_UClass_UStopWatchWidget, &UStopWatchWidget::StaticClass, TEXT("/Script/StarryTail"), TEXT("UStopWatchWidget"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStopWatchWidget);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
