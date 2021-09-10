// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

class UDA_ItemBase;
class ABaseCharacter;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 InventorySlotsTotal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 InventorySlotsUsed;

	ABaseCharacter* Owner;

//--------------------INVENTORY ARRAY -----------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UDA_ItemBase*> InventoryItems;

//-----------------INVENTORY MANAGEMENT FUNCTIONS-------------------------
	bool AddItemToInventory(UDA_ItemBase* Item);
	bool RemoveFromInventory(UDA_ItemBase* Item);

	void UpdateCarryCapacity(float NewValue);


//------------------------DELEGATES---------------------------------		
	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;	

};
