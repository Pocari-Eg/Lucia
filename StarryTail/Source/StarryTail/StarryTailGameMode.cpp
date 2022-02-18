// Copyright Epic Games, Inc. All Rights Reserved.

#include "StarryTailGameMode.h"
#include "StarryTailCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStarryTailGameMode::AStarryTailGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
