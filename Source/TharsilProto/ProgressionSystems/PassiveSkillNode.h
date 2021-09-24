// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TharsilProto/ProgressionSystems/PassiveSkilltreeNodeTypes.h"
#include "PassiveSkillNode.generated.h"


class UPassiveSkillManagerComponent;
//enum EPassiveSkillEffect;


UCLASS(Blueprintable)
class THARSILPROTO_API UPassiveSkillNodeObject : public UObject
{
	GENERATED_BODY()
	
public:

	//---------------------------------------------------When a node becomes "purchased" (by purchasing an adjacent node), all directly connected nodes, i.e. the neighbours, get unlocked, i.e. "Reached".
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsSkillNodeReached;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsSkillNodePurchased;

	//---------------------------------------------------This is pulled from the Data Table to allow for position and the neighbour assignment. 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 UniqueNodeID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AssignmentValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsValueInPercent;

	//----------------------------------------------------Descriptions
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText NodeName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText NodeDescription;

	//----------------------------------------------------Skill Node Icons. Can be set on Initialization to allow for player affordance in widget.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTexture2D* IconLocked;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTexture2D* IconReached;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTexture2D* IconPurchased;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPassiveSkillEffect ThisSkillsEffect;

	TArray<UPassiveSkillNodeObject> NeighbourNodes;


};
