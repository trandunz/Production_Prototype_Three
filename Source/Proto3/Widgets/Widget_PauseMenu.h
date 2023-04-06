// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROTO3_API UWidget_PauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UImage* TreeImage;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UTextBlock* TreeText1;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UTextBlock* TreeText2;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UImage* ShipImage;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UTextBlock* ShipText1;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UTextBlock* ShipText2;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UTextBlock* ShipText3;

	UFUNCTION(BlueprintCallable)
	void EnableDisableMenu();
};
