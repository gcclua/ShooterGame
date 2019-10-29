// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySystem/ItemInfoStruct.h"
#include "HUD/Inventory/ThrowItemWindow.h"
#include "InventoryActionMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_C_API UInventoryActionMenu : public UUserWidget
{
	GENERATED_BODY()

	public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	class UInventoryComponent *Inventory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	class UThrowItemWindow *ThrowItemWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	int SlotIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	FName ItemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	int Amount;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void Update(int NewSlotIndex);

	// Visual widgets

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *UseText;

	UPROPERTY(meta = (BindWidget))
	class UButton *UseButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *ThrowButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *SplitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *CancelButton;

	//Events

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnUseButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnThrowButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnSplitButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnCancelButtonClicked();
};
