// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PassiveSkillManagerComponent.generated.h"

UENUM(BlueprintType)
enum class EPassiveSkillEffect : uint8
{
	E_AddAttributeAgility UMETA(DisplayName = "Add Agility"),
	E_AddAttributeStrength UMETA(DisplayName = "Add Strength"),
	E_AddAttributeConstitution UMETA(DisplayName = "Add Constitution"),
	E_AddAttributeEndurance UMETA(DisplayName = "Add Endurance"),
	E_AddAttributeHealth UMETA(DisplayName = "Add Health"),
	E_AddAttributeHealthRegen UMETA(DisplayName = "Add Health Regen"),
	E_AddAttributeStamina UMETA(DisplayName = "Add Stamina"),
	E_AddAttributeStaminaRegen UMETA(DisplayName = "Add Stamina Regen"),
	E_AddAttributeCarryCapacity UMETA(DisplayName = "Add Carry Capacity"),
};


class UPassiveSkillNode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UPassiveSkillManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPassiveSkillManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<UPassiveSkillNode*> SkillTree;


	EPassiveSkillEffect PassiveEffects;

};
