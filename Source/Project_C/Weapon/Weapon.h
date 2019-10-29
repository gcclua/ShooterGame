// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class PROJECT_C_API AWeapon : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Weapon mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* WeaponMesh;

	// Called for getting a mesh of weapon
	class UStaticMeshComponent* GetWeaponMesh() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
