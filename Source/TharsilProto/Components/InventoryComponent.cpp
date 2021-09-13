// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "TharsilProto/InventoryItems/InventoryItemBase.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "Containers/Array.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ABaseCharacter>(GetOwner());
	InventorySlotsTotal = 20;
	InventorySlotsUsed = 0;
	CarryWeightCurrent = 0;
	CarryWeightTotalCapacity = CarryWeightBaseCapacity;
}

bool UInventoryComponent::AddItemToInventory(TSubclassOf<UInventoryItemBase> Item) 
{
	if(!Item)
	{
		return false;
	}

	//ThisInventoryItem = Cast<UInventoryItemBase>(Item); //this stupid cast doesn't wanna work!
	ThisInventoryItem = Item->GetDefaultObject<UInventoryItemBase>();

	if(!ThisInventoryItem)
	{
		UE_LOG(LogTemp, Error, TEXT("Error retrieving 'ThisInventoryItem' to be added to Inventory"));
		return false;
	}
	
	if(InventorySlotsUsed < InventorySlotsTotal)
	{
		CarryWeightCurrent += ThisInventoryItem->ItemWeight;
		UE_LOG(LogTemp, Error, TEXT("Current CarryWeight: %f."), CarryWeightCurrent);

		if (CarryWeightCurrent >= CarryWeightTotalCapacity)
		{
			if (Owner)
			{
				Owner->HandleCharacterSlowedEffect(true);
			}

			UE_LOG(LogTemp, Error, TEXT("Character Is Overencumbered"));
		}

		UE_LOG(LogTemp, Error, TEXT("'ThisInventoryItem' item weight to be added to inventory is: %f."), ThisInventoryItem->ItemWeight);

		ThisInventoryItem->OwningInventory = this;
		ThisInventoryItem->World = GetWorld();
		InventoryItems.Add(ThisInventoryItem);
		InventorySlotsUsed++;
		OnInventoryUpdated.Broadcast(); 		//This will update UI via delegate:

		return true;
	}
	else
	{
		// Display insufficient Space message
		return false;
	}
}

bool UInventoryComponent::RemoveFromInventory(TSubclassOf<UInventoryItemBase> Item) 
{
	if(Item)
	{
		ThisInventoryItem = Cast<UInventoryItemBase>(Item);

		ThisInventoryItem->OwningInventory = nullptr;
		ThisInventoryItem->World = nullptr;
		InventoryItems.RemoveSingle(ThisInventoryItem);

		OnInventoryUpdated.Broadcast(); 		//This will update UI via delegate:
		InventorySlotsUsed--;
		CarryWeightCurrent -= ThisInventoryItem->ItemWeight;

		if (CarryWeightCurrent < CarryWeightTotalCapacity)
		{
			Owner->HandleCharacterSlowedEffect(false);
		}

		return true;
	}
	return false;
}

void UInventoryComponent::UpdateCarryCapacity(float NewValue) 
{
	CarryWeightTotalCapacity = NewValue;
	if (CarryWeightTotalCapacity > CarryWeightCurrent)
	{
		Owner->HandleCharacterSlowedEffect(false);
	}
	else
	{
		Owner->HandleCharacterSlowedEffect(true);
	}
	OnInventoryUpdated.Broadcast();
}




