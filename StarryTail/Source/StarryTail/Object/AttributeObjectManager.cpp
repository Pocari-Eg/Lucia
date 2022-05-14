// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeObjectManager.h"

// Sets default values
AAttributeObjectManager::AAttributeObjectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAttributeObjectManager::BeginPlay()
{
	Super::BeginPlay();
	ObjectInit();

}

void AAttributeObjectManager::ObjectInit()
{
	if (Puzzle.Num() > 0) {
		for (int i = 0; i < Puzzle.Num(); i++)
		{
			if(Puzzle[i].Object!=nullptr)
			Puzzle[i].Object->SetObject(Puzzle[i].State, Puzzle[i].Attribute);
			Puzzle[i].Object->OnAnswerCheck.AddUObject(this, &AAttributeObjectManager::PuzzleCheck);
		}
	}

}

void AAttributeObjectManager::PuzzleCheck()
{
	
	if (Puzzle.Num() > 0 && Answer.Num() > 0 && Puzzle.Num() == Answer.Num())
	{
		for (int i = 0; i < Puzzle.Num(); i++)
		{
			if (Puzzle[i].Object->GetAttribute() != Answer[i]) {
				return;
			}
		}
	}

	STARRYLOG(Warning, TEXT("Puzzle Success"));
}


