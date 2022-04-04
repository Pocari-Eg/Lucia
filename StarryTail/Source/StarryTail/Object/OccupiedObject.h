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

//점령 시작 델리데이트
DECLARE_MULTICAST_DELEGATE(FOnOccupyDelegate);
UCLASS()
class STARRYTAIL_API AOccupiedObject : public AActor
{
	GENERATED_BODY()

public:
   //델리게이트
	FOnOccupyDelegate OnOccupy;
private:

	//점령지 표시하기 위한 메쉬
   UPROPERTY(VisibleAnywhere,Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
   //점령 지역 트리거 
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   USphereComponent* Area;


   //총 점령 수치
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   float  MaxOccupy;

   //현재 점령수치
   UPROPERTY(VisibleAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   float  CurrentOccupy;

   //점령 증가 수치
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
    float  OccupyNum;
   //점령 감소 수치
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   float  DeOccupyNum;

   //몬스터 점령 

   //적이 점령지에 들어오고 점령을 시작할 시간
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   int32  EnemyOccupyTime;

   //현재 남은 시간 체크
   int32 CurrentEnemyTime;

   //적이 점령지를 빼앗는 수치
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   float   EnemyOccupyNum;

   //점령지를 빼앗기는 수치
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   float   OccupyCancelNum;


   //나중에 표시 안함

   //플레이어가 점령지에 들어옴
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   bool IsInPlayer;
   //적이 점령지에 들어옴
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   bool IsInEnemy;
   //점령 여부
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   bool IsOccupied;

   //점령 중인지 여부
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
    bool IsOccupying;
   //적이 점령이제 얼마나 들어왔는지
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   int32 InEnemyCount;

   //점령지 속성
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   EAttributeKeyword AreaAttribute;

   //플레이어 속성
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   EAttributeKeyword PlayerAttribute;

   AIreneCharacter* Player;

   // Timer
   FTimerHandle TimerHandle;
   // Timer
   FTimerHandle EnemyTimerHandle;
   //UI
	//Hp Bar 위젯 -> 점령 게이지로 변경
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
	//점령지에 들어왓는지
	UFUNCTION()
	void OnBeginOverlap	(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//점령지에서 나갔는지.
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// 속성 비교
	void CompareAttribute();
	//점령
	void Occupying();
	//점령 빼앗김
	void DeOccupying();
};
