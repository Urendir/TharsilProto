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

	UFUNCTION(BlueprintCallable)
	void DecreaseCurrentHealth(float DamageValue);

	UFUNCTION(BlueprintCallable)
	float IncreaseCurrentHealth(float HealValue);

	UFUNCTION(BlueprintCallable)
	void UpdateMaxHealth(int32 ConstitutionPoints, int32 CurrentLevel);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );	

	// UPROPERTY(BlueprintAssignable)
	// FCharacterDeathDelegate CharacterDeathDelegate;

	bool CheckifCharacterisDead();

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

	// //THIS SHOULD BE MOVED TO THE XP COMPONENT!
	// int32 XPReward = 500;


	//------------------------PER ATTRIBUTEPOINT MODIFIERS---------------------------------------
	int32 PerConstitutionHealth = 15;
	int32 PerLevelHealth = 5;

		
};
