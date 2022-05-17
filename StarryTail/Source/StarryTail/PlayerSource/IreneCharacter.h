// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// �߰��ϴ� �κ�
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../StarryTail.h"
#include "PlayerCharacterDataStruct.h"

//������
//#include "StopWatch.h"
//#include "Components/WidgetComponent.h"

#include "IreneCharacter.generated.h"

//�Ӽ� ���� ��������Ʈ
DECLARE_MULTICAST_DELEGATE(FOnAttributeChangeDelegate);


UCLASS()
class STARRYTAIL_API AIreneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//�Ӽ���ȯ ��������Ʈ
	FOnAttributeChangeDelegate FOnAttributeChange;
protected:

public:
#pragma region GetClassOrObject
	// �÷��̾� ��Ʈ�ѷ�
	UPROPERTY()
	APlayerController* WorldController;

	// �������� Ŀ��
	UPROPERTY()
	UCurveFloat* JumpGravityCurve;

	// ī�޶� �ϰ� ī�޶�
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp;

	UPROPERTY()
	class UIreneAnimInstance* IreneAnim;
	UPROPERTY()
	class UIreneAttackInstance* IreneAttack;
	UPROPERTY()
	class UIreneInputInstance* IreneInput;

	// ĳ���Ͱ� ����ϴ� ����, ��� ���� �ִ� ����ü
	UPROPERTY(EditAnywhere)
	FPlayerCharacterDataStruct IreneData;
	UPROPERTY(BluePrintReadOnly)
	class UIreneUIManager* IreneUIManager;
	UPROPERTY()
	class UIreneFSM* IreneState;

	//ȸ�� ����ü
	UPROPERTY(EditAnywhere,Category=HpRecorvery)
	FPlayerRecoveryDataStruct HpRecoveryData;
	
	// ���� �Ž�
	UPROPERTY()
	USkeletalMeshComponent* Weapon;
	UPROPERTY()
	TArray<USkeletalMesh*> WeaponMeshArray;
	UPROPERTY()
	TArray<FName> WeaponSocketNameArray;

	UPROPERTY(EditAnywhere)
	TArray<UCurveFloat*> CameraShakeCurve;
private:
	FTimerHandle FixedUpdateTimer;
#pragma endregion GetClassOrObject

	//��ž��ġ
	//AStopWatch* StopWatch;
public:
#pragma region Setting
	// Sets default values for this character's properties
	AIreneCharacter();

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TargetReset()const;
#pragma endregion Setting

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

#pragma region State
	// ���� ��ȭ �� �α� ���
	void ChangeStateAndLog(class IState* NewState)const;
	void ActionEndChangeMoveState()const;
#pragma endregion State
	
#pragma region Collision
	// ����� ���� ã��
	void FindNearMonster();
	void NearMonsterAnalysis(const TArray<FHitResult> MonsterList, const bool bResult, const FCollisionQueryParams Params, const float Far)const;
	void SetNearMonster(const FHitResult RayHit, float& NearPosition, const float FindNearTarget)const;
	// ��ħ �浹 ó��
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(UPrimitiveComponent *MyComp, AActor *Other, UPrimitiveComponent *OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult &Hit) override;

	// �ǰ�
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
#pragma endregion Collision

#pragma region HitFeel
	public:
	UFUNCTION(BlueprintImplementableEvent)
	void HitStopEvent();

	void LastAttackCameraShake(const float DeltaTime);
	
	UPROPERTY(BluePrintReadWrite)
	bool CameraShakeOn;

	UPROPERTY(BluePrintReadWrite)
	bool IsTimeStopping;
#pragma endregion HitFeel
//��ž��ġ 
	//void WatchControl();
	//void WatchReset();
	FPlayerCharacterDataStruct* GetDataStruct(){return &IreneData;}
};
