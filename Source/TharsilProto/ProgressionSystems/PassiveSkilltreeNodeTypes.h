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
	E_AddAttributeAgility			UMETA(DisplayName = "Add Agility"),
	E_AddAttributeArcaneEssence			UMETA(DisplayName = "Add Arcane Essence"),
	E_AddAttributeArmorPenetration		UMETA(DisplayName = "Add Armor Penetration"),
	E_AddAttributeBreath				UMETA(DisplayName = "Add Breath"),
	E_AddAttributeCarryCapacity			UMETA(DisplayName = "Add Carry Capacity"),
	E_AddAttributeConstitution		UMETA(DisplayName = "Add Constitution"),
	E_AddAttributeEndurance			UMETA(DisplayName = "Add Endurance"),
	E_AddAttributeHealth			UMETA(DisplayName = "Add Health"), 
	E_AddAttributeHealthRegen		UMETA(DisplayName = "Add Health Regen"),
	E_AddAttributeSpirit			UMETA(DisplayName = "Add Spirit"),
	E_AddAttributeStamina			UMETA(DisplayName = "Add Stamina"),
	E_AddAttributeStaminaRegen		UMETA(DisplayName = "Add Stamina Regen"),
	E_AddAttributeStrength			UMETA(DisplayName = "Add Strength"),
	E_AddDamage1hCrush			UMETA(DisplayName = "Add 1h Crush Dmg"), //NOT ADDED YET
	E_AddDamage1hPierce			UMETA(DisplayName = "Add 1h Pierce Dmg"),
	E_AddDamage1hSlash			UMETA(DisplayName = "Add 1h Slash Dmg"),
	E_AddDamage2hCrush			UMETA(DisplayName = "Add 2h Crush Dmg"),
	E_AddDamage2hPierce			UMETA(DisplayName = "Add 2h Pierce Dmg"),
	E_AddDamage2hSlash			UMETA(DisplayName = "Add 2h Slash Dmg"),
	E_AddDamageCritical			UMETA(DisplayName = "Add Crit Damage"),
	E_AddDamageRangedCrush		UMETA(DisplayName = "Add Ranged Crush Dmg"),
	E_AddDamageRangedPierce		UMETA(DisplayName = "Add Ranged Pierce Dmg"),
	E_AddDamageRangedSlash		UMETA(DisplayName = "Add Ranged Pierce Dmg"),
	E_AddResistanceFrost			UMETA(DisplayName = "Resist Frost"), // ADDED
	E_IncreaseModifierCrippleChance				UMETA(DisplayName = "Cripple Chance"),
	E_AddResistanceOverheat				UMETA(DisplayName = "Resist Heat"),
	E_AddResistanceKnockback			UMETA(DisplayName = "Resist Knockback"),
	E_AddResistancePoison				UMETA(DisplayName = "Resist Poison"),
	E_IncreaseModifierBleedChance		UMETA(DisplayName = "Increase Bleed Chance"),
	E_IncreaseModifierBleedDuration		UMETA(DisplayName = "Increase Bleed Duration"),
	E_IncreaseModifierCrippleDuration		UMETA(DisplayName = "Increase Cripple Duration"),
	E_IncreaseModifierCritChance			UMETA(DisplayName = "Increase Crit Chance"),
	E_ReduceDamageOnBlock					UMETA(DisplayName = "Increase Blocked Damage"),
	E_IncreaseModifierKnockbackStrength		UMETA(DisplayName = "Increase Knockback Strength"),
	E_IncreaseModifierKnockdownChance		UMETA(DisplayName = "Increase Knockdown Chance"),
	E_IncreaseModifierSprintSpeed			UMETA(DisplayName = "Increase Sprint Speed"),
	E_IncreaseModifierStunDuration					UMETA(DisplayName = "Increase Stun Duration"),
	E_ReduceAttributeAttackStaminaCost		UMETA(DisplayName = "Reduce Attack Stamina Cost"),
	E_ReduceAttributeDodgeCost				UMETA(DisplayName = "Reduce Dodge Stamina Cost"),
	E_ReduceAttributeStanceStaminaCost		UMETA(DisplayName = "Reduce Stance Stamina Cost"),
	E_ReduceAttributeShoutStaminaCost		UMETA(DisplayName = "Reduce Shout Stamina Cost"),
	E_ReduceDurationStun			UMETA(DisplayName = "Reduce Stun Duration"),
	E_ReduceDurationBleed			UMETA(DisplayName = "Reduce Bleed Duration"),
	E_RedurceDurationCripple		UMETA(DisplayName = "Reduce Cripple Duration"),
	E_IncreaseBleedDamage			UMETA(DisplayName = "Increase Bleed Damage"),
	E_IncreaseFireDamage			UMETA(DisplayName = "Increase Fire Damage"),
	E_IncreaseModifierBurnChance			UMETA(DisplayName = "Increase Burn Chance"),
	E_IncreaseModifierBurnDuration			UMETA(DisplayName = "Increase Burn Duration"),
	E_IncreaseToxicDamage					UMETA(DisplayName = "Increase Toxic Damage"),
	E_IncreaseModifierPoisonChance			UMETA(DisplayName = "Increase Poison Chance"),
	E_IncreaseModifierPoisonDuration			UMETA(DisplayName = "Increase Poison Duration"),
	E_IncreaseModifierBlindnessDuration			UMETA(DisplayName = "Increase Blindness Duration"),
	E_IncreaseModifierStunChance			UMETA(DisplayName = "Increase Stun Chance"),
	E_IncreaseFrostDamage					UMETA(DisplayName = "Increase Frost Damage"),
	E_IncreaseModifierChillChance			UMETA(DisplayName = "Increase Chill Chance"),
	E_IncreaseModifierChillDuration			UMETA(DisplayName = "Increase Chill Duration"),
	E_IncreaseModifierFreezeChance			UMETA(DisplayName = "Increase Freeze Chance"),
	E_IncreaseModifierFreezeDuration			UMETA(DisplayName = "Increase Freeze Duration"),
	E_IncreaseCorrosiveDamage				UMETA(DisplayName = "Increase Corrosion Damage"),
	E_IncreaseModifierCorrosionDuration			UMETA(DisplayName = "Increase Corrosion Duration"),
	E_IncreaseModifierKnockdownResist			UMETA(DisplayName = "Increase Knockdown Resist"),
	E_SlashDefense							UMETA(DisplayName = "Increase Slash Defense"),
	E_PierceDefense							UMETA(DisplayName = "Increase Pierce Defense"),
	E_CrushDefense							UMETA(DisplayName = "Increase Crush Defense"),
	E_ArmorPenetrationPerCorrosion			UMETA(DisplayName = "Increase AP per Corrosion Tick"),
	E_IncreaseModifierCorrosionResist			UMETA(DisplayName = "Increase Corrosion Resist"),
	E_ReduceDamageToArmor					UMETA(DisplayName = "Reduce Damage To Armor"),
	E_ReduceDamageToWeapon					UMETA(DisplayName = "Reduce Damage To Weapons"),
	E_ReduceDurationChill					UMETA(DisplayName = "Reduce incoming chill duration"),
	E_ReduceDurationBurn					UMETA(DisplayName = "Reduce incoming burn duration"),
	E_ReduceDurationBlind					UMETA(DisplayName = "Reduce incoming blind duration"),


};



