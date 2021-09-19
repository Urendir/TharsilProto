// Fill out your copyright notice in the Description page of Project Settings.


#include "DefensiveCalculatorComponent.h"


// Sets default values for this component's properties
UDefensiveCalculatorComponent::UDefensiveCalculatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDefensiveCalculatorComponent::BeginPlay()
{
	Super::BeginPlay();


		CalculateCharacterResistances(DefensiveStats);
	
}

void UDefensiveCalculatorComponent::CalculateCharacterResistances(FDamageTypeBreakdown Resistances)
{
	Resistances.SlashDmg = 5.0f;
	Resistances.PierceDmg = 6.0f;
	Resistances.BluntDmg = 7.0f;
	Resistances.BleedChance = 0.053f;

	UE_LOG(LogTemp, Warning, TEXT("The Resistances for %s are Slash: %f, Pierce: %f, Blunt: %f, Bleed: %f"), *GetOwner()->GetName(), Resistances.SlashDmg, Resistances.PierceDmg, Resistances.BluntDmg, Resistances.BleedChance);


}

void UDefensiveCalculatorComponent::CalculateDamageToCharacter(ABaseCharacter* ThisCharacter, ABaseCharacter* Damager, FDamageTypeBreakdown* Damage)
{
	
}

void UDefensiveCalculatorComponent::CalculateDamageToArmor() 
{
	
}

void UDefensiveCalculatorComponent::CalculateBlockedDamage() 
{
	
}



