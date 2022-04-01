// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODBlueprintStatics.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODBlueprintStatics() {}
// Cross Module References
	FMODSTUDIO_API UEnum* Z_Construct_UEnum_FMODStudio_EFMOD_STUDIO_STOP_MODE();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FFMODEventInstance();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODBlueprintStatics_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODBlueprintStatics();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODBus_NoRegister();
	FMODSTUDIO_API UEnum* Z_Construct_UEnum_FMODStudio_EFMODEventProperty();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAsset_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEvent_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODBank_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_EAttachLocation();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAudioComponent_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODVCA_NoRegister();
// End Cross Module References
	static UEnum* EFMOD_STUDIO_STOP_MODE_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_FMODStudio_EFMOD_STUDIO_STOP_MODE, Z_Construct_UPackage__Script_FMODStudio(), TEXT("EFMOD_STUDIO_STOP_MODE"));
		}
		return Singleton;
	}
	template<> FMODSTUDIO_API UEnum* StaticEnum<EFMOD_STUDIO_STOP_MODE>()
	{
		return EFMOD_STUDIO_STOP_MODE_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EFMOD_STUDIO_STOP_MODE(EFMOD_STUDIO_STOP_MODE_StaticEnum, TEXT("/Script/FMODStudio"), TEXT("EFMOD_STUDIO_STOP_MODE"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_FMODStudio_EFMOD_STUDIO_STOP_MODE_Hash() { return 2025919102U; }
	UEnum* Z_Construct_UEnum_FMODStudio_EFMOD_STUDIO_STOP_MODE()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EFMOD_STUDIO_STOP_MODE"), 0, Get_Z_Construct_UEnum_FMODStudio_EFMOD_STUDIO_STOP_MODE_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ALLOWFADEOUT", (int64)ALLOWFADEOUT },
				{ "IMMEDIATE", (int64)IMMEDIATE },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "ALLOWFADEOUT.Name", "ALLOWFADEOUT" },
				{ "BlueprintType", "true" },
				{ "IMMEDIATE.Name", "IMMEDIATE" },
				{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_FMODStudio,
				nullptr,
				"EFMOD_STUDIO_STOP_MODE",
				"EFMOD_STUDIO_STOP_MODE",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FFMODEventInstance::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FMODSTUDIO_API uint32 Get_Z_Construct_UScriptStruct_FFMODEventInstance_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FFMODEventInstance, Z_Construct_UPackage__Script_FMODStudio(), TEXT("FMODEventInstance"), sizeof(FFMODEventInstance), Get_Z_Construct_UScriptStruct_FFMODEventInstance_Hash());
	}
	return Singleton;
}
template<> FMODSTUDIO_API UScriptStruct* StaticStruct<FFMODEventInstance>()
{
	return FFMODEventInstance::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FFMODEventInstance(FFMODEventInstance::StaticStruct, TEXT("/Script/FMODStudio"), TEXT("FMODEventInstance"), false, nullptr, nullptr);
static struct FScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventInstance
{
	FScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventInstance()
	{
		UScriptStruct::DeferCppStructOps<FFMODEventInstance>(FName(TEXT("FMODEventInstance")));
	}
} ScriptStruct_FMODStudio_StaticRegisterNativesFFMODEventInstance;
	struct Z_Construct_UScriptStruct_FFMODEventInstance_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODEventInstance_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFMODEventInstance_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFMODEventInstance>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFMODEventInstance_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
		nullptr,
		&NewStructOps,
		"FMODEventInstance",
		sizeof(FFMODEventInstance),
		alignof(FFMODEventInstance),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODEventInstance_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODEventInstance_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFMODEventInstance()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FFMODEventInstance_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FMODStudio();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("FMODEventInstance"), sizeof(FFMODEventInstance), Get_Z_Construct_UScriptStruct_FFMODEventInstance_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FFMODEventInstance_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FFMODEventInstance_Hash() { return 3262348046U; }
	DEFINE_FUNCTION(UFMODBlueprintStatics::execSetLocale)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Locale);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::SetLocale(Z_Param_Locale);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execMixerResume)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::MixerResume();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execMixerSuspend)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::MixerSuspend();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execSetOutputDriverByIndex)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_NewDriverIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::SetOutputDriverByIndex(Z_Param_NewDriverIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execSetOutputDriverByName)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_NewDriverName);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::SetOutputDriverByName(Z_Param_NewDriverName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execGetOutputDrivers)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FString>*)Z_Param__Result=UFMODBlueprintStatics::GetOutputDrivers();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceSetTransform)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_GET_STRUCT_REF(FTransform,Z_Param_Out_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::EventInstanceSetTransform(Z_Param_EventInstance,Z_Param_Out_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceKeyOff)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::EventInstanceKeyOff(Z_Param_EventInstance);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceRelease)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::EventInstanceRelease(Z_Param_EventInstance);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceStop)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_GET_UBOOL(Z_Param_Release);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::EventInstanceStop(Z_Param_EventInstance,Z_Param_Release);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstancePlay)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::EventInstancePlay(Z_Param_EventInstance);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceSetProperty)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_GET_PROPERTY(FByteProperty,Z_Param_Property);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::EventInstanceSetProperty(Z_Param_EventInstance,EFMODEventProperty::Type(Z_Param_Property),Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceGetParameterValue)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_GET_PROPERTY(FNameProperty,Z_Param_Name);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_UserValue);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_FinalValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::EventInstanceGetParameterValue(Z_Param_EventInstance,Z_Param_Name,Z_Param_Out_UserValue,Z_Param_Out_FinalValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceGetParameter)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_GET_PROPERTY(FNameProperty,Z_Param_Name);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=UFMODBlueprintStatics::EventInstanceGetParameter(Z_Param_EventInstance,Z_Param_Name);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceSetParameter)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_GET_PROPERTY(FNameProperty,Z_Param_Name);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::EventInstanceSetParameter(Z_Param_EventInstance,Z_Param_Name,Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceSetPaused)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_GET_UBOOL(Z_Param_Paused);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::EventInstanceSetPaused(Z_Param_EventInstance,Z_Param_Paused);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceSetPitch)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Pitch);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::EventInstanceSetPitch(Z_Param_EventInstance,Z_Param_Pitch);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceSetVolume)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Volume);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::EventInstanceSetVolume(Z_Param_EventInstance,Z_Param_Volume);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execEventInstanceIsValid)
	{
		P_GET_STRUCT(FFMODEventInstance,Z_Param_EventInstance);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UFMODBlueprintStatics::EventInstanceIsValid(Z_Param_EventInstance);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execGetGlobalParameterValueByName)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Name);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_UserValue);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_FinalValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::GetGlobalParameterValueByName(Z_Param_Name,Z_Param_Out_UserValue,Z_Param_Out_FinalValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execGetGlobalParameterByName)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Name);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=UFMODBlueprintStatics::GetGlobalParameterByName(Z_Param_Name);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execSetGlobalParameterByName)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Name);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::SetGlobalParameterByName(Z_Param_Name,Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execVCASetVolume)
	{
		P_GET_OBJECT(UFMODVCA,Z_Param_Vca);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Volume);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::VCASetVolume(Z_Param_Vca,Z_Param_Volume);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execBusStopAllEvents)
	{
		P_GET_OBJECT(UFMODBus,Z_Param_Bus);
		P_GET_PROPERTY(FByteProperty,Z_Param_stopMode);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::BusStopAllEvents(Z_Param_Bus,EFMOD_STUDIO_STOP_MODE(Z_Param_stopMode));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execBusSetMute)
	{
		P_GET_OBJECT(UFMODBus,Z_Param_Bus);
		P_GET_UBOOL(Z_Param_bMute);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::BusSetMute(Z_Param_Bus,Z_Param_bMute);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execBusSetPaused)
	{
		P_GET_OBJECT(UFMODBus,Z_Param_Bus);
		P_GET_UBOOL(Z_Param_bPaused);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::BusSetPaused(Z_Param_Bus,Z_Param_bPaused);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execBusSetVolume)
	{
		P_GET_OBJECT(UFMODBus,Z_Param_Bus);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Volume);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::BusSetVolume(Z_Param_Bus,Z_Param_Volume);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execFindEventInstances)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_OBJECT(UFMODEvent,Z_Param_Event);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FFMODEventInstance>*)Z_Param__Result=UFMODBlueprintStatics::FindEventInstances(Z_Param_WorldContextObject,Z_Param_Event);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execUnloadEventSampleData)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_OBJECT(UFMODEvent,Z_Param_Event);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::UnloadEventSampleData(Z_Param_WorldContextObject,Z_Param_Event);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execLoadEventSampleData)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_OBJECT(UFMODEvent,Z_Param_Event);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::LoadEventSampleData(Z_Param_WorldContextObject,Z_Param_Event);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execUnloadBankSampleData)
	{
		P_GET_OBJECT(UFMODBank,Z_Param_Bank);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::UnloadBankSampleData(Z_Param_Bank);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execLoadBankSampleData)
	{
		P_GET_OBJECT(UFMODBank,Z_Param_Bank);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::LoadBankSampleData(Z_Param_Bank);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execIsBankLoaded)
	{
		P_GET_OBJECT(UFMODBank,Z_Param_Bank);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UFMODBlueprintStatics::IsBankLoaded(Z_Param_Bank);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execUnloadBank)
	{
		P_GET_OBJECT(UFMODBank,Z_Param_Bank);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::UnloadBank(Z_Param_Bank);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execLoadBank)
	{
		P_GET_OBJECT(UFMODBank,Z_Param_Bank);
		P_GET_UBOOL(Z_Param_bBlocking);
		P_GET_UBOOL(Z_Param_bLoadSampleData);
		P_FINISH;
		P_NATIVE_BEGIN;
		UFMODBlueprintStatics::LoadBank(Z_Param_Bank,Z_Param_bBlocking,Z_Param_bLoadSampleData);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execFindEventByName)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Name);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UFMODEvent**)Z_Param__Result=UFMODBlueprintStatics::FindEventByName(Z_Param_Name);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execFindAssetByName)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Name);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UFMODAsset**)Z_Param__Result=UFMODBlueprintStatics::FindAssetByName(Z_Param_Name);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execPlayEventAttached)
	{
		P_GET_OBJECT(UFMODEvent,Z_Param_Event);
		P_GET_OBJECT(USceneComponent,Z_Param_AttachToComponent);
		P_GET_PROPERTY(FNameProperty,Z_Param_AttachPointName);
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_GET_PROPERTY(FByteProperty,Z_Param_LocationType);
		P_GET_UBOOL(Z_Param_bStopWhenAttachedToDestroyed);
		P_GET_UBOOL(Z_Param_bAutoPlay);
		P_GET_UBOOL(Z_Param_bAutoDestroy);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UFMODAudioComponent**)Z_Param__Result=UFMODBlueprintStatics::PlayEventAttached(Z_Param_Event,Z_Param_AttachToComponent,Z_Param_AttachPointName,Z_Param_Location,EAttachLocation::Type(Z_Param_LocationType),Z_Param_bStopWhenAttachedToDestroyed,Z_Param_bAutoPlay,Z_Param_bAutoDestroy);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execPlayEventAtLocation)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_OBJECT(UFMODEvent,Z_Param_Event);
		P_GET_STRUCT_REF(FTransform,Z_Param_Out_Location);
		P_GET_UBOOL(Z_Param_bAutoPlay);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FFMODEventInstance*)Z_Param__Result=UFMODBlueprintStatics::PlayEventAtLocation(Z_Param_WorldContextObject,Z_Param_Event,Z_Param_Out_Location,Z_Param_bAutoPlay);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODBlueprintStatics::execPlayEvent2D)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_OBJECT(UFMODEvent,Z_Param_Event);
		P_GET_UBOOL(Z_Param_bAutoPlay);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FFMODEventInstance*)Z_Param__Result=UFMODBlueprintStatics::PlayEvent2D(Z_Param_WorldContextObject,Z_Param_Event,Z_Param_bAutoPlay);
		P_NATIVE_END;
	}
	void UFMODBlueprintStatics::StaticRegisterNativesUFMODBlueprintStatics()
	{
		UClass* Class = UFMODBlueprintStatics::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "BusSetMute", &UFMODBlueprintStatics::execBusSetMute },
			{ "BusSetPaused", &UFMODBlueprintStatics::execBusSetPaused },
			{ "BusSetVolume", &UFMODBlueprintStatics::execBusSetVolume },
			{ "BusStopAllEvents", &UFMODBlueprintStatics::execBusStopAllEvents },
			{ "EventInstanceGetParameter", &UFMODBlueprintStatics::execEventInstanceGetParameter },
			{ "EventInstanceGetParameterValue", &UFMODBlueprintStatics::execEventInstanceGetParameterValue },
			{ "EventInstanceIsValid", &UFMODBlueprintStatics::execEventInstanceIsValid },
			{ "EventInstanceKeyOff", &UFMODBlueprintStatics::execEventInstanceKeyOff },
			{ "EventInstancePlay", &UFMODBlueprintStatics::execEventInstancePlay },
			{ "EventInstanceRelease", &UFMODBlueprintStatics::execEventInstanceRelease },
			{ "EventInstanceSetParameter", &UFMODBlueprintStatics::execEventInstanceSetParameter },
			{ "EventInstanceSetPaused", &UFMODBlueprintStatics::execEventInstanceSetPaused },
			{ "EventInstanceSetPitch", &UFMODBlueprintStatics::execEventInstanceSetPitch },
			{ "EventInstanceSetProperty", &UFMODBlueprintStatics::execEventInstanceSetProperty },
			{ "EventInstanceSetTransform", &UFMODBlueprintStatics::execEventInstanceSetTransform },
			{ "EventInstanceSetVolume", &UFMODBlueprintStatics::execEventInstanceSetVolume },
			{ "EventInstanceStop", &UFMODBlueprintStatics::execEventInstanceStop },
			{ "FindAssetByName", &UFMODBlueprintStatics::execFindAssetByName },
			{ "FindEventByName", &UFMODBlueprintStatics::execFindEventByName },
			{ "FindEventInstances", &UFMODBlueprintStatics::execFindEventInstances },
			{ "GetGlobalParameterByName", &UFMODBlueprintStatics::execGetGlobalParameterByName },
			{ "GetGlobalParameterValueByName", &UFMODBlueprintStatics::execGetGlobalParameterValueByName },
			{ "GetOutputDrivers", &UFMODBlueprintStatics::execGetOutputDrivers },
			{ "IsBankLoaded", &UFMODBlueprintStatics::execIsBankLoaded },
			{ "LoadBank", &UFMODBlueprintStatics::execLoadBank },
			{ "LoadBankSampleData", &UFMODBlueprintStatics::execLoadBankSampleData },
			{ "LoadEventSampleData", &UFMODBlueprintStatics::execLoadEventSampleData },
			{ "MixerResume", &UFMODBlueprintStatics::execMixerResume },
			{ "MixerSuspend", &UFMODBlueprintStatics::execMixerSuspend },
			{ "PlayEvent2D", &UFMODBlueprintStatics::execPlayEvent2D },
			{ "PlayEventAtLocation", &UFMODBlueprintStatics::execPlayEventAtLocation },
			{ "PlayEventAttached", &UFMODBlueprintStatics::execPlayEventAttached },
			{ "SetGlobalParameterByName", &UFMODBlueprintStatics::execSetGlobalParameterByName },
			{ "SetLocale", &UFMODBlueprintStatics::execSetLocale },
			{ "SetOutputDriverByIndex", &UFMODBlueprintStatics::execSetOutputDriverByIndex },
			{ "SetOutputDriverByName", &UFMODBlueprintStatics::execSetOutputDriverByName },
			{ "UnloadBank", &UFMODBlueprintStatics::execUnloadBank },
			{ "UnloadBankSampleData", &UFMODBlueprintStatics::execUnloadBankSampleData },
			{ "UnloadEventSampleData", &UFMODBlueprintStatics::execUnloadEventSampleData },
			{ "VCASetVolume", &UFMODBlueprintStatics::execVCASetVolume },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics
	{
		struct FMODBlueprintStatics_eventBusSetMute_Parms
		{
			UFMODBus* Bus;
			bool bMute;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Bus;
		static void NewProp_bMute_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bMute;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::NewProp_Bus = { "Bus", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventBusSetMute_Parms, Bus), Z_Construct_UClass_UFMODBus_NoRegister, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::NewProp_bMute_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventBusSetMute_Parms*)Obj)->bMute = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::NewProp_bMute = { "bMute", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventBusSetMute_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::NewProp_bMute_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::NewProp_Bus,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::NewProp_bMute,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Bus" },
		{ "Comment", "/** Mute/Unmute this bus\n\x09 * @param Bus - bus to use\n\x09 * @param bMute - mute\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Mute/Unmute this bus\n@param Bus - bus to use\n@param bMute - mute" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "BusSetMute", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventBusSetMute_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics
	{
		struct FMODBlueprintStatics_eventBusSetPaused_Parms
		{
			UFMODBus* Bus;
			bool bPaused;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Bus;
		static void NewProp_bPaused_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bPaused;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::NewProp_Bus = { "Bus", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventBusSetPaused_Parms, Bus), Z_Construct_UClass_UFMODBus_NoRegister, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::NewProp_bPaused_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventBusSetPaused_Parms*)Obj)->bPaused = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::NewProp_bPaused = { "bPaused", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventBusSetPaused_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::NewProp_bPaused_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::NewProp_Bus,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::NewProp_bPaused,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Bus" },
		{ "Comment", "/** Pause/Unpause all events going through this bus\n\x09 * @param Bus - bus to use\n\x09 * @param bPaused - paused\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Pause/Unpause all events going through this bus\n@param Bus - bus to use\n@param bPaused - paused" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "BusSetPaused", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventBusSetPaused_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics
	{
		struct FMODBlueprintStatics_eventBusSetVolume_Parms
		{
			UFMODBus* Bus;
			float Volume;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Bus;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Volume;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::NewProp_Bus = { "Bus", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventBusSetVolume_Parms, Bus), Z_Construct_UClass_UFMODBus_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::NewProp_Volume = { "Volume", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventBusSetVolume_Parms, Volume), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::NewProp_Bus,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::NewProp_Volume,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Bus" },
		{ "Comment", "/** Set volume on a bus\n\x09 * @param Bus - bus to use\n\x09 * @param Volume - volume\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Set volume on a bus\n@param Bus - bus to use\n@param Volume - volume" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "BusSetVolume", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventBusSetVolume_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics
	{
		struct FMODBlueprintStatics_eventBusStopAllEvents_Parms
		{
			UFMODBus* Bus;
			TEnumAsByte<EFMOD_STUDIO_STOP_MODE> stopMode;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Bus;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_stopMode;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::NewProp_Bus = { "Bus", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventBusStopAllEvents_Parms, Bus), Z_Construct_UClass_UFMODBus_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::NewProp_stopMode = { "stopMode", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventBusStopAllEvents_Parms, stopMode), Z_Construct_UEnum_FMODStudio_EFMOD_STUDIO_STOP_MODE, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::NewProp_Bus,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::NewProp_stopMode,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Bus" },
		{ "Comment", "/** Stops all EventInstances routed into the bus\n\x09 * @param Bus - bus to use\n\x09 * @param stopMode - desired stop mode\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Stops all EventInstances routed into the bus\n@param Bus - bus to use\n@param stopMode - desired stop mode" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "BusStopAllEvents", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventBusStopAllEvents_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceGetParameter_Parms
		{
			FFMODEventInstance EventInstance;
			FName Name;
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceGetParameter_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceGetParameter_Parms, Name), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceGetParameter_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::NewProp_EventInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Will be deprecated in FMOD 2.01, use `EventInstanceGetParameterValue(FFMODEventInstance, FName, float, float)` instead.\n     * Get a parameter on an FMOD Event Instance.\n\x09 * @param EventInstance - Event instance\n\x09 * @param Name - Name of parameter\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Will be deprecated in FMOD 2.01, use `EventInstanceGetParameterValue(FFMODEventInstance, FName, float, float)` instead.\nGet a parameter on an FMOD Event Instance.\n@param EventInstance - Event instance\n@param Name - Name of parameter" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceGetParameter", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceGetParameter_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceGetParameterValue_Parms
		{
			FFMODEventInstance EventInstance;
			FName Name;
			float UserValue;
			float FinalValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_UserValue;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FinalValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceGetParameterValue_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceGetParameterValue_Parms, Name), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::NewProp_UserValue = { "UserValue", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceGetParameterValue_Parms, UserValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::NewProp_FinalValue = { "FinalValue", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceGetParameterValue_Parms, FinalValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::NewProp_EventInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::NewProp_UserValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::NewProp_FinalValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Get a parameter on an FMOD Event Instance.\n\x09 * @param EventInstance - Event instance\n\x09 * @param Name - Name of parameter\n     * @param UserValue - Parameter value as set from the public API.\n     * @param FinalValue - Final combined parameter value.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Get a parameter on an FMOD Event Instance.\n@param EventInstance - Event instance\n@param Name - Name of parameter\n@param UserValue - Parameter value as set from the public API.\n@param FinalValue - Final combined parameter value." },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceGetParameterValue", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceGetParameterValue_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceIsValid_Parms
		{
			FFMODEventInstance EventInstance;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceIsValid_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventEventInstanceIsValid_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventEventInstanceIsValid_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::NewProp_EventInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Returns whether this FMOD Event Instance is valid.  The instance will be invalidated when the sound stops.\n\x09 * @param EventInstance - Event instance\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Returns whether this FMOD Event Instance is valid.  The instance will be invalidated when the sound stops.\n@param EventInstance - Event instance" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceIsValid", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceIsValid_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceKeyOff_Parms
		{
			FFMODEventInstance EventInstance;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceKeyOff_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff_Statics::NewProp_EventInstance,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Allow an FMOD Event Instance to continue past a sustain point.\n\x09 * @param EventInstance - Event instance\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Allow an FMOD Event Instance to continue past a sustain point.\n@param EventInstance - Event instance" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceKeyOff", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceKeyOff_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay_Statics
	{
		struct FMODBlueprintStatics_eventEventInstancePlay_Parms
		{
			FFMODEventInstance EventInstance;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstancePlay_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay_Statics::NewProp_EventInstance,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Plays an FMOD Event Instance.\n\x09 * @param EventInstance - Event instance\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Plays an FMOD Event Instance.\n@param EventInstance - Event instance" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstancePlay", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstancePlay_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceRelease_Parms
		{
			FFMODEventInstance EventInstance;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceRelease_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease_Statics::NewProp_EventInstance,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Release an FMOD Event Instance.\n    * @param EventInstance - Event instance\n    */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Release an FMOD Event Instance.\n@param EventInstance - Event instance" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceRelease", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceRelease_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceSetParameter_Parms
		{
			FFMODEventInstance EventInstance;
			FName Name;
			float Value;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetParameter_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetParameter_Parms, Name), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetParameter_Parms, Value), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::NewProp_EventInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Set a parameter on an FMOD Event Instance.\n\x09 * @param EventInstance - Event instance\n\x09 * @param Name - Name of parameter\n\x09 * @param Value - Value of parameter\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Set a parameter on an FMOD Event Instance.\n@param EventInstance - Event instance\n@param Name - Name of parameter\n@param Value - Value of parameter" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceSetParameter", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceSetParameter_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceSetPaused_Parms
		{
			FFMODEventInstance EventInstance;
			bool Paused;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static void NewProp_Paused_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_Paused;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetPaused_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::NewProp_Paused_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventEventInstanceSetPaused_Parms*)Obj)->Paused = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::NewProp_Paused = { "Paused", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventEventInstanceSetPaused_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::NewProp_Paused_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::NewProp_EventInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::NewProp_Paused,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Pause/Unpause an FMOD Event Instance.\n\x09 * @param EventInstance - Event instance\n\x09 * @param Paused - Whether to pause or unpause\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Pause/Unpause an FMOD Event Instance.\n@param EventInstance - Event instance\n@param Paused - Whether to pause or unpause" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceSetPaused", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceSetPaused_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceSetPitch_Parms
		{
			FFMODEventInstance EventInstance;
			float Pitch;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Pitch;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetPitch_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::NewProp_Pitch = { "Pitch", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetPitch_Parms, Pitch), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::NewProp_EventInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::NewProp_Pitch,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Set pitch on an FMOD Event Instance.\n\x09 * @param EventInstance - Event instance\n\x09 * @param Value - Volume to set\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Set pitch on an FMOD Event Instance.\n@param EventInstance - Event instance\n@param Value - Volume to set" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceSetPitch", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceSetPitch_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceSetProperty_Parms
		{
			FFMODEventInstance EventInstance;
			TEnumAsByte<EFMODEventProperty::Type> Property;
			float Value;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Property;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetProperty_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::NewProp_Property = { "Property", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetProperty_Parms, Property), Z_Construct_UEnum_FMODStudio_EFMODEventProperty, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetProperty_Parms, Value), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::NewProp_EventInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::NewProp_Property,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Set an FMOD event property on an FMOD Event Instance.\n\x09* @param EventInstance - Event instance\n\x09* @param Property - Property to set\n\x09* @param Value - Value to set\n\x09*/" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Set an FMOD event property on an FMOD Event Instance.\n@param EventInstance - Event instance\n@param Property - Property to set\n@param Value - Value to set" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceSetProperty", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceSetProperty_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceSetTransform_Parms
		{
			FFMODEventInstance EventInstance;
			FTransform Location;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetTransform_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetTransform_Parms, Location), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::NewProp_EventInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::NewProp_Location,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Set 3D attributes on a FMOD Event Instance.\n\x09 * @param EventInstance - Event instance\n\x09 * @param Location - Location to place event\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Set 3D attributes on a FMOD Event Instance.\n@param EventInstance - Event instance\n@param Location - Location to place event" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceSetTransform", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceSetTransform_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceSetVolume_Parms
		{
			FFMODEventInstance EventInstance;
			float Volume;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Volume;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetVolume_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::NewProp_Volume = { "Volume", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceSetVolume_Parms, Volume), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::NewProp_EventInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::NewProp_Volume,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Set volume on an FMOD Event Instance.\n\x09 * @param EventInstance - Event instance\n\x09 * @param Value - Volume to set\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Set volume on an FMOD Event Instance.\n@param EventInstance - Event instance\n@param Value - Volume to set" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceSetVolume", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceSetVolume_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics
	{
		struct FMODBlueprintStatics_eventEventInstanceStop_Parms
		{
			FFMODEventInstance EventInstance;
			bool Release;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EventInstance;
		static void NewProp_Release_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_Release;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::NewProp_EventInstance = { "EventInstance", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventEventInstanceStop_Parms, EventInstance), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::NewProp_Release_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventEventInstanceStop_Parms*)Obj)->Release = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::NewProp_Release = { "Release", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventEventInstanceStop_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::NewProp_Release_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::NewProp_EventInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::NewProp_Release,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|EventInstance" },
		{ "Comment", "/** Stop an FMOD Event Instance.\n\x09 * @param EventInstance - Event instance\n     * @param Release - Whether to release the Event Instance\n\x09 */" },
		{ "CPP_Default_Release", "false" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Stop an FMOD Event Instance.\n@param EventInstance - Event instance\n@param Release - Whether to release the Event Instance" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "EventInstanceStop", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventEventInstanceStop_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics
	{
		struct FMODBlueprintStatics_eventFindAssetByName_Parms
		{
			FString Name;
			UFMODAsset* ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::NewProp_Name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventFindAssetByName_Parms, Name), METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::NewProp_Name_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventFindAssetByName_Parms, ReturnValue), Z_Construct_UClass_UFMODAsset_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Find an asset by name.\n\x09 * @param EventName - The asset name\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Find an asset by name.\n@param EventName - The asset name" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "FindAssetByName", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventFindAssetByName_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics
	{
		struct FMODBlueprintStatics_eventFindEventByName_Parms
		{
			FString Name;
			UFMODEvent* ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::NewProp_Name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventFindEventByName_Parms, Name), METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::NewProp_Name_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventFindEventByName_Parms, ReturnValue), Z_Construct_UClass_UFMODEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Find an event by name.\n\x09 * @param EventName - The event name\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Find an event by name.\n@param EventName - The event name" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "FindEventByName", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventFindEventByName_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics
	{
		struct FMODBlueprintStatics_eventFindEventInstances_Parms
		{
			UObject* WorldContextObject;
			UFMODEvent* Event;
			TArray<FFMODEventInstance> ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Event;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventFindEventInstances_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventFindEventInstances_Parms, Event), Z_Construct_UClass_UFMODEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventFindEventInstances_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::NewProp_Event,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Return a list of all event instances that are playing for this event.\n\x09\x09""Be careful using this function because it is possible to find and alter any playing sound, even ones owned by other audio components.\n\x09 * @param Event - event to find instances from.\n\x09 */" },
		{ "DefaultToSelf", "WorldContextObject" },
		{ "HidePin", "WorldContextObject" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Return a list of all event instances that are playing for this event.\n              Be careful using this function because it is possible to find and alter any playing sound, even ones owned by other audio components.\n@param Event - event to find instances from." },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "FindEventInstances", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventFindEventInstances_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics
	{
		struct FMODBlueprintStatics_eventGetGlobalParameterByName_Parms
		{
			FName Name;
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventGetGlobalParameterByName_Parms, Name), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventGetGlobalParameterByName_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Will be deprecated in FMOD 2.01, use `GetGlobalParameterValueByName(FName, float, float)` instead.\n     * Get a global parameter from the System.\n     * @param Name - Name of parameter\n     */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Will be deprecated in FMOD 2.01, use `GetGlobalParameterValueByName(FName, float, float)` instead.\nGet a global parameter from the System.\n@param Name - Name of parameter" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "GetGlobalParameterByName", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventGetGlobalParameterByName_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics
	{
		struct FMODBlueprintStatics_eventGetGlobalParameterValueByName_Parms
		{
			FName Name;
			float UserValue;
			float FinalValue;
		};
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_UserValue;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FinalValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventGetGlobalParameterValueByName_Parms, Name), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::NewProp_UserValue = { "UserValue", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventGetGlobalParameterValueByName_Parms, UserValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::NewProp_FinalValue = { "FinalValue", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventGetGlobalParameterValueByName_Parms, FinalValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::NewProp_UserValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::NewProp_FinalValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Get a global parameter from the System.\n     * @param Name - Name of parameter\n     * @param UserValue - Parameter value as set from the public API.\n     * @param FinalValue - Final combined parameter value.\n     */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Get a global parameter from the System.\n@param Name - Name of parameter\n@param UserValue - Parameter value as set from the public API.\n@param FinalValue - Final combined parameter value." },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "GetGlobalParameterValueByName", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventGetGlobalParameterValueByName_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics
	{
		struct FMODBlueprintStatics_eventGetOutputDrivers_Parms
		{
			TArray<FString> ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventGetOutputDrivers_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** List all output device names.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "List all output device names." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "GetOutputDrivers", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventGetOutputDrivers_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics
	{
		struct FMODBlueprintStatics_eventIsBankLoaded_Parms
		{
			UFMODBank* Bank;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Bank;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::NewProp_Bank = { "Bank", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventIsBankLoaded_Parms, Bank), Z_Construct_UClass_UFMODBank_NoRegister, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventIsBankLoaded_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventIsBankLoaded_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::NewProp_Bank,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Returns true if a bank is loaded.\n\x09* @param Bank - bank to query\n\x09*/" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Returns true if a bank is loaded.\n@param Bank - bank to query" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "IsBankLoaded", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventIsBankLoaded_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics
	{
		struct FMODBlueprintStatics_eventLoadBank_Parms
		{
			UFMODBank* Bank;
			bool bBlocking;
			bool bLoadSampleData;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Bank;
		static void NewProp_bBlocking_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bBlocking;
		static void NewProp_bLoadSampleData_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bLoadSampleData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::NewProp_Bank = { "Bank", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventLoadBank_Parms, Bank), Z_Construct_UClass_UFMODBank_NoRegister, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::NewProp_bBlocking_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventLoadBank_Parms*)Obj)->bBlocking = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::NewProp_bBlocking = { "bBlocking", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventLoadBank_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::NewProp_bBlocking_SetBit, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::NewProp_bLoadSampleData_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventLoadBank_Parms*)Obj)->bLoadSampleData = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::NewProp_bLoadSampleData = { "bLoadSampleData", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventLoadBank_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::NewProp_bLoadSampleData_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::NewProp_Bank,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::NewProp_bBlocking,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::NewProp_bLoadSampleData,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Loads a bank.\n\x09 * @param Bank - bank to load\n\x09 * @param bBlocking - determines whether the bank will load synchronously\n\x09 * @param bLoadSampleData - determines whether sample data will be preloaded immediately\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Loads a bank.\n@param Bank - bank to load\n@param bBlocking - determines whether the bank will load synchronously\n@param bLoadSampleData - determines whether sample data will be preloaded immediately" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "LoadBank", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventLoadBank_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData_Statics
	{
		struct FMODBlueprintStatics_eventLoadBankSampleData_Parms
		{
			UFMODBank* Bank;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Bank;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData_Statics::NewProp_Bank = { "Bank", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventLoadBankSampleData_Parms, Bank), Z_Construct_UClass_UFMODBank_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData_Statics::NewProp_Bank,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Load bank sample data.\n\x09 * @param Bank - bank to load sample data from\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Load bank sample data.\n@param Bank - bank to load sample data from" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "LoadBankSampleData", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventLoadBankSampleData_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics
	{
		struct FMODBlueprintStatics_eventLoadEventSampleData_Parms
		{
			UObject* WorldContextObject;
			UFMODEvent* Event;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Event;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventLoadEventSampleData_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventLoadEventSampleData_Parms, Event), Z_Construct_UClass_UFMODEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::NewProp_Event,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Load event sample data.  This can be done ahead of time to avoid loading stalls.\n\x09 * @param Event - event to load sample data from.\n\x09 */" },
		{ "DefaultToSelf", "WorldContextObject" },
		{ "HidePin", "WorldContextObject" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Load event sample data.  This can be done ahead of time to avoid loading stalls.\n@param Event - event to load sample data from." },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "LoadEventSampleData", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventLoadEventSampleData_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_MixerResume_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_MixerResume_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Resume the FMOD mixer.  Used when resuming the application.\n\x09*/" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Resume the FMOD mixer.  Used when resuming the application." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_MixerResume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "MixerResume", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_MixerResume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_MixerResume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_MixerResume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_MixerResume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_MixerSuspend_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_MixerSuspend_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Suspend the FMOD mixer.  Used when suspending the application.\n\x09*/" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Suspend the FMOD mixer.  Used when suspending the application." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_MixerSuspend_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "MixerSuspend", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_MixerSuspend_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_MixerSuspend_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_MixerSuspend()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_MixerSuspend_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics
	{
		struct FMODBlueprintStatics_eventPlayEvent2D_Parms
		{
			UObject* WorldContextObject;
			UFMODEvent* Event;
			bool bAutoPlay;
			FFMODEventInstance ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Event;
		static void NewProp_bAutoPlay_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bAutoPlay;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEvent2D_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEvent2D_Parms, Event), Z_Construct_UClass_UFMODEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::NewProp_bAutoPlay_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventPlayEvent2D_Parms*)Obj)->bAutoPlay = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::NewProp_bAutoPlay = { "bAutoPlay", nullptr, (EPropertyFlags)0x0010040000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventPlayEvent2D_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::NewProp_bAutoPlay_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEvent2D_Parms, ReturnValue), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::NewProp_Event,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::NewProp_bAutoPlay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::Function_MetaDataParams[] = {
		{ "AdvancedDisplay", "2" },
		{ "bAutoPlay", "true" },
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Plays an event.  This returns an FMOD Event Instance.  The sound does not travel with any actor.\n\x09 * @param Event - event to play\n\x09 * @param bAutoPlay - Start the event automatically.\n\x09 */" },
		{ "DefaultToSelf", "WorldContextObject" },
		{ "HidePin", "WorldContextObject" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Plays an event.  This returns an FMOD Event Instance.  The sound does not travel with any actor.\n@param Event - event to play\n@param bAutoPlay - Start the event automatically." },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "PlayEvent2D", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventPlayEvent2D_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics
	{
		struct FMODBlueprintStatics_eventPlayEventAtLocation_Parms
		{
			UObject* WorldContextObject;
			UFMODEvent* Event;
			FTransform Location;
			bool bAutoPlay;
			FFMODEventInstance ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Event;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static void NewProp_bAutoPlay_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bAutoPlay;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEventAtLocation_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEventAtLocation_Parms, Event), Z_Construct_UClass_UFMODEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010040008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEventAtLocation_Parms, Location), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_Location_MetaData)) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_bAutoPlay_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventPlayEventAtLocation_Parms*)Obj)->bAutoPlay = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_bAutoPlay = { "bAutoPlay", nullptr, (EPropertyFlags)0x0010040000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventPlayEventAtLocation_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_bAutoPlay_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEventAtLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FFMODEventInstance, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_Event,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_bAutoPlay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::Function_MetaDataParams[] = {
		{ "AdvancedDisplay", "2" },
		{ "bAutoPlay", "true" },
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Plays an event at the given location. This returns an FMOD Event Instance.  The sound does not travel with any actor.\n\x09 * @param Event - event to play\n\x09 * @param Location - World position to play event at\n\x09 * @param bAutoPlay - Start the event automatically.\n\x09 */" },
		{ "DefaultToSelf", "WorldContextObject" },
		{ "HidePin", "WorldContextObject" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Plays an event at the given location. This returns an FMOD Event Instance.  The sound does not travel with any actor.\n@param Event - event to play\n@param Location - World position to play event at\n@param bAutoPlay - Start the event automatically." },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "PlayEventAtLocation", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventPlayEventAtLocation_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics
	{
		struct FMODBlueprintStatics_eventPlayEventAttached_Parms
		{
			UFMODEvent* Event;
			USceneComponent* AttachToComponent;
			FName AttachPointName;
			FVector Location;
			TEnumAsByte<EAttachLocation::Type> LocationType;
			bool bStopWhenAttachedToDestroyed;
			bool bAutoPlay;
			bool bAutoDestroy;
			UFMODAudioComponent* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Event;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AttachToComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AttachToComponent;
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_AttachPointName;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_LocationType;
		static void NewProp_bStopWhenAttachedToDestroyed_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bStopWhenAttachedToDestroyed;
		static void NewProp_bAutoPlay_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bAutoPlay;
		static void NewProp_bAutoDestroy_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bAutoDestroy;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEventAttached_Parms, Event), Z_Construct_UClass_UFMODEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_AttachToComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_AttachToComponent = { "AttachToComponent", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEventAttached_Parms, AttachToComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_AttachToComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_AttachToComponent_MetaData)) };
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_AttachPointName = { "AttachPointName", nullptr, (EPropertyFlags)0x0010040000000080, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEventAttached_Parms, AttachPointName), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010040000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEventAttached_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_LocationType = { "LocationType", nullptr, (EPropertyFlags)0x0010040000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEventAttached_Parms, LocationType), Z_Construct_UEnum_Engine_EAttachLocation, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bStopWhenAttachedToDestroyed_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventPlayEventAttached_Parms*)Obj)->bStopWhenAttachedToDestroyed = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bStopWhenAttachedToDestroyed = { "bStopWhenAttachedToDestroyed", nullptr, (EPropertyFlags)0x0010040000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventPlayEventAttached_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bStopWhenAttachedToDestroyed_SetBit, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bAutoPlay_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventPlayEventAttached_Parms*)Obj)->bAutoPlay = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bAutoPlay = { "bAutoPlay", nullptr, (EPropertyFlags)0x0010040000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventPlayEventAttached_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bAutoPlay_SetBit, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bAutoDestroy_SetBit(void* Obj)
	{
		((FMODBlueprintStatics_eventPlayEventAttached_Parms*)Obj)->bAutoDestroy = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bAutoDestroy = { "bAutoDestroy", nullptr, (EPropertyFlags)0x0010040000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODBlueprintStatics_eventPlayEventAttached_Parms), &Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bAutoDestroy_SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_ReturnValue_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000080588, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventPlayEventAttached_Parms, ReturnValue), Z_Construct_UClass_UFMODAudioComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_ReturnValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_ReturnValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_Event,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_AttachToComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_AttachPointName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_LocationType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bStopWhenAttachedToDestroyed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bAutoPlay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_bAutoDestroy,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::Function_MetaDataParams[] = {
		{ "AdvancedDisplay", "2" },
		{ "bAutoDestroy", "true" },
		{ "bAutoPlay", "true" },
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Plays an event attached to and following the specified component.\n\x09 * @param Event - event to play\n\x09 * @param AttachComponent - Component to attach to.\n\x09 * @param AttachPointName - Optional named point within the AttachComponent to play the sound at\n\x09 * @param Location - Depending on the value of Location Type this is either a relative offset from the attach component/point or an absolute world position that will be translated to a relative offset\n\x09 * @param LocationType - Specifies whether Location is a relative offset or an absolute world position\n\x09 * @param bStopWhenAttachedToDestroyed - Specifies whether the sound should stop playing when the owner of the attach to component is destroyed.\n\x09 * @param bAutoPlay - Start the event automatically.\n\x09 * @param bAutoDestroy - Automatically destroy the audio component when the sound is stopped.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Plays an event attached to and following the specified component.\n@param Event - event to play\n@param AttachComponent - Component to attach to.\n@param AttachPointName - Optional named point within the AttachComponent to play the sound at\n@param Location - Depending on the value of Location Type this is either a relative offset from the attach component/point or an absolute world position that will be translated to a relative offset\n@param LocationType - Specifies whether Location is a relative offset or an absolute world position\n@param bStopWhenAttachedToDestroyed - Specifies whether the sound should stop playing when the owner of the attach to component is destroyed.\n@param bAutoPlay - Start the event automatically.\n@param bAutoDestroy - Automatically destroy the audio component when the sound is stopped." },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "PlayEventAttached", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventPlayEventAttached_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics
	{
		struct FMODBlueprintStatics_eventSetGlobalParameterByName_Parms
		{
			FName Name;
			float Value;
		};
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventSetGlobalParameterByName_Parms, Name), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventSetGlobalParameterByName_Parms, Value), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Set a global parameter from the System.\n     * @param Name - Name of parameter\n     * @param Value - Value of parameter\n     */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Set a global parameter from the System.\n@param Name - Name of parameter\n@param Value - Value of parameter" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "SetGlobalParameterByName", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventSetGlobalParameterByName_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics
	{
		struct FMODBlueprintStatics_eventSetLocale_Parms
		{
			FString Locale;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Locale_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Locale;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::NewProp_Locale_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::NewProp_Locale = { "Locale", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventSetLocale_Parms, Locale), METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::NewProp_Locale_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::NewProp_Locale_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::NewProp_Locale,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Set the active locale for subsequent bank loads.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Set the active locale for subsequent bank loads." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "SetLocale", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventSetLocale_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex_Statics
	{
		struct FMODBlueprintStatics_eventSetOutputDriverByIndex_Parms
		{
			int32 NewDriverIndex;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_NewDriverIndex;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex_Statics::NewProp_NewDriverIndex = { "NewDriverIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventSetOutputDriverByIndex_Parms, NewDriverIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex_Statics::NewProp_NewDriverIndex,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Set current output device by its index from GetOutputDrivers.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Set current output device by its index from GetOutputDrivers." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "SetOutputDriverByIndex", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventSetOutputDriverByIndex_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName_Statics
	{
		struct FMODBlueprintStatics_eventSetOutputDriverByName_Parms
		{
			FString NewDriverName;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_NewDriverName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName_Statics::NewProp_NewDriverName = { "NewDriverName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventSetOutputDriverByName_Parms, NewDriverName), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName_Statics::NewProp_NewDriverName,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Set current output device by name or part of the name.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Set current output device by name or part of the name." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "SetOutputDriverByName", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventSetOutputDriverByName_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank_Statics
	{
		struct FMODBlueprintStatics_eventUnloadBank_Parms
		{
			UFMODBank* Bank;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Bank;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank_Statics::NewProp_Bank = { "Bank", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventUnloadBank_Parms, Bank), Z_Construct_UClass_UFMODBank_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank_Statics::NewProp_Bank,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Unloads a bank.\n\x09 * @param Bank - bank to unload\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Unloads a bank.\n@param Bank - bank to unload" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "UnloadBank", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventUnloadBank_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData_Statics
	{
		struct FMODBlueprintStatics_eventUnloadBankSampleData_Parms
		{
			UFMODBank* Bank;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Bank;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData_Statics::NewProp_Bank = { "Bank", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventUnloadBankSampleData_Parms, Bank), Z_Construct_UClass_UFMODBank_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData_Statics::NewProp_Bank,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Unload bank sample data.\n\x09 * @param Bank - bank to unload sample data from\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Unload bank sample data.\n@param Bank - bank to unload sample data from" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "UnloadBankSampleData", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventUnloadBankSampleData_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics
	{
		struct FMODBlueprintStatics_eventUnloadEventSampleData_Parms
		{
			UObject* WorldContextObject;
			UFMODEvent* Event;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Event;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventUnloadEventSampleData_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventUnloadEventSampleData_Parms, Event), Z_Construct_UClass_UFMODEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::NewProp_Event,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD" },
		{ "Comment", "/** Unload event sample data.\n\x09 * @param Event - event to load sample data from.\n\x09 */" },
		{ "DefaultToSelf", "WorldContextObject" },
		{ "HidePin", "WorldContextObject" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Unload event sample data.\n@param Event - event to load sample data from." },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "UnloadEventSampleData", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventUnloadEventSampleData_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics
	{
		struct FMODBlueprintStatics_eventVCASetVolume_Parms
		{
			UFMODVCA* Vca;
			float Volume;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Vca;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Volume;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::NewProp_Vca = { "Vca", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventVCASetVolume_Parms, Vca), Z_Construct_UClass_UFMODVCA_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::NewProp_Volume = { "Volume", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODBlueprintStatics_eventVCASetVolume_Parms, Volume), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::NewProp_Vca,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::NewProp_Volume,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|VCA" },
		{ "Comment", "/** Set volume on a VCA\n\x09 * @param Vca - VCA to use\n\x09 * @param Volume - volume\n\x09 */" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
		{ "ToolTip", "Set volume on a VCA\n@param Vca - VCA to use\n@param Volume - volume" },
		{ "UnsafeDuringActorConstruction", "true" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODBlueprintStatics, nullptr, "VCASetVolume", nullptr, nullptr, sizeof(FMODBlueprintStatics_eventVCASetVolume_Parms), Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UFMODBlueprintStatics_NoRegister()
	{
		return UFMODBlueprintStatics::StaticClass();
	}
	struct Z_Construct_UClass_UFMODBlueprintStatics_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODBlueprintStatics_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFMODBlueprintStatics_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_BusSetMute, "BusSetMute" }, // 714606804
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_BusSetPaused, "BusSetPaused" }, // 966718425
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_BusSetVolume, "BusSetVolume" }, // 3075182337
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_BusStopAllEvents, "BusStopAllEvents" }, // 1020414817
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameter, "EventInstanceGetParameter" }, // 1915885358
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceGetParameterValue, "EventInstanceGetParameterValue" }, // 1631337001
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceIsValid, "EventInstanceIsValid" }, // 2180219296
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceKeyOff, "EventInstanceKeyOff" }, // 3352169514
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstancePlay, "EventInstancePlay" }, // 1905927669
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceRelease, "EventInstanceRelease" }, // 1860839030
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetParameter, "EventInstanceSetParameter" }, // 2261564996
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPaused, "EventInstanceSetPaused" }, // 4288410155
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetPitch, "EventInstanceSetPitch" }, // 3584736686
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetProperty, "EventInstanceSetProperty" }, // 3561462903
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetTransform, "EventInstanceSetTransform" }, // 1876817962
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceSetVolume, "EventInstanceSetVolume" }, // 4051588896
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_EventInstanceStop, "EventInstanceStop" }, // 62701781
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_FindAssetByName, "FindAssetByName" }, // 129100614
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_FindEventByName, "FindEventByName" }, // 1877708210
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_FindEventInstances, "FindEventInstances" }, // 659245888
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterByName, "GetGlobalParameterByName" }, // 1112939552
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_GetGlobalParameterValueByName, "GetGlobalParameterValueByName" }, // 2232892789
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_GetOutputDrivers, "GetOutputDrivers" }, // 1011900475
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_IsBankLoaded, "IsBankLoaded" }, // 1546120277
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_LoadBank, "LoadBank" }, // 795330845
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_LoadBankSampleData, "LoadBankSampleData" }, // 36665782
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_LoadEventSampleData, "LoadEventSampleData" }, // 4238275259
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_MixerResume, "MixerResume" }, // 3576024406
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_MixerSuspend, "MixerSuspend" }, // 1380453362
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_PlayEvent2D, "PlayEvent2D" }, // 2384791466
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAtLocation, "PlayEventAtLocation" }, // 2415859971
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_PlayEventAttached, "PlayEventAttached" }, // 661395072
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_SetGlobalParameterByName, "SetGlobalParameterByName" }, // 3676849506
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_SetLocale, "SetLocale" }, // 2066386105
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByIndex, "SetOutputDriverByIndex" }, // 3262684055
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_SetOutputDriverByName, "SetOutputDriverByName" }, // 2241340473
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBank, "UnloadBank" }, // 4118580517
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_UnloadBankSampleData, "UnloadBankSampleData" }, // 2022836502
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_UnloadEventSampleData, "UnloadEventSampleData" }, // 584113536
		{ &Z_Construct_UFunction_UFMODBlueprintStatics_VCASetVolume, "VCASetVolume" }, // 363909536
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODBlueprintStatics_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "FMODBlueprintStatics.h" },
		{ "ModuleRelativePath", "Classes/FMODBlueprintStatics.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODBlueprintStatics_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODBlueprintStatics>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFMODBlueprintStatics_Statics::ClassParams = {
		&UFMODBlueprintStatics::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFMODBlueprintStatics_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODBlueprintStatics_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODBlueprintStatics()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFMODBlueprintStatics_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFMODBlueprintStatics, 2686371367);
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODBlueprintStatics>()
	{
		return UFMODBlueprintStatics::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFMODBlueprintStatics(Z_Construct_UClass_UFMODBlueprintStatics, &UFMODBlueprintStatics::StaticClass, TEXT("/Script/FMODStudio"), TEXT("UFMODBlueprintStatics"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODBlueprintStatics);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
