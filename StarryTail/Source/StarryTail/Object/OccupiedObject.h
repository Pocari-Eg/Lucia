// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"

#include"../IreneCharacter.h"

//UI 관련
#include "Components/WidgetComponent.h"
#include "../UI/HPBarWidget.h"

#include "OccupiedObject.generated.h"

UCLASS()
class STARRYTAIL_API AOccupiedObject : public AActor
{
	GENERATED_BODY()

public:

private:
   UPROPERTY(VisibleAnywhere,Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   USphereComponent* Area;



   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   int32  MaxOccupy;

   UPROPERTY(VisibleAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   int32  CurrentOccupy;

   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   int32  OccupyNum;

   //나중에 지울것
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   bool IsInPlayer;
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   bool IsOccupied;

   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   EAttributeKeyword AreaAttribute;
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   EAttributeKeyword PlayerAttribute;

   AIreneCharacter* Player;

   // Timer
   FTimerHandle TimerHandle;

   //UI
	//Hp Bar 위젯
   UPROPERTY(VisibleAnywhere, Category = UI)
   class UWidgetComponent* OccupyBarWidget;
	
public:	
	// Sets default values for this actor's properties
	AOccupiedObject();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void OnBeginOverlap	(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CompareAttribute();
	void Occupying();
};
