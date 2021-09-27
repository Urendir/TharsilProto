// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TharsilProto/Interactions/DamageTypeStruct.h"
#include "TharsilProto/ProgressionSystems/PassiveSkilltreeNodeTypes.h"
#include "PassiveSkillManagerComponent.generated.h"

USTRUCT(BlueprintType)
struct FPassiveSkillNode : public FTableRowBase
{
	GENERATED_BODY()
	

	//---------------------------------------------------This is pulled from the Data Table to allow for position and the neighbour assignment. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UniqueNodeID;

	//----------------------------------------------------Descriptions
	
	//the Name of the Node.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NodeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NodeDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AssignmentValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsValueInPercent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsSkillNodeByDefaultReached;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSkillNodeReached;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSkillNodePurchased;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPassiveSkillEffect ThisSkillsEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> NeighbourNodes;

	//----------------------------------------------------Skill Node Icons. Can be set on Initialization to allow for player affordance in widget.
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconLocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconReached;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconPurchased;
};



class UPassiveSkillNode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UPassiveSkillManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPassiveSkillManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	int32 AvailableSkillpoints = 10;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FPassiveSkillNode> SkillTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* PassiveSkillNodesTable;

	EPassiveSkillEffect PassiveEffects;

	FDamageTypeBreakdown OffensivePassiveStats;

	FDamageResistanceBreakdown DefensivePassiveStats;

	//Called on LevelUp or Skilltree Reset.
	UFUNCTION(BlueprintCallable)
	void IncreasePassiveSkillPoints();

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentPassiveSkillPoints();

	UFUNCTION(BlueprintCallable)
	void ReachSkillNode(FPassiveSkillNode SkillNode);

	UFUNCTION(BlueprintCallable)
	void PurchaseSkillNode(FPassiveSkillNode SkillNode);

	UFUNCTION(BlueprintCallable)
	TArray<int32> ReachNeighbourNodes(FPassiveSkillNode SkillNode);

	UFUNCTION(BlueprintCallable)
	void ResetSkillNodeState(FPassiveSkillNode SkillNode);
	
};