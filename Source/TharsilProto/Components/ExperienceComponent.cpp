// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceComponent.h"
#include "TharsilProto/Characters/BaseCharacterPlayable.h"
#include "TharsilProto/Characters/BaseCharacter.h"

// Sets default values for this component's properties
UExperienceComponent::UExperienceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Owner = Cast<ABaseCharacterPlayable>(GetOwner());
	CurrentLevel = 1;
}


// Called when the game starts
void UExperienceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CalculateXPToNextLevel();
}

void UExperienceComponent::IncreaseCurrentXP(int32 XPReward) 
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


int32 UExperienceComponent::CalculateXPToNextLevel() 
{
	if(CurrentLevel >= 120)
	{
		IsAtLevelCap = true;
	}	
	else if(CurrentLevel > LevelFirstCap)
	{
		float XPCalculation = CurrentLevel * CurrentLevel * MidMultiplier;
		XPToNextLevel = (int32)XPCalculation;
	}
	else
	{
		float XPCalculation = CurrentLevel * CurrentLevel * InitialMultiplier;
		XPToNextLevel = (int32)XPCalculation;
	}

	return XPToNextLevel;

	//TO DO: Display in Widget /XP Bar
}


void UExperienceComponent::HandleLevelUp() 
{
	CurrentLevel++;
	CalculateXPToNextLevel();
	Owner->HandleLevelUpProcess();
	OnLevelUpDelegate.Broadcast(CurrentLevel);
	DEBUG_DisplayLevel();
}


void UExperienceComponent::DEBUG_DisplayLevel() 
{
	UE_LOG(LogTemp, Warning, TEXT("Ding! Current Level is %i. For next level, %i XP is needed."), CurrentLevel, XPToNextLevel);
}




