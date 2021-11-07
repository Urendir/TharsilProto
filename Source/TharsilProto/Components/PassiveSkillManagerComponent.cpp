// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveSkillManagerComponent.h"
#include "TharsilProto/ProgressionSystems/PassiveSkillNode.h"
#include "TharsilProto/ProgressionSystems/PassiveSkilltreeNodeTypes.h"
#include "TharsilProto/Characters/BaseCharacterPlayable.h"

// Sets default values for this component's properties
UPassiveSkillManagerComponent::UPassiveSkillManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	//This makes sure that the data table is brought in from the data table location, if no table is provided in the blueprint.
	static ConstructorHelpers::FObjectFinder<UDataTable> PassiveSkillTreeTable(TEXT("DataTable'/Game/Stats/DT_PassiveSkillTree.DT_PassiveSkillTree'"));
	if (PassiveSkillTreeTable.Succeeded())
	{
		PassiveSkillNodesTable = PassiveSkillTreeTable.Object;
	}

	Owner = Cast<ABaseCharacterPlayable>(GetOwner());
}


// Called when the game starts
void UPassiveSkillManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	//initialize Array of Nodes here. These are called in the  tree and node widgets;
	if (PassiveSkillNodesTable)
	{
		TArray<FName> TableRowNames = PassiveSkillNodesTable->GetRowNames();
		int32 TableRowNameLength = TableRowNames.Num();
		SkillTree.Empty();

		for (size_t i = 0; i < TableRowNameLength; i++)
		{
			FName RowName = TableRowNames[i];
			static const FString ContextString(TEXT("Skill Node Table Context."));
			FPassiveSkillNode* SkillNode = PassiveSkillNodesTable->FindRow<FPassiveSkillNode>(RowName, ContextString, true);

			if (SkillNode)
			{
				SkillTree.Add(*SkillNode);				
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Skilltree has %i nodes."), SkillTree.Num());
}


//----------------------------------------------------------------------------------Operate on Skillpoints

void UPassiveSkillManagerComponent::IncreasePassiveSkillPoints()
{
	AvailableSkillpoints++;
}

int32 UPassiveSkillManagerComponent::GetCurrentPassiveSkillPoints()
{
	return AvailableSkillpoints;
}


//----------------------------------------------------------------------------------Node Modifications 

void UPassiveSkillManagerComponent::ReachSkillNode(FPassiveSkillNode SkillNode)
{
	SkillTree[SkillNode.UniqueNodeID].bIsSkillNodeReached = true;
}

void UPassiveSkillManagerComponent::PurchaseSkillNode(FPassiveSkillNode SkillNode)
{
	// for ease of reading: Checking 3 variables: you have points to spend, the node is reached and not yet purchased.
	if (AvailableSkillpoints > 0 && SkillTree[SkillNode.UniqueNodeID].bIsSkillNodeReached == true && SkillTree[SkillNode.UniqueNodeID].bIsSkillNodePurchased == false)
	{
		SkillTree[SkillNode.UniqueNodeID].bIsSkillNodePurchased = true;
		AvailableSkillpoints--;
	
		ProvideSkillNodeBonus(SkillNode);
	}
}


//Runs Through all neighbours of Node and sets them to reached. 
//This is called in BP atm, to also update the Node Widgets for the neighbours, using the array this function returns. 
TArray<int32> UPassiveSkillManagerComponent::ReachNeighbourNodes(FPassiveSkillNode SkillNode) 
{
	for (size_t i = 0; i < SkillNode.NeighbourNodes.Num(); i++)
	{
		SkillTree[SkillNode.NeighbourNodes[i]].bIsSkillNodeReached = true;
		//if (SkillTree[SkillNode.NeighbourNodes[i]].bIsSkillNodeReached == true)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Skill Node  %i set to reached."), SkillTree[SkillNode.NeighbourNodes[i]].UniqueNodeID);
		//}
	}
	
	return SkillTree[SkillNode.UniqueNodeID].NeighbourNodes;
}

void UPassiveSkillManagerComponent::ResetSkillNodeState(FPassiveSkillNode SkillNode)
{
	if (SkillNode.UniqueNodeID > 0)
	{
		SkillTree[SkillNode.UniqueNodeID].bIsSkillNodePurchased = false;
		IncreasePassiveSkillPoints();
	}
	if (SkillNode.bIsSkillNodeByDefaultReached == false)
	{
		SkillTree[SkillNode.UniqueNodeID].bIsSkillNodeReached = false;
	}
}

/// <summary>
/// 
/// -------------------------------------Switch Statement on Node Purchase-----------------------------------------------
/// 
/// This is being called when the Nodes get purchased. Massive switch to check the Enum. 
/// Functions are below. 
/// then the correct function gets called to give the effect for the node.
/// </summary>
/// <param name="SkillNode"></param>
void UPassiveSkillManagerComponent::ProvideSkillNodeBonus(FPassiveSkillNode SkillNode)
{
	if(SkillNode.AttributeType == EAffectedAttributeType::E_NoAffectedAttribute)
	{
		return;
	}

	switch (SkillNode.AttributeType)
	{
	case EAffectedAttributeType::E_EnergyAttribute:
		ModifyEnergyAttribute(SkillNode);
		break;
	case EAffectedAttributeType::E_MainAttribute:
		IncreaseMainAttributeValue(SkillNode.AssignmentValue, DetermineMainAttributeToIncrease(SkillNode));
		break;
	case EAffectedAttributeType::E_GeneralAttribute:
		break;
	case EAffectedAttributeType::E_PhysicalDamage:
		ModifyPhysicalAttributeValue(SkillNode);
		break;
	case EAffectedAttributeType::E_ElementalDamage:
		ModifyElementalDamageAttribute(SkillNode);
		break;
	case EAffectedAttributeType::E_StatusEffect:
	default:
		break;
	}





//DEPRECATED ITEM
	//TEnumAsByte<EPassiveSkillEffect> SkillEffect = SkillNode.ThisSkillsEffect;
	/*EPassiveSkillEffect SkillEffect = SkillNode.ThisSkillsEffect;
	
	switch (SkillEffect)
	{
	case EPassiveSkillEffect::E_AddAttributeAgility:
	
		AddAttributeAgility(SkillNode);
		break;
	case EPassiveSkillEffect::E_AddAttributeArmorPenetration:
		AddAttributeArmorPenetration(SkillNode);
		break;

	case EPassiveSkillEffect::E_AddAttributeCarryCapacity:
		AddAttributeCarryCapacity(SkillNode);
		break;

	case EPassiveSkillEffect::E_AddAttributeBreath:
		AddAttributeBreath(SkillNode);
		break;

	case EPassiveSkillEffect::E_AddAttributeConstitution:
		AddAttributeConstitution(SkillNode);
		break;

	case EPassiveSkillEffect::E_AddAttributeEndurance:
		AddAttributeEndurance(SkillNode);
		break;

	case EPassiveSkillEffect::E_AddAttributeHealth:
		AddAttributeHealth(SkillNode);
		break;

	case EPassiveSkillEffect::E_AddAttributeRegenHealth:
		AddAttributeHealthRegen(SkillNode);
		break;

	case EPassiveSkillEffect::E_AddAttributeStamina:
		AddAttributeStamina(SkillNode);
		break;

	case EPassiveSkillEffect::E_AddAttributeRegenStamina:
		AddAttributeStaminaRegen(SkillNode);
		break;

	case EPassiveSkillEffect::E_AddAttributeStrength:
		AddAttributeStrength(SkillNode);
		break;

	case EPassiveSkillEffect::E_AddResistanceFrost:
		AddDamageFrost(SkillNode);
		break;

	case EPassiveSkillEffect::E_ReduceCostAttack:

		break;

	case EPassiveSkillEffect::E_AddChanceBurn:

		break;

	case EPassiveSkillEffect::E_AddChanceChill:

		break;

	case EPassiveSkillEffect::E_AddAttributeSpirit:

		break;

	case EPassiveSkillEffect::E_AddAttributeArcaneEssence:

		break;

	case EPassiveSkillEffect::E_ReduceCostSprint:


		break;


	default:
		UE_LOG(LogTemp, Warning, TEXT("No Matching function for Passive Node found."));
		break;
	}*/


}

/// <summary>
/// ========================================FUNCTIONS IN SWITCH STATEMENT=======================================
/// These are called from within the switch statement, based on Node Type via Enum. 
/// </summary>

void UPassiveSkillManagerComponent::ModifyEnergyAttribute(FPassiveSkillNode SkillNode)
{
	switch (SkillNode.EnergyAttributeElement)
	{
	case EEnergyAttributeDescriptor::MaxValue:
		IncreaseEnergyAttributeMaxValue(SkillNode.AssignmentValue, DetermineEnergyAttributeToIncrease(SkillNode));
		break;
	case EEnergyAttributeDescriptor::RegenRate:
		IncreaseEnergyAttributeRegenRate(SkillNode.AssignmentValue, DetermineEnergyAttributeToIncrease(SkillNode));
		break;
	default:
		break;
	}
}

FEnergyAttribute UPassiveSkillManagerComponent::DetermineEnergyAttributeToIncrease(FPassiveSkillNode SkillNode)
{
	FEnergyAttribute AttributeToModify;
	switch (SkillNode.EnergyAttribute)
	{
	case EEnergyAttributeType::Breath:
		AttributeToModify = PassiveAttributes->Breath;
		break;
	case EEnergyAttributeType::Health:
		AttributeToModify = PassiveAttributes->Health;
		break;
	case EEnergyAttributeType::Mana:
		AttributeToModify = PassiveAttributes->Mana;
		break;
	case EEnergyAttributeType::Stamina:
		AttributeToModify = PassiveAttributes->Stamina;
		break;
	default:
		break;
	}
	return AttributeToModify;
}

void UPassiveSkillManagerComponent::IncreaseEnergyAttributeMaxValue(float AssignmentValue, FEnergyAttribute AttributeToIncrease)
{
	AttributeToIncrease.CurrentMaxValue += AssignmentValue;
}

void UPassiveSkillManagerComponent::IncreaseEnergyAttributeRegenRate(float AssignmentValue, FEnergyAttribute AttributeToIncrease)
{
	AttributeToIncrease.RegenerationRate += AssignmentValue;
}

FMainAttribute UPassiveSkillManagerComponent::DetermineMainAttributeToIncrease(FPassiveSkillNode SkillNode)
{
	FMainAttribute AttributeToIncrease;

	switch (SkillNode.MainAttribute)
	{
	case EMainAttributeType::Agility:
		AttributeToIncrease = PassiveAttributes->Agility;
		break;
	case EMainAttributeType::ArcaneEssence:
		AttributeToIncrease = PassiveAttributes->ArcaneEssence;
		break;
	case EMainAttributeType::Constitution:
		AttributeToIncrease = PassiveAttributes->Constitution;
		break;
	case EMainAttributeType::Endurance:
		AttributeToIncrease = PassiveAttributes->Endurance;
		break;
	case EMainAttributeType::Spirit:
		AttributeToIncrease = PassiveAttributes->Spirit;
		break;
	case EMainAttributeType::Strength:
		AttributeToIncrease = PassiveAttributes->Strength;
		break;
	default:
		break;
	}
	
	return AttributeToIncrease;
}

void UPassiveSkillManagerComponent::IncreaseMainAttributeValue(float AssignmentValue, FMainAttribute AttributeToUpdate)
{
	AttributeToUpdate.CurrentValue += AssignmentValue;
}

bool UPassiveSkillManagerComponent::AttributeTargetIsSelf(FPassiveSkillNode SkillNode)
{
	bool bIsSelfTarget;
	if (SkillNode.AffectedTarget == EAffectedTarget::E_Self)
	{
		bIsSelfTarget = true;
	}
	else 
	{
		bIsSelfTarget = false;
	}

	return bIsSelfTarget;
}

FPhysicalDamage UPassiveSkillManagerComponent::DeterminePhysicalCombatStyleToUpdate(FPassiveSkillNode SkillNode)
{
	FPhysicalDamage StyleToUpdate;
	switch (SkillNode.SpecificPhysicalDamage)
	{
	case EPhysicalDamageSpecific::OneHand:
		StyleToUpdate = PassiveAttributes->OneHandBonusDamage;
		break;
	case EPhysicalDamageSpecific::TwoHand:
		StyleToUpdate = PassiveAttributes->TwoHandBonusDamage;
		break;
	case EPhysicalDamageSpecific::Ranged:
		StyleToUpdate = PassiveAttributes->RangedBonusDamage;
		break;
	default:
		break;
	}
	
	return StyleToUpdate;
}

void UPassiveSkillManagerComponent::IncrementPhysicalDamage(FPassiveSkillNode SkillNode, FPhysicalDamage StyleToUpdate)
{
	switch (SkillNode.PhysicalDamageType)
	{
	case EPhysicalDamageType::ArmorPen:
		StyleToUpdate.ArmorPenetration += SkillNode.AssignmentValue;
		break;
	case EPhysicalDamageType::Crush:
		StyleToUpdate.DamageCrushModifier += SkillNode.AssignmentValue;
		break;
	case EPhysicalDamageType::Pierce:
		StyleToUpdate.DamagePierceModifier += SkillNode.AssignmentValue;
		break;
	case EPhysicalDamageType::Slash:
		StyleToUpdate.DamageSlashModifier += SkillNode.AssignmentValue;
		break;
	default:
		break;
	}
}

void UPassiveSkillManagerComponent::IncrementPhysicalResistance(FPassiveSkillNode SkillNode)
{
	switch (SkillNode.PhysicalDamageType)
	{
	case EPhysicalDamageType::ArmorPen:
		break;
	case EPhysicalDamageType::Crush:
		PassiveAttributes->PhysicalDamageAndResistance.DefenseCrushModifier += SkillNode.AssignmentValue;
		break;
	case EPhysicalDamageType::Pierce:
		PassiveAttributes->PhysicalDamageAndResistance.DefensePierceModifier += SkillNode.AssignmentValue;
		break;
	case EPhysicalDamageType::Slash:
		PassiveAttributes->PhysicalDamageAndResistance.DefenseSlashModifier += SkillNode.AssignmentValue;
		break;
	default:
		break;
	}
}

void UPassiveSkillManagerComponent::ModifyPhysicalAttributeValue(FPassiveSkillNode SkillNode)
{
	if (AttributeTargetIsSelf(SkillNode))
	{
		IncrementPhysicalResistance(SkillNode);
	}
	else
	{
		IncrementPhysicalDamage(SkillNode, DeterminePhysicalCombatStyleToUpdate(SkillNode));		
	}
}

void UPassiveSkillManagerComponent::ModifyElementalDamageAttribute(FPassiveSkillNode SkillNode)
{
	if (AttributeTargetIsSelf(SkillNode))
	{
		DecrementElementalDamageOnSelf(SkillNode, DetermineElementalDamageTypeToModify(SkillNode));
	}
	else
	{
		IncrementElementalDamageOnTarget(SkillNode, DetermineElementalDamageTypeToModify(SkillNode));
	}
}

FElementalDamage UPassiveSkillManagerComponent::DetermineElementalDamageTypeToModify(FPassiveSkillNode SkillNode)
{
	FElementalDamage ElementToModify;
	
	switch (SkillNode.ElementalDamageType)
	{
	case EElementalDamageType::E_Bleed:
		ElementToModify = PassiveAttributes->BleedDamage;
		break;
	case EElementalDamageType::E_Cold:
		ElementToModify = PassiveAttributes->ColdDamage;
		break;
	case EElementalDamageType::E_Corrosive:
		ElementToModify = PassiveAttributes->CorrosionDamage;
		break;
	case EElementalDamageType::E_Fire:
		ElementToModify = PassiveAttributes->FireDamage;
		break;
	case EElementalDamageType::E_Toxic:
		ElementToModify = PassiveAttributes->ToxicDamage;
		break;
	case EElementalDamageType::E_Blind:
		ElementToModify = PassiveAttributes->BlindDamage;
		break;
	case EElementalDamageType::E_Weak:
		ElementToModify = PassiveAttributes->WeakenDamage;
		break;
	default:
		break;
	}
	
	return ElementToModify;
}

void UPassiveSkillManagerComponent::IncrementElementalDamageOnTarget(FPassiveSkillNode SkillNode, FElementalDamage ElementToUpdate)
{
	ElementToUpdate.DamageOnTargetModifier += SkillNode.AssignmentValue;
}

void UPassiveSkillManagerComponent::DecrementElementalDamageOnSelf(FPassiveSkillNode SkillNode, FElementalDamage ElementToUpdate)
{
	ElementToUpdate.DamageReductionOnSelfModifier += SkillNode.AssignmentValue;
}

FStatusEffect UPassiveSkillManagerComponent::DetermineStatusEffectToModify(FPassiveSkillNode SkillNode)
{
	FStatusEffect AttributeToModify;
	
	switch (SkillNode.StatusEffectType)
	{
	case EStatusEffectType::E_Bleeding:
		AttributeToModify = PassiveAttributes->Bleeding;
		break;
	case EStatusEffectType::E_Burning:
		AttributeToModify = PassiveAttributes->Burning;
		break;
	case EStatusEffectType::E_Chilled:
		AttributeToModify = PassiveAttributes->Chilled;
		break;
	case EStatusEffectType::E_Corrosion:
		AttributeToModify = PassiveAttributes->Corrosion;
		break;
	case EStatusEffectType::E_Freezing:
		AttributeToModify = PassiveAttributes->Freezing;
		break;
	case EStatusEffectType::E_Necrosis:
		AttributeToModify = PassiveAttributes->Necrosis;
		break;
	case EStatusEffectType::E_Overheating:
		AttributeToModify = PassiveAttributes->Overheating;
		break;
	case EStatusEffectType::E_Poison:
		AttributeToModify = PassiveAttributes->Poison;
		break;
	case EStatusEffectType::E_Blinding:
		AttributeToModify = PassiveAttributes->Blinding;
		break;
	case EStatusEffectType::E_Weakening:
		AttributeToModify = PassiveAttributes->Weakening;
		break;
	case EStatusEffectType::E_Stun:
		AttributeToModify = PassiveAttributes->Stun;
		break;
	case EStatusEffectType::E_Knockdown:
		AttributeToModify = PassiveAttributes->KnockDown;
		break;
	case EStatusEffectType::E_Cripple:
		AttributeToModify = PassiveAttributes->Cripple;
		break;
		//More to be added

	default:
		break;
	}

	return AttributeToModify;
}

void UPassiveSkillManagerComponent::ModifyStatusEffectBasedOnSelection(FPassiveSkillNode SkillNode)
{
	switch (SkillNode.AffectedSatusEffectDescriptor)
	{
	case EAffectedDescriptor::E_Chance:
		if (AttributeTargetIsSelf(SkillNode))
		{
			DecrementStatusChanceOnSelf(SkillNode.AssignmentValue, DetermineStatusEffectToModify(SkillNode));
		}
		else
		{
			IncrementStatusChanceOnTarget(SkillNode.AssignmentValue, DetermineStatusEffectToModify(SkillNode));
		}
		break;
	case EAffectedDescriptor::E_DamageOnTick:
		if (AttributeTargetIsSelf(SkillNode))
		{
			DecrementStatusDmgTakenOnTick(SkillNode.AssignmentValue, DetermineStatusEffectToModify(SkillNode));
		}
		else
		{
			IncrementStatusDmgOnTick(SkillNode.AssignmentValue, DetermineStatusEffectToModify(SkillNode));
		}
		break;
	case EAffectedDescriptor::E_Duration:
		if (AttributeTargetIsSelf(SkillNode))
		{
			DecrementStatusDurationOnSelf(SkillNode.AssignmentValue, DetermineStatusEffectToModify(SkillNode));
		}
		else
		{
			IncrementStatusDurationOnTarget(SkillNode.AssignmentValue, DetermineStatusEffectToModify(SkillNode));
		}
		break;

	default:
		break;
	}
}

void UPassiveSkillManagerComponent::IncrementStatusDmgOnTick(float AssignmentValue, FStatusEffect StatusEffectToUpdate)
{
	StatusEffectToUpdate.DamageOnTargetTick += AssignmentValue;
}

void UPassiveSkillManagerComponent::DecrementStatusDmgTakenOnTick(float AssignmentValue, FStatusEffect StatusEffectToUpdate)
{
	StatusEffectToUpdate.DamageOnSelfTick += AssignmentValue;
}

void UPassiveSkillManagerComponent::IncrementStatusChanceOnTarget(float AssignmentValue, FStatusEffect StatusEffectToUpdate)
{
	StatusEffectToUpdate.ChanceOnTarget += AssignmentValue;
}

void UPassiveSkillManagerComponent::DecrementStatusChanceOnSelf(float AssignmentValue, FStatusEffect StatusEffectToUpdate)
{
	StatusEffectToUpdate.EffectChanceMitigation += AssignmentValue;
}

void UPassiveSkillManagerComponent::IncrementStatusDurationOnTarget(float AssignmentValue, FStatusEffect StatusEffectToUpdate)
{
	StatusEffectToUpdate.DurationOnTarget += AssignmentValue;
}

void UPassiveSkillManagerComponent::DecrementStatusDurationOnSelf(float AssignmentValue, FStatusEffect StatusEffectToUpdate)
{
	StatusEffectToUpdate.EffectDurationMitigation += AssignmentValue;
}




























/// <summary>
/// ========================================OBSOLETE=======================================
/// These are called from within the switch statement, based on Node Type via Enum. 
/// </summary>
/// <param name="SkillNode"></param>
//void UPassiveSkillManagerComponent::AddAttributeAgility(FPassiveSkillNode SkillNode)
//{
//	PassiveSkillAgility += SkillNode.AssignmentValue;
//	UE_LOG(LogTemp, Warning, TEXT("Passive Agility increased to %i."), PassiveSkillAgility);
//	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
//}
//
//void UPassiveSkillManagerComponent::AddAttributeArcaneEssence(FPassiveSkillNode SkillNode)
//{
//	PassiveSkillArcaneEssence += SkillNode.AssignmentValue;
//	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
//}
//
//void UPassiveSkillManagerComponent::AddAttributeArmorPenetration(FPassiveSkillNode SkillNode)
//{
//	ArmorPenetrationPassive += SkillNode.AssignmentValue;
//	UE_LOG(LogTemp, Warning, TEXT("Passive Armor Penetration increased to %i."), ArmorPenetrationPassive);
//}
//
//void UPassiveSkillManagerComponent::AddAttributeBreath(FPassiveSkillNode SkillNode)
//{
//	//ADD BREATH TO THE ENERGY COMPONENT!
//}
//
//void UPassiveSkillManagerComponent::AddAttributeCarryCapacity(FPassiveSkillNode SkillNode)
//{
//	CarryCapacityPassive += 5; //SkillNode.AssignmentValue;
//	UE_LOG(LogTemp, Warning, TEXT("Passive CarryCapacity increased to %f."), CarryCapacityPassive);
//}
//
//void UPassiveSkillManagerComponent::AddAttributeConstitution(FPassiveSkillNode SkillNode)
//{
//	PassiveSkillConstitution += SkillNode.AssignmentValue;
//	UE_LOG(LogTemp, Warning, TEXT("Passive Constitution increased to %i."), PassiveSkillConstitution);
//	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
//}
//
//void UPassiveSkillManagerComponent::AddAttributeEndurance(FPassiveSkillNode SkillNode)
//{
//	PassiveSkillEndurance += SkillNode.AssignmentValue;
//	UE_LOG(LogTemp, Warning, TEXT("Passive Endurance increased to %i."), PassiveSkillEndurance);
//	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
//}
//
//void UPassiveSkillManagerComponent::AddAttributeHealth(FPassiveSkillNode SkillNode)
//{
//	HealthPointsPassive += SkillNode.AssignmentValue;
//	UE_LOG(LogTemp, Warning, TEXT("Passive HP increased to %f."), HealthPointsPassive);
//	Owner->UpdateSecondaryAttributes();
//}
//
//void UPassiveSkillManagerComponent::AddAttributeHealthRegen(FPassiveSkillNode SkillNode)
//{
//	HealthRegenPassive += SkillNode.AssignmentValue;
//	UE_LOG(LogTemp, Warning, TEXT("Passive Health Regen increased to %f."), HealthRegenPassive);
//	Owner->UpdateSecondaryAttributes();
//}
//
//void UPassiveSkillManagerComponent::AddAttributeSpirit(FPassiveSkillNode SkillNode)
//{
//	PassiveSkillSpirit += SkillNode.AssignmentValue;
//	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
//}
//
//void UPassiveSkillManagerComponent::AddAttributeStamina(FPassiveSkillNode SkillNode)
//{
//	StaminaPointsPassive += SkillNode.AssignmentValue;
//	UE_LOG(LogTemp, Warning, TEXT("Passive Stamina increased to %f."), StaminaPointsPassive);
//	Owner->UpdateSecondaryAttributes();
//}
//
//void UPassiveSkillManagerComponent::AddAttributeStaminaRegen(FPassiveSkillNode SkillNode)
//{
//	StaminaRegenPassive += SkillNode.AssignmentValue;
//	UE_LOG(LogTemp, Warning, TEXT("Passive Stamina Regen increased to %f."), StaminaRegenPassive);
//	Owner->UpdateSecondaryAttributes();
//}
//
//void UPassiveSkillManagerComponent::AddAttributeStrength(FPassiveSkillNode SkillNode)
//{
//	PassiveSkillStrength += SkillNode.AssignmentValue;
//	UE_LOG(LogTemp, Warning, TEXT("Passive Strength increased to %i."), PassiveSkillStrength);
//	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
//}
//
//void UPassiveSkillManagerComponent::AddDamageCritical(FPassiveSkillNode SkillNode)
//{
//	CriticalDamagePassive += SkillNode.AssignmentValue;
//}
//
//void UPassiveSkillManagerComponent::AddSpeedSprint(FPassiveSkillNode SkillNode)
//{
//	SprintCostReductionPassive += SkillNode.AssignmentValue;
//	Owner->CalculateSprintSpeed(); // not part of the overall Secondary Attributes
//}
//
//void UPassiveSkillManagerComponent::AddDamageFrost(FPassiveSkillNode SkillNode)
//{
//
//}










//// Called every frame
//void UPassiveSkillManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}
