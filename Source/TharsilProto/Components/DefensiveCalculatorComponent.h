// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "TharsilProto/Interactions/DamageTypeStruct.h"
#include "DefensiveCalculatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UDefensiveCalculatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDefensiveCalculatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	//Default: 0.0002f. This impacts the % amount of Armor Penetration, calculated from the attacker's base point value. The % value is AP/5000, meaning that the desired hard cap for AP is 500, which results in 10% AP.
	float ArmorPenetrationModifier = 0.0002f;

	ABaseCharacter* Owner;

	UFUNCTION()
	void CalculateCharacterResistances();

	UFUNCTION()
	int32 CalculateIncomingDamage(FDamageTypeBreakdown Damage);

	UFUNCTION()
	float CalculateDamageToArmor(float IncomingDamage);

	UFUNCTION()
	void CalculateBlockedDamage();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances and Defense Stats")
	FDamageResistanceBreakdown DefensiveStats;


//---------------------------- FUNCTIONS TO CALCULATE INCOMING DMG ------------------------------------------------------------------------
	UFUNCTION()
	void ProcessIncomingDamage(ABaseCharacter* ThisCharacter, ABaseCharacter* Damager, FDamageTypeBreakdown Damage);



};
