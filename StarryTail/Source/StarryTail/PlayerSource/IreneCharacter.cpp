// Fill out your copyright notice in the Description page of Project Settings.
//
//  
// ���߿� �ؾ��� ��: �Ϲ� ���� �Ӽ� ���̺� ���� �� �б�, 
// 
// �α� ��¿� ����
// UE_LOG(LogTemp, Error, TEXT("Sub"));
// STARRYLOG(Error, TEXT("Sub"));
#pragma once

#include "IreneCharacter.h"
#include "DrawDebugHelpers.h"
#include "../STGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "../StarryTailGameMode.h"
#include "IreneUIManager.h"
#include "IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneAttackInstance.h"
#include "IreneInputInstance.h"
#include ".././EnemySource/Scientia/Feather.h"
#include ".././EnemySource/Scientia/Piece.h"
#include "Curves/CurveVector.h"
#include "../EnemySource/Bouldelith/Bouldelith.h"
#include "../EnemySource/Morbit/Morbit.h"

#pragma region Setting
// Sets default values
AIreneCharacter::AIreneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ݶ��̴� ����
	GetCapsuleComponent()->InitCapsuleSize(25.f, 80.0f);

	ShieldComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Shield(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if(SM_Shield.Succeeded())
	{
		ShieldComp->SetStaticMesh(SM_Shield.Object);
	}
	const ConstructorHelpers::FObjectFinder<UMaterial>MT_Shield(TEXT("/Game/Model/Irene/Material/MT_Shield.MT_Shield"));
	if(MT_Shield.Succeeded())
	{
		ShieldComp->SetMaterial(0,MT_Shield.Object);
	}
	ShieldComp->SetupAttachment(GetCapsuleComponent());
	ShieldComp->SetVisibility(false);
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComp->TargetArmLength = IreneData.FollowCameraZPosition;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 53));
	SpringArmComp->CameraLagSpeed = 0.0f;
	SpringArmComp->SetupAttachment(GetCapsuleComponent());

	// ī�޶� ����
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->FieldOfView = IreneData.FieldOfView;

	// ���̷��� �޽� ����
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Animation/Irene/Idle.Idle"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -80), FRotator(0, 270, 0));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
		GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
		GetCapsuleComponent()->SetGenerateOverlapEvents(true);
		//����
		if (GetMesh()->DoesSocketExist(TEXT("hand_rSwordSocket")))
		{
			Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Sword(TEXT("/Game/Animation/Irene/Weapon/Sword.Sword"));

			if (SK_Sword.Succeeded())
			{
				WeaponMesh=SK_Sword.Object;
			}
			Weapon->SetSkeletalMesh(WeaponMesh);
			Weapon->SetupAttachment(GetMesh(), TEXT("hand_rSwordSocket"));
			Weapon->SetCollisionProfileName(TEXT("PlayerAttack"));
			Weapon->SetGenerateOverlapEvents(false);
			Weapon->SetVisibility(false);
		}
		
		// �������Ʈ �ִϸ��̼� ����
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Animation/Irene/Animation/BP/BP_IreneAnimation.BP_IreneAnimation_C"));

		if (CharacterAnimInstance.Succeeded())
		{
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
		}
	}

	// ī�޶� ����ũ Ŀ��
	const ConstructorHelpers::FObjectFinder<UCurveVector>FireAttack1(TEXT("/Game/Math/AttackCurve/FireAttack1.FireAttack1"));
	const ConstructorHelpers::FObjectFinder<UCurveVector>FireAttack2(TEXT("/Game/Math/AttackCurve/FireAttack2.FireAttack2"));
	const ConstructorHelpers::FObjectFinder<UCurveVector>FireAttack3(TEXT("/Game/Math/AttackCurve/FireAttack3.FireAttack3"));
	const ConstructorHelpers::FObjectFinder<UCurveVector>WaterAttack1(TEXT("/Game/Math/AttackCurve/WaterAttack1.WaterAttack1"));
	const ConstructorHelpers::FObjectFinder<UCurveVector>WaterAttack2(TEXT("/Game/Math/AttackCurve/WaterAttack2.WaterAttack2"));
	const ConstructorHelpers::FObjectFinder<UCurveVector>WaterAttack3(TEXT("/Game/Math/AttackCurve/WaterAttack3.WaterAttack3"));
	const ConstructorHelpers::FObjectFinder<UCurveVector>ThunderAttack1(TEXT("/Game/Math/AttackCurve/ThunderAttack1.ThunderAttack1"));
	const ConstructorHelpers::FObjectFinder<UCurveVector>ThunderAttack2(TEXT("/Game/Math/AttackCurve/ThunderAttack2.ThunderAttack2"));
	const ConstructorHelpers::FObjectFinder<UCurveVector>ThunderAttack3(TEXT("/Game/Math/AttackCurve/ThunderAttack3.ThunderAttack3"));
	const ConstructorHelpers::FObjectFinder<UCurveVector>FireSkill1(TEXT("/Game/Math/AttackCurve/FireSkill1.FireSkill1"));
	const ConstructorHelpers::FObjectFinder<UCurveVector>WaterSkill1(TEXT("/Game/Math/AttackCurve/WaterSkill1.WaterSkill1"));	
	const ConstructorHelpers::FObjectFinder<UCurveVector>ThunderSkill1(TEXT("/Game/Math/AttackCurve/ThunderSkill1.ThunderSkill1"));
	if (FireAttack1.Succeeded() && FireAttack2.Succeeded() && FireAttack3.Succeeded() && FireSkill1.Succeeded() &&
	WaterAttack1.Succeeded() && WaterAttack2.Succeeded() && WaterAttack3.Succeeded() && WaterSkill1.Succeeded() &&
	ThunderAttack1.Succeeded() && ThunderAttack2.Succeeded() && ThunderAttack3.Succeeded() && ThunderSkill1.Succeeded())
	{
		CameraShakeCurve.Add(FireAttack1.Object);
		CameraShakeCurve.Add(FireAttack2.Object);
		CameraShakeCurve.Add(FireAttack3.Object);
		CameraShakeCurve.Add(WaterAttack1.Object);
		CameraShakeCurve.Add(WaterAttack2.Object);
		CameraShakeCurve.Add(WaterAttack3.Object);
		CameraShakeCurve.Add(ThunderAttack1.Object);
		CameraShakeCurve.Add(ThunderAttack2.Object);
		CameraShakeCurve.Add(ThunderAttack3.Object);
		CameraShakeCurve.Add(FireSkill1.Object);
		CameraShakeCurve.Add(WaterSkill1.Object);
		CameraShakeCurve.Add(ThunderSkill1.Object);
		UseShakeCurve = CameraShakeCurve[0];
	}
	const ConstructorHelpers::FObjectFinder<UCurveFloat>RunForwardCameraLag(TEXT("/Game/Math/CameraLag/RunForwardCameraLag.RunForwardCameraLag"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat>RunRightCameraLag(TEXT("/Game/Math/CameraLag/RunRightCameraLag.RunRightCameraLag"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat>RunDiagonalCameraLag(TEXT("/Game/Math/CameraLag/RunDiagonalCameraLag.RunDiagonalCameraLag"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat>RunBackWordCameraLag(TEXT("/Game/Math/CameraLag/RunBackwordCameraLag.RunBackwordCameraLag"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat>SprintForwardCameraLag(TEXT("/Game/Math/CameraLag/SprintForwardCameraLag.SprintForwardCameraLag"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat>SprintRightCameraLag(TEXT("/Game/Math/CameraLag/SprintRightCameraLag.SprintRightCameraLag"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat>SprintDiagonalCameraLag(TEXT("/Game/Math/CameraLag/SprintDiagonalCameraLag.SprintDiagonalCameraLag"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat>SprintBackWordCameraLag(TEXT("/Game/Math/CameraLag/SprintBackwordCameraLag.SprintBackwordCameraLag"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat>ThunderDodgeCameraLag(TEXT("/Game/Math/CameraLag/ThunderDodgeCameraLag.ThunderDodgeCameraLag"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat>ReturnDodgeCameraLag(TEXT("/Game/Math/CameraLag/ReturnCameraLag.ReturnCameraLag"));

	if (RunForwardCameraLag.Succeeded() && RunRightCameraLag.Succeeded() && RunDiagonalCameraLag.Succeeded() &&
		SprintForwardCameraLag.Succeeded() && SprintRightCameraLag.Succeeded() &&
		SprintDiagonalCameraLag.Succeeded() && ThunderDodgeCameraLag.Succeeded() && ReturnDodgeCameraLag.Succeeded())
	{
		CameraLagCurve.Add(RunForwardCameraLag.Object);
		CameraLagCurve.Add(RunRightCameraLag.Object);
		CameraLagCurve.Add(RunDiagonalCameraLag.Object);
		CameraLagCurve.Add(RunBackWordCameraLag.Object);
		CameraLagCurve.Add(SprintForwardCameraLag.Object);
		CameraLagCurve.Add(SprintRightCameraLag.Object);
		CameraLagCurve.Add(SprintDiagonalCameraLag.Object);
		CameraLagCurve.Add(SprintBackWordCameraLag.Object);
		CameraLagCurve.Add(ThunderDodgeCameraLag.Object);
		CameraLagCurve.Add(ReturnDodgeCameraLag.Object);
		UseLagCurve = CameraLagCurve[0];
	}
	
	// ī�޶� ȸ���� ĳ���� ȸ�� ���� �ȵǵ��� ����
	bUseControllerRotationYaw = false;
	SpringArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1050.0f, 0.0f);

	// ���� ����
	GetCharacterMovement()->JumpZVelocity = IreneData.JumpStartPower;

	// �⺻ �ִ� �̵��ӵ�
	GetCharacterMovement()->MaxWalkSpeed = IreneData.RunMaxSpeed;

	// �÷��̾� ���� �� �⺻ ���� ����
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// IreneCharacter.h�� ���� �ʱ�ȭ

	// ��Ʈ�ѷ� �ʱ�ȭ
	WorldController = nullptr;
	HpRecoveryData.bIsRecovering = false;

	// PlayerCharacterDataStruct.h�� ������ �ʱ�ȭ
	IreneData.CurrentHP = IreneData.MaxHP;
	IreneData.CurrentStamina = IreneData.MaxStamina;

	CameraShakeOn = false;
	//LastLagTime = 0.0f;
	
	HpRecoveryData.Amount = 300;
	HpRecoveryData.HP_Re_Time = 4;
	HpRecoveryData.Speed = 5;
	HpRecoveryData.Time = 10;

	bIsRadialBlurOn = false;
}

// Called when the game starts or when spawned
void AIreneCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ��Ʈ�ѷ� �޾ƿ���
	WorldController = GetWorld()->GetFirstPlayerController();
	
	//���缷
	 STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (nullptr == STGameInstance)
	{
		STARRYLOG(Error, TEXT("GameInstance is Not STGameInstance"));
	}
	else
	{
		STGameInstance->SetPlayer(this);
	}

	//��ž��ġ ���� 
	//StopWatch = GetWorld()->SpawnActor<AStopWatch>(FVector::ZeroVector, FRotator::ZeroRotator);
	//StopWatch->InitStopWatch();

	// �ִϸ��̼� �Ӽ� �ʱ�ȭ
	IreneAnim->SetAttribute(IreneAttack->GetSwordAttribute());
	
	IreneUIManager->Begin();
	IreneInput->Begin();
	
	FOnSwordAttributeChange.Broadcast();

	InitComplete();
}

void AIreneCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
		
	IreneState = NewObject<UIreneFSM>(this);
	IreneState->SetState(UIdleState::GetInstance());
	IreneState->Init(this);
	IreneAnim = Cast<UIreneAnimInstance>(GetMesh()->GetAnimInstance());
	IreneAnim->Init(this);
	IreneAttack = NewObject<UIreneAttackInstance>(this);
	IreneAttack->Init(this);
	IreneInput = NewObject<UIreneInputInstance>(this);
	IreneInput->Init(this);	

	IreneUIManager = NewObject<UIreneUIManager>(this);
	IreneUIManager->Init(this);
	
	IreneAnim->OnNextAttackCheck.AddLambda([this]()->void
		{
			if (IreneData.IsComboInputOn)
			{
				IreneAttack->AttackStartComboState();
				if (IreneInput->bUseLeftButton)
				{
					IreneAnim->NextToAttackMontageSection(IreneData.CurrentCombo);
				}
			}
		});
	IreneAnim->OnAttackHitCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackCheck);
	IreneAnim->OnAttackStopCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackStopCheck);
	IreneAnim->OnFootStep.AddUObject(IreneUIManager, &UIreneUIManager::FootStepSound);
	IreneAnim->OnRadialBlur.AddUObject(this, &AIreneCharacter::OnRadialBlur);
}

void AIreneCharacter::TargetReset()const
{
	// Ÿ���� ���ǿ� ���� �ʱ�ȭ�ϴ� �Լ�
	if (IreneAttack->TargetMonster != nullptr)
	{
		// Ÿ�ٸ��� �װų� �Ÿ��� �־����� �ʱ�ȭ
		// Ÿ�ٸ��� �װų� �������� �ȵǸ� �ʱ�ȭ -> �����
		const auto Mob = Cast<AMonster>(IreneAttack->TargetMonster);
		if (Mob != nullptr)
		{
			if (Mob->GetHp() <= 0 || !IreneAttack->TargetMonster->WasRecentlyRendered())//FVector::Dist(GetActorLocation(), IreneAttack->TargetMonster->GetActorLocation()) > 700.0f)
			{
				const auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
				Mon->MarkerOff();
				IreneAnim->SetIsHaveTargetMonster(false);
				IreneAnim->SetTargetMonster(nullptr);
				IreneAttack->TargetMonster = nullptr;				
			}			
		}
	}
	if (IreneAttack->CanThrowQuillMonster != nullptr)
	{
		// Ÿ�ٸ��� �װų� �Ÿ��� �־����� �ʱ�ȭ
		// Ÿ�ٸ��� �װų� �������� �ȵǸ� �ʱ�ȭ -> �����
		const auto Mob = Cast<AMonster>(IreneAttack->CanThrowQuillMonster);
		if (Mob != nullptr)
		{
			if (Mob->GetHp() <= 0 || !IreneAttack->CanThrowQuillMonster->WasRecentlyRendered())//FVector::Dist(GetActorLocation(), IreneAttack->TargetMonster->GetActorLocation()) > 700.0f)
				{
				const auto Mon=Cast<AMonster>(IreneAttack->CanThrowQuillMonster);
				Mon->TargetWidgetOff();
				IreneAttack->CanThrowQuillMonster = nullptr;	

			}			
		}
	}
}
#pragma endregion Setting

// Called every frame
void AIreneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LastAttackCameraShake(DeltaTime);
	//DoCameraLagCurve(DeltaTime);
	TargetReset();
	FindCanThrowQuillMonster(DeltaTime);
	
	if(!IreneState->IsDeathState())
		IreneInput->RecoveryStaminaGauge(DeltaTime);
	IreneState->Update(DeltaTime);
	//STARRYLOG(Error,TEXT("%s"),*IreneState->GetStateToString());
}

// Called to bind functionality to input
void AIreneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// ������ ���� Ű���� �Է�
	PlayerInputComponent->BindAxis("MoveW", IreneInput, &UIreneInputInstance::MoveW).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("MoveA", IreneInput, &UIreneInputInstance::MoveA).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("MoveS", IreneInput, &UIreneInputInstance::MoveS).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("MoveD", IreneInput, &UIreneInputInstance::MoveD).bExecuteWhenPaused = true;
	
	// ������ �� Ű���� �Է�
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, IreneInput, &UIreneInputInstance::DodgeKeyword);
	PlayerInputComponent->BindAxis("WaterDodge", IreneInput, &UIreneInputInstance::WaterDodgeKeyword);
	PlayerInputComponent->BindAction("MouseCursor", IE_Pressed, IreneInput, &UIreneInputInstance::MouseCursorKeyword);
	PlayerInputComponent->BindAction("FireKeyword", IE_Released, IreneInput, &UIreneInputInstance::FireKeywordReleased);
	PlayerInputComponent->BindAction("WaterKeyword", IE_Released, IreneInput, &UIreneInputInstance::WaterKeywordReleased);
	PlayerInputComponent->BindAction("ElectricKeyword", IE_Released, IreneInput, &UIreneInputInstance::ElectricKeywordReleased);
	PlayerInputComponent->BindAction("QuillAttributeChange", IE_Released, IreneInput, &UIreneInputInstance::QuillAttributeChangeReleased);

	// ���콺
	PlayerInputComponent->BindAxis("Turn", IreneInput, &UIreneInputInstance::Turn);
	PlayerInputComponent->BindAxis("LookUp", IreneInput, &UIreneInputInstance::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", IreneInput, &UIreneInputInstance::LeftButton);
	PlayerInputComponent->BindAction("RightButton", IE_Pressed, IreneInput, &UIreneInputInstance::RightButtonPressed);
	PlayerInputComponent->BindAction("RightButton", IE_Released, IreneInput, &UIreneInputInstance::RightButtonReleased);
	PlayerInputComponent->BindAxis("MouseWheel", IreneInput, &UIreneInputInstance::MouseWheel);
	
	// �� ��
	PlayerInputComponent->BindAction("Pause", IE_Pressed, IreneInput, &UIreneInputInstance::PauseWidgetOn).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Action", IE_Pressed, IreneInput, &UIreneInputInstance::DialogAction);
	PlayerInputComponent->BindAction("DialogSkip", IE_Pressed, IreneInput, &UIreneInputInstance::DialogSkip);
	//������
	//��ž��ġ ��Ʈ��
	/*PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchControl);
	PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);*/
}

#pragma region Collision
void AIreneCharacter::FindNearMonster()
{
	// ���� ����� ���͸� ã�� ���ݹ��� ���� �ָ� �ٰ����� �ϰ� �����ϴ� �Լ�
	
	if(IreneAttack->TargetMonster!=nullptr && IreneState->IsFirstAttack())
	{
		// ���� Ÿ���� ���
		const auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
		Mon->MarkerOff();		
		IreneAnim->SetIsHaveTargetMonster(false);
		IreneAttack->TargetMonster = nullptr;
	}

	// �� ���� �ڽ� ����, ����, �Ÿ�

	// �÷��̾� ��ġ�� ������� �ڽ��� ���� ���͵��� Ž���ϴ� ���
	//const FVector BoxSize = FVector(200, 50, 150);
	//auto HitMonsterList = IreneAttack->StartPositionFindNearMonster(BoxSize,GetActorLocation(),GetActorForwardVector());

	// ī�޶� ��ġ�� ������� �ڽ��� ���� ���͵��� Ž���ϴ� ���	
	auto AllPosition = SetCameraStartTargetPosition(FVector(200,200,500),CameraComp->GetComponentLocation());
	auto HitMonsterList = StartPositionFindNearMonster(AllPosition.Get<0>(),AllPosition.Get<1>(),AllPosition.Get<2>());	
	NearMonsterAnalysis(HitMonsterList.Get<0>(), HitMonsterList.Get<1>(), HitMonsterList.Get<2>(), AllPosition.Get<0>().Z, false);
	
	IreneAttack->DoAttack();
}
TTuple<FVector, FVector, FVector> AIreneCharacter::SetCameraStartTargetPosition(const FVector BoxSize, const FVector StartPosition) const
{
	const int BoxFarSize = BoxSize.Z;
	FVector Length = GetControlRotation().Quaternion() * FVector::ForwardVector;
	Length.Normalize();
	const FVector TargetPos = GetActorLocation()+(Length) * BoxFarSize;	
	const FVector CameraPos = StartPosition;
	const FVector ReturnBoxSize = FVector(BoxSize.X, BoxSize.Y, FVector::Dist(TargetPos,CameraPos)/2);
	return MakeTuple(ReturnBoxSize, CameraPos, TargetPos);
}

TTuple<TArray<FHitResult>, FCollisionQueryParams, bool> AIreneCharacter::StartPositionFindNearMonster(const FVector BoxSize, const FVector StartPosition, const FVector TargetPosition, const float LifeTime)const
{
	const FVector Center = (TargetPosition + StartPosition) /2;

	// ����Ʈ�� ��� �浹 ��� ��´�.
	TArray<FHitResult> MonsterList;
	const FCollisionQueryParams Params(NAME_None, false, this);
	const bool bResult = GetWorld()->SweepMultiByChannel(
		MonsterList,
		Center,
		Center,
		FRotationMatrix::MakeFromZ(CameraComp->GetForwardVector()).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel8,
		FCollisionShape::MakeBox(BoxSize),
		Params);

#if ENABLE_DRAW_DEBUG
	const FVector TraceVec = CameraComp->GetForwardVector();
	//const FVector Center = (TargetPosition + StartPosition) /2;
	const FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	const FColor DrawColor = bResult ? FColor::Magenta : FColor::Blue;
	const float DebugLifeTime = LifeTime;
	DrawDebugBox(GetWorld(), Center, BoxSize, CapsuleRot, DrawColor, false, DebugLifeTime*2);
#endif
	
	return MakeTuple(MonsterList, Params, bResult);
}
void AIreneCharacter::NearMonsterAnalysis(const TArray<FHitResult> MonsterList, const FCollisionQueryParams Params, const bool bResult, const float Far, const bool QuillTarget)const
{
	// ���� �浹ü �� ���� ����� �浹ü �ϳ��� �����ϴ� �Լ�
	// �ִ�Ÿ�
	float NearPosition = Far;
	FName TargetCollisionProfileName;

	for (FHitResult Monster : MonsterList)
	{
		if (bResult)
		{
			//STARRYLOG(Warning,TEXT("%s"), *Monster.GetActor()->GetName());
			// ����Ʈ����� �����ɽ�Ʈ �߻�(�ݺ�)
			FHitResult RayHit;
			bool bLayResult = GetWorld()->LineTraceSingleByChannel(
				RayHit,
				GetActorLocation(),
				Monster.GetActor()->GetActorLocation(),
				ECollisionChannel::ECC_GameTraceChannel8,
				Params);

			// ���� ���Ͱ� ĸ��������Ʈ�� ������ �ִ��� Ȯ��
			if (bLayResult && RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>() != nullptr)
			{
				// ĳ���Ϳ� Ÿ�� ���� �ּҰŸ� ã��
				float FindNearTarget = FVector::Dist(GetActorLocation(), RayHit.GetActor()->GetActorLocation());
				// ���� ������Ʈ �浹ü ������ �̸�
				// ���ο� ������Ʈ �浹ü ������ �̸�
				const FName RayCollisionProfileName = RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
				const FName EnemyProfile = "Enemy";
				const FName ObjectProfile = "Object";

				// ������ �� ĸ��������Ʈ�� ������ ī�޶� ������ �Ǹ� ���������� ����ִ� ���� �Ǵ� ������Ʈ ã��
				if (RayHit.Actor.IsValid() &&
					(RayCollisionProfileName == EnemyProfile || RayCollisionProfileName == ObjectProfile)
					&& RayHit.GetActor()->WasRecentlyRendered())
				{
					if(!QuillTarget)
					{
						// ù ���� �Ҵ�
						if (IreneAttack->TargetMonster == nullptr)
						{
							IreneAttack->TargetMonster = RayHit.GetActor();
							IreneAnim->SetTargetMonster(RayHit.GetActor());
							IreneAnim->SetIsHaveTargetMonster(true);
							NearPosition = FindNearTarget;
							
						}

						TargetCollisionProfileName = IreneAttack->TargetMonster->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
						if (IreneUIManager->bShowLog)
							UE_LOG(LogTemp, Warning, TEXT("Name: %s, Dist: %f"), *RayHit.GetActor()->GetName(), FindNearTarget);

						// ���� �Ǵ� ������Ʈ�� �÷��̾ �Ÿ��� ���� ���� ���͸� ã�´�.
						if (NearPosition >= FindNearTarget)
						{
							// ���� �ִܰŸ��� ���� ���Ͱ� �ִٸ�
							if (NearPosition == FindNearTarget)
							{
								if ((TargetCollisionProfileName == EnemyProfile && RayCollisionProfileName == EnemyProfile)||
									(TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == EnemyProfile)||
									(TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == ObjectProfile))
								{
									SetAttackNearMonster(RayHit,NearPosition,FindNearTarget);
								}
							}
							else
							{
								SetAttackNearMonster(RayHit,NearPosition,FindNearTarget);
							}
						}
					}
					else
					{
						if (IreneAttack->CanThrowQuillMonster == nullptr)
						{
							IreneAttack->CanThrowQuillMonster = RayHit.GetActor();
							NearPosition = FindNearTarget;
						}

						TargetCollisionProfileName = IreneAttack->CanThrowQuillMonster->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
						if (IreneUIManager->bShowLog)
							UE_LOG(LogTemp, Warning, TEXT("Name: %s, Dist: %f"), *RayHit.GetActor()->GetName(), FindNearTarget);

						// ���� �Ǵ� ������Ʈ�� �÷��̾ �Ÿ��� ���� ���� ���͸� ã�´�.
						if (NearPosition >= FindNearTarget)
						{
							// ���� �ִܰŸ��� ���� ���Ͱ� �ִٸ�
							if (NearPosition == FindNearTarget)
							{
								if ((TargetCollisionProfileName == EnemyProfile && RayCollisionProfileName == EnemyProfile)||
									(TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == EnemyProfile)||
									(TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == ObjectProfile))
								{
									SetQuillNearMonster(RayHit,NearPosition,FindNearTarget);
								}
							}
							else
							{
								SetQuillNearMonster(RayHit,NearPosition,FindNearTarget);
							}
						}
					}
				}
			}
		}
	}
}
void AIreneCharacter::SetAttackNearMonster(const FHitResult RayHit, float& NearPosition, const float FindNearTarget)const
{
	// ���� ����� ���͸� Ÿ�� ���ͷ� �����ϴ� �Լ�
	if (IreneAttack->TargetMonster == RayHit.GetActor())
	{
		NearPosition = FindNearTarget;
		IreneAttack->TargetMonster = RayHit.GetActor();
		IreneAnim->SetTargetMonster(RayHit.GetActor());
		IreneAnim->SetIsHaveTargetMonster(true);

		auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
		Mon->MarkerOn();
		Mon=Cast<AMonster>(IreneAttack->CanThrowQuillMonster);
		Mon->TargetWidgetOff();
		IreneAttack->CanThrowQuillMonster = RayHit.GetActor();
		Mon=Cast<AMonster>(IreneAttack->CanThrowQuillMonster);
		Mon->TargetWidgetOn();
		
		// ���͸� ã�� �Ĵٺ���
		const float Z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), IreneAttack->TargetMonster->GetActorLocation()).Yaw;
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, Z, 0.0f));
	}
}
void AIreneCharacter::SetQuillNearMonster(const FHitResult RayHit, float& NearPosition, const float FindNearTarget)const
{
	// ���� ����� ���͸� Ÿ�� ���ͷ� �����ϴ� �Լ�
	if (IreneAttack->CanThrowQuillMonster == RayHit.GetActor())
	{
		NearPosition = FindNearTarget;
		IreneAttack->CanThrowQuillMonster = RayHit.GetActor();
		//STARRYLOG(Warning,TEXT("%s"), *IreneAttack->CanThrowQuillMonster->GetName());
		// ���� UI ǥ���ϱ�
		const auto Mon=Cast<AMonster>(IreneAttack->CanThrowQuillMonster);
		Mon->TargetWidgetOn();
	}
}

void AIreneCharacter::FindCanThrowQuillMonster(const float DeltaTime)const
{
	auto AllPosition = SetCameraStartTargetPosition(FVector(400,200,700),CameraComp->GetComponentLocation());
	auto HitMonsterList = StartPositionFindNearMonster(AllPosition.Get<0>(),AllPosition.Get<1>(),AllPosition.Get<2>(),DeltaTime);	
	NearMonsterAnalysis(HitMonsterList.Get<0>(), HitMonsterList.Get<1>(), HitMonsterList.Get<2>(), AllPosition.Get<0>().Z, true);
}

void AIreneCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(IreneAttack->GetFollowTarget())
	{
		if(Cast<AMonster>(OtherActor))
		{
			// FindNearMonster() ���� �ٰ��� �� �浹�ϸ� ���߰� ����
			IreneInput->SetStopMoveAutoTarget();
			IreneAttack->DoAttack();
		}
	}
}
void AIreneCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}
void AIreneCharacter::NotifyHit(UPrimitiveComponent *MyComp, AActor *Other, UPrimitiveComponent *OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult &Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if(IreneAttack->GetFollowTarget())
	{
		if(Cast<AMonster>(Other))
		{
			// FindNearMonster() ���� �ٰ��� �� �浹�ϸ� ���߰� ����
			IreneInput->SetStopMoveAutoTarget();
			IreneAttack->DoAttack();
		}
	}
}

float AIreneCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(!IreneData.IsInvincibility)
	{
		if (IreneData.CurrentHP > 0)
		{
			if(IreneData.Shield > 0)
			{
				const float CurShield = IreneData.Shield;
				IreneData.Shield -= DamageAmount;
				if(IreneData.Shield <= 0)
				{
					IreneAttack->ResetWaterQuillStack();
				}
				DamageAmount -= CurShield;
				if(DamageAmount > 0)
					IreneData.CurrentHP -= DamageAmount;
			}
			else
			{
				IreneData.CurrentHP -= DamageAmount;
			}
			IreneUIManager->OnHpChanged.Broadcast();
			
			if (IreneData.CurrentHP <= 0)
			{
				ChangeStateAndLog(UDeathState::GetInstance());
				LevelRestartEvent();
			}
			else
			{
				if(!IreneState->IsChargeState() && !IreneState->IsSkillState() && !IreneState->IsAttackState() && !IreneState->IsJumpState())
				{
					ChangeStateAndLog(UHit2State::GetInstance());
				}
			}
		}
		if (IreneAttack->TargetMonster == nullptr)
		{
			if (Cast<AFeather>(DamageCauser))
				return FinalDamage;
			if (Cast<APiece>(DamageCauser))
				return FinalDamage;

			// ������ ���͸� Ÿ�� ���ͷ� ����
			IreneAttack->TargetMonster = DamageCauser;
			IreneAnim->SetTargetMonster(IreneAttack->TargetMonster);
			IreneAnim->SetIsHaveTargetMonster(true);
			auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
			Mon->MarkerOn();
			Mon=Cast<AMonster>(IreneAttack->CanThrowQuillMonster);
			Mon->TargetWidgetOff();
			IreneAttack->CanThrowQuillMonster = DamageCauser;
			Mon=Cast<AMonster>(IreneAttack->CanThrowQuillMonster);
			Mon->TargetWidgetOn();
		}
	}
	return FinalDamage;
}

#pragma endregion Collision

#pragma region State
void AIreneCharacter::ChangeStateAndLog(IState* NewState)const
{
	if(!IreneState->IsDeathState())
	{
		IreneState->ChangeState(NewState);
		//STARRYLOG(Error,TEXT("%s"), *IreneState->GetStateToString());
		IreneAnim->SetIreneStateAnim(IreneState->GetState());
	}
}

void AIreneCharacter::ActionEndChangeMoveState()const
{
	// ���� Ű �Է¿� ���� ���¸� �����ϴ� �Լ�
	if (IreneInput->MoveKey[0] > 2)
		IreneInput->MoveKey[0] -= 2;
	if (IreneInput->MoveKey[1] > 2)
		IreneInput->MoveKey[1] -= 2;
	if (IreneInput->MoveKey[2] > 2)
		IreneInput->MoveKey[2] -= 2;
	if (IreneInput->MoveKey[3] > 2)
		IreneInput->MoveKey[3] -= 2;
	
	if (IreneInput->MoveKey[0] == 0 && IreneInput->MoveKey[1] == 0 && IreneInput->MoveKey[2] == 0 && IreneInput->MoveKey[3] == 0)
	{
		ChangeStateAndLog(UIdleState::GetInstance());
	}
	else if (GetCharacterMovement()->MaxWalkSpeed == IreneData.SprintMaxSpeed)
	{
		ChangeStateAndLog(USprintLoopState::GetInstance());
	}
	else
	{
		ChangeStateAndLog(URunLoopState::GetInstance());
	}
}
#pragma endregion State

#pragma region HitFeel
float AIreneCharacter::BattleCameraRotation(UPARAM(ref) float& Angle)
{
	const FVector IreneForward = GetCapsuleComponent()->GetForwardVector();
	const FVector CameraForward = -1.0f*(CameraComp->GetForwardVector());
	const FVector CameraUp = CameraComp->GetUpVector();

    FRotator Rot(0.0f, Angle,0.0f);

	const FVector IreneRight = Rot.RotateVector(IreneForward);
	Rot = FRotator(0.0f, -Angle, 0.0f);
	const FVector IreneLeft = Rot.RotateVector(IreneForward);	
	
	const float RightAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(CameraForward, IreneRight)));
	const float LeftAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(CameraForward, IreneLeft)));

	bool bIsLeftClose = false;

	if (LeftAngle <= RightAngle)bIsLeftClose = true;

	bool bIsLeftRotation = false;
	if (bIsLeftClose)
	{
		const FVector Cross = FVector::CrossProduct(CameraForward, IreneLeft);

		const float Dot = FVector::DotProduct(CameraUp, Cross);

		if (Dot > 0)bIsLeftRotation = true;
		else bIsLeftRotation = false;
	}
	else {
		const FVector Cross = FVector::CrossProduct(CameraForward, IreneRight);

		const float Dot = FVector::DotProduct(CameraUp, Cross);

		if (Dot > 0)bIsLeftRotation = true;
		else bIsLeftRotation = false;
	}

	if (bIsLeftClose)
	{
		if (bIsLeftRotation)
		{
			return (LeftAngle / 2.5f);
		}
		else {
			return (-1.0f* (LeftAngle / 2.5f));
		}

	}
	else {
		if (bIsLeftRotation)
		{
			return (RightAngle / 2.5f);
		}
		else {
			return (-1.0f * (RightAngle / 2.5f));
		}
	}
}
void AIreneCharacter::OnRadialBlur()
{
	bIsRadialBlurOn = true;
}
void AIreneCharacter::LastAttackCameraShake(const float DeltaTime)
{
	// ������ �ؼ� ���� �浹�� �ϸ� �Լ��� ����Ǹ� ī�޶� ����ũ�� �ϴ� �Լ�
	if (CameraShakeOn)
	{
		if(!FixedUpdateCameraShakeTimer.IsValid())
		{
			constexpr float TimeSpeed = 0.01f;
			GetWorld()->GetTimerManager().SetTimer(FixedUpdateCameraShakeTimer, FTimerDelegate::CreateLambda([&]()
			{
				const float CameraShakeTime = IreneAttack->GetCameraShakeTime();
				IreneAttack->SetCameraShakeTime(CameraShakeTime + 0.1f);
			}), TimeSpeed, true);
		}
		const FVector CameraRotate = UseShakeCurve->GetVectorValue(IreneAttack->GetCameraShakeTime());
		CameraComp->SetRelativeLocation(CameraRotate);
	}
	else
	{
		IreneAttack->SetCameraShakeTime(0);
		//CameraShakeOn = false;
		CameraComp->SetRelativeLocation(FVector::ZeroVector);
		if(FixedUpdateCameraShakeTimer.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(FixedUpdateCameraShakeTimer);
			FixedUpdateCameraShakeTimer.Invalidate();
		}
	}
}
void AIreneCharacter::SetUseShakeCurve(UCurveVector* Curve)
{
	UseShakeCurve = Curve;
}
// void AIreneCharacter::DoCameraLagCurve(const float DeltaTime)
// {
// 	if(!FixedUpdateCameraLagTimer.IsValid())
// 	{
// 		constexpr float TimeSpeed = 0.01f;
// 		GetWorld()->GetTimerManager().SetTimer(FixedUpdateCameraLagTimer, FTimerDelegate::CreateLambda([&]()
// 		{
// 			const float CameraShakeTime = CameraLagTime;
// 			CameraLagTime = CameraShakeTime + 0.1f / 10.0f;
// 		}), TimeSpeed, true);
// 	}
// 	
// 	if(UseLagCurve->GetName().Compare(FString("ReturnCameraLag"))==0)
// 	{
// 		SpringArmComp->CameraLagSpeed = UseLagCurve->GetFloatValue(CameraLagTime) * LastLagTime;		
// 	}
// 	else
// 	{
// 		SpringArmComp->CameraLagSpeed = UseLagCurve->GetFloatValue(CameraLagTime);
// 	}
// }
void AIreneCharacter::SetUseCameraLag(UCurveFloat* Curve)
{
	UseLagCurve = Curve;
}
void AIreneCharacter::PlayFadeInAnimation()
{
	IreneUIManager->PlayHUDAnimation();
}
void AIreneCharacter::SetIreneDialog()
{
	ChangeStateAndLog(UIdleState::GetInstance());
}
void AIreneCharacter::SetBattleCamera()
{
	IreneData.BattleCameraZPosition = IreneData.MaxBattleCameraZPosition;
}
void AIreneCharacter::SetRaidBattleCamera()
{
	IreneData.BattleCameraZPosition = IreneData.MaxRaidCameraZPosition;
}

void AIreneCharacter::SetFirstLevel(bool isFirst)
{
	IreneUIManager->PlayerHud->bIsFirstLevel = isFirst;
}

void AIreneCharacter::PlayFadeOutAnimation()
{
	PlayFadeOutEvent();
}
#pragma endregion HitFeel

#pragma region StopWatch
//��ž��ġ ��Ʈ�� �Լ�
//void AIreneCharacter::WatchControl()
//{
//	StopWatch->WatchControl();
//}
//
//void AIreneCharacter::WatchReset()
//{
//	StopWatch->WatchReset();
//}
#pragma endregion StopWatch
