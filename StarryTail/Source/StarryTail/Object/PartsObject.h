// Fill out your copyright notice in the Description page of Project Settings.


//������Ʈ�� ���� � ����� TimeLine�� �������Ʈ���� ����� ��Ȱ�Ͽ�
//��� ����Ʈ���� ����
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h" 
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"



#include "PartsObject.generated.h"
class APartsTrigger;
UCLASS()
class STARRYTAIL_API APartsObject : public AActor
{
	GENERATED_BODY()

	public:
	//��ü�� �ѹ� �̵��Ҷ� �󸶳� �̵��Ұ��ΰ�.
	UPROPERTY(EditAnywhere, Category = Platform)
	float Speed;
	UPROPERTY(EditAnywhere, Category = Platform)
	USphereComponent* Center;
	//�޽�
	UPROPERTY(EditAnywhere, Category = Platform)
	UStaticMeshComponent* Mesh;
	//�̵���� Spline
	UPROPERTY(EditAnywhere, Category = Platform)
	USplineComponent* Track;

	//���� ������Ʈ 
	UPROPERTY(EditAnywhere, Category = Platform)
	APartsObject* NextObject;
	//���� ������Ʈ
	UPROPERTY(EditAnywhere, Category = Platform)
	APartsObject* PrevObject;

	//���� ������ �Ÿ�
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Platform)
	float ZMovementDistance;
	//���� ������ �ӵ�
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Platform)
	float ZMovementSpeed;
	//���� �������� �Ұ�����
	UPROPERTY(BluePrintReadOnly, Category = Platform)
	bool ZMoving;

	//�ι�° Ʈ���Ű� �۵��Ǿ��� �ð�
	UPROPERTY(EditAnywhere, Category = Event)
	int32 TriggerTime;
	//�ι�° Ʈ���� �۵� ����
	UPROPERTY(EditAnywhere, Category = Event)
	bool IsEndTriggerOn;

private:

	//��ο� ������Ʈ�� ���ʸ��� �̵���ų������
	float Time;
	//��ο� ���ۼ�Ʈ �̵��ߴ���
	float Percent;
	// Timer
	FTimerHandle TimerHandle;

	//��� ���� ��ġ
	FVector InitSplineLocation;
	//���� ������ �ӵ� ����
	float InitZMovementSpeed;

	//Ʈ���� ����� ��� ���� �ð� ����
	int32 InitTriggerTime;

	APartsTrigger* PartsTrigger;

public:
	// Sets default values for this actor's properties
	APartsObject();
	virtual void Tick(float DeltaTime) override;

	//��� ������ ������ �۵�
	void ForwardMove(APartsTrigger* Trigger);
	//��� ������ ������ �۵�
	void BackwardMove();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//������ ������
	void Forward();
	//������ ������
	void Backward();
	//���� Ʈ���� �۵� �ð� ����
	void CountDown();


};
