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

// -------------------------------------------------- Physical Damage Variables---------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlashDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrushDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PierceDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BleedDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToxicDmg = 0.0f;

// -------------------------------------------------- Magical Damage Variables---------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CorrosiveDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ColdDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaterDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LightningDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FaeDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NecroticDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EtherealDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DarknessDmg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LightDmg = 0.0f;

//------------------------------------------------ Status Condition Variables ----------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BleedChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrippleChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockdownChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockbackChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StunChance = 0.0f;


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

	//---------------------------- BASIC PHYSICAL ARMOR & DEFENSE STATS ------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SlashDefense = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PierceDefense = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrushDefense = 0.0f;

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

	// high armor damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CorrosionResist = 0.0f;

	//---------------------------- MAGICAL DEFENSE STATS ------------------------------------------------------------------------
	/*These will be obtained from the Armor that is equipped, as well as from any skills that grant bonuses to the various resistances*/

		// This is supposed to be high in fire-based creatures, medium in fleshy creatures and low in dried undead, for example.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireResist = 0.0f;

	// Molten creatures would be slowed by this. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ColdResist = 0.0f;

	// Fire creatures would be susceptible to this.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WaterResist = 0.0f;

	// Lightning damages living creatures and water based creatures.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LightningResist = 0.0f;

	// Fae damage is higher against necrotic creatures
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FaeResist = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NecroticResist = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EtherealResist = 0.0f;

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




