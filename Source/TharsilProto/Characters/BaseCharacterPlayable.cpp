// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterPlayable.h"
#include "TharsilProto/Components/ExperienceComponent.h"
#include "TharsilProto/Components/AttributesComponent.h"
#include "TharsilProto/Components/HealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TharsilProto/Components/HealthComponent.h"


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
    UpdateSecondaryAttributes();
}


void ABaseCharacterPlayable::InteractWithItem() 
{
    //to be done via linetrace.
}


void ABaseCharacterPlayable::HandleLevelUpProcess() 
{
    UpdateSecondaryAttributes();
    AttributesComponent->IncreaseAttributePoints();
}

void ABaseCharacterPlayable::UpdateSecondaryAttributes() 
{
    UE_LOG(LogTemp, Warning, TEXT("Healthcomponent pinged to update HP. "));
    if(HealthComponent !=nullptr)
    {
        ABaseCharacter::HealthComponent->UpdateMaxHealth(AttributesComponent->AttributeConstitution, XPComponent->CurrentLevel);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Healthcomponent is nullptr."))
    }
}


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

void ABaseCharacterPlayable::BasicAttack() //Damage Calculation to be created based on Weapon equipped, skill used, attribute points assigned to Strength. 
{
	UE_LOG(LogTemp, Warning, TEXT("I Attack!"));
}

void ABaseCharacterPlayable::DEBUG_XPRewarder() 
{
	 //DEBUG code/ Should Be Dynamic. Value is here for testing purposes
    if(XPComponent == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: Unable to access the XP Component.")); 
        return;
    }
    XPComponent->IncreaseCurrentXP(XPReward);
}