// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_ItemBase.h"
#include "TharsilProto/DataAssets/DA_CraftingMaterial.h"
#include "Internationalization/Text.h"
#include "Containers/UnrealString.h"


UDA_ItemBase::UDA_ItemBase() 
{
    ItemType = "ItemType";
    MaterialUnitsUsed = 1;
    ItemWeight = 1;
    BaseItemValue = 1;
}

FText UDA_ItemBase::DefineItemName() 
{
    FString Space = " ";
    FString Name = PrimaryCraftingMaterial->MaterialName + Space + ItemType;
    
    ItemDisplayName = FText::AsCultureInvariant(Name);
    return ItemDisplayName;
}


float UDA_ItemBase::CalculateBaseItemValue() //NEEDS TO BE FLESHED OUT WITH FULL CALCULATION.
{
    
    return BaseItemValue;
}

float UDA_ItemBase::CalculateItemWeight() //NEEDS TO BE FLESHED OUT WITH FULL CALCULATION.
{
    return 0;
}


