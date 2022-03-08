// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IreneCharacter.h"
#include "EnemyMagicAttack.generated.h"

UCLASS()
class STARRYTAIL_API AEnemyMagicAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyMagicAttack();

	UPROPERTY(VisibleAnyWhere, Category = Mesh)
		USphereComponent* Collision; //�ݸ��� ���߿� ���ϴ� ������� ����
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
private:
	// Location ������ �������� �����غ���
	UPROPERTY(VisibleAnyWhere, Category = Player)
	AIreneCharacter* Player;
	// ��ƼŬ ����Ʈ
	UParticleSystemComponent* OurParticleSystem;
	UFUNCTION()
		void OnCollisionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed, meta = (AllowPrivateAccess = "true"))
	float Speed;
};
