// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TharsilProto/CombatEffects/CombatAttributesSet.h"
#include "DA_AbilityModBase.generated.h"



/**
 * 
 */
UCLASS()
class THARSILPROTO_API UDA_AbilityModBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public: 
	/*This is the name that will be shown in the UI*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mod Description")
	FString DisplayName;

	/*This is an description for the Mod*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mod Description")
		FText Description;

	/*The thumbnail of the mod.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mod Description")
		UTexture2D* Thumbnail;





};
