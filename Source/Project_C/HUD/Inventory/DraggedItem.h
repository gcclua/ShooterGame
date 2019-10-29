// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySystem/ItemInfoStruct.h"
#include "OverlaySlot.h"
#include "DraggedItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_C_API UDraggedItem : public UUserWidget
{
	GENERATED_BODY()
	
	public:

	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	// class UInventoryComponent *Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	int Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	int SlotIndex;

	// Visual widgets

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *TextAmount;
	
	UPROPERTY(meta = (BindWidget))
	class UImage *ItemIcon;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void Update(int Index, UInventoryComponent *Inventory);
	
};
