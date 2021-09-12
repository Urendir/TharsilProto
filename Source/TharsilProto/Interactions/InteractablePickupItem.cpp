// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractablePickupItem.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "TharsilProto/DataAssets/Items/DA_ItemBase.h"
#include "TharsilProto/InventoryItems/InventoryItemBase.h"
#include "TharsilProto/Components/InventoryComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractablePickupItem::AInteractablePickupItem()
{
	StaticMeshItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = StaticMeshItem;

}

// Called when the game starts or when spawned
void AInteractablePickupItem::BeginPlay()
{
	Super::BeginPlay();

	if(BaseItem)
	{
		ItemDisplayName = BaseItem->ItemDisplayName;
		PickupMesh = BaseItem->PickupMesh;
		StaticMeshItem->SetStaticMesh(PickupMesh);
	}

	if(InventoryItem)
	{
		ThisInventoryItem = InventoryItem->GetDefaultObject<UInventoryItemBase>();
		if(!ThisInventoryItem)
		{
			UE_LOG(LogTemp, Error, TEXT("Error retrieving 'Inventory Item' from within interactablePickup, when trying to calculate Item Weight"));
		}
		
		ThisInventoryItem->InitializeItemValues();
		ItemWeight = ThisInventoryItem->ItemWeight;

	}
	
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
		//Destroy();
		StaticMeshItem->SetStaticMesh(nullptr);
	}

}

void AInteractablePickupItem::StartFocus_Implementation() 
{
	
}

void AInteractablePickupItem::EndFocus_Implementation() 
{
	
}





