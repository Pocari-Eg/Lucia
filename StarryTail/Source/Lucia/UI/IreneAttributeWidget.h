// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Lucia.h"
#include "Blueprint/UserWidget.h"
#include "IreneAttributeWidget.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UIreneAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
  //위젯에 표시할 아이린 현재 속성
	UPROPERTY(BluePrintReadOnly)
	EAttributeKeyword CurrentAttribute;

public:
	//아이린 속성 bind
	void BindCharacterAttribute(EAttributeKeyword Attribute);


};
