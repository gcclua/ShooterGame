// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemInfoStruct.h"

FItemInfoStruct::FItemInfoStruct()
{
    this->Name = FText::FromString("No Name");
    this->Description = FText::FromString("No Description");
    this->ItemRarityEnum = EItemRarityEnum::IR_Common;
    this->ItemCategoryEnum = EItemCategoryEnum::IC_Miscellaneous;
    this->Value = 1;
    this->bCanBeStacked = false;
    this->bCanBeUsed = false;
    this->UseText = FText::FromString("No Use Text");
    this->IternalName = FString(TEXT("noname"));
    this->bCanBeAssignedToHotkey = false;
    this->bItemClass = false;
    this->SlotWidth = 1;
    this->SlotHeight = 1;
}

FInventorySlotStruct::FInventorySlotStruct()
{
    this->ItemName = FName(TEXT("None"));
    this->Amount = 0;
    this->TopLeftIndex = -1;
}

FInventorySlotStruct::FInventorySlotStruct(FName ItemName, int32 Amount)
{
    this->ItemName = ItemName;
    this->Amount = Amount;
    this->TopLeftIndex = -1;
}
