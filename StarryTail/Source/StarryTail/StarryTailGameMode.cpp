// Copyright Epic Games, Inc. All Rights Reserved.

#include "StarryTailGameMode.h"
#include "IreneCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStarryTailGameMode::AStarryTailGameMode()
{
	DefaultPawnClass = AIreneCharacter::StaticClass();
}
