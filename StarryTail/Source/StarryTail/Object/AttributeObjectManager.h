// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "AttributeObject.h"
#include <LevelSequence/Public/LevelSequenceActor.h>
#include "AttributeObjectManager.generated.h"

USTRUCT()
struct FPuzzleInfo
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere, Category = "Info")
	AAttributeObject* Object;
	UPROPERTY(EditAnywhere, Category = "Info")
	EAttributeKeyword Attribute;
	UPROPERTY(EditAnywhere, Category = "Info")
	EState State;

};
UCLASS()
class STARRYTAIL_API AAttributeObjectManager : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,Category = Puzzle)
	TArray<FPuzzleInfo> Puzzle				;
	UPROPERTY(EditAnywhere, Category = Puzzle)
	TArray<EAttributeKeyword> Answer;
	UPROPERTY(EditAnywhere, Category = Sequence)
	ALevelSequenceActor* SequenceActor;
private:
	int32 AnswerCount;
public:	
	// Sets default values for this actor's properties
	AAttributeObjectManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ObjectInit();
	
	void PuzzleCheck();
	void ObjectActive();

};
