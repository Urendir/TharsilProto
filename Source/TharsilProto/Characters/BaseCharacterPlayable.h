// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "TharsilProto/CombatEffects/CombatInteractionInterface.h"
#include "BaseCharacterPlayable.generated.h"

/**
 * 
 */

class UActiveAbilityComponent;
class UAttributesComponent;
class UCameraComponent;
class UExperienceComponent;
class UInventoryComponent;
class UInventoryItemBase;
class UPassiveSkillManagerComponent;
class USpringArmComponent;

UCLASS()
class THARSILPROTO_API ABaseCharacterPlayable : public ABaseCharacter, public ICombatInteractionInterface
{
	GENERATED_BODY()

protected: 
	virtual void BeginPlay() override;

public:
	ABaseCharacterPlayable();

	//------------------------------------------PUBLIC COMPONENTS----------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UActiveAbilityComponent* AbilityComponent;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//-------------------------------------------Component Interaction--------------------------------------------
	
	UFUNCTION(BlueprintCallable)	
	void HandleLevelUpProcess();

	UFUNCTION()
	void AddPassiveBonusesToPrimaryAttributes(int32 AgilityPas, int32 ArcEssPas, int32 Constitutionpas, int32 EndurancePas, int32 SpiritPas, int32 StrengthPas);	//Called by Passive Component to update the main 6 attributes in attribute component. 

	UFUNCTION(BlueprintCallable)		
	void UpdateSecondaryAttributes();

	UFUNCTION()
	void RecheckStaminaCostsOnInventoryUpdate();

	UFUNCTION(BlueprintCallable)
	void CalculateSprintSpeed();

	
	//------------------------------------------Combat Functions-------------------------------------------------
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OnActiveAbilityTriggered(ABaseCharacter* Target);

	//Combat Interaction Interface Implementation
	/*This is triggered when the character is activating an offensive ability and attempting to damage the target character, one the target is deemed attackable (via interface check)*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void AttemptToDamageTarget(ABaseCharacter* Target);
	virtual void AttemptToDamageTarget_Implementation(ABaseCharacter* Target);

	/*This function is triggered by the attacker, once all numeric values were calculated on the attacker side and is then calculating the damage on the receiver's end.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void OnAttacked(ABaseCharacter* Attacker);
	virtual void OnAttacked_Implementation(ABaseCharacter* Attacker);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void OnDeathFromAttack(ABaseCharacterPlayable* AttackingPlayer);
	virtual void OnDeathFromAttack_Implementation(ABaseCharacterPlayable* AttackingPlayer);

	//HandleCharacterDeath: Override of UFUNCTION in parent class (BaseCharacter) cannot have a UFUNCTION() declaration above it; 
	//it will use the same parameters as the original declaration.
	virtual void HandleCharacterDeath() override;

	//CalculateCharacterDamageNumbers: Override of UFUNCTION in parent class (BaseCharacter) cannot have a UFUNCTION() declaration above it; 
	//it will use the same parameters as the original declaration.
	virtual void CalculateCharacterDamageNumbers() override;
	
	virtual float CalculateLatestCritChance() override;

	virtual float CalculateLatestCritDamage() override;

	UFUNCTION(BlueprintCallable)
	void GivePassiveAttributesToCombatComponent();

	/// =============================================ACTIVE ABILITY SYSTEM FUNCTIONS============================
	/// These are created to be part of the keybinding allocation for Unreal. 
	/// They are supposed to then all call a specific function in the Ability Component, that also controls the cooldown of each ability slot. 
	/// <summary>
	/// 
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void CallPrimaryAbility();

	UFUNCTION(BlueprintCallable)
	void CallSecondaryAbility();

	UFUNCTION(BlueprintCallable)
	void CallQuickAbility1();

	UFUNCTION(BlueprintCallable)
	void CallQuickAbility2();

	UFUNCTION(BlueprintCallable)
	void CallQuickAbility3();

	UFUNCTION(BlueprintCallable)
	void CallQuickAbility4();

	UFUNCTION(BlueprintCallable)
	void CallQuickAbility5();

	UFUNCTION(BlueprintCallable)
	void CallQuickAbility6();

	//Check Resource Costs for various abilities
	UFUNCTION(BlueprintCallable)
	float GetCurrentAvailableStamina();
	UFUNCTION(BlueprintCallable)
	float GetCurrentAvailableHealth();
	UFUNCTION(BlueprintCallable)
	float GetCurrentAvailableMana();

	//Apply Ability Resource Cost to Current resources
	UFUNCTION(BlueprintCallable)
	void ApplyAbilityStaminaCost(float StaminaCost);
	UFUNCTION(BlueprintCallable)
	void ApplyAbilityHealthCost(float HealthCost);
	UFUNCTION(BlueprintCallable)
	void ApplyAbilityManaCost(float ManaCost);

	//------------------------------------------Interact with Items--------------------------------------------------
	UFUNCTION(BlueprintNativeEvent)
	void LineTraceForwardForInteraction();
	void LineTraceForwardForInteraction_Implementation();

	UFUNCTION()
	void RemoveFocusedActor();

	UFUNCTION(BlueprintCallable, Category = "Item Interaction")
	void UseItem(UInventoryItemBase* Item);
	//void UseItem(TSubclassOf<UInventoryItemBase> Item);

private:

	//-------------------------------------------PRIVATE COMPONENTS --------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAttributesComponent* AttributesComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPassiveSkillManagerComponent* PassiveSkillTreeManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UExperienceComponent* XPComponent;

	//-------------------------------------------Camera and SpringArm--------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UFUNCTION()
	void ZoomCamera(float Value);

	//-------------------------------------------Interaction Variables----------------------------------------------
	AActor* CurrentlyFocusedActor;

	UInventoryItemBase* ThisInventoryItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Targeting", meta = (AllowPrivateAccess = "true"))
	float LineTraceLength = 1000.0f;	

	//--------------------------------------------Movement Variables---------------------------------------------------------
	float CurrentSprintSpeed = 1200.0f;

	//-------------------------------------------Interaction Functions----------------------------------------------
	UFUNCTION()
	void InteractWithItem();

	UFUNCTION()
	void DEBUG_XPRewarder();
	UFUNCTION()
	void DEBUG_HighXPRewarder();

	//-------------------------------------------Movement Functions--------------------------------------------
	UFUNCTION()
	void MoveForwardBack(float AxisValue);
	UFUNCTION()
	void MoveLeftRight(float AxisValue);

};


