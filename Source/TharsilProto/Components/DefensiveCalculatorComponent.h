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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances and Defense Stats")
	FDamageResistanceBreakdown DefensiveStats;

//---------------------------- FUNCTIONS TO CALCULATE INCOMING DMG ------------------------------------------------------------------------

	void CalculateCharacterResistances(FDamageResistanceBreakdown Resistances);

	void CalculateDamageToCharacter(ABaseCharacter* ThisCharacter, ABaseCharacter* Damager, FDamageTypeBreakdown* Damage);

void CalculateDamageToArmor();

void CalculateBlockedDamage();

};
