// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "LevelBlockout.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLevelBlockout() {}
// Cross Module References
	LEVELGENERATIONTOOL_API UEnum* Z_Construct_UEnum_LevelGenerationTool_EProp();
	UPackage* Z_Construct_UPackage__Script_LevelGenerationTool();
	LEVELGENERATIONTOOL_API UScriptStruct* Z_Construct_UScriptStruct_FSpawnData();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelBlockout_Generate();
	LEVELGENERATIONTOOL_API UClass* Z_Construct_UClass_ALevelBlockout();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelBlockout_SetBasicBlock();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
	LEVELGENERATIONTOOL_API UClass* Z_Construct_UClass_ALevelBlockout_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
// End Cross Module References
static UEnum* EProp_StaticEnum()
{
	static UEnum* Singleton = nullptr;
	if (!Singleton)
	{
		Singleton = GetStaticEnum(Z_Construct_UEnum_LevelGenerationTool_EProp, Z_Construct_UPackage__Script_LevelGenerationTool(), TEXT("EProp"));
	}
	return Singleton;
}
static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EProp(EProp_StaticEnum, TEXT("/Script/LevelGenerationTool"), TEXT("EProp"), false, nullptr, nullptr);
	UEnum* Z_Construct_UEnum_LevelGenerationTool_EProp()
	{
		UPackage* Outer = Z_Construct_UPackage__Script_LevelGenerationTool();
		extern uint32 Get_Z_Construct_UEnum_LevelGenerationTool_EProp_CRC();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EProp"), 0, Get_Z_Construct_UEnum_LevelGenerationTool_EProp_CRC(), false);
		if (!ReturnEnum)
		{
			ReturnEnum = new(EC_InternalUseOnlyConstructor, Outer, TEXT("EProp"), RF_Public|RF_Transient|RF_MarkAsNative) UEnum(FObjectInitializer());
			TArray<TPair<FName, int64>> EnumNames;
			EnumNames.Emplace(TEXT("EProp::E_KEY"), 0);
			EnumNames.Emplace(TEXT("EProp::E_DOOR_OPEN"), 1);
			EnumNames.Emplace(TEXT("EProp::E_DOOR_LOCKED"), 2);
			EnumNames.Emplace(TEXT("EProp::E_MAX"), 3);
			ReturnEnum->SetEnums(EnumNames, UEnum::ECppForm::EnumClass);
			ReturnEnum->CppType = TEXT("EProp");
#if WITH_METADATA
			UMetaData* MetaData = ReturnEnum->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnEnum, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnEnum, TEXT("E_DOOR_LOCKED.DisplayName"), TEXT("Door Locked"));
			MetaData->SetValue(ReturnEnum, TEXT("E_DOOR_OPEN.DisplayName"), TEXT("Door Open"));
			MetaData->SetValue(ReturnEnum, TEXT("E_KEY.DisplayName"), TEXT("Key"));
			MetaData->SetValue(ReturnEnum, TEXT("ModuleRelativePath"), TEXT("LevelBlockout.h"));
#endif
		}
		return ReturnEnum;
	}
	uint32 Get_Z_Construct_UEnum_LevelGenerationTool_EProp_CRC() { return 375176716U; }
class UScriptStruct* FSpawnData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LEVELGENERATIONTOOL_API uint32 Get_Z_Construct_UScriptStruct_FSpawnData_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSpawnData, Z_Construct_UPackage__Script_LevelGenerationTool(), TEXT("SpawnData"), sizeof(FSpawnData), Get_Z_Construct_UScriptStruct_FSpawnData_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSpawnData(FSpawnData::StaticStruct, TEXT("/Script/LevelGenerationTool"), TEXT("SpawnData"), false, nullptr, nullptr);
static struct FScriptStruct_LevelGenerationTool_StaticRegisterNativesFSpawnData
{
	FScriptStruct_LevelGenerationTool_StaticRegisterNativesFSpawnData()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("SpawnData")),new UScriptStruct::TCppStructOps<FSpawnData>);
	}
} ScriptStruct_LevelGenerationTool_StaticRegisterNativesFSpawnData;
	UScriptStruct* Z_Construct_UScriptStruct_FSpawnData()
	{
		UPackage* Outer = Z_Construct_UPackage__Script_LevelGenerationTool();
		extern uint32 Get_Z_Construct_UScriptStruct_FSpawnData_CRC();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SpawnData"), sizeof(FSpawnData), Get_Z_Construct_UScriptStruct_FSpawnData_CRC(), false);
		if (!ReturnStruct)
		{
			ReturnStruct = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SpawnData"), RF_Public|RF_Transient|RF_MarkAsNative) UScriptStruct(FObjectInitializer(), NULL, new UScriptStruct::TCppStructOps<FSpawnData>, EStructFlags(0x00000001));
			UProperty* NewProp__prop = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("_prop"), RF_Public|RF_Transient|RF_MarkAsNative) UEnumProperty(CPP_PROPERTY_BASE(_prop, FSpawnData), 0x0010000000000005, Z_Construct_UEnum_LevelGenerationTool_EProp());
			UProperty* NewProp__prop_Underlying = new(EC_InternalUseOnlyConstructor, NewProp__prop, TEXT("UnderlyingType"), RF_Public|RF_Transient|RF_MarkAsNative) UByteProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000);
			UProperty* NewProp__position = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("_position"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(_position, FSpawnData), 0x0010000000000005, Z_Construct_UScriptStruct_FVector());
			ReturnStruct->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnStruct->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnStruct, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("ModuleRelativePath"), TEXT("LevelBlockout.h"));
			MetaData->SetValue(NewProp__prop, TEXT("Category"), TEXT("SpawnData"));
			MetaData->SetValue(NewProp__prop, TEXT("ModuleRelativePath"), TEXT("LevelBlockout.h"));
			MetaData->SetValue(NewProp__position, TEXT("Category"), TEXT("SpawnData"));
			MetaData->SetValue(NewProp__position, TEXT("ModuleRelativePath"), TEXT("LevelBlockout.h"));
#endif
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSpawnData_CRC() { return 4048164331U; }
	void ALevelBlockout::StaticRegisterNativesALevelBlockout()
	{
		UClass* Class = ALevelBlockout::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "Generate", (Native)&ALevelBlockout::execGenerate },
			{ "SetBasicBlock", (Native)&ALevelBlockout::execSetBasicBlock },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, ARRAY_COUNT(AnsiFuncs));
	}
	UFunction* Z_Construct_UFunction_ALevelBlockout_Generate()
	{
		UObject* Outer = Z_Construct_UClass_ALevelBlockout();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("Generate"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("GridActions"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelBlockout.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelBlockout_SetBasicBlock()
	{
		struct LevelBlockout_eventSetBasicBlock_Parms
		{
			UStaticMesh* mesh;
		};
		UObject* Outer = Z_Construct_UClass_ALevelBlockout();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SetBasicBlock"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535, sizeof(LevelBlockout_eventSetBasicBlock_Parms));
			UProperty* NewProp_mesh = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("mesh"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(mesh, LevelBlockout_eventSetBasicBlock_Parms), 0x0010000000000080, Z_Construct_UClass_UStaticMesh_NoRegister());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("GridSettings"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelBlockout.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ALevelBlockout_NoRegister()
	{
		return ALevelBlockout::StaticClass();
	}
	UClass* Z_Construct_UClass_ALevelBlockout()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_LevelGenerationTool();
			OuterClass = ALevelBlockout::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= (EClassFlags)0x20900080u;

				OuterClass->LinkChild(Z_Construct_UFunction_ALevelBlockout_Generate());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelBlockout_SetBasicBlock());

				UProperty* NewProp__spawnData = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("_spawnData"), RF_Public|RF_Transient|RF_MarkAsNative) UArrayProperty(CPP_PROPERTY_BASE(_spawnData, ALevelBlockout), 0x0010000000000005);
				UProperty* NewProp__spawnData_Inner = new(EC_InternalUseOnlyConstructor, NewProp__spawnData, TEXT("_spawnData"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000, Z_Construct_UScriptStruct_FSpawnData());
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelBlockout_Generate(), "Generate"); // 1576755506
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelBlockout_SetBasicBlock(), "SetBasicBlock"); // 79993034
				static TCppClassTypeInfo<TCppClassTypeTraits<ALevelBlockout> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("LevelBlockout.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("LevelBlockout.h"));
				MetaData->SetValue(NewProp__spawnData, TEXT("Category"), TEXT("LevelBlockout"));
				MetaData->SetValue(NewProp__spawnData, TEXT("ModuleRelativePath"), TEXT("LevelBlockout.h"));
				MetaData->SetValue(NewProp__spawnData, TEXT("ToolTip"), TEXT("--- Members ---"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALevelBlockout, 2494350274);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALevelBlockout(Z_Construct_UClass_ALevelBlockout, &ALevelBlockout::StaticClass, TEXT("/Script/LevelGenerationTool"), TEXT("ALevelBlockout"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALevelBlockout);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
