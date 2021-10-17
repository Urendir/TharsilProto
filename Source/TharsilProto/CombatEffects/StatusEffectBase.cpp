// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectBase.h"
#include "Math/UnrealMathUtility.h"

void FStatusEffectBase::CalcChanceOnTarget()
{
	float ChanceOT = ChanceOnTargetBase + ChanceOnTargetFromAbility + ChanceOnTargetFromEquipment + ChanceOnTargetFromPassive;
	if (bIsStackable)
	{
		ChanceOnTarget = ChanceOT;
	}
	else 
	{
		ChanceOnTarget = FMath::Min(ChanceOT, ChanceOnTargetMax);
	}
}

void FStatusEffectBase::CalcDurationOnTarget()
{
	float DurationOT = DurationOnTargetBase + DurationOnTargetFromAbility + DurationOnTargetFromEquipment + DurationOnTargetFromPassive;
	DurationOnSelf = FMath::Min(DurationOT, DurationOnTargetMax);
}

void FStatusEffectBase::CalcDamageOnTarget()
{
	DamageOnTarget = DamageOnTargetBase + DamageOnTargetFromAbility + DamageOnTargetFromEquipment + DamageOnTargetFromPassive;
}

void FStatusEffectBase::CalcChanceOnSelf()
{
	float ChanceOS = ChanceOnSelfBase + ChanceOnSelfFromPassive + ChanceOnSelfFromAbility + ChanceOnSelfFromEquipment;
	
	if (bIsStackable)
	{
		ChanceOnSelf = ChanceOS;
	}
	else 
	{
		ChanceOnSelf = FMath::Min(ChanceOS, ChanceOnSelfMax);
	}
}

void FStatusEffectBase::CalcDurationOnSelf()
{
	DurationOnSelf = DurationOnSelfBase + DurationOnSelfFromAbility + DurationOnSelfFromEquipment + DurationOnSelfFromPassive;

}



void FStatusEffectBase::ApplyPassiveToOnSelf(float PassiveValue)
{


}
