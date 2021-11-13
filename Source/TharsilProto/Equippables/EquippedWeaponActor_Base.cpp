// Fill out your copyright notice in the Description page of Project Settings.


#include "EquippedWeaponActor_Base.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "TharsilProto/DataAssets/Items/DA_CraftedWeaponBase.h"


AEquippedWeaponActor_Base::AEquippedWeaponActor_Base()
{
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
}