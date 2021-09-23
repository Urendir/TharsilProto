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

	// ...
}


// Called when the game starts
void UPassiveSkillManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	//initialize Array of Nodes;
	
}













//// Called every frame
//void UPassiveSkillManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

