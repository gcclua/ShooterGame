// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameHUD.h"
#include "Player/MainPlayerController.h"


void UMainGameHUD::NativeConstruct()
{
    Super::NativeConstruct();

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UMainGameHUDRebuilt"));
    PlayerContr = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
}

void UMainGameHUD::InitializeMainWidgets()
{

}
