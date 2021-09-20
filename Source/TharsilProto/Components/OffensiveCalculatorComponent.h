// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TharsilProto/Characters/BaseCharacter.h"
#include "TharsilProto/Interactions/DamageTypeStruct.h"
#include "OffensiveCalculatorComponent.generated.h"

class ABaseCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UOffensiveCalculatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOffensiveCalculatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Offensive Stats", meta = (AllowPrivateAccess = "true"))
	FDamageTypeBreakdown DamageCollection;

//----------------------------------------------- This is the basic Outgoing Damage Function----------------------------------------------
	UFUNCTION(BlueprintCallable)
	void DamageEnemyCharacter(ABaseCharacter* DamageTarget, FDamageTypeBreakdown Damage);


private:	
	ABaseCharacter* Owner;

	UFUNCTION()
	void CalculateDamageRatings();

	UFUNCTION()
	void DamageOwnEquipment();

};
