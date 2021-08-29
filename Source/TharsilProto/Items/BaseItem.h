// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS()
class THARSILPROTO_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/**This is the name that will be shown in the inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
	FText ItemDisplayName;
	
	/**This is an optional description for the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")
	UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Descriptors")
	UStaticMesh* PickupMesh;	

	/**The amount of weight the item will use in the inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
	float ItemWeight;

	/**The monetary value of the item*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptors")
	float ItemValue;


};
