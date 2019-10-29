// Fill out your copyright notice in the Description page of Project Settings.

#include "DraggedItem.h"
#include "InventorySystem/InventoryComponent.h"


void UDraggedItem::Update(int Index, UInventoryComponent *Inventory)
{
    FItemInfoStruct ItemInfo;
    Inventory->GetStructAtIndex(Index, ItemInfo);
    Inventory->GetItemAtIndex(Index, ItemName, Amount);

    float MarginLeft = 1.0f * (ItemInfo.SlotWidth-1);
    float MarginTop = 1.0f * (ItemInfo.SlotHeight-1);
    float MarginRight = -64.0f * (ItemInfo.SlotWidth-1);
     float MarginBot = -64.0f * (ItemInfo.SlotHeight-1);

    UOverlaySlot *IconSlot = Cast<UOverlaySlot>(ItemIcon->Slot);
    IconSlot->SetPadding(FMargin(0.0f, 0.0f, MarginRight, MarginBot));

    ItemIcon->SetBrushFromTexture(ItemInfo.Icon, false);
    if (ItemInfo.bCanBeStacked)
    {
        TextAmount->SetText(FText::FromString(FString::Printf(TEXT("x%02d"), Amount)));
    }
    else
    {
        TextAmount->SetVisibility(ESlateVisibility::Hidden);
    }
    
}

