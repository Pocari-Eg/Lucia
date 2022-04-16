// Fill out your copyright notice in the Description page of Project Settings.
//
//  
// 나중에 해야할 것: 일반 공격 속성 테이블 따라 값 읽기, 
// 
// 로그 출력용 더미
// UE_LOG(LogTemp, Error, TEXT("Sub"));
// STARRYLOG(Error, TEXT("Sub"));

#include "IreneCharacter.h"
#include "IreneAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "STGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "StarryTailGameMode.h"
#include "UI/PlayerHudWidget.h"


#pragma region Setting
// Sets default values
AIreneCharacter::AIreneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레톤 메쉬 설정
	ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Animation/Irene/Idle.Idle"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -80), FRotator(0, 270, 0));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

		//무기
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
		//카메라
		//FName CameraSocket(TEXT("Hip_Socket"));
		//if (GetMesh()->DoesSocketExist(CameraSocket))
		//{
			// 스프링암 설정
			//SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
			//SpringArmComp->TargetArmLength = CharacterDataStruct.FollowCameraZPosition;
			//SpringArmComp->bEnableCameraLag = true;
			//SpringArmComp->CameraLagSpeed = 0.0f;
			//SpringArmComp->SetupAttachment(GetMesh(), CameraSocket);
		//}


		//콜리전 적용
		Weapon->SetCollisionProfileName(TEXT("PlayerAttack"));
		Weapon->SetGenerateOverlapEvents(false);

		// 블루프린트 애니메이션 적용
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Animation/Irene/BP/BP_IreneAnination.BP_IreneAnination_C"));

		if (CharacterAnimInstance.Succeeded())
		{
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
		}
	}
	// 점프커브
	ConstructorHelpers::FObjectFinder<UCurveFloat>JumpCurve(TEXT("/Game/Math/Jump.Jump"));
	if (JumpCurve.Succeeded())
	{
		JumpGravityCurve = JumpCurve.Object;
	}

	// 카메라 쉐이크 커브
	ConstructorHelpers::FObjectFinder<UCurveFloat>CameraCurveDataObject(TEXT("/Game/Math/CameraShakeCurve.CameraShakeCurve"));
	if (CameraCurveDataObject.Succeeded())
	{
		CameraShakeCurve.Add(CameraCurveDataObject.Object);
	}

	// 데이터 테이블
	ConstructorHelpers::FObjectFinder<UDataTable>DT_AttackDataTable(TEXT("/Game/Math/BP_AttackDataTable.BP_AttackDataTable"));
	if (DT_AttackDataTable.Succeeded())
	{
		AttackDataTable = DT_AttackDataTable.Object;
	}

	// 콜라이더 설정
	GetCapsuleComponent()->InitCapsuleSize(25.f, 80.0f);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComp->TargetArmLength = CharacterDataStruct.FollowCameraZPosition;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->SetRelativeLocation(FVector(0,0,53));
	SpringArmComp->CameraLagSpeed = 0.0f;
	SpringArmComp->SetupAttachment(GetCapsuleComponent());

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
	GetCharacterMovement()->JumpZVelocity = CharacterDataStruct.JumpStartPower;

	// 기본 최대 이동속도
	GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;

	// 플레이어 스폰 시 기본 제어 설정
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 상태 클래스 메모리 할당 후 정지 상태 적용
	CharacterState = new IreneFSM();
	CharacterState->setState(IdleState::getInstance());

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

	// PlayerCharacterDataStruct.h의 변수들 초기화
	CharacterDataStruct.CurrentHP = CharacterDataStruct.MaxHP;
	CharacterDataStruct.CurrentMP = CharacterDataStruct.MaxMP;

	//초기 속성
	Attribute = EAttributeKeyword::e_Fire;

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_PlayerHud(TEXT("/Game/UI/BluePrint/BP_PlayerHud.BP_PlayerHud_C"));
	if (UI_PlayerHud.Succeeded())
	{

		PlayerHudClass = UI_PlayerHud.Class;
	}

	WalkEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/SFX_FootStep");
	AttackEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/SFX_Attack");

	bStartJump = false;
	JumpingTime = 0.0f;
	bFollowTarget = false;
	FollowTargetAlpha = 0.0f;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;
	IsCharging = false;
	ChargingTime = 0.0f;
	bUseLeftButton = false;
	bUseRightButton = false;
	bUseMP = false;
	UseMP = 0.0f;

	bShowLog = false;

	CameraShakeOn = false;
	GoTargetOn = false;
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

	// 애니메이션 속성 초기화
	IreneAnim->SetAttribute(Attribute);
	

	PlayerHud = CreateWidget<UPlayerHudWidget>(GetGameInstance(), PlayerHudClass);
	PlayerHud->AddToViewport();
	PlayerHud->BindCharacter(this);
	PlayerHud->FireAttributesOn();
	//사운드 세팅
	AttackSound = new SoundManager(AttackEvent, GetWorld());
	AttackSound->SetVolume(0.3f);
	AttackSound->SetParameter("Attributes", 0.0f);
	WalkSound = new SoundManager(WalkEvent, GetWorld());
	WalkSound -> SetVolume(1.2f);
	AttackSound->SetParameter("Material", 0.0f);

}
void AIreneCharacter::Destroyed()
{
	Super::Destroyed();

	// Example to bind to OnPlayerDied event in GameMode. 
	if (UWorld* World = GetWorld())
	{
		if (AStarryTailGameMode* GameMode = Cast<AStarryTailGameMode>(World->GetAuthGameMode()))
		{
			GameMode->GetOnPlayerDied().Broadcast(this);
		}
	}
}

void AIreneCharacter::CallRestartPlayer()
{
	//Get a reference to the Pawn Controller.
	AController* CortollerRef = GetController();

	//Destroy the Player.   
	Destroy();

		//Get the World and GameMode in the world to invoke its restart player function.
		if (UWorld* World = GetWorld())
		{
			if (AStarryTailGameMode* GameMode = Cast<AStarryTailGameMode>(World->GetAuthGameMode()))
			{
				GameMode->RestartPlayer(CortollerRef);
			}
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
				if(bUseLeftButton)
					IreneAnim->JumpToAttackMontageSection(CharacterDataStruct.CurrentCombo);
				if (bUseRightButton)
					IreneAnim->JumpToEffectAttackMontageSection(CharacterDataStruct.CurrentCombo);
			}
		});
	IreneAnim->OnAttackHitCheck.AddUObject(this, &AIreneCharacter::AttackCheck);
	IreneAnim->OnAttackStopCheck.AddUObject(this, &AIreneCharacter::AttackStopCheck);
	IreneAnim->OnFootStep.AddUObject(this, &AIreneCharacter::FootStepSound);
}
#pragma endregion Setting

// Called every frame
void AIreneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 대쉬상태일땐 MoveAuto로 강제 이동을 시킴
	if (CharacterState->getStateToString().Compare(FString("Dodge")) != 0)
	{
		if (CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0) {
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
		//구르다가 땅에 도착
		IsFallingRoll = false;
		DodgeKeyword();
	}
	MoveStop();
	
	if (CharacterDataStruct.IsInvincibility == true)
		SetActorEnableCollision(false);

	// 점프 그래프 사용
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

	// 카메라 쉐이크 그래프 사용
	if (CharacterDataStruct.IsAttacking && CharacterDataStruct.CurrentCombo == CharacterDataStruct.MaxCombo && CameraShakeOn)
	{
		CameraShakeTime += DeltaTime;
		FRotator CameraRotate = CameraComp->GetRelativeRotation();
		CameraRotate.Pitch += CameraShakeCurve[0]->GetFloatValue(CameraShakeTime*50);
		CameraComp->SetRelativeRotation(CameraRotate);
	}
	else
	{
		CameraShakeTime = 0;
		CameraShakeOn = false;
		CameraComp->SetRelativeRotation(FRotator::ZeroRotator);
	}

	// 차징 사용
	//if(IsCharging)
	//{
	//	ChargingTime += DeltaTime;
	//}

	if (TargetMonster != nullptr)
	{
		//if (bShowLog)
			//UE_LOG(LogTemp, Error, TEXT("Target Name: %s, Dist: %f"), *TargetMonster->GetName(), FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()));
		// 타겟몹이 죽거나 거리가 멀어지면 초기화
		if (TargetMonster->IsPendingKill() == true || FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()) > 700.0f)
			TargetMonster = nullptr;
	}
}

#pragma region Move
void AIreneCharacter::MoveForward()
{
	if (CharacterState->getStateToString().Compare(FString("Death")) != 0)
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
	if (CharacterState->getStateToString().Compare(FString("Death")) != 0)
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
	if (CharacterState->getStateToString().Compare(FString("Idle")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
		{
			if (CharacterState->getStateToString().Compare(FString("Sprint")) == 0)
			{
				IreneAnim->SetSprintStopAnim(true);
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
					{
						IreneAnim->SetSprintStopAnim(false);
					}, 0.3f, false);
			}
			ChangeStateAndLog(IdleState::getInstance());
		}
	}
	// 점프 상태 중 키입력에 따라 바닥에 도착할 경우 정지, 걷기, 달리기 상태 지정
	if (CharacterState->getStateToString().Compare(FString("Jump")) == 0)
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
	// 이동 후 공격
	if (bFollowTarget)
	{
		FollowTargetAlpha += GetWorld()->GetDeltaSeconds() * 2 * CharacterDataStruct.TargetFollowSpeed;
		if (FollowTargetAlpha >= 1)
			FollowTargetAlpha = 1;
		FVector tar = FMath::Lerp(PlayerPosVec, TargetPosVec, FollowTargetAlpha);
		GetCapsuleComponent()->SetRelativeLocation(tar);

		if (FVector::Dist(tar, TargetPosVec) <= 1)
		{
			if(GetAnimName() == FName("B_Attack_1"))
				GoTargetOn = true;
			DoAttack();
		}
	}
	if (CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0)
	{
		if (MoveAutoDirection == FVector(0, 0, 0))
		{
			MoveAutoDirection += GetActorForwardVector();
			MoveAutoDirection.Normalize();
		}

		// 대쉬 도중 떨어지면 점프 상태로 강제 변화
		if (GetMovementComponent()->IsFalling())
		{
			CharacterDataStruct.MoveSpeed = 1.0f;
			MoveAutoDirection = FVector(0, 0, 0);
			GetWorld()->GetTimerManager().ClearTimer(MoveAutoWaitHandle);
			if (CharacterState->getStateToString().Compare(FString("Death")) != 0)
				CharacterState->setState(JumpState::getInstance());
		}

		//if (CharacterState->getStateToString().Compare(FString("Dodge")) == 0)
			//AddMovementInput(MoveAutoDirection, CharacterDataStruct.MoveSpeed);
	}
}

void AIreneCharacter::StartJump()
{
	if (!GetCharacterMovement()->IsFalling() &&
		CharacterState->getStateToString().Compare(FString("Dodge")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
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
		Direction.Normalize();

		GetMovementComponent()->Velocity = GetMovementComponent()->Velocity / 3;

		bPressedJump = true;
		bStartJump = true;
		ChangeStateAndLog(JumpState::getInstance());
	}
}
void AIreneCharacter::StopJump()
{
	bPressedJump = false;
}

#pragma region MoveInput
void AIreneCharacter::MovePressedW()
{
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		if (CharacterState->getStateToString().Compare(FString("Idle")) == 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
			ChangeStateAndLog(RunState::getInstance());
		}
		MoveKey[0] = 1;
	}
	else
		MoveKey[0] = 3;
}
void AIreneCharacter::MovePressedA()
{
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		if (CharacterState->getStateToString().Compare(FString("Idle")) == 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
			ChangeStateAndLog(RunState::getInstance());
		}
		MoveKey[1] = 1;
	}
	else
		MoveKey[1] = 3;
}
void AIreneCharacter::MovePressedS()
{
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		if (CharacterState->getStateToString().Compare(FString("Idle")) == 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
			ChangeStateAndLog(RunState::getInstance());
		}
		MoveKey[2] = 1;
	}
	else
		MoveKey[2] = 3;
}
void AIreneCharacter::MovePressedD()
{
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		if (CharacterState->getStateToString().Compare(FString("Idle")) == 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
			ChangeStateAndLog(RunState::getInstance());
		}
		MoveKey[3] = 1;
	}
	else
		MoveKey[3] = 3;
}

void AIreneCharacter::MoveDoubleClickW()
{
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		MoveKey[0] = 2;
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;
		ChangeStateAndLog(SprintState::getInstance());
		CharacterDataStruct.MoveSpeed = 2;
	}
	else
		MoveKey[0] = 4;
}
void AIreneCharacter::MoveDoubleClickA()
{
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		MoveKey[1] = 2;
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;
		ChangeStateAndLog(SprintState::getInstance());
		CharacterDataStruct.MoveSpeed = 2;
	}
	else
		MoveKey[1] = 4;
}
void AIreneCharacter::MoveDoubleClickS()
{
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		MoveKey[2] = 2;
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;
		ChangeStateAndLog(SprintState::getInstance());
		CharacterDataStruct.MoveSpeed = 2;
	}
	else
		MoveKey[2] = 4;
}
void AIreneCharacter::MoveDoubleClickD()
{
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		MoveKey[3] = 2;
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;
		ChangeStateAndLog(SprintState::getInstance());
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
#pragma endregion MoveInput
#pragma endregion Move

#pragma region Input
void AIreneCharacter::Turn(float Rate)
{
	if (WorldController->bShowMouseCursor == false &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
		AddControllerYawInput(Rate * CharacterDataStruct.EDPI);
}
void AIreneCharacter::LookUp(float Rate)
{
	float yaw = FRotator::NormalizeAxis(WorldController->GetControlRotation().Pitch) + Rate * CharacterDataStruct.EDPI * WorldController->InputPitchScale;

	if (yaw < 50)
	{
		if (WorldController->bShowMouseCursor == false &&
			CharacterState->getStateToString().Compare(FString("Death")) != 0)
			AddControllerPitchInput(Rate * CharacterDataStruct.EDPI);
	}
}

void AIreneCharacter::LeftButton(float Rate)
{	
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Fall")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Dodge")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		if (Rate >= 1.0 && !AttackWaitHandle.IsValid() && bUseRightButton == false)
		{
			bUseLeftButton = true;
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
				ChangeStateAndLog(BasicAttackState::getInstance());
				AttackStartComboState();
				AttackSound->SetParameter("Attributes", 0.0f);
				IreneAnim->PlayAttackMontage();
				
				IreneAnim->JumpToAttackMontageSection(CharacterDataStruct.CurrentCombo);
				CharacterDataStruct.IsAttacking = true;
			}
		}
	}
}
void AIreneCharacter::RightButton(float Rate)
{

	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Fall")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Dodge")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		FAttackDataTable* table = GetNameAtDataTable(FName("Actionkeyword_1_F"));
		if (table != nullptr)
		{
			if (Rate >= 1.0 && !AttackWaitHandle.IsValid() && bUseLeftButton == false && CharacterDataStruct.CurrentMP >= table->MANA)
			{
				bUseRightButton = true;
				// 마우스 오른쪽 누르고 있을 때 연속공격 지연 시간(한번에 여러번 공격 인식 안하도록 함)
				float WaitTime = 0.15f;

				GetWorld()->GetTimerManager().SetTimer(AttackWaitHandle, FTimerDelegate::CreateLambda([&]()
					{
						AttackWaitHandle.Invalidate();
					}), WaitTime, false);

				if (CharacterDataStruct.IsAttacking)
				{
					if (CharacterDataStruct.CanNextCombo)
					{
						if (!(CharacterDataStruct.CurrentMP == table->MANA && IreneAnim->GetCurrentActiveMontage() != NULL))
							CharacterDataStruct.IsComboInputOn = true;
					}
				}
				else
				{
					ChangeStateAndLog(ActionAttackState::getInstance());
					AttackStartComboState();

					switch (Attribute)
		          {
		             case EAttributeKeyword::e_None:
			            break;
		               case EAttributeKeyword::e_Fire:
			            AttackSound->SetParameter("Attributes", 1.0f);
			           break;
		              case EAttributeKeyword::e_Water:
			           AttackSound->SetParameter("Attributes", 2.0f);
		             	break;
		           case EAttributeKeyword::e_Thunder:
		            	AttackSound->SetParameter("Attributes", 3.0f);

		           	break;
		                default:
			           break;
	            	} 
				
					IreneAnim->PlayEffectAttackMontage();
					IreneAnim->JumpToEffectAttackMontageSection(CharacterDataStruct.CurrentCombo);
					CharacterDataStruct.IsAttacking = true;
				}
			}
		}
	}
}
void AIreneCharacter::RightButtonPressed()
{	
	/*
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Fall")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Dodge")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		ChangeStateAndLog(AttackState::getInstance());
		IsCharging = true;
		ChargingTime = 0.0f;
	}
	*/
}
void AIreneCharacter::RightButtonReleased()
{
	/*
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Fall")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Dodge")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		IsCharging = false;
		if(ChargingTime > 7.0f)
		{
			CharacterDataStruct.Strength = 100;
			IreneAnim->PlayEffectAttackMontage();
		}
		else if(ChargingTime > 4.0f)
		{
			CharacterDataStruct.Strength = 60;
			IreneAnim->PlayEffectAttackMontage();
		}
		else if (ChargingTime > 1.0f)
		{
			CharacterDataStruct.Strength = 40;
			IreneAnim->PlayEffectAttackMontage();
		}
		else
		{
			CharacterDataStruct.Strength = 5;
			IreneAnim->PlayEffectAttackMontage();
		}
		ChargingTime = 0.0f;
	}*/
}

void AIreneCharacter::MouseWheel(float Rate)
{
	SpringArmComp->TargetArmLength -= Rate * CharacterDataStruct.MouseWheelSpeed;
	SpringArmComp->TargetArmLength = FMath::Clamp(SpringArmComp->TargetArmLength, CharacterDataStruct.MinFollowCameraZPosition, CharacterDataStruct.MaxFollowCameraZPosition);
}

void AIreneCharacter::MainKeyword()
{
	if (CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0) 
	{
		//속상변환 차례대로 속성이 변환
		switch (Attribute)
		{
		case EAttributeKeyword::e_Fire:
			PlayerHud->WaterAttributesOn();
			Attribute = EAttributeKeyword::e_Water;
			break;
		case EAttributeKeyword::e_Water:
			PlayerHud->ThunderAttributesOn();

			Attribute = EAttributeKeyword::e_Thunder;
			break;
		case EAttributeKeyword::e_Thunder:
			PlayerHud->FireAttributesOn();
			Attribute = EAttributeKeyword::e_Fire;
			break;
		default:
			break;
		}
		FOnAttributeChange.Broadcast();
		IreneAnim->SetAttribute(Attribute);
	}
}

void AIreneCharacter::DodgeKeyword()
{
	if (!GetMovementComponent()->IsFalling() &&
		CharacterState->getStateToString().Compare(FString("Dodge")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		IreneAnim->StopAllMontages(0);
		ChangeStateAndLog(DodgeState::getInstance());

		float WaitTime = 0.5f; //시간을 설정
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;

		MoveAutoDirection.ZeroVector;
		// w키나 아무방향 없으면 정면으로 이동
		if (MoveKey[0] != 0 || (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0))
		{
			MoveAutoDirection += CameraComp->GetForwardVector();
		}
		if (MoveKey[1] != 0)
		{
			MoveAutoDirection += CameraComp->GetRightVector() * -1;
		}
		if (MoveKey[2] != 0)
		{
			MoveAutoDirection += CameraComp->GetForwardVector() * -2;
		}
		if (MoveKey[3] != 0)
		{
			MoveAutoDirection += CameraComp->GetRightVector();
		}
		MoveAutoDirection.Normalize();

		float z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation()+ MoveAutoDirection).Yaw;
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, z, 0.0f));

		GetWorld()->GetTimerManager().SetTimer(MoveAutoWaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				// 도중에 추락 안하고 정상적으로 진행됬을 때
				if (CharacterState->getStateToString().Compare(FString("Dodge")) == 0)
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
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AIreneCharacter::DodgeKeyword);
	PlayerInputComponent->BindAction("MouseCursor", IE_Pressed, this, &AIreneCharacter::MouseCursorKeyword);

	// 마우스
	PlayerInputComponent->BindAxis("Turn", this, &AIreneCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AIreneCharacter::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", this, &AIreneCharacter::LeftButton);
	PlayerInputComponent->BindAction("RightButton", IE_Pressed, this, &AIreneCharacter::RightButtonPressed);
	PlayerInputComponent->BindAction("RightButton", IE_Released, this, &AIreneCharacter::RightButtonReleased);
	PlayerInputComponent->BindAxis("MouseWheel", this, &AIreneCharacter::MouseWheel);
	PlayerInputComponent->BindAxis("RightButtonAxis", this, &AIreneCharacter::RightButton);

	//박찬영
	//스탑워치 컨트롤
	/*PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchContorl);
	PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);*/
}
#pragma endregion Input

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
	Weapon->SetGenerateOverlapEvents(false);
	bUseLeftButton = false;
	bUseRightButton = false;
	bUseMP = false;
	UseMP = 0.0f;
	CharacterDataStruct.CanNextCombo = false;
	CharacterDataStruct.IsComboInputOn = false;
	CharacterDataStruct.CurrentCombo = 0;
	AttackSoundParameter = 0.0f;
	AttackSound->SetParameter("Attributes", AttackSoundParameter);
	if (CharacterState->getStateToString().Compare(FString("Dodge")) != 0)
		ActionEndChangeMoveState();
}

void AIreneCharacter::AttackCheck()
{
	if (IreneAnim->GetCurrentActiveMontage() != NULL)
	{
		Weapon->SetGenerateOverlapEvents(true);
		AttackSound->SoundPlay2D();
		FindNearMonster();
	}
}
void AIreneCharacter::AttackStopCheck()
{
	IsTimeStopping = false;
	Weapon->SetGenerateOverlapEvents(false);
}
void AIreneCharacter::DoAttack()
{
	// 나중에 카메라 쉐이크 데이터 사용할 때 사용할 것(사용한다면...)
	//WorldController->ClientStartCameraShake(CameraShakeCurve);	

	// 몬스터 추적 초기화
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

				auto Mob = Cast<AMonster>(Monster.Actor);
				if (Mob != nullptr)
				{
					Mob->SetAttackedInfo(bUseMP, UseMP);
				}
				UGameplayStatics::ApplyDamage(Monster.Actor.Get(), CharacterDataStruct.Strength, NULL, this, NULL);
			}
		}
	}

	// 마나 회복
	if(bUseMP == false && UseMP != 0.0f)
	{
		CharacterDataStruct.CurrentMP += UseMP;
		
		if (CharacterDataStruct.CurrentMP > CharacterDataStruct.MaxMP)
			CharacterDataStruct.CurrentMP = CharacterDataStruct.MaxMP;
			
		OnMpChanged.Broadcast();
	}

	//속성공격 기준 몬스터 할당해제
	if (bResult)
	{
		auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
		if (STGameInstance->GetAttributeEffectMonster() != nullptr)
		{
			STGameInstance->ResetAttributeEffectMonster();
		}
	}
}
#pragma endregion Attack

#pragma region Collision
void AIreneCharacter::FindNearMonster()
{
	FAttackDataTable* table = GetNameAtDataTable(GetAnimName());
	if (table != nullptr)
	{
		CharacterDataStruct.Strength = table->ATTACK_DAMAGE_1;

		// 마나 사용 조건
		if (table->Main_Keyword != 0 && CharacterDataStruct.CurrentMP >= table->MANA)
		{
			bUseMP = true;
			UseMP = table->MANA;
			CharacterDataStruct.CurrentMP -= table->MANA;
		}
		// 마나 회복 조건
		else
		{
			bUseMP = false;
			UseMP = table->MANA;
		}
		if (table->Main_Keyword != 0 && CharacterDataStruct.CurrentMP < table->MANA)
		{
			bUseMP = false;
			UseMP = 0;
		}

		OnMpChanged.Broadcast();
	}

	if (TargetMonster != nullptr)
	{
		// 타겟이 캐릭터의 뒤에 있다면 추적 취소
		FVector targetData = TargetMonster->GetActorLocation() - GetActorLocation();
		targetData.Normalize();
		if (FVector::DotProduct(GetActorForwardVector(), targetData) < 0)
		{
			TargetMonster = nullptr;
		}
	}

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
					if (NearPosition >= FindNearTarget)
					{
						// 만약 최단거리가 같은 액터가 있다면
						if (NearPosition == FindNearTarget)
						{
							if (TargetCollisionProfileName == EnemyProfile && RayCollisionProfileName == EnemyProfile)
							{
								NearPosition = FindNearTarget;
								if(TargetMonster == nullptr)
									TargetMonster = RayHit.GetActor();
							}
							else if (TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == EnemyProfile)
							{
								NearPosition = FindNearTarget;
								if (TargetMonster == nullptr)
									TargetMonster = RayHit.GetActor();
							}
							else if (TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == ObjectProfile)
							{
								NearPosition = FindNearTarget;
								if (TargetMonster == nullptr)
									TargetMonster = RayHit.GetActor();
							}
						}
						else
						{
							NearPosition = FindNearTarget;
							if (TargetMonster == nullptr)
								TargetMonster = RayHit.GetActor();
						}
					}
				}
			}
		}
	}

	// 몬스터를 찾고 쳐다보기
	if (TargetMonster != nullptr)
	{
		//UE_LOG(LogTemp, Error, TEXT("Target Name: %s, Dist: %f"), *TargetMonster->GetName(), FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()));

		float z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetMonster->GetActorLocation()).Yaw;
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, z, 0.0f));
		// 몬스터가 공격범위 보다 멀리 있다면
		float TargetPos = FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()) - CharacterDataStruct.AttackRange;
		if (TargetPos > CharacterDataStruct.AttackRange)
		{
			// 추적 세팅
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
		//hp 바
		OnHpChanged.Broadcast();
		if (CharacterDataStruct.CurrentHP <= 0)
		{
			IreneAnim->StopAllMontages(0);
			IreneAnim->SetDeadAnim(true);
			ChangeStateAndLog(DeathState::getInstance());
		}
	}
	if (TargetMonster == nullptr)
	{
		TargetMonster = DamageCauser;
	}
	return FinalDamage;
}

#pragma endregion Collision

#pragma region State
void AIreneCharacter::ChangeStateAndLog(State* newState)
{
	if ((CharacterState->getStateToString().Compare(FString("Dodge")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0) || 
		newState == DeathState::getInstance())	
	{
		if (CharacterState->getStateToString().Compare(FString("Sprint")) != 0)
		{
			IreneAnim->SetSprintStateAnim(false);
			IreneAnim->SetSprintStopAnim(false);
		}
		else
		{
			IreneAnim->SetSprintStateAnim(true);
		}
		CharacterState->ChangeState(newState);
		IreneAnim->SetIreneStateAnim(CharacterState->getState());
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

	if (CharacterState->getStateToString().Compare(FString("Death")) != 0) 
	{
		CharacterState->setState(nullptr);
	}
	if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
		ChangeStateAndLog(IdleState::getInstance());
	}
	else if (MoveKey[0] == 2 || MoveKey[1] == 2 || MoveKey[2] == 2 || MoveKey[3] == 2)
	{
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.SprintMaxSpeed;
		ChangeStateAndLog(SprintState::getInstance());
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = CharacterDataStruct.RunMaxSpeed;
		ChangeStateAndLog(RunState::getInstance());
	}
}
FName AIreneCharacter::GetAnimName()
{
	if (CharacterState->getStateToString().Compare(FString("Dodge")) == 0)
	{
		return FName("Dodge");
	}
	if (CharacterState->getStateToString().Compare(FString("Jump")) == 0)
	{
		return FName("Jump");
	}
	if (bUseLeftButton) 
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
			switch (Attribute)
			{
			case EAttributeKeyword::e_None:
				break;
			case EAttributeKeyword::e_Fire:
				AttackSound->SetParameter("Attributes", 1.0f);
				break;
			case EAttributeKeyword::e_Water:
				AttackSound->SetParameter("Attributes", 2.0f);

				break;
			case EAttributeKeyword::e_Thunder:
				AttackSound->SetParameter("Attributes", 3.0f);

				break;
			default:
				break;
			}
			return FName("B_Attack_4");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && Attribute == EAttributeKeyword::e_None)
		{
		
			return FName("B_Attack_5_N");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && Attribute == EAttributeKeyword::e_Fire)
		{
			STARRYLOG_S(Warning);
			
			return FName("B_Attack_5_F");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && Attribute == EAttributeKeyword::e_Water)
		{
			return FName("B_Attack_5_W");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && Attribute == EAttributeKeyword::e_Thunder)
		{
			return FName("B_Attack_5_E");
		}
	}
	if (bUseRightButton) 
	{

		if (Attribute == EAttributeKeyword::e_Fire)
		{
			return FName("Actionkeyword_1_F");
		}
		if (Attribute == EAttributeKeyword::e_Water)
		{
			return FName("Actionkeyword_1_W");
		}
		if (Attribute == EAttributeKeyword::e_Thunder)
		{
			return FName("Actionkeyword_1_E");
		}
	}
	return FName("");
}
#pragma endregion State

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
float AIreneCharacter::GetHpRatio()
{
	// 비율변환 0.0 ~ 1.0
	return (CharacterDataStruct.CurrentHP < KINDA_SMALL_NUMBER) ? 0.0f : CharacterDataStruct.CurrentHP / CharacterDataStruct.MaxHP;
}

float AIreneCharacter::GetMpRatio()
{
	return (CharacterDataStruct.CurrentMP < KINDA_SMALL_NUMBER) ? 0.0f : CharacterDataStruct.CurrentMP / CharacterDataStruct.MaxMP;

}

void AIreneCharacter::FootStepSound()
{
	WalkSound->SoundPlay3D(GetActorTransform());
}
#pragma endregion Park

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
#pragma endregion StopWatch