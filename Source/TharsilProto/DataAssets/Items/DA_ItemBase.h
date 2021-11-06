// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_ItemBase.generated.h"

//------------------------------------ This Enum Allows to set the origin of the item--------------------------------
UENUM(BlueprintType)
enum class ItemOrigin : uint8
{
	E_Default 		UMETA(DisplayName = "Default"),
	E_Harvested			UMETA(DisplayName = "Harvested"),
	E_Mined			UMETA(DisplayName = "Mined"),
	E_Salvaged			UMETA(DisplayName = "Salvaged"),
	E_Butchered			UMETA(DisplayName = "Butchered"),
	E_Crafted	UMETA(DisplayName = "Crafted"),
	E_Reward	UMETA(DisplayName = "Reward")
};

//------------------------------------ This Enum Allows to set the rarity of the item--------------------------------
UENUM(BlueprintType)
enum class ItemRarity : uint8
{
	E_Default 			UMETA(DisplayName = "Default"),
	E_Plentyful			UMETA(DisplayName = "Plentyful"),
	E_Common			UMETA(DisplayName = "Common"),
	E_Scarce			UMETA(DisplayName = "Scarce"),
	E_Rare				UMETA(DisplayName = "Rare"),
	E_VeryRare			UMETA(DisplayName = "Very Rare"),
	E_ExtrRare			UMETA(DisplayName = "Extremely Rare")
};

class UDA_CraftingMaterial;


UCLASS()
class THARSILPROTO_API UDA_ItemBase : public UDataAsset
{
	GENERATED_BODY()
	
public:	
	
	UDA_ItemBase();

	/**This is the name that will be shown in the inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
	FString ItemDisplayName;
	/**This is an optional description for the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors", meta = (MultiLine = true))
	FText ItemDescription;
	/**The amount of weight the item will use in the inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemWeight = 0.0f;
	/**The monetary value of the base item*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemValue = 0.0f;
	/*How many items can fit in a stack*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	int32 StackSizeMax = 0;
	/*How many items are currently in the stack*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	int32 StackSizeCurrent = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")
	UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")
	UStaticMesh* PickupMesh;	
	float CalculateBaseItemValue();
	float CalculateBaseItemWeight();
	float CalculateBaseItemDurability();
};
