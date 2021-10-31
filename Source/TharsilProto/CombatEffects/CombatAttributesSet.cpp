// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatAttributesSet.h"

UCombatAttributesSet::UCombatAttributesSet()
{
		
	//Set up Bleed Damage and status effects
	BleedDamage.bHasSecondaryState = false; //there is no higher effect that bleeding
	BleedDamage.DamageOnTarget = 15.0f;
	BleedDamage.PrimaryEffect = Bleeding;
	Bleeding.bIsStacking = true;
	Bleeding.MaximumStacks = 25;
	Bleeding.ChanceOnTarget = PhysicalDamage.BleedChanceOnpierceBase;
	Bleeding.DurationOnTarget = 5.0f;
	Bleeding.DamageOnTargetTick = 15.0f;

	//Set up all Fire Damage and Status effects.
	FireDamage.bHasSecondaryState = true; // 'overheat' has higher effect 'burn'
	FireDamage.DamageOnTarget = 20.0f;
	FireDamage.PrimaryEffect = Overheating;
	FireDamage.SecondaryEffect = Burning;
	Overheating.DamageOnTargetTick = 5.0f;
	Overheating.bIsStacking = true; // Five Stacks of overheating get consumed to cause one stack of burning. 
	Overheating.ChanceOnTarget = 0.05f;
	Overheating.DurationOnTarget = 7.5f;
	Burning.DamageOnTargetTick = 20.0f;
	Burning.bIsStacking = true;
	Burning.MaximumStacks = 10;
	Burning.ChanceOnTarget = 0.025f;
	Burning.DurationOnTarget = 5.0f;

	ColdDamage.bHasSecondaryState = true;
	ColdDamage.DamageOnTarget = 10.0f;
	ColdDamage.PrimaryEffect = Chilled;
	ColdDamage.PrimaryEffect = Freezing;
	Chilled.DamageOnTargetTick = 5.0f;
	Chilled.bIsStacking = true;	// Five Stacks of chilled would cause the Frozen Condition. 
	Chilled.ChanceOnTarget = 0.015f;
	Chilled.DurationOnTarget = 5.0f;
	Chilled.MaximumStacks = 10;
	Freezing.DamageOnTargetTick = 25.0f;
	Freezing.bIsStacking = false;
	Freezing.ChanceOnTarget = 0.005f;
	Freezing.DurationOnTarget = 6.0f;

	ToxicDamage.bHasSecondaryState = true;
	ToxicDamage.DamageOnTarget = 10.0f;
	ToxicDamage.PrimaryEffect = Poison;
	ToxicDamage.SecondaryEffect = Necrosis;
	Poison.DamageOnTargetTick = 10.0f;
	Poison.bIsStacking = true; //Five stacks of poison will cause necrosis.
	Poison.ChanceOnTarget = 0.075f;
	Poison.DurationOnTarget = 10.0f;
	Poison.MaximumStacks = 25;
	Necrosis.DamageOnTargetTick = 20.0f;
	Necrosis.bIsStacking = false;
	Necrosis.ChanceOnTarget = 0.005f;
	Necrosis.DurationOnTarget = 8.0f;

	CorrosionDamage.bHasSecondaryState = false;
	CorrosionDamage.DamageOnTarget = 15.0f;
	CorrosionDamage.PrimaryEffect = Corrosion;
	Corrosion.DamageOnTargetTick = 10.0f;
	Corrosion.bIsStacking = true;
	Corrosion.ChanceOnTarget = 0.075f;
	Corrosion.DurationOnTarget = 3.0f;
	Corrosion.MaximumStacks = 10;

	//Set up Pure status effects.	
	Stun.bIsStacking = false;
	Stun.ChanceOnTarget = PhysicalDamage.StunChanceOnCrushBase;
	Stun.DurationOnTarget = 3.5f;

	KnockDown.bIsStacking = false;
	KnockDown.ChanceOnTarget = 0.01f;
	KnockDown.DurationOnTarget = 2.0f;

	Cripple.bIsStacking = false;
	Cripple.ChanceOnTarget = 0.01f;
	Cripple.DurationOnTarget = 5.0f;

	Blind.bIsStacking = false;
	Blind.ChanceOnTarget = 0.001f;
	Blind.DurationOnTargetBase = 3.5f;

}

void UCombatAttributesSet::AddEntireCombatValueSet(UCombatAttributesSet* ValuesToAdd)
{
	AddPhysicalDamageSetValues(ValuesToAdd->PhysicalDamage, PhysicalDamage);
	AddElementalDamageSetValues(ValuesToAdd->BleedDamage, BleedDamage);
	AddElementalDamageSetValues(ValuesToAdd->FireDamage, FireDamage);
	AddElementalDamageSetValues(ValuesToAdd->ColdDamage, ColdDamage);
	AddElementalDamageSetValues(ValuesToAdd->ToxicDamage, ToxicDamage);
	AddElementalDamageSetValues(ValuesToAdd->CorrosionDamage, CorrosionDamage);
	AddElementalDamageSetValues(ValuesToAdd->BlindingDamage, BlindingDamage);
	AddElementalDamageSetValues(ValuesToAdd->WeakeningDamage, WeakeningDamage);
	AddStatusEffectValues(ValuesToAdd->Stun, Stun);
	AddStatusEffectValues(ValuesToAdd->KnockDown, KnockDown);
	AddStatusEffectValues(ValuesToAdd->Cripple, Cripple);

}

void UCombatAttributesSet::AddPhysicalDamageSetValues(FPhysicalDamage ValuesToAdd, FPhysicalDamage ParentValue)
{
	ParentValue.ArmorPenetration += ValuesToAdd.ArmorPenetration;
	ParentValue.DamageCrush += ValuesToAdd.DamageCrush;
	ParentValue.DamagePierce += ValuesToAdd.DamagePierce;
	ParentValue.DamageSlash += ValuesToAdd.DamageSlash;
	ParentValue.DefenseCrush += ValuesToAdd.DefenseCrush;
	ParentValue.DefensePierce += ValuesToAdd.DefensePierce;
	ParentValue.DefenseSlash += ValuesToAdd.DefenseSlash;
}

void UCombatAttributesSet::AddElementalDamageSetValues(FElementalDamage ValuesToAdd, FElementalDamage ParentValue)
{
	ParentValue.DamageOnTarget += ValuesToAdd.DamageOnTarget;
	ParentValue.DamageReductionOnSelf += ValuesToAdd.DamageReductionOnSelf;
	AddStatusEffectValues(ValuesToAdd.PrimaryEffect, ParentValue.PrimaryEffect);
	if (ParentValue.bHasSecondaryState)
	{
		AddStatusEffectValues(ValuesToAdd.SecondaryEffect, ParentValue.SecondaryEffect);
	}
}

void UCombatAttributesSet::AddStatusEffectValues(FStatusEffect ValuesToAdd, FStatusEffect ParentValue)
{
	ParentValue.ChanceOnTarget				+= ValuesToAdd.ChanceOnTarget;
	ParentValue.DamageOnSelfTick			+= ValuesToAdd.DamageOnSelfTick;
	ParentValue.DamageOnTargetTick			+= ValuesToAdd.DamageOnTargetTick;
	ParentValue.DurationOnTarget			+= ValuesToAdd.DurationOnTarget;
	ParentValue.EffectChanceMitigation		+= ValuesToAdd.EffectChanceMitigation;
	ParentValue.EffectDurationMitigation	+= ValuesToAdd.EffectDurationMitigation;
}

float UCombatAttributesSet::GetArmorPenetrationOnPierce()
{
	return PhysicalDamage.DamagePierce * (PhysicalDamage.ArmorPenetration * 0.0002f);
}

float UCombatAttributesSet::GetArmorPenetrationOnCrush()
{
	return PhysicalDamage.DamageCrush * PhysicalDamage.ArmorPenetration * 0.0002f;
}
