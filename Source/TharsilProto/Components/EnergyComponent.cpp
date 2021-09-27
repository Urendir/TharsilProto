// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyComponent.h"
#include "Math/UnrealMathUtility.h"

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

	OwningCharacter = Cast<ABaseCharacter>(GetOwner());
}


// Called every frame
void UEnergyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (OwningCharacter->bIsSprinting)
	{
		float StaminaDrain = StaminaToSprint * DeltaTime;
		DecreaseCurrentStamina(StaminaDrain);
	}
	else 
	{
		RestoreEnergyOverTime(DeltaTime);
	}
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
	StaminaMaximum = Endurance * StaminaPerLevel + Level * StaminaPerLevel + StaminaBase;
}

bool UEnergyComponent::DecreaseCurrentStamina(float DecrementAmount)
{
	if (StaminaCurrent > DecrementAmount)
	{
		StaminaCurrent -= DecrementAmount;
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// Helper Functions to provide Stamina costs and information to the Owner Component. 
/// </summary>
/// <returns></returns>
float UEnergyComponent::GetStaminaCostJump()
{
	return StaminaToJump;
}

float UEnergyComponent::SetStaminaCostJump(float NewCost)
{
	StaminaToJump += NewCost;

	return StaminaToJump;
}

float UEnergyComponent::GetStaminaCostToSprint()
{
	return StaminaToSprint;
}

float UEnergyComponent::SetStaminaCostToSprint(float NewCost)
{
	StaminaToSprint += NewCost;
	return StaminaToSprint;
}

float UEnergyComponent::WhatsCurrentStamina()
{
	return StaminaCurrent;
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

void UEnergyComponent::RestoreEnergyOverTime(float DeltaTime)
{
	if (StaminaCurrent < StaminaMaximum)
	{
		float NewStamina = StaminaCurrent + StaminaRegenerationAmount * DeltaTime;
		//StaminaCurrent = NewStamina;
		if (NewStamina > StaminaMaximum)
		{
			StaminaCurrent = StaminaMaximum;
		}
		else
		{
			StaminaCurrent = NewStamina;
		}
	}
	
	if (ManaCurrent < ManaMaximum)
	{
		ManaCurrent = FMath::Min(ManaMaximum, ManaCurrent + ManaRegenerationAmount * DeltaTime);
	}
}

