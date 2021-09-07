// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	//------------------------MAIN PLAYER ATTRIBUTES-----------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 AttributeStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 AttributeAgility;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 AttributeConstitution;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 AttributeEndurance;

	//-------------------GENERAL NR OF STATS and Skillpoints---------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 UnspentAttributePoints = 0;  		//Unspent Main Attribute Points - can be added to str, agi, con, end.
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))	
	int32 AttributeStartMinimum = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))	
	int32 TotalAttributePoints;			//Sum of all Attribute Points, spent and unspent, minus the minimum cap(5x4). Will be used for Resets.
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))	
	int32 AttributePointsPerLevel = 2;	

	//-------------------Attribute calculation on Level Up---------------------------------		
	UFUNCTION(BlueprintCallable)
	void IncreaseAttributePoints();

	UFUNCTION(BlueprintCallable)
	void ResetAttributePoints();

	float CalculateCarryCapPerStrength();

private: 
	ABaseCharacter* Owner;

	//------------------------PER ATTRIBUTEPOINT MODIFIERS---------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Modifiers", meta = (AllowPrivateAccess = "true"))	
	float PerConstitutionHealth = 15.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Modifiers", meta = (AllowPrivateAccess = "true"))	
	float PerStrengthCarryCapacity = 1.3f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Modifiers", meta = (AllowPrivateAccess = "true"))	
	int32 PerEnduranceStamina = 10.f;

};
