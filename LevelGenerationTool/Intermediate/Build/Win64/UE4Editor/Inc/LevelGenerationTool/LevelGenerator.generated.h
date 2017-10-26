// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UStaticMesh;
struct FVector2D;
#ifdef LEVELGENERATIONTOOL_LevelGenerator_generated_h
#error "LevelGenerator.generated.h already included, missing '#pragma once' in LevelGenerator.h"
#endif
#define LEVELGENERATIONTOOL_LevelGenerator_generated_h

#define LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execEmptySubGridTest) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->EmptySubGridTest(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execEmptySurround) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_x); \
		P_GET_PROPERTY(UIntProperty,Z_Param_y); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->EmptySurround(Z_Param_x,Z_Param_y); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execEmptyAdjacent) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_x); \
		P_GET_PROPERTY(UIntProperty,Z_Param_y); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->EmptyAdjacent(Z_Param_x,Z_Param_y); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGenerateBlockout) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->GenerateBlockout(); \
		P_NATIVE_END; \
	} \
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
	DECLARE_FUNCTION(execDelaunayTriangulation) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->DelaunayTriangulation(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPartitionSpace) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_granularity); \
		P_GET_PROPERTY(UIntProperty,Z_Param_roomInset); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->PartitionSpace(Z_Param_granularity,Z_Param_roomInset); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRandomWalkBiased) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_steps); \
		P_GET_STRUCT(FVector2D,Z_Param_start); \
		P_GET_STRUCT(FVector2D,Z_Param_target); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RandomWalkBiased(Z_Param_steps,Z_Param_start,Z_Param_target); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRandomWalk) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_steps); \
		P_GET_STRUCT(FVector2D,Z_Param_start); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RandomWalk(Z_Param_steps,Z_Param_start); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPerfectMaze) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->PerfectMaze(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execNewGrid) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_width); \
		P_GET_PROPERTY(UIntProperty,Z_Param_height); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->NewGrid(Z_Param_width,Z_Param_height); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResetLevel) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ResetLevel(); \
		P_NATIVE_END; \
	}


#define LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execEmptySubGridTest) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->EmptySubGridTest(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execEmptySurround) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_x); \
		P_GET_PROPERTY(UIntProperty,Z_Param_y); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->EmptySurround(Z_Param_x,Z_Param_y); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execEmptyAdjacent) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_x); \
		P_GET_PROPERTY(UIntProperty,Z_Param_y); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->EmptyAdjacent(Z_Param_x,Z_Param_y); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGenerateBlockout) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->GenerateBlockout(); \
		P_NATIVE_END; \
	} \
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
	DECLARE_FUNCTION(execDelaunayTriangulation) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->DelaunayTriangulation(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPartitionSpace) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_granularity); \
		P_GET_PROPERTY(UIntProperty,Z_Param_roomInset); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->PartitionSpace(Z_Param_granularity,Z_Param_roomInset); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRandomWalkBiased) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_steps); \
		P_GET_STRUCT(FVector2D,Z_Param_start); \
		P_GET_STRUCT(FVector2D,Z_Param_target); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RandomWalkBiased(Z_Param_steps,Z_Param_start,Z_Param_target); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRandomWalk) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_steps); \
		P_GET_STRUCT(FVector2D,Z_Param_start); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RandomWalk(Z_Param_steps,Z_Param_start); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPerfectMaze) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->PerfectMaze(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execNewGrid) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_width); \
		P_GET_PROPERTY(UIntProperty,Z_Param_height); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->NewGrid(Z_Param_width,Z_Param_height); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResetLevel) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ResetLevel(); \
		P_NATIVE_END; \
	}


#define LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesALevelGenerator(); \
	friend LEVELGENERATIONTOOL_API class UClass* Z_Construct_UClass_ALevelGenerator(); \
public: \
	DECLARE_CLASS(ALevelGenerator, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/LevelGenerationTool"), NO_API) \
	DECLARE_SERIALIZER(ALevelGenerator) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_INCLASS \
private: \
	static void StaticRegisterNativesALevelGenerator(); \
	friend LEVELGENERATIONTOOL_API class UClass* Z_Construct_UClass_ALevelGenerator(); \
public: \
	DECLARE_CLASS(ALevelGenerator, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/LevelGenerationTool"), NO_API) \
	DECLARE_SERIALIZER(ALevelGenerator) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ALevelGenerator(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ALevelGenerator) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALevelGenerator); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALevelGenerator); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALevelGenerator(ALevelGenerator&&); \
	NO_API ALevelGenerator(const ALevelGenerator&); \
public:


#define LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALevelGenerator(ALevelGenerator&&); \
	NO_API ALevelGenerator(const ALevelGenerator&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALevelGenerator); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALevelGenerator); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ALevelGenerator)


#define LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_PRIVATE_PROPERTY_OFFSET
#define LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_11_PROLOG
#define LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_PRIVATE_PROPERTY_OFFSET \
	LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_RPC_WRAPPERS \
	LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_INCLASS \
	LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_PRIVATE_PROPERTY_OFFSET \
	LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_INCLASS_NO_PURE_DECLS \
	LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LevelGenerationTool_Source_LevelGenerationTool_LevelGenerator_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
