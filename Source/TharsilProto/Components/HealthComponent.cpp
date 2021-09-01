// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	RememberedLevel = 1;

	// if(Owner)
	// {
	// Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	// }
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) 
{
	if(Damage <=0)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, CurrentMaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("CurrentHealth is: %f"), CurrentHealth);

	if(CurrentHealth== 0)
	{
		HandleCharacterDeath();
		UE_LOG(LogTemp, Warning, TEXT("Character Death"));
	}

}

float UHealthComponent::DecreaseCurrentHealth(float DamageValue) 
{
	if(CurrentHealth - DamageValue > 0) 				//Improve this!
	{
		CurrentHealth = CurrentHealth - DamageValue;
	}
	else
	{
		CurrentHealth = 0;
		HandleCharacterDeath(); 
	}

	return CurrentHealth;
}

float UHealthComponent::IncreaseCurrentHealth(float HealValue) 
{
	if(CurrentHealth + HealValue > CurrentMaxHealth)     //Improve this!
	{
		CurrentHealth = CurrentMaxHealth;
		return CurrentHealth;
	}
	else
	{
		CurrentHealth += HealValue;
		return CurrentHealth;
	}	
}

void UHealthComponent::UpdateMaxHealth(int32 ConstitutionPoints, int32 CurrentLevel)
{
	UE_LOG(LogTemp, Warning, TEXT("Asked to update Health with the following: Constitution: %i; Current Level: %i"), ConstitutionPoints, CurrentLevel);
	CurrentMaxHealth = ConstitutionPoints * PerConstitutionHealth + CurrentLevel * PerLevelHealth + BaseHealth;
	if(CurrentLevel != RememberedLevel || CurrentLevel == 1)
	{
	CurrentHealth = CurrentMaxHealth;
	RememberedLevel = CurrentLevel;
	}
	UE_LOG(LogTemp, Warning, TEXT("CurrentHealth is: %f, Maximum is %f, rememberedLevel: %i"), CurrentHealth, CurrentMaxHealth, RememberedLevel);	
}

void UHealthComponent::HandleCharacterDeath() 
{
	IsCharacterDead = true;	
	UE_LOG(LogTemp, Warning, TEXT("CurrentHealth is: %f. Character is Dead."), CurrentHealth);	
}


