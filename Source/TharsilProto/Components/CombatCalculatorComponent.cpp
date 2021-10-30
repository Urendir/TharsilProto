// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCalculatorComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TharsilProto/Characters/BaseCharacter.h"


// Sets default values for this component's properties
UCombatCalculatorComponent::UCombatCalculatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OwningCharacter = Cast<ABaseCharacter>(GetOwner());

}


// Called when the game starts
void UCombatCalculatorComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UCombatCalculatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



bool UCombatCalculatorComponent::OutCheckForCritical(float Passive, float ActiveAbility, float Agility)
{
	float CritChanceBeforeAbility = FMath::Min(((Agility * CombatAttributes->CritChancePerAgi) + Passive + CombatAttributes->CritChanceBase), CombatAttributes->AbsoluteMaxCriticalChanceBeforeAbility);
	float CritChance = CritChanceBeforeAbility + ActiveAbility;
	if (FMath::Rand() < CritChance)
	{
		bIsAttackCritical = true;
	}
	else bIsAttackCritical = false;

	return bIsAttackCritical;
}


float UCombatCalculatorComponent::OutObtainLatestCritDamage()
{
	//TBD!
	return 0.0f;
}





/// <summary>
/// Calculate all incoming damage and status effects by comparing the types in the attacking AttributesSet to the defender's AttributesSet
/// </summary>
/// <param name="DamagingCombatAttributes"> This is the attacking character's combat attributes - so their raw damage and change to deal status effects.</param>
/// <param name="DamageCauser"> The Attacking Character</param>
/// <param name="bIsCriticalHit"> True if the hit is dealing critical damage.</param>

void UCombatCalculatorComponent::InProcessDamage(UCombatAttributesSet* DamagingCombatAttributes, ABaseCharacter* DamageCauser, bool bIsCriticalHit)
{
	float SlashDmg = DamagingCombatAttributes->PhysicalDamage.DamageSlash * (1 - CombatAttributes->PhysicalDamage.DefenseSlash);
	float PierceDef = CombatAttributes->PhysicalDamage.DefensePierce - DamagingCombatAttributes->GetArmorPenetrationOnPierce();
	float PierceDmg = DamagingCombatAttributes->PhysicalDamage.DamagePierce * (1 - PierceDef);
	float CrushDef = CombatAttributes->PhysicalDamage.DefenseCrush - DamagingCombatAttributes->GetArmorPenetrationOnCrush();
	float CrushDmg = DamagingCombatAttributes->PhysicalDamage.DamageCrush * (1 - CrushDef);
	float FireDmg = 0.0f;
	float ColdDmg = 0.0f;
	float ToxicDmg = 0.0f;

	if (DamagingCombatAttributes->FireDamage.bIsActive)
	{
		FireDmg = DamagingCombatAttributes->FireDamage.DamageOnTarget * (1 - CombatAttributes->FireDamage.DamageReductionOnSelf);
		
		float ChanceToOverheat = DamagingCombatAttributes->FireDamage.PrimaryEffect.ChanceOnTarget;
	}

	if (DamagingCombatAttributes->ColdDamage.bIsActive)
	{
		ColdDmg = DamagingCombatAttributes->ColdDamage.DamageOnTarget * (1 - CombatAttributes->ColdDamage.DamageReductionOnSelf);
	}

	if (DamagingCombatAttributes->ToxicDamage.bIsActive)
	{
		ToxicDmg = DamagingCombatAttributes->ToxicDamage.DamageOnTarget * (1 - CombatAttributes->ToxicDamage.DamageReductionOnSelf);
	}

	float TotalDamage = SlashDmg + PierceDmg + CrushDmg + FireDmg + ColdDmg + ToxicDmg;
	
	if (bIsCriticalHit)
	{
		TotalDamage = TotalDamage * DamageCauser->CombatCalculatorComponent->OutObtainLatestCritDamage();
	}

	InDetermineStatusEffects(DamagingCombatAttributes);
}

void UCombatCalculatorComponent::InDetermineStatusEffects(UCombatAttributesSet* DamagingCombatAttributes)
{
	InProcessStatusElementDamage(DamagingCombatAttributes->BleedDamage, CombatAttributes->BleedDamage, bIsBleeding);
	InProcessStatusElementDamage(DamagingCombatAttributes->FireDamage, CombatAttributes->FireDamage, bIsOverheating, bIsBurning);
	InProcessStatusElementDamage(DamagingCombatAttributes->ColdDamage, CombatAttributes->ColdDamage, bIsChilled, bIsFrozen);
	InProcessStatusElementDamage(DamagingCombatAttributes->ToxicDamage, CombatAttributes->ToxicDamage, bIsPoisoned, bIsNecrosis);

	InProcessStatusEffect(DamagingCombatAttributes->Stun, CombatAttributes->Stun, bIsStunned);
	InProcessStatusEffect(DamagingCombatAttributes->KnockDown, CombatAttributes->KnockDown, bIsKnockedDown);
	InProcessStatusEffect(DamagingCombatAttributes->Cripple, CombatAttributes->Cripple, bIsCrippled);
	InProcessStatusEffect(DamagingCombatAttributes->Blind, CombatAttributes->Blind, bIsBlinded);
}

void UCombatCalculatorComponent::InProcessStatusElementDamage(FElementalDamage Offensive, FElementalDamage Defensive, bool PrimaryStatusBool, bool SecondaryStatusBool)
{
	if (Offensive.bIsActive)
	{
		InProcessStatusEffect(Offensive.PrimaryEffect, Defensive.PrimaryEffect, PrimaryStatusBool);
		if (Offensive.bHasSecondaryState)
		{
			if (Offensive.PrimaryEffect.CurrentStacks == 5 && Defensive.SecondaryEffect.CurrentStacks < Defensive.SecondaryEffect.MaximumStacks)
			{
				Defensive.SecondaryEffect.CurrentStacks++;
			}
			InProcessStatusEffect(Offensive.SecondaryEffect, Defensive.SecondaryEffect, SecondaryStatusBool);
		}
	}
}

void UCombatCalculatorComponent::InProcessStatusElementDamage(FElementalDamage Offensive, FElementalDamage Defensive, bool PrimaryStatusBool)
{
	if (Offensive.bIsActive)
	{
		InProcessStatusEffect(Offensive.PrimaryEffect, Defensive.PrimaryEffect, PrimaryStatusBool);
	}
}


void UCombatCalculatorComponent::InProcessStatusEffect(FStatusEffect OffensiveEffect, FStatusEffect DefensiveEffect, bool StatusBool)
{
	if (DefensiveEffect.CurrentStacks < DefensiveEffect.MaximumStacks)
	{
		if (FMath::Rand() <= OffensiveEffect.ChanceOnTarget - DefensiveEffect.EffectChanceMitigation)
		{
			DefensiveEffect.CurrentStacks++;
			float EffectDuration = OffensiveEffect.DurationOnTarget;
			EffectDuration = EffectDuration - (EffectDuration * DefensiveEffect.EffectDurationMitigation);

			StatusBool = true;
		}
	}
}





