// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_ItemBase.h"
#include "TharsilProto/DataAssets/DA_CraftingMaterial.h"
#include "TharsilProto/Characters/BaseCharacter.h"

UDA_ItemBase::UDA_ItemBase() 
{
    
}

class UWorld* UDA_ItemBase::GetWorld() const
{
    return World;
}

float UDA_ItemBase::CalculateItemValue() //NEEDS TO BE FLESHED OUT WITH FULL CALCULATION.
{
   
    return 0;
}

float UDA_ItemBase::CalculateItemWeight() //NEEDS TO BE FLESHED OUT WITH FULL CALCULATION.
{
    return 0;
}

void UDA_ItemBase::UseItem(ABaseCharacter* Character) 
{
    
}
