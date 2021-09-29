// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "EnergyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UEnergyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnergyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION()
	void RecalculateStaminaAttributes(int32 Endurance, int32 Agility, int32 Level, float PassiveStaminaMod, float PassiveStaminaRegen);
	UFUNCTION()
	void RecalculateStaminaCosts(int32 Agility, float EncumberanceRate, float PassiveSprintCostReduction);

	UFUNCTION()
	void RecalculateManaAttributes(int32 ArcaneEssence, int32 Level, float PassiveManaMod);

	UFUNCTION(BlueprintCallable)
	bool DecreaseCurrentStamina(float DecrementAmount);

	float GetStaminaCostJump();

	float GetStaminaCostToSprint();

	float WhatsCurrentStamina(); // THis is a temporary function, until combat is reworked. 

private:

	ABaseCharacter* OwningCharacter;

	int32 RememberedLevel;

	/// <summary>
	/// Stamina variables - used to calculate max, current and regen amount. 
	/// impacted via the attributes component.
	/// </summary>

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaBase = 95.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaCurrent = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaMaximum = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenerationAmount = 2.0f; //Amount of Stamina regenerated every half a second.

	float StaminaPerLevel = 5.0f;
	float StaminaPerEndurance = 10.0f;
	float StaminaToJump = 5.0f;
	float BaseStaminaToJump = 15.0f;
	float StaminaToSprint = 5.0f;
	float BaseStaminaToSprint = 10.0f;

	/// <summary>
	/// Breath Variables. Relevant for once underwater is implemented
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float BreathBase = 95.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float BreathCurrent = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float BreathMaximum = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float BreathRegenerationAmount = 2.0f; //Amount of Stamina regenerated every half a second.

	float BreathPerLevel = 5.0f;
	float BreathPerEndurance = 10.0f;
	float BreathCostPerSec = 20.0f;



	/// <summary>
	///--------------------------------------------------Magic Energy Variables and Functions. 
	/// Magic to be enabled after specific quest completion.
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	bool isMagicUser;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float ManaBase = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float ManaCurrent = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float ManaMaximum = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float ManaRegenerationAmount = 3.0f; // Amount of Mana regenerated per half a second.

	float ManaPerLevel = 5.0f;
	float ManaPerEssence = 5.0f;

	void DecreaseCurrentMana();
	void RestoreEnergyOverTime(float DeltaTime);
	void EnableManaUsage();

	/// <summary>
	/// These are both called in  void RecalculateEnergyStats(int32 Endurance, int32 CharacterLevel);
	/// Called by owning player. 
	/// </summary>

	void RecalculateMaximumStamina(int32 Endurance, int32 Level, float PassiveStaminaMod);
	void RecalculateStaminaRegen(float PassiveStaminaRegen);


};
