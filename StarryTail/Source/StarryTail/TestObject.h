// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StarryTail.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Components/BoxComponent.h> // 테스트
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
	UCapsuleComponent* Trigger; //콜리전 나중에 원하는 모양으로 수정
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UStaticMeshComponent* Mesh; // 메쉬 

	//오브젝트 속성
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TYPE); 
	EAttributeKeyword Attribute;


	// 속성 표시 위젯 
	UPROPERTY(EditAnywhere, Category = UI)
	class UWidgetComponent* AttributeWidget;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* AttributeWidget2;

private:
	// 오브젝트 hp
	UPROPERTY(EditAnywhere,Category=INFO, meta = (AllowPrivateAccess = "true"))
	float Hp;


public:
	// Sets default values for this actor's properties
	ATestObject();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

private:
	//hp 설정
	void SetHp(float ATK);

	//충돌 처리
	UFUNCTION()
	void OnAttackedOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

