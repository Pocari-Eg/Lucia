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

#pragma region Setting
// Sets default values
AIreneCharacter::AIreneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���̷��� �޽� ����
	ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Developers/syhwms/Collections/AnimTest/Idle.Idle"));
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
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_WEAPON(TEXT("/Game/Developers/syhwms/Collections/AnimTest/Sword/PC_sworddummy02.PC_sworddummy02"));
			if (SK_WEAPON.Succeeded())
			{
				Weapon->SetSkeletalMesh(SK_WEAPON.Object);
			}
			Weapon->SetupAttachment(GetMesh(), WeaponSocket);
		}

		//�ݸ��� ����
		Weapon->SetCollisionProfileName(TEXT("PlayerAttack"));

		// �������Ʈ �ִϸ��̼� ����
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Developers/syhwms/Collections/AnimTest/BP_Irene.BP_Irene_C"));

		if (CharacterAnimInstance.Succeeded())
		{
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
		}
	}

	// �������� ����
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 13.0f), FRotator(-20.0f, 90.0f, 0.0f));
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

	// ���� ����
	GetCharacterMovement()->JumpZVelocity = 800.0f;

	// �⺻ �ִ� �̵��ӵ�
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	// ĸ�� ������ ����
	GetCapsuleComponent()->InitCapsuleSize(25.f, 80.0f);

	// �÷��̾� ���� �� �⺻ ���� ����
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// ���� Ŭ���� �޸� �Ҵ� �� ���� ���� ����
	CharacterState = new IreneFSM();
	CharacterState->setState(StateEnum::Idle);

	// IreneCharater.h�� ���� �ʱ�ȭ

	// WASD Ű �Է� �ʱ�ȭ
	MoveKey.Add(0);
	MoveKey.Add(0);
	MoveKey.Add(0);
	MoveKey.Add(0);

	// �ڵ��̵� ���� �ʱ�ȭ
	MoveAutoDirection.ZeroVector;
	// �߶� �� ������ �Է� �ʱ�ȭ
	IsFallingRoll = false;

	MainKeywordType = 0;
	SubKeywordType = 0;

	CharacterDataStruct.IsAttacking = false;
	CharacterDataStruct.MaxCombo = 3;
	AttackEndComboState();
	AttackWaitHandle.Invalidate();
	CharacterDataStruct.AttackRange = 200.0f;
	CharacterDataStruct.AttackRadius = 50.0f;

	// PlayerCharacterDataStruct.h�� �ϴ� public ������ �ʱ�ȭ

	// ���� �ƴ�
	CharacterDataStruct.IsInvincibility = false;
	// �ʱ� ü��
	CharacterDataStruct.HP = 100;
	// �ʱ� �̵��ӵ�
	CharacterDataStruct.MoveSpeed = 1;
	// �ʱ� ���ݷ�
	CharacterDataStruct.ATK = 20.0f;

	//������
	//�ʱ� �Ӽ�
	Attribute = EAttributeKeyword::e_Fire;

	//ui ����
	AttributeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ATTRIBUTEWIDGET"));
	AttributeWidget->SetupAttachment(GetMesh());
	AttributeWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 170.0f));
	AttributeWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	AttributeWidget->SetWidgetSpace(EWidgetSpace::World);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Developers/Pocari/Collections/Widget/BP_AttributesWidget.BP_AttributesWidget_C"));
	if (UI_HUD.Succeeded())
	{
		AttributeWidget->SetWidgetClass(UI_HUD.Class);
		AttributeWidget->SetDrawSize(FVector2D(20.0f, 20.0f));
	}
}

// Called when the game starts or when spawned
void AIreneCharacter::BeginPlay()
{
	Super::BeginPlay();

	//������
	//��ž��ġ ���� 
	//StopWatch = GetWorld()->SpawnActor<AStopWatch>(FVector::ZeroVector, FRotator::ZeroRotator);
	//StopWatch->InitStopWatch();
	// �Ӽ� ������ �Ӽ��� ����
	auto Widget = Cast<UIreneAttributeWidget>(AttributeWidget->GetUserWidgetObject());
	if (nullptr != Widget)
	{
		Widget->BindCharacterAttribute(Attribute);
	}

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
	// PlayerCharacterDataStruct.h�� ��� public�� �Ҵ� �� ������� �ΰ��� ���� �����ϰ� ���ִ� ���
	// ���� "//" �κ��� �����ְ� �������� �������� �����ϰ� �÷��̸� �ϰ� �ΰ��ӿ��� ���� �����ϸ� �ٷ� ���� ��
	// 
	//SpringArmComp->TargetArmLength = CharacterDataStruct.FollowCameraZPosition;
	//CameraComp->FieldOfView = CharacterDataStruct.FieldofView;

	// �뽬�����϶� MoveAuto�� ���� �̵��� ��Ŵ
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dash") != 0)
	{
		if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0) {
			MoveForward();
			MoveRight();
		}
	}
	else
	{
		MoveAuto();
	}
	if (IsFallingRoll && !GetMovementComponent()->IsFalling())
	{
		//�����ٰ� ���� ����
		IsFallingRoll = false;
		DashKeyword();
	}
	MoveStop();
	if (CharacterDataStruct.IsInvincibility == true)
		SetActorEnableCollision(false);

}

#pragma region Move
void AIreneCharacter::MoveForward()
{
	// 0: ����, 2: ����
	if (MoveKey[0] != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, CharacterDataStruct.MoveSpeed);
	}
	if (MoveKey[2] != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction * -1, CharacterDataStruct.MoveSpeed);
	}
}
void AIreneCharacter::MoveRight()
{
	// 1: ����, 3: ����
	if (MoveKey[1] != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction * -1, CharacterDataStruct.MoveSpeed);
	}
	if (MoveKey[3] != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, CharacterDataStruct.MoveSpeed);
	}
}
void AIreneCharacter::MoveStop()
{
	// �ƹ� Ű �Է��� ���� ��� ���� ���� ����
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0)
	{
		if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
		{
			ChangeStateAndLog(StateEnum::Idle);
		}
	}
	// ���� ���� �� Ű�Է¿� ���� �ٴڿ� ������ ��� ����, �ȱ�, �޸��� ���� ����
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") == 0)
	{
		if (!GetCharacterMovement()->IsFalling())
		{
			ActionEndChangeMoveState();
		}
	}
}
void AIreneCharacter::MoveAuto()
{
	if (MoveAutoDirection == FVector(0, 0, 0))
	{
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

	// �뽬 ���� �������� ���� ���·� ���� ��ȭ
	if (GetMovementComponent()->IsFalling())
	{
		CharacterDataStruct.MoveSpeed = 1.0f;
		MoveAutoDirection = FVector(0, 0, 0);
		GetWorld()->GetTimerManager().ClearTimer(MoveAutoWaitHandle);
		CharacterState->setState(StateEnum::Jump);
	}

	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dash") == 0)
		AddMovementInput(MoveAutoDirection, CharacterDataStruct.MoveSpeed);
}

void AIreneCharacter::StartJump()
{
	if (!GetCharacterMovement()->IsFalling() && strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dash") != 0)
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
		MoveAutoDirection.Normalize();
		// ���� ������ �ݴ� �������� ���� ���ؼ� ���� �Ÿ��� ���δ�.

		GetCharacterMovement()->AddImpulse(Direction * -1 * CharacterDataStruct.JumpDistance * (GetMovementComponent()->Velocity.Size() / GetMovementComponent()->GetMaxSpeed()));
		bPressedJump = true;
		ChangeStateAndLog(StateEnum::Jump);
	}
}
void AIreneCharacter::StopJump()
{
	bPressedJump = false;
}

void AIreneCharacter::MovePressedW()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300;
		ChangeStateAndLog(StateEnum::Walk);
	}
	MoveKey[0] = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MovePressedA()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300;
		ChangeStateAndLog(StateEnum::Walk);
	}
	MoveKey[1] = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MovePressedS()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300;
		ChangeStateAndLog(StateEnum::Walk);
	}
	MoveKey[2] = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MovePressedD()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300;
		ChangeStateAndLog(StateEnum::Walk);
	}
	MoveKey[3] = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}

void AIreneCharacter::MoveDoubleClickW()
{
	MoveKey[0] = 2;

	// ���� �� �޸��� ����
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
		ChangeStateAndLog(StateEnum::Run);
		CharacterDataStruct.MoveSpeed = 2;
	}
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveDoubleClickA()
{
	MoveKey[1] = 2;

	// ���� �� �޸��� ����
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
		ChangeStateAndLog(StateEnum::Run);
		CharacterDataStruct.MoveSpeed = 2;
	}
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveDoubleClickS()
{
	MoveKey[2] = 2;

	// ���� �� �޸��� ����
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
		ChangeStateAndLog(StateEnum::Run);
		CharacterDataStruct.MoveSpeed = 2;
	}
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveDoubleClickD()
{
	MoveKey[3] = 2;

	// ���� �� �޸��� ����
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
		ChangeStateAndLog(StateEnum::Run);
		CharacterDataStruct.MoveSpeed = 2;
	}
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}

void AIreneCharacter::MoveReleasedW()
{
	MoveKey[0] = 0;
	// �ٸ� Ű �� �޸��Ⱑ ����� �ȱ� �ӵ��� �����δ�.
	if (MoveKey[1] != 2 && MoveKey[2] != 2 && MoveKey[3] != 2)
		CharacterDataStruct.MoveSpeed = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveReleasedA()
{
	MoveKey[1] = 0;
	// �ٸ� Ű �� �޸��Ⱑ ����� �ȱ� �ӵ��� �����δ�.
	if (MoveKey[0] != 2 && MoveKey[2] != 2 && MoveKey[3] != 2)
		CharacterDataStruct.MoveSpeed = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveReleasedS()
{
	MoveKey[2] = 0;
	// �ٸ� Ű �� �޸��Ⱑ ����� �ȱ� �ӵ��� �����δ�.
	if (MoveKey[0] != 2 && MoveKey[1] != 2 && MoveKey[3] != 2)
		CharacterDataStruct.MoveSpeed = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveReleasedD()
{
	MoveKey[3] = 0;
	// �ٸ� Ű �� �޸��Ⱑ ����� �ȱ� �ӵ��� �����δ�.
	if (MoveKey[0] != 2 && MoveKey[1] != 2 && MoveKey[2] != 2)
		CharacterDataStruct.MoveSpeed = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
#pragma endregion

#pragma region Input
void AIreneCharacter::Turn(float Rate)
{
	AddControllerYawInput(Rate * CharacterDataStruct.EDPI);
}
void AIreneCharacter::LookUp(float Rate)
{
	AddControllerPitchInput(Rate * CharacterDataStruct.EDPI);
}

void AIreneCharacter::LeftButton(float Rate)
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
			AttackStartComboState();
			IreneAnim->PlayAttackMontage();
			IreneAnim->JumpToAttackMontageSection(CharacterDataStruct.CurrentCombo);
			CharacterDataStruct.IsAttacking = true;
		}
	}
}

void AIreneCharacter::MouseWheel(float Rate)
{
	SpringArmComp->TargetArmLength -= Rate * CharacterDataStruct.MouseWheelSpeed;
	SpringArmComp->TargetArmLength = FMath::Clamp(SpringArmComp->TargetArmLength, 50.0f, 400.0f);
}

void AIreneCharacter::MainKeyword()
{
	MainKeywordType++;
	if (MainKeywordType >= 3)
		MainKeywordType = 0;
	switch (MainKeywordType)
	{
	case 0:
		UE_LOG(LogTemp, Warning, TEXT("MainFire"));
		break;
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("MainWater"));
		break;
	case 2:
		UE_LOG(LogTemp, Warning, TEXT("MainLightning"));
		break;
	}
}
void AIreneCharacter::SubKeyword()
{
	SubKeywordType++;
	if (SubKeywordType >= 4)
		SubKeywordType = 0;
	switch (SubKeywordType)
	{
	case 0:
		UE_LOG(LogTemp, Warning, TEXT("SubNone"));
		break;
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("SubFire"));
		break;
	case 2:
		UE_LOG(LogTemp, Warning, TEXT("SubWater"));
		break;
	case 3:
		UE_LOG(LogTemp, Warning, TEXT("SubLightning"));
		break;
	}
}
void AIreneCharacter::ActionKeyword1()
{
	UE_LOG(LogTemp, Warning, TEXT("ActionKeyword1"));
}
void AIreneCharacter::ActionKeyword2()
{
	UE_LOG(LogTemp, Warning, TEXT("ActionKeyword2"));
}
void AIreneCharacter::ActionKeyword3()
{
	UE_LOG(LogTemp, Warning, TEXT("ActionKeyword3"));
}

void AIreneCharacter::DashKeyword()
{
	if (!GetMovementComponent()->IsFalling() && strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dash") != 0)
	{
		ChangeStateAndLog(StateEnum::Dash);

		float WaitTime = 1.5f; //�ð��� ����
		CharacterDataStruct.MoveSpeed = 30.0f; // �뽬 �ӵ� ����

		GetWorld()->GetTimerManager().SetTimer(MoveAutoWaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				// ���߿� �߶� ���ϰ� ���������� �������� ��
				if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dash") == 0)
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
			int32 FallingPower = 500000;
			GetCharacterMovement()->AddImpulse(FVector(0, 0, -1) * FallingPower);

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
	PlayerInputComponent->BindAction("SubKeyword", IE_Pressed, this, &AIreneCharacter::SubKeyword);
	PlayerInputComponent->BindAction("ActionKeyword1", IE_Pressed, this, &AIreneCharacter::ActionKeyword1);
	PlayerInputComponent->BindAction("ActionKeyword2", IE_Pressed, this, &AIreneCharacter::ActionKeyword2);
	PlayerInputComponent->BindAction("ActionKeyword3", IE_Pressed, this, &AIreneCharacter::ActionKeyword3);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AIreneCharacter::DashKeyword);

	// ���콺
	PlayerInputComponent->BindAxis("Turn", this, &AIreneCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AIreneCharacter::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", this, &AIreneCharacter::LeftButton);
	PlayerInputComponent->BindAxis("MouseWheel", this, &AIreneCharacter::MouseWheel);


	//������
	//��ž��ġ ��Ʈ��
	/*PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchContorl);
	PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);*/

	// �Ӽ� ��ȯ �׽�Ʈ
	PlayerInputComponent->BindAction("AttributeChange", IE_Pressed, this, &AIreneCharacter::AttributeChange);
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
}

void AIreneCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
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

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(50.0f, DamageEvent, GetController(), this);
		}
	}
}
#pragma endregion

#pragma region State
void AIreneCharacter::ChangeStateAndLog(StateEnum newState)
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dash") != 0)
	{
		CharacterState->setState(newState);

		FString str = CharacterState->StateEnumToString(CharacterState->getState());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}
}

void AIreneCharacter::ActionEndChangeMoveState()
{
	CharacterDataStruct.MoveSpeed = 1.0f;
	MoveAutoDirection = FVector(0, 0, 0);

	CharacterState->setState(StateEnum::Idle);
	if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300;
		ChangeStateAndLog(StateEnum::Idle);
	}
	else if (MoveKey[0] == 2 || MoveKey[1] == 2 || MoveKey[2] == 2 || MoveKey[3] == 2)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
		ChangeStateAndLog(StateEnum::Run);
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 300;
		ChangeStateAndLog(StateEnum::Walk);
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
	return CharacterDataStruct.ATK;
}
//������
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

void AIreneCharacter::AttributeChange()
{
	//�Ӽͺ�ȯ ���ʴ�� �Ӽ��� ��ȯ

	switch (Attribute)
	{

	case EAttributeKeyword::e_Fire:
		Attribute = EAttributeKeyword::e_Water;

		break;
	case EAttributeKeyword::e_Water:
		Attribute = EAttributeKeyword::e_Thunder;

		break;
	case EAttributeKeyword::e_Thunder:
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
}
#pragma endregion

