// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TharsilProto/CombatEffects/StatusEffectBase.h"
#include "TharsilProto/CombatEffects/CombatAttributesSet.h"
#include "CombatCalculatorComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API UCombatCalculatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatCalculatorComponent();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseCharacter* OwningCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCombatAttributesSet* CombatAttributes;




/// <summary>
/// NEGATIVE Status Effect Flags and timer checks. These are set when the Owning Character has the respective status affecting them in a negative way.
/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBleeding;
	UPROPERTY()
	float BleedTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsStunned;
	UPROPERTY()
	float StunTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsKnockedDown;
	UPROPERTY()
		float KnockDownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBlinded;
	UPROPERTY()
		float BlindTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCrippled;
	UPROPERTY()
		float CrippledTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsWeakened;
	UPROPERTY()
		float WeakenedTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOverheating;
	UPROPERTY()
		float OverheatTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBurning;
	UPROPERTY()
		float BurnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsChilled;
	UPROPERTY()
		float ChillTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFrozen;
	UPROPERTY()
		float FreezeTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPoisoned;
	UPROPERTY()
		float PoisonTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsNecrosis;
	UPROPERTY()
		float NecrosisTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCorroding;
	UPROPERTY()
		float CorrosionTimer;


/// <summary>
/// POSITIVE Status Effect Flags. These are set when the Owning Character has the respective status affecting them in a positive way.
/// </summary>

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRested;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSatiated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEmboldened;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEmpowered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsGuarded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSolidified;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsAttackCritical;




protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*Called from Character*/
	UFUNCTION()
	bool OutCheckForCritical(float Passive, float ActiveAbility, float Agility);
	/*Called from Character*/
	UFUNCTION()
	float OutObtainLatestCritDamage();

	
	UFUNCTION()
	void InProcessDamage(UCombatAttributesSet* DamagingCombatAttributes, ABaseCharacter* DamageCauser, bool bIsCriticalHit);
	UFUNCTION()
	void InDetermineStatusEffects(UCombatAttributesSet* DamagingCombatAttributes);

	void InProcessStatusElementDamage(FElementalDamage Offensive, FElementalDamage Defensive, bool PrimaryStatusBool, bool SecondaryStatusBool);
	void InProcessStatusElementDamage(FElementalDamage Offensive, FElementalDamage Defensive, bool PrimaryStatusBool);

	UFUNCTION()
	void InProcessStatusEffect(FStatusEffect OffensiveEffect, FStatusEffect DefensiveEffect, bool StatusBool);

		
};
