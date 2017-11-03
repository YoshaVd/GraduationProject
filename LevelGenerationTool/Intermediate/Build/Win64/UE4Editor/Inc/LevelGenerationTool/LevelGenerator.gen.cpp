// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "LevelGenerator.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLevelGenerator() {}
// Cross Module References
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_EmptySubGridTest();
	LEVELGENERATIONTOOL_API UClass* Z_Construct_UClass_ALevelGenerator();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_GenerateBlockout();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_GetSpawnLocation();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_NewGrid();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_PartitionSpace();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_PerfectMaze();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_RandomWalk();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_RandomWalkBiased();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_ResetLevel();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_SetBasicBlock();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_SetDeviation_Granularity();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_SetPercentage_DoubleCorridor();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_SetPercentage_WideCorridor();
	LEVELGENERATIONTOOL_API UClass* Z_Construct_UClass_ALevelGenerator_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_LevelGenerationTool();
	LEVELGENERATIONTOOL_API UClass* Z_Construct_UClass_ALevelBlockout_NoRegister();
// End Cross Module References
	void ALevelGenerator::StaticRegisterNativesALevelGenerator()
	{
		UClass* Class = ALevelGenerator::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "EmptySubGridTest", (Native)&ALevelGenerator::execEmptySubGridTest },
			{ "GenerateBlockout", (Native)&ALevelGenerator::execGenerateBlockout },
			{ "GetSpawnLocation", (Native)&ALevelGenerator::execGetSpawnLocation },
			{ "NewGrid", (Native)&ALevelGenerator::execNewGrid },
			{ "PartitionSpace", (Native)&ALevelGenerator::execPartitionSpace },
			{ "PerfectMaze", (Native)&ALevelGenerator::execPerfectMaze },
			{ "RandomWalk", (Native)&ALevelGenerator::execRandomWalk },
			{ "RandomWalkBiased", (Native)&ALevelGenerator::execRandomWalkBiased },
			{ "ResetLevel", (Native)&ALevelGenerator::execResetLevel },
			{ "SetBasicBlock", (Native)&ALevelGenerator::execSetBasicBlock },
			{ "SetDeviation_Granularity", (Native)&ALevelGenerator::execSetDeviation_Granularity },
			{ "SetPercentage_DoubleCorridor", (Native)&ALevelGenerator::execSetPercentage_DoubleCorridor },
			{ "SetPercentage_WideCorridor", (Native)&ALevelGenerator::execSetPercentage_WideCorridor },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, ARRAY_COUNT(AnsiFuncs));
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_EmptySubGridTest()
	{
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("EmptySubGridTest"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level Actions"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("test grid functionality"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_GenerateBlockout()
	{
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GenerateBlockout"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level Actions"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_GetSpawnLocation()
	{
		struct LevelGenerator_eventGetSpawnLocation_Parms
		{
			FVector ReturnValue;
		};
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GetSpawnLocation"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04820401, 65535, sizeof(LevelGenerator_eventGetSpawnLocation_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(ReturnValue, LevelGenerator_eventGetSpawnLocation_Parms), 0x0010000000000580, Z_Construct_UScriptStruct_FVector());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level Actions"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_NewGrid()
	{
		struct LevelGenerator_eventNewGrid_Parms
		{
			int32 width;
			int32 height;
		};
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("NewGrid"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535, sizeof(LevelGenerator_eventNewGrid_Parms));
			UProperty* NewProp_height = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("height"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(height, LevelGenerator_eventNewGrid_Parms), 0x0010000000000082);
			UProperty* NewProp_width = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("width"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(width, LevelGenerator_eventNewGrid_Parms), 0x0010000000000082);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level Actions"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
			MetaData->SetValue(NewProp_height, TEXT("NativeConst"), TEXT(""));
			MetaData->SetValue(NewProp_width, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_PartitionSpace()
	{
		struct LevelGenerator_eventPartitionSpace_Parms
		{
			int32 granularity;
			int32 roomInset;
		};
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("PartitionSpace"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535, sizeof(LevelGenerator_eventPartitionSpace_Parms));
			UProperty* NewProp_roomInset = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("roomInset"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(roomInset, LevelGenerator_eventPartitionSpace_Parms), 0x0010000000000082);
			UProperty* NewProp_granularity = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("granularity"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(granularity, LevelGenerator_eventPartitionSpace_Parms), 0x0010000000000082);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level Actions"));
			MetaData->SetValue(ReturnFunction, TEXT("CPP_Default_granularity"), TEXT("5"));
			MetaData->SetValue(ReturnFunction, TEXT("CPP_Default_roomInset"), TEXT("0"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
			MetaData->SetValue(NewProp_roomInset, TEXT("NativeConst"), TEXT(""));
			MetaData->SetValue(NewProp_granularity, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_PerfectMaze()
	{
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("PerfectMaze"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level Actions"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("algorithms"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_RandomWalk()
	{
		struct LevelGenerator_eventRandomWalk_Parms
		{
			int32 steps;
			FVector2D start;
		};
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("RandomWalk"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04820401, 65535, sizeof(LevelGenerator_eventRandomWalk_Parms));
			UProperty* NewProp_start = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("start"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(start, LevelGenerator_eventRandomWalk_Parms), 0x0010000000000082, Z_Construct_UScriptStruct_FVector2D());
			UProperty* NewProp_steps = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("steps"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(steps, LevelGenerator_eventRandomWalk_Parms), 0x0010000000000082);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level Actions"));
			MetaData->SetValue(ReturnFunction, TEXT("CPP_Default_start"), TEXT("(X=-1.000,Y=-1.000)"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
			MetaData->SetValue(NewProp_start, TEXT("NativeConst"), TEXT(""));
			MetaData->SetValue(NewProp_steps, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_RandomWalkBiased()
	{
		struct LevelGenerator_eventRandomWalkBiased_Parms
		{
			int32 steps;
			FVector2D start;
			FVector2D target;
		};
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("RandomWalkBiased"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04820401, 65535, sizeof(LevelGenerator_eventRandomWalkBiased_Parms));
			UProperty* NewProp_target = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("target"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(target, LevelGenerator_eventRandomWalkBiased_Parms), 0x0010000000000082, Z_Construct_UScriptStruct_FVector2D());
			UProperty* NewProp_start = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("start"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(start, LevelGenerator_eventRandomWalkBiased_Parms), 0x0010000000000082, Z_Construct_UScriptStruct_FVector2D());
			UProperty* NewProp_steps = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("steps"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(steps, LevelGenerator_eventRandomWalkBiased_Parms), 0x0010000000000082);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level Actions"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
			MetaData->SetValue(NewProp_target, TEXT("NativeConst"), TEXT(""));
			MetaData->SetValue(NewProp_start, TEXT("NativeConst"), TEXT(""));
			MetaData->SetValue(NewProp_steps, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_ResetLevel()
	{
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("ResetLevel"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level Actions"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_SetBasicBlock()
	{
		struct LevelGenerator_eventSetBasicBlock_Parms
		{
			UStaticMesh* mesh;
		};
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SetBasicBlock"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535, sizeof(LevelGenerator_eventSetBasicBlock_Parms));
			UProperty* NewProp_mesh = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("mesh"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(mesh, LevelGenerator_eventSetBasicBlock_Parms), 0x0010000000000080, Z_Construct_UClass_UStaticMesh_NoRegister());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level Actions"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("blockout code"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_SetDeviation_Granularity()
	{
		struct LevelGenerator_eventSetDeviation_Granularity_Parms
		{
			int32 deviation;
		};
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SetDeviation_Granularity"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535, sizeof(LevelGenerator_eventSetDeviation_Granularity_Parms));
			UProperty* NewProp_deviation = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("deviation"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(deviation, LevelGenerator_eventSetDeviation_Granularity_Parms), 0x0010000000000082);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level parameters"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
			MetaData->SetValue(NewProp_deviation, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_SetPercentage_DoubleCorridor()
	{
		struct LevelGenerator_eventSetPercentage_DoubleCorridor_Parms
		{
			int32 odds;
		};
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SetPercentage_DoubleCorridor"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535, sizeof(LevelGenerator_eventSetPercentage_DoubleCorridor_Parms));
			UProperty* NewProp_odds = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("odds"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(odds, LevelGenerator_eventSetPercentage_DoubleCorridor_Parms), 0x0010000000000082);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level parameters"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
			MetaData->SetValue(NewProp_odds, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALevelGenerator_SetPercentage_WideCorridor()
	{
		struct LevelGenerator_eventSetPercentage_WideCorridor_Parms
		{
			int32 odds;
		};
		UObject* Outer = Z_Construct_UClass_ALevelGenerator();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SetPercentage_WideCorridor"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535, sizeof(LevelGenerator_eventSetPercentage_WideCorridor_Parms));
			UProperty* NewProp_odds = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("odds"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(odds, LevelGenerator_eventSetPercentage_WideCorridor_Parms), 0x0010000000000082);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Level parameters"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("set level parameters"));
			MetaData->SetValue(NewProp_odds, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ALevelGenerator_NoRegister()
	{
		return ALevelGenerator::StaticClass();
	}
	UClass* Z_Construct_UClass_ALevelGenerator()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_LevelGenerationTool();
			OuterClass = ALevelGenerator::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= (EClassFlags)0x20900080u;

				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_EmptySubGridTest());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_GenerateBlockout());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_GetSpawnLocation());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_NewGrid());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_PartitionSpace());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_PerfectMaze());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_RandomWalk());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_RandomWalkBiased());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_ResetLevel());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_SetBasicBlock());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_SetDeviation_Granularity());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_SetPercentage_DoubleCorridor());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_SetPercentage_WideCorridor());

				UProperty* NewProp__pLevelBlockout = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("_pLevelBlockout"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(_pLevelBlockout, ALevelGenerator), 0x0010000000000005, Z_Construct_UClass_ALevelBlockout_NoRegister());
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_EmptySubGridTest(), "EmptySubGridTest"); // 616385459
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_GenerateBlockout(), "GenerateBlockout"); // 3395057221
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_GetSpawnLocation(), "GetSpawnLocation"); // 970805539
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_NewGrid(), "NewGrid"); // 1297228795
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_PartitionSpace(), "PartitionSpace"); // 4117621945
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_PerfectMaze(), "PerfectMaze"); // 1284617506
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_RandomWalk(), "RandomWalk"); // 4051217133
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_RandomWalkBiased(), "RandomWalkBiased"); // 211378781
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_ResetLevel(), "ResetLevel"); // 1710962714
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_SetBasicBlock(), "SetBasicBlock"); // 2312428768
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_SetDeviation_Granularity(), "SetDeviation_Granularity"); // 2209787177
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_SetPercentage_DoubleCorridor(), "SetPercentage_DoubleCorridor"); // 3412002295
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_SetPercentage_WideCorridor(), "SetPercentage_WideCorridor"); // 1616273556
				static TCppClassTypeInfo<TCppClassTypeTraits<ALevelGenerator> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("LevelGenerator.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
				MetaData->SetValue(NewProp__pLevelBlockout, TEXT("Category"), TEXT("LevelGenerator"));
				MetaData->SetValue(NewProp__pLevelBlockout, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALevelGenerator, 3187746054);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALevelGenerator(Z_Construct_UClass_ALevelGenerator, &ALevelGenerator::StaticClass, TEXT("/Script/LevelGenerationTool"), TEXT("ALevelGenerator"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALevelGenerator);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
