// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef BTECZOMBIES_ZombiePlayerController_generated_h
#error "ZombiePlayerController.generated.h already included, missing '#pragma once' in ZombiePlayerController.h"
#endif
#define BTECZOMBIES_ZombiePlayerController_generated_h

#define FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_SPARSE_DATA
#define FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execFire); \
	DECLARE_FUNCTION(execStopJump); \
	DECLARE_FUNCTION(execStartJump); \
	DECLARE_FUNCTION(execLookUp); \
	DECLARE_FUNCTION(execTurn); \
	DECLARE_FUNCTION(execMoveRight); \
	DECLARE_FUNCTION(execMoveForward);


#define FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execFire); \
	DECLARE_FUNCTION(execStopJump); \
	DECLARE_FUNCTION(execStartJump); \
	DECLARE_FUNCTION(execLookUp); \
	DECLARE_FUNCTION(execTurn); \
	DECLARE_FUNCTION(execMoveRight); \
	DECLARE_FUNCTION(execMoveForward);


#define FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAZombiePlayerController(); \
	friend struct Z_Construct_UClass_AZombiePlayerController_Statics; \
public: \
	DECLARE_CLASS(AZombiePlayerController, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/BTECZombies"), NO_API) \
	DECLARE_SERIALIZER(AZombiePlayerController)


#define FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_INCLASS \
private: \
	static void StaticRegisterNativesAZombiePlayerController(); \
	friend struct Z_Construct_UClass_AZombiePlayerController_Statics; \
public: \
	DECLARE_CLASS(AZombiePlayerController, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/BTECZombies"), NO_API) \
	DECLARE_SERIALIZER(AZombiePlayerController)


#define FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AZombiePlayerController(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AZombiePlayerController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AZombiePlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AZombiePlayerController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AZombiePlayerController(AZombiePlayerController&&); \
	NO_API AZombiePlayerController(const AZombiePlayerController&); \
public:


#define FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AZombiePlayerController(AZombiePlayerController&&); \
	NO_API AZombiePlayerController(const AZombiePlayerController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AZombiePlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AZombiePlayerController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AZombiePlayerController)


#define FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_17_PROLOG
#define FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_SPARSE_DATA \
	FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_RPC_WRAPPERS \
	FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_INCLASS \
	FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_SPARSE_DATA \
	FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_INCLASS_NO_PURE_DECLS \
	FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> BTECZOMBIES_API UClass* StaticClass<class AZombiePlayerController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
