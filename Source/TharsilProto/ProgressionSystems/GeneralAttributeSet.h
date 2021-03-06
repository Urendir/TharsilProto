// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Misc/App.h"
#include "UObject/NoExportTypes.h"
#include "GeneralAttributeSet.generated.h"



/**
						MAIN CHARACTER ATTRIBUTES and their calculation
						---------------------
				This struct is used to define the main attributes of the character: strength, agility, endurance, constitution, arcane essence and spirit.
*/


USTRUCT(BlueprintType)
struct THARSILPROTO_API FEnergyAttribute : public FTableRowBase
{
	GENERATED_BODY()

public:
	//-----------------------------
	/*Current AttributeValue. This fluctuates depending on various elements. E.g. Health gets decreased by damage. Stamina decreased by sprinting*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Attribute Values")
	float CurrentValue = 0.0f;
	/*The current maximum of the Attribute.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Attribute Values")
	float CurrentMaxValue = 0.0f;
	/*the value that the character starts with, before leveling bonuses, gear etc*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Energy Attribute Values")
	float DefaultValue = 0.0f;
	/*This is used for temporary buffs.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Attribute Values")
	float LastRememberedValue = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Energy Attribute Values")
	float RegenerationRate = 0.0f;
	/*used if an attribute drains rather than regenerates. If = true, the regenerationRate float will be used to calculate the drain rate.*/
	bool bIsDraining = false;


};


USTRUCT(BlueprintType)
struct THARSILPROTO_API FGeneralAttribute : public FTableRowBase
{
	GENERATED_BODY()

public:
	//-----------------------------
	/*the value that the character starts with, before leveling bonuses, gear etc*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Energy Attribute Values")
		float DefaultValue = 0.0f;
	/*Current AttributeValue*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Attribute Values")
		float CurrentValue = 0.0f;

	/*This is used for temporary buffs.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Attribute Values")
		float LastRememberedValue = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Energy Attribute Values")
		float MaxValue = 9999999999.0f;
};

USTRUCT(BlueprintType)
struct THARSILPROTO_API FMainAttribute : public FTableRowBase
{
	GENERATED_BODY()

public:
	//-----------------------------
	/*the value that the character starts with, before leveling bonuses, gear etc*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Energy Attribute Values")
		float DefaultValue = 0.0f;
	/*Current AttributeValue*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Attribute Values")
		float CurrentValue = 0.0f;

	/*This is used for temporary buffs.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Attribute Values")
		float LastRememberedValue = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Energy Attribute Values")
		float MaxValue = 255.0f;
};

/**
						PHYSICAL ATTRIBUTES
						---------------------
				These are the non magical, non-status effects.
*/

USTRUCT(BlueprintType)
struct THARSILPROTO_API FPhysicalDamage : public FTableRowBase
{
	GENERATED_BODY()

public:

	/*This is a numeric value indicating the raw Slash Damage*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageSlash = 0.0f;
	/*This is a numeric value indicating the raw Pierce Damage*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamagePierce = 1.0f;
	/*This is a numeric value indicating the raw Crush Damage*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageCrush = 10.0f;
	/*Armor Penetration total can go from 0 to 600 and is then divided in the damage calculation, to give a percent of ignored armor on pierce and crush attack*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ArmorPenetration = 0;
	/*This is a modifier of the damage of Slashing Attacks. Influenced by Passive traits and abilities*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageSlashModifier = 0.0f;
	/*This is a modifier of the damage of Piercing Attacks. Influenced by Passive traits and abilities*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamagePierceModifier = 0.0f;
	/*This is a modifier of the damage of Crushing Attacks. Influenced by Passive traits and abilities*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageCrushModifier = 0.0f;


	/*This is a percentile indicator of the damage mitigation to Slashing Attacks*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DefenseSlash = 0.0f;
	/*This is a percentile indicator of the damage mitigation to Piercing Attacks*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DefensePierce = 0.0f;
	/*This is a percentile indicator of the damage mitigation to Crushing Attacks*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DefenseCrush = 0.0f;
	/*This is a modifier of the damage mitigation to Slashing Attacks. Influenced by Passive traits and abilities*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DefenseSlashModifier = 0.0f;
	/*This is a modifier of the damage mitigation to Piercing Attacks. Influenced by Passive traits and abilities*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DefensePierceModifier = 0.0f;
	/*This is a modifier of the damage mitigation to Crushing Attacks. Influenced by Passive traits and abilities*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DefenseCrushModifier = 0.0f;


	/*Chances to cause Status Effects per damage type*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float BleedChanceOnSlashBase = 0.005f; //0.5%
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float StunChanceOnCrushBase = 0.005f; //0.5%
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float BleedChanceOnpierceBase = 0.0025f; //0.25%
};

//
////------------------------------------ This Enum Allows for Status Effect Selection--------------------------------
//
//UENUM(BlueprintType)
//enum class EStatusEffect : uint8
//{
//	E_Default = 0		UMETA(DisplayName = "None"),
//	E_Overheating = 1		UMETA(DisplayName = "Overheating"),
//	E_Burning = 2		UMETA(DisplayName = "Burning"),
//	E_Chilled = 3		UMETA(DisplayName = "Chilled"),
//	E_Freezing = 4		UMETA(DisplayName = "Freezing"),
//	E_Poisoned = 5		UMETA(DisplayName = "Poisoned"),
//	E_Crippled = 6		UMETA(DisplayName = "Crippled"),
//	E_Stunned = 7		UMETA(DisplayName = "Stunned"),
//	E_Blinded = 8		UMETA(DisplayName = "Blinded"),
//	E_KnockDown = 9		UMETA(DisplayName = "Knocked Down"),
//	E_Terrified = 10	UMETA(DisplayName = "Terrified"),
//};


/**
						STATUS EFFECT ATTRIBUTES AND DAMAGE TYPES
						---------------------
				These are damage types that can tick and can cause status effects. eg. bleed damage, fire damage, poison damage.
*/

USTRUCT(BlueprintType)
struct THARSILPROTO_API FStatusEffect : public FTableRowBase
{
	GENERATED_BODY()

public:
	/*Can multiple stacks of the primary effect be applied to a character?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsStacking = false;

	//-----------------------------
	/*Damage done to the target on Tick*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageOnTargetTick = 0.0f;
	//-----------------------------
	/*Damage done to this character on Tick*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageOnSelfTick = 0.0f;

	/*The Duration this effect should still continue to tick.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DurationRemaining = 0.0f;

	/*This is to be determined in the constructor of the UCombatAttributesSet and should be based on the type of effect. A non-stackable effect defaults to 1 max stack. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 MaximumStacks = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 CurrentStacks = 0;

	/*This is the duration in seconds that the status effect will be active on the target*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DurationOnTarget = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DurationOnTargetBase = 1.0f;

	/*Chance to apply the effect on target, when triggered*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ChanceOnTarget = 0.0f;

	/*This impacts the time an effect is active on a character*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EffectDurationMitigation = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EffectChanceMitigation = 0.0f;

};


USTRUCT(BlueprintType)
struct THARSILPROTO_API FElementalDamage : public FTableRowBase
{
	GENERATED_BODY()

public:

	/*This is set to false when the attack does not have a component that could trigger this specific damage type*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsActive = true;


	/*Damage done to the target on Activation as one-off*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageOnTarget = 0.0f;
	/*This is a modifier applied from Passives and other elements.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageOnTargetModifier = 0.0f;
	/*How much defense the character has against this type of damage. This is Hard Damage Mitigation. Represented in PERCENT*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageReductionOnSelf = 0.0f;
	/*This is a modifier applied from Passives and other elements.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageReductionOnSelfModifier = 0.0f;

	//STATUS EFFECT -PRIMARY (overheat, chill, poison)

	/*This is effect one. A fire spell can cause overheating and then burning. This would be overheating*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FStatusEffect PrimaryEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bHasSecondaryState;
	//STATUS EFFECT - SECONDARY (burn, freeze, necrosis)

	/*This is effect one. A fire spell can cause overheating and then burning. This would be burning */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FStatusEffect SecondaryEffect;

};




/**
 * 
 */
UCLASS(BlueprintType)
class THARSILPROTO_API UGeneralAttributeSet : public UObject
{
	GENERATED_BODY()

public:

	UGeneralAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Attribute Values")
	FMainAttribute Strength;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Attribute Values")
	FMainAttribute Agility;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Attribute Values")
	FMainAttribute Constitution;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Attribute Values")
	FMainAttribute Endurance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Attribute Values")
	FMainAttribute Spirit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Attribute Values")
	FMainAttribute ArcaneEssence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy Attribute Values")
	FEnergyAttribute Health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy Attribute Values")
	FEnergyAttribute Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy Attribute Values")
	FEnergyAttribute Mana;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy Attribute Values")
	FEnergyAttribute Breath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General Attribute Values")
	FGeneralAttribute CritChance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General Attribute Values")
	FGeneralAttribute CritDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Costs")
	FGeneralAttribute AttackCostReduction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Costs")
	FGeneralAttribute StanceCostReduction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Costs")
	FGeneralAttribute SprintSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Costs")
	FGeneralAttribute SprintCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FPhysicalDamage PhysicalDamageAndResistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FPhysicalDamage OneHandBonusDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FPhysicalDamage TwoHandBonusDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FPhysicalDamage RangedBonusDamage;

	// Status Effects that Damage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FElementalDamage BleedDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FElementalDamage FireDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FElementalDamage ColdDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FElementalDamage ToxicDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FElementalDamage CorrosionDamage;
	//Status effect elements of Damage Types.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Bleeding;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Overheating;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Burning;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Chilled;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Freezing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Poison;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Necrosis;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Corrosion;

	//Special Status Effects that only apply on certain attacks.
	//these can be seen as hybrids - not pure status effect, not damage type.

	/*Can be triggered by certain attack types only*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special Status Effects")
	FElementalDamage BlindDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Special Status Effects")
	FStatusEffect Blinding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special Status Effects")
	FElementalDamage WeakenDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Special Status Effects")
	FStatusEffect Weakening;

	//Pure Chance Effects, no damage but cause other effects. Can always be triggered by regular attacks with a low chance.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pure Status Effects")
	FStatusEffect Stun;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pure Status Effects")
	FStatusEffect KnockDown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pure Status Effects")
	FStatusEffect Cripple;


	
};
