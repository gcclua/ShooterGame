// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemInfoStruct.generated.h"

UENUM(BlueprintType)
enum class EItemRarityEnum : uint8
{
	IR_Common UMETA(DisplayName = "Common"),
	IR_Rare UMETA(DisplayName = "Rare"),
	IR_Epic UMETA(DisplayName = "Epic")
};

UENUM(BlueprintType)
enum class EItemCategoryEnum : uint8
{
	IC_Miscellaneous UMETA(DisplayName = "Miscellaneous"),
	IC_Consumables UMETA(DisplayName = "Consumables"),
	IC_Equipment UMETA(DisplayName = "Equipment"),
	IC_Weapon UMETA(DisplayName = "Weapon"),
	IC_QuestItems UMETA(DisplayName = "QuestItems"),
	IC_Readables UMETA(DisplayName = "Readables")
};

USTRUCT(BlueprintType)
struct FItemInfoStruct : public FTableRowBase
{
	GENERATED_BODY()

  public:
	FItemInfoStruct();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D *Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EItemRarityEnum ItemRarityEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EItemCategoryEnum ItemCategoryEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeStacked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText UseText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString IternalName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeAssignedToHotkey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotHeight;
};

USTRUCT(BlueprintType)
struct FInventorySlotStruct
{
	GENERATED_BODY()

  public:
	FInventorySlotStruct();

	FInventorySlotStruct(FName ItemName, int32 Amount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TopLeftIndex;
};
