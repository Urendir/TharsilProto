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

	HelperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Helper Mesh"));
	HelperMesh->SetupAttachment(RootComponent);

	ItemDisplayName = TEXT("DefaultName");		// <--------If you see this value, something messed up!
	ItemWeight = 666.0f;						// <--------If you see this value, something messed up!

}

// Called when the game starts or when spawned
void AInteractablePickupItem::BeginPlay()
{
	Super::BeginPlay();

	if (!BaseItem)  //This avoids any fuckery in UE, making sure that the BaseItem is there before all of the dependencies are called.
	{
		UE_LOG(LogTemp, Error, TEXT("The Data Asset isn't being called properly by InteractablePickupItem."));
	}
	else
	{
		PickupMesh = BaseItem->PickupMesh;
		StaticMeshItem->SetStaticMesh(PickupMesh);	
		HelperMesh->SetStaticMesh(nullptr);
		ItemDisplayName = BaseItem->ItemDisplayName;
	}

	if (!InventoryItem)
	{
		UE_LOG(LogTemp, Error, TEXT("The InventoryItem isn't being called properly by InteractablePickupItem."));
	}

	if(InventoryItem)
	{
		ThisInventoryItem = InventoryItem->GetDefaultObject<UInventoryItemBase>();
		if(!ThisInventoryItem)
		{
			UE_LOG(LogTemp, Error, TEXT("Error retrieving 'Inventory Item' from within interactablePickup, when trying to calculate Item Weight"));
		}
		
		if (ThisInventoryItem->bValuesAreInitialized == false)
		{
			ThisInventoryItem->InitializeItemValues();
		}
		ItemWeight = ThisInventoryItem->ItemWeight;
		ItemDisplayName = ThisInventoryItem->ItemDisplayName;
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
		StaticMeshItem->SetStaticMesh(nullptr);  //rather than fully destroying the item now, we just make it invisible. 
	}

}

void AInteractablePickupItem::StartFocus_Implementation() 
{
	
}

void AInteractablePickupItem::EndFocus_Implementation() 
{
	
}





