// Copyright Epic Games, Inc. All Rights Reserved.

#include "Proto3GameMode.h"
#include "Proto3Character.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AProto3GameMode::AProto3GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_SandSailPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AProto3GameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> monuments{};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonument::StaticClass(), monuments);

	for(auto monument : monuments)
	{
		Monuments.Add(Cast<AMonument>(monument));
	}
}

void AProto3GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	bool allMonumentsFound{true};
	for(auto monument : Monuments)
	{
		if (!monument->IsSeen)
		{
			allMonumentsFound = false;
		}
	}

	if (allMonumentsFound)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Level_MainMenu");
	}
}
