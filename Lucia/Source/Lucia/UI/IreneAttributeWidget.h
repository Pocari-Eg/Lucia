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
  //������ ǥ���� ���̸� ���� �Ӽ�
	UPROPERTY(BluePrintReadOnly)
	EAttributeKeyword CurrentAttribute;

public:
	//���̸� �Ӽ� bind
	void BindCharacterAttribute(EAttributeKeyword Attribute);


};
