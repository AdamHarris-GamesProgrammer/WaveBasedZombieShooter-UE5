// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef BTECZOMBIES_ZombieProjectile_generated_h
#error "ZombieProjectile.generated.h already included, missing '#pragma once' in ZombieProjectile.h"
#endif
#define BTECZOMBIES_ZombieProjectile_generated_h

#define FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_SPARSE_DATA
#define FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit);


#define FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit);


#define FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAZombieProjectile(); \
	friend struct Z_Construct_UClass_AZombieProjectile_Statics; \
public: \
	DECLARE_CLASS(AZombieProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/BTECZombies"), NO_API) \
	DECLARE_SERIALIZER(AZombieProjectile)


#define FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_INCLASS \
private: \
	static void StaticRegisterNativesAZombieProjectile(); \
	friend struct Z_Construct_UClass_AZombieProjectile_Statics; \
public: \
	DECLARE_CLASS(AZombieProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/BTECZombies"), NO_API) \
	DECLARE_SERIALIZER(AZombieProjectile)


#define FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AZombieProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AZombieProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AZombieProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AZombieProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AZombieProjectile(AZombieProjectile&&); \
	NO_API AZombieProjectile(const AZombieProjectile&); \
public:


#define FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AZombieProjectile(AZombieProjectile&&); \
	NO_API AZombieProjectile(const AZombieProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AZombieProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AZombieProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AZombieProjectile)


#define FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_14_PROLOG
#define FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_SPARSE_DATA \
	FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_RPC_WRAPPERS \
	FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_INCLASS \
	FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_SPARSE_DATA \
	FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_INCLASS_NO_PURE_DECLS \
	FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> BTECZOMBIES_API UClass* StaticClass<class AZombieProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
