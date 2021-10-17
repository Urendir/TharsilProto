// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TharsilProto/CombatEffects/StatusEffectBase.h"
#include "CombatNumbersStruct.generated.h"



//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------Damage&Defense Types Struct Below ------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------These will be obtained from the Weapon/Armor that is equipped, as well as from any passives, skills and abilities that grant bonuses to the various attack types-----

USTRUCT(BlueprintType)
struct FCombatNumbers
{
	GENERATED_BODY()

public:

	// -------------Fixed Number-------------------- Physical Damage Variables---------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlashDmg = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlashDefense = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrushDmg = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrushDefense = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PierceDmg = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PierceDefense = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ArmorPenetration = 0.0f;


	//--------------------------------------- Status Effect Variables-----------------------------------


	/// <summary>
	/// CrippledStatus will inflict a limping animation and slow down movement for the duration of the effect.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusEffectBase CrippledStatus;


	//==============KnockBack==========================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusEffectBase KnockbackStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusEffectBase KnockdownStatus;

	// When stunned, movement is stopped. No attacks possible. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusEffectBase StunnedStatus;


	// Bleed Damage = Triggered on Slash or dedicated. Deals high DOT.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusEffectBase BleedingStatus;

	// Poison Damage = Triggered from certain skills/mods. Intended to slow down health regen and deal DOT. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusEffectBase PoisonedStatus;

	// -------------------------------------------------- Magical Damage Variables---------------------

	// Corrosion deals DOT to health and DOT to equipped armor / Increases AP against target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusEffectBase CorrodingStatus;

	//Fire can cause Burning. burning deals high DOT. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusEffectBase BurningStatus;

	//Cold Damage causes Freeze Chance to trigger. Freeze deals slow and reduces Stamina Regen.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusEffectBase ChilledStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusEffectBase FrozenStatus;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float LightningDmg = 0.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float FaeDmg = 0.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float NecroticDmg = 0.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float AetherealDmg = 0.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float DarknessDmg = 0.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float LightDmg = 0.0f;



	FCombatNumbers()
	{
	};

};

