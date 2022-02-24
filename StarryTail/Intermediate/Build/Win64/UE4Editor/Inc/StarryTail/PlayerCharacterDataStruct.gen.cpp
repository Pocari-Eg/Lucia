// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StarryTail/PlayerCharacterDataStruct.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePlayerCharacterDataStruct() {}
// Cross Module References
	STARRYTAIL_API UScriptStruct* Z_Construct_UScriptStruct_FPlayerCharacterDataStruct();
	UPackage* Z_Construct_UPackage__Script_StarryTail();
// End Cross Module References
class UScriptStruct* FPlayerCharacterDataStruct::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern STARRYTAIL_API uint32 Get_Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct, Z_Construct_UPackage__Script_StarryTail(), TEXT("PlayerCharacterDataStruct"), sizeof(FPlayerCharacterDataStruct), Get_Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Hash());
	}
	return Singleton;
}
template<> STARRYTAIL_API UScriptStruct* StaticStruct<FPlayerCharacterDataStruct>()
{
	return FPlayerCharacterDataStruct::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FPlayerCharacterDataStruct(FPlayerCharacterDataStruct::StaticStruct, TEXT("/Script/StarryTail"), TEXT("PlayerCharacterDataStruct"), false, nullptr, nullptr);
static struct FScriptStruct_StarryTail_StaticRegisterNativesFPlayerCharacterDataStruct
{
	FScriptStruct_StarryTail_StaticRegisterNativesFPlayerCharacterDataStruct()
	{
		UScriptStruct::DeferCppStructOps<FPlayerCharacterDataStruct>(FName(TEXT("PlayerCharacterDataStruct")));
	}
} ScriptStruct_StarryTail_StaticRegisterNativesFPlayerCharacterDataStruct;
	struct Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FollowCameraZPosition_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FollowCameraZPosition;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldofView_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FieldofView;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HP_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_HP;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MoveSpeed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MoveSpeed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DashDistance_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DashDistance;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "PlayerCharacterDataStruct.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FPlayerCharacterDataStruct>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_FollowCameraZPosition_MetaData[] = {
		{ "Category", "PlayerCharacterDataStruct" },
		{ "Comment", "// ???????\xcf\xb0? ?\xc3\xb7??\xcc\xbe? ?? ?\xc5\xb8?\n" },
		{ "ModuleRelativePath", "PlayerCharacterDataStruct.h" },
		{ "ToolTip", "???????\xcf\xb0? ?\xc3\xb7??\xcc\xbe? ?? ?\xc5\xb8?" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_FollowCameraZPosition = { "FollowCameraZPosition", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FPlayerCharacterDataStruct, FollowCameraZPosition), METADATA_PARAMS(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_FollowCameraZPosition_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_FollowCameraZPosition_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_FieldofView_MetaData[] = {
		{ "Category", "PlayerCharacterDataStruct" },
		{ "Comment", "// \xc4\xab?\xde\xb6? ?????\xca\xb5? ???? ??\n" },
		{ "ModuleRelativePath", "PlayerCharacterDataStruct.h" },
		{ "ToolTip", "\xc4\xab?\xde\xb6? ?????\xca\xb5? ???? ??" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_FieldofView = { "FieldofView", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FPlayerCharacterDataStruct, FieldofView), METADATA_PARAMS(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_FieldofView_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_FieldofView_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_HP_MetaData[] = {
		{ "Category", "PlayerCharacterDataStruct" },
		{ "Comment", "// \xc3\xbc??\n" },
		{ "ModuleRelativePath", "PlayerCharacterDataStruct.h" },
		{ "ToolTip", "\xc3\xbc??" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_HP = { "HP", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FPlayerCharacterDataStruct, HP), METADATA_PARAMS(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_HP_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_HP_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_MoveSpeed_MetaData[] = {
		{ "Category", "PlayerCharacterDataStruct" },
		{ "Comment", "// ?\xcc\xb5??\xd3\xb5?\n" },
		{ "ModuleRelativePath", "PlayerCharacterDataStruct.h" },
		{ "ToolTip", "?\xcc\xb5??\xd3\xb5?" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_MoveSpeed = { "MoveSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FPlayerCharacterDataStruct, MoveSpeed), METADATA_PARAMS(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_MoveSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_MoveSpeed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_DashDistance_MetaData[] = {
		{ "Category", "PlayerCharacterDataStruct" },
		{ "Comment", "// ?\xcc\xb5??\xd3\xb5? 1?? ?????? 0.1?\xcc\xb5?\n" },
		{ "ModuleRelativePath", "PlayerCharacterDataStruct.h" },
		{ "ToolTip", "?\xcc\xb5??\xd3\xb5? 1?? ?????? 0.1?\xcc\xb5?" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_DashDistance = { "DashDistance", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FPlayerCharacterDataStruct, DashDistance), METADATA_PARAMS(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_DashDistance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_DashDistance_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_FollowCameraZPosition,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_FieldofView,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_HP,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_MoveSpeed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::NewProp_DashDistance,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_StarryTail,
		nullptr,
		&NewStructOps,
		"PlayerCharacterDataStruct",
		sizeof(FPlayerCharacterDataStruct),
		alignof(FPlayerCharacterDataStruct),
		Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000011),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FPlayerCharacterDataStruct()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_StarryTail();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("PlayerCharacterDataStruct"), sizeof(FPlayerCharacterDataStruct), Get_Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FPlayerCharacterDataStruct_Hash() { return 4157026121U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
