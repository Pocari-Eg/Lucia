// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/StopWatch.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStopWatch() {}
// Cross Module References
	STARRYTAIL_API UClass* Z_Construct_UClass_AStopWatch_NoRegister();
	STARRYTAIL_API UClass* Z_Construct_UClass_AStopWatch();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	STARRYTAIL_API UClass* Z_Construct_UClass_UStopWatchWidget_NoRegister();
// End Cross Module References
	void AStopWatch::StaticRegisterNativesAStopWatch()
	{
	}
	UClass* Z_Construct_UClass_AStopWatch_NoRegister()
	{
		return AStopWatch::StaticClass();
	}
	struct Z_Construct_UClass_AStopWatch_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Minutes_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_Minutes;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Seconds_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_Seconds;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TimerWidgetClass_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_TimerWidgetClass;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TimerWidget_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_TimerWidget;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AStopWatch_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStopWatch_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "StopWatch.h" },
		{ "ModuleRelativePath", "StopWatch.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStopWatch_Statics::NewProp_Minutes_MetaData[] = {
		{ "Category", "TIMER" },
		{ "ModuleRelativePath", "StopWatch.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AStopWatch_Statics::NewProp_Minutes = { "Minutes", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AStopWatch, Minutes), METADATA_PARAMS(Z_Construct_UClass_AStopWatch_Statics::NewProp_Minutes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AStopWatch_Statics::NewProp_Minutes_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStopWatch_Statics::NewProp_Seconds_MetaData[] = {
		{ "Category", "TIMER" },
		{ "Comment", "// ??\n" },
		{ "ModuleRelativePath", "StopWatch.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AStopWatch_Statics::NewProp_Seconds = { "Seconds", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AStopWatch, Seconds), METADATA_PARAMS(Z_Construct_UClass_AStopWatch_Statics::NewProp_Seconds_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AStopWatch_Statics::NewProp_Seconds_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStopWatch_Statics::NewProp_TimerWidgetClass_MetaData[] = {
		{ "Category", "UI" },
		{ "ModuleRelativePath", "StopWatch.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AStopWatch_Statics::NewProp_TimerWidgetClass = { "TimerWidgetClass", nullptr, (EPropertyFlags)0x0024080000010005, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AStopWatch, TimerWidgetClass), Z_Construct_UClass_UStopWatchWidget_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AStopWatch_Statics::NewProp_TimerWidgetClass_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AStopWatch_Statics::NewProp_TimerWidgetClass_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStopWatch_Statics::NewProp_TimerWidget_MetaData[] = {
		{ "Comment", "// TimerHandle;\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "StopWatch.h" },
		{ "ToolTip", "TimerHandle;" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStopWatch_Statics::NewProp_TimerWidget = { "TimerWidget", nullptr, (EPropertyFlags)0x0040000000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AStopWatch, TimerWidget), Z_Construct_UClass_UStopWatchWidget_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AStopWatch_Statics::NewProp_TimerWidget_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AStopWatch_Statics::NewProp_TimerWidget_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AStopWatch_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStopWatch_Statics::NewProp_Minutes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStopWatch_Statics::NewProp_Seconds,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStopWatch_Statics::NewProp_TimerWidgetClass,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStopWatch_Statics::NewProp_TimerWidget,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AStopWatch_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AStopWatch>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AStopWatch_Statics::ClassParams = {
		&AStopWatch::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AStopWatch_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AStopWatch_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AStopWatch_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AStopWatch_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AStopWatch()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AStopWatch_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AStopWatch, 3768462044);
	template<> STARRYTAIL_API UClass* StaticClass<AStopWatch>()
	{
		return AStopWatch::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AStopWatch(Z_Construct_UClass_AStopWatch, &AStopWatch::StaticClass, TEXT("/Script/StarryTail"), TEXT("AStopWatch"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AStopWatch);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
