// Copyright Epic Games, Inc. All Rights Reserved.

#include "StarryTailGameMode.h"
#include "StarryTailCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStarryTailGameMode::AStarryTailGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClass(TEXT("/Script/StarryTail.IreneCharacter"));
	if(PlayerPawnClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnClass.Class;
	}
}
