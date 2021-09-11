// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TharsilProto/DataAssets/Items/DA_ItemBase.h"
#include "TharsilProto/Interactions/InteractionInterface.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItemBase.generated.h"



//------------------------------------ This Enum Allows for Quality Selection--------------------------------

UENUM(BlueprintType)
enum class EQualityRating : uint8
{
	E_Default = 0		UMETA(DisplayName = "Default"),
	E_Inferior = 1		UMETA(DisplayName = "Inferior"),
	E_Lesser = 2		UMETA(DisplayName = "Lesser"),
	E_Common = 3		UMETA(DisplayName = "Common"),
	E_Good = 4			UMETA(DisplayName = "Good"),
	E_Fine = 5			UMETA(DisplayName = "Fine"),
	E_Superior = 6		UMETA(DisplayName = "Superior"),
	E_Exquisite	= 7		UMETA(DisplayName = "Exquisite"),
	E_Unique = 8		UMETA(DisplayName = "Unique"),
	E_Legendary = 9		UMETA(DisplayName = "Legendary"),
};

class ABaseCharacter;
class UInventoryComponent;
class UWorld;
class ABaseCharacter;
class AInteractablePickupItem;
class UDA_ItemBase;


UCLASS(Blueprintable)
class THARSILPROTO_API UInventoryItemBase : public UObject
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();	

public:
	UInventoryItemBase();
	
	virtual class UWorld* GetWorld() const;

	UPROPERTY(Transient)
	UWorld* World;

	/**This is the name that will be shown in the inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	FText ItemDisplayName;
	
	/**This is an optional description for the item*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Referenced Items")
	UDA_ItemBase* BaseItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")  //This will be used once we drop items back into the world. 
	TSubclassOf<AInteractablePickupItem> PickupItem;

	AInteractablePickupItem* PickupItemReference;	

	/**Selects the quality of the Item, influencing its value*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")	
	EQualityRating QualityRating;		

	/**The amount of weight the item will use in the inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemWeight;

	/**The maximum durability score of the item*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemDurability;	

	/**The Inventory This item will belong to*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	UInventoryComponent* OwningInventory;

	/**The monetary value of the item*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemValue;

	float QualityModifierWeight;
	float QualityModifierValue;
	float QualityModifierDurability;

	void InitializeItemValues();
	void CalculateQualityModifiers();
	float CalculateTotalItemValue();
	float CalculateTotalItemWeight();
	float CalculateTotalItemDurability();

	UFUNCTION(BlueprintCallable)
	virtual void UseItem(ABaseCharacter* Character);

	
};