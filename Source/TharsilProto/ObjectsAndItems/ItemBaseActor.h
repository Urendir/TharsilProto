// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBaseActor.generated.h"



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
class UDA_CraftingMaterial;
class UDA_ItemBase;
class ABaseCharacter;

UCLASS()
class THARSILPROTO_API AItemBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBaseActor();

	virtual class UWorld* GetWorld() const;

	UPROPERTY(Transient)
	UWorld* World;

	/**Selects the quality of the Item, influencing its value*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Descriptors")	
	EQualityRating QualityRating = EQualityRating::E_Default;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	UDA_ItemBase* ItemBaseData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	FString ItemType = "ItemType";

	/**This is the name that will be shown in the inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	FText ItemDisplayName;
	
	/**This is an optional description for the item*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	UTexture2D* Thumbnail;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	UStaticMesh* PickupMesh;	

	/**Material Primarily used in crafting this object. E.g. for a Sword, it would be steel. For a spear, it would be wood. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	UDA_CraftingMaterial* PrimaryCraftingMaterial;

	/**The amount of weight the item will use in the inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemWeight;

	/**The monetary value of the item*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors");
	UInventoryComponent* OwningInventory;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	


	UFUNCTION(BlueprintCallable)
	virtual void UseItem(ABaseCharacter* Character);

};
