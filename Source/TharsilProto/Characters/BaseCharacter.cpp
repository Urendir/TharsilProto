// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "TharsilProto/Components/HealthComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(!HealthComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Healthcomponent failed to be created on baseCharacter class "));
	}
	
}

void ABaseCharacter::HandleCharacterDeath() 
{
    CharacterDeathDelegate.Broadcast(XPReward);
    bIsCharacterDead = true;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

