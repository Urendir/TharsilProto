// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemBase.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "TharsilProto/DataAssets/Items/DA_ItemBase.h"
#include "TharsilProto/Interactions/InteractablePickupItem.h"
#include "TharsilProto/Components/InventoryComponent.h"


UInventoryItemBase::UInventoryItemBase() 
{
    
}

class UWorld* UInventoryItemBase::GetWorld() const
{
    return World;
}

float UInventoryItemBase::CalculateItemValue() 
{
    return 0;
}

float UInventoryItemBase::CalculateItemWeight() 
{
    return 0;
}

void UInventoryItemBase::UseItem(ABaseCharacter* Character) 
{
    
}
