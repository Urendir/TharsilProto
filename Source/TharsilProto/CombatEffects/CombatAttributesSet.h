// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "TharsilProto/ProgressionSystems/GeneralAttributeSet.h"
#include "Misc/App.h"
#include "UObject/NoExportTypes.h"
#include "CombatAttributesSet.generated.h"

/**
 * 
 */



UCLASS(Blueprintable)
class THARSILPROTO_API UCombatAttributesSet : public UObject
{
	GENERATED_BODY()
	
public: 
	UCombatAttributesSet();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FPhysicalDamage PhysicalDamage;

	// Status Effects that Damage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FElementalDamage BleedDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FElementalDamage FireDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FElementalDamage ColdDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FElementalDamage ToxicDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Values")
	FElementalDamage CorrosionDamage;

	//Status effect elements of Damage Types.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Overheating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Burning;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Chilled;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Freezing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Poison;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Necrosis;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Bleeding;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	FStatusEffect Corrosion;

	//Special Status Effects that only apply on certain attacks.
	//these can be seen as hybrids - not pure status effect, not damage type.

	/*Can be triggered by certain attack types only*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special Status Effects")
	FElementalDamage BlindingDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Special Status Effects")
	FStatusEffect Blind;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special Status Effects")
	FElementalDamage WeakeningDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Special Status Effects")
	FStatusEffect Weakened;





	//Pure Chance Effects, no damage but cause other effects. Can always be triggered by regular attacks with a low chance.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pure Status Effects")
	FStatusEffect Stun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pure Status Effects")
	FStatusEffect KnockDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pure Status Effects")
	FStatusEffect Cripple;




	//-------------------------------Critical Modifiers-----------------------------------------------

	/*The multiplier for damage on a critical hit. 1.5 crit damage means that you deal 150% of the total damage calculation to the target*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CritDamageBase = 1.475f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CritDamagePerStr = 0.005f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CritChancePerAgi = 0.005f;

	/*The basic Critical Chance, before additions from the active ability;.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CritChanceBase = 0.025f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AbsoluteMaxCriticalChanceBeforeAbility = 0.85f;

	UFUNCTION()
	void AddEntireCombatValueSet(UCombatAttributesSet* ValuesToAdd);
	UFUNCTION()
	void AddPhysicalDamageSetValues(FPhysicalDamage ValuesToAdd, FPhysicalDamage ParentValue);
	UFUNCTION()
	void AddElementalDamageSetValues(FElementalDamage ValuesToAdd, FElementalDamage ParentValue);
	UFUNCTION()
	void AddStatusEffectValues(FStatusEffect ValuesToAdd, FStatusEffect ParentValue);

	UFUNCTION()
	float GetArmorPenetrationOnPierce();
	UFUNCTION()
	float GetArmorPenetrationOnCrush();
};
