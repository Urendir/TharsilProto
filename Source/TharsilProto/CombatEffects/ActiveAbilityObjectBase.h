// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActiveAbilityObjectBase.generated.h"

/**
 * 
 */

class UDA_ActiveAbilityBase;

UCLASS(BlueprintType)
class THARSILPROTO_API UActiveAbilityObjectBase : public UObject
{
	GENERATED_BODY()

public:
	
	UActiveAbilityObjectBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDA_ActiveAbilityBase> ActiveAbilityData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOnCooldown = false;

	UPROPERTY()
	float TimeToCoolDown = 0.0f;

	UPROPERTY()
	float CooldownCounter = 0.0f;

	UFUNCTION()
	UDA_ActiveAbilityBase* GetUsableAbilityData();
};
