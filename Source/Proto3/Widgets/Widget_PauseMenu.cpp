// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_PauseMenu.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Proto3/Proto3GameMode.h"

void UWidget_PauseMenu::EnableDisableMenu()
{
	if (GetVisibility() == ESlateVisibility::Hidden)
	{
		SetVisibility(ESlateVisibility::Visible);

		if (auto* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (auto* gamemode = Cast<AProto3GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				for (auto i : gamemode->Monuments)
				{
					if (i->MonumentNumber == 1 && i->IsSeen == true)
					{
						TreeImage->SetVisibility(ESlateVisibility::Visible);
						TreeText1->SetVisibility(ESlateVisibility::Visible);
						TreeText2->SetVisibility(ESlateVisibility::Visible);
					}

					if (i->MonumentNumber == 2 && i->IsSeen == true)
					{
						ShipImage->SetVisibility(ESlateVisibility::Visible);
						ShipText1->SetVisibility(ESlateVisibility::Visible);
						ShipText2->SetVisibility(ESlateVisibility::Visible);
						ShipText3->SetVisibility(ESlateVisibility::Visible);
					}
				}
			}
			
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
