// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttributesUpdated);

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
	int32 AttributeAgility;
	int32 PassiveAdditionAgility = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 CommittedToAgility = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 AttributeArcaneEssence;
	int32 PassiveAdditionArcaneEssence = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 CommittedToArcaneEssence = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 AttributeConstitution;
	int32 PassiveAdditionConstitution = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 CommittedToConstitution = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 AttributeEndurance;
	int32 PassiveAdditionEndurance = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 CommittedToEndurance = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 AttributeSpirit;
	int32 PassiveAdditionSpirit = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 CommittedToSpirit = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 AttributeStrength;
	int32 PassiveAdditionStrength = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 CommittedToStrength = 0;

	//-------------------GENERAL NR OF STATS and Skillpoints---------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))
	int32 UnspentAttributePoints = 0;  		//Unspent Main Attribute Points - can be added to str, agi, con, end.
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))	
	int32 AttributeStartMinimum = 5;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Stats", meta = (AllowPrivateAccess = "true"))	
	int32 AttributePointsPerLevel = 2;	

	//-------------------Attribute calculation on Level Up---------------------------------		
	UFUNCTION(BlueprintCallable)
	void CalculateTotalAttributePoints();

	UFUNCTION(BlueprintCallable)
	void IncreaseAttributePoints();

	UFUNCTION(BlueprintCallable)
	void ResetAttributePoints();
	void InitializeAttributePoints();

	float CalculateCarryCapPerStrength();

	UPROPERTY(BlueprintAssignable)
	FOnAttributesUpdated OnAttributesUpdated;

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
