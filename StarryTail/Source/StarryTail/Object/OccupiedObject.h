// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"

#include"../IreneCharacter.h"

//UI ����
#include "Components/WidgetComponent.h"
#include "../UI/HPBarWidget.h"

#include "OccupiedObject.generated.h"

//���� ���� ��������Ʈ
DECLARE_MULTICAST_DELEGATE(FOnOccupyDelegate);
UCLASS()
class STARRYTAIL_API AOccupiedObject : public AActor
{
	GENERATED_BODY()

public:
   //��������Ʈ
	FOnOccupyDelegate OnOccupy;
private:

	//������ ǥ���ϱ� ���� �޽�
   UPROPERTY(VisibleAnywhere,Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
   //���� ���� Ʈ���� 
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   USphereComponent* Area;


   //�� ���� ��ġ
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   float  MaxOccupy;

   //���� ���ɼ�ġ
   UPROPERTY(VisibleAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   float  CurrentOccupy;

   //���� ���� ��ġ
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
    float  OccupyNum;
   //���� ���� ��ġ
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   float  DeOccupyNum;

   //���� ���� 

   //���� �������� ������ ������ ������ �ð�
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   int32  EnemyOccupyTime;

   //���� ���� �ð� üũ
   int32 CurrentEnemyTime;

   //���� �������� ���Ѵ� ��ġ
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   float   EnemyOccupyNum;

   //�������� ���ѱ�� ��ġ
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   float   OccupyCancelNum;


   //���߿� ǥ�� ����

   //�÷��̾ �������� ����
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   bool IsInPlayer;
   //���� �������� ����
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   bool IsInEnemy;
   //���� ����
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   bool IsOccupied;

   //���� ������ ����
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
    bool IsOccupying;
   //���� �������� �󸶳� ���Դ���
   UPROPERTY(VisibleAnywhere, Category = Trigger, meta = (AllowPrivateAccess = "true"))
   int32 InEnemyCount;

   //������ �Ӽ�
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   EAttributeKeyword AreaAttribute;

   //�÷��̾� �Ӽ�
   UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
   EAttributeKeyword PlayerAttribute;

   AIreneCharacter* Player;

   // Timer
   FTimerHandle TimerHandle;
   // Timer
   FTimerHandle EnemyTimerHandle;
   //UI
	//Hp Bar ���� -> ���� �������� ����
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
	//�������� ���Ӵ���
	UFUNCTION()
	void OnBeginOverlap	(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//���������� ��������.
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// �Ӽ� ��
	void CompareAttribute();
	//����
	void Occupying();
	//���� ���ѱ�
	void DeOccupying();
};
