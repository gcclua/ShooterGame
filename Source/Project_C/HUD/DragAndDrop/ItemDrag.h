// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "HUD/Inventory/InventorySlot.h"
#include "ItemDrag.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_C_API UItemDrag : public UDragDropOperation
{
	GENERATED_BODY()
	
	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	class UInventorySlot *DraggedSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	bool bIsItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	bool bWasShiftDown;

};
