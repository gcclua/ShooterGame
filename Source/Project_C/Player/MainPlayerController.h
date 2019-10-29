// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InventorySystem/InventoryComponent.h"
#include "InventorySystem/PickupActor.h"
#include "HUD/MainGameHUD.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECT_C_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:

	//Constructor
	AMainPlayerController();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:

	// Called to bind functionality to input
	// virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	class UInventoryComponent *Inventory;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<class APickupActor*> OverlappingPickupActors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HUD")
	TSubclassOf<class UMainGameHUD> MainHUDClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HUD")
	class UMainGameHUD *MainGameHUD;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void InitializeHUD();

	UFUNCTION(BlueprintCallable, Category = "InputController")
	void SetupInput();

	UFUNCTION(BlueprintCallable, Category = "InputController")
	void CenterCursor();

	UFUNCTION(BlueprintCallable, Category = "InputController")
	void SetInputGame();

	UFUNCTION(BlueprintCallable, Category = "InputController")
	void SetInputUI();

	UFUNCTION(BlueprintCallable, Category = "InputController")
	void ToggleInventory();



};
