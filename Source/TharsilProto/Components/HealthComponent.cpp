// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ABaseCharacter>(GetOwner());

	RememberedLevel = 1;

	// if(Owner) this is already in BP. 
	// {
	// Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	// }
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ApplyHealthRegenOverTime(DeltaTime);
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

void UHealthComponent::ApplyHealthRegenOverTime(float DeltaTime)
{
	if (CurrentHealth < CurrentMaxHealth && !bHasTakenDamageRecently)
	{
		float HealthValue = CurrentHealth + HealthRegenPerSecond * DeltaTime;

		CurrentHealth = HealthValue;
	}

	if (bHasTakenDamageRecently && DamageDelayTicker < DamageDelay)
	{
		DamageDelayTicker = DamageDelayTicker + 1 * DeltaTime;
	}
	if (DamageDelayTicker >= DamageDelay)
	{
		bHasTakenDamageRecently = false;
		DamageDelayTicker = 0.0f;
	}
}


void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) 
{
	if(Damage <=0)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, CurrentMaxHealth);

	if(CurrentHealth== 0)
	{
		Owner->HandleCharacterDeath();
	}

}

void UHealthComponent::DecreaseCurrentHealth(float DamageValue) 
{
	UE_LOG(LogTemp, Warning, TEXT("Decreasing Damage by: %f"), DamageValue);
	
	bHasTakenDamageRecently = true;
	if(CurrentHealth - DamageValue > 0) 				//Improve this!
	{
		CurrentHealth = CurrentHealth - DamageValue;
	}
	else
	{
		CurrentHealth = 0;
		Owner->HandleCharacterDeath();
	}
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

float UHealthComponent::IncreaseCurrentHealthRegen(float HPRegenAddition, float HPRegenModifier)
{
	if (HPRegenModifier > 1.0f)
	{
		HealthRegenPerSecond = (HealthRegenPerSecondBase + HPRegenAddition) * HPRegenModifier;
	}
	else
	{
		HealthRegenPerSecond = HealthRegenPerSecondBase + HPRegenAddition;
	}
	
	return HealthRegenPerSecond;
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



