// Fill out your copyright notice in the Description page of Project Settings.

#include "ThrowItemWindow.h"
#include "InventorySystem/InventoryComponent.h"
#include "Player/MainPlayerController.h"

void UThrowItemWindow::NativeConstruct()
{
    Super::NativeConstruct();

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ThrowItemWindowRebuilt"));
    PlayerContr = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
    Inventory = PlayerContr->Inventory;

    PlusButton->OnClicked.AddDynamic(this, &UThrowItemWindow::OnPlusButtonClicked);
    MinusButton->OnClicked.AddDynamic(this, &UThrowItemWindow::OnMinusButtonClicked);
    ConfirmButton->OnClicked.AddDynamic(this, &UThrowItemWindow::OnConfirmButtonClicked);
    CancelButton->OnClicked.AddDynamic(this, &UThrowItemWindow::OnCancelButtonClicked);

    PlusButton->OnPressed.AddDynamic(this, &UThrowItemWindow::OnPlusButtonPressed);
    PlusButton->OnReleased.AddDynamic(this, &UThrowItemWindow::OnPlusButtonReleased);
    MinusButton->OnPressed.AddDynamic(this, &UThrowItemWindow::OnMinusButtonPressed);
    MinusButton->OnReleased.AddDynamic(this, &UThrowItemWindow::OnMinusButtonReleased);
}

void UThrowItemWindow::CallThrowItem(int Index)
{
    SlotIndex = Index;
    FName ItemName;
    FItemInfoStruct ItemInfo;
    ThrowCount = 0;

    Inventory->GetItemAtIndex(SlotIndex,ItemName,MaxAmount);
    Inventory->GetStructAtIndex(SlotIndex, ItemInfo);

    if (ItemInfo.bCanBeStacked && MaxAmount > 1) 
    {
        ItemNameText->SetText(FText::FromString(
            FString::Printf(TEXT("%sx%02d"),*ItemName.ToString(), MaxAmount)));
        ItemIcon->SetBrushFromTexture(ItemInfo.Icon, false);
        CountText->SetText(FText::FromString(FString::Printf(TEXT("%02d"), ThrowCount)));

        // Inventory->InventoryWidget->SlotPanel->SetIsEnabled(false);
        SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        Inventory->RemoveItemAtIndex(SlotIndex, 1);
    }
}

void UThrowItemWindow::OnPlusButtonClicked()
{
    ClickCount++;

    FTimerHandle handle;
    GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
        ClickCount = 0;
    }, 0.3f, 0);

    if(ClickCount > 1)
    {
        ClickCount = 0;
        ThrowCount = MaxAmount;
        CountText->SetText(FText::FromString(FString::Printf(TEXT("%02d"), ThrowCount)));
    }
    else
    {
        ThrowCount++;
        if (ThrowCount > MaxAmount)
            ThrowCount = MaxAmount;
        CountText->SetText(FText::FromString(FString::Printf(TEXT("%02d"), ThrowCount)));
    }
}

void UThrowItemWindow::OnMinusButtonClicked()
{
    ClickCount++;

    FTimerHandle handle;
    GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
        ClickCount = 0;
    }, 0.3f, 0);

    if(ClickCount > 1)
    {
        ClickCount = 0;
        ThrowCount = 1;
        CountText->SetText(FText::FromString(FString::Printf(TEXT("%02d"), ThrowCount)));
    }
    else
    {
        ThrowCount--;
        if (ThrowCount < 1)
            ThrowCount = 1;
        CountText->SetText(FText::FromString(FString::Printf(TEXT("%02d"), ThrowCount)));
    }
}

void UThrowItemWindow::OnConfirmButtonClicked()
{
    if (ThrowCount > 0)
    {
        Inventory->RemoveItemAtIndex(SlotIndex, ThrowCount);
    }
        OnCancelButtonClicked();
}

void UThrowItemWindow::OnCancelButtonClicked()
{
    // Inventory->InventoryWidget->SlotPanel->SetIsEnabled(true);
    SetVisibility(ESlateVisibility::Hidden);
}

FTimerHandle TimerHandle;

void UThrowItemWindow::OnPlusButtonPressed()
{
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {
        ThrowCount++;
        if (ThrowCount > MaxAmount)
            ThrowCount = MaxAmount;
        CountText->SetText(FText::FromString(FString::Printf(TEXT("%02d"), ThrowCount)));
    }, 0.2f, 1);
}

void UThrowItemWindow::OnPlusButtonReleased()
{
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UThrowItemWindow::OnMinusButtonPressed()
{
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {
        ThrowCount--;
        if (ThrowCount < 1)
            ThrowCount = 1;
        CountText->SetText(FText::FromString(FString::Printf(TEXT("%02d"), ThrowCount)));
    }, 0.2f, 1);
}

void UThrowItemWindow::OnMinusButtonReleased()
{
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
