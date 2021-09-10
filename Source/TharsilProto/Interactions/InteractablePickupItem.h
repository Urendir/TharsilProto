// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractablePickupItem.generated.h"



class ABaseCharacter;
class UInventoryComponent;
class UWorld;
class ABaseCharacter;


UCLASS()
class THARSILPROTO_API AInteractablePickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractablePickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

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

	/**One unit = 1000 cubic centimeters, so a cube with 10cm on each side*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")	
	float MaterialUnitsUsed;

	

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
