// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "../EnemySource/Monster.h"
#include "../Sound/SoundManager.h"
#include "AttributeObject.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAnswerCheckDelegate);


UENUM(BluePrintType)
enum class EState : uint8
{
	e_Disabled = 0 UMETA(DisplayName = "Disabled"),
	e_Activate UMETA(DisplayName = "Activate"),
	e_Constant  UMETA(DisplayName = "Constant")
};
UCLASS()
class STARRYTAIL_API AAttributeObject : public AMonster
{
GENERATED_BODY()

private:
 //메쉬
	
//상태
	UPROPERTY(VisibleAnywhere,Category=Info, meta = (AllowPrivateAccess = "ture"))
	EState State;
	UPROPERTY(VisibleAnywhere, Category = Info, meta = (AllowPrivateAccess = "ture"))
	EAttributeKeyword Attribute;
public:
//트리거
	UPROPERTY(EditAnywhere, Category=Trigger)
	UCapsuleComponent* Trigger;
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* ObjectMesh;
	FOnAnswerCheckDelegate OnAnswerCheck;
public:	
	// Sets default values for this actor's properties
	AAttributeObject();

	void SetObject(EState NewState, EAttributeKeyword NewAttribute);

	EAttributeKeyword GetAttribute();

	 void HitCheck(AIreneCharacter* Irene);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

};
