// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DamageTypeStruct.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------Damage Types Struct Below ---------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-------These will be obtained from the Weapon that is equipped, as well as from any skills that grant bonuses to the various attack types------

USTRUCT(BlueprintType)
struct FDamageTypeBreakdown
{
	GENERATED_BODY()

public:

// -------------Fixed Number-------------------- Physical Damage Variables---------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlashDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrushDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PierceDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ArmorPenetration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalDamageModifier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalChance = 0.0f;

//--------------------------------------- Status Effect Variables-----------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrippleChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrippleDuration;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockdownChance = 0.0f;

	//Determines how far back the defender gets knocked and impacts knockdown chance of defender.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockbackStrength = 0.0f;

	// When stunned, movement is stopped. No attacks possible. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StunChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StunDuration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlindChance = 0.0f;

	// Bleed Damage = Triggered on Slash or dedicated. Deals high DOT.

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BleedDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BleedChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BleedDuration = 0.0f;

	// Poison Damage = Triggered from certain skills/mods. Intended to slow down health regen and deal DOT. 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToxicDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PoisonChance = 0.0f;

// -------------------------------------------------- Magical Damage Variables---------------------

	// Corrosion deals DOT to health and DOT to equipped armor / Increases AP against target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CorrosiveDmg = 0.0f;

	//Fire can cause Burning. burning deals high DOT. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireDmg = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BurnChance = 0.0f;

	//Cold Damage causes Freeze Chance to trigger. Freeze deals slow and reduces Stamina Regen.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ColdDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LightningDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FaeDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NecroticDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AetherealDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DarknessDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LightDmg = 0.0f;



	FDamageTypeBreakdown()
	{
	};

};

//-----------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------Defensive Damage Resistances Struct below---------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-------These will be obtained from the Armor that is equipped, as well as from any skills that grant bonuses to the various resistances--------


USTRUCT(BlueprintType)
struct FDamageResistanceBreakdown
{
	GENERATED_BODY()

public:

	//------------Fixed Number------ BASIC PHYSICAL ARMOR & DEFENSE STATS ------------------------------------------------------------------------
	// These will get divided by a modifier to obtain the percentile defense rating. 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SlashDefense = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PierceDefense = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrushDefense = 0.0f;

	//-----------------------------Percentage Modifiers for Resistance to Status Effects ----------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float KnockbackResist = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float KnockdownResist = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrippleResist = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StunResist = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
	float BleedResist = 0.0f;

	// poison damage, spores etc.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ToxinResist = 0.0f;


	//---------------------------- MAGICAL DEFENSE STATS ------------------------------------------------------------------------
	/*These will be obtained from the Armor that is equipped, as well as from any skills that grant bonuses to the various resistances*/
	
	// high armor damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CorrosionResist = 0.0f;

	// This is supposed to be high in fire-based creatures, medium in fleshy creatures and low in dried undead, for example.
	//Impacts chance of Burning.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireResist = 0.0f;

	// Fire would be vulnerable. All living creatures would be slowed by this. Slower Stamina Regen. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ColdResist = 0.0f;

	// Lightning damages living creatures and water based creatures.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LightningResist = 0.0f;

	// Fae damage is higher against necrotic creatures
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FaeResist = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NecroticResist = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AetherealResist = 0.0f;

	//Creatures based on Darkness (shadows or other) are immune to this. Light creatures are weak.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DarknessResist = 0.0f;

	//Creatures based on Darness are weak to this, ones based on light are immune
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LightResist = 0.0f;

	FDamageResistanceBreakdown()
	{
	};
};




