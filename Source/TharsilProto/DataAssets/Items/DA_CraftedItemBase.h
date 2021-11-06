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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Materials Needed for Crafting")
	UDA_CraftingMaterialBase* CraftingMaterial1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Materials Needed for Crafting")
	UDA_CraftingMaterialBase* CraftingMaterial2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Materials Needed for Crafting")
	UDA_CraftingMaterialBase* CraftingMaterial3;


};
