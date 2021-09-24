// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveSkillManagerComponent.h"
#include "TharsilProto/ProgressionSystems/PassiveSkillNode.h"
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

	//initialize Array of Nodes;

	//int32 UniqueID = 2;

	//if (PassiveSkillNodesTable)
	//{
	//	TableRowNames = PassiveSkillNodesTable->GetRowNames();

	//	for each (FName RowName in TableRowNames)
	//	{
	//		FPassiveSkillNode* SkillNode; 
	//		SkillNode->NodeName = PassiveSkillNodesTable->byname;
	//		
	//	}
	//	
	//	static const FString ContextString(TEXT("Skill Node Table Context."));
	//	FPassiveSkillNode* SkillNode =  PassiveSkillNodesTable->FindRow<FPassiveSkillNode>(FName(TEXT("%i"),UniqueID), ContextString, true);

	//}

}













//// Called every frame
//void UPassiveSkillManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

