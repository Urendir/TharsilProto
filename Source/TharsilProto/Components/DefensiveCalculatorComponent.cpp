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

	// ...
	
}

void UDefensiveCalculatorComponent::CalculateDamageToCharacter(float SlashDmg, float PierceDmg, float CrushDmg, float BleedChance, float KnockbackChance, ABaseCharacter* Damager) 
{
	
}

void UDefensiveCalculatorComponent::CalculateDamageToArmor() 
{
	
}

void UDefensiveCalculatorComponent::CalculateBlockedDamage() 
{
	
}



