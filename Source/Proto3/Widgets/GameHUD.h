// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROTO3_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UWidget_PauseMenu* PauseMenu;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UImage* FadeImage;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UImage* Instructions;

	float InstructionsTime{8.0f};

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UImage* JournalUpdated;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UTextBlock* JournalUpdatedText;

	bool MonumentShowing{};

	bool Monument1Seen{};
	bool Monument2Seen{};

	float JournalTime{5.0f};
	float JournalTimer{};
	
public:
	UFUNCTION(BlueprintCallable)
	void EnableDisableMenu();

	UFUNCTION(BlueprintCallable)
	void FadeIn(float _time);
	
	UFUNCTION(BlueprintCallable)
	void FadeOut(float _time);

	UPROPERTY(VisibleAnywhere)
	float FadeInTimer{};
	UPROPERTY(VisibleAnywhere)
	float FadeOutTimer{};

	float LatestFadeTime{};
};
