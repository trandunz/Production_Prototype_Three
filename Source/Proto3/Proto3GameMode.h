// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Monument.h"
#include "GameFramework/GameModeBase.h"
#include "Proto3GameMode.generated.h"

UCLASS(minimalapi)
class AProto3GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProto3GameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere)
	TArray<AMonument*> Monuments;
};



