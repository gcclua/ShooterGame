// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "Player/MainPlayerCharacter.h"
#include "Player/MainPlayerController.h"
#include "PickupActor.generated.h"

UCLASS()
class PROJECT_C_API APickupActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	APickupActor();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Main mesh component acting as root component.
	UPROPERTY(VisibleAnywhere, Category = "PickupActor")
	UStaticMeshComponent *MainMesh;

	// Pickup collision component.
	UPROPERTY(VisibleAnywhere, Category = "PickupActor")
	USphereComponent *PickupCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FName ItemNameToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	int Amount;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
    void Interact(AMainPlayerController *PlayerControllerRef);
    virtual void Interact_Implementation(AMainPlayerController *PlayerControllerRef) override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void LiveOrDie(bool bWasSuccessful, int RestAmount);

	// Overlap begin function for pickup collider
	UFUNCTION()
	void OnPickupOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	// Overlap end function for pickup collider
	UFUNCTION()
	void OnPickupOverlapEnd(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);
};
