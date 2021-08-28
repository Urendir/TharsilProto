// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExperienceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UExperienceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExperienceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public: 
	//------------------------FUNCTIONS for XP Accumulation and Leveling-----------------------------------	
	
	UFUNCTION(BlueprintCallable)
	void IncreaseCurrentXP(int32 XPReward);

private:
	//------------------------LEVELING CALCULATION VARIABLES-------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Stats", meta = (AllowPrivateAccess = "true"))
	int32 CurrentLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Stats", meta = (AllowPrivateAccess = "true"))
	int32 CurrentXP = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Stats", meta = (AllowPrivateAccess = "true"))
	int32 XPToNextLevel;


	//------------------------LEVELING XP MODIFIER VARIABLES-------------------------------------
	//The below Calculates XP To Next Level = Current Level * Multiplier / Divider;
	//The Caps will be checked against current level to determine the modifiers for each level.

	//Levels 0-9
	float InitialMultiplier = 110.0f;
	//Levels 10 to 119
	int32 LevelFirstCap = 10;
	float MidMultiplier = 95.0f;

	int32 LevelHardCap = 120;
	//This becomes relevant once the CurrentLevel == LevelHardCap. XP gain should stop at that point. 
	bool IsAtLevelCap = false;

	//------------------------PER LEVEL MODIFIERS--------------------------------------------
	float PerLevelHealth = 5.f;
	int32 PerLevelStamina = 3.f;
	float PerLevelCarryCapacity = 0.25;

	//------------------------FUNCTIONS--------------------------------------------
	int32 CalculateXPToNextLevel();
	void HandleLevelUp();

	void DEBUG_DisplayLevel();

};
