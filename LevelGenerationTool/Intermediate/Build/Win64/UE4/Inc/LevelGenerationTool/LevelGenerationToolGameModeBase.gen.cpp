// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "LevelGenerationToolGameModeBase.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLevelGenerationToolGameModeBase() {}
// Cross Module References
	LEVELGENERATIONTOOL_API UClass* Z_Construct_UClass_ALevelGenerationToolGameModeBase_NoRegister();
	LEVELGENERATIONTOOL_API UClass* Z_Construct_UClass_ALevelGenerationToolGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_LevelGenerationTool();
// End Cross Module References
	void ALevelGenerationToolGameModeBase::StaticRegisterNativesALevelGenerationToolGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_ALevelGenerationToolGameModeBase_NoRegister()
	{
		return ALevelGenerationToolGameModeBase::StaticClass();
	}
	UClass* Z_Construct_UClass_ALevelGenerationToolGameModeBase()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AGameModeBase();
			Z_Construct_UPackage__Script_LevelGenerationTool();
			OuterClass = ALevelGenerationToolGameModeBase::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= (EClassFlags)0x20900288u;


				static TCppClassTypeInfo<TCppClassTypeTraits<ALevelGenerationToolGameModeBase> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("HideCategories"), TEXT("Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("LevelGenerationToolGameModeBase.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("LevelGenerationToolGameModeBase.h"));
				MetaData->SetValue(OuterClass, TEXT("ShowCategories"), TEXT("Input|MouseInput Input|TouchInput"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALevelGenerationToolGameModeBase, 891996885);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALevelGenerationToolGameModeBase(Z_Construct_UClass_ALevelGenerationToolGameModeBase, &ALevelGenerationToolGameModeBase::StaticClass, TEXT("/Script/LevelGenerationTool"), TEXT("ALevelGenerationToolGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALevelGenerationToolGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
