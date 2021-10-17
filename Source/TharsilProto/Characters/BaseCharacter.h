// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TharsilProto/Interactions/DamageTypeStruct.h"
#include "BaseCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDeathDelegate, int32, XPToAssign);

class UHealthComponent;
class UEnergyComponent;
class UCharacterMovementComponent;
struct FDamageTypeBreakdown;


UCLASS()
class THARSILPROTO_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float BaseSprintSpeed = 1100.0f;
	//------------------------------------Variables for character state-------------------------------------
private:

	float SavedMaxWalkSpeed;
	float SavedMaxWalkSpeedCrouched;
	float SavedMaxSwimSpeed;
	float SavedMaxFlySpeed;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable)
	FCharacterDeathDelegate CharacterDeathDelegate;
	
	//TO DO : THIS SHOULD BE MOVED TO THE XP COMPONENT!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	int32 XPReward = 500;

	//-----------------------------------------COMPONENTS-------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UEnergyComponent* EnergyComponent;

	UCharacterMovementComponent* MovementComponent;

	//--------------------------------------Component Influencing Variables and Functions---------------------------------

	UFUNCTION(BlueprintCallable) 
	void SaveCharacterSpeedValues(); //This is used to restore Slow effects to health values. Should be calculated on each attribute point redistribution, to account for speed buffs from Agility.

	//------------------------------------Variables for character state-------------------------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	bool bIsCharacterSlowed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	bool bIsCharacterDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool HasWeaponDrawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool IsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float SlowDebuffValue = 2.5; //This influences how much a slowdebuff (like overencumberance) will reduce movement speed. Default is 3, so walk speed will be 600/3 = 200.

	bool bIsSprinting = false;

	//-------------------------------------------Movement Functions--------------------------------------------

	void SimpleJump();
	virtual void SprintStart();
	void SprintStop();


	//-------------------------------------Character state change and Interaction Functions----------------------------------	

	UFUNCTION(BlueprintCallable)
	virtual void HandleCharacterDeath();

	UFUNCTION(BlueprintCallable)
	virtual void ForwardIncomingDamageToCalculator(ABaseCharacter* ThisCharacter, ABaseCharacter* Damager, FDamageTypeBreakdown Damage);

	UFUNCTION(BlueprintCallable)
	void ProcessDamageTakenFromCalculator(float IncomingTotalDamage);

	UFUNCTION(BlueprintCallable)
	virtual void HandleCharacterSlowedEffect(bool bIsSlowed);



};
