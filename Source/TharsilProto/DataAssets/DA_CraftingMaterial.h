// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Math/UnrealMathUtility.h"
#include "DA_CraftingMaterial.generated.h"


//------------------------------------ This Enum Allows for Material Type Selection--------------------------------
UENUM(BlueprintType)  
enum class EMaterialType : uint8
{
	E_Default 		UMETA(DisplayName ="Default"),
	E_Metal			UMETA(DisplayName ="Metal"),
	E_Wood			UMETA(DisplayName ="Wood"),
	E_Stone			UMETA(DisplayName ="Stone"),
	E_Bone			UMETA(DisplayName ="Bone"),
	E_PlantFiber	UMETA(DisplayName ="Plant Fiber"),
	E_AnimalFiber	UMETA(DisplayName ="Animal Fiber")
};

//------------------------------------ Data Asset Below--------------------------------
UCLASS(BlueprintType)
class THARSILPROTO_API UDA_CraftingMaterial : public UDataAsset
{
	GENERATED_BODY()

public:	
	UDA_CraftingMaterial();
//------------------------------------------------Basic Attributes of Material--------------------------------------
	float MinDurability = 20.f;
	float MaxDurability = 1400.f;
	float MinWeight = 0.1f;
	float MaxWeight = 5.f;
	float MinRarity = 1.f;
	float MaxRarity = 250.f;
	float MinComplexity = 1.f;
	float MaxComplexity = 250.f;

	float DurabilityModifier = 6.f;
	float WeightModifier = 3.f;
	float RarityModifier = 32.f;
	float ComplexityModifier = 18.f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString MaterialName = "Default Material";

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	EMaterialType MaterialType = EMaterialType::E_Default;

	/** Min:20, Max: 1400. This Determines how much Durability the final item will have, based on how much of this material was used.  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DurabilityPerUnit = 1.f; //TODO - Clamp This!

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WeightPerUnit = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RarityRating = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ComplexityToProduce = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float PricePerUnit;

	UFUNCTION(BlueprintPure)
	float GetPricePerUnit();



};
