// Copyright Epic Games, Inc. All Rights Reserved.

#include "FallingGameMode.h"
#include "FallingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFallingGameMode::AFallingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
