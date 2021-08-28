// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	float DecreaseCurrentHealth(float DamageValue);

	UFUNCTION(BlueprintCallable)
	float IncreaseCurrentHealth(float HealValue);

	UFUNCTION(BlueprintCallable)
	void UpdateMaxHealth(float NewMaxHealthValue);

	void HandleCharacterDeath();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	AActor* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 1.f; //Placeholder. Correct value is received from StatsComponent on Begin play.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float CurrentMaxHealth = 10.f; //Placeholder. Correct value is received from StatsComponent on Begin play. 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	bool IsCharacterDead = false;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );	

		
};
