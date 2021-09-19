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

void UDefensiveCalculatorComponent::CalculateCharacterResistances(FDamageResistanceBreakdown Resistances)
{
	Resistances.SlashDefense = 5.0f;
	Resistances.PierceDefense = 6.0f;
	Resistances.CrushDefense = 7.0f;
	Resistances.BleedResist = 0.053f;

	UE_LOG(LogTemp, Warning, TEXT("The Resistances for %s are Slash: %f, Pierce: %f, Blunt: %f, Bleed: %f"), *GetOwner()->GetName(), Resistances.SlashDefense, Resistances.PierceDefense, Resistances.CrushDefense, Resistances.BleedResist);


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



