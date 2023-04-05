// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Widget_PauseMenu.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

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
