// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UStaticMesh;
#ifdef LEVELGENERATIONTOOL_LevelBlockout_generated_h
#error "LevelBlockout.generated.h already included, missing '#pragma once' in LevelBlockout.h"
#endif
#define LEVELGENERATIONTOOL_LevelBlockout_generated_h

#define LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetBasicBlock) \
	{ \
		P_GET_OBJECT(UStaticMesh,Z_Param_mesh); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->SetBasicBlock(Z_Param_mesh); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGenerate) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->Generate(); \
		P_NATIVE_END; \
	}


#define LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetBasicBlock) \
	{ \
		P_GET_OBJECT(UStaticMesh,Z_Param_mesh); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->SetBasicBlock(Z_Param_mesh); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGenerate) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->Generate(); \
		P_NATIVE_END; \
	}


#define LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesALevelBlockout(); \
	friend LEVELGENERATIONTOOL_API class UClass* Z_Construct_UClass_ALevelBlockout(); \
public: \
	DECLARE_CLASS(ALevelBlockout, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/LevelGenerationTool"), NO_API) \
	DECLARE_SERIALIZER(ALevelBlockout) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_INCLASS \
private: \
	static void StaticRegisterNativesALevelBlockout(); \
	friend LEVELGENERATIONTOOL_API class UClass* Z_Construct_UClass_ALevelBlockout(); \
public: \
	DECLARE_CLASS(ALevelBlockout, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/LevelGenerationTool"), NO_API) \
	DECLARE_SERIALIZER(ALevelBlockout) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ALevelBlockout(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ALevelBlockout) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALevelBlockout); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALevelBlockout); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALevelBlockout(ALevelBlockout&&); \
	NO_API ALevelBlockout(const ALevelBlockout&); \
public:


#define LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALevelBlockout(ALevelBlockout&&); \
	NO_API ALevelBlockout(const ALevelBlockout&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALevelBlockout); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALevelBlockout); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ALevelBlockout)


#define LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_PRIVATE_PROPERTY_OFFSET
#define LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_17_PROLOG
#define LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_PRIVATE_PROPERTY_OFFSET \
	LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_RPC_WRAPPERS \
	LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_INCLASS \
	LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_PRIVATE_PROPERTY_OFFSET \
	LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_INCLASS_NO_PURE_DECLS \
	LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LevelGenerationTool_Source_LevelGenerationTool_LevelBlockout_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
