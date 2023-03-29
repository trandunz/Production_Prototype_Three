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


public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UWidget_PauseMenu* PauseMenu;

public:
	UFUNCTION(BlueprintCallable)
	void EnableDisableMenu();
	
};
