// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemBase.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "TharsilProto/Interactions/InteractablePickupItem.h"
#include "TharsilProto/Components/InventoryComponent.h"


UInventoryItemBase::UInventoryItemBase() 
{
    InitializeItemValues();
}

void UInventoryItemBase::BeginPlay() 
{
    // not sure this will be needed, but anyway...
    InitializeItemValues();
}

void UInventoryItemBase::InitializeItemValues() 
{
    if(BaseItem)
	{
		ItemDisplayName = BaseItem->ItemDisplayName;
        ItemDescription= BaseItem->ItemDescription;
		Thumbnail = BaseItem->Thumbnail;
        CalculateQualityModifiers(); 
        CalculateTotalItemDurability();
        CalculateTotalItemWeight();
        CalculateTotalItemValue();
	}
}


class UWorld* UInventoryItemBase::GetWorld() const
{
    return World;
}

void UInventoryItemBase::CalculateQualityModifiers() 
{
    
    switch (QualityRating)
    {
    case EQualityRating::E_Inferior:
        QualityModifierWeight = 1.5f;
        QualityModifierValue = 0.6f;
        QualityModifierDurability = 0.5f;
        break;
    case EQualityRating::E_Lesser:
        QualityModifierWeight = 1.3f;
        QualityModifierValue = 0.8f;
        QualityModifierDurability = 0.75f;        
        break;        
    case EQualityRating::E_Common:
        QualityModifierWeight = 1.0f;
        QualityModifierValue = 1.0f;
        QualityModifierDurability = 1.0f;        
        break;
    case EQualityRating::E_Good:
        QualityModifierWeight = 0.9f;
        QualityModifierValue = 1.2f;
        QualityModifierDurability = 1.5f;
        break;
    case EQualityRating::E_Fine:
        QualityModifierWeight = 0.8f;
        QualityModifierValue = 1.75f;
        QualityModifierDurability = 2.0f;
        break;    
    case EQualityRating::E_Superior:
        QualityModifierWeight = 0.75f;
        QualityModifierValue = 2.5f;
        QualityModifierDurability = 2.5f;
        break;                          
    case EQualityRating::E_Exquisite:
        QualityModifierWeight = 0.7f;
        QualityModifierValue = 4.0f;
        QualityModifierDurability = 3.0f;
        break;  
    case EQualityRating::E_Unique:
        QualityModifierWeight = 0.7f;
        QualityModifierValue = 6.0f;
        QualityModifierDurability = 4.0f;
        break;
    case EQualityRating::E_Legendary:
        QualityModifierWeight = 0.65f;
        QualityModifierValue = 10.0f;
        QualityModifierDurability = 5.0f;
        break;            
    default:
        QualityModifierValue = 0;   
        break;
    }  
}

float UInventoryItemBase::CalculateTotalItemValue() 
{
    ItemValue = BaseItem->CalculateBaseItemValue() * QualityModifierValue;
    return ItemValue;
}

float UInventoryItemBase::CalculateTotalItemWeight() 
{
    ItemWeight = BaseItem->CalculateBaseItemWeight() * QualityModifierWeight;
    return ItemWeight;
}

float UInventoryItemBase::CalculateTotalItemDurability() 
{
    ItemDurability = BaseItem->CalculateBaseItemDurability() * QualityModifierDurability;
    return ItemDurability;
}


void UInventoryItemBase::UseItem(ABaseCharacter* Character) 
{
    UE_LOG(LogTemp, Warning, TEXT("The Item was successfully used"));
}

