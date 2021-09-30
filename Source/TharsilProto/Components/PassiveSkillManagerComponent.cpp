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
	//TEnumAsByte<EPassiveSkillEffect> SkillEffect = SkillNode.ThisSkillsEffect;
	EPassiveSkillEffect SkillEffect = SkillNode.ThisSkillsEffect;
	
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
	}


}


/// <summary>
/// ========================================FUNCTIONS IN SWITCH STATEMENT=======================================
/// These are called from within the switch statement, based on Node Type via Enum. 
/// </summary>
/// <param name="SkillNode"></param>
void UPassiveSkillManagerComponent::AddAttributeAgility(FPassiveSkillNode SkillNode)
{
	PassiveSkillAgility += SkillNode.AssignmentValue;
	UE_LOG(LogTemp, Warning, TEXT("Passive Agility increased to %i."), PassiveSkillAgility);
	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
}

void UPassiveSkillManagerComponent::AddAttributeArcaneEssence(FPassiveSkillNode SkillNode)
{
	PassiveSkillArcaneEssence += SkillNode.AssignmentValue;
	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
}

void UPassiveSkillManagerComponent::AddAttributeArmorPenetration(FPassiveSkillNode SkillNode)
{
	ArmorPenetrationPassive += SkillNode.AssignmentValue;
	UE_LOG(LogTemp, Warning, TEXT("Passive Armor Penetration increased to %i."), ArmorPenetrationPassive);
}

void UPassiveSkillManagerComponent::AddAttributeBreath(FPassiveSkillNode SkillNode)
{
	//ADD BREATH TO THE ENERGY COMPONENT!
}

void UPassiveSkillManagerComponent::AddAttributeCarryCapacity(FPassiveSkillNode SkillNode)
{
	CarryCapacityPassive += 5; //SkillNode.AssignmentValue;
	UE_LOG(LogTemp, Warning, TEXT("Passive CarryCapacity increased to %f."), CarryCapacityPassive);
}

void UPassiveSkillManagerComponent::AddAttributeConstitution(FPassiveSkillNode SkillNode)
{
	PassiveSkillConstitution += SkillNode.AssignmentValue;
	UE_LOG(LogTemp, Warning, TEXT("Passive Constitution increased to %i."), PassiveSkillConstitution);
	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
}

void UPassiveSkillManagerComponent::AddAttributeEndurance(FPassiveSkillNode SkillNode)
{
	PassiveSkillEndurance += SkillNode.AssignmentValue;
	UE_LOG(LogTemp, Warning, TEXT("Passive Endurance increased to %i."), PassiveSkillEndurance);
	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
}

void UPassiveSkillManagerComponent::AddAttributeHealth(FPassiveSkillNode SkillNode)
{
	HealthPointsPassive += SkillNode.AssignmentValue;
	UE_LOG(LogTemp, Warning, TEXT("Passive HP increased to %f."), HealthPointsPassive);
	Owner->UpdateSecondaryAttributes();
}

void UPassiveSkillManagerComponent::AddAttributeHealthRegen(FPassiveSkillNode SkillNode)
{
	HealthRegenPassive += SkillNode.AssignmentValue;
	UE_LOG(LogTemp, Warning, TEXT("Passive Health Regen increased to %f."), HealthRegenPassive);
	Owner->UpdateSecondaryAttributes();
}

void UPassiveSkillManagerComponent::AddAttributeSpirit(FPassiveSkillNode SkillNode)
{
	PassiveSkillSpirit += SkillNode.AssignmentValue;
	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
}

void UPassiveSkillManagerComponent::AddAttributeStamina(FPassiveSkillNode SkillNode)
{
	StaminaPointsPassive += SkillNode.AssignmentValue;
	UE_LOG(LogTemp, Warning, TEXT("Passive Stamina increased to %f."), StaminaPointsPassive);
	Owner->UpdateSecondaryAttributes();
}

void UPassiveSkillManagerComponent::AddAttributeStaminaRegen(FPassiveSkillNode SkillNode)
{
	StaminaRegenPassive += SkillNode.AssignmentValue;
	UE_LOG(LogTemp, Warning, TEXT("Passive Stamina Regen increased to %f."), StaminaRegenPassive);
	Owner->UpdateSecondaryAttributes();
}

void UPassiveSkillManagerComponent::AddAttributeStrength(FPassiveSkillNode SkillNode)
{
	PassiveSkillStrength += SkillNode.AssignmentValue;
	UE_LOG(LogTemp, Warning, TEXT("Passive Strength increased to %i."), PassiveSkillStrength);
	Owner->AddPassiveBonusesToPrimaryAttributes(PassiveSkillAgility, PassiveSkillArcaneEssence, PassiveSkillConstitution, PassiveSkillEndurance, PassiveSkillSpirit, PassiveSkillStrength);
}

void UPassiveSkillManagerComponent::AddDamageCritical(FPassiveSkillNode SkillNode)
{
	CriticalDamagePassive += SkillNode.AssignmentValue;
}

void UPassiveSkillManagerComponent::AddSpeedSprint(FPassiveSkillNode SkillNode)
{
	SprintCostReductionPassive += SkillNode.AssignmentValue;
	Owner->CalculateSprintSpeed(); // not part of the overall Secondary Attributes
}

void UPassiveSkillManagerComponent::AddDamageFrost(FPassiveSkillNode SkillNode)
{

}










//// Called every frame
//void UPassiveSkillManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}
