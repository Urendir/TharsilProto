// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "TharsilProto/Interactions/DamageTypeStruct.h"
#include "OffensiveCalculatorComponent.generated.h"

class ABaseCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UOffensiveCalculatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOffensiveCalculatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Offensive Stats", meta = (AllowPrivateAccess = "true"))
	FDamageTypeBreakdown DamageCollection;



	/// <summary>
	/// Critical Damage Functions
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void CalculateCriticalModifiers(int32 Agility);


//----------------------------------------------- This is the basic Outgoing Damage Function----------------------------------------------
	UFUNCTION(BlueprintCallable)
	void DamageEnemyCharacter(ABaseCharacter* DamageTarget, FDamageTypeBreakdown Damage);


private:	
	ABaseCharacter* Owner;

	/// <summary>
	/// Critical Damage Modifiers
	/// </summary>

	float CriticalDamageModifier = 1.75f;
	float CriticalChance = 0.0f;

	float CritPerAgilityUnder50 = 0.005f;
	float CritPerAgilityUnder100 = 0.003f;
	float CritPerAgilityUnder150 = 0.002f;
	float CritPerAgilityAbove150 = 0.001f;

	/// <summary>
	/// Damage Functions
	/// </summary>
	UFUNCTION()
	void CalculateDamageRatings();

	UFUNCTION()
	void DamageOwnEquipment();

};
