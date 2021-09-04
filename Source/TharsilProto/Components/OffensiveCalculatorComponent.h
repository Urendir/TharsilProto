// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TharsilProto/Characters/BaseCharacter.h"
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

private:	

//---------------------------- BASIC ATTACK STATS ------------------------------------------------------------------------
/*These will be obtained from the Weapon that is equipped, as well as from any skills that grant bonuses to the various modifiers*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float SlashDmg;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float PierceDmg;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float CrushDmg;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float BleedChance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float KnockbackChance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive Stats", meta = (AllowPrivateAccess = "true"))
	float CrippleChance;

public:	

	void DamageCharacter(ABaseCharacter* DamageTarget );

	void DamageOwnEquipment();

};
