// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TharsilProto/Interactions/InteractionInterface.h"
#include "TharsilProto/DataAssets/Items/DA_ItemBase.h"
#include "InteractablePickupItem.generated.h"



class ABaseCharacter;
class UInventoryItemBase;
class UWorld;
class ABaseCharacter;
class UDA_ItemBase;
class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS(Blueprintable)
class THARSILPROTO_API AInteractablePickupItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractablePickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// virtual class UWorld* GetWorld() const;

	// UPROPERTY(Transient)
	// UWorld* World;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	UStaticMeshComponent* StaticMeshItem;


	/**This is the name that will be shown in the inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	FText ItemDisplayName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	UStaticMesh* PickupMesh;	

	/**The amount of weight the item will use in the inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemWeight;

	/**The Inventory Element for this Item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Referenced Items")
	TSubclassOf<UInventoryItemBase> InventoryItem;

	UInventoryItemBase* ThisInventoryItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Referenced Items")
	UDA_ItemBase* BaseItem;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Interaction")
	void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Interaction")
	void StartFocus();
	virtual void StartFocus_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Interaction")
	void EndFocus();
	virtual void EndFocus_Implementation();
};
