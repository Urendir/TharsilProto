// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDeathDelegate, int32, XPToAssign);

class UHealthComponent;
class UInventoryComponent;
class UInventoryItemBase;
class UCharacterMovementComponent;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable)
	FCharacterDeathDelegate CharacterDeathDelegate;

	UInventoryItemBase* ThisInventoryItem;
	
	//TO DO : THIS SHOULD BE MOVED TO THE XP COMPONENT!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	int32 XPReward = 500;

	//-----------------------------------------COMPONENTS-------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	UCharacterMovementComponent* MovementComponent;

	//--------------------------------------Component Influencing Variables and Functions---------------------------------

	virtual void CalculateCarryWeight();

	UFUNCTION(BlueprintCallable) 
	void SaveCharacterSpeedValues(); //This is used to restore Slow effects to health values. Should be calculated on each attribute point redistribution, to account for speed buffs from Agility.

	//------------------------------------Variables for character state-------------------------------------

	float SavedMaxWalkSpeed;
	float SavedMaxWalkSpeedCrouched;
	float SavedMaxSwimSpeed;
	float SavedMaxFlySpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	bool bIsCharacterSlowed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	bool bIsCharacterDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool HasWeaponDrawn = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool IsAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float SlowDebuffValue = 3; //This influences how much a slowdebuff (like overencumberance) will reduce movement speed. Default is 3, so walk speed will be 600/3 = 200.

	//-------------------------------------Character state change and Interaction Functions----------------------------------	

	UFUNCTION(BlueprintCallable)
	virtual void HandleCharacterDeath();

	UFUNCTION(BlueprintCallable)
	virtual void HandleIncomingDamage(float IncomingTotalDamage);


	UFUNCTION(BlueprintCallable)
	virtual void HandleCharacterSlowedEffect(bool bIsSlowed);

	UFUNCTION(BlueprintCallable, Category = "Item Interaction")
	void UseItem(TSubclassOf<UInventoryItemBase> Item);

	
};
