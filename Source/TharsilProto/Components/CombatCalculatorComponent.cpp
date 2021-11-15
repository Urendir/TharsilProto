// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCalculatorComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TharsilProto/Characters/BaseCharacter.h"


// Sets default values for this component's properties
UCombatCalculatorComponent::UCombatCalculatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OwningCharacter = Cast<ABaseCharacter>(GetOwner());
	CombatAttributes = CreateDefaultSubobject<UCombatAttributesSet>(TEXT("CombatAttributes"));
}


// Called when the game starts
void UCombatCalculatorComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UCombatCalculatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//ProcessStackingStatusEffectTick(bIsBleeding, BleedStacks, DeltaTime);
	//ProcessStackingStatusEffectTick(bIsOverheating, OverheatStacks, DeltaTime);
	//ProcessStackingStatusEffectTick(bIsBurning, BurnStacks, DeltaTime);
	//ProcessStackingStatusEffectTick(bIsChilled, ChillStacks, DeltaTime);
	//ProcessStackingStatusEffectTick(bIsPoisoned, PoisonStacks, DeltaTime);
	//ProcessStackingStatusEffectTick(bIsCorroding, CorrosionStacks, DeltaTime);

	//

}

void UCombatCalculatorComponent::RecalculateAllOutgoingDamage()
{

}



bool UCombatCalculatorComponent::OutCheckForCritical(float Passive, float ActiveAbility, float Agility)
{
	if (!CombatAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("CombatAttributes Not Loaded correctly!"));
	}

	float CritChanceBeforeAbility = 0.0f;
	CritChanceBeforeAbility = FMath::Min(((Agility * CombatAttributes->CritChancePerAgi) + Passive + CombatAttributes->CritChanceBase), CombatAttributes->AbsoluteMaxCriticalChanceBeforeAbility);
	float CritChance = CritChanceBeforeAbility + ActiveAbility;
	if (FMath::Rand() < CritChance)
	{
		bIsAttackCritical = true;
	}
	else bIsAttackCritical = false;

	return bIsAttackCritical;
}


float UCombatCalculatorComponent::ObtainLatestCritDamage(float PassiveCritDmg, int32 Strength, float EquipmentCritDmg, float AbilityCritDmg)
{
	float CritDamage = PassiveCritDmg + EquipmentCritDmg + AbilityCritDmg + ((float)Strength * CombatAttributes->CritDamagePerStr) + CombatAttributes->CritDamageBase;
	return CritDamage;
}





/// <summary>
/// Calculate all incoming damage and status effects by comparing the types in the attacking AttributesSet to the defender's AttributesSet
/// </summary>
/// <param name="DamagingCombatAttributes"> This is the attacking character's combat attributes - so their raw damage and change to deal status effects.</param>
/// <param name="DamageCauser"> The Attacking Character</param>
/// <param name="bIsCriticalHit"> True if the hit is dealing critical damage.</param>

void UCombatCalculatorComponent::InProcessDamage(UCombatAttributesSet* DamagingCombatAttributes, ABaseCharacter* DamageCauser, bool bIsCriticalHit)
{
	float SlashDmg = DamagingCombatAttributes->PhysicalDamageAndResistance.DamageSlash * (1 - CombatAttributes->PhysicalDamageAndResistance.DefenseSlash);
	float PierceDef = CombatAttributes->PhysicalDamageAndResistance.DefensePierce - DamagingCombatAttributes->GetArmorPenetrationOnPierce();
	float PierceDmg = DamagingCombatAttributes->PhysicalDamageAndResistance.DamagePierce * (1 - PierceDef);
	float CrushDef = CombatAttributes->PhysicalDamageAndResistance.DefenseCrush - DamagingCombatAttributes->GetArmorPenetrationOnCrush();
	float CrushDmg = DamagingCombatAttributes->PhysicalDamageAndResistance.DamageCrush * (1 - CrushDef);
	float FireDmg = 0.0f;
	float ColdDmg = 0.0f;
	float ToxicDmg = 0.0f;

	if (DamagingCombatAttributes->FireDamage.bIsActive)
	{
		FireDmg = DamagingCombatAttributes->FireDamage.DamageOnTarget * (1 - CombatAttributes->FireDamage.DamageReductionOnSelf);
	}

	if (DamagingCombatAttributes->ColdDamage.bIsActive)
	{
		ColdDmg = DamagingCombatAttributes->ColdDamage.DamageOnTarget * (1 - CombatAttributes->ColdDamage.DamageReductionOnSelf);
	}

	if (DamagingCombatAttributes->ToxicDamage.bIsActive)
	{
		ToxicDmg = DamagingCombatAttributes->ToxicDamage.DamageOnTarget * (1 - CombatAttributes->ToxicDamage.DamageReductionOnSelf);
	}

	float TotalDamage = SlashDmg + PierceDmg + CrushDmg + FireDmg + ColdDmg + ToxicDmg;
	
	if (bIsCriticalHit)
	{
		TotalDamage = TotalDamage * DamageCauser->CalculateLatestCritDamage();
		UE_LOG(LogTemp, Warning, TEXT("CRITICAL HIT!"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Damage was calculated as %f, applicable to %s"), TotalDamage, *OwningCharacter->GetName());
	InDetermineStatusEffects(DamagingCombatAttributes);

	//Apply Health Damage
}


void UCombatCalculatorComponent::InDetermineStatusEffects(UCombatAttributesSet* DamagingCombatAttributes)
{
	if (DamagingCombatAttributes->BleedDamage.bIsActive)
	{
		AttemptApplyStatusEffects(DamagingCombatAttributes->BleedDamage.PrimaryEffect, CombatAttributes->BleedDamage.PrimaryEffect, bIsBleeding, BleedStacks);
	}
	if (DamagingCombatAttributes->FireDamage.bIsActive)
	{
		AttemptApplyStatusEffects(DamagingCombatAttributes->FireDamage.PrimaryEffect, CombatAttributes->FireDamage.PrimaryEffect, bIsOverheating, OverheatStacks);
		AttemptApplyStatusEffects(DamagingCombatAttributes->FireDamage.SecondaryEffect, CombatAttributes->FireDamage.SecondaryEffect, bIsBurning, BurnStacks);
	}
	if (DamagingCombatAttributes->ColdDamage.bIsActive)
	{
		AttemptApplyStatusEffects(DamagingCombatAttributes->ColdDamage.PrimaryEffect, CombatAttributes->ColdDamage.PrimaryEffect, bIsChilled, ChillStacks);
		AttemptApplyStatusEffects(DamagingCombatAttributes->ColdDamage.SecondaryEffect, CombatAttributes->ColdDamage.SecondaryEffect, bIsFrozen);
	}
	if (DamagingCombatAttributes->ToxicDamage.bIsActive)
	{
		AttemptApplyStatusEffects(DamagingCombatAttributes->ToxicDamage.PrimaryEffect, CombatAttributes->ToxicDamage.PrimaryEffect, bIsPoisoned, PoisonStacks);
		AttemptApplyStatusEffects(DamagingCombatAttributes->ToxicDamage.SecondaryEffect, CombatAttributes->ToxicDamage.SecondaryEffect, bIsNecrosis);
	}
	if (DamagingCombatAttributes->CorrosionDamage.bIsActive)
	{
		AttemptApplyStatusEffects(DamagingCombatAttributes->CorrosionDamage.PrimaryEffect, CombatAttributes->CorrosionDamage.PrimaryEffect, bIsCorroding, CorrosionStacks);
	}
	AttemptApplyStatusEffects(DamagingCombatAttributes->Stun, CombatAttributes->Stun, bIsStunned);
	AttemptApplyStatusEffects(DamagingCombatAttributes->KnockDown, CombatAttributes->KnockDown, bIsKnockedDown);
	AttemptApplyStatusEffects(DamagingCombatAttributes->Cripple, CombatAttributes->Cripple, bIsCrippled);
	AttemptApplyStatusEffects(DamagingCombatAttributes->Blind, CombatAttributes->Blind, bIsBlinded);
}


void UCombatCalculatorComponent::AttemptApplyStatusEffects(FStatusEffect IncomingEffectData, FStatusEffect OwnEffectData, bool StatusBool)
{
	if (FMath::Rand() <= IncomingEffectData.ChanceOnTarget - OwnEffectData.EffectChanceMitigation)
	{
		float EffectDuration = IncomingEffectData.DurationOnTarget;
		OwnEffectData.DurationRemaining = EffectDuration - (EffectDuration * OwnEffectData.EffectDurationMitigation);

		OwnEffectData.DamageOnSelfTick = IncomingEffectData.DamageOnTargetTick;

		StatusBool = true;
	}
}

void UCombatCalculatorComponent::AttemptApplyStatusEffects(FStatusEffect IncomingEffectData, FStatusEffect OwnEffectData, bool StatusBool, TArray<FStatusEffect> StatusEffectArray)
{
	if (FMath::Rand() <= IncomingEffectData.ChanceOnTarget - OwnEffectData.EffectChanceMitigation)
	{
		float EffectDuration = IncomingEffectData.DurationOnTarget;
		OwnEffectData.DurationRemaining = EffectDuration - (EffectDuration * OwnEffectData.EffectDurationMitigation);
		OwnEffectData.DamageOnSelfTick = IncomingEffectData.DamageOnTargetTick;

		ApplyStackingStatusEffect(StatusEffectArray, OwnEffectData);
		StatusBool = true;
	}
}


void UCombatCalculatorComponent::ApplyStackingStatusEffect(TArray<FStatusEffect> StatusEffectArray, FStatusEffect StatusEffect)
{
	if (StatusEffect.MaximumStacks > StatusEffectArray.Num())
	{
		StatusEffectArray.Push(StatusEffect);
	}
}

void UCombatCalculatorComponent::ProcessStackingStatusEffectTick(bool StatusBool, TArray<FStatusEffect> StatusEffectArray, float DeltaTime)
{
	if (!StatusBool)
	{
		return;
	}

	if (StatusEffectArray.Num() < 1)
	{
		StatusBool = false;
	}

	for (size_t i = 0; i < StatusEffectArray.Num(); i++)
	{	
		if (StatusEffectArray[i].DurationRemaining > 0)
		{
			//process Damage with Effect.DamageOnTargetTick
			StatusEffectArray[i].DurationRemaining -= 1 * DeltaTime;
		}
		else
		{
			StatusEffectArray.RemoveAt(i, 1, true);
		}
	}

}

void UCombatCalculatorComponent::ProcessNonStackingStatusEffectTick(bool StatusBool, FStatusEffect StatusEffect, float DeltaTime)
{
	if (!StatusBool)
	{
		return;
	}

	if (StatusEffect.DurationRemaining <= 0.0f)
	{
		StatusBool = false;
	}
	else
	{
		StatusEffect.DurationRemaining -= 1 * DeltaTime;
	}
}





