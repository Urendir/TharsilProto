// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DamageTypeStruct.generated.h"

USTRUCT(BlueprintType)
struct FDamageTypeBreakdown
{
	GENERATED_BODY()

public:

// -------------------------------------------------- Physical Damage Variables---------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlashDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BluntDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PierceDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BleedDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToxicDmg;

// -------------------------------------------------- Magical Damage Variables---------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CorrosiveDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ColdDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaterDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LightningDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FaeDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NecroticDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EtherealDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DarknessDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LightDmg;

//------------------------------------------------ Status Condition Variables ----------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BleedChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrippleChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockdownChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockbackChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StunChance;


	FDamageTypeBreakdown()
	{
		SlashDmg = 0.0f;

		BluntDmg = 0.0f;

		PierceDmg = 0.0f;

		BleedDmg = 0.0f;

		ToxicDmg = 0.0f;

		CorrosiveDmg = 0.0f;

		FireDmg = 0.0f;

		ColdDmg = 0.0f;

		WaterDmg = 0.0f;

		LightningDmg = 0.0f;

		FaeDmg = 0.0f;

		NecroticDmg = 0.0f;

		EtherealDmg = 0.0f;

		DarknessDmg = 0.0f;

		LightDmg = 0.0f;

		BleedChance = 0.0f;

		CrippleChance = 0.0f;

		KnockdownChance = 0.0f;

		KnockbackChance = 0.0f;

		StunChance = 0.0f;

	};

};

