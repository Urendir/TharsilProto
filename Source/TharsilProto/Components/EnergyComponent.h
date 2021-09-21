// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

	UFUNCTION(BlueprintCallable)
		void RecalculateEnergyStats(int32 Endurance, int32 CharacterLevel);

	UFUNCTION(BlueprintCallable)
	bool DecreaseCurrentStamina(float DecrementAmount);

	UFUNCTION(BlueprintCallable)
	bool StaminaDrainOnJump(float StaminaCostToJump);

	float GetStaminaCostJump();
	float SetStaminaCostJump(float NewCost);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaBase = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaCurrent = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaMaximum = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenerationAmount = 5.0f; //Amount of Stamina regenerated every half a second.

	float StaminaPerLevel = 5.0f;
	float StaminaPerEndurance = 10.0f;
	float StaminaToJump = 25.0f;
	float StaminaToSprint = 10.0f;

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

	int32 RememberedLevel;

	void RecalculateMaximumStamina(int32 Endurance, int32 Level);
	//void StaminaDrainOnSprint();

	void RecalculateMaximumMana(int32 ArcaneEssence, int32 Level);
	void DecreaseCurrentMana();

	void EnableManaUsage();

	void RestoreEnergyOverTime(float DeltaTime);
};
