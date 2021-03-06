// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterPlayable.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "TharsilProto/CombatEffects/ActiveAbilityObjectBase.h"
#include "TharsilProto/Components/ActiveAbilityComponent.h"
#include "TharsilProto/Components/AttributesComponent.h"
#include "TharsilProto/Components/CombatCalculatorComponent.h"
#include "TharsilProto/Components/EnergyComponent.h"
#include "TharsilProto/Components/ExperienceComponent.h"
#include "TharsilProto/Components/HealthComponent.h"
#include "TharsilProto/Components/InventoryComponent.h"
#include "TharsilProto/Components/PassiveSkillManagerComponent.h"
#include "TharsilProto/Interactions/InteractionInterface.h"
#include "TharsilProto/InventoryItems/InventoryItemBase.h"



ABaseCharacterPlayable::ABaseCharacterPlayable() 
{
    PrimaryActorTick.bCanEverTick = true;

    AbilityComponent = CreateDefaultSubobject<UActiveAbilityComponent>(TEXT("Active Abilities"));
    AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("Attributes"));
    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
    PassiveSkillTreeManager = CreateDefaultSubobject<UPassiveSkillManagerComponent>(TEXT("Passive Skill Manager"));
    XPComponent = CreateDefaultSubobject<UExperienceComponent>(TEXT("Leveling System"));

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void ABaseCharacterPlayable::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForwardBackward"), this, &ABaseCharacterPlayable::MoveForwardBack);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &ABaseCharacterPlayable::MoveLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpDown"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis(TEXT("CameraZoom"), this, &ABaseCharacterPlayable::ZoomCamera);
    PlayerInputComponent->BindAction(TEXT("InteractWithObject"), IE_Pressed, this, &ABaseCharacterPlayable::InteractWithItem);
	//PlayerInputComponent->BindAction(TEXT("PrimaryAttack"), IE_Pressed, this, &ABaseCharacterPlayable::BasicAttack); = NO LONGER VALID.
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ABaseCharacter::SimpleJump);
    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ABaseCharacter::SprintStart);
    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ABaseCharacter::SprintStop);
    PlayerInputComponent->BindAction(TEXT("PrimaryAbility"), IE_Pressed, this, &ABaseCharacterPlayable::CallPrimaryAbility);
    PlayerInputComponent->BindAction(TEXT("SecondaryAbility"), IE_Pressed, this, &ABaseCharacterPlayable::CallSecondaryAbility);
    PlayerInputComponent->BindAction(TEXT("QuickAbility2"), IE_Pressed, this, &ABaseCharacterPlayable::CallQuickAbility2);


	//COMMENT THIS OUT AFTER TESTING:
	PlayerInputComponent->BindAction(TEXT("XPDump"), IE_Pressed, this,&ABaseCharacterPlayable::DEBUG_XPRewarder); //DEBUG Item to add XP on button click
    PlayerInputComponent->BindAction(TEXT("HighXPDump"), IE_Pressed, this, &ABaseCharacterPlayable::DEBUG_HighXPRewarder);
}


// Called when the game starts or when spawned
void ABaseCharacterPlayable::BeginPlay()
{
	Super::BeginPlay();  
	
 
    HasWeaponDrawn = false;
	IsAttacking = false;
    bIsCharacterDead = false;
    XPReward = 500;

    if(!InventoryComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryComponent is nullptr."));
    }
    if(!AttributesComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("AttributesComponent is nullptr."));
    }
    if(!XPComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("XPComponent is nullptr."));
    }
    if(!HealthComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("HealthComponent is nullptr."));
    }   
    if (!EnergyComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("EnergyComponent is nullptr."));
    }
    if (!PassiveSkillTreeManager)
    {
        UE_LOG(LogTemp, Error, TEXT("PassiveSkillTreeManager is nullptr."));
    }

    UpdateSecondaryAttributes();
}




/// <summary>
/// This function only impacts the distance between camera and character.
/// </summary>
/// <param name="value"></param>
void ABaseCharacterPlayable::ZoomCamera(float Value)
{
    float TempLength = FMath::Clamp(SpringArm->TargetArmLength + (Value * -10), 200.0f, 700.0f);

    SpringArm->TargetArmLength = TempLength;
}


/// <summary>
/// ==========================================Item Interaction Functions. =============================================================
/// Used to line trace for anything implementing interaction interface. 
/// Used ingame to pick up items. 
/// </summary>

void ABaseCharacterPlayable::InteractWithItem()
{
    LineTraceForwardForInteraction(); 
    if(CurrentlyFocusedActor)
    {
        IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(CurrentlyFocusedActor); //LEARNING: This is looking for the interface on the currently focused actor, to check if it has one.           
        if(InteractionInterface)
        {
            InteractionInterface->Execute_OnInteract(CurrentlyFocusedActor, this);
        }        
    }
}


void ABaseCharacterPlayable::LineTraceForwardForInteraction_Implementation()
{
    FVector Location;
    FRotator Rotation;
    FHitResult HitResult;

    GetController()->GetPlayerViewPoint(Location, Rotation);
    const FVector Start = Location;
    const FVector End = Start + (Rotation.Vector() * LineTraceLength);
    FCollisionQueryParams TraceParams;
    TArray<AActor*> ActorsToIgnore;

    bool bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Yellow, FLinearColor::White, 0.5f);    

    if(bHit)
    {
        AActor* Interactable = HitResult.GetActor();

        if(Interactable)
        {
            if(Interactable != CurrentlyFocusedActor)
            {
                if(CurrentlyFocusedActor)
                {
                    IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(CurrentlyFocusedActor); //LEARNING: This is looking for the interface on the currently focused actor, to check if it has one. 
                    
                    if(InteractionInterface)
                    {
                        InteractionInterface->Execute_EndFocus(CurrentlyFocusedActor);
                    }
                }

                IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(Interactable);
                if(InteractionInterface)
                {
                    InteractionInterface->Execute_StartFocus(Interactable);
                }
                CurrentlyFocusedActor = Interactable;
            }
        }
        else
        {
            if(CurrentlyFocusedActor)
            {
                IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(CurrentlyFocusedActor); //LEARNING: This is looking for the interface on the currently focused actor, to check if it has one. 
                if(InteractionInterface)
                {
                    InteractionInterface->Execute_EndFocus(CurrentlyFocusedActor);
                }
            }
            CurrentlyFocusedActor = nullptr;
        }
    }
}


void ABaseCharacterPlayable::UseItem(UInventoryItemBase* Item)
{
    if (Item)
    {
    //ThisInventoryItem = Cast<UInventoryItemBase>(Item);
    Item->UseItem(this);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Issue with Item. Cannot Run Use."));
    }
}


void ABaseCharacterPlayable::RemoveFocusedActor()
{
    CurrentlyFocusedActor = nullptr;
}

//----------------------------------------------RPG SYSTEMS / PROGRESSION and COMPONENT INTERACTIONS-----------------------------------------------------
/// <summary>
/// 
/// </summary>
void ABaseCharacterPlayable::HandleLevelUpProcess() 
{
    UpdateSecondaryAttributes();
    AttributesComponent->IncreaseAttributePoints();
    PassiveSkillTreeManager->IncreasePassiveSkillPoints();
}

void ABaseCharacterPlayable::AddPassiveBonusesToPrimaryAttributes(int32 AgilityPas, int32 ArcEssPas, int32 Constitutionpas, int32 EndurancePas, int32 SpiritPas, int32 StrengthPas)
{
    AttributesComponent->PassiveAdditionAgility = AgilityPas;
    AttributesComponent->PassiveAdditionArcaneEssence = ArcEssPas;
    AttributesComponent->PassiveAdditionConstitution = Constitutionpas;
    AttributesComponent->PassiveAdditionEndurance = EndurancePas;
    AttributesComponent->PassiveAdditionSpirit = SpiritPas;
    AttributesComponent->PassiveAdditionStrength = StrengthPas;

    AttributesComponent->CalculateTotalAttributePoints();
}


void ABaseCharacterPlayable::UpdateSecondaryAttributes() 
{
    if (InventoryComponent)
    {
        InventoryComponent->CalculateCurrentCarryCapacity(AttributesComponent->AttributeStrength, XPComponent->CurrentLevel);
    }
    if(HealthComponent !=nullptr)
    {
        ABaseCharacter::HealthComponent->UpdateMaxHealth(AttributesComponent->AttributeConstitution, XPComponent->CurrentLevel);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Healthcomponent is nullptr."));
    }
    if (EnergyComponent != nullptr)
    {
        EnergyComponent->RecalculateManaAttributes(AttributesComponent->AttributeArcaneEssence, XPComponent->CurrentLevel, PassiveSkillTreeManager->PassiveAttributes->Mana.CurrentMaxValue);
        EnergyComponent->RecalculateStaminaAttributes(AttributesComponent->AttributeEndurance, AttributesComponent->AttributeAgility, XPComponent->CurrentLevel, PassiveSkillTreeManager->PassiveAttributes->Stamina.CurrentMaxValue, PassiveSkillTreeManager->PassiveAttributes->Stamina.RegenerationRate);
        EnergyComponent->RecalculateStaminaCosts(AttributesComponent->AttributeAgility, InventoryComponent->CalculateCurrentEncumberanceRate(), 0);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("EnergyComponent is nullptr."));
    }
    CalculateSprintSpeed();

    AttributesComponent->OnAttributesUpdated.Broadcast();
}


void ABaseCharacterPlayable::RecheckStaminaCostsOnInventoryUpdate()
{
    EnergyComponent->RecalculateStaminaCosts(AttributesComponent->AttributeAgility, InventoryComponent->CalculateCurrentEncumberanceRate(), PassiveSkillTreeManager->PassiveAttributes->SprintCost.CurrentValue);
}

//---------------------------------------------------------------------------LOCOMOTION--------------------------------------------------------------------------
void ABaseCharacterPlayable::MoveForwardBack(float AxisValue) 
{
	if(!bIsCharacterDead)
    {
        AddMovementInput(GetActorForwardVector() * AxisValue);
    }
}

void ABaseCharacterPlayable::MoveLeftRight(float AxisValue) 
{
    if(!bIsCharacterDead)
    {
        AddMovementInput(GetActorRightVector() * AxisValue);
    }
}

void ABaseCharacterPlayable::CalculateSprintSpeed()
{
    CurrentSprintSpeed = BaseSprintSpeed * InventoryComponent->CalculateCurrentEncumberanceRate() * (1 + PassiveSkillTreeManager->PassiveAttributes->SprintSpeed.CurrentValue);
}


//-------------------------------------------------------------------COMBAT FUNCTIONS-------------------------------------------------
//Combat Interaction Interface Implementation



void ABaseCharacterPlayable::OnActiveAbilityTriggered(ABaseCharacter* Target)
{
    UE_LOG(LogTemp, Warning, TEXT("OnActiveAbilityTriggered was called"));
    ICombatInteractionInterface* TargetCombatInterface = Cast<ICombatInteractionInterface>(Target);
    if (TargetCombatInterface != nullptr)
    {
        //Target->OnAttacked(this);
        if (Target->bWasJustDamaged == false)
        {
            TargetCombatInterface->Execute_OnAttacked(Target, this);// this will be removed when the delegate is done.
            //Target->bWasJustDamaged = true;
            AttemptToDamageTarget(Target);
        }
    }
}

/*This is triggered when the character is activating an offensive ability and attempting to damage the target character, one the target is deemed attackable (via interface check)*/
void ABaseCharacterPlayable::AttemptToDamageTarget_Implementation(ABaseCharacter* TargetOfAttack)
{
    UE_LOG(LogTemp, Warning, TEXT("%s is being attacking %s and attempting to deal damage. Damage Implementation on Player Character works."), *GetName(), *TargetOfAttack->GetName());
    
    if (CombatCalculatorComponent && PassiveSkillTreeManager && AbilityComponent && AttributesComponent)
    {
        bool IsCrit = CombatCalculatorComponent->OutCheckForCritical(PassiveSkillTreeManager->PassiveAttributes->CritChance.CurrentValue, AbilityComponent->CritPlaceholder, AttributesComponent->AttributeAgility );
        //Update Combat Attributes - TO DO HERE!

        //TargetOfAttack->CombatCalculatorComponent->InProcessDamage(CombatCalculatorComponent->CombatAttributes, this, IsCrit);
        OnCharacterDamagedDelegate.Broadcast(this, IsCrit, TargetOfAttack);
    }
}

void ABaseCharacterPlayable::OnAttacked_Implementation(ABaseCharacter* Attacker)
{
    UE_LOG(LogTemp, Warning, TEXT("%s is being attacked by %s"), *GetName(), *Attacker->GetName());
    
}

void ABaseCharacterPlayable::OnDeathFromAttack_Implementation(ABaseCharacter* AttackingCharacter)
{
    //This is used in the NPC Enemies to grant XP to player Character.
}








/// =============================================ACTIVE ABILITY SYSTEM FUNCTIONS============================
/// These are created to be part of the keybinding allocation for Unreal. 
/// They are supposed to then all call a specific function in the Ability Component, that also controls the cooldown of each ability slot. 
/// 

void ABaseCharacterPlayable::CallPrimaryAbility()
{
    AbilityComponent->AttemptTriggerAbility(AbilityComponent->PrimaryAbility);
}

void ABaseCharacterPlayable::CallSecondaryAbility()
{
    AbilityComponent->AttemptTriggerAbility(AbilityComponent->SecondaryAbility);
}

void ABaseCharacterPlayable::CallQuickAbility1()
{
    AbilityComponent->AttemptTriggerAbility(AbilityComponent->QuickAbility1);
}

void ABaseCharacterPlayable::CallQuickAbility2()
{
    AbilityComponent->AttemptTriggerAbility(AbilityComponent->QuickAbility2);
}

void ABaseCharacterPlayable::CallQuickAbility3()
{
    AbilityComponent->AttemptTriggerAbility(AbilityComponent->QuickAbility3);
}

void ABaseCharacterPlayable::CallQuickAbility4()
{
    AbilityComponent->AttemptTriggerAbility(AbilityComponent->QuickAbility4);
}

void ABaseCharacterPlayable::CallQuickAbility5()
{
    AbilityComponent->AttemptTriggerAbility(AbilityComponent->QuickAbility5);
}

void ABaseCharacterPlayable::CallQuickAbility6()
{
    AbilityComponent->AttemptTriggerAbility(AbilityComponent->QuickAbility6);
}



float ABaseCharacterPlayable::GetCurrentAvailableStamina()
{
    UE_LOG(LogTemp, Warning, TEXT("Checking Current Stamina, should be %f"), EnergyComponent->GetCurrentStamina());
    return EnergyComponent->GetCurrentStamina();   
}

float ABaseCharacterPlayable::GetCurrentAvailableHealth()
{
    return HealthComponent->GetCurrentHealth();
}

float ABaseCharacterPlayable::GetCurrentAvailableMana()
{
    return EnergyComponent->GetCurrentMana();
}

void ABaseCharacterPlayable::ApplyAbilityStaminaCost(float StaminaCost)
{
    EnergyComponent->DecreaseCurrentStamina(StaminaCost);
}

void ABaseCharacterPlayable::ApplyAbilityHealthCost(float HealthCost)
{
    //HealthComponent-> Update Current health.
}

void ABaseCharacterPlayable::ApplyAbilityManaCost(float ManaCost)
{
    EnergyComponent->DecreaseCurrentMana(ManaCost);
}


//===================================================COMBAT DATA CALCULATION===============================
//Used for damage calculations within Combat component

UCombatAttributesSet* ABaseCharacterPlayable::CalculateCharacterDamageNumbers(UActiveAbilityObjectBase* TriggeredAbility)
{
    if (CombatCalculatorComponent && PassiveSkillTreeManager && InventoryComponent)
    {
        CombatCalculatorComponent->CombatAttributes->AddEntireCombatValueSet(TriggeredAbility->AbilityAttributes);
    }
    return CombatCalculatorComponent->CombatAttributes;
}

float ABaseCharacterPlayable::CalculateLatestCritChance()
{
    PassiveSkillTreeManager->PassiveAttributes->CritChance.CurrentValue;
    
    //passive crit chance
    //ability crit chance
    //equipment crit chance
    //attribute based modifiers.
    return 0.0f;
}

float ABaseCharacterPlayable::CalculateLatestCritDamage()
{
    float CritDmg = CombatCalculatorComponent->ObtainLatestCritDamage(PassiveSkillTreeManager->PassiveAttributes->CritDamage.CurrentValue, AttributesComponent->AttributeStrength, 0, 0);
    
    return CritDmg;
}

void ABaseCharacterPlayable::GivePassiveAttributesToCombatComponent()
{


}


void ABaseCharacterPlayable::HandleCharacterDeath() 
{
    CharacterDeathDelegate.Broadcast(XPReward);
    bIsCharacterDead = true;
}


//=======================================================TEST / DEVELOPMENT FUNCTIONS==================================

/// <summary>
/// DEBUG FUNCTION. REMOVE THIS AFTER TESTING
/// </summary>
void ABaseCharacterPlayable::DEBUG_XPRewarder() 
{
	 //DEBUG code/ Should Be Dynamic. FUNCTION is here for testing purposes
    if(XPComponent == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: Unable to access the XP Component.")); 
        return;
    }
    XPComponent->IncreaseCurrentXP(XPReward * XPComponent->CurrentLevel);
}

void ABaseCharacterPlayable::DEBUG_HighXPRewarder()
{
    //DEBUG code/ Should Be Dynamic. FUNCTION is here for testing purposes
    if (XPComponent == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: Unable to access the XP Component."));
        return;
    }
    XPComponent->IncreaseCurrentXP(XPReward * XPComponent->CurrentLevel * 10);
}

