// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatingCombatTextComponent.generated.h"

class AFloatingTextActor;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UFloatingCombatTextComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloatingCombatTextComponent();

private:
	//Floating combat text actor, used to display text on damage (i.e. floating damage numbers)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FloatingCombatTextComponent", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AFloatingTextActor> FloatingTextActorClass = nullptr;

	//Amount of vertical Space between each number
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FloatingCombatTextComponent", Meta = (AllowPrivateAccess = "true"))
	float TextVerticalSpacing = 40.0f;

	//Offset to apply where above the actor this spawns
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FloatingCombatTextComponent", Meta = (AllowPrivateAccess = "true"))
	float TextVerticalOffset = 100.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Adds the text at the specified location in worldspace. - Multiplayer enabled.
	UFUNCTION(Client, Unreliable, BlueprintCallable, Category = "FloatingCombatTextComponent")
	void AddFloatingText_CLIENT(const FText& Text, FVector WorldLocation);

private: 
	//callback for when a floating text actor is destroyed.
	UFUNCTION()
	void OnTextDestroyed(AActor* DestroyedActor);

	//array of all active floating text actos.
	UPROPERTY()
	TArray<AFloatingTextActor*> ActiveTextActors;
};
