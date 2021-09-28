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
	E_AddAttributeAgility	UMETA(DisplayName = "AddAttributeAgility"),
	E_AddAttributeArcaneEssence	UMETA(DisplayName = "AddAttributeArcaneEssence"),
	E_AddAttributeArmorPenetration	UMETA(DisplayName = "AddAttributeArmorPenetration"),
	E_AddAttributeBreath	UMETA(DisplayName = "AddAttributeBreath"),
	E_AddAttributeCarryCapacity	UMETA(DisplayName = "AddAttributeCarryCapacity"),
	E_AddAttributeConstitution	UMETA(DisplayName = "AddAttributeConstitution"),
	E_AddAttributeEndurance	UMETA(DisplayName = "AddAttributeEndurance"),
	E_AddAttributeHealth	UMETA(DisplayName = "AddAttributeHealth"),
	E_AddAttributeRegenHealth	UMETA(DisplayName = "AddAttributeRegenHealth"),
	E_AddAttributeRegenStamina	UMETA(DisplayName = "AddAttributeRegenStamina"),
	E_AddAttributeSpirit	UMETA(DisplayName = "AddAttributeSpirit"),
	E_AddAttributeStamina	UMETA(DisplayName = "AddAttributeStamina"),
	E_AddAttributeStrength	UMETA(DisplayName = "AddAttributeStrength"),
	E_AddChanceBleed	UMETA(DisplayName = "AddChanceBleed"),
	E_AddChanceBurn	UMETA(DisplayName = "AddChanceBurn"),
	E_AddChanceChill	UMETA(DisplayName = "AddChanceChill"),
	E_AddChanceCripple	UMETA(DisplayName = "AddChanceCripple"),
	E_AddChanceCrit	UMETA(DisplayName = "AddChanceCrit"),
	E_AddChanceFreeze	UMETA(DisplayName = "AddChanceFreeze"),
	E_AddChanceKnockdown	UMETA(DisplayName = "AddChanceKnockdown"),
	E_AddChancePoison	UMETA(DisplayName = "AddChancePoison"),
	E_AddChanceStun	UMETA(DisplayName = "AddChanceStun"),
	E_AddDamage1hCrush	UMETA(DisplayName = "AddDamage1hCrush"),
	E_AddDamage1hPierce	UMETA(DisplayName = "AddDamage1hPierce"),
	E_AddDamage1hSlash	UMETA(DisplayName = "AddDamage1hSlash"),
	E_AddDamage2hCrush	UMETA(DisplayName = "AddDamage2hCrush"),
	E_AddDamage2hPierce	UMETA(DisplayName = "AddDamage2hPierce"),
	E_AddDamage2hSlash	UMETA(DisplayName = "AddDamage2hSlash"),
	E_AddDamageBleed	UMETA(DisplayName = "AddDamageBleed"),
	E_AddDamageCorrosive	UMETA(DisplayName = "AddDamageCorrosive"),
	E_AddDamageCritical	UMETA(DisplayName = "AddDamageCritical"),
	E_AddDamageFire	UMETA(DisplayName = "AddDamageFire"),
	E_AddDamageFrost	UMETA(DisplayName = "AddDamageFrost"),
	E_AddDamageRangedCrush	UMETA(DisplayName = "AddDamageRangedCrush"),
	E_AddDamageRangedPierce	UMETA(DisplayName = "AddDamageRangedPierce"),
	E_AddDamageRangedSlash	UMETA(DisplayName = "AddDamageRangedSlash"),
	E_AddDamageToxic	UMETA(DisplayName = "AddDamageToxic"),
	E_AddDurationBleed	UMETA(DisplayName = "AddDurationBleed"),
	E_AddDurationBlindness	UMETA(DisplayName = "AddDurationBlindness"),
	E_AddDurationChill	UMETA(DisplayName = "AddDurationChill"),
	E_AddDurationCripple	UMETA(DisplayName = "AddDurationCripple"),
	E_AddDurationFreeze	UMETA(DisplayName = "AddDurationFreeze"),
	E_AddDurationPoison	UMETA(DisplayName = "AddDurationPoison"),
	E_AddDurationStun	UMETA(DisplayName = "AddDurationStun"),
	E_AddDurationBurn	UMETA(DisplayName = "AddDurationBurn"),
	E_AddDurationCorrosion	UMETA(DisplayName = "AddDurationCorrosion"),
	E_AddResistanceCorrosion	UMETA(DisplayName = "AddResistanceCorrosion"),
	E_AddResistanceCrush	UMETA(DisplayName = "AddResistanceCrush"),
	E_AddResistanceFrost	UMETA(DisplayName = "AddResistanceFrost"),
	E_AddResistanceKnockback	UMETA(DisplayName = "AddResistanceKnockback"),
	E_AddResistanceKnockdown	UMETA(DisplayName = "AddResistanceKnockdown"),
	E_AddResistanceOverheat	UMETA(DisplayName = "AddResistanceOverheat"),
	E_AddResistancePierce	UMETA(DisplayName = "AddResistancePierce"),
	E_AddResistancePoison	UMETA(DisplayName = "AddResistancePoison"),
	E_AddResistanceSlash	UMETA(DisplayName = "AddResistanceSlash"),
	E_AddSpeedSprint	UMETA(DisplayName = "AddSpeedSprint"),
	E_AddStrengthKnockback	UMETA(DisplayName = "AddStrengthKnockback"),
	E_PerCorrosionArmorPenetration	UMETA(DisplayName = "PerCorrosionArmorPenetration"),
	E_ReduceCostAttack	UMETA(DisplayName = "ReduceCostAttack"),
	E_ReduceCostDodge	UMETA(DisplayName = "ReduceCostDodge"),
	E_ReduceCostShout	UMETA(DisplayName = "ReduceCostShout"),
	E_ReduceCostSprint	UMETA(DisplayName = "ReduceCostSprint"),
	E_ReduceCostStance	UMETA(DisplayName = "ReduceCostStance"),
	E_ReduceDamageOnBlock	UMETA(DisplayName = "ReduceDamageOnBlock"),
	E_ReduceDamageToArmor	UMETA(DisplayName = "ReduceDamageToArmor"),
	E_ReduceDamageToWeapon	UMETA(DisplayName = "ReduceDamageToWeapon"),
	E_ReduceDurationBleed	UMETA(DisplayName = "ReduceDurationBleed"),
	E_ReduceDurationBlind	UMETA(DisplayName = "ReduceDurationBlind"),
	E_ReduceDurationBurn	UMETA(DisplayName = "ReduceDurationBurn"),
	E_ReduceDurationChill	UMETA(DisplayName = "ReduceDurationChill"),
	E_ReduceDurationStun	UMETA(DisplayName = "ReduceDurationStun"),
	E_RedurceDurationCripple	UMETA(DisplayName = "RedurceDurationCripple"),

};



