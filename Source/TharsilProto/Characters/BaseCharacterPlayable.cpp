// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterPlayable.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TharsilProto/Components/ExperienceComponent.h"
#include "TharsilProto/Components/AttributesComponent.h"
#include "TharsilProto/Components/HealthComponent.h"
#include "TharsilProto/Components/EnergyComponent.h"
#include "TharsilProto/Components/InventoryComponent.h"
#include "TharsilProto/Components/PassiveSkillManagerComponent.h"
#include "TharsilProto/Interactions/InteractionInterface.h"


ABaseCharacterPlayable::ABaseCharacterPlayable() 
{
    PrimaryActorTick.bCanEverTick = true;

    AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("Attributes"));
    XPComponent = CreateDefaultSubobject<UExperienceComponent>(TEXT("Leveling System"));
    PassiveSkillTreeManager = CreateDefaultSubobject<UPassiveSkillManagerComponent>(TEXT("Passive Skill Manager"));

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
    PlayerInputComponent->BindAction(TEXT("InteractWithObject"), IE_Pressed, this, &ABaseCharacterPlayable::InteractWithItem);
	//PlayerInputComponent->BindAction(TEXT("PrimaryAttack"), IE_Pressed, this, &ABaseCharacterPlayable::BasicAttack); = NO LONGER VALID.
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ABaseCharacter::SimpleJump);
    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ABaseCharacter::SprintStart);
    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ABaseCharacter::SprintStop);

	//COMMENT THIS OUT AFTER TESTING:
	PlayerInputComponent->BindAction(TEXT("XPDump"), IE_Pressed, this,&ABaseCharacterPlayable::DEBUG_XPRewarder); //DEBUG Item to add XP on button click
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
/// Item Interaction Functions. Used to line trace for anything implementing interaction interface. 
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
        ABaseCharacter::EnergyComponent->RecalculateManaAttributes(AttributesComponent->AttributeArcaneEssence, XPComponent->CurrentLevel, PassiveSkillTreeManager->ManaPointsPassive);
        ABaseCharacter::EnergyComponent->RecalculateStaminaAttributes(AttributesComponent->AttributeEndurance, AttributesComponent->AttributeAgility, XPComponent->CurrentLevel, PassiveSkillTreeManager->StaminaPointsPassive, PassiveSkillTreeManager->StaminaRegenPassive);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("EnergyComponent is nullptr."));
    }
    CalculateSprintSpeed();

    AttributesComponent->OnAttributesUpdated.Broadcast();
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
    CurrentSprintSpeed = BaseSprintSpeed * InventoryComponent->CalculateCurrentEncumberanceRate() * (1 + PassiveSkillTreeManager->SprintSpeedPassive);
}



//---------------------------------------------------------------------------------COMBAT FUNCTIONS--------------------------------------------------------------------
bool ABaseCharacterPlayable::BasicAttack() //Damage Calculation to be created based on Weapon equipped, skill used, attribute points assigned to Strength. 
{
	UE_LOG(LogTemp, Warning, TEXT("I Attack!"));
    return EnergyComponent->DecreaseCurrentStamina(45); //Magic number to be replaced by skill cost.
}

bool ABaseCharacterPlayable::CanYouAffordBasicAttack() //This is a temporary function to test combat. Once combat gets reworked, remove it. 
{
    if (EnergyComponent->WhatsCurrentStamina() < 45)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void ABaseCharacterPlayable::HandleCharacterDeath() 
{
    CharacterDeathDelegate.Broadcast(XPReward);
    bIsCharacterDead = true;
}



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

