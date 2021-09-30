// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemBase.h"
#include "TharsilProto/Characters/BaseCharacterPlayable.h"
#include "TharsilProto/Interactions/InteractablePickupItem.h"
#include "TharsilProto/Components/InventoryComponent.h"

//-------------------------------------------------------------Constructor And BeginPlay

UInventoryItemBase::UInventoryItemBase() 
{
    bValuesAreInitialized = false;
}

void UInventoryItemBase::BeginPlay() 
{
    if (!BaseItem)  //This avoids any fuckery in UE, making sure that the BaseItem is there before all of the dependencies are called.
    {
        UE_LOG(LogTemp, Error, TEXT("The Data Asset isn't being called properly by InventoryItemBase."));
    }
    else
    {
        InitializeItemValues();
    }
}

//-------------------------------------------------Initializing of Values at beginning of play----------------------------

void UInventoryItemBase::InitializeItemValues() 
{
    CalculateQualityModifiers(); 
    ItemDescription = BaseItem->ItemDescription;
	Thumbnail = BaseItem->Thumbnail;
    CalculateTotalItemDurability();
    CurrentDurability = ItemDurability;
    CalculateTotalItemWeight();
    CalculateTotalItemValue();

    if (QualityPrefix.Len() == 0)
    {
        ItemDisplayName = BaseItem->ItemDisplayName;
    }
    else 
    {
        ItemDisplayName = QualityPrefix + BaseItem->ItemDisplayName;
    }
    bValuesAreInitialized = true;
}

// Quality Modifiers are used in calculating the final scores for Durability, Weight and Value of items. 
// This should be called in InitializeItemValues only.

void UInventoryItemBase::CalculateQualityModifiers() 
{
    if(QualityRating == EQualityRating::E_Inferior)
    {
        QualityModifierWeight = 1.5f;
        QualityModifierValue = 0.6f;
        QualityModifierDurability = 0.5f;
        QualityPrefix = TEXT("Inferior ");
    }
    else if(QualityRating == EQualityRating::E_Lesser)
    {
        QualityModifierWeight = 1.3f;
        QualityModifierValue = 0.8f;
        QualityModifierDurability = 0.75f;  
        QualityPrefix = TEXT("Lesser ");
    }
    else if(QualityRating == EQualityRating::E_Common)
    {
        QualityModifierWeight = 1.0f;
        QualityModifierValue = 1.0f;
        QualityModifierDurability = 1.0f;   
        QualityPrefix = TEXT("Common ");
    }
    else if(QualityRating == EQualityRating::E_Good)
    {
        QualityModifierWeight = 0.9f;
        QualityModifierValue = 1.2f;
        QualityModifierDurability = 1.5f;       
        QualityPrefix = TEXT("Good ");
    }  
    else if(QualityRating == EQualityRating::E_Fine)
    {
        QualityModifierWeight = 0.8f;
        QualityModifierValue = 1.75f;
        QualityModifierDurability = 2.0f;
        QualityPrefix = TEXT("Fine ");
    }    
    else if(QualityRating == EQualityRating::E_Superior)
    {
        QualityModifierWeight = 0.75f;
        QualityModifierValue = 2.5f;
        QualityModifierDurability = 2.5f;
        QualityPrefix = TEXT("Superior ");
    }
    else if(QualityRating == EQualityRating::E_Exquisite)
    {
        QualityModifierWeight = 0.7f;
        QualityModifierValue = 4.0f;
        QualityModifierDurability = 3.0f; 
        QualityPrefix = TEXT("Exquisite ");
    }
    else if(QualityRating == EQualityRating::E_Unique)
    {
        QualityModifierWeight = 0.7f;
        QualityModifierValue = 6.0f;
        QualityModifierDurability = 4.0f;
        QualityPrefix = TEXT("Unique ");
    }
    else if(QualityRating == EQualityRating::E_Legendary)
    {
        QualityModifierWeight = 0.65f;
        QualityModifierValue = 10.0f;
        QualityModifierDurability = 5.0f;
        QualityPrefix = TEXT("Legendary ");
    }
    else
    {
        QualityModifierWeight = 0;
        QualityModifierValue = 0;
        QualityModifierDurability = 0;
        QualityPrefix.Empty();
    }
}

float UInventoryItemBase::CalculateTotalItemDurability() 
{
    if(BaseItem)
    {
        ItemDurability = BaseItem->CalculateBaseItemDurability() * QualityModifierDurability;
    }
    return ItemDurability;
}

float UInventoryItemBase::CalculateTotalItemWeight() 
{
    if(!BaseItem)
    {
        UE_LOG(LogTemp, Error, TEXT("Error retrieving 'BaseItem' Data Asset when calculating Item Weight"));
    }
    ItemWeight = BaseItem->CalculateBaseItemWeight() * QualityModifierWeight;

    return ItemWeight;
}

float UInventoryItemBase::CalculateTotalItemValue() 
{
    if(BaseItem)
    {
        ItemValue = BaseItem->CalculateBaseItemValue() * QualityModifierValue;
    }
    return ItemValue;
}


//--------------------------------------------------Item Interaction and Usage----------------------------------

void UInventoryItemBase::UseItem(ABaseCharacterPlayable* Character)
{
    UE_LOG(LogTemp, Warning, TEXT("The Item was successfully used"));
}


class UWorld* UInventoryItemBase::GetWorld() const
{
    return World;
}
