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

	// PlayerCharacterDataStruct.h�� ������ �ʱ�ȭ
	IreneData.CurrentHP = IreneData.MaxHP;
	IreneData.CurrentStamina = IreneData.MaxStamina;

	CameraShakeOn = false;

	HpRecoveryData.Amount = 300;
	HpRecoveryData.HP_Re_Time = 4;
	HpRecoveryData.Speed = 5;
	HpRecoveryData.Time = 10;
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

void AIreneCharacter::TargetReset()const
{
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
	TargetReset();
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
	PlayerInputComponent->BindAction("MoveW", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedW);
	PlayerInputComponent->BindAction("MoveA", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedA);
	PlayerInputComponent->BindAction("MoveS", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedS);
	PlayerInputComponent->BindAction("MoveD", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedD);

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
	PlayerInputComponent->BindAction("Pause", IE_Pressed, IreneInput, &UIreneInputInstance::PauseWidgetOn);
	
	//������
	//��ž��ġ ��Ʈ��
	/*PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchControl);
	PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);*/
}

#pragma region Collision
void AIreneCharacter::FindNearMonster()
{
	if(IreneAttack->TargetMonster!=nullptr && IreneState->IsFirstAttack())
	{
		// ���� Ÿ���� ���
		const auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
		Mon->MarkerOff();
		IreneAnim->SetIsHaveTargetMonster(false);
		IreneAttack->TargetMonster = nullptr;
	}

	TUniquePtr<FAttackDataTable> Table;
	if(IreneState->GetStateToAttackDataTableName() != FName("Error GetStateToAttackDataTableName"))	
		Table = MakeUnique<FAttackDataTable>(*IreneAttack->GetNameAtAttackDataTable(IreneState->GetStateToAttackDataTableName()));	
	else	
		Table = MakeUnique<FAttackDataTable>(*IreneAttack->GetNameAtAttackDataTable(FName("B_Attack_1_F")));
	
	if (Table != nullptr)
	{
		// ���ݷ� ���
		IreneData.Strength = Table->ATTACK_DAMAGE_1;
	}

	// �� ���� �ڽ� ũ��
	float Far = 300;
	if(IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		Far = 500;
	// ����, ����, �Ÿ�
	const FVector BoxSize = FVector(300, 50, Far);

	// ����Ʈ�� ��� �浹 ��� ��´�.
	TArray<FHitResult> MonsterList;
	const FCollisionQueryParams Params(NAME_None, false, this);
	const bool bResult = GetWorld()->SweepMultiByChannel(
		MonsterList,
		GetActorLocation() + GetActorForwardVector() * Far,
		GetActorLocation() + GetActorForwardVector() * Far,
		FRotationMatrix::MakeFromZ(GetActorForwardVector() * Far).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel8,
		FCollisionShape::MakeBox(BoxSize * 1),
		Params);

	#if ENABLE_DRAW_DEBUG
		const FVector TraceVec = GetActorForwardVector() * Far;
		const FVector Center = GetActorLocation() + TraceVec + (GetActorForwardVector()*-150.0f);
		const FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		const FColor DrawColor = bResult ? FColor::Magenta : FColor::Blue;
		constexpr float DebugLifeTime = 5.0f;

		DrawDebugBox(GetWorld(), Center, BoxSize, CapsuleRot, DrawColor, false, DebugLifeTime);
	#endif

	NearMonsterAnalysis(MonsterList, bResult, Params, Far);

	// ���͸� ã�� �Ĵٺ���
	if (IreneAttack->TargetMonster != nullptr)
	{		
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
	NearPosition = FindNearTarget;
	if (IreneAttack->TargetMonster == nullptr)
	{
		IreneAttack->TargetMonster = RayHit.GetActor();
		IreneAnim->SetTargetMonster(IreneAttack->TargetMonster->GetActorLocation());
		IreneAnim->SetIsHaveTargetMonster(true);
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
				ChangeStateAndLog(UDeathState::GetInstance());
			else
				ChangeStateAndLog(UHit1State::GetInstance());
		}
		if (IreneAttack->TargetMonster == nullptr)
		{
			// ������ ���͸� Ÿ�� ���ͷ� ����
			IreneAttack->TargetMonster = DamageCauser;
			IreneAnim->SetTargetMonster(IreneAttack->TargetMonster->GetActorLocation());
			IreneAnim->SetIsHaveTargetMonster(true);
		}
	}
	return FinalDamage;
}

#pragma endregion Collision

#pragma region State
void AIreneCharacter::ChangeStateAndLog(IState* NewState)const
{
	IreneState->ChangeState(NewState);
	IreneAnim->SetIreneStateAnim(IreneState->GetState());
}

void AIreneCharacter::ActionEndChangeMoveState()const
{
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
void AIreneCharacter::LastAttackCameraShake(const float DeltaTime)
{
	if (CameraShakeOn)
	{
		if(!FixedUpdateTimer.IsValid())
		{
			constexpr float TimeSpeed = 0.01f;
			GetWorld()->GetTimerManager().SetTimer(FixedUpdateTimer, FTimerDelegate::CreateLambda([&]()
			{
				const float CameraShakeTime = IreneAttack->GetCameraShakeTime();
				IreneAttack->SetCameraShakeTime(CameraShakeTime + 0.1f);
				STARRYLOG(Error,TEXT("%f"), IreneAttack->GetCameraShakeTime());
			}), TimeSpeed, true);
		}
		FRotator CameraRotate = CameraComp->GetRelativeRotation();
		CameraRotate.Pitch = CameraShakeCurve[0]->GetFloatValue(IreneAttack->GetCameraShakeTime());
		CameraComp->SetRelativeRotation(CameraRotate);
	}
	else
	{
		IreneAttack->SetCameraShakeTime(0);
		//CameraShakeOn = false;
		CameraComp->SetRelativeRotation(FRotator::ZeroRotator);
		if(FixedUpdateTimer.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(FixedUpdateTimer);
	}
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
