// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActiveAbilityComponent.generated.h"


class ABaseCharacterPlayable;
class UDA_ActiveAbilityBase;
class UActiveAbilityObjectBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UActiveAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActiveAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*This ability block is here to prevent any other ability from triggering. This is intended to act as a global cooldown, if an ability has a long animation*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Active Abilities")
	bool bIsGlobalAbilityBlock = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Active Abilities")
	float GlobalAbilityBlockTimer = 0.0f;


	float CritPlaceholder = 0.0f;

	ABaseCharacterPlayable* OwningCharacter;

	/// <summary>
	/// Standard Attack or generic click ability.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Active Abilities")
	UActiveAbilityObjectBase* PrimaryAbility;

	/// <summary>
	/// Right Click Ability - usually a block. 
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Active Abilities")
	UActiveAbilityObjectBase* SecondaryAbility;
	
	/// <summary>
	/// Abilities on Quickbar, i.e. the standard 1-6 ability buttons on the UI.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Active Abilities")
	UActiveAbilityObjectBase* QuickAbility1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Active Abilities")
	UActiveAbilityObjectBase* QuickAbility2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Active Abilities")
	UActiveAbilityObjectBase* QuickAbility3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Active Abilities")
	UActiveAbilityObjectBase* QuickAbility4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Active Abilities")
	UActiveAbilityObjectBase* QuickAbility5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Active Abilities")
	UActiveAbilityObjectBase* QuickAbility6;

	UFUNCTION(BlueprintCallable)
	void ApplyAbilityToSlot(TSubclassOf<UDA_ActiveAbilityBase> AbilityToSlot, UActiveAbilityObjectBase* AbilitySlot);

	UFUNCTION(BlueprintCallable)
	void AttemptTriggerAbility(UActiveAbilityObjectBase* CalledAbility);

private:
	UFUNCTION(BlueprintCallable)
	bool CheckAbilityResourceCost(UDA_ActiveAbilityBase* AbilityDataAsset);
	UFUNCTION(BlueprintCallable)
	void CommitAbilityResourceCost(UDA_ActiveAbilityBase* AbilityDataAsset);
	UFUNCTION()
	void TriggerGlobalAbilityBlock(UDA_ActiveAbilityBase* AbilityDataAsset);
	UFUNCTION()
	void TickGlobalAbilityBlock(float DeltaTime);
	UFUNCTION()
	void StartAbilityCooldown(UActiveAbilityObjectBase* CalledAbility);
	UFUNCTION()
	void TickAbilityCooldown(UActiveAbilityObjectBase* AbilityToTick, float DeltaTime);
};
