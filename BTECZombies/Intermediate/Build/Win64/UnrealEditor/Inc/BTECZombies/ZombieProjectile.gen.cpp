// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BTECZombies/ZombieProjectile.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeZombieProjectile() {}
// Cross Module References
	BTECZOMBIES_API UClass* Z_Construct_UClass_AZombieProjectile_NoRegister();
	BTECZOMBIES_API UClass* Z_Construct_UClass_AZombieProjectile();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_BTECZombies();
	ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UProjectileMovementComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AZombieProjectile::execOnHit)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComponent);
		P_GET_OBJECT(AActor,Z_Param_OtherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComponent);
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse);
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnHit(Z_Param_HitComponent,Z_Param_OtherActor,Z_Param_OtherComponent,Z_Param_NormalImpulse,Z_Param_Out_Hit);
		P_NATIVE_END;
	}
	void AZombieProjectile::StaticRegisterNativesAZombieProjectile()
	{
		UClass* Class = AZombieProjectile::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnHit", &AZombieProjectile::execOnHit },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AZombieProjectile_OnHit_Statics
	{
		struct ZombieProjectile_eventOnHit_Parms
		{
			UPrimitiveComponent* HitComponent;
			AActor* OtherActor;
			UPrimitiveComponent* OtherComponent;
			FVector NormalImpulse;
			FHitResult Hit;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_HitComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_HitComponent;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OtherComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComponent;
		static const UECodeGen_Private::FStructPropertyParams NewProp_NormalImpulse;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Hit_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Hit;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_HitComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_HitComponent = { "HitComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZombieProjectile_eventOnHit_Parms, HitComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_HitComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_HitComponent_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZombieProjectile_eventOnHit_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_OtherComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_OtherComponent = { "OtherComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZombieProjectile_eventOnHit_Parms, OtherComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_OtherComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_OtherComponent_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_NormalImpulse = { "NormalImpulse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZombieProjectile_eventOnHit_Parms, NormalImpulse), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_Hit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_Hit = { "Hit", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZombieProjectile_eventOnHit_Parms, Hit), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_Hit_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_Hit_MetaData)) }; // 1416937132
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_HitComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_OtherActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_OtherComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_NormalImpulse,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::NewProp_Hit,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ZombieProjectile.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AZombieProjectile, nullptr, "OnHit", nullptr, nullptr, sizeof(Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::ZombieProjectile_eventOnHit_Parms), Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AZombieProjectile_OnHit()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AZombieProjectile_OnHit_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AZombieProjectile);
	UClass* Z_Construct_UClass_AZombieProjectile_NoRegister()
	{
		return AZombieProjectile::StaticClass();
	}
	struct Z_Construct_UClass_AZombieProjectile_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__pCollisionComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__pCollisionComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__pProjectileMovementComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__pProjectileMovementComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__pProjectileMeshComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__pProjectileMeshComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__pProjectileMaterial_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__pProjectileMaterial;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AZombieProjectile_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_BTECZombies,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AZombieProjectile_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AZombieProjectile_OnHit, "OnHit" }, // 2712026436
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombieProjectile_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ZombieProjectile.h" },
		{ "ModuleRelativePath", "ZombieProjectile.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pCollisionComponent_MetaData[] = {
		{ "Category", "Projectile" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ZombieProjectile.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pCollisionComponent = { "_pCollisionComponent", nullptr, (EPropertyFlags)0x00100000000b0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AZombieProjectile, _pCollisionComponent), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pCollisionComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pCollisionComponent_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMovementComponent_MetaData[] = {
		{ "Category", "Movement" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ZombieProjectile.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMovementComponent = { "_pProjectileMovementComponent", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AZombieProjectile, _pProjectileMovementComponent), Z_Construct_UClass_UProjectileMovementComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMovementComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMovementComponent_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMeshComponent_MetaData[] = {
		{ "Category", "Projectile" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ZombieProjectile.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMeshComponent = { "_pProjectileMeshComponent", nullptr, (EPropertyFlags)0x00100000000b0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AZombieProjectile, _pProjectileMeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMeshComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMeshComponent_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMaterial_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "ZombieProjectile.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMaterial = { "_pProjectileMaterial", nullptr, (EPropertyFlags)0x0010000000030001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AZombieProjectile, _pProjectileMaterial), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMaterial_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AZombieProjectile_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pCollisionComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMovementComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMeshComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AZombieProjectile_Statics::NewProp__pProjectileMaterial,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AZombieProjectile_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AZombieProjectile>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AZombieProjectile_Statics::ClassParams = {
		&AZombieProjectile::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AZombieProjectile_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AZombieProjectile_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AZombieProjectile_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AZombieProjectile_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AZombieProjectile()
	{
		if (!Z_Registration_Info_UClass_AZombieProjectile.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AZombieProjectile.OuterSingleton, Z_Construct_UClass_AZombieProjectile_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AZombieProjectile.OuterSingleton;
	}
	template<> BTECZOMBIES_API UClass* StaticClass<AZombieProjectile>()
	{
		return AZombieProjectile::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AZombieProjectile);
	struct Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AZombieProjectile, AZombieProjectile::StaticClass, TEXT("AZombieProjectile"), &Z_Registration_Info_UClass_AZombieProjectile, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AZombieProjectile), 3846718779U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_41514479(TEXT("/Script/BTECZombies"),
		Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombieProjectile_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
