// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "Button.h"
#include "ButtonSlot.h"
#include "SlateTypes.h"
#include "Image.h"
#include "InventoryWindow.h"
#include "HUD/DragAndDrop/ItemDrag.h"
#include "DraggedItem.h"
#include "InventorySystem/ItemInfoStruct.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_C_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

	public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	class UInventoryComponent *Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	class UInventoryWindow *InventoryWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Slot")
	TSubclassOf<class UDraggedItem> DraggedItemClass;

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
	class UButton *SlotButton;
	
	UPROPERTY(meta = (BindWidget))
	class UImage *ItemIcon;
	
	UFUNCTION(BlueprintCallable, Category = "Slot")
	void UpdateSlot();

	// Mouse Events and clicking events

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	int ClickCount;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnSlotButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnSlotButtonHovered();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnSlotButtonUnHovered();

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent);

	virtual void NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation);
	virtual bool NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation);
};
