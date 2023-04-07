// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Widget_PauseMenu.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Proto3/Proto3GameMode.h"

void UGameHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	bool isFading{};
	if (FadeInTimer > 0)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly{});
		isFading = true;
		FadeInTimer -= InDeltaTime;
		FadeImage->SetColorAndOpacity(FLinearColor{0,0,0,FadeInTimer / LatestFadeTime});
		
		if (FadeInTimer <= 0)
		{
			
			FadeOut(LatestFadeTime);
			isFading = false;
		}
	}
	if (FadeOutTimer > 0)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly{});
		isFading = true;
		FadeOutTimer -= InDeltaTime;
		FadeImage->SetColorAndOpacity(FLinearColor{0,0,0,FMath::Lerp(1.0f,0.0f, FadeOutTimer / LatestFadeTime)});

		if (FadeOutTimer <= 0)
		{
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly{});
			isFading = false;
		}
	}

	if (!isFading)
	{
		FadeImage->SetColorAndOpacity(FLinearColor{0,0,0,0});
	}
	
	// Starting instructions
	InstructionsTime -= InDeltaTime;
	if (InstructionsTime <= 0)
	{
		Instructions->SetVisibility(ESlateVisibility::Hidden);
		InstructionsTime = 0;
	}

	// Journal Updated UI
	if (auto* gamemode = Cast<AProto3GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		for (auto i : gamemode->Monuments)
		{
			if (i->MonumentNumber == 1 && i->IsSeen == true && Monument1Seen == false)
			{
				MonumentShowing = true;
				Monument1Seen = true;
				JournalTimer = JournalTime;
			}

			if (i->MonumentNumber == 2 && i->IsSeen == true && Monument2Seen == false)
			{
				MonumentShowing = true;
				Monument2Seen = true;
				JournalTimer = JournalTime;
			}
		}
	}

	if (MonumentShowing == true)
	{
		JournalUpdated->SetVisibility(ESlateVisibility::Visible);
		JournalUpdatedText->SetVisibility(ESlateVisibility::Visible);
		JournalTimer -= InDeltaTime;

		if (JournalTimer <= 0)
		{
			JournalUpdated->SetVisibility(ESlateVisibility::Hidden);
			JournalUpdatedText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
}

void UGameHUD::EnableDisableMenu()
{
	PauseMenu->EnableDisableMenu();
}

void UGameHUD::FadeIn(float _time)
{
	FadeImage->SetColorAndOpacity(FLinearColor{0,0,0,0});
	LatestFadeTime = _time;
	FadeInTimer = _time;
}

void UGameHUD::FadeOut(float _time)
{
	FadeImage->SetColorAndOpacity(FLinearColor{0,0,0,1});
	LatestFadeTime = _time;
	FadeOutTimer = _time;
}
