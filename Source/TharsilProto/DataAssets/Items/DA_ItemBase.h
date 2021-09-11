// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_ItemBase.generated.h"

class UDA_CraftingMaterial;


UCLASS()
class THARSILPROTO_API UDA_ItemBase : public UDataAsset
{
	GENERATED_BODY()
	
public:	
	
	UDA_ItemBase();


	/**This is the name that will be shown in the inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
	FText ItemDisplayName;
	
	/**This is an optional description for the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")
	UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")
	UStaticMesh* PickupMesh;	

	/**Material Primarily used in crafting this object. E.g. for a Sword, it would be steel. For a spear, it would be wood. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")
	UDA_CraftingMaterial* PrimaryCraftingMaterial;

	/**One unit = 1000 cubic centimeters, so a cube with 10cm on each side*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")	
	float MaterialUnitsUsed;

	/**The amount of weight the item will use in the inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemWeight;

	/**The monetary value of the base item*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemValue;

	/**The max durability value of the base item*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemBaseDurability;

	float DurabilityModifier = 0.8f;

	float CalculateBaseItemValue();
	float CalculateBaseItemWeight();
	float CalculateBaseItemDurability();





};
