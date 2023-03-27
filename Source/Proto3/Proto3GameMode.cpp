// Copyright Epic Games, Inc. All Rights Reserved.

#include "Proto3GameMode.h"
#include "Proto3Character.h"
#include "UObject/ConstructorHelpers.h"

AProto3GameMode::AProto3GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
