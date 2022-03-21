// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
//�ʱ� ���� ����
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Components/BoxComponent.h> // �׽�Ʈ
#include "../IreneCharacter.h"

//UI ����
#include "Components/WidgetComponent.h"
#include "../UI/IreneAttributeWidget.h"
#include "../UI/HPBarWidget.h"

//��ȯ ��ü
#include "../Enemy.h"

#include "TestObject.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHpChangeDelegate);
UCLASS()
class STARRYTAIL_API ATestObject : public AActor
{
	GENERATED_BODY()
public:
   
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UCapsuleComponent* Trigger; //�ݸ��� ���߿� ���ϴ� ������� ����
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UStaticMeshComponent* Mesh; // �޽� 

	//������Ʈ �Ӽ�
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TYPE); 
	EAttributeKeyword Attribute;


	// �Ӽ� ǥ�� ���� 
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* AttributeWidget;

	//Hp Bar ����
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HpBarWidget;

	//HP ��ȭ ��������Ʈ
	FOnHpChangeDelegate OnHpChanged;
private:
	// ������Ʈ MaxHp
	UPROPERTY(EditAnywhere,Category=INFO, meta = (AllowPrivateAccess = "true"))
	float MaxHP;
	//������Ʈ CurrentHp
	float CurrentHP;

	//����  ���� �ݰ�
	UPROPERTY(EditAnywhere, Category = INFO, meta = (AllowPrivateAccess = "true"))
	float SpawnRadius;
	//Radius���� üũ
	float OldRadius;

public:
	// Sets default values for this actor's properties
	ATestObject();

	virtual void Tick(float DeltaTime) override;

	//���� HP�� UI�� �ѱ��
	float GetHpRatio();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

private:
	//hp ����
	void SetHp(float ATK);

	//�浹 ó��
	UFUNCTION()
	void OnAttackedOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//������ �浹 ó�� ���
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	void SpawnEenmy();
	void DrawSpawnErea();
};

