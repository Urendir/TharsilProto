// Fill out your copyright notice in the Description page of Project Settings.


#include "DefensiveCalculatorComponent.h"
#include "Math/UnrealMathUtility.h"


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

	Owner = Cast<ABaseCharacter>(GetOwner());
	CalculateCharacterResistances();
}

void UDefensiveCalculatorComponent::CalculateCharacterResistances()
{
	DefensiveStats.SlashDefense = 5.0f;
	DefensiveStats.PierceDefense = 6.0f;
	DefensiveStats.CrushDefense = 7.0f;

	//Magical Secondary elements.
	DefensiveStats.BleedResist = 0.053f;
	DefensiveStats.ColdResist = 0.01f;
	DefensiveStats.CorrosionResist = 0.01f;
	DefensiveStats.DarknessResist = 0.05f;;
	DefensiveStats.AetherealResist = 0.01f;
	DefensiveStats.FaeResist = 0.05f;
	DefensiveStats.FireResist = 0.05f;
	DefensiveStats.LightningResist = 0.01f;
	DefensiveStats.LightResist = 0.1f;
	DefensiveStats.NecroticResist = 0.03f;
	DefensiveStats.ToxinResist = 0.02f;
	DefensiveStats.WaterResist = 0.1f;

	UE_LOG(LogTemp, Warning, TEXT("The Resistances for %s are Fae: %f, Fire: %f, Darkness: %f, Water: %f"), *GetOwner()->GetName(), DefensiveStats.FaeResist, DefensiveStats.FireResist, DefensiveStats.DarknessResist, DefensiveStats.WaterResist);


}

void UDefensiveCalculatorComponent::ProcessIncomingDamage(ABaseCharacter* ThisCharacter, ABaseCharacter* Damager, FDamageTypeBreakdown Damage)
{
	float DamageToHealth = CalculateIncomingDamage(Damage);

	if (Owner)
	{
		Owner->ProcessDamageTaken(DamageToHealth);
	}
}

int32 UDefensiveCalculatorComponent::CalculateIncomingDamage(FDamageTypeBreakdown Damage)
{
	float FlatPhysicalDamage = Damage.SlashDmg + Damage.PierceDmg + Damage.CrushDmg;

	float ArmorPenetrationRating = (float)Damage.ArmorPenetration * ArmorPenetrationModifier;


	float Slash = Damage.SlashDmg * (1.0f - (DefensiveStats.SlashDefense - ArmorPenetrationRating * 0.5));
	int32 SlashDamage = (int32)Slash;
	SlashDamage = FMath::Clamp(SlashDamage, 0, (int32)Slash);
	float Pierce = Damage.PierceDmg * 1 - (DefensiveStats.PierceDefense - ArmorPenetrationRating);
	int32 PierceDamage = (int32)Pierce;
	PierceDamage = FMath::Clamp(PierceDamage, 0, (int32)Pierce);
	float Crush = Damage.CrushDmg * 1 - (DefensiveStats.CrushDefense - ArmorPenetrationRating);
	int32 CrushDamage = (int32)Crush;
	CrushDamage = FMath::Clamp(CrushDamage, 0, (int32)Crush);



	int32 FinalDamage = SlashDamage + PierceDamage + CrushDamage;

	return FinalDamage;
}

float UDefensiveCalculatorComponent::CalculateDamageToArmor(float IncomingDamage) 
{
	float DamageToArmor = IncomingDamage * 0.25;

	return DamageToArmor;
}

void UDefensiveCalculatorComponent::CalculateBlockedDamage() 
{
	
}



