// Fill out your copyright notice in the Description page of Project Settings.
//
//  
// 나중에 해야할 것: FSM을 UE4 FSM상속 스크립트로 바꾸기
// 일반 공격 속성 테이블 따라 값 읽기, 
// 
// 로그 출력용 더미
// UE_LOG(LogTemp, Warning, TEXT("SubKeyword"));

#include "IreneCharacter.h"
#include "IreneAnimInstance.h"
#include "DrawDebugHelpers.h"

// Sets default values
AIreneCharacter::AIreneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레톤 메쉬 설정
	ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Developers/syhwms/Collections/Walk.Walk_KeQing"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, 270, 0));
		GetMesh()->SetWorldScale3D(FVector(10.0f, 10.0f, 10.0f));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

		//무기
		FName WeaponSocket(TEXT("hand_rSocket"));
		if (GetMesh()->DoesSocketExist(WeaponSocket))
		{
			Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_WEAPON(TEXT("/Game/Developers/syhwms/Collections/Move.Move_Weapon"));
			if (SK_WEAPON.Succeeded())
			{
				Weapon->SetSkeletalMesh(SK_WEAPON.Object);
			}
			Weapon->SetupAttachment(GetMesh(), WeaponSocket);
		}

		//콜리전 적용
		Weapon->SetCollisionProfileName(TEXT("PlayerAttack"));

		// 블루프린트 애니메이션 적용
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Developers/syhwms/Collections/BP_KeQing.BP_KeQing_C"));

		if (CharacterAnimInstance.Succeeded())
		{
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
		}
	}

	// 스프링암 설정
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 13.0f), FRotator(-20.0f, 90.0f, 0.0f));
	SpringArmComp->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	SpringArmComp->TargetArmLength = CharacterDataStruct.FollowCameraZPosition;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 0.0f;

	// 카메라 설정
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->FieldOfView = CharacterDataStruct.FieldofView;

	// 카메라 회전과 캐릭터 회전 연동 안되도록 설정
	bUseControllerRotationYaw = false;
	SpringArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 점프 높이
	GetCharacterMovement()->JumpZVelocity = 800.0f;

	// 기본 최대 이동속도
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	// 캡슐 사이즈 설정
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// 플레이어 스폰 시 기본 제어 설정
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 상태 클래스 메모리 할당 후 정지 상태 적용
	CharacterState = new IreneFSM();
	CharacterState->setState(StateEnum::Idle);

	// IreneCharater.h의 변수 초기화

	// WASD 키 입력 초기화
	MoveKey.Add(0);
	MoveKey.Add(0);
	MoveKey.Add(0);
	MoveKey.Add(0);

	// 자동이동 방향 초기화
	MoveAutoDirection.ZeroVector;
	// 추락 중 구르기 입력 초기화
	IsFallingRoll = false;

	MainKeywordType = 0;
	SubKeywordType = 0;

	IsAttacking = false;
	MaxCombo = 3;
	AttackEndComboState();
	AttackWaitHandle.Invalidate();
	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	// PlayerCharacterDataStruct.h의 하단 public 변수들 초기화

	// 무적 아님
	CharacterDataStruct.IsInvincibility = false;
	// 초기 체력
	CharacterDataStruct.HP = 100;
	// 초기 이동속도
	CharacterDataStruct.MoveSpeed = 1;
	// 초기 공격력
	CharacterDataStruct.ATK = 20.0f;

	//박찬영
	//초기 속성
	Attribute = EAttributeKeyword::e_Fire;

	//ui 설정
	AttributeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ATTRIBUTEWIDGET"));
	AttributeWidget->SetupAttachment(GetMesh());
	AttributeWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 21.0f));
	AttributeWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	AttributeWidget->SetWidgetSpace(EWidgetSpace::World);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Developers/Pocari/Collections/Widget/BP_AttributesWidget.BP_AttributesWidget_C"));
	if (UI_HUD.Succeeded())
	{
		AttributeWidget->SetWidgetClass(UI_HUD.Class);
		AttributeWidget->SetDrawSize(FVector2D(2.0f, 2.0f));
	}
}

// Called when the game starts or when spawned
void AIreneCharacter::BeginPlay()
{
	Super::BeginPlay();

	//박찬영
	//스탑워치 생성 
	//StopWatch = GetWorld()->SpawnActor<AStopWatch>(FVector::ZeroVector, FRotator::ZeroRotator);
	//StopWatch->InitStopWatch();
	// 속성 위젯에 속성값 설정
	auto Widget = Cast<UIreneAttributeWidget>(AttributeWidget->GetUserWidgetObject());
	if (nullptr != Widget)
	{
		Widget->BindCharacterAttribute(Attribute);
	}
	
}

void AIreneCharacter::MoveForward()
{
	// 0: 전진, 2: 후진
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
	// 1: 좌측, 3: 우측
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
	// 아무 키 입력이 없을 경우 정지 상태 지정
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") != 0 && 
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0)
	{
		if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0) 
		{
			ChangeStateAndLog(IreneIdleState::getInstance());
		}
	}
	// 점프 상태 중 키입력에 따라 바닥에 도착할 경우 정지, 걷기, 달리기 상태 지정
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") == 0)
	{
		if (!GetCharacterMovement()->IsFalling())
		{
			if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
			{
				GetCharacterMovement()->MaxWalkSpeed = 300;
				ChangeStateAndLog(IreneIdleState::getInstance());
			}
			else if (MoveKey[0] == 2 || MoveKey[1] == 2 || MoveKey[2] == 2 || MoveKey[3] == 2)
			{
				GetCharacterMovement()->MaxWalkSpeed = 600;
				ChangeStateAndLog(IreneRunState::getInstance());
			}
			else
			{
				GetCharacterMovement()->MaxWalkSpeed = 300;
				ChangeStateAndLog(IreneWalkState::getInstance());
			}
		}
	}
}
void AIreneCharacter::MoveAuto()
{
	if(MoveAutoDirection == FVector(0,0,0))
	{
		// w키나 아무방향 없으면 정면으로 이동
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

	// 대쉬 도중 떨어지면 점프 상태로 강제 변화
	if(GetMovementComponent()->IsFalling())
	{
		CharacterDataStruct.MoveSpeed = 1.0f;
		MoveAutoDirection = FVector(0, 0, 0);
		GetWorld()->GetTimerManager().ClearTimer(MoveAutoWaitHandle);
		CharacterState->setState(StateEnum::Jump);
	}

	if(strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dash") == 0)
		AddMovementInput(MoveAutoDirection, CharacterDataStruct.MoveSpeed);
}

void AIreneCharacter::StartJump()
{
	if (!GetCharacterMovement()->IsFalling() && strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dash") != 0)
	{
		// 키 입력을 바탕으로 점프 방향을 얻는다.
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
		// 구한 방향의 반대 방향으로 힘을 가해서 점프 거리를 줄인다.
		
		GetCharacterMovement()->AddImpulse(Direction * -1 * CharacterDataStruct.JumpDistance * (GetMovementComponent()->Velocity.Size() /GetMovementComponent()->GetMaxSpeed()));
		bPressedJump = true;
		ChangeStateAndLog(IreneJumpState::getInstance());
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
		ChangeStateAndLog(IreneWalkState::getInstance());
	}
	MoveKey[0] = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MovePressedA()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300;
		ChangeStateAndLog(IreneWalkState::getInstance());
	}
	MoveKey[1] = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MovePressedS()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300;
		ChangeStateAndLog(IreneWalkState::getInstance());
	}
	MoveKey[2] = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MovePressedD()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300;
		ChangeStateAndLog(IreneWalkState::getInstance());
	}
	MoveKey[3] = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}

void AIreneCharacter::MoveDoubleClickW()
{
	MoveKey[0] = 2;

	// 점프 중 달리기 금지
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
		ChangeStateAndLog(IreneRunState::getInstance());
		CharacterDataStruct.MoveSpeed = 2;
	}
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveDoubleClickA()
{
	MoveKey[1] = 2;

	// 점프 중 달리기 금지
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
		ChangeStateAndLog(IreneRunState::getInstance());
		CharacterDataStruct.MoveSpeed = 2;
	}
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveDoubleClickS()
{
	MoveKey[2] = 2;

	// 점프 중 달리기 금지
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
		ChangeStateAndLog(IreneRunState::getInstance());
		CharacterDataStruct.MoveSpeed = 2;
	}
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveDoubleClickD()
{
	MoveKey[3] = 2;

	// 점프 중 달리기 금지
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
		ChangeStateAndLog(IreneRunState::getInstance());
		CharacterDataStruct.MoveSpeed = 2;
	}
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}

void AIreneCharacter::MoveReleasedW()
{
	MoveKey[0] = 0;
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
	if (MoveKey[1] != 2 && MoveKey[2] != 2 && MoveKey[3] != 2) 
		CharacterDataStruct.MoveSpeed = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveReleasedA()
{
	MoveKey[1] = 0;
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
	if (MoveKey[0] != 2 && MoveKey[2] != 2 && MoveKey[3] != 2)
		CharacterDataStruct.MoveSpeed = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveReleasedS()
{
	MoveKey[2] = 0;
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
	if (MoveKey[0] != 2 && MoveKey[1] != 2 && MoveKey[3] != 2)
		CharacterDataStruct.MoveSpeed = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveReleasedD()
{
	MoveKey[3] = 0;
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
	if (MoveKey[0] != 2 && MoveKey[1] != 2 && MoveKey[2] != 2)
		CharacterDataStruct.MoveSpeed = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}

void AIreneCharacter::Turn(float Rate)
{
	AddControllerYawInput(Rate);
}
void AIreneCharacter::LookUp(float Rate)
{
	AddControllerPitchInput(Rate);
}

void AIreneCharacter::LeftButton(float Rate)
{
	if (Rate >= 1.0 && !AttackWaitHandle.IsValid()) 
	{
		// 마우스 왼쪽 누르고 있을 때 연속공격 지연 시간(한번에 여러번 공격 인식 안하도록 함)
		float WaitTime = 0.15f;

		GetWorld()->GetTimerManager().SetTimer(AttackWaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				AttackWaitHandle.Invalidate();
			}), WaitTime, false);

		if (IsAttacking)
		{
			if (CanNextCombo)
			{
				IsComboInputOn = true;
			}
		}
		else
		{
			AttackStartComboState();
			IreneAnim->PlayAttackMontage();
			IreneAnim->JumpToAttackMontageSection(CurrentCombo);
			IsAttacking = true;
		}
	}
}

void AIreneCharacter::MainKeyword()
{
	MainKeywordType++;
	if (MainKeywordType >= 3)
		MainKeywordType = 0;
	switch(MainKeywordType)
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
		ChangeStateAndLog(IreneDashState::getInstance());

		float WaitTime = 1.5f; //시간을 설정
		CharacterDataStruct.MoveSpeed = 30.0f; // 대쉬 속도 설정

		GetWorld()->GetTimerManager().SetTimer(MoveAutoWaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				// 도중에 추락 안하고 정상적으로 진행됬을 때
				if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dash") == 0)
				{
					CharacterDataStruct.MoveSpeed = 1.0f;
					MoveAutoDirection = FVector(0, 0, 0);

					CharacterState->setState(StateEnum::Idle);
					if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
					{
						ChangeStateAndLog(IreneIdleState::getInstance());
					}
					else if (MoveKey[0] == 2 || MoveKey[1] == 2 || MoveKey[2] == 2 || MoveKey[3] == 2)
					{
						ChangeStateAndLog(IreneRunState::getInstance());
					}
					else
					{
						ChangeStateAndLog(IreneWalkState::getInstance());
					}
				}
			}), WaitTime, false);
	}
	if(GetMovementComponent()->IsFalling())
	{
		if (!IsFallingRoll)
		{
			IsFallingRoll = true;
			int32 FallingPower = 500000;
			GetCharacterMovement()->AddImpulse(FVector(0, 0, -1) * FallingPower);

			MoveAutoDirection.ZeroVector;
			// w키나 아무방향 없으면 정면으로 이동
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

// Called every frame
void AIreneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// PlayerCharacterDataStruct.h의 상단 public에 할당 된 변수들로 인게임 수정 가능하게 해주는 기능
	// 앞의 "//" 부분을 지워주고 에디터의 컴파일을 진행하고 플레이를 하고 인게임에서 값을 수정하면 바로 적용 됨
	// 
	//SpringArmComp->TargetArmLength = CharacterDataStruct.FollowCameraZPosition;
	//CameraComp->FieldOfView = CharacterDataStruct.FieldofView;

	// 대쉬상태일땐 MoveAuto로 강제 이동을 시킴
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
		//구르다가 땅에 도착
		IsFallingRoll = false;
		DashKeyword();
	}
	MoveStop();
	
}

void AIreneCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	IreneAnim = Cast<UIreneAnimInstance>(GetMesh()->GetAnimInstance());

	IreneAnim->OnMontageEnded.AddDynamic(this, &AIreneCharacter::OnAttackMontageEnded);

	IreneAnim->OnNextAttackCheck.AddLambda([this]()->void
		{
			CanNextCombo = false;

			if (IsComboInputOn)
			{
				AttackStartComboState();
				IreneAnim->JumpToAttackMontageSection(CurrentCombo);
			}
		});

	IreneAnim->OnAttackHitCheck.AddUObject(this, &AIreneCharacter::AttackCheck);
}

// Called to bind functionality to input
void AIreneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 움직임 관련 키보드 입력
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

	// 움직임 외 키보드 입력
	PlayerInputComponent->BindAction("MainKeyword", IE_Pressed, this, &AIreneCharacter::MainKeyword);
	PlayerInputComponent->BindAction("SubKeyword", IE_Pressed, this, &AIreneCharacter::SubKeyword);
	PlayerInputComponent->BindAction("ActionKeyword1", IE_Pressed, this, &AIreneCharacter::ActionKeyword1);
	PlayerInputComponent->BindAction("ActionKeyword2", IE_Pressed, this, &AIreneCharacter::ActionKeyword2);
	PlayerInputComponent->BindAction("ActionKeyword3", IE_Pressed, this, &AIreneCharacter::ActionKeyword3);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AIreneCharacter::DashKeyword);

	// 마우스
	PlayerInputComponent->BindAxis("Turn", this, &AIreneCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AIreneCharacter::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", this, &AIreneCharacter::LeftButton);


	//박찬영
	//스탑워치 컨트롤
	/*PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchContorl);
	PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);*/

	// 속성 변환 테스트
	PlayerInputComponent->BindAction("AttributeChange", IE_Pressed, this, &AIreneCharacter::AttributeChange);
}

EAttributeKeyword AIreneCharacter::GetAttribute()
{
	return Attribute;
}

float AIreneCharacter::GetATK()
{
	return CharacterDataStruct.ATK;
}

void AIreneCharacter::ChangeStateAndLog(State* newState)
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dash") != 0)
	{
		CharacterState->ChangeState(newState);

		FString str = CharacterState->StateEnumToString(CharacterState->getState());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}
}

void AIreneCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	AttackEndComboState();
}

void AIreneCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void AIreneCharacter::AttackEndComboState()
{
	CanNextCombo = false;
	IsComboInputOn = false;
	CurrentCombo = 0;
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

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	if(bResult)
	{
		if(HitResult.Actor.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());
		}
	}
}

//박찬영
//스탑워치 컨트롤 함수
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
	//속셩변환 차례대로 속성이 변환

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