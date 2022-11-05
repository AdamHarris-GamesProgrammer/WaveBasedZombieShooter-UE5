// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BTECZombies/BTECZombiesGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBTECZombiesGameModeBase() {}
// Cross Module References
	BTECZOMBIES_API UClass* Z_Construct_UClass_ABTECZombiesGameModeBase_NoRegister();
	BTECZOMBIES_API UClass* Z_Construct_UClass_ABTECZombiesGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_BTECZombies();
// End Cross Module References
	void ABTECZombiesGameModeBase::StaticRegisterNativesABTECZombiesGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ABTECZombiesGameModeBase);
	UClass* Z_Construct_UClass_ABTECZombiesGameModeBase_NoRegister()
	{
		return ABTECZombiesGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ABTECZombiesGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABTECZombiesGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_BTECZombies,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABTECZombiesGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "BTECZombiesGameModeBase.h" },
		{ "ModuleRelativePath", "BTECZombiesGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABTECZombiesGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABTECZombiesGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ABTECZombiesGameModeBase_Statics::ClassParams = {
		&ABTECZombiesGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ABTECZombiesGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ABTECZombiesGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ABTECZombiesGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ABTECZombiesGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABTECZombiesGameModeBase.OuterSingleton, Z_Construct_UClass_ABTECZombiesGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ABTECZombiesGameModeBase.OuterSingleton;
	}
	template<> BTECZOMBIES_API UClass* StaticClass<ABTECZombiesGameModeBase>()
	{
		return ABTECZombiesGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABTECZombiesGameModeBase);
	struct Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_BTECZombiesGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_BTECZombiesGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ABTECZombiesGameModeBase, ABTECZombiesGameModeBase::StaticClass, TEXT("ABTECZombiesGameModeBase"), &Z_Registration_Info_UClass_ABTECZombiesGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABTECZombiesGameModeBase), 3961287641U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_BTECZombiesGameModeBase_h_2779804570(TEXT("/Script/BTECZombies"),
		Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_BTECZombiesGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_BTECZombiesGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
