// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_PrimarySkillLine.generated.h"

/**
 * 
 */
UCLASS()
class THARSILPROTO_API UDA_PrimarySkillLine : public UDataAsset
{
	GENERATED_BODY()
	
public: 
	//------------------------FUNCTIONS for XP Accumulation and Leveling-----------------------------------	
	
	UFUNCTION(BlueprintCallable)
	void IncreaseCurrentXP(int32 XPReward);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Stats", meta = (AllowPrivateAccess = "true"))
	int32 CurrentLevel;

private:
	//------------------------LEVELING CALCULATION VARIABLES-------------------------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Stats", meta = (AllowPrivateAccess = "true"))
	int32 CurrentXP = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Stats", meta = (AllowPrivateAccess = "true"))
	int32 XPToNextLevel;


	//------------------------LEVELING XP MODIFIER VARIABLES-------------------------------------
	//The below Calculates XP To Next Level = Current Level * Multiplier / Divider;
	//The Caps will be checked against current level to determine the modifiers for each level.

	//Levels 0-19
	float InitialMultiplier = 380.f;
	float InitialDivider= 0.5f;
	//Levels 20-39
	int32 LevelFirstCap = 20;
	float FirstCapMultiplier = 680.f;
	float FirstCapDivider= 0.32f;
	//Levels 40-79
	int32 LevelMidCap = 40;
	float MidCapMultiplier = 925.f;
	float MidCapDivider= 0.25f;
	//Level 80 and above
	int32 LevelSoftCap = 80;
	float SoftCapMultiplier = 2300.f;
	float SoftCapDivider = 0.13f;
	
	//This becomes relevant once the character hits level 120. XP gain should stop at that point. 
	bool IsAtLevelCap = false;
	int32 LevelHardCap = 120;

	//------------------------PER LEVEL MODIFIERS--------------------------------------------
	float PerLevelHealth = 5.f;
	int32 PerLevelStamina = 3.f;
	float PerLevelCarryCapacity = 0.25;

	//------------------------FUNCTIONS--------------------------------------------
	int32 CalculateXPToNextLevel();
	void HandleLevelUp();

	void DEBUG_DisplayLevel();

};
