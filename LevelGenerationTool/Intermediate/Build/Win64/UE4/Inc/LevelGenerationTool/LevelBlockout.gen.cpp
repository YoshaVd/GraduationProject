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
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelBlockout_GenerateBlockout();
	LEVELGENERATIONTOOL_API UClass* Z_Construct_UClass_ALevelBlockout();
	LEVELGENERATIONTOOL_API UFunction* Z_Construct_UFunction_ALevelBlockout_SetBasicBlock();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
	LEVELGENERATIONTOOL_API UClass* Z_Construct_UClass_ALevelBlockout_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_LevelGenerationTool();
// End Cross Module References
	void ALevelBlockout::StaticRegisterNativesALevelBlockout()
	{
		UClass* Class = ALevelBlockout::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "GenerateBlockout", (Native)&ALevelBlockout::execGenerateBlockout },
			{ "SetBasicBlock", (Native)&ALevelBlockout::execSetBasicBlock },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, ARRAY_COUNT(AnsiFuncs));
	}
	UFunction* Z_Construct_UFunction_ALevelBlockout_GenerateBlockout()
	{
		UObject* Outer = Z_Construct_UClass_ALevelBlockout();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GenerateBlockout"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535);
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

				OuterClass->LinkChild(Z_Construct_UFunction_ALevelBlockout_GenerateBlockout());
				OuterClass->LinkChild(Z_Construct_UFunction_ALevelBlockout_SetBasicBlock());

				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelBlockout_GenerateBlockout(), "GenerateBlockout"); // 742444291
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALevelBlockout_SetBasicBlock(), "SetBasicBlock"); // 79993034
				static TCppClassTypeInfo<TCppClassTypeTraits<ALevelBlockout> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("LevelBlockout.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("LevelBlockout.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALevelBlockout, 830536886);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALevelBlockout(Z_Construct_UClass_ALevelBlockout, &ALevelBlockout::StaticClass, TEXT("/Script/LevelGenerationTool"), TEXT("ALevelBlockout"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALevelBlockout);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
