// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "../EnemySource/Monster.h"
#include "../Sound/SoundManager.h"
#include "AttributeObject.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnActiveCheckDelegate);


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
	UPROPERTY(VisibleAnywhere,Category=PuzzleInfo, meta = (AllowPrivateAccess = "ture"))
	EState State;
	UPROPERTY(VisibleAnywhere, Category = PuzzleInfo, meta = (AllowPrivateAccess = "ture"))
	EAttributeKeyword Attribute;

	bool IsActive;
public:
//트리거
	UPROPERTY(EditAnywhere, Category=Trigger)
	UCapsuleComponent* Trigger;
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* ObjectMesh;
	FOnActiveCheckDelegate OnActiveCheck;


	//UPROPERTY(EditAnywhere, Category = Mesh)
	//AActor* Plate;
	//UPROPERTY(EditAnywhere, Category = Mesh)
	//AActor* Crystal;

	//UPROPERTY(VisibleAnyWhere,BluePrintReadWrite, Category = Mesh)
	//UStaticMeshComponent* PlateMesh;
	//UPROPERTY(VisibleAnyWhere,BluePrintReadWrite, Category = Mesh)
	//USkeletalMeshComponent* CrystalMesh;

public:	
	// Sets default values for this actor's properties
	AAttributeObject();

	void SetObject(EState NewState, EAttributeKeyword NewAttribute);

	UFUNCTION(BluePrintCallable)
	EAttributeKeyword GetAttribute();

	 void HitCheck(AIreneCharacter* Irene);

	 bool GetActive();

	 UFUNCTION(BlueprintImplementableEvent)
	 void  AttributeChangeEvent();

	 //트리거 Off
	 void TriggerOff();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

};
