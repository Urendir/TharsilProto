// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_ItemBase.h"
#include "TharsilProto/DataAssets/DA_CraftingMaterial.h"


UDA_ItemBase::UDA_ItemBase() 
{
    
}

float UDA_ItemBase::CalculateBaseItemValue() //NEEDS TO BE FLESHED OUT WITH FULL CALCULATION.
{
    float BaseItemValue = PrimaryCraftingMaterial->GetPricePerUnit() * MaterialUnitsUsed;
    UE_LOG(LogTemp, Warning, TEXT("The BaseItem Value is: %f"), BaseItemValue);
    
    return BaseItemValue;
}

float UDA_ItemBase::CalculateBaseItemWeight() //NEEDS TO BE FLESHED OUT WITH FULL CALCULATION.
{
    return 0;
}

float UDA_ItemBase::CalculateBaseItemDurability() 
{
    ItemBaseDurability = PrimaryCraftingMaterial->DurabilityPerUnit * MaterialUnitsUsed * DurabilityModifier;
    return ItemBaseDurability;
}

