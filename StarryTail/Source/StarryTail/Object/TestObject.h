// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
//초기 설정 관련
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Components/BoxComponent.h> // 테스트
#include "../IreneCharacter.h"

//UI 관련
#include "Components/WidgetComponent.h"
#include "../UI/IreneAttributeWidget.h"
#include "../UI/HPBarWidget.h"

//소환 객체
#include "../Enemy.h"

#include "TestObject.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHpChangeDelegate);
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
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* AttributeWidget;

	//Hp Bar 위젯
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HpBarWidget;

	//HP 변화 델리게이트
	FOnHpChangeDelegate OnHpChanged;
private:
	// 오브젝트 MaxHp
	UPROPERTY(EditAnywhere,Category=INFO, meta = (AllowPrivateAccess = "true"))
	float MaxHP;
	//오브젝트 CurrentHp
	float CurrentHP;

	//몬스터  스폰 반경
	UPROPERTY(EditAnywhere, Category = INFO, meta = (AllowPrivateAccess = "true"))
	float SpawnRadius;
	//Radius변경 체크
	float OldRadius;

public:
	// Sets default values for this actor's properties
	ATestObject();

	virtual void Tick(float DeltaTime) override;

	//현재 HP를 UI로 넘기기
	float GetHpRatio();

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
	//성열현 충돌 처리 방식
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	void SpawnEenmy();
	void DrawSpawnErea();
};

