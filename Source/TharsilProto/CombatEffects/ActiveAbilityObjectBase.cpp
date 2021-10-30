// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveAbilityObjectBase.h"
#include "TharsilProto/Characters/BaseCharacterPlayable.h"
#include "TharsilProto/DataAssets/Abilities/DA_ActiveAbilityBase.h"


UActiveAbilityObjectBase::UActiveAbilityObjectBase()
{

}

UDA_ActiveAbilityBase* UActiveAbilityObjectBase::GetUsableAbilityData()
{
	if (ActiveAbilityData)
	{
		UDA_ActiveAbilityBase* AbilityData = Cast<UDA_ActiveAbilityBase>(ActiveAbilityData);
		return AbilityData;
	}
	return nullptr;
}
