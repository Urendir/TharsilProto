// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterNPC.h"

/*This is triggered when the character is activating an offensive ability and attempting to damage the target character, one the target is deemed attackable (via interface check)*/
void ABaseCharacterNPC::AttemptToDamageTarget_Implementation(ABaseCharacter* Target)
{

}

void ABaseCharacterNPC::OnAttacked_Implementation(ABaseCharacter* Attacker)
{
    UE_LOG(LogTemp, Error, TEXT("%s is being attacked by %s"), *GetName(), *Attacker->GetName());
}

void ABaseCharacterNPC::OnDeathFromAttack_Implementation(ABaseCharacter* AttackingCharacter)
{
    //This is used in the NPC Enemies to grant XP to player Character.
}
