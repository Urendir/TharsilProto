// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "TharsilProto/CombatEffects/CombatInteractionInterface.h"
#include "BaseCharacterNPC.generated.h"

/**
 * 
 */
UCLASS()
class THARSILPROTO_API ABaseCharacterNPC : public ABaseCharacter, public ICombatInteractionInterface
{
	GENERATED_BODY()
	
public:
		//Combat Interaction Interface Implementation
	/*This is triggered when the character is activating an offensive ability and attempting to damage the target character, one the target is deemed attackable (via interface check)*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
		void AttemptToDamageTarget(ABaseCharacter* Target);
	virtual void AttemptToDamageTarget_Implementation(ABaseCharacter* Target);

	/*This function is triggered by the attacker, once all numeric values were calculated on the attacker side and is then calculating the damage on the receiver's end.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
		void OnAttacked(ABaseCharacter* Attacker);
	virtual void OnAttacked_Implementation(ABaseCharacter* Attacker);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
		void OnDeathFromAttack(ABaseCharacter* AttackingCharacter);
	virtual void OnDeathFromAttack_Implementation(ABaseCharacter* AttackingCharacter);

};
