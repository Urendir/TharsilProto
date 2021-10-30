// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingTextActor.generated.h"

UCLASS(Abstract, Blueprintable)
class THARSILPROTO_API AFloatingTextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingTextActor();

	//Initializes the actor with the required starting information, that will populate the floating text widget. 
	UFUNCTION(BlueprintImplementableEvent, Category = "Floating Text Actor")
	void Initialize(const FText& Text);

	//Gets the Anchor Location of the floating text.
	inline const FVector& GetAnchorLocation() const { return AnchorLocation;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//location where the text is anchored - usually the top of the character.
	UPROPERTY()
	FVector AnchorLocation;

};
