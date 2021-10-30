// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "StatusEffectBase.generated.h"

/**
 * The Status Effect base give the main elements of all status effects in the game:
------Duration on enemy, when applied in combat;
------Duration on Self;
------Stackable/StackSize;
------Damage Generated (if that is the case); 
----etc.
 * 
 * This should be subclassed to build individual combat effects.
 */

USTRUCT(BlueprintType)
struct THARSILPROTO_API FStatusEffectBase : public FTableRowBase
{
	GENERATED_BODY()

public:

/**
						OFFENSIVE ATTRIBUTES
						---------------------
				These are applied to Target on Attack
*/

	//Chance to apply to enemy, on hit. This is influenced by Active abilities, Skills, equipment, passive stats.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChanceOnTarget = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ChanceOnTargetBase = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ChanceOnTargetFromPassive = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ChanceOnTargetFromAbility = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ChanceOnTargetFromEquipment = 0.0f;
	//Absolute Chance to apply this status effect. If effect is not stackable, the default of 1 is used. Higher than 1 means multiple stacks are applied at once.
	UPROPERTY()
	float ChanceOnTargetMax = 1.0f;

	void CalcChanceOnTarget();

	//Duration on Target
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DurationOnTarget = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DurationOnTargetBase = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DurationOnTargetFromPassive = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DurationOnTargetFromAbility = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DurationOnTargetFromEquipment = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DurationOnTargetMax = 10.0f;

	void CalcDurationOnTarget();

	//Damage on Target

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageOnTarget = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DamageOnTargetBase = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DamageOnTargetFromPassive = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DamageOnTargetFromAbility = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DamageOnTargetFromEquipment = 0.0f;

	void CalcDamageOnTarget();

/**
						DEFENSIVE ATTRIBUTES
						---------------------
				These are applied to Self, in response to attack/environment
*/

	//Chance to Apply the status on self. This is generally 1 for most skills. (100%)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChanceOnSelf = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ChanceOnSelfBase = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ChanceOnSelfFromPassive = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ChanceOnSelfFromAbility = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ChanceOnSelfFromEquipment = 0.0f;
	//Absolute Chance to apply this status effect. If effect is not stackable, the default of 1 is used. Higher than 1 means multiple stacks are applied at once.
	UPROPERTY()
	float ChanceOnSelfMax = 1.0f;

	void CalcChanceOnSelf();


	//The Enemy's DurationOnTarget gets reduced by this DurationOnSelf, when the owning character is the target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DurationOnSelf = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DurationOnSelfBase = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DurationOnSelfFromPassive = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DurationOnSelfFromAbility = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DurationOnSelfFromEquipment = 0.0f;
	
	void CalcDurationOnSelf(float IncomingDurationOnTarget);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageReductionOnSelf = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DamageReductionFromPassive = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DamageReductionFromAbility = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DamageReductionFromEquipment = 0.0f;
	
/**
						GENERAL ATTRIBUTES
						---------------------
				Generic descriptors. Impact other elements
*/


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsStackable = false;

	//is this status effect currently applied on the character?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive = false;

	UPROPERTY()
	float MaxStacks = 25.0f;



	//virtual void ApplyPassiveToOnTarget(float PassiveValue);
	


	FStatusEffectBase()
	{
	};
};
