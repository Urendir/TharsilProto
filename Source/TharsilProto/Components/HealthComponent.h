// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDeathDelegate, int32, XPToAssign);

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth();

	UFUNCTION(BlueprintCallable)
	void DecreaseCurrentHealth(float DamageValue);

	UFUNCTION(BlueprintCallable)
	float IncreaseCurrentHealth(float HealValue);

	UFUNCTION(BlueprintCallable)
	float IncreaseCurrentHealthRegen(float HPRegenAddition, float HPRegenModifier);

	UFUNCTION(BlueprintCallable)
	void UpdateMaxHealth(int32 ConstitutionPoints, int32 CurrentLevel);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );	

	// UPROPERTY(BlueprintAssignable)
	// FCharacterDeathDelegate CharacterDeathDelegate;

	//bool CheckifCharacterisDead();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	ABaseCharacter* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 1.f; //Placeholder. Correct value is received from StatsComponent on Begin play.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float CurrentMaxHealth = 10.f; //Placeholder. Correct value is received from StatsComponent on Begin play. 
	
	float BaseHealth = 120.f;	//used as initial buffer for starting health
	int32 RememberedLevel;

	//------------------------PER ATTRIBUTEPOINT MODIFIERS---------------------------------------
	int32 PerConstitutionHealth = 15;
	int32 PerLevelHealth = 5;

//----------------------------------------- HEALTH REGENERATION VARIABLES AND FUNCTION
	float HealthRegenPerSecondBase = 1.0f;	//This is used to restore to default. 
	float HealthRegenPerSecond = 1.0f;		//amount of health to be regenerated per second. this gets influenced by passives, food, etc.
	bool bHasTakenDamageRecently;			//this is set to true when you get smacked. 
	float DamageDelay = 5.0f;				//this is the time in seconds it takes for health regen to kick in again.
	float DamageDelayTicker = 0.0f;			//this is incrementing while bHasTakenDamageRecently is true. 

	void ApplyHealthRegenOverTime(float DeltaTime);
	

};
