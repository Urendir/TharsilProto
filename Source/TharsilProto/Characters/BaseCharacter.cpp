// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "TharsilProto/Components/HealthComponent.h"
#include "TharsilProto/Components/InventoryComponent.h"
#include "TharsilProto/Components/DefensiveCalculatorComponent.h"
#include "TharsilProto/Components/OffensiveCalculatorComponent.h"
#include "TharsilProto/InventoryItems/InventoryItemBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	DefenseComponent = CreateDefaultSubobject<UDefensiveCalculatorComponent>(TEXT("Defense Component"));
	OffenseComponent = CreateDefaultSubobject<UOffensiveCalculatorComponent>(TEXT("Offense Component"));
	MovementComponent = GetCharacterMovement();

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

	bIsCharacterDead = false;
	bIsCharacterSlowed = false;
	IsAttacking = false;
	HasWeaponDrawn = false;

	SaveCharacterSpeedValues();
	
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


//----------------------------------------------------------------------HEALTH and DEATH----------------------------------------------------------

void ABaseCharacter::HandleCharacterDeath() 
{
    CharacterDeathDelegate.Broadcast(XPReward);
    bIsCharacterDead = true;
}

void ABaseCharacter::ProcessDamageTaken(float IncomingTotalDamage)
{
	UE_LOG(LogTemp, Warning, TEXT("The Taken damage was: %f"), IncomingTotalDamage);

	HealthComponent->DecreaseCurrentHealth(IncomingTotalDamage);
}

void ABaseCharacter::ForwardIncomingDamageToCalculator(ABaseCharacter* ThisCharacter, ABaseCharacter* Damager, FDamageTypeBreakdown Damage)
{
	DefenseComponent->ProcessIncomingDamage(ThisCharacter, Damager, Damage);
	UE_LOG(LogTemp, Warning, TEXT("Dealing Damage: Slash: %f, Pierce: %f, Crush: %f, Armor Penetration: %i "), Damage.SlashDmg, Damage.PierceDmg, Damage.CrushDmg, Damage.ArmorPenetration);
}

//-------------------------------------------------------------------------------------STATUS EFFECTS---------------------------------------------------------

void ABaseCharacter::SaveCharacterSpeedValues()
{
	if (!bIsCharacterSlowed)
	{
		SavedMaxWalkSpeed = MovementComponent->MaxWalkSpeed;
		SavedMaxWalkSpeedCrouched = MovementComponent->MaxWalkSpeedCrouched;
		SavedMaxSwimSpeed = MovementComponent->MaxSwimSpeed;
		SavedMaxFlySpeed = MovementComponent->MaxFlySpeed;
	}
}

void ABaseCharacter::HandleCharacterSlowedEffect(bool bIsSlowed)
{
	
	UE_LOG(LogTemp, Error, TEXT("Character Is Slowed"));
	

	if (bIsSlowed && !bIsCharacterSlowed)
	{
		MovementComponent->MaxWalkSpeed /= SlowDebuffValue;
		MovementComponent->MaxWalkSpeedCrouched /= SlowDebuffValue;
		MovementComponent->MaxSwimSpeed /= SlowDebuffValue;
		MovementComponent->MaxFlySpeed /= SlowDebuffValue;
		MovementComponent->SetJumpAllowed(false);
		bIsCharacterSlowed = true;
	}
	
	if(!bIsSlowed && bIsCharacterSlowed)
	{
		MovementComponent->MaxWalkSpeed = SavedMaxWalkSpeed;
		MovementComponent->MaxWalkSpeedCrouched = SavedMaxWalkSpeedCrouched;
		MovementComponent->MaxSwimSpeed = SavedMaxSwimSpeed;
		MovementComponent->MaxFlySpeed = SavedMaxFlySpeed;
		MovementComponent->SetJumpAllowed(true);
		bIsCharacterSlowed = false;
	}
}

void ABaseCharacter::UseItem(TSubclassOf<UInventoryItemBase> Item) 
{
	ThisInventoryItem = Cast<UInventoryItemBase>(Item);
	ThisInventoryItem->UseItem(this);
}


