// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveAbilityComponent.h"
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
	PrimaryAbility = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("PrimaryAbility"));
	SecondaryAbility = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("SecondaryAbility"));
	QuickAbility1 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility1"));
	QuickAbility2 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility2"));
	QuickAbility3 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility3"));
	QuickAbility4 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility4"));
	QuickAbility5 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility5"));
	QuickAbility6 = CreateDefaultSubobject<UActiveAbilityObjectBase>(TEXT("QuickAbility6"));
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
	
	TickAbilityCooldown(PrimaryAbility, DeltaTime);
	TickAbilityCooldown(SecondaryAbility, DeltaTime);
	TickAbilityCooldown(QuickAbility1, DeltaTime);
	TickAbilityCooldown(QuickAbility2, DeltaTime);
	TickAbilityCooldown(QuickAbility3, DeltaTime);
	TickAbilityCooldown(QuickAbility4, DeltaTime);
	TickAbilityCooldown(QuickAbility5, DeltaTime);
	TickAbilityCooldown(QuickAbility6, DeltaTime);
}

void UActiveAbilityComponent::ApplyAbilityToSlot(TSubclassOf<UDA_ActiveAbilityBase> AbilityToSlot, UActiveAbilityObjectBase* AbilitySlot)
{
	AbilitySlot->ActiveAbilityData = AbilityToSlot;
	if (AbilitySlot != nullptr)
	{
		AbilitySlot->TimeToCoolDown = AbilitySlot->GetUsableAbilityData()->CooldownTime;
	}
}

void UActiveAbilityComponent::AttemptTriggerAbility(UActiveAbilityObjectBase* CalledAbility)
{
	UE_LOG(LogTemp, Warning, TEXT("Attempted to trigger ability"));
	if(!CalledAbility)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempt to trigger ability failed as nullptr"));
		return;
	}

	if (!CalledAbility->bIsOnCooldown && !bIsGlobalAbilityBlock)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempt to trigger ability has succeeded preliminarily"));
		UDA_ActiveAbilityBase* AbilityData = CalledAbility->GetUsableAbilityData();
		if (!AbilityData)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Ability Data detected"));
			return;
		}
		if (CheckAbilityResourceCost(AbilityData))
		{
			CommitAbilityResourceCost(AbilityData);
			CalledAbility->bIsOnCooldown = true;
			//trigger effect
		}
	}
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

