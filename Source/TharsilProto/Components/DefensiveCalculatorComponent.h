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

//---------------------------- BASIC PHYSICAL ARMOR & DEFENSE STATS ------------------------------------------------------------------------
/*These will be obtained from the Armor that is equipped, as well as from any skills that grant bonuses to the various resistances*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float SlashDefense;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float PierceDefense;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float CrushDefense;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float KnockbackResist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float KnockdownResist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float CrippleResist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float StunResist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float BleedResist;

	// poison damage, spores etc.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float ToxinResist;  

	// high armor damage.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float CorrosionResist; 

//---------------------------- MAGICAL DEFENSE STATS ------------------------------------------------------------------------
/*These will be obtained from the Armor that is equipped, as well as from any skills that grant bonuses to the various resistances*/

	// This is supposed to be high in fire-based creatures, medium in fleshy creatures and low in dried undead, for example.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float FireResist;

	// Molten creatures would be slowed by this. 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float ColdResist;

	// Fire creatures would be susceptible to this.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float WaterResist;

	// Lightning damages living creatures and water based creatures.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float LightningResist;

	// Fae damage is higher against necrotic creatures
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float FaeResist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float NecroticResist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float EtherealResist;

	//Creatures based on Darkness (shadows or other) are immune to this. Light creatures are weak.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float DarknessResist;

	//Creatures based on Darness are weak to this, ones based on light are immune
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	float LightResist;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magical Resistance Stats", meta = (AllowPrivateAccess = "true"))
	FDamageTypeBreakdown DefensiveStats;

//---------------------------- FUNCTIONS TO CALCULATE INCOMING DMG ------------------------------------------------------------------------

	void CalculateCharacterResistances(FDamageTypeBreakdown Resistances);

	void CalculateDamageToCharacter(ABaseCharacter* ThisCharacter, ABaseCharacter* Damager, FDamageTypeBreakdown* Damage);

void CalculateDamageToArmor();

void CalculateBlockedDamage();

};
