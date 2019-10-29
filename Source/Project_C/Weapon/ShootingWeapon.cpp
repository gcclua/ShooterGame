// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingWeapon.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AShootingWeapon::AShootingWeapon()
{
	MuzzlePoint = CreateDefaultSubobject< USceneComponent >(TEXT("MuzzlePoint"));
	MuzzlePoint->SetupAttachment(GetWeaponMesh());

}

class USceneComponent* AShootingWeapon::GetShootingWeaponMuzzle() const {
	return MuzzlePoint;
}