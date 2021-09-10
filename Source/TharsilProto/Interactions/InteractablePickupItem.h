// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TharsilProto/Interactions/InteractionInterface.h"
#include "InteractablePickupItem.generated.h"



class ABaseCharacter;
class UInventoryItemBase;
class UWorld;
class ABaseCharacter;


UCLASS()
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

	/**This is the name that will be shown in the inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
	FText ItemDisplayName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")
	UStaticMesh* PickupMesh;	

	/**The amount of weight the item will use in the inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
	float ItemWeight;

	/**The Inventory Element for this Item*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
	UInventoryItemBase* InventoryItem;

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
