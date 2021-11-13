// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Math/UnrealMathUtility.h"


#include "DA_ActiveAbilityBase.generated.h"

/**
 * 
 */

class UCombatAttributesSet;
class UAnimMontage;

UCLASS(Blueprintable)
class THARSILPROTO_API UDA_ActiveAbilityBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	/**This is the name that will be shown in the UI*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
		FString DisplayName;

	/**This is an description for the ability*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
		FText Description;

	//The thumbnail of the ability.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
		UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
		UAnimMontage* AnimationMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float CooldownTime;

	/// <summary>
	/// The amount of time that the ability is blocking other abilities from triggering. 
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
	float TimeToBlockAbilities;
	/*What is the Stamina cost of the ability? All Abilities have this active*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float StaminaCost;
	/*Does the ability cost health, in addition to stamina?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		bool bHasHealthCost;
	/*If bHasHealthCost=true, how much health does the ability cost?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float HealthCost;
	/*Does the ability cost mana, in addition to stamina?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		bool bHasManaCost;
	/*If bHasManaCost=true, how much mana does the ability cost?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		bool bIsSelfTargetOnly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Effects")
	TSubclassOf<UCombatAttributesSet> AbilityAttributes;

	// The Amount of points that can be used for mods on this ability. More mods get added as the Skill Line is leveled up. Max is 10 for high power abilities.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mods")
		int32 ModCapacity;

	UFUNCTION(BlueprintCallable)
	virtual void ApplyAbilityEffect();



	//Mod Array.

};
