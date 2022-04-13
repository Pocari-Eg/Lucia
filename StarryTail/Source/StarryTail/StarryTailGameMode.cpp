// Copyright Epic Games, Inc. All Rights Reserved.

#include "StarryTailGameMode.h"
#include "IreneCharacter.h"
#include"UI/PlayerHudWidget.h"
#include "UObject/ConstructorHelpers.h"

AStarryTailGameMode::AStarryTailGameMode()
{
	DefaultPawnClass = AIreneCharacter::StaticClass();
    HUDClass = UPlayerHudWidget::StaticClass();
}

void AStarryTailGameMode::BeginPlay()
{
    Super::BeginPlay();

    //Bind our Player died delegate to the Gamemode's PlayerDied function.
    if (!OnPlayerDied.IsBound())
    {
        OnPlayerDied.AddDynamic(this, &AStarryTailGameMode::PlayerDied);
    }

}

void AStarryTailGameMode::RestartPlayer(AController* NewPlayer)
{
    Super::RestartPlayer(NewPlayer);
}

void AStarryTailGameMode::PlayerDied(ACharacter* Character)
{
    //Get a reference to our Character's Player Controller
    AController* CharacterController = Character->GetController();
    RestartPlayer(CharacterController);
}