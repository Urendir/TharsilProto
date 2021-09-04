// Fill out your copyright notice in the Description page of Project Settings.


#include "LineTraceWorldComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
ULineTraceWorldComponent::ULineTraceWorldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULineTraceWorldComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULineTraceWorldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Start = GetOwner()->GetActorLocation();
	FVector End = ((GetForwardVector() * TraceDistance) + Start);
	FHitResult Hit;
	FCollisionQueryParams TraceParams;

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
	DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 0.2f);

	if(bHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Orange, FString::Printf(TEXT("Trace Hit %s"), *Hit.GetActor()->GetName()));
	}
}

