// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "PassiveSkilltreeNodeTypes.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPassiveSkillEffect : uint8
{
	E_AddAttributeAgility	UMETA(DisplayName = "Add Agility"),
	E_AddAttributeArmorPenetration UMETA(DisplayName = "Add Armor Penetration"),
	E_AddAttributeCarryCapacity UMETA(DisplayName = "Add Carry Capacity"),
	E_AddAttributeConstitution UMETA(DisplayName = "Add Constitution"),
	E_AddDamage1hCrush UMETA(DisplayName = "Add 1h Crush Dmg"),
	E_AddDamage1hPierce		UMETA(DisplayName = "Add 1h Pierce Dmg"),
	E_AddDamage1hSlash		UMETA(DisplayName = "Add 1h Slash Dmg"),
	E_AddDamage2hCrush		UMETA(DisplayName = "Add 2h Crush Dmg"),
	E_AddDamage2hPierce		UMETA(DisplayName = "Add 2h Pierce Dmg"),
	E_AddDamage2hSlash		UMETA(DisplayName = "Add 2h Slash Dmg"),
	E_AddAttackDamageCritical		UMETA(DisplayName = "Add Crit Damage"),
	E_AddAttributeEndurance UMETA(DisplayName = "Add Endurance"),
	E_AddAttributeHealth UMETA(DisplayName = "Add Health"),
	E_AddAttributeHealthRegen UMETA(DisplayName = "Add Health Regen"),
	E_AddAttributeStamina UMETA(DisplayName = "Add Stamina"),
	E_AddAttributeStaminaRegen UMETA(DisplayName = "Add Stamina Regen"),
	E_AddAttributeStrength	UMETA(DisplayName = "Add Strength"),
	E_IncreaseModifierBleedChance		UMETA(DisplayName = "Increase Bleed Chance"),
	E_IncreaseModifierCritChance		UMETA(DisplayName = "Increase Crit Chance"),
	E_IncreaseModifierKnockdownChance		UMETA(DisplayName = "Increase Knockdown Chance"),
	E_IncreaseDurationStun		UMETA(DisplayName = "Increase Stun Duration"),
	E_IncreaseModifierKnockbackStrength		UMETA(DisplayName = "Increase Knockback Strength"),
	E_IncreaseModifierDamageBlocked		UMETA(DisplayName = "Increase Blocked Damage"),
	E_ReduceAttributeAttackStaminaCost		UMETA(DisplayName = "Reduce Attack Stamina Cost"),
	E_ReduceAttributeStanceStaminaCost		UMETA(DisplayName = "Reduce Stance Stamina Cost"),
	E_AddResistanceCold 		UMETA(DisplayName = "Resist Cold"),
	E_AddResistanceCripple		UMETA(DisplayName = "Resist Cripple"),
	E_AddResistanceKnockback		UMETA(DisplayName = "Resist Knockback"),
	E_AddResistanceKnockdown		UMETA(DisplayName = "Resist Knockdown"),
	E_AddResistancePoison		UMETA(DisplayName = "Resist Poison"),
	E_AddResistanceStun		UMETA(DisplayName = "Resist Stun"),


};



