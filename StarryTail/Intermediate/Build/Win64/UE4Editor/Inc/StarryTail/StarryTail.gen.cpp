// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/StarryTail.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStarryTail() {}
// Cross Module References
	STARRYTAIL_API UEnum* Z_Construct_UEnum_StarryTail_WatchState();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
	STARRYTAIL_API UEnum* Z_Construct_UEnum_StarryTail_EAttributeKeyword();
// End Cross Module References
	static UEnum* WatchState_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_StarryTail_WatchState, Z_Construct_UPackage__Script_StarryTail(), TEXT("WatchState"));
		}
		return Singleton;
	}
	template<> STARRYTAIL_API UEnum* StaticEnum<WatchState>()
	{
		return WatchState_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_WatchState(WatchState_StaticEnum, TEXT("/Script/StarryTail"), TEXT("WatchState"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_StarryTail_WatchState_Hash() { return 2266834081U; }
	UEnum* Z_Construct_UEnum_StarryTail_WatchState()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_StarryTail();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("WatchState"), 0, Get_Z_Construct_UEnum_StarryTail_WatchState_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "WatchState::e_Reset", (int64)WatchState::e_Reset },
				{ "WatchState::e_Pause", (int64)WatchState::e_Pause },
				{ "WatchState::e_Play", (int64)WatchState::e_Play },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Comment", "// \xc5\xb8?\xcc\xb8??? ???\xc2\xb8? ??\xc5\xb8???? ????\xc3\xbc\n" },
				{ "e_Pause.DisplayName", "PAUSE" },
				{ "e_Pause.Name", "WatchState::e_Pause" },
				{ "e_Play.DisplayName", "PLAY" },
				{ "e_Play.Name", "WatchState::e_Play" },
				{ "e_Reset.DisplayName", "RESET" },
				{ "e_Reset.Name", "WatchState::e_Reset" },
				{ "ModuleRelativePath", "StarryTail.h" },
				{ "ToolTip", "\xc5\xb8?\xcc\xb8??? ???\xc2\xb8? ??\xc5\xb8???? ????\xc3\xbc" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_StarryTail,
				nullptr,
				"WatchState",
				"WatchState",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* EAttributeKeyword_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_StarryTail_EAttributeKeyword, Z_Construct_UPackage__Script_StarryTail(), TEXT("EAttributeKeyword"));
		}
		return Singleton;
	}
	template<> STARRYTAIL_API UEnum* StaticEnum<EAttributeKeyword>()
	{
		return EAttributeKeyword_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EAttributeKeyword(EAttributeKeyword_StaticEnum, TEXT("/Script/StarryTail"), TEXT("EAttributeKeyword"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_StarryTail_EAttributeKeyword_Hash() { return 2774241557U; }
	UEnum* Z_Construct_UEnum_StarryTail_EAttributeKeyword()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_StarryTail();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EAttributeKeyword"), 0, Get_Z_Construct_UEnum_StarryTail_EAttributeKeyword_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EAttributeKeyword::e_None", (int64)EAttributeKeyword::e_None },
				{ "EAttributeKeyword::e_Fire", (int64)EAttributeKeyword::e_Fire },
				{ "EAttributeKeyword::e_Water", (int64)EAttributeKeyword::e_Water },
				{ "EAttributeKeyword::e_Thunder", (int64)EAttributeKeyword::e_Thunder },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "e_Fire.DisplayName", "FIRE" },
				{ "e_Fire.Name", "EAttributeKeyword::e_Fire" },
				{ "e_None.DisplayName", "NONE" },
				{ "e_None.Name", "EAttributeKeyword::e_None" },
				{ "e_Thunder.DisplayName", "THUNDER" },
				{ "e_Thunder.Name", "EAttributeKeyword::e_Thunder" },
				{ "e_Water.DisplayName", "WATER" },
				{ "e_Water.Name", "EAttributeKeyword::e_Water" },
				{ "ModuleRelativePath", "StarryTail.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_StarryTail,
				nullptr,
				"EAttributeKeyword",
				"EAttributeKeyword",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
