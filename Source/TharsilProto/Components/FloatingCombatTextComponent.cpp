// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingCombatTextComponent.h"
#include "TharsilProto/Components/FloatingTextActor.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFloatingCombatTextComponent::UFloatingCombatTextComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFloatingCombatTextComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFloatingCombatTextComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (GetOwner<APawn>()->IsLocallyControlled() == false)
	{
		return;
	}

	FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);

	////This checks for bad viewport size.
	//if (ViewportSize.X <= 0.0f || ViewportSize.Y <= 0.0f)
	//{
	//	return;
	//}


	////Get the viewport's scale (the DPI scale)
	//const int32 ViewportX = FGenericPlatformMath::FloorToInt(ViewportSize.X);
	//const int32 ViewportY = FGenericPlatformMath::FloorToInt(ViewportSize.Y);
	//const float ViewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(ViewportX, ViewportY));

	
	////Check for any bad scale
	//if (ViewportScale <= 0.0f)
	//{
	//	return;
	//}

	//const FVector CameraLocation = GetOwner<APawn>()->GetController<APlayerController>()->PlayerCameraManager->GetCameraLocation();

	////Adjusts the vertical location of the active text actor bt the viewport size, so they appear evenly stacked on screen
	//for (int32 i = 1; i < ActiveTextActors.Num(); ++i)
	//{
	//	//Calculates vertical offset based on distance from camera.
	//	AFloatingTextActor* TextActor = ActiveTextActors[i];
	//	const float Distance = FVector::Dist(CameraLocation, TextActor->GetAnchorLocation());
	//	const float VerticalOffset = Distance / (ViewportSize.X / ViewportScale);

	//	//Adjust floating text actor location by calculated amount
	//	TextActor->SetActorLocation(TextActor->GetAnchorLocation() + FVector(0.0f, 0.0f, i * VerticalOffset * TextVerticalSpacing));
	//}
}

void UFloatingCombatTextComponent::AddFloatingText_CLIENT_Implementation(const FText& Text, FVector WorldLocation)
{
	if(FloatingTextActorClass == nullptr)
	{
		return;
	}

	const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, WorldLocation + FVector(0.0f, 0.0f, TextVerticalOffset));
	AFloatingTextActor* NewTextActor = GetWorld()->SpawnActorDeferred<AFloatingTextActor>(FloatingTextActorClass, SpawnTransform, GetOwner());

	if(NewTextActor == nullptr)
	{
		return;
	}

	//Initialize and finish Spawning Actor.
	NewTextActor->Initialize(Text);
	NewTextActor->OnDestroyed.AddDynamic(this, &UFloatingCombatTextComponent::OnTextDestroyed);
	UGameplayStatics::FinishSpawningActor(NewTextActor, SpawnTransform);

	//Adds the new actor to the beginning of the array, so it is closest to the character.
	ActiveTextActors.Insert(NewTextActor, 0);
}

void UFloatingCombatTextComponent::OnTextDestroyed(AActor* DestroyedActor)
{
	ActiveTextActors.Pop();
}



