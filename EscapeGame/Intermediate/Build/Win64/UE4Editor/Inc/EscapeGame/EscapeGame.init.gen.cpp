// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEscapeGame_init() {}
	ESCAPEGAME_API UFunction* Z_Construct_UDelegateFunction_EscapeGame_OnFireballThrow__DelegateSignature();
	ESCAPEGAME_API UFunction* Z_Construct_UDelegateFunction_EscapeGame_OnItemAdded__DelegateSignature();
	ESCAPEGAME_API UFunction* Z_Construct_UDelegateFunction_EscapeGame_OnItemUsed__DelegateSignature();
	ESCAPEGAME_API UFunction* Z_Construct_UDelegateFunction_EscapeGame_OnTalkeInvoke__DelegateSignature();
	ESCAPEGAME_API UFunction* Z_Construct_UDelegateFunction_EscapeGame_OnClickNext__DelegateSignature();
	ESCAPEGAME_API UFunction* Z_Construct_UDelegateFunction_EscapeGame_OnClickPrev__DelegateSignature();
	ESCAPEGAME_API UFunction* Z_Construct_UDelegateFunction_EscapeGame_OnClickSkip__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_EscapeGame()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_EscapeGame_OnFireballThrow__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_EscapeGame_OnItemAdded__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_EscapeGame_OnItemUsed__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_EscapeGame_OnTalkeInvoke__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_EscapeGame_OnClickNext__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_EscapeGame_OnClickPrev__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_EscapeGame_OnClickSkip__DelegateSignature,
			};
			static const UE4CodeGen_Private::FPackageParams PackageParams = {
				"/Script/EscapeGame",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xBC94C40B,
				0xD75449DF,
				METADATA_PARAMS(nullptr, 0)
			};
			UE4CodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);
		}
		return ReturnPackage;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
