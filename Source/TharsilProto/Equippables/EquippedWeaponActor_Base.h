// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TharsilProto/EquippedItemActor_Base.h"
#include "EquippedWeaponActor_Base.generated.h"

/**
 * 
 */
class UDA_CraftedWeaponBase;
class USkeletalMeshComponent;
class UCapsuleComponent;

UCLASS(Blueprintable)
class THARSILPROTO_API AEquippedWeaponActor_Base : public AEquippedItemActor_Base
{
	GENERATED_BODY()

		AEquippedWeaponActor_Base();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	UDA_CraftedWeaponBase* WeaponData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	UCapsuleComponent* CapsuleCollider;


};
