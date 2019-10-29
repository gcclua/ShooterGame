// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "HUD/MainGameHUD.h"
#include "HUD/Inventory/InventoryWindow.h"
#include "HUD/Inventory/InventorySlot.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set default inventory values
	SlotsPerRow = 4;
	AmountOfSlots = 20;
	MaxStackSize = 99;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Slots.SetNum(AmountOfSlots, false);
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::IsBlockValid(int TopLeftIndex, int Height, int Width)
{
	bool bWidthValid = TopLeftIndex%SlotsPerRow + Width <= SlotsPerRow;
	bool bHeightValid = TopLeftIndex/SlotsPerRow + Height <= AmountOfSlots/SlotsPerRow;

	return bWidthValid && bHeightValid;
}

bool UInventoryComponent::IsBlockEmpty(int TopLeftIndex, int Height, int Width)
{
	bool bIsEmpty = false;

	if (IsBlockValid(TopLeftIndex, Height, Width))
	{
		bIsEmpty = true;
		int tempIndex = 0;
		for (int i = 0; i < Height; i++)
		{
			for(int j = 0; j < Width; j++)
			{
				tempIndex = TopLeftIndex + j + SlotsPerRow * i;
				if (Slots[tempIndex].TopLeftIndex != -1)
					bIsEmpty = false;
			}
		}
	}

	return bIsEmpty;
}

bool UInventoryComponent::IsBlockSwapEmpty(int TopLeftIndex, int Height, int Width, int IgnoreIndex)
{
	bool bIsEmpty = false;

	if (IsBlockValid(TopLeftIndex, Height, Width))
	{
		bIsEmpty = true;
		int tempIndex = 0;
		for (int i = 0; i < Height; i++)
		{
			for(int j = 0; j < Width; j++)
			{
				tempIndex = TopLeftIndex + j + SlotsPerRow * i;
				if (Slots[tempIndex].TopLeftIndex != -1 && Slots[tempIndex].TopLeftIndex != IgnoreIndex)
					bIsEmpty = false;
			}
		}
	}

	return bIsEmpty;
}

bool UInventoryComponent::GetBlockInfo(int TopLeftIndex, int &OutHeight, int &OutWidth)
{
	int tempIndex = 0;
	OutHeight = 0;
	OutWidth = 0;

	for (int i = TopLeftIndex; i < AmountOfSlots; i += SlotsPerRow)
	{
		if (Slots[i].TopLeftIndex == TopLeftIndex)
			OutHeight++;
		else
			break;
	}

	for(int j = TopLeftIndex%SlotsPerRow; j < SlotsPerRow; j++)
	{
		tempIndex = TopLeftIndex + j;
		if (tempIndex <AmountOfSlots && Slots[tempIndex].TopLeftIndex == TopLeftIndex)
			OutWidth++;
		else
			break;
	}

	return true;
}

bool UInventoryComponent::SetBlockReferences(int TopLeftIndex, int Height, int Width)
{
	if (IsBlockValid(TopLeftIndex, Height, Width))
	{
		int tempIndex = 0;
		for (int i = 0; i < Height; i++)
		{
			for(int j = 0; j < Width; j++)
			{
				tempIndex = TopLeftIndex + j + SlotsPerRow * i;
				Slots[tempIndex].TopLeftIndex = TopLeftIndex;
			}
		}
		return true;
	}
	return false;
}

bool UInventoryComponent::ClearBlockReferences(int TopLeftIndex, int Height, int Width)
{
	if (IsBlockValid(TopLeftIndex, Height, Width))
	{
		int tempIndex = 0;
		for (int i = 0; i < Height; i++)
		{
			for(int j = 0; j < Width; j++)
			{
				tempIndex = TopLeftIndex + j + SlotsPerRow * i;
				Slots[tempIndex].TopLeftIndex = -1;
			}
		}
		return true;
	}
	return false;
}

bool UInventoryComponent::IsSlotEmpty(int SlotIndex)
{
	bool bIsEmpty = Slots[SlotIndex].TopLeftIndex == -1;
	return bIsEmpty;
}

bool UInventoryComponent::SearchEmptyBlock(int Height, int Width, int &OutFoundTLI) //TLI = TopLeftIndex
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (IsBlockEmpty(i, Height, Width))
		{
			OutFoundTLI = i;
			return true;
		}
	}
	return false;
}

bool UInventoryComponent::SearchFreeStack(FName ItemName, int &OutFoundTLI) //TLI = TopLeftIndex
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if ((Slots[i].ItemName == ItemName) && (Slots[i].Amount < MaxStackSize))
		{
			OutFoundTLI = i;
			return true;
		}
	}
	return false;
}

bool UInventoryComponent::GetStructAtIndex(int SlotIndex, FItemInfoStruct &OutItemInfoAtTLI) //TLI = TopLeftIndex
{
	int MainIndex = Slots[SlotIndex].TopLeftIndex;

	if (MainIndex != -1)
	{
		FItemInfoStruct *row =
			ItemTable->FindRow<FItemInfoStruct>(Slots[MainIndex].ItemName, FString(""));

		if (row)
		{
			OutItemInfoAtTLI = *row;
			return true;
		}
	}
	return false;
}

bool UInventoryComponent::GetItemAtIndex(int SlotIndex, FName &ItemNameAtTLI, int &AmountAtTLI) //TLI = TopLeftIndex
{
	int MainIndex = Slots[SlotIndex].TopLeftIndex;

	if (MainIndex != -1)
	{
		FItemInfoStruct *row =
			ItemTable->FindRow<FItemInfoStruct>(Slots[MainIndex].ItemName, FString(""));

		if (row)
		{
			ItemNameAtTLI = Slots[MainIndex].ItemName;
			AmountAtTLI = Slots[MainIndex].Amount;
			return true;
		}
	}

	return false;
}

bool UInventoryComponent::AddToIndex(int TopLeftIndex, FName ItemName, int Height, int Width, int AmountToAdd, int &RestAmount) //TLI = TopLeftIndex
{
	FName ItemNameAtTLI;
	int AmountAtTLI;
	//If there is smth in slot
	if (GetItemAtIndex(TopLeftIndex, ItemNameAtTLI, AmountAtTLI))
	{
		if (ItemNameAtTLI != ItemName || AmountAtTLI >= MaxStackSize)
		{
			RestAmount = AmountToAdd;
			return false;
		}
		AmountToAdd += AmountAtTLI;
	}

	if (AmountToAdd <= MaxStackSize)
	{
		Slots[TopLeftIndex] = FInventorySlotStruct(ItemName, AmountToAdd);
		RestAmount = 0;
	}
	else
	{
		Slots[TopLeftIndex] = FInventorySlotStruct(ItemName, MaxStackSize);
		RestAmount = AmountToAdd - MaxStackSize;
	}

	SetBlockReferences(TopLeftIndex, Height, Width);
	UpdateBlockVisual(TopLeftIndex, Height, Width);

	return true;
}

bool UInventoryComponent::AddItem(FName ItemName, int AmountToAdd, int &RestAmount) //TLI = TopLeftIndex
{
	FItemInfoStruct *row =
		ItemTable->FindRow<FItemInfoStruct>(ItemName, FString(""));

	if (!row)
	{
		RestAmount = AmountToAdd;
		return false;
	}

	int FoundTLI;

	if (row->bCanBeStacked)
	{
		if (!SearchFreeStack(ItemName, FoundTLI))
		{
			if (!SearchEmptyBlock(row->SlotHeight, row->SlotWidth, FoundTLI))
			{
				RestAmount = AmountToAdd;
				return false;
			}
		}
		if (AddToIndex(FoundTLI, ItemName, row->SlotHeight, row->SlotWidth, AmountToAdd, RestAmount) && RestAmount == 0)
			return true;
		else
			return AddItem(ItemName, RestAmount, RestAmount);
	}
	else
	{
		if (!SearchEmptyBlock(row->SlotHeight, row->SlotWidth, FoundTLI))
		{
			RestAmount = AmountToAdd;
			return false;
		}
		int FakeRestAmount;
		AddToIndex(FoundTLI, ItemName, row->SlotHeight, row->SlotWidth, 1, FakeRestAmount);
		if(AmountToAdd > 1)
		{
			AddItem(ItemName, AmountToAdd-1, RestAmount);
			return true;
		}
		else
		{
			RestAmount = 0;
			return true;
		}
	}

	return false;
}

bool UInventoryComponent::RemoveItemAtIndex(int SlotIndex, int RemoveAmount)
{
	int MainIndex = Slots[SlotIndex].TopLeftIndex;

	if (!IsSlotEmpty(MainIndex) && RemoveAmount > 0)
	{
		FName ItemName;
		int Amount;
		FItemInfoStruct ItemInfo;

		GetItemAtIndex(MainIndex, ItemName, Amount);
		GetStructAtIndex(MainIndex, ItemInfo);

		if (RemoveAmount >= Amount)
		{
			Slots[MainIndex] = FInventorySlotStruct();
			ClearBlockReferences(MainIndex, ItemInfo.SlotHeight, ItemInfo.SlotWidth);
		}
		else
		{
			Slots[MainIndex].Amount = Amount - RemoveAmount;
		}
		UpdateBlockVisual(MainIndex, ItemInfo.SlotHeight, ItemInfo.SlotWidth);
		return true;
	}

	return false;
}

bool UInventoryComponent::SplitStackToIndex(int SlotIndex, int SplitAmount, int SplitIndex, bool bToFreeSlot)
{
	int MainSlotIndex = Slots[SlotIndex].TopLeftIndex;
	int MainSplitIndex;

	int AmountAtMain;
	FName ItemNameAtMain;
	FItemInfoStruct ItemInfoAtMain;

	bool check1 = GetItemAtIndex(MainSlotIndex, ItemNameAtMain, AmountAtMain) && AmountAtMain > SplitAmount;
	bool check2 = GetStructAtIndex(MainSlotIndex, ItemInfoAtMain) && ItemInfoAtMain.bCanBeStacked && SplitAmount > 0;

	if (check1 && check2)
	{
		int RestAmount = 0;
		if (bToFreeSlot)
		{
			if (SearchEmptyBlock(ItemInfoAtMain.SlotHeight, ItemInfoAtMain.SlotWidth, MainSplitIndex))
			{
				AddToIndex(MainSplitIndex, ItemNameAtMain, ItemInfoAtMain.SlotHeight, ItemInfoAtMain.SlotWidth, SplitAmount, RestAmount);
				RemoveItemAtIndex(MainSlotIndex, SplitAmount);
				return true;
			}
			return false;
		}

		MainSplitIndex = Slots[SlotIndex].TopLeftIndex;
		int AmountAtSecond;
		FName SecondItemName;

		if (GetItemAtIndex(MainSplitIndex, SecondItemName, AmountAtSecond) && ItemNameAtMain==SecondItemName)
		{
			AddToIndex(MainSplitIndex, ItemNameAtMain, ItemInfoAtMain.SlotHeight, ItemInfoAtMain.SlotWidth, SplitAmount, RestAmount);
			RemoveItemAtIndex(MainSlotIndex, SplitAmount-RestAmount);
			return true;
		}
	}
	return false;
}

bool UInventoryComponent::CombineStacks(int SlotIndex1, int SlotIndex2)
{    
	int MainIndex1 = Slots[SlotIndex1].TopLeftIndex;
	int MainIndex2 = Slots[SlotIndex2].TopLeftIndex;

	int Amount1;
	FName ItemName1;

	if(!GetItemAtIndex(MainIndex1,ItemName1,Amount1) || Amount1>=MaxStackSize || IsSlotEmpty(SlotIndex2))
		return false;

	FItemInfoStruct ItemInfo1;
	FItemInfoStruct ItemInfo2;

	GetStructAtIndex(MainIndex1, ItemInfo1);
	GetStructAtIndex(MainIndex2, ItemInfo2);

	if (!ItemInfo1.bCanBeStacked || !ItemInfo2.bCanBeStacked)
		return false;

	int RestAmount;
	bool bSuccess = AddToIndex(MainIndex2, ItemName1, ItemInfo1.SlotHeight, ItemInfo1.SlotWidth, Amount1, RestAmount);

	if (RestAmount > 0)
	{
		Amount1 -= RestAmount;
		RemoveItemAtIndex(MainIndex1, Amount1);
		if (Amount1 == 0) {
			return false;
		}
		return bSuccess;
	}
	else
	{
		RemoveItemAtIndex(MainIndex1, Amount1);
		return bSuccess;
	}
}

bool UInventoryComponent::SwapSlots(int SlotIndex1, int SlotIndex2)
{
	int MainIndex1 = Slots[SlotIndex1].TopLeftIndex;
	int MainIndex2 = Slots[SlotIndex2].TopLeftIndex;
	FItemInfoStruct ItemInfo;
	GetStructAtIndex(MainIndex1, ItemInfo);

	if (IsBlockSwapEmpty(SlotIndex2, ItemInfo.SlotHeight, ItemInfo.SlotWidth, MainIndex1))
	{
		int RestAmount;
		FName ItemNameAt1 = Slots[MainIndex1].ItemName;
		int AmountAt1 = Slots[MainIndex1].Amount;
		RemoveItemAtIndex(MainIndex1, Slots[MainIndex1].Amount);
		AddToIndex(SlotIndex2, ItemNameAt1, ItemInfo.SlotHeight, ItemInfo.SlotWidth, AmountAt1, RestAmount);
	}
	else
	{
		/* code */
	}

	return true;
}

void UInventoryComponent::UseItemAtIndex(int SlotIndex)
{
	int MainIndex = Slots[SlotIndex].TopLeftIndex;

	FString UsedItemName = Slots[MainIndex].ItemName.ToString();
	FString UsedText = TEXT("Used Item: ");
	UsedText += UsedItemName;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, UsedText);
	RemoveItemAtIndex(MainIndex, 1);
}

void UInventoryComponent::UpdateBlockVisual(int TopLeftIndex, int Height, int Width)
{
	if (IsBlockValid(TopLeftIndex, Height, Width))
	{
		AMainPlayerController *PlayerContr = Cast<AMainPlayerController>(GetOwner());
		UInventoryWindow *InventoryWindow = PlayerContr->MainGameHUD->InventoryWidget;
		int tempIndex = 0;
		for (int i = 0; i < Height; i++)
		{
			for(int j = 0; j < Width; j++)
			{
				tempIndex = TopLeftIndex + j + SlotsPerRow * i;
				InventoryWindow->SlotWidgetsArray[tempIndex]->UpdateSlot();
			}
		}
	}
}

