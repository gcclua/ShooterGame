// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD/Inventory/InventoryWindow.h"
#include "MainGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_C_API UMainGameHUD : public UUserWidget
{
	GENERATED_BODY()

	public:

	virtual void NativeConstruct() override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	class AMainPlayerController *PlayerContr;

	UPROPERTY(meta = (BindWidget))
	class UInventoryWindow *InventoryWidget;

	UPROPERTY(meta = (BindWidget))
	class UThrowItemWindow *ThrowItemWidget;


	UFUNCTION(BlueprintCallable, Category = "MainWidgets")
	void InitializeMainWidgets();
	
};
