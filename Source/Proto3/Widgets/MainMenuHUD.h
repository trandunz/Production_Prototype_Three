// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROTO3_API UMainMenuHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
};
