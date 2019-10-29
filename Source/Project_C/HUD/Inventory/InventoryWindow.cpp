// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWindow.h"
#include "InventorySystem/InventoryComponent.h"
#include "Player/MainPlayerController.h"

void UInventoryWindow::NativeConstruct()
{
    Super::NativeConstruct();

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InventoryWindowRebuilt"));
    PlayerContr = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());

    this->SetVisibility(ESlateVisibility::Hidden);
    this->bIsOpened = false;
    MainGameHUD = PlayerContr->MainGameHUD;
    Inventory = PlayerContr->Inventory;

    ActionMenu->Inventory = Inventory;
    ActionMenu->ThrowItemWidget = MainGameHUD->ThrowItemWidget;

    GenerateSlots();
}

void UInventoryWindow::GenerateSlots()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GeneratingSlots"));
    SlotPanel->ClearChildren();
    SlotWidgetsArray.Empty();
    for (int i = 0; i < Inventory->AmountOfSlots; i++)
    {
        UInventorySlot *NewSlot = CreateWidget<UInventorySlot>
            (Cast<AMainPlayerController>(Inventory->GetOwner()), SlotClass);
        SlotWidgetsArray.Add(NewSlot);

        UUniformGridSlot *GridSlot = SlotPanel->AddChildToUniformGrid(NewSlot);
        GridSlot->SetRow(FMath::RoundToZero((float)i / (float)SlotsPerRow));
        GridSlot->SetColumn(i%SlotsPerRow);
        
        NewSlot->SlotIndex = i;
        NewSlot->Inventory = Inventory;
        NewSlot->InventoryWidget = this;
        NewSlot->UpdateSlot();
    }
}

void UInventoryWindow::OpenActionMenu(UInventorySlot *EvokerSlot)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OpenActionMenu"));
    UUniformGridSlot *GridSlot = UWidgetLayoutLibrary::SlotAsUniformGridSlot(EvokerSlot);
    float PosX = GridSlot->Column * 64;
    float PosY = GridSlot->Row*64 - ScrollBox->GetScrollOffset()/1.5f;
    FMath::Clamp(PosY, 0.0f, 200.0f);
    FVector2D *Pos = new FVector2D(PosX, PosY);
    ActionMenu->SetRenderTranslation(*Pos);
    ActionMenu->Update(EvokerSlot->SlotIndex);
    ActionMenu->SetVisibility(ESlateVisibility::Visible);
}

