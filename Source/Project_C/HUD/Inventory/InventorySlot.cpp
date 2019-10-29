// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlot.h"
#include "InventorySystem/InventoryComponent.h"
#include "WidgetBlueprintLibrary.h"


void UInventorySlot::NativeConstruct()
{
    Super::NativeConstruct();
    
    SlotButton->OnClicked.AddDynamic(this, &UInventorySlot::OnSlotButtonClicked);
    SlotButton->OnHovered.AddDynamic(this, &UInventorySlot::OnSlotButtonHovered);
    SlotButton->OnUnhovered.AddDynamic(this, &UInventorySlot::OnSlotButtonUnHovered);

}

void UInventorySlot::UpdateSlot()
{
    // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UpdatingSlot"));
    if(Inventory->IsSlotEmpty(SlotIndex))
    {
        SlotButton->SetIsEnabled(false);
        SlotButton->SetToolTip(nullptr);
        TextAmount->SetVisibility(ESlateVisibility::Hidden);

        ItemIcon->SetVisibility(ESlateVisibility::Hidden);
        UButtonSlot *IconSlot = Cast<UButtonSlot>(ItemIcon->Slot);
        IconSlot->SetPadding(FMargin(0.0f));
    }
    else
    {
        SlotButton->SetIsEnabled(true);
        Inventory->GetItemAtIndex(SlotIndex, ItemName, Amount);
        FItemInfoStruct ItemInfo;
        Inventory->GetStructAtIndex(SlotIndex, ItemInfo);

        if(ItemInfo.bCanBeStacked)
        {
            TextAmount->SetText(FText::FromString(FString::Printf(TEXT("x%02d"), Amount)));
            TextAmount->SetVisibility(ESlateVisibility::HitTestInvisible);
        }
        else
        {
            TextAmount->SetVisibility(ESlateVisibility::Hidden);
        }

        if (Inventory->Slots[SlotIndex].TopLeftIndex == SlotIndex)
        {
            float MarginLeft = 1.0f * (ItemInfo.SlotWidth-1);
            float MarginTop = 1.0f * (ItemInfo.SlotHeight-1);
            float MarginRight = -64.0f * (ItemInfo.SlotWidth-1);
            float MarginBot = -64.0f * (ItemInfo.SlotHeight-1);

            UButtonSlot *IconSlot = Cast<UButtonSlot>(ItemIcon->Slot);
            // IconSlot->SetPadding(FMargin(MarginLeft, MarginTop, MarginRight, MarginBot));
            IconSlot->SetPadding(FMargin(0.0f, 0.0f, MarginRight, MarginBot));
            ItemIcon->SetBrushFromTexture(ItemInfo.Icon, false);
            ItemIcon->SetVisibility(ESlateVisibility::HitTestInvisible);
        }
    }
}

void UInventorySlot::OnSlotButtonClicked()
{
    ClickCount++;

    if(ClickCount > 1)
    {
        FItemInfoStruct ItemStruct;
        Inventory->GetStructAtIndex(SlotIndex, ItemStruct);
        if (ItemStruct.bCanBeUsed){
            ClickCount = 0;
            Inventory->UseItemAtIndex(SlotIndex);
        }
    }
}

void UInventorySlot::OnSlotButtonHovered()
{
    FItemInfoStruct ItemInfo;
    Inventory->GetStructAtIndex(SlotIndex, ItemInfo);

    FButtonStyle HoveredStyle = SlotButton->WidgetStyle;
    HoveredStyle.SetNormal(HoveredStyle.Hovered);

    int TopLeftIndex = Inventory->Slots[SlotIndex].TopLeftIndex;
    int tempIndex = 0;
	for (int i = 0; i < ItemInfo.SlotHeight; i++)
	{
		for(int j = 0; j < ItemInfo.SlotWidth; j++)
		{
			tempIndex = TopLeftIndex + j + Inventory->SlotsPerRow * i;
            if (tempIndex != SlotIndex)
                InventoryWidget->SlotWidgetsArray[tempIndex]->SlotButton->SetStyle(HoveredStyle);
		}
	}
}

void UInventorySlot::OnSlotButtonUnHovered()
{
    FItemInfoStruct ItemInfo;
    Inventory->GetStructAtIndex(SlotIndex, ItemInfo);

    FButtonStyle NormalStyle = SlotButton->WidgetStyle;

    int TopLeftIndex = Inventory->Slots[SlotIndex].TopLeftIndex;
    int tempIndex = 0;
	for (int i = 0; i < ItemInfo.SlotHeight; i++)
	{
		for(int j = 0; j < ItemInfo.SlotWidth; j++)
		{
			tempIndex = TopLeftIndex + j + Inventory->SlotsPerRow * i;
            if (tempIndex != SlotIndex)
                InventoryWidget->SlotWidgetsArray[tempIndex]->SlotButton->SetStyle(NormalStyle);
		}
	}
}

FReply UInventorySlot::NativeOnPreviewMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
    Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

    if (SlotButton->GetIsEnabled())
    {
        if (InMouseEvent.IsMouseButtonDown(FKey("RightMouseButton")))
        {
            InventoryWidget->OpenActionMenu(this);
            return FReply::Handled();
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Detecting Drag"));
            FEventReply DragReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, FKey("LeftMouseButton"));
            ClickCount++;
            return DragReply.NativeReply;
        }
    }
    else
    {
        return FReply::Handled();
    }
}

void UInventorySlot::NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NativeOnDragDetected"));

    UItemDrag *DragOperation = Cast<UItemDrag>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDrag::StaticClass()));
    
    UDraggedItem *DraggedItemWidget = CreateWidget<UDraggedItem>(this, DraggedItemClass);
    DraggedItemWidget->Update(SlotIndex, Inventory);

	DragOperation->DefaultDragVisual = DraggedItemWidget;
	DragOperation->Pivot = EDragPivot::TopLeft;
	// DragOperation->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	// DragOperation->Payload = this;
    DragOperation->DraggedSlot = this;
    DragOperation->bIsItem = true;
    DragOperation->bWasShiftDown = false;

	OutOperation = DragOperation;
}

bool UInventorySlot::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NativeOnDrop - Slot"));
    UItemDrag *DragOperation = Cast<UItemDrag>(InOperation);
    if (DragOperation)
    {
        if (DragOperation->DraggedSlot != this)
        {
            UInventorySlot *DroppedSlot = DragOperation->DraggedSlot;

            if (DragOperation->bWasShiftDown)
            {
                if (Inventory->SplitStackToIndex(DroppedSlot->SlotIndex, DroppedSlot->Amount/2, SlotIndex, false))
                    return true;
            }
            
            if (Inventory->CombineStacks(DroppedSlot->SlotIndex, SlotIndex))
                return true;
            
            return Inventory->SwapSlots(DroppedSlot->SlotIndex, SlotIndex);

        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}
