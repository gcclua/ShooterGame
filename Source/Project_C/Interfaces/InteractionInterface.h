// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

UINTERFACE(Blueprintable)
class UInteractionInterface : public UInterface
{
    GENERATED_BODY()
};

class IInteractionInterface
{
    GENERATED_BODY()

  public:

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
    void Interact(AMainPlayerController *PlayerControllerRef);
};
