// Fill out your copyright notice in the Description page of Project Settings.


#include "EquippedItemActor_Base.h"

// Sets default values
AEquippedItemActor_Base::AEquippedItemActor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEquippedItemActor_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquippedItemActor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

