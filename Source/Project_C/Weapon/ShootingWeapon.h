// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "ShootingWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_C_API AShootingWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	// Sets default values
	AShootingWeapon();

protected:
	// Bullet exists, while max distance isn't reached
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperties")
	int32 MaxBulletDistance;

	// Damage of a bullet for a child weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperties")
	int32 Damage;				
	
	// Time interval (in seconds) between shots of two bullets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperties")
	int32 FireRate;

	//Muzzle location of shooting weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* MuzzlePoint;
	
public:
	// Getting muzzle
	class USceneComponent* GetShootingWeaponMuzzle() const;

};
