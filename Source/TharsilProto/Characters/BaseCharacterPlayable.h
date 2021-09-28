// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseCharacterPlayable.generated.h"

/**
 * 
 */


class UExperienceComponent;
class UAttributesComponent;
class USpringArmComponent;
class UCameraComponent;
class UPassiveSkillManagerComponent;

UCLASS()
class THARSILPROTO_API ABaseCharacterPlayable : public ABaseCharacter
{
	GENERATED_BODY()

protected: 
	virtual void BeginPlay() override;

public:
	ABaseCharacterPlayable();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//-------------------------------------------Component Interaction--------------------------------------------
	UFUNCTION(BlueprintCallable)	
	void HandleLevelUpProcess();

	void AddPassiveBonusesToPrimaryAttributes(int32 AgilityPas, int32 ArcEssPas, int32 Constitutionpas, int32 EndurancePas, int32 SpiritPas, int32 StrengthPas);	//Called by Passive Component to update the main 6 attributes in attribute component. 

	UFUNCTION(BlueprintCallable)		
	void UpdateSecondaryAttributes();

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

	void RemoveFocusedActor();

private:

	//-------------------------------------------Components --------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UExperienceComponent* XPComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAttributesComponent* AttributesComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPassiveSkillManagerComponent* PassiveSkillTreeManager;

	//-------------------------------------------Camera and SpringArm--------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	//-------------------------------------------Interaction Variables----------------------------------------------
	AActor* CurrentlyFocusedActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Targeting", meta = (AllowPrivateAccess = "true"))
	float LineTraceLength = 1000.0f;	

	//--------------------------------------------Movement Variables---------------------------------------------------------
	float CurrentSprintSpeed = 1200.0f;

	//-------------------------------------------Interaction Functions----------------------------------------------

	void InteractWithItem();

	void DEBUG_XPRewarder();

	//-------------------------------------------Movement Functions--------------------------------------------
	void MoveForwardBack(float AxisValue);
	void MoveLeftRight(float AxisValue);


};


