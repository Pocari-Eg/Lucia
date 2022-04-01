// Fill out your copyright notice in the Description page of Project Settings.
//
//  
// ���߿� �ؾ��� ��: �Ϲ� ���� �Ӽ� ���̺� ���� �� �б�, 
// 
// �α� ��¿� ����
// UE_LOG(LogTemp, Warning, TEXT("SubKeyword"));

#include "IreneCharacter.h"
#include "IreneAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "STGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#pragma region Setting
// Sets default values
AIreneCharacter::AIreneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���̷��� �޽� ����
	ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Animation/Irene/Idle.Idle"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -80), FRotator(0, 270, 0));
		//GetMesh()->SetWorldScale3D(FVector(10.0f, 10.0f, 10.0f));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

		//����
		FName WeaponSocket(TEXT("hand_rSocket"));
		if (GetMesh()->DoesSocketExist(WeaponSocket))
		{
			Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_WEAPON(TEXT("/Game/Animation/IreneSword/PC_sworddummy02.PC_sworddummy02"));
			if (SK_WEAPON.Succeeded())
			{
				Weapon->SetSkeletalMesh(SK_WEAPON.Object);
			}
			Weapon->SetupAttachment(GetMesh(), WeaponSocket);
		}

		//�ݸ��� ����
		//Weapon->SetCollisionProfileName(TEXT("PlayerAttack"));

		// �������Ʈ �ִϸ��̼� ����
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Animation/Irene/BP/BP_IreneAnination.BP_IreneAnination_C"));

		if (CharacterAnimInstance.Succeeded())
		{
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
		}
	}
	// ����Ŀ��
	ConstructorHelpers::FObjectFinder<UCurveFloat>JumpCurve(TEXT("/Game/Math/Jump.Jump"));
	if (JumpCurve.Succeeded())
	{
		JumpGravityCurve = JumpCurve.Object;
	}

	// �ݶ��̴� ����
	GetCapsuleComponent()->InitCapsuleSize(25.f, 80.0f);
	/*
	FindMonsterCollsion = CreateDefaultSubobject<UBoxComponent>(TEXT("FindMonster"));
	FindMonsterCollsion->SetRelativeLocation(FVector(300, 0, 0));
	FindMonsterCollsion->SetBoxExtent(FVector(300.0f, 300.0f, 100.0f));

	FindTargetCollsion = CreateDefaultSubobject<UBoxComponent>(TEXT("FindTarget"));
	FindTargetCollsion->SetRelativeLocation(FVector(100, 0, 0));
	FindTargetCollsion->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	*/

	// �������� ����
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 46.0f), FRotator(-20.0f, 90.0f, 0.0f));
	//SpringArmComp->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	SpringArmComp->TargetArmLength = CharacterDataStruct.FollowCameraZPosition;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 0.0f;

	// ī�޶� ����
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->FieldOfView = CharacterDataStruct.FieldofView;

	// ī�޶� ȸ���� ĳ���� ȸ�� ���� �ȵǵ��� ����
	bUseControllerRotationYaw = false;
	SpringArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	// ���� ����
	GetCharacterMovement()->JumpZVelocity = CharacterDataStruct.JumpStartPower;

	// �⺻ �ִ� �̵��ӵ�
	GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;

	// �÷��̾� ���� �� �⺻ ���� ����
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// ���� Ŭ���� �޸� �Ҵ� �� ���� ���� ����
	CharacterState = new IreneFSM();
	CharacterState->setState(StateEnum::Idle);

	// IreneCharater.h�� ���� �ʱ�ȭ

	// ��Ʈ�ѷ� �ʱ�ȭ
	WorldController = nullptr;

	// WASD Ű �Է� �ʱ�ȭ
	MoveKey.Add(0);
	MoveKey.Add(0);
	MoveKey.Add(0);
	MoveKey.Add(0);

	// �ڵ��̵� ���� �ʱ�ȭ
	MoveAutoDirection.ZeroVector;
	// �߶� �� ������ �Է� �ʱ�ȭ
	IsFallingRoll = false;

	TargetMonster = nullptr;

	// PlayerCharacterDataStruct.h�� �ϴ� public ������ �ʱ�ȭ

	CharacterDataStruct.CurrentHP = CharacterDataStruct.MaxHP;
	CharacterDataStruct.CurrentMP = CharacterDataStruct.MaxMP;

	//�ʱ� �Ӽ�
	Attribute = EAttributeKeyword::e_Fire;

	//ui ����
	AttributeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ATTRIBUTEWIDGET"));
	AttributeWidget->SetupAttachment(GetMesh());
	AttributeWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 210.0f));
	AttributeWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	AttributeWidget->SetWidgetSpace(EWidgetSpace::World);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Developers/Pocari/Collections/Widget/BP_AttributesWidget.BP_AttributesWidget_C"));
	if (UI_HUD.Succeeded())
	{
		AttributeWidget->SetWidgetClass(UI_HUD.Class);
		AttributeWidget->SetDrawSize(FVector2D(20.0f, 20.0f));
	}

	//HP UI ����
	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HpBarWidget->SetupAttachment(GetMesh());
	HpBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 170.0f));
	HpBarWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	HpBarWidget->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBARWIDGET(TEXT("/Game/Developers/Pocari/Collections/Widget/BP_HPBar.BP_HPBar_C"));

	if (UI_HPBARWIDGET.Succeeded()) 
	{
		HpBarWidget->SetWidgetClass(UI_HPBARWIDGET.Class);
		HpBarWidget->SetDrawSize(FVector2D(150, 50.0f));
	}	

	bStartJump = false;
	JumpingTime = 0.0f;
	bFollowTarget = false;
	FollowTargetAlpha = 0.0f;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;

	bShowLog = false;
}

// Called when the game starts or when spawned
void AIreneCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ��Ʈ�ѷ� �޾ƿ���
	WorldController = GetWorld()->GetFirstPlayerController();

	//���缷
	auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
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

	// �Ӽ� ������ �Ӽ��� ����
	auto Widget = Cast<UIreneAttributeWidget>(AttributeWidget->GetUserWidgetObject());
	if (nullptr != Widget)
	{
		Widget->BindCharacterAttribute(Attribute);
	}


	//���� ����
	AttackSound = new SoundManager(AttackEvent, GetWorld());
	AttackSound->SetVolume(0.4f);
	AttackSound->SetParameter("Attributes", 1.0f);


}
void AIreneCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	IreneAnim = Cast<UIreneAnimInstance>(GetMesh()->GetAnimInstance());
	IreneAnim->OnMontageEnded.AddDynamic(this, &AIreneCharacter::OnAttackMontageEnded);
	IreneAnim->OnNextAttackCheck.AddLambda([this]()->void
		{
			CharacterDataStruct.CanNextCombo = false;
			if (CharacterDataStruct.IsComboInputOn)
			{
				AttackStartComboState();
				IreneAnim->JumpToAttackMontageSection(CharacterDataStruct.CurrentCombo);
				
			}
		});
	IreneAnim->OnAttackHitCheck.AddUObject(this, &AIreneCharacter::AttackCheck);
}
#pragma endregion

// Called every frame
void AIreneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �뽬�����϶� MoveAuto�� ���� �̵��� ��Ŵ
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") != 0)
	{
		if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0) {
			MoveForward();
			MoveRight();
		}
		else
			MoveAuto();
	}
	else
	{
		MoveAuto();
	}
	if (IsFallingRoll && !GetMovementComponent()->IsFalling())
	{
		//�����ٰ� ���� ����
		IsFallingRoll = false;
		DodgeKeyword();
	}
	MoveStop();
	if (CharacterDataStruct.IsInvincibility == true)
		SetActorEnableCollision(false);

	if (bStartJump)
	{
		JumpingTime += DeltaTime;
		GetCharacterMovement()->GravityScale = JumpGravityCurve->GetFloatValue(JumpingTime);
	}

	if (!GetCharacterMovement()->IsFalling())
	{
		JumpingTime = 0.0f;
		bStartJump = false;
	}

	if (TargetMonster != nullptr)
	{
		//if (bShowLog)
			//UE_LOG(LogTemp, Error, TEXT("Target Name: %s, Dist: %f"), *TargetMonster->GetName(), FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()));
		// Ÿ�ٸ��� �װų� �Ÿ��� �־����� �ʱ�ȭ
		if (TargetMonster->IsPendingKill() == true || FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()) > 700.0f)
			TargetMonster = nullptr;
	}
	//�÷��̾��� ī�޶� ��ǥ�� ���� ������ ��ǥ�� ���� ������ ī�޶� �ٶ󺸵��� 
	FRotator CameraRot = UKismetMathLibrary::FindLookAtRotation(AttributeWidget->GetComponentTransform().GetLocation(),
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());

	// Yaw ���� ��ȯ�Ͽ� ������ ī�޶� �����
	AttributeWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
	HpBarWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
}

#pragma region Move
void AIreneCharacter::MoveForward()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		// 0: ����, 2: ����
		if (MoveKey[0] != 0 && MoveKey[0] < 3)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, CharacterDataStruct.MoveSpeed);
		}
		if (MoveKey[2] != 0 && MoveKey[2] < 3)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction * -1, CharacterDataStruct.MoveSpeed);
		}
	}
}
void AIreneCharacter::MoveRight()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		// 1: ����, 3: ����
		if (MoveKey[1] != 0 && MoveKey[1] < 3)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction * -1, CharacterDataStruct.MoveSpeed);
		}
		if (MoveKey[3] != 0 && MoveKey[3] < 3)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, CharacterDataStruct.MoveSpeed);
		}
	}
}
void AIreneCharacter::MoveStop()
{
	// �ƹ� Ű �Է��� ���� ��� ���� ���� ����
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
		{
			if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Sprint") == 0)
			{
				IreneAnim->SetSprintStopAnim(true);
			}
			ChangeStateAndLog(StateEnum::Idle);
		}
	}
	// ���� ���� �� Ű�Է¿� ���� �ٴڿ� ������ ��� ����, �ȱ�, �޸��� ���� ����
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") == 0)
	{
		if (!GetCharacterMovement()->IsFalling())
		{
			ActionEndChangeMoveState();
			GetCharacterMovement()->GravityScale = 2;
		}
	}
}
void AIreneCharacter::MoveAuto()
{
	// �̵� �� ����
	if (bFollowTarget)
	{
		FollowTargetAlpha += GetWorld()->GetDeltaSeconds() * 2 * CharacterDataStruct.TargetFollowSpeed;
		if (FollowTargetAlpha >= 1)
			FollowTargetAlpha = 1;
		FVector tar = FMath::Lerp(PlayerPosVec, TargetPosVec, FollowTargetAlpha);
		GetCapsuleComponent()->SetRelativeLocation(tar);
		if (FVector::Dist(tar, TargetPosVec) <= 1)
		{
			DoAttack();
		}
	}
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0)
	{
		if (MoveAutoDirection == FVector(0, 0, 0))
		{
			MoveAutoDirection += GetActorForwardVector();
			MoveAutoDirection.Normalize();
		}

		// �뽬 ���� �������� ���� ���·� ���� ��ȭ
		if (GetMovementComponent()->IsFalling())
		{
			CharacterDataStruct.MoveSpeed = 1.0f;
			MoveAutoDirection = FVector(0, 0, 0);
			GetWorld()->GetTimerManager().ClearTimer(MoveAutoWaitHandle);
			if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
				CharacterState->setState(StateEnum::Jump);
		}

		if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") == 0)
			AddMovementInput(MoveAutoDirection, CharacterDataStruct.MoveSpeed);
	}
}

void AIreneCharacter::StartJump()
{
	if (!GetCharacterMovement()->IsFalling()
		&& strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") != 0
		&& strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0
		&& strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		// Ű �Է��� �������� ���� ������ ��´�.
		FVector Direction = FVector(0, 0, 0);
		if (MoveKey[0] != 0)
		{
			Direction += GetActorForwardVector();
		}
		if (MoveKey[1] != 0)
		{
			Direction += GetActorRightVector() * -1;
		}
		if (MoveKey[2] != 0)
		{
			Direction += GetActorForwardVector() * -1;
		}
		if (MoveKey[3] != 0)
		{
			Direction += GetActorRightVector();
		}
		Direction.Normalize();

		GetMovementComponent()->Velocity = GetMovementComponent()->Velocity / 3;

		bPressedJump = true;
		bStartJump = true;
		ChangeStateAndLog(StateEnum::Jump);
	}
}
void AIreneCharacter::StopJump()
{
	bPressedJump = false;
}

void AIreneCharacter::MovePressedW()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") == 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
			ChangeStateAndLog(StateEnum::Run);
		}
		MoveKey[0] = 1;
	}
	else
		MoveKey[0] = 3;
}
void AIreneCharacter::MovePressedA()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") == 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
			ChangeStateAndLog(StateEnum::Run);
		}
		MoveKey[1] = 1;
	}
	else
		MoveKey[1] = 3;
}
void AIreneCharacter::MovePressedS()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") == 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
			ChangeStateAndLog(StateEnum::Run);
		}
		MoveKey[2] = 1;
	}
	else
		MoveKey[2] = 3;
}
void AIreneCharacter::MovePressedD()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") == 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
			ChangeStateAndLog(StateEnum::Run);
		}
		MoveKey[3] = 1;
	}
	else
		MoveKey[3] = 3;
}

void AIreneCharacter::MoveDoubleClickW()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		MoveKey[0] = 2;
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;
		ChangeStateAndLog(StateEnum::Sprint);
		CharacterDataStruct.MoveSpeed = 2;
	}
	else
		MoveKey[0] = 4;
}
void AIreneCharacter::MoveDoubleClickA()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		MoveKey[1] = 2;
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;
		ChangeStateAndLog(StateEnum::Sprint);
		CharacterDataStruct.MoveSpeed = 2;
	}
	else
		MoveKey[1] = 4;
}
void AIreneCharacter::MoveDoubleClickS()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		MoveKey[2] = 2;
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;
		ChangeStateAndLog(StateEnum::Sprint);
		CharacterDataStruct.MoveSpeed = 2;
	}
	else
		MoveKey[2] = 4;
}
void AIreneCharacter::MoveDoubleClickD()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		MoveKey[3] = 2;
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;
		ChangeStateAndLog(StateEnum::Sprint);
		CharacterDataStruct.MoveSpeed = 2;
	}
	else
		MoveKey[3] = 4;
}

void AIreneCharacter::MoveReleasedW()
{
	MoveKey[0] = 0;
	// �ٸ� Ű �� �޸��Ⱑ ����� �ȱ� �ӵ��� �����δ�.
	if (MoveKey[1] != 2 && MoveKey[2] != 2 && MoveKey[3] != 2)
		CharacterDataStruct.MoveSpeed = 1;
}
void AIreneCharacter::MoveReleasedA()
{
	MoveKey[1] = 0;
	// �ٸ� Ű �� �޸��Ⱑ ����� �ȱ� �ӵ��� �����δ�.
	if (MoveKey[0] != 2 && MoveKey[2] != 2 && MoveKey[3] != 2)
		CharacterDataStruct.MoveSpeed = 1;
}
void AIreneCharacter::MoveReleasedS()
{
	MoveKey[2] = 0;
	// �ٸ� Ű �� �޸��Ⱑ ����� �ȱ� �ӵ��� �����δ�.
	if (MoveKey[0] != 2 && MoveKey[1] != 2 && MoveKey[3] != 2)
		CharacterDataStruct.MoveSpeed = 1;
}
void AIreneCharacter::MoveReleasedD()
{
	MoveKey[3] = 0;
	// �ٸ� Ű �� �޸��Ⱑ ����� �ȱ� �ӵ��� �����δ�.
	if (MoveKey[0] != 2 && MoveKey[1] != 2 && MoveKey[2] != 2)
		CharacterDataStruct.MoveSpeed = 1;
}
#pragma endregion

#pragma region Input
void AIreneCharacter::Turn(float Rate)
{
	if (WorldController->bShowMouseCursor == false &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
		AddControllerYawInput(Rate * CharacterDataStruct.EDPI);
}
void AIreneCharacter::LookUp(float Rate)
{
	if (WorldController->bShowMouseCursor == false &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
		AddControllerPitchInput(Rate * CharacterDataStruct.EDPI);
}

void AIreneCharacter::LeftButton(float Rate)
{
	
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Fall") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		if (Rate >= 1.0 && !AttackWaitHandle.IsValid())
		{
			
			// ���콺 ���� ������ ���� �� ���Ӱ��� ���� �ð�(�ѹ��� ������ ���� �ν� ���ϵ��� ��)
			float WaitTime = 0.15f;

			GetWorld()->GetTimerManager().SetTimer(AttackWaitHandle, FTimerDelegate::CreateLambda([&]()
				{
					
					AttackWaitHandle.Invalidate();
				}), WaitTime, false);

			if (CharacterDataStruct.IsAttacking)
			{
				if (CharacterDataStruct.CanNextCombo)
				{
				
					CharacterDataStruct.IsComboInputOn = true;
				}
			}
			else
			{
				ChangeStateAndLog(StateEnum::Attack);
				AttackStartComboState();
				
				IreneAnim->PlayAttackMontage();
				
				IreneAnim->JumpToAttackMontageSection(CharacterDataStruct.CurrentCombo);
				CharacterDataStruct.IsAttacking = true;
			}
		}
	}
}
void AIreneCharacter::RightButton()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Fall") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		ChangeStateAndLog(StateEnum::Attack);
		IreneAnim->PlayEffectAttackMontage();
	}
}
void AIreneCharacter::MouseWheel(float Rate)
{
	SpringArmComp->TargetArmLength -= Rate * CharacterDataStruct.MouseWheelSpeed;
	SpringArmComp->TargetArmLength = FMath::Clamp(SpringArmComp->TargetArmLength, CharacterDataStruct.MinFollowCameraZPosition, CharacterDataStruct.MaxFollowCameraZPosition);
}

void AIreneCharacter::MainKeyword()
{
	//�ӻ�ȯ ���ʴ�� �Ӽ��� ��ȯ
	switch (Attribute)
	{
	case EAttributeKeyword::e_Fire:
		AttackSound->SetParameter("Attributes", 2.0f);
		Attribute = EAttributeKeyword::e_Water;
		break;
	case EAttributeKeyword::e_Water:
		AttackSound->SetParameter("Attributes", 3.0f);

		Attribute = EAttributeKeyword::e_Thunder;
		break;
	case EAttributeKeyword::e_Thunder:
		AttackSound->SetParameter("Attributes", 1.0f);
		Attribute = EAttributeKeyword::e_Fire;
		
		break;
	default:
		break;
	}
	auto Widget = Cast<UIreneAttributeWidget>(AttributeWidget->GetUserWidgetObject());
	if (nullptr != Widget)
	{
		Widget->BindCharacterAttribute(Attribute);
	}
	FOnAttributeChange.Broadcast();
}

void AIreneCharacter::DodgeKeyword()
{
	if (!GetMovementComponent()->IsFalling() &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		IreneAnim->StopAllMontages(0);
		ChangeStateAndLog(StateEnum::Dodge);

		float WaitTime = 1.5f; //�ð��� ����
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;

		GetWorld()->GetTimerManager().SetTimer(MoveAutoWaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				// ���߿� �߶� ���ϰ� ���������� �������� ��
				if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") == 0)
				{
					ActionEndChangeMoveState();
				}
			}), WaitTime, false);
	}
	if (GetMovementComponent()->IsFalling())
	{
		if (!IsFallingRoll)
		{
			IsFallingRoll = true;

			MoveAutoDirection.ZeroVector;
			// wŰ�� �ƹ����� ������ �������� �̵�
			if (MoveKey[0] != 0 || (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0))
			{
				MoveAutoDirection += GetActorForwardVector();
			}
			if (MoveKey[1] != 0)
			{
				MoveAutoDirection += GetActorRightVector() * -1;
			}
			if (MoveKey[2] != 0)
			{
				MoveAutoDirection += GetActorForwardVector() * -2;
			}
			if (MoveKey[3] != 0)
			{
				MoveAutoDirection += GetActorRightVector();
			}
			MoveAutoDirection.Normalize();
		}
	}
}

void AIreneCharacter::MouseCursorKeyword()
{
	if (WorldController->bShowMouseCursor == false)
		WorldController->bShowMouseCursor = true;
	else
		WorldController->bShowMouseCursor = false;
}

// Called to bind functionality to input
void AIreneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ������ ���� Ű���� �Է�
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AIreneCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AIreneCharacter::StopJump);

	PlayerInputComponent->BindAction("MoveW", IE_Pressed, this, &AIreneCharacter::MovePressedW);
	PlayerInputComponent->BindAction("MoveA", IE_Pressed, this, &AIreneCharacter::MovePressedA);
	PlayerInputComponent->BindAction("MoveS", IE_Pressed, this, &AIreneCharacter::MovePressedS);
	PlayerInputComponent->BindAction("MoveD", IE_Pressed, this, &AIreneCharacter::MovePressedD);
	PlayerInputComponent->BindAction("MoveW", IE_DoubleClick, this, &AIreneCharacter::MoveDoubleClickW);
	PlayerInputComponent->BindAction("MoveA", IE_DoubleClick, this, &AIreneCharacter::MoveDoubleClickA);
	PlayerInputComponent->BindAction("MoveS", IE_DoubleClick, this, &AIreneCharacter::MoveDoubleClickS);
	PlayerInputComponent->BindAction("MoveD", IE_DoubleClick, this, &AIreneCharacter::MoveDoubleClickD);
	PlayerInputComponent->BindAction("MoveW", IE_Released, this, &AIreneCharacter::MoveReleasedW);
	PlayerInputComponent->BindAction("MoveA", IE_Released, this, &AIreneCharacter::MoveReleasedA);
	PlayerInputComponent->BindAction("MoveS", IE_Released, this, &AIreneCharacter::MoveReleasedS);
	PlayerInputComponent->BindAction("MoveD", IE_Released, this, &AIreneCharacter::MoveReleasedD);

	// ������ �� Ű���� �Է�
	PlayerInputComponent->BindAction("MainKeyword", IE_Pressed, this, &AIreneCharacter::MainKeyword);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AIreneCharacter::DodgeKeyword);
	PlayerInputComponent->BindAction("MouseCursor", IE_Pressed, this, &AIreneCharacter::MouseCursorKeyword);

	// ���콺
	PlayerInputComponent->BindAxis("Turn", this, &AIreneCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AIreneCharacter::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", this, &AIreneCharacter::LeftButton);
	PlayerInputComponent->BindAction("RightButton", IE_Pressed, this, &AIreneCharacter::RightButton);
	PlayerInputComponent->BindAxis("MouseWheel", this, &AIreneCharacter::MouseWheel);

	//������
	//��ž��ġ ��Ʈ��
	/*PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchContorl);
	PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);*/
}
#pragma endregion

#pragma region Attack
void AIreneCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	CharacterDataStruct.IsAttacking = false;
	AttackEndComboState();
}

void AIreneCharacter::AttackStartComboState()
{
	CharacterDataStruct.CanNextCombo = true;
	CharacterDataStruct.IsComboInputOn = false;
	CharacterDataStruct.CurrentCombo = FMath::Clamp<int32>(CharacterDataStruct.CurrentCombo + 1, 1, CharacterDataStruct.MaxCombo);
}
void AIreneCharacter::AttackEndComboState()
{
	CharacterDataStruct.CanNextCombo = false;
	CharacterDataStruct.IsComboInputOn = false;
	CharacterDataStruct.CurrentCombo = 0;
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") != 0)
		ActionEndChangeMoveState();
}

void AIreneCharacter::AttackCheck()
{
	STARRYLOG_S(Error);
	AttackSound->SoundPlay2D();
	FindNearMonster();
	FTimerHandle AttackCheckWaitHandle;
}
void AIreneCharacter::DoAttack()
{
	// ���� ���� �ʱ�ȭ
	bFollowTarget = false;
	FollowTargetAlpha = 0;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;

	TArray<FHitResult> MonsterList;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepMultiByChannel(
		MonsterList,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * CharacterDataStruct.AttackRange,
		FRotationMatrix::MakeFromZ(GetActorForwardVector() * CharacterDataStruct.AttackRange).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(50.0f),
		Params);
	

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * CharacterDataStruct.AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = CharacterDataStruct.AttackRange * 0.5f + CharacterDataStruct.AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		CharacterDataStruct.AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	for (FHitResult Monster : MonsterList)
	{
		if (bResult)
		{
			if (Monster.Actor.IsValid())
			{
				FDamageEvent DamageEvent;
				UGameplayStatics::ApplyDamage(Monster.Actor.Get(), CharacterDataStruct.Strength, NULL, this, NULL);
			}
		}
	}
	//���� ����ϴ� ���� �� ApplyDamage�ݺ� ���� �� ȣ��
	//���� ��� ���� �߰� �� ���Ϳ��� �ڵ� ���� ���� ���� �� (��Ÿ����)
	if (bResult)
	{
		auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
		if (STGameInstance->GetAttributeEffectMonster() != nullptr)
		{
			STGameInstance->ResetAttributeEffectMonster();
		}
	}

	

}
#pragma endregion

#pragma region Collision
void AIreneCharacter::FindNearMonster()
{
	if (TargetMonster != nullptr)
	{
		// Ÿ���� ĳ������ �ڿ� �ִٸ� ���� ���
		FVector targetData = TargetMonster->GetActorLocation() - GetActorLocation();
		targetData.Normalize();
		if (FVector::DotProduct(GetActorForwardVector(), targetData) < 0)
		{
			TargetMonster = nullptr;
		}
	}

	float far = 300;
	// ����, ����, ����
	FVector BoxSize = FVector(150, 50, far);
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
	FVector Center = GetActorLocation() + TraceVec;
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
				FName TargetCollisionProfileName;
				// ���ο� ������Ʈ �浹ü ������ �̸�
				FName RayCollisionProfileName = RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
				FName EnemyProfile = "Enemy";
				FName ObjectProfile = "Object";

				// ������ �� ĸ��������Ʈ�� ������ ī�޶� ������ �Ǹ� ���������� ����ִ� ���� �Ǵ� ������Ʈ ã��
				if (RayHit.Actor.IsValid() &&
					(RayCollisionProfileName == EnemyProfile || RayCollisionProfileName == ObjectProfile)
					&& RayHit.GetActor()->WasRecentlyRendered())
				{
					// ù ���� �Ҵ�
					if (TargetMonster == nullptr)
					{
						TargetMonster = RayHit.GetActor();
						NearPosition = FindNearTarget;
					}

					TargetCollisionProfileName = TargetMonster->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
					if (bShowLog)
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
								TargetMonster = RayHit.GetActor();
							}
							else if (TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == EnemyProfile)
							{
								NearPosition = FindNearTarget;
								TargetMonster = RayHit.GetActor();
							}
							else if (TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == ObjectProfile)
							{
								NearPosition = FindNearTarget;
								TargetMonster = RayHit.GetActor();
							}
						}
						else
						{
							NearPosition = FindNearTarget;
							TargetMonster = RayHit.GetActor();
						}
					}
				}
			}
		}
	}
	// ���͸� ã�� �Ĵٺ���
	if (TargetMonster != nullptr)
	{
		//UE_LOG(LogTemp, Error, TEXT("Target Name: %s, Dist: %f"), *TargetMonster->GetName(), FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()));

		float z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetMonster->GetActorLocation()).Yaw;
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, z, 0.0f));
		// ���Ͱ� ���ݹ��� ���� �ָ� �ִٸ�
		float TargetPos = FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()) - CharacterDataStruct.AttackRange;
		if (TargetPos > CharacterDataStruct.AttackRange)
		{
			// ���� ����
			bFollowTarget = true;
			PlayerPosVec = GetActorLocation();
			TargetPosVec = GetActorLocation() + GetActorForwardVector() * (TargetPos);
		}
		else
		{
			DoAttack();
		}
	}
}
void AIreneCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}
void AIreneCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}
float AIreneCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CharacterDataStruct.CurrentHP > 0)
	{
		CharacterDataStruct.CurrentHP -= DamageAmount - CharacterDataStruct.Defenses;
		//hp ��
		auto HpBar = Cast<UHPBarWidget>(HpBarWidget->GetWidget());
		if (HpBar != nullptr)
		{
			HpBar->UpdateWidget(GetHpRatio());
		}
		if (CharacterDataStruct.CurrentHP <= 0)
		{
			IreneAnim->StopAllMontages(0);
			IreneAnim->SetDeadAnim(true);
			ChangeStateAndLog(StateEnum::Death);
		}
	}
	if (TargetMonster == nullptr)
	{
		TargetMonster = DamageCauser;
	}
	return FinalDamage;
}

#pragma endregion

#pragma region State
void AIreneCharacter::ChangeStateAndLog(StateEnum newState)
{
	if ((strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0) ||
		newState == StateEnum::Death)
	{
		if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Sprint") != 0) 
		{
			IreneAnim->SetSprintStateAnim(false);
			IreneAnim->SetSprintStopAnim(false);
		}
		else
		{
			IreneAnim->SetSprintStateAnim(true);
		}
		CharacterState->setState(newState);

		FString str = CharacterState->StateEnumToString(CharacterState->getState());
		if (bShowLog)
			UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}
}

void AIreneCharacter::ActionEndChangeMoveState()
{
	CharacterDataStruct.MoveSpeed = 1.0f;
	MoveAutoDirection = FVector(0, 0, 0);

	if (MoveKey[0] > 2)
		MoveKey[0] -= 2;
	if (MoveKey[1] > 2)
		MoveKey[1] -= 2;
	if (MoveKey[2] > 2)
		MoveKey[2] -= 2;
	if (MoveKey[3] > 2)
		MoveKey[3] -= 2;

	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
		CharacterState->setState(StateEnum::Idle);
	if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
		ChangeStateAndLog(StateEnum::Idle);
	}
	else if (MoveKey[0] == 2 || MoveKey[1] == 2 || MoveKey[2] == 2 || MoveKey[3] == 2)
	{
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;
		ChangeStateAndLog(StateEnum::Sprint);
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
		ChangeStateAndLog(StateEnum::Run);
	}
}
#pragma endregion

// ������ �ڵ�
#pragma region Park
EAttributeKeyword AIreneCharacter::GetAttribute()
{
	return Attribute;
}
float AIreneCharacter::GetATK()
{
	return CharacterDataStruct.Strength;
}
float AIreneCharacter::GetHpRatio()
{
	// ������ȯ 0.0 ~ 1.0
	return (CharacterDataStruct.CurrentHP < KINDA_SMALL_NUMBER) ? 0.0f : CharacterDataStruct.CurrentHP / CharacterDataStruct.MaxHP;
}
#pragma endregion

#pragma region StopWatch
//��ž��ġ ��Ʈ�� �Լ�
//void AIreneCharacter::WatchContorl()
//{
//	StopWatch->WatchControl();
//}
//
//void AIreneCharacter::WatchReset()
//{
//	StopWatch->WatchReset();
//}
#pragma endregion