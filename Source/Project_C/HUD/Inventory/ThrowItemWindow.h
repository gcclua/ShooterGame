// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySystem/ItemInfoStruct.h"
#include "ThrowItemWindow.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_C_API UThrowItemWindow : public UUserWidget
{
	GENERATED_BODY()
	
	public:

 	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	class AMainPlayerController *PlayerContr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	class UInventoryComponent *Inventory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int SlotIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int MaxAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int ThrowCount;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int ClickCount;

	// Visual widgets

	UPROPERTY(meta = (BindWidget))
	class UImage *ItemIcon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ItemNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *CountText;

	UPROPERTY(meta = (BindWidget))
	class UButton *MinusButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *PlusButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *CancelButton;

	UFUNCTION(BlueprintCallable, Category = "ThrowItem")
	void CallThrowItem(int Index);

	// Events

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnPlusButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnMinusButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnConfirmButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnCancelButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnPlusButtonPressed();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnPlusButtonReleased();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnMinusButtonPressed();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnMinusButtonReleased();
};
