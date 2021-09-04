// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TharsilProto/Interactions/InteractionInterface.h"
#include "InteractableBase.generated.h"

UCLASS()
class THARSILPROTO_API AInteractableBase : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Interaction")
	void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Interaction")
	void StartFocus();
	virtual void StartFocus_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Interaction")
	void EndFocus();
	virtual void EndFocus_Implementation();


};


