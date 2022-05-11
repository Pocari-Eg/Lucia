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
#include "Kismet/GameplayStatics.h"
#include "../StarryTailGameMode.h"
#include "IreneUIManager.h"
#include "IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneAttackInstance.h"
#include "IreneInputInstance.h"
#include "WaterBasicAttack.h"

#pragma region Setting
// Sets default values
AIreneCharacter::AIreneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���̷��� �޽� ����
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Animation/Irene/Animation/Idle.Idle"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -80), FRotator(0, 270, 0));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
		GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
		GetCapsuleComponent()->SetGenerateOverlapEvents(true);
		//����
		const FName WeaponSocket(TEXT("hand_rSwordSocket"));
		if (GetMesh()->DoesSocketExist(WeaponSocket))
		{
			Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_WEAPON(TEXT("/Game/Animation/Irene/Weapon/Sword.Sword"));
			if (SK_WEAPON.Succeeded())
			{
				Weapon->SetSkeletalMesh(SK_WEAPON.Object);
			}
			Weapon->SetupAttachment(GetMesh(), WeaponSocket);
			//�ݸ��� ����
			Weapon->SetCollisionProfileName(TEXT("PlayerAttack"));
			Weapon->SetGenerateOverlapEvents(false);
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
	const ConstructorHelpers::FObjectFinder<UCurveFloat>CameraCurveDataObject(TEXT("/Game/Math/CameraShakeCurve.CameraShakeCurve"));
	if (CameraCurveDataObject.Succeeded())
	{
		CameraShakeCurve.Add(CameraCurveDataObject.Object);
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
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

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
	FireRecoveryData.bIsRecovering = false;
	WaterRecoveryData.bIsRecovering = false;
	ElectricRecoveryData.bIsRecovering = false;

	// PlayerCharacterDataStruct.h�� ������ �ʱ�ȭ
	IreneData.CurrentHP = IreneData.MaxHP;
	IreneData.CurrentMP = IreneData.MaxMP;

	CameraShakeOn = false;

	HpRecoveryData.Amount = 300;
	HpRecoveryData.HP_Re_Time = 4;
	HpRecoveryData.Speed = 5;
	HpRecoveryData.Time = 10;
	FireRecoveryData.Amount = 200;
	FireRecoveryData.Fire_Re_Time = 2;
	FireRecoveryData.Speed = 4.0f;
	FireRecoveryData.Time = 0;
	WaterRecoveryData.Amount = 200;
	WaterRecoveryData.Water_Re_Time = 2;
	WaterRecoveryData.Speed = 4.0f;
	WaterRecoveryData.Time = 0;
	ElectricRecoveryData.Amount = 200;
	ElectricRecoveryData.Electric_Re_Time = 2;
	ElectricRecoveryData.Speed = 4.0f;
	ElectricRecoveryData.Time = 0;
}

// Called when the game starts or when spawned
void AIreneCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ��Ʈ�ѷ� �޾ƿ���
	WorldController = GetWorld()->GetFirstPlayerController();

	//���缷
	const auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (nullptr == GameInstance)
	{
		STARRYLOG(Error, TEXT("GameInstance is Not STGameInstance"));
	}
	else
	{
		GameInstance->SetPlayer(this);
	}

	//��ž��ġ ���� 
	//StopWatch = GetWorld()->SpawnActor<AStopWatch>(FVector::ZeroVector, FRotator::ZeroRotator);
	//StopWatch->InitStopWatch();

	// �ִϸ��̼� �Ӽ� �ʱ�ȭ
	IreneAnim->SetAttribute(IreneAttack->GetAttribute());
	IreneUIManager->Begin();

	FOnAttributeChange.Broadcast();
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
					IreneAnim->JumpToAttackMontageSection(IreneData.CurrentCombo);
				if (IreneInput->bUseRightButton)
					IreneAnim->JumpToEffectAttackMontageSection(IreneData.CurrentCombo);
			}
		});
	IreneAnim->OnAttackHitCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackCheck);
	IreneAnim->OnAttackStopCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackStopCheck);
	IreneAnim->OnFootStep.AddUObject(IreneUIManager, &UIreneUIManager::FootStepSound);
}
#pragma endregion Setting

// Called every frame
void AIreneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// �뽬�����϶� MoveAuto�� ���� �̵��� ��Ŵ
	if (IreneState->GetStateToString().Compare(FString("Dodge")) != 0)
	{
		if (IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0)
		{
			IreneInput->MoveForward();
			IreneInput->MoveRight();
		}
		else
			IreneInput->MoveAuto();
	}
	else
	{
		IreneInput->MoveAuto();
	}
	if (IreneInput->GetFallingRoll() && !GetMovementComponent()->IsFalling())
	{
		//�����ٰ� ���� ����
		IreneInput->SetFallingRoll(false);
		IreneInput->DodgeKeyword();
	}
	IreneInput->MoveStop();

	if (IreneData.IsInvincibility == true)
		SetActorEnableCollision(false);

	// ���� �׷��� ���
	if (IreneInput->GetStartJump())
	{
		const float JumpTime = IreneInput->GetJumpingTime();
		IreneInput->SetJumpingTime(JumpTime+DeltaTime);
		GetCharacterMovement()->GravityScale = JumpGravityCurve->GetFloatValue(JumpTime);
	}
	if (!GetCharacterMovement()->IsFalling())
	{
		IreneInput->SetJumpingTime(0);
		IreneInput->SetStartJump(false);
	}

	// ī�޶� ����ũ �׷��� ���
	if (IreneData.IsAttacking && IreneData.CurrentCombo == IreneData.MaxCombo && CameraShakeOn)
	{
		const float CameraShakeTime = IreneAttack->GetCameraShakeTime();
		IreneAttack->SetCameraShakeTime(DeltaTime);
		FRotator CameraRotate = CameraComp->GetRelativeRotation();
		CameraRotate.Pitch += CameraShakeCurve[0]->GetFloatValue(CameraShakeTime * 50);
		CameraComp->SetRelativeRotation(CameraRotate);
	}
	else
	{
		IreneAttack->SetCameraShakeTime(0);
		CameraShakeOn = false;
		CameraComp->SetRelativeRotation(FRotator::ZeroRotator);
	}

	// ��¡ ���
	//if(IsCharging)
	//{
	//	ChargingTime += DeltaTime;
	//}

	if (IreneAttack->TargetMonster != nullptr)
	{
		//if (bShowLog)
			//UE_LOG(LogTemp, Error, TEXT("Target Name: %s, Dist: %f"), *TargetMonster->GetName(), FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()));
		// Ÿ�ٸ��� �װų� �Ÿ��� �־����� �ʱ�ȭ
		const auto Mob = Cast<AMonster>(IreneAttack->TargetMonster);
		if (Mob != nullptr)
		{
			if (Mob->GetHp() <= 0 || FVector::Dist(GetActorLocation(), IreneAttack->TargetMonster->GetActorLocation()) > 700.0f)
			{
				auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
				Mon->MarkerOff();
				IreneAnim->SetIsHaveTargetMonster(false);
				IreneAttack->TargetMonster = nullptr;
			}			
		}
	}

	// ī�޶� ȸ��
	// if (IreneAttack->bFollowCameraTarget)
	// {
	// 	const float Dist = FVector::Dist(IreneAttack->CameraRot.Vector(), IreneAttack->TargetCameraRot.Vector());
	// 	IreneAttack->FollowTargetCameraAlpha += GetWorld()->GetDeltaSeconds() * IreneData.TargetCameraFollowSpeed / Dist;
	// 	if (IreneAttack->FollowTargetCameraAlpha >= 1)
	// 	{
	// 		IreneAttack->FollowTargetCameraAlpha = 1;
	// 	}
	// 	const FRotator Tar = FMath::Lerp(IreneAttack->CameraRot, IreneAttack->TargetCameraRot, IreneAttack->FollowTargetCameraAlpha);
	// 	WorldController->SetControlRotation(Tar);
	// 	if (IreneAttack->FollowTargetCameraAlpha >= 1)
	// 	{
	// 		IreneAttack->bFollowCameraTarget = false;
	// 		IreneAttack->FollowTargetCameraAlpha = 0.0f;
	// 		IreneAttack->CameraRot = FRotator::ZeroRotator;
	// 		IreneAttack->TargetCameraRot = FRotator::ZeroRotator;
	// 	}
	// }

	IreneInput->RecoveryStaminaGauge(DeltaTime);
	IreneState->Update(DeltaTime);
}

// Called to bind functionality to input
void AIreneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// ������ ���� Ű���� �Է�
	PlayerInputComponent->BindAction("Jump", IE_Pressed, IreneInput, &UIreneInputInstance::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, IreneInput, &UIreneInputInstance::StopJump);

	PlayerInputComponent->BindAction("MoveW", IE_Pressed, IreneInput, &UIreneInputInstance::MovePressedW);
	PlayerInputComponent->BindAction("MoveA", IE_Pressed, IreneInput, &UIreneInputInstance::MovePressedA);
	PlayerInputComponent->BindAction("MoveS", IE_Pressed, IreneInput, &UIreneInputInstance::MovePressedS);
	PlayerInputComponent->BindAction("MoveD", IE_Pressed, IreneInput, &UIreneInputInstance::MovePressedD);
	PlayerInputComponent->BindAction("MoveW", IE_DoubleClick, IreneInput, &UIreneInputInstance::MoveDoubleClickW);
	PlayerInputComponent->BindAction("MoveA", IE_DoubleClick, IreneInput, &UIreneInputInstance::MoveDoubleClickA);
	PlayerInputComponent->BindAction("MoveS", IE_DoubleClick, IreneInput, &UIreneInputInstance::MoveDoubleClickS);
	PlayerInputComponent->BindAction("MoveD", IE_DoubleClick, IreneInput, &UIreneInputInstance::MoveDoubleClickD);
	PlayerInputComponent->BindAction("MoveW", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedW);
	PlayerInputComponent->BindAction("MoveA", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedA);
	PlayerInputComponent->BindAction("MoveS", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedS);
	PlayerInputComponent->BindAction("MoveD", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedD);

	// ������ �� Ű���� �Է�
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, IreneInput, &UIreneInputInstance::DodgeKeyword);
	PlayerInputComponent->BindAxis("WaterDodge", IreneInput, &UIreneInputInstance::WaterDodgeKeyword);
	PlayerInputComponent->BindAction("MouseCursor", IE_Pressed, IreneInput, &UIreneInputInstance::MouseCursorKeyword);

	// ���콺
	PlayerInputComponent->BindAxis("Turn", IreneInput, &UIreneInputInstance::Turn);
	PlayerInputComponent->BindAxis("LookUp", IreneInput, &UIreneInputInstance::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", IreneInput, &UIreneInputInstance::LeftButton);
	PlayerInputComponent->BindAction("RightButton", IE_Pressed, IreneInput, &UIreneInputInstance::RightButtonPressed);
	PlayerInputComponent->BindAction("RightButton", IE_Released, IreneInput, &UIreneInputInstance::RightButtonReleased);
	PlayerInputComponent->BindAxis("MouseWheel", IreneInput, &UIreneInputInstance::MouseWheel);
	PlayerInputComponent->BindAxis("RightButtonAxis", IreneInput, &UIreneInputInstance::RightButton);
	PlayerInputComponent->BindAction("FireKeyword", IE_Released, IreneInput, &UIreneInputInstance::FireKeywordReleased);
	PlayerInputComponent->BindAction("WaterKeyword", IE_Released, IreneInput, &UIreneInputInstance::WaterKeywordReleased);
	PlayerInputComponent->BindAction("ElectricKeyword", IE_Released, IreneInput, &UIreneInputInstance::ElectricKeywordReleased);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, IreneInput, &UIreneInputInstance::PauseWidgetOn);
	
	//������
	//��ž��ġ ��Ʈ��
	/*PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchControl);
	PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);*/
}

#pragma region Collision
void AIreneCharacter::FindNearMonster()
{
	if(IreneAttack->TargetMonster!=nullptr && GetAnimName()==FName("B_Attack_1"))
	{
		auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
		Mon->MarkerOff();
		IreneAnim->SetIsHaveTargetMonster(false);
		IreneAttack->TargetMonster = nullptr;
	}
	FString AttributeForm = GetAnimName().ToString();

	if(IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire && (GetAnimName()!=FName("B_Attack_5_F")&& GetAnimName()!=FName("ActionKeyword_1_F")))
	{
		AttributeForm = GetAnimName().ToString() + FString("_F");
	}
	else if(IreneAttack->GetAttribute() == EAttributeKeyword::e_Water && (GetAnimName()!=FName("B_Attack_5_W")&& GetAnimName()!=FName("ActionKeyword_1_W")))
	{
		AttributeForm = GetAnimName().ToString() + FString("_W");
	}
	else if(IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder && (GetAnimName()!=FName("B_Attack_5_E")&& GetAnimName()!=FName("ActionKeyword_1_E")))
	{
		AttributeForm = GetAnimName().ToString() + FString("_E");
	}
	TUniquePtr<FAttackDataTable> Table = MakeUnique<FAttackDataTable>(*IreneAttack->GetNameAtAttackDataTable(FName(AttributeForm)));
	if (Table != nullptr)
	{
		IreneData.Strength = Table->ATTACK_DAMAGE_1;
	
		// ���� ��� ����
		if (Table->Form > 1 && IreneAttack->GetAttribute() != EAttributeKeyword::e_None)
		{
			IreneAttack->SetUseMP(true);
			// if (IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire) {
			// 	IreneAttack->FormGauge[0] -= table->Gauge;
			// 	IreneAttack->FOnFireGaugeChange.Broadcast();
			// }
			// else if (IreneAttack->GetAttribute() == EAttributeKeyword::e_Water) {
			// 	IreneAttack->FormGauge[1] -= table->Gauge;
			// 	IreneAttack->FOnWaterGaugeChange.Broadcast();
			// }
			// else if (IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder) {
			// 	IreneAttack->FormGauge[2] -= table->Gauge;
			// 	IreneAttack->FOnElectricGaugeChange.Broadcast();
			// }
			//IreneAttack->UseMP = table->Gauge;
		}
		// ���� ȸ�� ����
		if (Table->Form < 2)
		{
			IreneAttack->SetUseMP(false);
			IreneAttack->SetUseMPSize(0);
		}
	
		IreneUIManager->OnMpChanged.Broadcast();
	}

	// if (TargetMonster != nullptr)
	// {
	// 	// Ÿ���� ĳ������ �ڿ� �ִٸ� ���� ���
	// 	FVector targetData = TargetMonster->GetActorLocation() - GetActorLocation();
	// 	targetData.Normalize();
	// 	if (FVector::DotProduct(GetActorForwardVector(), targetData) < 0)
	// 	{
	// 		TargetMonster = nullptr;
	// 	}
	// }

	float far = 300;
	if(IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		far = 500;
	// ����, ����, ����
	FVector BoxSize = FVector(200, 50, far);
	// �ִ�Ÿ�
	float NearPosition = far;

	// ����Ʈ�� ��� �浹 ��� ��´�.
	TArray<FHitResult> MonsterList;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepMultiByChannel(
		MonsterList,
		GetActorLocation() + GetActorForwardVector() * far,
		GetActorLocation() + GetActorForwardVector() * far,
		FRotationMatrix::MakeFromZ(GetActorForwardVector() * far).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel8,
		FCollisionShape::MakeBox(BoxSize * 1),
		Params);
	
	#if ENABLE_DRAW_DEBUG
		FVector TraceVec = GetActorForwardVector() * far;
		FVector Center = GetActorLocation() + TraceVec + (GetActorForwardVector()*-150.0f);
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Magenta : FColor::Blue;
		float DebugLifeTime = 5.0f;

		DrawDebugBox(GetWorld(), Center, BoxSize, CapsuleRot, DrawColor, false, DebugLifeTime);
	#endif

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
				FName RayCollisionProfileName = RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
				FName EnemyProfile = "Enemy";
				FName ObjectProfile = "Object";

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
						IreneAnim->SetTargetMonster(IreneAttack->TargetMonster->GetActorLocation());
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
							if (TargetCollisionProfileName == EnemyProfile && RayCollisionProfileName == EnemyProfile)
							{
								NearPosition = FindNearTarget;
								if (IreneAttack->TargetMonster == nullptr)
									{
									IreneAttack->TargetMonster = RayHit.GetActor();
									IreneAnim->SetTargetMonster(IreneAttack->TargetMonster->GetActorLocation());
									IreneAnim->SetIsHaveTargetMonster(true);
								}
							}
							else if (TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == EnemyProfile)
							{
								NearPosition = FindNearTarget;
								if (IreneAttack->TargetMonster == nullptr)
								{
									IreneAttack->TargetMonster = RayHit.GetActor();
									IreneAnim->SetTargetMonster(IreneAttack->TargetMonster->GetActorLocation());
									IreneAnim->SetIsHaveTargetMonster(true);
								}
							}
							else if (TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == ObjectProfile)
							{
								NearPosition = FindNearTarget;
								if (IreneAttack->TargetMonster == nullptr)
								{
									IreneAttack->TargetMonster = RayHit.GetActor();
									IreneAnim->SetTargetMonster(IreneAttack->TargetMonster->GetActorLocation());
									IreneAnim->SetIsHaveTargetMonster(true);
								}
							}
						}
						else
						{
							NearPosition = FindNearTarget;
							if (IreneAttack->TargetMonster == nullptr)
							{
								IreneAttack->TargetMonster = RayHit.GetActor();
								IreneAnim->SetTargetMonster(IreneAttack->TargetMonster->GetActorLocation());
								IreneAnim->SetIsHaveTargetMonster(true);
							}
						}
					}
				}
			}
		}
	}
	// if(IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
	// {
	// 	if(IreneAttack->TargetMonster)
	// 	{
	// 		AWaterBasicAttack* WaterBasic = GetWorld()->SpawnActor<AWaterBasicAttack>(IreneAttack->TargetMonster->GetActorLocation() - GetActorForwardVector() * 300, GetActorForwardVector().Rotation());
	// 	}
	// 	else
	// 	{
	// 		AWaterBasicAttack* WaterBasic = GetWorld()->SpawnActor<AWaterBasicAttack>(GetActorLocation() + GetActorForwardVector() * 300, GetActorForwardVector().Rotation());
	// 	}
	// }
	// ���͸� ã�� �Ĵٺ���
	if (IreneAttack->TargetMonster != nullptr)
	{		
		if(GetAnimName() == FName("B_Attack_1") || IreneInput->bUseRightButton)
		{
			auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
			Mon->MarkerOn();
			//UE_LOG(LogTemp, Error, TEXT("Target Name: %s, Dist: %f"), *TargetMonster->GetName(), FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()));
			float z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), IreneAttack->TargetMonster->GetActorLocation()).Yaw;
			GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, z, 0.0f));
			
			//IreneAttack->bFollowCameraTarget = true;
			//IreneAttack->CameraRot = WorldController->GetControlRotation();
			//FRotator ForwardRotator = GetActorForwardVector().Rotation();
			//IreneAttack->TargetCameraRot = FRotator(ForwardRotator.Pitch + WorldController->GetControlRotation().Pitch, ForwardRotator.Yaw, ForwardRotator.Roll);

			auto CharacterRadius = GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorScale().X;
			auto MonsterRadius = Mon->GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorScale().X;
			
			float TargetPos = FVector::Dist(GetActorLocation(), Mon->GetLocation());

			// ���Ͱ� ���ݹ��� ���� �ָ� �ִٸ�
			if (TargetPos - (CharacterRadius + MonsterRadius) > IreneData.AttackRange && IreneAttack->GetAttribute() != EAttributeKeyword::e_Water)
			{
				// ���� ����
				IreneAttack->SetFollowTarget(true);
				IreneAttack->SetPlayerPosVec(GetActorLocation());
				IreneAttack->SetTargetPosVec(GetActorLocation() + GetActorForwardVector() * TargetPos);
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
	IreneInput->bUseRightButton = false;
}
void AIreneCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(IreneAttack->GetFollowTarget())
	{
		if(Cast<AMonster>(OtherActor))
		{
			IreneAttack->SetFollowTarget(false);
			IreneAttack->SetFollowTargetAlpha(0);
			IreneAttack->SetPlayerPosVec(FVector::ZeroVector);
			IreneAttack->SetTargetPosVec(FVector::ZeroVector);
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
			IreneAttack->SetFollowTarget(false);
			IreneAttack->SetFollowTargetAlpha(0);
			IreneAttack->SetPlayerPosVec(FVector::ZeroVector);
			IreneAttack->SetTargetPosVec(FVector::ZeroVector);
			IreneAttack->DoAttack();
		}
	}
}

float AIreneCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (IreneData.CurrentHP > 0)
	{
		IreneData.CurrentHP -= DamageAmount - IreneData.Defenses;
		//hp ��
		IreneUIManager->OnHpChanged.Broadcast();
		ChangeStateAndLog(UHitState::GetInstance());
		if (IreneData.CurrentHP <= 0)
		{
			IreneAnim->StopAllMontages(0);
			IreneAnim->SetDeadAnim(true);
			ChangeStateAndLog(UDeathState::GetInstance());
		}
	}
	if (IreneAttack->TargetMonster == nullptr)
	{
		IreneAttack->TargetMonster = DamageCauser;
		IreneAnim->SetTargetMonster(IreneAttack->TargetMonster->GetActorLocation());
		IreneAnim->SetIsHaveTargetMonster(true);
	}
	return FinalDamage;
}

#pragma endregion Collision

#pragma region State
void AIreneCharacter::ChangeStateAndLog(IState* NewState)
{
	if ((IreneState->GetStateToString().Compare(FString("Dodge")) != 0 &&
		IreneState->GetStateToString().Compare(FString("Death")) != 0) ||
		NewState == UDeathState::GetInstance())
	{
		if (IreneState->GetStateToString().Compare(FString("Sprint")) != 0)
		{
			IreneAnim->SetSprintStateAnim(false);
			IreneAnim->SetSprintStopAnim(false);
		}
		else
		{
			IreneAnim->SetSprintStateAnim(true);
		}
		IreneState->ChangeState(NewState);
		IreneAnim->SetIreneStateAnim(IreneState->GetState());

		if (NewState == URunState::GetInstance() || NewState == USprintState::GetInstance())
			Weapon->SetVisibility(false);
		else
			Weapon->SetVisibility(true);

		if(NewState == UIdleState::GetInstance())
			IreneUIManager->HPRecoveryWaitStart();
		else {
			if (HpRecoveryData.bIsRecovering == true)IreneUIManager->HpRecoveringCancel();
			else IreneUIManager->HPRecoveryWaitCancel();
		}
	}
}

void AIreneCharacter::ActionEndChangeMoveState()
{
	IreneInput->MoveAutoDirection = FVector(0, 0, 0);

	if (IreneInput->MoveKey[0] > 2)
		IreneInput->MoveKey[0] -= 2;
	if (IreneInput->MoveKey[1] > 2)
		IreneInput->MoveKey[1] -= 2;
	if (IreneInput->MoveKey[2] > 2)
		IreneInput->MoveKey[2] -= 2;
	if (IreneInput->MoveKey[3] > 2)
		IreneInput->MoveKey[3] -= 2;

	if (IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		IreneState->SetState(nullptr);
	}
	if (IreneInput->MoveKey[0] == 0 && IreneInput->MoveKey[1] == 0 && IreneInput->MoveKey[2] == 0 && IreneInput->MoveKey[3] == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = IreneData.RunMaxSpeed;
		ChangeStateAndLog(UIdleState::GetInstance());
	}
	else if (IreneInput->MoveKey[0] == 2 || IreneInput->MoveKey[1] == 2 || IreneInput->MoveKey[2] == 2 || IreneInput->MoveKey[3] == 2)
	{
		GetCharacterMovement()->MaxWalkSpeed = IreneData.SprintMaxSpeed;
		ChangeStateAndLog(USprintState::GetInstance());
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = IreneData.RunMaxSpeed;
		ChangeStateAndLog(URunState::GetInstance());
	}
}

FName AIreneCharacter::GetAnimName()
{
	if (IreneState->GetStateToString().Compare(FString("Dodge")) == 0)
	{
		return FName("Dodge");
	}
	if (IreneState->GetStateToString().Compare(FString("Jump")) == 0)
	{
		return FName("Jump");
	}
	if (IreneInput->bUseLeftButton)
	{
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack1"))
		{
			return FName("B_Attack_1");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack2"))
		{
			return FName("B_Attack_2");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack3"))
		{
			return FName("B_Attack_3");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack4"))
		{
			return FName("B_Attack_4");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && IreneAttack->GetAttribute() == EAttributeKeyword::e_None)
		{
			return FName("B_Attack_5_N");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
		{
			return FName("B_Attack_5_F");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		{
			return FName("B_Attack_5_W");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
		{
			return FName("B_Attack_5_E");
		}
	}
	if (IreneInput->bUseRightButton)
	{
		if (IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
		{
			return FName("ActionKeyword_1_F");
		}
		if (IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		{
			return FName("ActionKeyword_1_W");
		}
		if (IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
		{
			return FName("ActionKeyword_1_E");
		}
	}
	return FName("");
}
#pragma endregion State

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
