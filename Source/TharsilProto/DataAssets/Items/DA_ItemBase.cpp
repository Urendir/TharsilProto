// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_ItemBase.h"
#include "TharsilProto/DataAssets/DA_CraftingMaterial.h"


UDA_ItemBase::UDA_ItemBase() 
{
    
}

float UDA_ItemBase::CalculateItemValue() 
{
    int32 QualityRatingValue = (int32)QualityRating;
    return QualityRatingValue;
}

float UDA_ItemBase::CalculateItemWeight() 
{
    return 0;
}
