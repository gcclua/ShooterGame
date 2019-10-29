// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create sphere as a collision of a projectile
	ProjectileCollisionComponent = CreateDefaultSubobject <USphereComponent>(TEXT("ProjectileCollisionComponent"));
	//Set this collision sphere as a root component
	RootComponent = ProjectileCollisionComponent;

	// Define projectile movement component
	ProjectileMovementComponent = CreateDefaultSubobject <UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(ProjectileCollisionComponent);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& ShootDirection) {
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}