// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BTECZombies/ZombieHUD.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeZombieHUD() {}
// Cross Module References
	BTECZOMBIES_API UClass* Z_Construct_UClass_AZombieHUD_NoRegister();
	BTECZOMBIES_API UClass* Z_Construct_UClass_AZombieHUD();
	ENGINE_API UClass* Z_Construct_UClass_AHUD();
	UPackage* Z_Construct_UPackage__Script_BTECZombies();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
// End Cross Module References
	void AZombieHUD::StaticRegisterNativesAZombieHUD()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AZombieHUD);
	UClass* Z_Construct_UClass_AZombieHUD_NoRegister()
	{
		return AZombieHUD::StaticClass();
	}
	struct Z_Construct_UClass_AZombieHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__pCrosshairTexture_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__pCrosshairTexture;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AZombieHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_BTECZombies,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombieHUD_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "ZombieHUD.h" },
		{ "ModuleRelativePath", "ZombieHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombieHUD_Statics::NewProp__pCrosshairTexture_MetaData[] = {
		{ "Category", "ZombieHUD" },
		{ "ModuleRelativePath", "ZombieHUD.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AZombieHUD_Statics::NewProp__pCrosshairTexture = { "_pCrosshairTexture", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AZombieHUD, _pCrosshairTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AZombieHUD_Statics::NewProp__pCrosshairTexture_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AZombieHUD_Statics::NewProp__pCrosshairTexture_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AZombieHUD_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AZombieHUD_Statics::NewProp__pCrosshairTexture,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AZombieHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AZombieHUD>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AZombieHUD_Statics::ClassParams = {
		&AZombieHUD::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AZombieHUD_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AZombieHUD_Statics::PropPointers),
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AZombieHUD_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AZombieHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AZombieHUD()
	{
		if (!Z_Registration_Info_UClass_AZombieHUD.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AZombieHUD.OuterSingleton, Z_Construct_UClass_AZombieHUD_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AZombieHUD.OuterSingleton;
	}
	template<> BTECZOMBIES_API UClass* StaticClass<AZombieHUD>()
	{
		return AZombieHUD::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AZombieHUD);
	struct Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombieHUD_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombieHUD_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AZombieHUD, AZombieHUD::StaticClass, TEXT("AZombieHUD"), &Z_Registration_Info_UClass_AZombieHUD, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AZombieHUD), 426005429U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombieHUD_h_711690408(TEXT("/Script/BTECZombies"),
		Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombieHUD_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombieHUD_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
