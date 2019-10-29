// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"
#include "WidgetBlueprintLibrary.h"

// Sets default values for this controller's properties
AMainPlayerController::AMainPlayerController()
    :
    APlayerController()
{
	// Set default inventory values
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
    AddOwnedComponent(Inventory);

	// ...
}

// Called when the game starts or when spawned
void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
    InitializeHUD();
    SetupInput();
}

void AMainPlayerController::SetupInput()
{
    EnableInput(this);
    check(InputComponent);
    InputComponent->BindAction("Inventory", IE_Pressed, this, &AMainPlayerController::ToggleInventory);
}

void AMainPlayerController::CenterCursor()
{
    const ULocalPlayer* LocalPlayer = GetLocalPlayer();
    if( LocalPlayer && LocalPlayer->ViewportClient )
    {
        FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
        if( Viewport )
        {
            FVector2D ViewportSize;
            LocalPlayer->ViewportClient->GetViewportSize(ViewportSize);
            int32 X = static_cast<int32>(ViewportSize.X * 0.5f);
            int32 Y = static_cast<int32>(ViewportSize.Y * 0.5f);
            Viewport->SetMouse(X, Y);
        }
    }
}

void AMainPlayerController::SetInputGame()
{
    bShowMouseCursor = false;
    SetInputMode(FInputModeGameOnly());
}

void AMainPlayerController::SetInputUI()
{
    bShowMouseCursor = true;
    SetInputMode(FInputModeGameAndUI());
    CenterCursor();

}
 
void AMainPlayerController::ToggleInventory()
{
    if(MainGameHUD->InventoryWidget->bIsOpened)
    {
        MainGameHUD->InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
        MainGameHUD->InventoryWidget->bIsOpened = false;
        SetInputGame();
    }
    else
    {
        MainGameHUD->InventoryWidget->SetVisibility(ESlateVisibility::Visible);
        MainGameHUD->InventoryWidget->bIsOpened = true;
        SetInputUI();
    }
}

// // Called to bind functionality to input
// void AMainPlayerController::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);

// 	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainPlayerCharacter::Interact);
// }

void AMainPlayerController::InitializeHUD()
{
    MainGameHUD = CreateWidget<UMainGameHUD>(this, MainHUDClass);
    MainGameHUD->AddToViewport(0);
}
