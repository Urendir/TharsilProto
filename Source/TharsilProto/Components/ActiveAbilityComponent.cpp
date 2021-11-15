// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveAbilityComponent.h"
#include "Animation/AnimInstance.h"
#include "TharsilProto/Characters/BaseCharacterPlayable.h"
#include "TharsilProto/DataAssets/Abilities/DA_ActiveAbilityBase.h"
#include "TharsilProto/CombatEffects/ActiveAbilityObjectBase.h"


// Sets default values for this component's properties
UActiveAbilityComponent::UActiveAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OwningCharacter = Cast<ABaseCharacterPlayable>(GetOwner());
	AbilityPrimarySlot = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("Primary Ability Slot"));
	AbilitySecondarySlot = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("Secondary Ability Slot"));
	AbilityQuickSlot1 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility Slot 1"));
	AbilityQuickSlot2 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility Slot 2"));
	AbilityQuickSlot3 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility Slot 3"));
	AbilityQuickSlot4 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility Slot 4"));
	AbilityQuickSlot5 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility Slot 5"));
	AbilityQuickSlot6 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility Slot 6"));
}


// Called when the game starts
void UActiveAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActiveAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	TickGlobalAbilityBlock(DeltaTime);
	
	TickAbilityCooldown(AbilityPrimarySlot, DeltaTime);
	TickAbilityCooldown(AbilitySecondarySlot, DeltaTime);
	TickAbilityCooldown(AbilityQuickSlot1, DeltaTime);
	TickAbilityCooldown(AbilityQuickSlot2, DeltaTime);
	TickAbilityCooldown(AbilityQuickSlot3, DeltaTime);
	TickAbilityCooldown(AbilityQuickSlot4, DeltaTime);
	TickAbilityCooldown(AbilityQuickSlot5, DeltaTime);
	TickAbilityCooldown(AbilityQuickSlot6, DeltaTime);
}

void UActiveAbilityComponent::ApplyAbilityToSlot(UDA_ActiveAbilityBase* AbilityData, UActiveAbilityObjectBase* AbilitySlot)
{
	AbilitySlot->ActiveAbilityData = AbilityData;
	if (AbilitySlot != nullptr)
	{
		AbilitySlot->TimeToCoolDown = AbilityData->CooldownTime;
	}
}

//THIS IS THE OBSOLETE IMPLEMENTATION OF THE ABILITY TRIGGER. KEEPING IT FOR REFERENCE/LEARNING
//void UActiveAbilityComponent::AttemptTriggerAbility(UActiveAbilityObjectBase* CalledAbility)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Attempted to trigger ability"));
//	if(!CalledAbility)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Attempt to trigger ability failed as nullptr"));
//		return;
//	}
//
//	if (!CalledAbility->bIsOnCooldown && !bIsGlobalAbilityBlock)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Attempt to trigger ability has succeeded preliminarily"));
//		UDA_ActiveAbilityBase* AbilityData = CalledAbility->GetUsableAbilityData();
//		if (!AbilityData)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("No Ability Data detected"));
//			return;
//		}
//		if (CheckAbilityResourceCost(AbilityData))
//		{
//			CurrentAbility = AbilityData;
//			//CommitAbilityResourceCost(AbilityData);
//			CalledAbility->bIsOnCooldown = true;
//			//trigger effect
//		}
//	}
//}

void UActiveAbilityComponent::AttemptTriggerAbility(UDA_ActiveAbilityBase* CalledAbility)
{
	UE_LOG(LogTemp, Warning, TEXT("Attempted to trigger ability"));
	if (!CalledAbility)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tsubclass of ability failed as nullptr"));
		return;
	}

	if (!bIsGlobalAbilityBlock)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempt to trigger ability has succeeded preliminarily"));
		CurrentAbility = CalledAbility;
		
		if (!CurrentAbility)
		{
			UE_LOG(LogTemp, Warning, TEXT("Current Ability is nullptr"));
		} 
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Current Ability name is %s"), *CurrentAbility->DisplayName);
		}
	
		if (CheckAbilityResourceCost(CurrentAbility))
		{
			OwningCharacter->PlayAnimMontage(CurrentAbility->AnimationMontage, 1.0f);
			//UAnimInstance::Montage_Play(Ability->AnimationMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, true);
			// Trigger Cooldown! CalledAbility->bIsOnCooldown = true;
			//CommitAbilityResourceCost(CalledAbility); -> This is now called by Anim notify at appropriate moment. 
			//trigger effect after committing
			UE_LOG(LogTemp, Warning, TEXT("Anim Montage should be playing"));
		}
	}
}

UActiveAbilityObjectBase* UActiveAbilityComponent::FindMatchingSlot(UDA_ActiveAbilityBase* TriggeredAbility)
{
	if (TriggeredAbility == PrimaryAbility)
	{
		return AbilityPrimarySlot;
	}
	else if (TriggeredAbility == SecondaryAbility)
	{
		return AbilitySecondarySlot;
	}
	else if (TriggeredAbility == QuickAbility1)
	{
		return AbilityQuickSlot1;
	}
	else if (TriggeredAbility == QuickAbility2)
	{
		return AbilityQuickSlot2;
	}
	else if (TriggeredAbility == QuickAbility3)
	{
		return AbilityQuickSlot3;
	}
	else if (TriggeredAbility == QuickAbility4)
	{
		return AbilityQuickSlot4;
	}
	else if (TriggeredAbility == QuickAbility5)
	{
		return AbilityQuickSlot5;
	}
	else if (TriggeredAbility == QuickAbility6)
	{
		return AbilityQuickSlot6;
	}
	//TO DO  - add the rest
	return nullptr;
}

bool UActiveAbilityComponent::CheckAbilityResourceCost(UDA_ActiveAbilityBase* AbilityDataAsset)
{
	bool bHasEnoughResourceToCast = false;
	if (OwningCharacter->GetCurrentAvailableStamina() > AbilityDataAsset->StaminaCost)
	{
		bHasEnoughResourceToCast = true;
	}
	if (AbilityDataAsset->bHasManaCost && OwningCharacter->GetCurrentAvailableMana() < AbilityDataAsset->ManaCost)
	{
		bHasEnoughResourceToCast = false;
	}
	if (AbilityDataAsset->bHasHealthCost && OwningCharacter->GetCurrentAvailableHealth() < AbilityDataAsset->HealthCost)
	{
		bHasEnoughResourceToCast = false;
	}
	return bHasEnoughResourceToCast;
}

void UActiveAbilityComponent::CommitAbilityResourceCost(UDA_ActiveAbilityBase* AbilityDataAsset)
{
	TriggerGlobalAbilityBlock(AbilityDataAsset);
	StartAbilityCooldown(FindMatchingSlot(AbilityDataAsset));
	OwningCharacter->ApplyAbilityStaminaCost(AbilityDataAsset->StaminaCost);

	if (AbilityDataAsset->bHasHealthCost)
	{
		OwningCharacter->ApplyAbilityHealthCost(AbilityDataAsset->HealthCost);
	}
	
	if(AbilityDataAsset->bHasManaCost)
	{
		OwningCharacter->ApplyAbilityManaCost(AbilityDataAsset->ManaCost);
	}


}

void UActiveAbilityComponent::TriggerGlobalAbilityBlock(UDA_ActiveAbilityBase* AbilityDataAsset)
{
	GlobalAbilityBlockTimer = AbilityDataAsset->TimeToBlockAbilities;
	if (GlobalAbilityBlockTimer > 0.0f)
	{
		bIsGlobalAbilityBlock = true;
	}
}

void UActiveAbilityComponent::TickGlobalAbilityBlock(float DeltaTime)
{
	if (bIsGlobalAbilityBlock)
	{
		if (GlobalAbilityBlockTimer <= 0)
		{
			bIsGlobalAbilityBlock = false;
		}
		GlobalAbilityBlockTimer -= (1 * DeltaTime);
	}

}


void UActiveAbilityComponent::StartAbilityCooldown(UActiveAbilityObjectBase* CalledAbility)
{
	if (!CalledAbility->bIsOnCooldown && !bIsGlobalAbilityBlock)
	{
		CalledAbility->bIsOnCooldown = true;
		CalledAbility->CooldownCounter = CalledAbility->TimeToCoolDown;
	}
}

void UActiveAbilityComponent::TickAbilityCooldown(UActiveAbilityObjectBase* AbilityToTick, float DeltaTime)
{
	if (AbilityToTick->bIsOnCooldown)
	{
		if (AbilityToTick->CooldownCounter <= 0)
		{
			AbilityToTick->bIsOnCooldown = false;
		}
		else
		{
			AbilityToTick->CooldownCounter -= 1 * DeltaTime;
		}
	}
}

