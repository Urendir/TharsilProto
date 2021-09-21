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
	
}


// Called every frame
void UEnergyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnergyComponent::RecalculateEnergyStats(int32 Endurance, int32 CharacterLevel)
{
}

void UEnergyComponent::RecalculateMaximumStamina()
{
}

void UEnergyComponent::DecreaseCurrentStamina()
{
}


void UEnergyComponent::RecalculateMaximumMana()
{
}

void UEnergyComponent::DecreaseCurrentMana()
{
}

void UEnergyComponent::EnableManaUsage()
{
}

