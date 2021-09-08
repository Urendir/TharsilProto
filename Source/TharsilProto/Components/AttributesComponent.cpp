// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributesComponent.h"
#include "TharsilProto/Characters/BaseCharacterPlayable.h"
#include "TharsilProto/Characters/BaseCharacter.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Owner = Cast<ABaseCharacterPlayable>(GetOwner());

	AttributeStrength = AttributeStartMinimum; //Minimum Attribute Cap is 5, max is 120.
	AttributeAgility = AttributeStartMinimum;
	AttributeConstitution = AttributeStartMinimum;
	AttributeEndurance = AttributeStartMinimum;
}


// Called when the game starts
void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAttributesComponent::IncreaseAttributePoints() 
{
	UnspentAttributePoints +=AttributePointsPerLevel;
}

void UAttributesComponent::ResetAttributePoints() 
{
	TotalAttributePoints = UnspentAttributePoints + AttributeStrength + AttributeAgility + AttributeConstitution + AttributeEndurance;

	AttributeStrength = AttributeStartMinimum; //Minimum Attribute Cap is 5, max is 120.
	AttributeAgility = AttributeStartMinimum;
	AttributeConstitution = AttributeStartMinimum;
	AttributeEndurance = AttributeStartMinimum;

	UnspentAttributePoints = TotalAttributePoints - AttributeStartMinimum*4; //This is to account for the points that remain in the 4 attributes.
	OnAttributesUpdated.Broadcast();
}

float UAttributesComponent::CalculateCarryCapPerStrength() 
{
	return PerStrengthCarryCapacity * (float)AttributeStrength;
}




