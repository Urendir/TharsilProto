// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "TharsilProto/DataAssets/Items/DA_ItemBase.h"
#include "TharsilProto/Characters/BaseCharacter.h"

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

	Owner->GetOwner();
	InventorySlotsTotal = 20;
	InventorySlotsUsed = 0;
	CarryWeightCurrent = 0;
	CarryWeightTotalCapacity = CarryWeightBaseCapacity;
}

bool UInventoryComponent::AddItemToInventory(UDA_ItemBase* Item) 
{
	if(!Item)
	{
		return false;
	}
	if(Item->ItemWeight + CarryWeightCurrent < CarryWeightTotalCapacity && InventorySlotsUsed < InventorySlotsTotal)
	{
		Item->OwningInventory = this;
		Item->World = GetWorld();
		InventoryItems.Add(Item);
		//Update UI via delegate:
		OnInventoryUpdated.Broadcast();
		InventorySlotsUsed++;
		CarryWeightCurrent += Item->ItemWeight;

		return true;
	}
	else if(Item->ItemWeight + CarryWeightCurrent >= CarryWeightTotalCapacity && InventorySlotsUsed < InventorySlotsTotal)
	{
		// Do something like Over-Encumber Character
		return true;
	}
	else
	{
		// Display insufficient Space message
		return false;
	}
}

bool UInventoryComponent::RemoveFromInventory(UDA_ItemBase* Item) 
{
	if(Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		InventoryItems.RemoveSingle(Item);
		//Update UI via delegate:
		OnInventoryUpdated.Broadcast();
		InventorySlotsUsed--;
		CarryWeightCurrent -= Item->ItemWeight;

		return true;
	}
	return false;
}

void UInventoryComponent::UpdateCarryCapacity(float NewValue) 
{
	CarryWeightTotalCapacity = NewValue;
	OnInventoryUpdated.Broadcast();
}




