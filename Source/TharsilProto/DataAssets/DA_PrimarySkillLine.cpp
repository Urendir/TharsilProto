// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_PrimarySkillLine.h"


void UDA_PrimarySkillLine::IncreaseCurrentXP(int32 XPReward) 
{
    if(IsAtLevelCap)
	{
		return;
	}

	int32 XPPool = CurrentXP + XPReward;

	if(XPPool > XPToNextLevel)
	{
		CurrentXP = XPPool - XPToNextLevel;
		HandleLevelUp();
	}
	else
	{
		CurrentXP = XPPool;
	}
	UE_LOG(LogTemp, Warning, TEXT("CurrentXP is: %i"), CurrentXP);
}

int32 UDA_PrimarySkillLine::CalculateXPToNextLevel() 
{
    if(CurrentLevel >= 120)
	{
		IsAtLevelCap = true;
	}
	else if(CurrentLevel > 80)
	{
		float XPCalculation =(CurrentLevel*SoftCapMultiplier)/SoftCapDivider;
		XPToNextLevel = (int32)XPCalculation; 
	}	
	else if(CurrentLevel > 40)
	{
		float XPCalculation =(CurrentLevel*MidCapMultiplier)/MidCapDivider;
		XPToNextLevel = (int32)XPCalculation;
	}
	else if(CurrentLevel > 20)
	{
		float XPCalculation =(CurrentLevel*FirstCapMultiplier)/FirstCapDivider;
		XPToNextLevel = (int32)XPCalculation;
	}
	else
	{
		float XPCalculation =(CurrentLevel*InitialMultiplier)/InitialDivider;
		XPToNextLevel = (int32)XPCalculation;
	}

	return XPToNextLevel;
}

void UDA_PrimarySkillLine::HandleLevelUp() 
{
    CurrentLevel++;
	CalculateXPToNextLevel();
}

void UDA_PrimarySkillLine::DEBUG_DisplayLevel() 
{
    
}
