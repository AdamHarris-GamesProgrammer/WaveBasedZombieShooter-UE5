// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BTECZombies/ZombiePlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeZombiePlayerController() {}
// Cross Module References
	BTECZOMBIES_API UClass* Z_Construct_UClass_AZombiePlayerController_NoRegister();
	BTECZOMBIES_API UClass* Z_Construct_UClass_AZombiePlayerController();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_BTECZombies();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	BTECZOMBIES_API UClass* Z_Construct_UClass_AZombieProjectile_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AZombiePlayerController::execFire)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Fire();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AZombiePlayerController::execStopJump)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StopJump();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AZombiePlayerController::execStartJump)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StartJump();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AZombiePlayerController::execLookUp)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->LookUp(Z_Param_value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AZombiePlayerController::execTurn)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Turn(Z_Param_value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AZombiePlayerController::execMoveRight)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->MoveRight(Z_Param_value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AZombiePlayerController::execMoveForward)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->MoveForward(Z_Param_value);
		P_NATIVE_END;
	}
	void AZombiePlayerController::StaticRegisterNativesAZombiePlayerController()
	{
		UClass* Class = AZombiePlayerController::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Fire", &AZombiePlayerController::execFire },
			{ "LookUp", &AZombiePlayerController::execLookUp },
			{ "MoveForward", &AZombiePlayerController::execMoveForward },
			{ "MoveRight", &AZombiePlayerController::execMoveRight },
			{ "StartJump", &AZombiePlayerController::execStartJump },
			{ "StopJump", &AZombiePlayerController::execStopJump },
			{ "Turn", &AZombiePlayerController::execTurn },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AZombiePlayerController_Fire_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AZombiePlayerController_Fire_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AZombiePlayerController_Fire_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AZombiePlayerController, nullptr, "Fire", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AZombiePlayerController_Fire_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombiePlayerController_Fire_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AZombiePlayerController_Fire()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AZombiePlayerController_Fire_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics
	{
		struct ZombiePlayerController_eventLookUp_Parms
		{
			float value;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZombiePlayerController_eventLookUp_Parms, value), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics::NewProp_value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AZombiePlayerController, nullptr, "LookUp", nullptr, nullptr, sizeof(Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics::ZombiePlayerController_eventLookUp_Parms), Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AZombiePlayerController_LookUp()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AZombiePlayerController_LookUp_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics
	{
		struct ZombiePlayerController_eventMoveForward_Parms
		{
			float value;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZombiePlayerController_eventMoveForward_Parms, value), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics::NewProp_value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics::Function_MetaDataParams[] = {
		{ "Comment", "//Handles moving forward and backward\n//Adding UFUNCTION macro means that the engine is aware of these functions and will be included in serialization\n" },
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
		{ "ToolTip", "Handles moving forward and backward\nAdding UFUNCTION macro means that the engine is aware of these functions and will be included in serialization" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AZombiePlayerController, nullptr, "MoveForward", nullptr, nullptr, sizeof(Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics::ZombiePlayerController_eventMoveForward_Parms), Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AZombiePlayerController_MoveForward()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AZombiePlayerController_MoveForward_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics
	{
		struct ZombiePlayerController_eventMoveRight_Parms
		{
			float value;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZombiePlayerController_eventMoveRight_Parms, value), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics::NewProp_value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics::Function_MetaDataParams[] = {
		{ "Comment", "//Handles moving right and left\n" },
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
		{ "ToolTip", "Handles moving right and left" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AZombiePlayerController, nullptr, "MoveRight", nullptr, nullptr, sizeof(Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics::ZombiePlayerController_eventMoveRight_Parms), Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AZombiePlayerController_MoveRight()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AZombiePlayerController_MoveRight_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AZombiePlayerController_StartJump_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AZombiePlayerController_StartJump_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AZombiePlayerController_StartJump_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AZombiePlayerController, nullptr, "StartJump", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AZombiePlayerController_StartJump_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombiePlayerController_StartJump_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AZombiePlayerController_StartJump()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AZombiePlayerController_StartJump_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AZombiePlayerController_StopJump_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AZombiePlayerController_StopJump_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AZombiePlayerController_StopJump_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AZombiePlayerController, nullptr, "StopJump", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AZombiePlayerController_StopJump_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombiePlayerController_StopJump_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AZombiePlayerController_StopJump()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AZombiePlayerController_StopJump_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AZombiePlayerController_Turn_Statics
	{
		struct ZombiePlayerController_eventTurn_Parms
		{
			float value;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AZombiePlayerController_Turn_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ZombiePlayerController_eventTurn_Parms, value), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AZombiePlayerController_Turn_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AZombiePlayerController_Turn_Statics::NewProp_value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AZombiePlayerController_Turn_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AZombiePlayerController_Turn_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AZombiePlayerController, nullptr, "Turn", nullptr, nullptr, sizeof(Z_Construct_UFunction_AZombiePlayerController_Turn_Statics::ZombiePlayerController_eventTurn_Parms), Z_Construct_UFunction_AZombiePlayerController_Turn_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombiePlayerController_Turn_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AZombiePlayerController_Turn_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AZombiePlayerController_Turn_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AZombiePlayerController_Turn()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AZombiePlayerController_Turn_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AZombiePlayerController);
	UClass* Z_Construct_UClass_AZombiePlayerController_NoRegister()
	{
		return AZombiePlayerController::StaticClass();
	}
	struct Z_Construct_UClass_AZombiePlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__pCameraComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__pCameraComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__pFPSMesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__pFPSMesh;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MuzzleOffset_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MuzzleOffset;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ProjectileClass_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_ProjectileClass;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AZombiePlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_BTECZombies,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AZombiePlayerController_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AZombiePlayerController_Fire, "Fire" }, // 3695337656
		{ &Z_Construct_UFunction_AZombiePlayerController_LookUp, "LookUp" }, // 1714618087
		{ &Z_Construct_UFunction_AZombiePlayerController_MoveForward, "MoveForward" }, // 2217099530
		{ &Z_Construct_UFunction_AZombiePlayerController_MoveRight, "MoveRight" }, // 2533492678
		{ &Z_Construct_UFunction_AZombiePlayerController_StartJump, "StartJump" }, // 1233084206
		{ &Z_Construct_UFunction_AZombiePlayerController_StopJump, "StopJump" }, // 3702162692
		{ &Z_Construct_UFunction_AZombiePlayerController_Turn, "Turn" }, // 2000889261
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombiePlayerController_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "ZombiePlayerController.h" },
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombiePlayerController_Statics::NewProp__pCameraComponent_MetaData[] = {
		{ "Category", "ZombiePlayerController" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AZombiePlayerController_Statics::NewProp__pCameraComponent = { "_pCameraComponent", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AZombiePlayerController, _pCameraComponent), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AZombiePlayerController_Statics::NewProp__pCameraComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AZombiePlayerController_Statics::NewProp__pCameraComponent_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombiePlayerController_Statics::NewProp__pFPSMesh_MetaData[] = {
		{ "Category", "Mesh" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AZombiePlayerController_Statics::NewProp__pFPSMesh = { "_pFPSMesh", nullptr, (EPropertyFlags)0x00100000000b0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AZombiePlayerController, _pFPSMesh), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AZombiePlayerController_Statics::NewProp__pFPSMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AZombiePlayerController_Statics::NewProp__pFPSMesh_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombiePlayerController_Statics::NewProp_MuzzleOffset_MetaData[] = {
		{ "Category", "Gameplay" },
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AZombiePlayerController_Statics::NewProp_MuzzleOffset = { "MuzzleOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AZombiePlayerController, MuzzleOffset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_AZombiePlayerController_Statics::NewProp_MuzzleOffset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AZombiePlayerController_Statics::NewProp_MuzzleOffset_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombiePlayerController_Statics::NewProp_ProjectileClass_MetaData[] = {
		{ "Category", "Projectile" },
		{ "ModuleRelativePath", "ZombiePlayerController.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AZombiePlayerController_Statics::NewProp_ProjectileClass = { "ProjectileClass", nullptr, (EPropertyFlags)0x0014000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AZombiePlayerController, ProjectileClass), Z_Construct_UClass_AZombieProjectile_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AZombiePlayerController_Statics::NewProp_ProjectileClass_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AZombiePlayerController_Statics::NewProp_ProjectileClass_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AZombiePlayerController_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AZombiePlayerController_Statics::NewProp__pCameraComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AZombiePlayerController_Statics::NewProp__pFPSMesh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AZombiePlayerController_Statics::NewProp_MuzzleOffset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AZombiePlayerController_Statics::NewProp_ProjectileClass,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AZombiePlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AZombiePlayerController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AZombiePlayerController_Statics::ClassParams = {
		&AZombiePlayerController::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AZombiePlayerController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AZombiePlayerController_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AZombiePlayerController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AZombiePlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AZombiePlayerController()
	{
		if (!Z_Registration_Info_UClass_AZombiePlayerController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AZombiePlayerController.OuterSingleton, Z_Construct_UClass_AZombiePlayerController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AZombiePlayerController.OuterSingleton;
	}
	template<> BTECZOMBIES_API UClass* StaticClass<AZombiePlayerController>()
	{
		return AZombiePlayerController::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AZombiePlayerController);
	struct Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AZombiePlayerController, AZombiePlayerController::StaticClass, TEXT("AZombiePlayerController"), &Z_Registration_Info_UClass_AZombiePlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AZombiePlayerController), 287315389U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_942832836(TEXT("/Script/BTECZombies"),
		Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_BTECZombies_Source_BTECZombies_ZombiePlayerController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
