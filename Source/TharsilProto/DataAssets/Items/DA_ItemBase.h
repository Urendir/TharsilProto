// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_ItemBase.generated.h"

class UDA_CraftingMaterial;
class ABaseCharacter;


UCLASS()
class THARSILPROTO_API UDA_ItemBase : public UDataAsset
{
	GENERATED_BODY()
	
public:	
	
	UDA_ItemBase();

	/**What is this? a pot? a bow? a cart?*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	FString ItemType = "ItemType";

	/**This is the name that will be shown in the inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	FText ItemDisplayName;
	
	/**This is an optional description for the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Descriptors", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Descriptors")
	UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Descriptors")
	UStaticMesh* PickupMesh;	

	/**Material Primarily used in crafting this object. E.g. for a Sword, it would be steel. For a spear, it would be wood. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Descriptors")
	UDA_CraftingMaterial* PrimaryCraftingMaterial;

	/**One unit = 1000 cubic centimeters, so a cube with 10cm on each side*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Descriptors")	
	float MaterialUnitsUsed;

	// /**Selects the quality of the Item, influencing its value*/
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Descriptors")	
	// EItemQuality Quality;


	/**The amount of weight the item will use in the inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemWeight;

	/**The monetary value of the item*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float BaseItemValue;


	FText DefineItemName();
	float CalculateBaseItemValue();
	float CalculateItemWeight();






};
