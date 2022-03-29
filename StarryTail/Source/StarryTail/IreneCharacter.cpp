// Fill out your copyright notice in the Description page of Project Settings.
//
//  
// 나중에 해야할 것: 일반 공격 속성 테이블 따라 값 읽기, 
// 
// 로그 출력용 더미
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

	// 스켈레톤 메쉬 설정
	ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Developers/syhwms/Collections/AnimTest/Idle.Idle"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -80), FRotator(0, 270, 0));
		//GetMesh()->SetWorldScale3D(FVector(10.0f, 10.0f, 10.0f));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

		//무기
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

		//콜리전 적용
		//Weapon->SetCollisionProfileName(TEXT("PlayerAttack"));

		// 블루프린트 애니메이션 적용
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Developers/syhwms/Collections/AnimTest/BP_Irene.BP_Irene_C"));

		if (CharacterAnimInstance.Succeeded())
		{
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
		}
	}

	// 콜라이더 설정
	GetCapsuleComponent()->InitCapsuleSize(25.f, 80.0f);
	/*
	FindMonsterCollsion = CreateDefaultSubobject<UBoxComponent>(TEXT("FindMonster"));
	FindMonsterCollsion->SetRelativeLocation(FVector(300, 0, 0));
	FindMonsterCollsion->SetBoxExtent(FVector(300.0f, 300.0f, 100.0f));

	FindTargetCollsion = CreateDefaultSubobject<UBoxComponent>(TEXT("FindTarget"));
	FindTargetCollsion->SetRelativeLocation(FVector(100, 0, 0));
	FindTargetCollsion->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	*/

	// 스프링암 설정
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 46.0f), FRotator(-20.0f, 90.0f, 0.0f));
	//SpringArmComp->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
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
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	// 점프 높이
	GetCharacterMovement()->JumpZVelocity = 900.0f;

	// 기본 최대 이동속도
	GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;

	// 플레이어 스폰 시 기본 제어 설정
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 상태 클래스 메모리 할당 후 정지 상태 적용
	CharacterState = new IreneFSM();
	CharacterState->setState(StateEnum::Idle);

	// IreneCharater.h의 변수 초기화

	// 컨트롤러 초기화
	WorldController = nullptr;

	// WASD 키 입력 초기화
	MoveKey.Add(0);
	MoveKey.Add(0);
	MoveKey.Add(0);
	MoveKey.Add(0);

	// 자동이동 방향 초기화
	MoveAutoDirection.ZeroVector;
	// 추락 중 구르기 입력 초기화
	IsFallingRoll = false;

	TargetMonster = nullptr;

	// PlayerCharacterDataStruct.h의 하단 public 변수들 초기화

	CharacterDataStruct.CurrentHP = CharacterDataStruct.MaxHP;
	CharacterDataStruct.CurrentMP = CharacterDataStruct.MaxMP;

	//초기 속성
	Attribute = EAttributeKeyword::e_Fire;

	//ui 설정
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

	bShowLog = false;
}

// Called when the game starts or when spawned
void AIreneCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 컨트롤러 받아오기
	WorldController = GetWorld()->GetFirstPlayerController();

	//김재섭
	auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (nullptr == GameInstance)
	{
		STARRYLOG(Error, TEXT("GameInstance is Not STGameInstance"));
	}
	else
	{
		GameInstance->SetPlayer(this);
	}

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

	// 대쉬상태일땐 MoveAuto로 강제 이동을 시킴
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") != 0)
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
		DodgeKeyword();
	}
	MoveStop();
	if (CharacterDataStruct.IsInvincibility == true)
		SetActorEnableCollision(false);

	if(GetCharacterMovement()->IsFalling())
	{
		if (GetCharacterMovement()->GravityScale >= 1 && GetCharacterMovement()->GravityScale < 2.1f) 
		{
			// GravityScale = y축 값, x축 부호-, 수치는 작을수록 체공 증가
			GetCharacterMovement()->GravityScale = 2-FMath::Clamp(FMath::Cos(FMath::DegreesToRadians((GetCharacterMovement()->Velocity.Z * 9) / (GetCharacterMovement()->JumpZVelocity/10))) * 1.0f, -1.0f, 1.0f);
		}
		else
			GetCharacterMovement()->GravityScale = 2.1f;
	}
	else
		GetCharacterMovement()->GravityScale = 2;

	if (TargetMonster != nullptr) 
	{
		//if (bShowLog)
			//UE_LOG(LogTemp, Error, TEXT("Target Name: %s, Dist: %f"), *TargetMonster->GetName(), FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()));
		// 타겟몹이 죽거나 거리가 멀어지면 초기화
		if (TargetMonster->IsPendingKill() == true || FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()) > 500.0f)
			TargetMonster = nullptr;
	}
}

#pragma region Move
void AIreneCharacter::MoveForward()
{
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		// 0: 전진, 2: 후진
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
		// 1: 좌측, 3: 우측
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
	// 아무 키 입력이 없을 경우 정지 상태 지정
	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Idle") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Jump") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
		{
			ChangeStateAndLog(StateEnum::Idle);
		}
	}
	// 점프 상태 중 키입력에 따라 바닥에 도착할 경우 정지, 걷기, 달리기 상태 지정
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
	if (MoveAutoDirection == FVector(0, 0, 0))
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
	if (GetMovementComponent()->IsFalling())
	{
		CharacterDataStruct.MoveSpeed = 1.0f;
		MoveAutoDirection = FVector(0, 0, 0);
		GetWorld()->GetTimerManager().ClearTimer(MoveAutoWaitHandle);
		if(strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
			CharacterState->setState(StateEnum::Jump);
	}

	if (strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") == 0)
		AddMovementInput(MoveAutoDirection, CharacterDataStruct.MoveSpeed);
}

void AIreneCharacter::StartJump()
{
	if (!GetCharacterMovement()->IsFalling() 
		&& strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") != 0 
		&& strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Attack") != 0
		&& strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
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

		GetMovementComponent()->Velocity = GetMovementComponent()->Velocity / 3;

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
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
	if (MoveKey[1] != 2 && MoveKey[2] != 2 && MoveKey[3] != 2)
		CharacterDataStruct.MoveSpeed = 1;
}
void AIreneCharacter::MoveReleasedA()
{
	MoveKey[1] = 0;
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
	if (MoveKey[0] != 2 && MoveKey[2] != 2 && MoveKey[3] != 2)
		CharacterDataStruct.MoveSpeed = 1;
}
void AIreneCharacter::MoveReleasedS()
{
	MoveKey[2] = 0;
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
	if (MoveKey[0] != 2 && MoveKey[1] != 2 && MoveKey[3] != 2)
		CharacterDataStruct.MoveSpeed = 1;
}
void AIreneCharacter::MoveReleasedD()
{
	MoveKey[3] = 0;
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
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
			// 마우스 왼쪽 누르고 있을 때 연속공격 지연 시간(한번에 여러번 공격 인식 안하도록 함)
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
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		ChangeStateAndLog(StateEnum::Attack);
		IreneAnim->PlayEffectAttackMontage();
	}
}
void AIreneCharacter::MouseWheel(float Rate)
{
	SpringArmComp->TargetArmLength -= Rate * CharacterDataStruct.MouseWheelSpeed;
	SpringArmComp->TargetArmLength = FMath::Clamp(SpringArmComp->TargetArmLength, 250.0f, 550.0f);
}

void AIreneCharacter::MainKeyword()
{
	//속상변환 차례대로 속성이 변환
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
	FOnAttributeChange.Broadcast();
}
void AIreneCharacter::ActionKeyword1()
{
	if (bShowLog)
	UE_LOG(LogTemp, Warning, TEXT("ActionKeyword1"));
}
void AIreneCharacter::ActionKeyword2()
{
	if (bShowLog)
	UE_LOG(LogTemp, Warning, TEXT("ActionKeyword2"));
}
void AIreneCharacter::ActionKeyword3()
{
	if (bShowLog)
	UE_LOG(LogTemp, Warning, TEXT("ActionKeyword3"));
}

void AIreneCharacter::DodgeKeyword()
{
	if (!GetMovementComponent()->IsFalling() &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Dodge") != 0 &&
		strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
	{
		IreneAnim->StopAllMontages(0);
		ChangeStateAndLog(StateEnum::Dodge);

		float WaitTime = 1.5f; //시간을 설정
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;

		GetWorld()->GetTimerManager().SetTimer(MoveAutoWaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				// 도중에 추락 안하고 정상적으로 진행됬을 때
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
			//int32 FallingPower = 500000;
			//GetCharacterMovement()->AddImpulse(FVector(0, 0, -1) * FallingPower);

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
	PlayerInputComponent->BindAction("ActionKeyword1", IE_Pressed, this, &AIreneCharacter::ActionKeyword1);
	PlayerInputComponent->BindAction("ActionKeyword2", IE_Pressed, this, &AIreneCharacter::ActionKeyword2);
	PlayerInputComponent->BindAction("ActionKeyword3", IE_Pressed, this, &AIreneCharacter::ActionKeyword3);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AIreneCharacter::DodgeKeyword);
	PlayerInputComponent->BindAction("MouseCursor", IE_Pressed, this, &AIreneCharacter::MouseCursorKeyword);

	// 마우스
	PlayerInputComponent->BindAxis("Turn", this, &AIreneCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AIreneCharacter::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", this, &AIreneCharacter::LeftButton);
	PlayerInputComponent->BindAction("RightButton", IE_Pressed, this, &AIreneCharacter::RightButton);
	PlayerInputComponent->BindAxis("MouseWheel", this, &AIreneCharacter::MouseWheel);

	//박찬영
	//스탑워치 컨트롤
	/*PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchContorl);
	PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);*/

	// 속성 변환 테스트
	//PlayerInputComponent->BindAction("AttributeChange", IE_Pressed, this, &AIreneCharacter::AttributeChange);
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
	FindNearMonster();

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
}
#pragma endregion

#pragma region Collision
void AIreneCharacter::FindNearMonster()
{
	float far = 300;
	// 가로, 높이, 세로
	FVector BoxSize = FVector(150, 50, far);
	// 최대거리
	float NearPosition = far;

	// 리스트에 모든 충돌 결과 담는다.
	TArray<FHitResult> MonsterList;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepMultiByChannel(
		MonsterList,
		GetActorLocation() + GetActorForwardVector() * far,
		GetActorLocation() + GetActorForwardVector() * far,
		FRotationMatrix::MakeFromZ(GetActorForwardVector() * far).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel8,
		FCollisionShape::MakeBox(BoxSize*1),
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
			// 리스트결과에 레이케스트 발사(반복)
			FHitResult RayHit;
			bool bLayResult = GetWorld()->LineTraceSingleByChannel(
				RayHit,
				GetActorLocation(),
				Monster.GetActor()->GetActorLocation(),
				ECollisionChannel::ECC_GameTraceChannel8,
				Params);

			// 맞춘 액터가 캡슐오브젝트를 가지고 있는지 확인
			if (bLayResult && RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>() != nullptr)
			{
				// 거리 최소 찾기
				float FindNearTarget = FVector::Dist(GetActorLocation(), RayHit.GetActor()->GetActorLocation());
				// 기존 오브젝트 충돌체 프로필 이름
				FName TargetCollisionProfileName;
				// 새로운 오브젝트 충돌체 프로필 이름
				FName RayCollisionProfileName = RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
				FName EnemyProfile = "Enemy";
				FName ObjectProfile = "Object";

				// 맞췄을 때 캡슐컴포넌트를 가지고 카메라에 렌더링 되며 정상적으로 살아있는 몬스터 또는 오브젝트 찾기
				if (RayHit.Actor.IsValid() &&
					(RayCollisionProfileName == EnemyProfile || RayCollisionProfileName == ObjectProfile)
					&& RayHit.GetActor()->WasRecentlyRendered())
				{						
					// 첫 몬스터 할당
					if (TargetMonster == nullptr)
					{
						TargetMonster = RayHit.GetActor();
						NearPosition = FindNearTarget;
					}

					TargetCollisionProfileName = TargetMonster->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
					if (bShowLog)
					UE_LOG(LogTemp, Warning, TEXT("Name: %s, Dist: %f"), *RayHit.GetActor()->GetName(), FindNearTarget);

					// 몬스터 또는 오브젝트와 플레이어간 거리가 가장 작은 액터를 찾는다.
					if(NearPosition >= FindNearTarget)
					{
						// 만약 최단거리가 같은 액터가 있다면
						if (NearPosition == FindNearTarget)
						{
							if(TargetCollisionProfileName == EnemyProfile && RayCollisionProfileName == EnemyProfile)
							{
								NearPosition = FindNearTarget;
								TargetMonster = RayHit.GetActor();
							}
							else if(TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == EnemyProfile)
							{
								NearPosition = FindNearTarget;
								TargetMonster = RayHit.GetActor();
							}
							else if(TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == ObjectProfile)
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
	// 몬스터를 찾고 쳐다보기
	if(TargetMonster != nullptr)
	{
		if (bShowLog)
		UE_LOG(LogTemp, Error, TEXT("Target Name: %s, Dist: %f"), *TargetMonster->GetName(), FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()));
		float z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetMonster->GetActorLocation()).Yaw;
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, z, 0.0f));
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

	if(strcmp(CharacterState->StateEnumToString(CharacterState->getState()), "Death") != 0)
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

// 박찬영 코드
#pragma region Park
EAttributeKeyword AIreneCharacter::GetAttribute()
{
	return Attribute;
}

float AIreneCharacter::GetATK()
{
	return CharacterDataStruct.Strength;
}

void AIreneCharacter::AttributeChange()
{
	
}
#pragma endregion

#pragma region StopWatch
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
#pragma endregion