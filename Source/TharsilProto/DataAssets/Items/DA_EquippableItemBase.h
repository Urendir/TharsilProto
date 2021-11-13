// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DA_CraftedItemBase.h"
#include "DA_EquippableItemBase.generated.h"

/**
 * 
 */
UCLASS()
class THARSILPROTO_API UDA_EquippableItemBase : public UDA_CraftedItemBase
{
	GENERATED_BODY()

public:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General Equipment Stats")
		float MaxDurability = 0.0f;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General Equipment Stats")
		float PrestigeScore = 0.0f;
};
