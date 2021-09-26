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


	float ArmorPenetrationModifier = 0.0002f;
	//Default: 0.0002f. This impacts the % amount of Armor Penetration, calculated from the attacker's base point value. 
	//The % value is AP/5000, meaning that the desired hard cap for AP is 500, which results in 10% AP.

	float ArmorPointsToResistanceDivider = 600.0f;
	//Default: 600. Used to divide the armor points by, to get the % of damage resistance for slash, pierce, crush dmg. 
	// example: if armor shows 150 slash resistance, 150/600 = 0.25. =25% actual slash resistance. 
	//not public and only used internally in calculations.

	ABaseCharacter* Owner;

	UFUNCTION()
	void CalculateCharacterResistances(FDamageResistanceBreakdown ResistanceModifiers);

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
