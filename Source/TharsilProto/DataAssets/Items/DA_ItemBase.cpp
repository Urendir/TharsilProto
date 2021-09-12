// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_ItemBase.h"
#include "TharsilProto/DataAssets/DA_CraftingMaterial.h"


UDA_ItemBase::UDA_ItemBase() 
{
    
}

float UDA_ItemBase::CalculateBaseItemValue() 
{
    float BaseItemValue = PrimaryCraftingMaterial->GetPricePerUnit() * MaterialUnitsUsed;
    
    return BaseItemValue;
}

float UDA_ItemBase::CalculateBaseItemWeight() 
{
    ItemWeight = PrimaryCraftingMaterial->WeightPerUnit * MaterialUnitsUsed;
    return ItemWeight;
}

float UDA_ItemBase::CalculateBaseItemDurability() 
{
    ItemBaseDurability = PrimaryCraftingMaterial->DurabilityPerUnit * MaterialUnitsUsed * DurabilityModifier;
    return ItemBaseDurability;
}

