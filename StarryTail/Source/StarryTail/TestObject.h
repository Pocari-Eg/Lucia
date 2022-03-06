// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StarryTail.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Components/BoxComponent.h> // �׽�Ʈ
#include "IreneCharacter.h"

#include "UI/IreneAttributeWidget.h"
#include "Components/WidgetComponent.h"

#include "TestObject.generated.h"

UCLASS()
class STARRYTAIL_API ATestObject : public AActor
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UCapsuleComponent* Trigger; //�ݸ��� ���߿� ���ϴ� ������� ����
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UStaticMeshComponent* Mesh; // �޽� 

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TYPE); //���� Ÿ�� 
	EAttributeKeyword Attribute;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* AttributeWidget;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* AttributeWidget2;

public:
	// Sets default values for this actor's properties
	ATestObject();

	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

public:
	UFUNCTION()
	void OnAttackedOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

