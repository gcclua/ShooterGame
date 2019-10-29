// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerCharacter.h"
#include "Weapon/ShootingWeapon.h"
#include "Weapon/Projectile.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
AMainPlayerCharacter::AMainPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera component
	CameraComponent = CreateDefaultSubobject< UCameraComponent >(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());

	// Set default SpeedMultiplication
	SpeedMultiplication = 1.0f;
}

// Called when the game starts or when spawned
void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Attaching a weapon to the main character
	AttachWeaponToCharacter();
	
}

// Called every frame
void AMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to attach a weapon to a character
void AMainPlayerCharacter::AttachWeaponToCharacter() {
	if (WeaponClass) {
		UWorld* World = GetWorld();
		if (World) {
			FVector WeaponSocketLocation;
			FRotator WeaponSocketRotation;

			// Define WeaponSocket location and rotaion and set transform rules for our weapon, when it's spawned
			WeaponSocketLocation = GetMesh()->GetSocketLocation("WeaponSocket");
			WeaponSocketRotation = GetMesh()->GetSocketRotation("WeaponSocket");
			FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

			// Spawn Wepoan with location and rotation of WeaponSocket
			SpawnedWeapon = World->SpawnActor< AShootingWeapon >(WeaponClass, WeaponSocketLocation, WeaponSocketRotation);

			// Attach weapon to WeaponSocket
			SpawnedWeapon->AttachToComponent(GetMesh(), TransformRules, "WeaponSocket");
		}
	}
}

// Called to fire
void AMainPlayerCharacter::OnFire() {
	// Start debugging
	FHitResult OutHit;

	FVector Start = SpawnedWeapon->GetShootingWeaponMuzzle()->GetComponentLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector End = ((ForwardVector * 100000000.f) + Start);
	FCollisionQueryParams CollisionParams;

	// DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
	{
		if (OutHit.bBlockingHit)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));
		}
	}
	// End debugging

	// Attempt to fire a projectile
	if (ProjectileClass) {
		// Get muzzle location and rotation for spawning projectile
		FVector MuzzleLocation = SpawnedWeapon->GetShootingWeaponMuzzle()->GetComponentLocation();
		FRotator MuzzleRotation = SpawnedWeapon->GetShootingWeaponMuzzle()->GetComponentRotation();

		UWorld* World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			
			// Spawn projectile at the muzzle
			AProjectile* Projectile = World->SpawnActor< AProjectile >(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile) {
				// Set the projectile initial trajectory
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);

			}
		}
	}

}

// Called to bind functionality to input
void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayerCharacter::MoveRight);

	// Set up camera bindings
	PlayerInputComponent->BindAxis("Turn", this, &AMainPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainPlayerCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainPlayerCharacter::Interact);

	// Setup "action" bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainPlayerCharacter::StopJump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainPlayerCharacter::OnFire);
}

void AMainPlayerCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AMainPlayerCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMainPlayerCharacter::StartJump() {
	bPressedJump = true;
}

void AMainPlayerCharacter::StopJump() {
	bPressedJump = false;
}

void AMainPlayerCharacter::Interact()
{
	AMainPlayerController *PlayerContr = Cast<AMainPlayerController>(GetController());

	if (PlayerContr->OverlappingPickupActors.Num() > 0)
	{
		APickupActor *FirstPickupActor = PlayerContr->OverlappingPickupActors[0];
		IInteractionInterface *InteractionInterface = Cast<IInteractionInterface>(FirstPickupActor);
		if (InteractionInterface)
		{
			InteractionInterface->Execute_Interact(FirstPickupActor, PlayerContr);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character: nothing to throw away or pickup"));
	}
}
