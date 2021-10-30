// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatAttributesSet.h"

UCombatAttributesSet::UCombatAttributesSet()
{
		
	//Set up Bleed Damage and status effects
	BleedDamage.bHasSecondaryState = false; //there is no higher effect that bleeding
	BleedDamage.DamageOnTarget = 15.0f;
	BleedDamage.DamageOnTargetTick = 15.0f;
	BleedDamage.PrimaryEffect = Bleeding;
	Bleeding.bIsStacking = true;
	Bleeding.MaximumStacks = 25;
	Bleeding.ChanceOnTarget = PhysicalDamage.BleedChanceOnpierceBase;
	Bleeding.DurationOnTarget = 5.0f;

	//Set up all Fire Damage and Status effects.
	FireDamage.bHasSecondaryState = true; // 'overheat' has higher effect 'burn'
	FireDamage.DamageOnTarget = 20.0f;
	FireDamage.DamageOnTargetTick = 20.0f;
	FireDamage.PrimaryEffect = Overheating;
	FireDamage.SecondaryEffect = Burning;
	Overheating.bIsStacking = true; // Five Stacks of overheating get consumed to cause one stack of burning. 
	Overheating.ChanceOnTarget = 0.05f;
	Overheating.DurationOnTarget = 7.5f;
	Burning.bIsStacking = true;
	Burning.MaximumStacks = 10;
	Burning.ChanceOnTarget = 0.025f;
	Burning.DurationOnTarget = 5.0f;

	ColdDamage.bHasSecondaryState = true;
	ColdDamage.DamageOnTarget = 10.0f;
	ColdDamage.DamageOnTargetTick = 5.0f;
	ColdDamage.PrimaryEffect = Chilled;
	ColdDamage.PrimaryEffect = Freezing;
	Chilled.bIsStacking = true;	// Five Stacks of chilled would cause the Frozen Condition. 
	Chilled.ChanceOnTarget = 0.015f;
	Chilled.DurationOnTarget = 5.0f;
	Chilled.MaximumStacks = 10;
	Freezing.bIsStacking = false;
	Freezing.ChanceOnTarget = 0.005f;
	Freezing.DurationOnTarget = 6.0f;

	ToxicDamage.bHasSecondaryState = true;
	ToxicDamage.DamageOnTarget = 10.0f;
	ToxicDamage.DamageOnTargetTick = 10.0f;
	ToxicDamage.PrimaryEffect = Poison;
	ToxicDamage.SecondaryEffect = Necrosis;
	Poison.bIsStacking = true; //Five stacks of poison will cause necrosis.
	Poison.ChanceOnTarget = 0.075f;
	Poison.DurationOnTarget = 10.0f;
	Poison.MaximumStacks = 25;
	Necrosis.bIsStacking = false;
	Necrosis.ChanceOnTarget = 0.005f;
	Necrosis.DurationOnTarget = 8.0f;

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

float UCombatAttributesSet::GetArmorPenetrationOnPierce()
{
	return PhysicalDamage.DamagePierce * (PhysicalDamage.ArmorPenetration * 0.0002f);
}

float UCombatAttributesSet::GetArmorPenetrationOnCrush()
{
	return PhysicalDamage.DamageCrush * PhysicalDamage.ArmorPenetration * 0.0002f;
}
