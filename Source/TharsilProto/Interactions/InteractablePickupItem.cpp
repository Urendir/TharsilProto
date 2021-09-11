// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractablePickupItem.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "TharsilProto/DataAssets/Items/DA_ItemBase.h"
#include "TharsilProto/InventoryItems/InventoryItemBase.h"
#include "TharsilProto/Components/InventoryComponent.h"

// Sets default values
AInteractablePickupItem::AInteractablePickupItem()
{
	if(BaseItem)
	{
		ItemDisplayName = BaseItem->ItemDisplayName;
		PickupMesh = BaseItem->PickupMesh;
	}

	

	if(InventoryItem)
	{
		ThisInventoryItem = Cast<UInventoryItemBase>(InventoryItem);
		ItemWeight = ThisInventoryItem->CalculateTotalItemWeight();
	}

}

// Called when the game starts or when spawned
void AInteractablePickupItem::BeginPlay()
{
	Super::BeginPlay();

}

// class UWorld* AInteractablePickupItem::GetWorld() const
// {
// 	return World;
// }

void AInteractablePickupItem::OnInteract_Implementation(AActor* Caller) 
{
	ABaseCharacter* InteractingCharacter = Cast<ABaseCharacter>(Caller);
	
	if(InteractingCharacter)
	{
		InteractingCharacter->InventoryComponent->AddItemToInventory(InventoryItem);
		Destroy();
	}

}

void AInteractablePickupItem::StartFocus_Implementation() 
{
	
}

void AInteractablePickupItem::EndFocus_Implementation() 
{
	
}





