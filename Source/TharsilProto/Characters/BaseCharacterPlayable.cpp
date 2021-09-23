// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterPlayable.h"
#include "TharsilProto/Components/ExperienceComponent.h"
#include "TharsilProto/Components/AttributesComponent.h"
#include "TharsilProto/Components/HealthComponent.h"
#include "TharsilProto/Components/EnergyComponent.h"
#include "TharsilProto/Components/InventoryComponent.h"
#include "TharsilProto/Components/PassiveSkillManagerComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
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
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ABaseCharacterPlayable::SimpleJump);
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

//------------------------------------------------------------------ COMPONENT INTERACTION / RPG SYSTEMS------------------------------------------------------------------
void ABaseCharacterPlayable::CalculateCarryWeight() 
{
    float CarryWeightTotal;
    
    if(InventoryComponent && AttributesComponent && XPComponent)
    {
        CarryWeightTotal = InventoryComponent->CarryWeightBaseCapacity + AttributesComponent->CalculateCarryCapPerStrength() + (float)XPComponent->CurrentLevel * InventoryComponent->CarryWeightPerLevel;
    }
    else
    {
        CarryWeightTotal = 1.0f;
    }

    InventoryComponent->UpdateCarryCapacity(CarryWeightTotal);
}


void ABaseCharacterPlayable::RemoveFocusedActor()
{
    CurrentlyFocusedActor = nullptr;
}

void ABaseCharacterPlayable::HandleLevelUpProcess() 
{
    UpdateSecondaryAttributes();
    AttributesComponent->IncreaseAttributePoints();
}


void ABaseCharacterPlayable::UpdateSecondaryAttributes() 
{
    CalculateCarryWeight();
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
        ABaseCharacter::EnergyComponent->RecalculateEnergyStats(AttributesComponent->AttributeEndurance, XPComponent->CurrentLevel);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("EnergyComponent is nullptr."));
    }


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

void ABaseCharacterPlayable::SimpleJump()
{
    bool CanJump = EnergyComponent->StaminaDrainOnJump(EnergyComponent->GetStaminaCostJump());
    if (CanJump)
    {
        ACharacter::Jump();
    }
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
    XPComponent->IncreaseCurrentXP(XPReward);
}

