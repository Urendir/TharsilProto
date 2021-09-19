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
	UE_LOG(LogTemp, Warning, TEXT("The Resistances for %s are Slash: %f, Pierce: %f, Blunt: %f, Bleed: %f"), *GetOwner()->GetName(), DefensiveStats.SlashDefense, DefensiveStats.PierceDefense, DefensiveStats.CrushDefense, DefensiveStats.BleedResist);
	UE_LOG(LogTemp, Warning, TEXT("The Resistances for %s are Fae: %f, Fire: %f, Darkness: %f, Water: %f"), *GetOwner()->GetName(), DefensiveStats.FaeResist, DefensiveStats.FireResist,  DefensiveStats.DarknessResist, DefensiveStats.WaterResist);


}

void UDefensiveCalculatorComponent::CalculateCharacterResistances(FDamageResistanceBreakdown Resistances)
{
	Resistances.SlashDefense = 5.0f;
	Resistances.PierceDefense = 6.0f;
	Resistances.CrushDefense = 7.0f;
	Resistances.BleedResist = 0.053f;
	Resistances.ColdResist = 0.01f;
	Resistances.CorrosionResist = 0.01f;
	Resistances.DarknessResist = 0.05f;;
	Resistances.AetherealResist = 0.01f;
	Resistances.FaeResist = 0.05f;
	Resistances.FireResist = 0.05f;
	Resistances.LightningResist = 0.01f;
	Resistances.LightResist = 0.1f;
	Resistances.NecroticResist = 0.03f;
	Resistances.ToxinResist = 0.02f;
	Resistances.WaterResist = 0.1f;

	DefensiveStats = Resistances;
	UE_LOG(LogTemp, Warning, TEXT("The Resistances for %s are Fae: %f, Fire: %f, Darkness: %f, Water: %f"), *GetOwner()->GetName(), DefensiveStats.FaeResist, DefensiveStats.FireResist, DefensiveStats.DarknessResist, DefensiveStats.WaterResist);

	DefensiveStats.FaeResist = 15.0f;
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



