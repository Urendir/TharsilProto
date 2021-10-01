// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseCharacterPlayable.generated.h"

/**
 * 
 */

class UAttributesComponent;
class UCameraComponent;
class UExperienceComponent;
class UInventoryComponent;
class UInventoryItemBase;
class UPassiveSkillManagerComponent;
class USpringArmComponent;

UCLASS()
class THARSILPROTO_API ABaseCharacterPlayable : public ABaseCharacter
{
	GENERATED_BODY()

protected: 
	virtual void BeginPlay() override;

public:
	ABaseCharacterPlayable();

	//------------------------------------------PUBLIC COMPONENTS----------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//-------------------------------------------Component Interaction--------------------------------------------
	UFUNCTION(BlueprintCallable)	
	void HandleLevelUpProcess();

	void AddPassiveBonusesToPrimaryAttributes(int32 AgilityPas, int32 ArcEssPas, int32 Constitutionpas, int32 EndurancePas, int32 SpiritPas, int32 StrengthPas);	//Called by Passive Component to update the main 6 attributes in attribute component. 

	UFUNCTION(BlueprintCallable)		
	void UpdateSecondaryAttributes();

	void RecheckStaminaCostsOnInventoryUpdate();

	UFUNCTION(BlueprintCallable)
	void CalculateSprintSpeed();
	//------------------------------------------Combat Functions-------------------------------------------------
	virtual void HandleCharacterDeath() override;


	//------------------------------------------Interact with Items--------------------------------------------------
	UFUNCTION(BlueprintNativeEvent)
	void LineTraceForwardForInteraction();
	void LineTraceForwardForInteraction_Implementation();

	UFUNCTION(BlueprintCallable)
	bool BasicAttack();

	UFUNCTION(BlueprintCallable)
	bool CanYouAffordBasicAttack();

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


