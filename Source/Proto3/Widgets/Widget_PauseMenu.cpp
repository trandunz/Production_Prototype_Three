// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_PauseMenu.h"
#include "Kismet/GameplayStatics.h"

void UWidget_PauseMenu::EnableDisableMenu()
{
	if (GetVisibility() == ESlateVisibility::Hidden)
	{
		SetVisibility(ESlateVisibility::Visible);

		if (auto* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			//controller->SetInputMode(FInputModeUIOnly{});
			controller->SetInputMode(FInputModeGameAndUI{});
			
			controller->bShowMouseCursor = true;

			controller->Pause();
		}
	}
	else
	{
		if (auto* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			controller->bShowMouseCursor = false;
			controller->SetInputMode(FInputModeGameOnly{});

			controller->SetPause(false);
		}

		SetVisibility(ESlateVisibility::Hidden);
	}
}