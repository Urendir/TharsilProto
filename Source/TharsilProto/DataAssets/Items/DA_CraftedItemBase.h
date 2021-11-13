// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TharsilProto/DataAssets/Items/DA_ItemBase.h"
#include "DA_CraftedItemBase.generated.h"

class UDA_CraftingMaterialBase;

UCLASS()
class THARSILPROTO_API UDA_CraftedItemBase : public UDA_ItemBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials Needed for Crafting")
	UDA_CraftingMaterialBase* CraftingMaterial1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials Needed for Crafting")
	int32 UnitsUsedMaterial1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials Needed for Crafting")
	UDA_CraftingMaterialBase* CraftingMaterial2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials Needed for Crafting")
	int32 UnitsUsedMaterial2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials Needed for Crafting")
	UDA_CraftingMaterialBase* CraftingMaterial3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials Needed for Crafting")
	int32 UnitsUsedMaterial3;

};
