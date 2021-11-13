// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DA_EquippableItemBase.h"
#include "TharsilProto/ProgressionSystems/GeneralAttributeSet.h"
#include "DA_CraftedArmorBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Category = "Armor Description")
enum class EArmorLayer : uint8
{
	E_Default		UMETA(DisplayName = "Default"),
	E_Helmet		UMETA(DisplayName = "Helmet"),
	E_HeadChain		UMETA(DisplayName = "Head Chain"),
	E_Coif			UMETA(DisplayName = "Coif"),
	E_Spaulder		UMETA(DisplayName = "Spaulder"),
	E_OuterGarment	UMETA(DisplayName = "Outer Garment"),
	E_BodyPlate		UMETA(DisplayName = "Body Plate"),
	E_BodyChainmail	UMETA(DisplayName = "Body Chainmail"),
	E_BodyGarment	UMETA(DisplayName = "Body Garment"),
	E_Gloves		UMETA(DisplayName = "Gloves"),
	E_ArmPlate		UMETA(DisplayName = "Arm Plate"),
	E_LegPlate		UMETA(DisplayName = "Leg Plate"),
	E_LegChain		UMETA(DisplayName = "Leg Chainmail"),
	E_Hose			UMETA(DisplayName = "Pantaloons"),
	E_Boots			UMETA(DisplayName = "Boots"),
};


UCLASS()
class THARSILPROTO_API UDA_CraftedArmorBase : public UDA_EquippableItemBase
{
	GENERATED_BODY()
	
public:

	/*This is a percentile indicator of the damage mitigation to Slashing Attacks*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense Attributes")
	float DefenseSlash = 0.0f;
	/*This is a percentile indicator of the damage mitigation to Piercing Attacks*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense Attributes")
	float DefensePierce = 0.0f;
	/*This is a percentile indicator of the damage mitigation to Crushing Attacks*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense Attributes")
	float DefenseCrush = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense Attributes")
	float HeatProtection = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense Attributes")
	float ColdProtection = 0.0f;
};
