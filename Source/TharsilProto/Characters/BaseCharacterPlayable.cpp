// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterPlayable.h"
#include "TharsilProto/Components/ExperienceComponent.h"
#include "TharsilProto/Components/AttributesComponent.h"
#include "TharsilProto/Components/HealthComponent.h"
#include "TharsilProto/Components/InventoryComponent.h"
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
	PlayerInputComponent->BindAction(TEXT("PrimaryAttack"), IE_Pressed, this, &ABaseCharacterPlayable::BasicAttack);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
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
        UE_LOG(LogTemp, Error, TEXT("Carryweightbase (%f) + CarryweightPerStr (%f) + Currentlvl (%i) * CarryWEightPerLvl(%f)"), InventoryComponent->CarryWeightBaseCapacity, AttributesComponent->CalculateCarryCapPerStrength(), XPComponent->CurrentLevel, InventoryComponent->CarryWeightPerLevel);
        CarryWeightTotal = InventoryComponent->CarryWeightBaseCapacity + AttributesComponent->CalculateCarryCapPerStrength() + (float)XPComponent->CurrentLevel * InventoryComponent->CarryWeightPerLevel;
    }
    else
    {
        CarryWeightTotal = 1.0f;
    }
    UE_LOG(LogTemp, Error, TEXT("CarryweightTotal: %f"), CarryWeightTotal);

    InventoryComponent->UpdateCarryCapacity(CarryWeightTotal);
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


//---------------------------------------------------------------------------------COMBAT FUNCTIONS--------------------------------------------------------------------
void ABaseCharacterPlayable::BasicAttack() //Damage Calculation to be created based on Weapon equipped, skill used, attribute points assigned to Strength. 
{
	UE_LOG(LogTemp, Warning, TEXT("I Attack!"));
}

void ABaseCharacterPlayable::HandleCharacterDeath() 
{
    CharacterDeathDelegate.Broadcast(XPReward);
    bIsCharacterDead = true;
}

void ABaseCharacterPlayable::HandleIncomingDamage(float IncomingTotalDamage) 
{
	
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

