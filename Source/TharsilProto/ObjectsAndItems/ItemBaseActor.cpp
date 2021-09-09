// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBaseActor.h"

#include "TharsilProto/DataAssets/Items/DA_ItemBase.h"
#include "TharsilProto/DataAssets/DA_CraftingMaterial.h"
#include "TharsilProto/Characters/BaseCharacter.h"

// Sets default values
AItemBaseActor::AItemBaseActor()
{


}

class UWorld* AItemBaseActor::GetWorld() const
{
	return GetWorld();
}

// Called when the game starts or when spawned
void AItemBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemBaseActor::UseItem(ABaseCharacter* Character) 
{
	
}

