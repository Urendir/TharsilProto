// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TharsilProto/Characters/BaseCharacter.h"
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

//---------------------------- BASIC ARMOR & DEFENSE STATS ------------------------------------------------------------------------
/*These will be obtained from the Armor that is equipped, as well as from any skills that grant bonuses to the various resistances*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float SlashDefense;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float PierceDefense;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float CrushDefense;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float BleedResist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float KnockbackResist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float CrippleResist;

public:
//---------------------------- FUNCTIONS TO CALCULATE INCOMING DMG ------------------------------------------------------------------------

void CalculateDamageToCharacter(float SlashDmg, float PierceDmg, float CrushDmg, float BleedChance, float KnockbackChance, ABaseCharacter* Damager);

void CalculateDamageToArmor();

void CalculateBlockedDamage();

};
