// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyComponent.h"

// Sets default values for this component's properties
UEnergyComponent::UEnergyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnergyComponent::BeginPlay()
{
	Super::BeginPlay();

	StaminaMaximum = StaminaBase;
	StaminaCurrent = StaminaMaximum;
	RememberedLevel = 1;
}


// Called every frame
void UEnergyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnergyComponent::RecalculateEnergyStats(int32 Endurance, int32 CharacterLevel)
{
	RecalculateMaximumStamina(Endurance, CharacterLevel);
	RecalculateMaximumMana(Endurance, CharacterLevel); // ADD Arcane Essence to Attributes and then add it into calculation here instead of Endurance. 
	if (CharacterLevel != RememberedLevel || CharacterLevel == 1)
	{
		ManaCurrent = ManaMaximum;
		StaminaCurrent = StaminaMaximum;
		RememberedLevel = CharacterLevel;
	}
}

void UEnergyComponent::RecalculateMaximumStamina(int32 Endurance, int32 Level)
{
	UE_LOG(LogTemp, Warning, TEXT("Asked to update Stamina with the following: Endurance: %i; Current Level: %i"), Endurance, Level);
	StaminaMaximum = Endurance * StaminaPerLevel + Level * StaminaPerLevel + StaminaBase;

	UE_LOG(LogTemp, Warning, TEXT("Current Stamina is: %f, Maximum is %f, rememberedLevel: %i"), StaminaCurrent, StaminaMaximum, RememberedLevel);
}

void UEnergyComponent::DecreaseCurrentStamina()
{
}


void UEnergyComponent::RecalculateMaximumMana(int32 ArcaneEssence, int32 Level)
{
	ManaMaximum = ArcaneEssence * ManaPerEssence + Level * ManaPerLevel + ManaBase;

}

void UEnergyComponent::DecreaseCurrentMana()
{
}

void UEnergyComponent::EnableManaUsage()
{
}

