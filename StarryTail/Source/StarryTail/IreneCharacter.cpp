// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneCharacter.h"

// Sets default values
AIreneCharacter::AIreneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레톤 메쉬 설정
	ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if(CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, 270, 0));

		// 블루프린트 애니메이션 적용
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C"));
		if (CharacterAnimInstance.Succeeded()) 
		{			
			GetMesh()->SetAnimInstanceClass(CharacterAnimInstance.Class);
		}
	}

	// 스프링암 설정
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComp->SetupAttachment(GetMesh());
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 200.0f), FRotator(0.0f, 90.0f, 0.0f));
	SpringArmComp->TargetArmLength = CharacterDataStruct.FollowCameraZPosition;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;

	// 카메라 설정
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->FieldOfView = CharacterDataStruct.FieldofView;

	// 카메라 회전과 캐릭터 회전 연동 안되도록 설정
	//bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	//SpringArmComp->bUsePawnControlRotation = true;

	// 캡슐 사이즈 설정
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// 플레이어 스폰 시 기본 제어 설정
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 상태 클래스 메모리 할당 후 정지 상태 적용
	CharacterState = new IreneFSM();
	CharacterState->setState(StateEnum::Idle);
}

// Called when the game starts or when spawned
void AIreneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIreneCharacter::MoveForward(float AxisValue)
{
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Walk") != 0)
			ChangeStateAndLog(IreneWalkState::getInstance());

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue * CharacterDataStruct.MoveSpeed);
	}
}
void AIreneCharacter::MoveRight(float AxisValue)
{
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Walk") != 0)
			ChangeStateAndLog(IreneWalkState::getInstance());

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, AxisValue * CharacterDataStruct.MoveSpeed);
	}
}

void AIreneCharacter::StartJump()
{
	bPressedJump = true;
	UE_LOG(LogTemp, Warning, TEXT("StartJump"));
}
void AIreneCharacter::StopJump()
{
	bPressedJump = false;
}

void AIreneCharacter::MoveDoubleClickW()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveDoubleClickW"));
	CharacterDataStruct.MoveSpeed = 2;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveDoubleClickA()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveDoubleClickA"));
	CharacterDataStruct.MoveSpeed = 2;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveDoubleClickS()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveDoubleClickS"));
	CharacterDataStruct.MoveSpeed = 2;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveDoubleClickD()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveDoubleClickD"));
	CharacterDataStruct.MoveSpeed = 2;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}

void AIreneCharacter::MoveReleasedW()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveReleasedW"));
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Walk") == 0)
		ChangeStateAndLog(IreneIdleState::getInstance());

	CharacterDataStruct.MoveSpeed = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveReleasedA()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveReleasedA"));
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Walk") == 0)
		ChangeStateAndLog(IreneIdleState::getInstance());

	CharacterDataStruct.MoveSpeed = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveReleasedS()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveReleasedS"));
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Walk") == 0)
		ChangeStateAndLog(IreneIdleState::getInstance());

	CharacterDataStruct.MoveSpeed = 1;
	//GetCharacterMovement()->JumpZVelocity = 600.0f * CharacterDataStruct.MoveSpeed;
}
void AIreneCharacter::MoveReleasedD()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveReleasedD"));
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Walk") == 0)
		ChangeStateAndLog(IreneIdleState::getInstance());

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


void AIreneCharacter::LeftButton()
{
	UE_LOG(LogTemp, Warning, TEXT("LeftButton"));
}

void AIreneCharacter::MainKeyword()
{
	UE_LOG(LogTemp, Warning, TEXT("MainKeyword"));
}
void AIreneCharacter::SubKeyword()
{
	UE_LOG(LogTemp, Warning, TEXT("SubKeyword"));
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
	//if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Walk") != 0)

	// 공중에 있을 때 대쉬 불가

	ChangeStateAndLog(IreneDashState::getInstance());

	const FVector ForwardDir = this->GetActorRotation().Vector();
	LaunchCharacter(ForwardDir * CharacterDataStruct.DashDistance, true, true);

	ChangeStateAndLog(IreneIdleState::getInstance());
}

// Called every frame
void AIreneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AIreneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 움직임 관련 키보드 입력
	PlayerInputComponent->BindAxis("MoveForward", this, &AIreneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AIreneCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AIreneCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AIreneCharacter::StopJump);

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
	PlayerInputComponent->BindAction("LeftButton", IE_Pressed, this, &AIreneCharacter::LeftButton);
}

void AIreneCharacter::ChangeStateAndLog(State* newState)
{
	CharacterState->ChangeState(newState);

	FString str = CharacterState->StateEnumToString(CharacterState->getState());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
}
