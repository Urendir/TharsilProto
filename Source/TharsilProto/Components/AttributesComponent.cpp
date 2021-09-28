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

	InitializeAttributePoints();
}


// Called when the game starts
void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAttributesComponent::CalculateTotalAttributePoints()
{
	AttributeAgility = PassiveAdditionAgility + CommittedToAgility + AttributeStartMinimum;
	AttributeArcaneEssence = PassiveAdditionArcaneEssence + CommittedToArcaneEssence + AttributeStartMinimum;
	AttributeConstitution = PassiveAdditionConstitution + CommittedToConstitution + AttributeStartMinimum;
	AttributeEndurance = PassiveAdditionEndurance + CommittedToEndurance + AttributeStartMinimum;
	AttributeSpirit = PassiveAdditionSpirit + CommittedToSpirit + AttributeStartMinimum;
	AttributeStrength = PassiveAdditionStrength + CommittedToStrength + AttributeStartMinimum;
	
	UE_LOG(LogTemp, Warning, TEXT("Recalculating Attributes. Strength: %i, Agility: %i."), AttributeStrength, AttributeAgility);

	OnAttributesUpdated.Broadcast();
}

void UAttributesComponent::IncreaseAttributePoints()
{
	UnspentAttributePoints +=AttributePointsPerLevel;
}

void UAttributesComponent::ResetAttributePoints() 
{
	UnspentAttributePoints = CommittedToAgility + CommittedToArcaneEssence + CommittedToEndurance + CommittedToConstitution + CommittedToSpirit + CommittedToStrength;
	InitializeAttributePoints();
	OnAttributesUpdated.Broadcast();
}


void UAttributesComponent::InitializeAttributePoints()
{
	AttributeStrength = AttributeStartMinimum; //Minimum Attribute Cap is 5, max is 120.
	AttributeAgility = AttributeStartMinimum;
	AttributeConstitution = AttributeStartMinimum;
	AttributeEndurance = AttributeStartMinimum;
	AttributeSpirit = AttributeStartMinimum;
	AttributeArcaneEssence = AttributeStartMinimum;
	CommittedToAgility = 0;
	CommittedToArcaneEssence = 0;
	CommittedToConstitution = 0;
	CommittedToEndurance = 0;
	CommittedToSpirit = 0;
	CommittedToStrength = 0;
}

float UAttributesComponent::CalculateCarryCapPerStrength() 
{
	return PerStrengthCarryCapacity * (float)AttributeStrength;
}




