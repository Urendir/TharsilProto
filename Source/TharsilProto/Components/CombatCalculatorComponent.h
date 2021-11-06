// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Array.h"
#include "TharsilProto/CombatEffects/CombatAttributesSet.h"
#include "CombatCalculatorComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UCombatCalculatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatCalculatorComponent();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseCharacter* OwningCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCombatAttributesSet* CombatAttributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FStatusEffect> BleedStacks;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FStatusEffect> OverheatStacks;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FStatusEffect> BurnStacks;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FStatusEffect> ChillStacks;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FStatusEffect> PoisonStacks;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FStatusEffect> CorrosionStacks;



/// <summary>
/// NEGATIVE Status Effect Flags and timer checks. These are set when the Owning Character has the respective status affecting them in a negative way.
/// </summary>
	UPROPERTY(BlueprintReadWrite)
	bool bIsBleeding;
	UPROPERTY(BlueprintReadWrite)
	bool bIsStunned;
	UPROPERTY(BlueprintReadWrite)
	bool bIsKnockedDown;
	UPROPERTY(BlueprintReadWrite)
	bool bIsBlinded;
	UPROPERTY(BlueprintReadWrite)
	bool bIsCrippled;
	UPROPERTY(BlueprintReadWrite)
	bool bIsWeakened;
	UPROPERTY(BlueprintReadWrite)
	bool bIsOverheating;
	UPROPERTY(BlueprintReadWrite)
	bool bIsBurning;
	UPROPERTY(BlueprintReadWrite)
	bool bIsChilled;
	UPROPERTY(BlueprintReadWrite)
	bool bIsFrozen;
	UPROPERTY(BlueprintReadWrite)
	bool bIsPoisoned;
	UPROPERTY(BlueprintReadWrite)
	bool bIsNecrosis;
	UPROPERTY(BlueprintReadWrite)
	bool bIsCorroding;

/// <summary>
/// POSITIVE Status Effect Flags. These are set when the Owning Character has the respective status affecting them in a positive way.
/// </summary>

	UPROPERTY(BlueprintReadWrite)
	bool bIsRested;
	UPROPERTY(BlueprintReadWrite)
	bool bIsSatiated;
	UPROPERTY(BlueprintReadWrite)
	bool bIsEmboldened;
	UPROPERTY(BlueprintReadWrite)
	bool bIsEmpowered;
	UPROPERTY(BlueprintReadWrite)
	bool bIsGuarded;
	UPROPERTY(BlueprintReadWrite)
	bool bIsSolidified;
	UPROPERTY(BlueprintReadWrite)
	bool bIsAttackCritical;

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


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*Gets all relevant numbers from other components via owner.*/
	UFUNCTION()
	void RecalculateAllOutgoingDamage();

	/*Called from Character*/
	UFUNCTION()
	bool OutCheckForCritical(float Passive, float ActiveAbility, float Agility);
	/*Called from Character*/
	UFUNCTION()
	float ObtainLatestCritDamage(float PassiveCritDmg, int32 Strength, float EquipmentCritDmg, float AbilityCritDmg);

	
	UFUNCTION()
	void InProcessDamage(UCombatAttributesSet* DamagingCombatAttributes, ABaseCharacter* DamageCauser, bool bIsCriticalHit);
	UFUNCTION()
	void InDetermineStatusEffects(UCombatAttributesSet* DamagingCombatAttributes);


	/*This checks chance for status effect vs defenses and applies effects as needed. Calls the Apply Functions.*/
	void AttemptApplyStatusEffects(FStatusEffect IncomingEffectData, FStatusEffect OwnEffectData, bool StatusBool);
	void AttemptApplyStatusEffects(FStatusEffect IncomingEffectData, FStatusEffect OwnEffectData, bool StatusBool, TArray<FStatusEffect> StatusEffectArray);

	/*If the applied status effect is stacking, this effect gets applied*/
	UFUNCTION()
	void ApplyStackingStatusEffect(TArray<FStatusEffect> StatusEffectArray, FStatusEffect StatusEffect);
		
private:
	UFUNCTION()
	void ProcessStackingStatusEffectTick(bool StatusBool, TArray<FStatusEffect> StatusEffectArray, float DeltaTime);
	UFUNCTION()
	void ProcessNonStackingStatusEffectTick(bool StatusBool, FStatusEffect StatusEffect, float DeltaTime);
};
