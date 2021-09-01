// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_CraftingMaterial.h"

UDA_CraftingMaterial::UDA_CraftingMaterial() 
{
    DurabilityPerUnit = FMath::Clamp(DurabilityPerUnit, 20.0f, 1400.0f);
    GetPricePerUnit(); 
}

float UDA_CraftingMaterial::GetPricePerUnit() 
{
    float NormDurability = (DurabilityPerUnit - MinDurability)/(MaxDurability - MinDurability);
    float NormWeight = 1+(MinWeight- WeightPerUnit)/(MaxWeight - MinWeight);
    float NormRarity = (RarityRating - MinRarity)/(MaxRarity-MinRarity);
    float NormComplexity = (ComplexityToProduce - MinComplexity) / (MaxComplexity-MinComplexity);

    PricePerUnit = NormDurability*DurabilityModifier + NormWeight*WeightModifier + NormRarity*RarityModifier + NormComplexity*ComplexityModifier;
    return PricePerUnit;
}

