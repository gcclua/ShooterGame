// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemInfoStruct.h"
#include "HUD/Inventory/InventorySlot.h"
#include "HUD/Inventory/InventoryWindow.h"
#include "Player/MainPlayerController.h"
#include "InventoryComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_C_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int AmountOfSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventorySlotStruct> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	class APlayerController *PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTables")
	class UDataTable *ItemTable;

	//Work with grid

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridControl")
	int SlotsPerRow;

	//returns true if all slots in block are empty
	UFUNCTION(BlueprintCallable, Category = "GridControl")
	bool IsBlockValid(int TopLeftIndex, int Height, int Width);

	UFUNCTION(BlueprintCallable, Category = "GridControl")
	bool IsBlockEmpty(int TopLeftIndex, int Height, int Width);

	UFUNCTION(BlueprintCallable, Category = "GridControl")
	bool IsBlockSwapEmpty(int TopLeftIndex, int Height, int Width, int IgnoreIndex);

	UFUNCTION(BlueprintCallable, Category = "GridControl")
	bool GetBlockInfo(int TopLeftIndex, int &OutHeight, int &OutWeight);

	UFUNCTION(BlueprintCallable, Category = "GridControl")
	bool SetBlockReferences(int TopLeftIndex, int Height, int Width);

	UFUNCTION(BlueprintCallable, Category = "GridControl")
	bool ClearBlockReferences(int TopLeftIndex, int Height, int Width);

	//Inventory functions
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsSlotEmpty(int SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool SearchEmptyBlock(int Height, int Width, int &OutFoundIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool SearchFreeStack(FName ItemName, int &OutFoundIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool GetStructAtIndex(int SlotIndex, FItemInfoStruct &OutItemInfo);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool GetItemAtIndex(int SlotIndex, FName &OutItemName, int &OutAmount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddToIndex(int SlotIndex, FName ItemName, int Height, int Width, int Amount, int &RestAmount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(FName ItemName, int Amount, int &RestAmount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItemAtIndex(int SlotIndex, int RemoveAmount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool SplitStackToIndex(int SlotIndex, int SplitAmount, int SplitIndex, bool bToFreeSlot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CombineStacks(int SlotIndex1, int SlotIndex2);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool SwapSlots(int SlotIndex1, int SlotIndex2);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItemAtIndex(int SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdateBlockVisual(int TopLeftIndex, int Height, int Width);


	// UI properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	class UInventoryWindow *InventoryWidget;

	//Testing functional
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	class UInventorySlot *SlotWidget;

	// UFUNCTION(BlueprintCallable, Category = "Inventory")
	// void ChangeTestTextOnSlot();
};
