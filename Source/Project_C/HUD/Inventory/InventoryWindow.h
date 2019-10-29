// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD/MainGameHUD.h"
#include "HUD/Inventory/InventorySlot.h"
#include "HUD/Inventory/InventoryActionMenu.h"
#include "UniformGridPanel.h"
#include "UniformGridSlot.h"
#include "ScrollBox.h"
#include "WidgetLayoutLibrary.h"
#include "InventoryWindow.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_C_API UInventoryWindow : public UUserWidget
{
	GENERATED_BODY()

	public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	class AMainPlayerController *PlayerContr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	class UInventoryComponent *Inventory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HUD")
	class UMainGameHUD *MainGameHUD;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TSubclassOf<class UInventorySlot> SlotClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TArray<class UInventorySlot*> SlotWidgetsArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int SlotsPerRow;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	bool bIsOpened;

	// Visual widgets

	UPROPERTY(meta = (BindWidget))
	class UScrollBox *ScrollBox;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel *SlotPanel;

	UPROPERTY(meta = (BindWidget))
	class UInventoryActionMenu *ActionMenu;

	UFUNCTION(BlueprintCallable, Category = "Slot")
	void GenerateSlots();

	// Mouse Events and clicking events

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OpenActionMenu(UInventorySlot *EvokerSlot);
	
};
