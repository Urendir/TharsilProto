// Fill out your copyright notice in the Description page of Project Settings.


#include "OffensiveCalculatorComponent.h"


// Sets default values for this component's properties
UOffensiveCalculatorComponent::UOffensiveCalculatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UOffensiveCalculatorComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ABaseCharacter>(GetOwner());
	CalculateDamageRatings();
}

void UOffensiveCalculatorComponent::CalculateDamageRatings()
{
	DamageCollection.BleedDmg = 150.0f;
	DamageCollection.SlashDmg = 30.0f;
	DamageCollection.PierceDmg = 10.0f;
	DamageCollection.CrushDmg = 20.0f;
	DamageCollection.ArmorPenetration = 50;
}

void UOffensiveCalculatorComponent::DamageEnemyCharacter(ABaseCharacter* DamageTarget, FDamageTypeBreakdown Damage)
{
	CalculateDamageRatings();
	if (!Owner)
	{
		return;
	}

	DamageTarget->ForwardIncomingDamageToCalculator(DamageTarget, Owner, DamageCollection);	
}


void UOffensiveCalculatorComponent::DamageOwnEquipment() 
{
	
}



