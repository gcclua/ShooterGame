// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryActionMenu.h"
#include "InventorySystem/InventoryComponent.h"
#include "Player/MainPlayerController.h"

void UInventoryActionMenu::NativeConstruct()
{
    Super::NativeConstruct();

    UseButton->OnClicked.AddDynamic(this, &UInventoryActionMenu::OnUseButtonClicked);
    ThrowButton->OnClicked.AddDynamic(this, &UInventoryActionMenu::OnThrowButtonClicked);
    SplitButton->OnClicked.AddDynamic(this, &UInventoryActionMenu::OnSplitButtonClicked);
    CancelButton->OnClicked.AddDynamic(this, &UInventoryActionMenu::OnCancelButtonClicked);
}

void UInventoryActionMenu::Update(int NewSlotIndex)
{
    SlotIndex = NewSlotIndex;
    Inventory->GetItemAtIndex(SlotIndex, ItemName, Amount);
    FItemInfoStruct ItemInfo;
    Inventory->GetStructAtIndex(SlotIndex, ItemInfo);

    if(ItemInfo.ItemCategoryEnum == EItemCategoryEnum::IC_QuestItems)
    {
        ThrowButton->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        ThrowButton->SetVisibility(ESlateVisibility::Visible);
    }

    if (ItemInfo.bCanBeStacked && Amount > 1)
    {
        SplitButton->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        SplitButton->SetVisibility(ESlateVisibility::Collapsed);
    }

    if (ItemInfo.bCanBeUsed) {
        UseText->SetText(ItemInfo.UseText);
        UseButton->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        UseButton->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UInventoryActionMenu::OnUseButtonClicked()
{
    Inventory->UseItemAtIndex(SlotIndex);
    SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryActionMenu::OnThrowButtonClicked()
{
    ThrowItemWidget->CallThrowItem(SlotIndex);
    SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryActionMenu::OnSplitButtonClicked()
{
    Inventory->SplitStackToIndex(SlotIndex, Amount/2, 1, true);
    SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryActionMenu::OnCancelButtonClicked()
{
    SetVisibility(ESlateVisibility::Hidden);
}
