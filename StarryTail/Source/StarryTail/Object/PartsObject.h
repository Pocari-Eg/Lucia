// Fill out your copyright notice in the Description page of Project Settings.


//������Ʈ�� ���� � ����� TimeLine�� �������Ʈ���� ����� ��Ȱ�Ͽ�
//��� ����Ʈ���� ����
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h" 
#include "Components/SphereComponent.h"

#include "Components/TimeLineComponent.h"



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

	//�޽�
	UPROPERTY(EditAnywhere,BluePrintReadOnly ,Category = Platform)
	UStaticMeshComponent* Mesh;
	//�̵���� Spline
	UPROPERTY(EditAnywhere, BluePrintReadOnly,Category = Platform)
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


	//Ÿ�Ӷ��� Ŀ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline", Meta = (AllowPrivateAccess = "true"))
	UCurveFloat* TimeLineCurve;

	//Ÿ�Ӷ���
	FTimeline PartsObjTimeline;

	UPROPERTY(BluePrintReadOnly)
	bool IsHoverStop;
private:
	// Timer
	FTimerHandle TimerHandle;

	//��� ���� ��ġ
	FVector InitSplineLocation;
	//���� ������ �ӵ� ����
	float InitZMovementSpeed;

	//Ʈ���� ����� ��� ���� �ð� ����
	int32 InitTriggerTime;

	//�۵� Ʈ����
	APartsTrigger* PartsTrigger;

	//������ ���� ����
	bool IsBackMove;

	bool IsTimelineOn;

	

public:
	// Sets default values for this actor's properties
	APartsObject();
	virtual void Tick(float DeltaTime) override;

	//������ �۵�
	void MovingStart(APartsTrigger* Trigger);
	

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//������ ������
	UFUNCTION()
	void MovingObject();
	//���� ������ üũ
	UFUNCTION()
	void NextMoveSet();
	//���� Ʈ���� �۵� �ð� ����
	void CountDown();


};
