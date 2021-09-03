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

	UFUNCTION(BlueprintCallable)		
	void UpdateSecondaryAttributes();

private:

	//-------------------------------------------Components --------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UExperienceComponent* XPComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAttributesComponent* AttributesComponent;

	//-------------------------------------------Camera and SpringArm--------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;


	//-------------------------------------------Movement Functions--------------------------------------------
	void MoveForwardBack(float AxisValue);
	void MoveLeftRight(float AxisValue);

	//-------------------------------------------Interaction Functions----------------------------------------------
	void BasicAttack();
	void InteractWithItem();

	void DEBUG_XPRewarder();



};


