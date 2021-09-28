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


void UEnergyComponent::RecalculateStaminaAttributes(int32 Endurance, int32 Agility, int32 Level, float PassiveStaminaMod, float PassiveStaminaRegen)
{
	RecalculateMaximumStamina(Endurance, Level, PassiveStaminaMod);
	RecalculateStaminaRegen(PassiveStaminaRegen);
	RecalculateStaminaCosts(Agility);

	if (Level != RememberedLevel || Level == 1)
	{
		StaminaCurrent = StaminaMaximum;
		RememberedLevel = Level;
	}
}

void UEnergyComponent::RecalculateMaximumStamina(int32 Endurance, int32 Level, float PassiveStaminaMod)
{
	StaminaMaximum = Endurance * StaminaPerEndurance + Level * StaminaPerLevel + StaminaBase + PassiveStaminaMod;
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

void UEnergyComponent::RecalculateStaminaRegen(float PassiveStaminaRegen)
{
	StaminaRegenerationAmount = (StaminaMaximum*0.09) * (1 + PassiveStaminaRegen);
}

void UEnergyComponent::RecalculateStaminaCosts(int32 Agility)
{
	StaminaToJump = BaseStaminaToJump + (StaminaMaximum * 0.3) - (Agility * 0.5f);			//Magic numbers TBD by playtesting
	StaminaToSprint = BaseStaminaToSprint + (StaminaMaximum * 0.15) - (Agility * 0.5f);		//Magic numbers TBD by playtesting
}

void UEnergyComponent::RecalculateManaAttributes(int32 ArcaneEssence, int32 Level, float PassiveManaMod)
{
	ManaMaximum = ArcaneEssence * ManaPerEssence + Level * ManaPerLevel + ManaBase + PassiveManaMod;

	if (Level != RememberedLevel || Level == 1)
	{
		StaminaCurrent = StaminaMaximum;
		RememberedLevel = Level;
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

float UEnergyComponent::GetStaminaCostToSprint()
{
	return StaminaToSprint;
}

float UEnergyComponent::WhatsCurrentStamina()
{
	return StaminaCurrent;
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

