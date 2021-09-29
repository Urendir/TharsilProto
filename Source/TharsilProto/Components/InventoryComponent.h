// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

class UInventoryItemBase;
class ABaseCharacterPlayable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CarryWeightTotalCapacity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CarryWeightCurrent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CarryWeightBaseCapacity = 30.0f; 	//This One is used in the calculation for the Carry Cap as a basic unit. this is the minimum capacity. 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CarryWeightPerLevel = 0.5f;		//This is used to calculate the Carry Cap when linked with the Level of the Character.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Modifiers", meta = (AllowPrivateAccess = "true"))
	float PerStrengthCarryCapacity = 1.3f;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 InventorySlotsTotal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 InventorySlotsUsed;

	ABaseCharacterPlayable* Owner;

//--------------------INVENTORY ARRAY -----------------------

	UInventoryItemBase* ThisInventoryItem; //This is used to ensure the proper usage of "Item" in the Add and Remove functions.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UInventoryItemBase*> InventoryItems;

//------------------------DELEGATES---------------------------------		
	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;	


//-----------------INVENTORY MANAGEMENT FUNCTIONS-------------------------
	UFUNCTION(BlueprintCallable)
	bool AddItemToInventory(TSubclassOf<UInventoryItemBase> Item);
	UFUNCTION(BlueprintCallable)
	bool MoveItemInInventory(TSubclassOf<UInventoryItemBase> ItemToMove, int32 FromLocation, int32 ToLocation);
	UFUNCTION(BlueprintCallable)
	bool RemoveFromInventory(TSubclassOf<UInventoryItemBase> Item);

//------------------ Weight Calculations--------------------------------------
	UFUNCTION(BlueprintCallable)
	float CalculateCurrentEncumberanceRate();
	UFUNCTION(BlueprintCallable)
	void CalculateCurrentCarryCapacity(int32 Strength, int32 Level);
	UFUNCTION(BlueprintCallable)
	void UpdateCarryWeightTotalCapacity(float NewValue);

};
