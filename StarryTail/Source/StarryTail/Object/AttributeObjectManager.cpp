// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeObjectManager.h"

// Sets default values
AAttributeObjectManager::AAttributeObjectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AnswerCount = 2;
}

// Called when the game starts or when spawned
void AAttributeObjectManager::BeginPlay()
{
	Super::BeginPlay();

	if (Puzzle.Num() > 0) {
		for (int i = 0; i < Puzzle.Num(); i++)
		{
			if (Puzzle[i].Object != nullptr)
				Puzzle[i].Object->OnActiveCheck.AddUObject(this, &AAttributeObjectManager::ObjectActive);

		}
	}
	
}

void AAttributeObjectManager::ObjectInit()
{
	STARRYLOG_S(Error);
	if (Puzzle.Num() > 0) {
		for (int i = 0; i < Puzzle.Num(); i++)
		{
			if(Puzzle[i].Object!=nullptr)
			Puzzle[i].Object->SetObject(Puzzle[i].State, Puzzle[i].Attribute);

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
				ObjectInit();
				AnswerCount--;
				STARRYLOG(Warning, TEXT("Puzzle Fail"));
				return;
			}
		}
	}

	STARRYLOG(Warning, TEXT("Puzzle Success"));
	if (SequenceActor != nullptr) {
		SequenceActor->SequencePlayer->Play();
	}
	for (int i = 0; i < Puzzle.Num(); i++)
	{
		Puzzle[i].Object->TriggerOff();
	}
}

void AAttributeObjectManager::ObjectActive()
{
	for (int i = 0; i < Puzzle.Num(); i++)
	{
		if (Puzzle[i].Object->GetActive() == false)
		{
			STARRYLOG(Warning, TEXT("None All ACtive"));
			return;
		}
	}
	STARRYLOG(Warning, TEXT("All ACtive"));
	PuzzleCheck();
}


