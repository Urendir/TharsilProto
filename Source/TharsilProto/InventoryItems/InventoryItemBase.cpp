// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemBase.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "TharsilProto/Interactions/InteractablePickupItem.h"
#include "TharsilProto/Components/InventoryComponent.h"


UInventoryItemBase::UInventoryItemBase() 
{
    if(BaseItem)
    {
        InitializeItemValues();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("The Data Asset isn't being called properly."));
    }
}

void UInventoryItemBase::BeginPlay() 
{
    //InitializeItemValues();
}

void UInventoryItemBase::InitializeItemValues() 
{
    UE_LOG(LogTemp, Error, TEXT("InitializeItemValues was called"));
    CalculateQualityModifiers(); 

	ItemDisplayName = BaseItem->ItemDisplayName;
    ItemDescription = BaseItem->ItemDescription;
	Thumbnail = BaseItem->Thumbnail;
    CalculateTotalItemDurability();
    CalculateTotalItemWeight();
    CalculateTotalItemValue();
    UE_LOG(LogTemp, Error, TEXT("InitializeItemValues has gone through all the functions."));


}


class UWorld* UInventoryItemBase::GetWorld() const
{
    return World;
}

void UInventoryItemBase::CalculateQualityModifiers() 
{

    if(QualityRating = EQualityRating::E_Inferior)
    {
        QualityModifierWeight = 1.5f;
        QualityModifierValue = 0.6f;
        QualityModifierDurability = 0.5f;
    }
    else if(QualityRating = EQualityRating::E_Lesser)
    {
        QualityModifierWeight = 1.3f;
        QualityModifierValue = 0.8f;
        QualityModifierDurability = 0.75f;  
    }
    else if(QualityRating = EQualityRating::E_Common)
    {
        QualityModifierWeight = 1.0f;
        QualityModifierValue = 1.0f;
        QualityModifierDurability = 1.0f;        
    }
    else if(QualityRating = EQualityRating::E_Good)
    {
        QualityModifierWeight = 0.9f;
        QualityModifierValue = 1.2f;
        QualityModifierDurability = 1.5f;       
    }  
    else if(QualityRating = EQualityRating::E_Fine)
    {
        QualityModifierWeight = 0.8f;
        QualityModifierValue = 1.75f;
        QualityModifierDurability = 2.0f;    
    }    
    else if(QualityRating = EQualityRating::E_Exquisite)
    {
        QualityModifierWeight = 0.75f;
        QualityModifierValue = 2.5f;
        QualityModifierDurability = 2.5f;       
    }
    else if(QualityRating == EQualityRating::E_Exquisite)
    {
        QualityModifierWeight = 0.7f;
        QualityModifierValue = 4.0f;
        QualityModifierDurability = 3.0f;      
    }
    else if(QualityRating == EQualityRating::E_Unique)
    {
        QualityModifierWeight = 0.7f;
        QualityModifierValue = 6.0f;
        QualityModifierDurability = 4.0f;     
    }
    else if(QualityRating == EQualityRating::E_Legendary)
    {
        QualityModifierWeight = 0.65f;
        QualityModifierValue = 10.0f;
        QualityModifierDurability = 5.0f;      
    }
    else
    {
        QualityModifierWeight = 0;
        QualityModifierValue = 0;
        QualityModifierDurability = 0;
    }
    UE_LOG(LogTemp, Error, TEXT("The Modifier function has run. Modifier for Weight, Value And Durability are: %f, %f, %f."),QualityModifierWeight, QualityModifierValue, QualityModifierDurability );
}

float UInventoryItemBase::CalculateTotalItemValue() 
{
    if(BaseItem)
    {
        ItemValue = BaseItem->CalculateBaseItemValue() * QualityModifierValue;
    }
    return ItemValue;
}

float UInventoryItemBase::CalculateTotalItemWeight() 
{
    if(!BaseItem)
    {
        UE_LOG(LogTemp, Error, TEXT("Error retrieving 'BaseItem' Data Asset when calculating Item Weight"));
    }
    UE_LOG(LogTemp, Error, TEXT("QualityModifier for Weight is: %f"), QualityModifierWeight);
    ItemWeight = BaseItem->CalculateBaseItemWeight() * QualityModifierWeight;

    return ItemWeight;
}

float UInventoryItemBase::CalculateTotalItemDurability() 
{
    if(BaseItem)
    {
        ItemDurability = BaseItem->CalculateBaseItemDurability() * QualityModifierDurability;
    }
    return ItemDurability;
}


void UInventoryItemBase::UseItem(ABaseCharacter* Character) 
{
    UE_LOG(LogTemp, Warning, TEXT("The Item was successfully used"));
}

