// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TharsilProto/DataAssets/Abilities/DA_AbilityModBase.h"
#include "TharsilProto/DataAssets/Abilities/DA_ActiveAbilityBase.h"
#include "LearningPathManagerComponent.generated.h"


USTRUCT(BlueprintType)
struct THARSILPROTO_API FLearningPathMainLeveling : public FTableRowBase
{
	GENERATED_BODY()

public:
	//-----------------------------
	/*the current level reached on this learning path*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learning Path Metrics")
	int32 CurrentLevel = 0;
	/*The current maximum of the Attribute.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learning Path Metrics")
	float ExperienceToLevel = 0.0f;
	/*First ability granted*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	UDA_ActiveAbilityBase* GrantedAbilityA;
	/*Second ability granted*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	UDA_ActiveAbilityBase* GrantedAbilityB;
	/*Third ability granted*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	UDA_ActiveAbilityBase* GrantedAbilityC;
	/*Fourth ability granted*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	UDA_ActiveAbilityBase* GrantedAbilityD;
	/*Adds a mod slot to ability 1*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	bool ModSlotAbility1;
	/*Adds a mod slot to ability 2*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	bool ModSlotAbility2;
	/*Adds a mod slot to ability 3*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	bool ModSlotAbility3;
	/*Adds a mod slot to ability 4*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	bool ModSlotAbility4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mods")
		UDA_AbilityModBase* ModA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mods")
		UDA_AbilityModBase* ModB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mods")
		UDA_AbilityModBase* ModC;

};

USTRUCT(BlueprintType)
struct THARSILPROTO_API FLearningPathSecondaryLeveling : public FTableRowBase
{
	GENERATED_BODY()

public:
	//-----------------------------
	/*the current level reached on this learning path*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learning Path Metrics")
		int32 CurrentLevel = 0;
	/*The current maximum of the Attribute.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learning Path Metrics")
		float ExperienceToLevel = 0.0f;
	/*First ability granted*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		UDA_ActiveAbilityBase* GrantedAbilityA;
	/*Second ability granted*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		UDA_ActiveAbilityBase* GrantedAbilityB;

	/*Adds a mod slot to ability 1*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		bool ModSlotAbility1;
	/*Adds a mod slot to ability 2*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		bool ModSlotAbility2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mods")
		UDA_AbilityModBase* ModA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mods")
		UDA_AbilityModBase* ModB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mods")
		UDA_AbilityModBase* ModC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mods")
		UDA_AbilityModBase* ModD;
};




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THARSILPROTO_API ULearningPathManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULearningPathManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



public: 







		
};
