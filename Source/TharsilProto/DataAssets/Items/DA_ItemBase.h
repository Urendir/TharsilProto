// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_ItemBase.generated.h"

class UDA_CraftingMaterial;
class ABaseCharacter;

//------------------------------------ This Enum Allows for Quality Selection--------------------------------
// UENUM(BlueprintType)  
// enum class EItemQuality : uint8
// {
// 	E_Default 		UMETA(DisplayName ="Default"),
// 	E_Inferior		UMETA(DisplayName ="Inferior"),
// 	E_Basic			UMETA(DisplayName ="Basic"),
// 	E_Common		UMETA(DisplayName ="Common"),
// 	E_Good			UMETA(DisplayName ="Good"),
// 	E_Fine			UMETA(DisplayName ="Fine"),
// 	E_Superior		UMETA(DisplayName ="Superior"),
// 	E_Exquisite		UMETA(DisplayName ="Exquisite"),
// 	E_Unique		UMETA(DisplayName ="Unique"),
// };


UENUM(BlueprintType)
enum class EQualityRating : uint8
{
	E_Default = 0		UMETA(DisplayName = "Default"),
	E_Inferior = 1		UMETA(DisplayName = "Inferior"),
	E_Basic	= 2			UMETA(DisplayName = "Basic"),
	E_Common = 3		UMETA(DisplayName = "Common"),
	E_Good = 4			UMETA(DisplayName = "Good"),
	E_Fine = 5			UMETA(DisplayName = "Fine"),
	E_Superior = 6		UMETA(DisplayName = "Superior"),
	E_Exquisite	= 7		UMETA(DisplayName = "Exquisite"),
	E_Unique = 8		UMETA(DisplayName = "Unique"),
	E_Legendary = 9		UMETA(DisplayName = "Legendary"),
};

class UInventoryComponent;
class UWorld;
class ABaseCharacter;

UCLASS()
class THARSILPROTO_API UDA_ItemBase : public UDataAsset
{
	GENERATED_BODY()
	
public:	
	
	UDA_ItemBase();

	virtual class UWorld* GetWorld() const;

	UPROPERTY(Transient)
	UWorld* World;

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

	// /**Selects the quality of the Item, influencing its value*/
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")	
	// EItemQuality Quality;


	/**Selects the quality of the Item, influencing its value*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")	
	EQualityRating QualityRating;		

	/**The amount of weight the item will use in the inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
	float ItemWeight;

	/**The monetary value of the item*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
	float ItemValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors");
	UInventoryComponent* OwningInventory;

	float CalculateItemValue();
	float CalculateItemWeight();

	UFUNCTION(BlueprintCallable)
	virtual void UseItem(ABaseCharacter* Character);




};
