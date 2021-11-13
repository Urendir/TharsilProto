// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DA_EquippableItemBase.h"
#include "TharsilProto/ProgressionSystems/GeneralAttributeSet.h"
#include "DA_CraftedWeaponBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Category = "Weapon Description")
enum class EWeaponType : uint8
{
	E_Default		UMETA(DisplayName = "Default"),
	E_SwordShord	UMETA(DisplayName = "Sword"),
	E_Axe			UMETA(DisplayName = "Axe"),
	E_Spear			UMETA(DisplayName = "Spear"),
	E_Hammer		UMETA(DisplayName = "Hammer"),
};


UENUM(BlueprintType, Category = "Weapon Description")
enum class ESwordType : uint8
{
	E_Default			UMETA(DisplayName = "Default"),
	E_SwordShord		UMETA(DisplayName = "Shortsword"),
	E_SwordArming		UMETA(DisplayName = "Arming Sword"),
	E_SwordBroad		UMETA(DisplayName = "Broadsword"),
	E_SwordLong			UMETA(DisplayName = "Longsword"),
	E_SwordBastard		UMETA(DisplayName = "Bastard Sword"),
	E_SwordGreat		UMETA(DisplayName = "Greatsword"),
};

UENUM(BlueprintType, Category = "Weapon Description")
enum class EAxeType : uint8
{
	E_AxeBearded		UMETA(DisplayName = "Bearded Axe"),
	E_AxeBoarding		UMETA(DisplayName = "Boarding Axe"),
	E_AxeOno			UMETA(DisplayName = "Ono Axe"),
	E_AxeGreat			UMETA(DisplayName = "Greataxe"),
	E_AxeNorse			UMETA(DisplayName = "Northman's Axe"),
	E_AxeHooked			UMETA(DisplayName = "Hooked Axe"),
	E_AxeSagaris		UMETA(DisplayName = "Sagaris Axe"),
	E_AxeDoralian		UMETA(DisplayName = "Doralian Axe"),
	E_AxeBattle			UMETA(DisplayName = "Battleaxe"),
};


UCLASS()
class THARSILPROTO_API UDA_CraftedWeaponBase : public UDA_EquippableItemBase
{
	GENERATED_BODY()

	UDA_CraftedWeaponBase();

public:
	
	/*Determine Type of Weapon Created*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	EWeaponType TypeOfWeapon;

	/*Determine Type of Sword Created*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats") //This should onyl show if TypeOfWeapon is Sword.
		ESwordType TypeOfSword;
	/*Determine Type of Axe Created*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")	//This should onyl show if TypeOfWeapon is Axe.
		EAxeType TypeOfAxe;

	/*This is a numeric value indicating the raw Slash Damage*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		float DamageSlash = 0.0f;
	/*This is a numeric value indicating the raw Pierce Damage*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		float DamagePierce = 1.0f;
	/*This is a numeric value indicating the raw Crush Damage*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		float DamageCrush = 10.0f;
	/*Armor Penetration total can go from 0 to 600 and is then divided in the damage calculation, to give a percent of ignored armor on pierce and crush attack*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		int32 ArmorPenetration = 0;
	
};
