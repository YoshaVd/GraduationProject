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
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_GenerateBlockout();
	LEVELGENERATIONTOOL_API UClass* Z_Construct_UClass_ALevelGenerator();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_NewGrid();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_PerfectMaze();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_ResetLevel();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelGenerator_SetBasicBlock();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
	LEVELGENERATIONTOOL_API UClass* Z_Construct_UClass_ALevelGenerator_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_LevelGenerationTool();
// End Cross Module References
	void ALevelGenerator::StaticRegisterNativesALevelGenerator()
	{
		UClass* Class = ALevelGenerator::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "GenerateBlockout", (Native)&ALevelGenerator::execGenerateBlockout },
			{ "NewGrid", (Native)&ALevelGenerator::execNewGrid },
			{ "PerfectMaze", (Native)&ALevelGenerator::execPerfectMaze },
			{ "ResetLevel", (Native)&ALevelGenerator::execResetLevel },
			{ "SetBasicBlock", (Native)&ALevelGenerator::execSetBasicBlock },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, ARRAY_COUNT(AnsiFuncs));
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

				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_GenerateBlockout());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_NewGrid());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_PerfectMaze());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_ResetLevel());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelGenerator_SetBasicBlock());

				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_GenerateBlockout(), "GenerateBlockout"); // 3395057221
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_NewGrid(), "NewGrid"); // 1297228795
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_PerfectMaze(), "PerfectMaze"); // 1001929933
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_ResetLevel(), "ResetLevel"); // 1710962714
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelGenerator_SetBasicBlock(), "SetBasicBlock"); // 2355805464
				static TCppClassTypeInfo<TCppClassTypeTraits<ALevelGenerator> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("LevelGenerator.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("LevelGenerator.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALevelGenerator, 176774438);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALevelGenerator(Z_Construct_UClass_ALevelGenerator, &ALevelGenerator::StaticClass, TEXT("/Script/LevelGenerationTool"), TEXT("ALevelGenerator"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALevelGenerator);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
