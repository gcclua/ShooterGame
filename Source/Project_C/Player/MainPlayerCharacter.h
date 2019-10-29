// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InventorySystem/PickupActor.h"
#include "Interfaces/InteractionInterface.h"
#include "MainPlayerCharacter.generated.h"

UCLASS()
class PROJECT_C_API AMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Create object of class Weapon
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf< class AShootingWeapon > WeaponClass;

	// Create camera component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	// Spawned Weapon
	class AShootingWeapon* SpawnedWeapon;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf< class AProjectile > ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to attach a weapon to the main character
	void AttachWeaponToCharacter();

	// Called to fire
	UFUNCTION()
	void OnFire();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward
	UFUNCTION()
	void MoveForward(float Value);

	// Handles input for moving right and left
	UFUNCTION()
	void MoveRight(float Value);

	// Sets jump flag when key is pressed.
	UFUNCTION()
	void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
	void StopJump();

	// Function that handles interaction with object.
	UFUNCTION()
	void Interact();

	UPROPERTY(EditAnywhere)
	float SpeedMultiplication; // I don't know how i will use it, but let it be

};
