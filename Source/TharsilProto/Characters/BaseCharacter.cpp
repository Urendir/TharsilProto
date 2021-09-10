// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "TharsilProto/Components/HealthComponent.h"
#include "TharsilProto/Components/InventoryComponent.h"
#include "TharsilProto/InventoryItems/InventoryItemBase.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(!HealthComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("HealthComponent failed to be created on baseCharacter class "));
	}
	if(!InventoryComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryComponent failed to be created on baseCharacter class "));
	}
	
}


// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
 
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::CalculateCarryWeight() 
{
	InventoryComponent->CarryWeightBaseCapacity = 1.0f;
}	

void ABaseCharacter::HandleCharacterDeath() 
{
    CharacterDeathDelegate.Broadcast(XPReward);
    bIsCharacterDead = true;
}

void ABaseCharacter::HandleIncomingDamage(float IncomingTotalDamage) 
{
	
}

void ABaseCharacter::UseItem(UInventoryItemBase* Item) 
{
	Item->UseItem(this);
}


