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
	
	//LAUNCH THE FUNCTION TO DETERMINE THE SKILLPOINT ACTION
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


void UPassiveSkillManagerComponent::ProvideSkillNodeBonus(FPassiveSkillNode SkillNode)
{
	//TEnumAsByte<EPassiveSkillEffect> SkillEffect = SkillNode.ThisSkillsEffect;
	EPassiveSkillEffect SkillEffect = SkillNode.ThisSkillsEffect;
	
	switch (SkillEffect)
	{
	case EPassiveSkillEffect::E_AddAttributeAgility:
	
		AddAttributeAgility(SkillNode);
		break;
	case EPassiveSkillEffect::E_AddAttributeStrength:
		AddAttributeStrength(SkillNode);

	default:
		UE_LOG(LogTemp, Warning, TEXT("No Matching function for Passive Node found."));
		break;
	}


}











//// Called every frame
//void UPassiveSkillManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}


void UPassiveSkillManagerComponent::AddAttributeAgility(FPassiveSkillNode SkillNode)
{
}

void UPassiveSkillManagerComponent::AddAttributeBreath(FPassiveSkillNode SkillNode)
{
}

void UPassiveSkillManagerComponent::AddAttributeCarryCapacity(FPassiveSkillNode SkillNode)
{
}

void UPassiveSkillManagerComponent::AddAttributeConstitution(FPassiveSkillNode SkillNode)
{
}

void UPassiveSkillManagerComponent::AddAttributeEndurance(FPassiveSkillNode SkillNode)
{
}

void UPassiveSkillManagerComponent::AddAttributeHealth(FPassiveSkillNode SkillNode)
{
}

void UPassiveSkillManagerComponent::AddAttributeHealthRegen(FPassiveSkillNode SkillNode)
{
}

void UPassiveSkillManagerComponent::AddAttributeStamina(FPassiveSkillNode SkillNode)
{
}

void UPassiveSkillManagerComponent::AddAttributeStaminaRegen(FPassiveSkillNode SkillNode)
{
}

void UPassiveSkillManagerComponent::AddAttributeStrength(FPassiveSkillNode SkillNode)
{
}
