// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractablePickupItem.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "TharsilProto/DataAssets/Items/DA_ItemBase.h"

// Sets default values
AInteractablePickupItem::AInteractablePickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AInteractablePickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

class UWorld* AInteractablePickupItem::GetWorld() const
{
	return World;
}

float AInteractablePickupItem::CalculateItemValue() 
{
	return 0;
}

float AInteractablePickupItem::CalculateItemWeight() 
{
	return 0;
}

void AInteractablePickupItem::UseItem(ABaseCharacter* Character) 
{
	
}


