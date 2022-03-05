// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "Blueprint/UserWidget.h"

#include "CharacterAttributeWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UCharacterAttributeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BluePrintReadOnly)
	EAttributeKeyword CurrentAttribute;

public:
	void BindCharacterAttribute(EAttributeKeyword Attribute);
};
