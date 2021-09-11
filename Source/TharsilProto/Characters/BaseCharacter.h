// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDeathDelegate, int32, XPToAssign);

class UHealthComponent;
class UInventoryComponent;
class UInventoryItemBase;

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

	//--------------------------------------Component Influencing Variables and Functions---------------------------------

	virtual void CalculateCarryWeight();

	//------------------------------------Booleans for character state-------------------------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	bool bIsCharacterDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool HasWeaponDrawn = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool IsAttacking = false;

	//-------------------------------------Character state change and Interaction Functions----------------------------------	

	UFUNCTION(BlueprintCallable)
	virtual void HandleCharacterDeath();

	UFUNCTION(BlueprintCallable)
	virtual void HandleIncomingDamage(float IncomingTotalDamage);

	UFUNCTION(BlueprintCallable, Category = "Item Interaction")
	void UseItem(TSubclassOf<UInventoryItemBase> Item);


};
