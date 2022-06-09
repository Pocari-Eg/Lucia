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

#pragma region Setting
// Sets default values
AIreneCharacter::AIreneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		WeaponSocketNameArray.Add(TEXT("hand_rSwordSocket"));
		WeaponSocketNameArray.Add(TEXT("hand_lWandSocket"));
		WeaponSocketNameArray.Add(TEXT("hand_rSpearSocket"));

		if (GetMesh()->DoesSocketExist(WeaponSocketNameArray[0]) && GetMesh()->DoesSocketExist(WeaponSocketNameArray[1]) && GetMesh()->DoesSocketExist(WeaponSocketNameArray[2]))
		{
			Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Sword(TEXT("/Game/Animation/Irene/Weapon/Sword.Sword"));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Wand(TEXT("/Game/Animation/Irene/Weapon/Wand.Wand"));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Spear(TEXT("/Game/Animation/Irene/Weapon/Spear.Spear"));

			if (SK_Sword.Succeeded())
			{
				WeaponMeshArray.Add(SK_Sword.Object);
			}
			if(SK_Wand.Succeeded())
			{
				WeaponMeshArray.Add(SK_Wand.Object);
			}
			if(SK_Spear.Succeeded())
			{
				WeaponMeshArray.Add(SK_Spear.Object);
			}
			Weapon->SetSkeletalMesh(WeaponMeshArray[0]);
			Weapon->SetupAttachment(GetMesh(), WeaponSocketNameArray[0]);
			Weapon->SetCollisionProfileName(TEXT("PlayerAttack"));
			Weapon->SetGenerateOverlapEvents(false);
			Weapon->SetVisibility(false);
		}
		
		//ī�޶�
		//FName CameraSocket(TEXT("Hip_Socket"));
		//if (GetMesh()->DoesSocketExist(CameraSocket))
		//{
			// �������� ����
			//SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
			//SpringArmComp->TargetArmLength = CharacterDataStruct.FollowCameraZPosition;
			//SpringArmComp->bEnableCameraLag = true;
			//SpringArmComp->CameraLagSpeed = 0.0f;
			//SpringArmComp->SetupAttachment(GetMesh(), CameraSocket);
		//}

		// �������Ʈ �ִϸ��̼� ����
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Animation/Irene/Animation/BP/BP_IreneAnimation.BP_IreneAnimation_C"));

		if (CharacterAnimInstance.Succeeded())
		{
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
		}
	}
	// ����Ŀ��
	const ConstructorHelpers::FObjectFinder<UCurveFloat>JumpCurve(TEXT("/Game/Math/Jump.Jump"));
	if (JumpCurve.Succeeded())
	{
		JumpGravityCurve = JumpCurve.Object;
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

	const ConstructorHelpers::FObjectFinder<UParticleSystem>Pe_Water1(TEXT("/Game/Effect/VFX_Irene/Water/W_BasicAtk_PS/PS_W_atk1.PS_W_atk1"));
	const ConstructorHelpers::FObjectFinder<UParticleSystem>Pe_Water2(TEXT("/Game/Effect/VFX_Irene/Water/W_BasicAtk_PS/PS_W_atk2.PS_W_atk2"));
	const ConstructorHelpers::FObjectFinder<UParticleSystem>Pe_Water3(TEXT("/Game/Effect/VFX_Irene/Water/W_BasicAtk_PS/PS_W_atk3.PS_W_atk3"));
	if (Pe_Water1.Succeeded() && Pe_Water2.Succeeded() && Pe_Water3.Succeeded())
	{
		WaterParticle.Add(Pe_Water1.Object);
		WaterParticle.Add(Pe_Water2.Object);
		WaterParticle.Add(Pe_Water3.Object);
	}
	
	// �ݶ��̴� ����
	GetCapsuleComponent()->InitCapsuleSize(25.f, 80.0f);

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
	Weapon->SetSkeletalMesh(WeaponMeshArray[1]);
	Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketNameArray[1]);
	
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
	IreneAnim->SetAttribute(IreneAttack->GetAttribute());
	
	IreneUIManager->Begin();
	IreneInput->Begin();
	
	FOnAttributeChange.Broadcast();

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
	
	IreneAnim->OnMontageEnded.AddDynamic(IreneAttack, &UIreneAttackInstance::OnAttackMontageEnded);
	IreneAnim->OnNextAttackCheck.AddLambda([this]()->void
		{
			IreneData.CanNextCombo = false;
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
		const auto Mob = Cast<AMonster>(IreneAttack->TargetMonster);
		if (Mob != nullptr)
		{
			if (Mob->GetHp() <= 0 || FVector::Dist(GetActorLocation(), IreneAttack->TargetMonster->GetActorLocation()) > 700.0f)
			{
				const auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
				Mon->MarkerOff();
				IreneAnim->SetIsHaveTargetMonster(false);
				IreneAnim->SetTargetMonster(nullptr);
				IreneAttack->TargetMonster = nullptr;				
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
	IreneInput->RightButton(DeltaTime);
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, IreneInput, &UIreneInputInstance::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, IreneInput, &UIreneInputInstance::StopJump);

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
	
	// �� ���� �ڽ� ũ��
	float Far = 200;
	if(IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		Far = 500;
	// ����, ����, �Ÿ�
	const FVector BoxSize = FVector(150, 50, Far);

	// ����Ʈ�� ��� �浹 ��� ��´�.
	TArray<FHitResult> MonsterList;
	const FCollisionQueryParams Params(NAME_None, false, this);
	const bool bResult = GetWorld()->SweepMultiByChannel(
		MonsterList,
		GetActorLocation() + GetActorForwardVector() * (Far - 150.0f),
		GetActorLocation() + GetActorForwardVector() * (Far - 150.0f),
		FRotationMatrix::MakeFromZ(GetActorForwardVector() * Far).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel8,
		FCollisionShape::MakeBox(BoxSize),
		Params);

	#if ENABLE_DRAW_DEBUG
		const FVector TraceVec = GetActorForwardVector() * Far;
		const FVector Center = GetActorLocation() + TraceVec + (GetActorForwardVector() * -150.0f);
		const FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		const FColor DrawColor = bResult ? FColor::Magenta : FColor::Blue;
		constexpr float DebugLifeTime = 5.0f;

		DrawDebugBox(GetWorld(), Center, BoxSize, CapsuleRot, DrawColor, false, DebugLifeTime);
	#endif

	NearMonsterAnalysis(MonsterList, bResult, Params, Far);
	if(IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		PlayWaterEffect();
	
	// ���͸� ã�� �Ĵٺ���
	if (IreneAttack->TargetMonster != nullptr)
	{
		// ���� ���󰡴� ����
		if(IreneState->IsFirstAttack() || IreneInput->bUseRightButton)
		{
			const auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
			Mon->MarkerOn();
			const float Z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), IreneAttack->TargetMonster->GetActorLocation()).Yaw;
			GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, Z, 0.0f));

			// �ٰ������ϴ� �Ÿ� ���
			const auto CharacterRadius = GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorScale().X;
			const auto MonsterRadius = Mon->GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorScale().X;			
			const float TargetPos = FVector::Dist(GetActorLocation(), Mon->GetLocation());
			
			// ���Ͱ� ���ݹ��� ���� �ָ� �ִٸ�
			if (TargetPos - (CharacterRadius + MonsterRadius) > IreneData.AttackRange && IreneAttack->GetAttribute() != EAttributeKeyword::e_Water)
			{
				// ���� ����
				IreneInput->SetStartMoveAutoTarget(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * TargetPos);
			}
			else
			{
				IreneAttack->DoAttack();
			}
		}
		else
		{
			IreneAttack->DoAttack();
		}
	}
}
void AIreneCharacter::NearMonsterAnalysis(const TArray<FHitResult> MonsterList, const bool bResult, const FCollisionQueryParams Params, const float Far)const
{
	// ���� �浹ü �� ���� ����� �浹ü �ϳ��� �����ϴ� �Լ�
	// �ִ�Ÿ�
	float NearPosition = Far;
	
	for (FHitResult Monster : MonsterList)
	{
		if (bResult)
		{
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
				// �Ÿ� �ּ� ã��
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
					FName TargetCollisionProfileName;

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
								SetNearMonster(RayHit,NearPosition,FindNearTarget);
							}
						}
						else
						{
							SetNearMonster(RayHit,NearPosition,FindNearTarget);
						}
					}
				}
			}
		}
	}
}
void AIreneCharacter::SetNearMonster(const FHitResult RayHit, float& NearPosition, const float FindNearTarget)const
{
	// ���� ����� ���͸� Ÿ�� ���ͷ� �����ϴ� �Լ�
	NearPosition = FindNearTarget;
	if (IreneAttack->TargetMonster == nullptr)
	{
		IreneAttack->TargetMonster = RayHit.GetActor();
		IreneAnim->SetTargetMonster(RayHit.GetActor());
		IreneAnim->SetIsHaveTargetMonster(true);
	}
}
void AIreneCharacter::PlayWaterEffect()
{
	if(IreneAttack->TargetMonster)
	{
		const auto CastMonster = Cast<AMonster>(IreneAttack->TargetMonster);
		if(CastMonster == nullptr)
		{
			return;
		}
		if(IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack1"))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterParticle[0], CastMonster->GetLocation());
		}
		else if(IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack2"))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterParticle[1], CastMonster->GetLocation());
		}
		else if(IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack3"))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterParticle[2], CastMonster->GetLocation());
		}
	}
	else
	{
		const FVector Location = GetActorLocation() + GetActorForwardVector() * 800;
		if(IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack1"))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterParticle[0],Location);
		}
		else if(IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack2"))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterParticle[1],Location);
		}
		else if(IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack3"))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterParticle[2],Location);
		}
	}
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
			IreneData.CurrentHP -= DamageAmount - IreneData.Defenses;
			IreneUIManager->OnHpChanged.Broadcast();
			
			if (IreneData.CurrentHP <= 0)
			{
				ChangeStateAndLog(UDeathState::GetInstance());
				LevelRestartEvent();
			}
			else
			{
				if(!IreneState->IsChargeState())
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
			const auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
			Mon->MarkerOn();
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
		STARRYLOG(Error,TEXT("%s"), *IreneState->GetStateToString());
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
