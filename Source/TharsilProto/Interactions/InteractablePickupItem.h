// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TharsilProto/Interactions/InteractionInterface.h"
#include "TharsilProto/DataAssets/Items/DA_ItemBase.h"
#include "InteractablePickupItem.generated.h"


class UInventoryItemBase;
class UWorld;
class ABaseCharacterPlayable;
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

	/**The Inventory Element for this Item*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Referenced Items")
	TSubclassOf<UInventoryItemBase> InventoryItem;

	UInventoryItemBase* ThisInventoryItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Referenced Items")
	UDA_ItemBase* BaseItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	UStaticMeshComponent* StaticMeshItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	UStaticMeshComponent* HelperMesh;

	/**This is the name that will be shown in the inventory. Determined by the Item's Data Asset.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	FString ItemDisplayName;

	/**This is the Static Mesh that will be shown in the world. Determined by the Item's Data Asset.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	UStaticMesh* PickupMesh;	

	/**The amount of weight the item will use in the inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Descriptors")
	float ItemWeight;


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
