// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCalculatorComponent.h"
#include "TharsilProto/CombatEffects/StatusEffectBase.h"
#include "TharsilProto/Components/CombatNumbersStruct.h"

// Sets default values for this component's properties
UCombatCalculatorComponent::UCombatCalculatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatCalculatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatCalculatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

