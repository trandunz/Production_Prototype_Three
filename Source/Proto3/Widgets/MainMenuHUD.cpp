// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (auto* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		controller->SetInputMode(FInputModeUIOnly{});
		controller->bShowMouseCursor = true;
	}
}
