// Fill out your copyright notice in the Description page of Project Settings.
//
//  
// 나중에 해야할 것: 일반 공격 속성 테이블 따라 값 읽기, 
// 
// 로그 출력용 더미
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

#pragma region Setting
// Sets default values
AIreneCharacter::AIreneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레톤 메쉬 설정
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Model/Irene/Irene_Skin.Irene_Skin"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -80), FRotator(0, 270, 0));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

		//무기
		const FName WeaponSocket(TEXT("hand_rSocket"));
		if (GetMesh()->DoesSocketExist(WeaponSocket))
		{
			Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_WEAPON(TEXT("/Game/Model/Irene/Test_Sw.Test_Sw"));
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
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Model/Irene/Animation/BP/BP_IreneAnimation.BP_IreneAnimation_C"));

		if (CharacterAnimInstance.Succeeded())
		{
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
		}
	}
	// 점프커브
	const ConstructorHelpers::FObjectFinder<UCurveFloat>JumpCurve(TEXT("/Game/Math/Jump.Jump"));
	if (JumpCurve.Succeeded())
	{
		JumpGravityCurve = JumpCurve.Object;
	}

	// 카메라 쉐이크 커브
	const ConstructorHelpers::FObjectFinder<UCurveFloat>CameraCurveDataObject(TEXT("/Game/Math/CameraShakeCurve.CameraShakeCurve"));
	if (CameraCurveDataObject.Succeeded())
	{
		CameraShakeCurve.Add(CameraCurveDataObject.Object);
	}

	// 콜라이더 설정
	GetCapsuleComponent()->InitCapsuleSize(25.f, 80.0f);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComp->TargetArmLength = IreneData.FollowCameraZPosition;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 53));
	SpringArmComp->CameraLagSpeed = 0.0f;
	SpringArmComp->SetupAttachment(GetCapsuleComponent());

	// 카메라 설정
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->FieldOfView = IreneData.FieldOfView;

	// 카메라 회전과 캐릭터 회전 연동 안되도록 설정
	bUseControllerRotationYaw = false;
	SpringArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	// 점프 높이
	GetCharacterMovement()->JumpZVelocity = IreneData.JumpStartPower;

	// 기본 최대 이동속도
	GetCharacterMovement()->MaxWalkSpeed = IreneData.RunMaxSpeed;

	// 플레이어 스폰 시 기본 제어 설정
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// IreneCharacter.h의 변수 초기화

	// 컨트롤러 초기화
	WorldController = nullptr;
	HpRecoveryData.bIsRecovering = false;

	// PlayerCharacterDataStruct.h의 변수들 초기화
	IreneData.CurrentHP = IreneData.MaxHP;
	IreneData.CurrentMP = IreneData.MaxMP;

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
	const auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
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
	IreneAnim->SetAttribute(IreneAttack->Attribute);
	IreneUIManager->Begin();


}
void AIreneCharacter::Destroyed()
{
	Super::Destroyed();

	// Example to bind to OnPlayerDied event in GameMode. 
	if (const UWorld* World = GetWorld())
	{
		if (const AStarryTailGameMode* GameMode = Cast<AStarryTailGameMode>(World->GetAuthGameMode()))
		{
			GameMode->GetOnPlayerDied().Broadcast(this);
		}
	}
}

void AIreneCharacter::CallRestartPlayer()
{
	//Get a reference to the Pawn Controller.
	AController* ControllerRef = GetController();

	//Destroy the Player.   
	Destroy();

	//Get the World and GameMode in the world to invoke its restart player function.
	if (const UWorld* World = GetWorld())
	{
		if (AStarryTailGameMode* GameMode = Cast<AStarryTailGameMode>(World->GetAuthGameMode()))
		{
			GameMode->RestartPlayer(ControllerRef);
		}
	}
}

void AIreneCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	IreneState = NewObject<UIreneFSM>(this);
	IreneState->SetState(UIdleState::GetInstance());
	
	IreneAnim = Cast<UIreneAnimInstance>(GetMesh()->GetAnimInstance());
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
	
	// 대쉬상태일땐 MoveAuto로 강제 이동을 시킴
	if (IreneState->GetStateToString().Compare(FString("Dodge")) != 0)
	{
		if (IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0) {
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
	if (IreneInput->IsFallingRoll && !GetMovementComponent()->IsFalling())
	{
		//구르다가 땅에 도착
		IreneInput->IsFallingRoll = false;
		IreneInput->DodgeKeyword();
	}
	IreneInput->MoveStop();

	if (IreneData.IsInvincibility == true)
		SetActorEnableCollision(false);

	// 점프 그래프 사용
	if (IreneInput->bStartJump)
	{
		IreneInput->JumpingTime += DeltaTime;
		GetCharacterMovement()->GravityScale = JumpGravityCurve->GetFloatValue(IreneInput->JumpingTime);
	}
	if (!GetCharacterMovement()->IsFalling())
	{
		IreneInput->JumpingTime = 0.0f;
		IreneInput->bStartJump = false;
	}

	// 카메라 쉐이크 그래프 사용
	if (IreneData.IsAttacking && IreneData.CurrentCombo == IreneData.MaxCombo && CameraShakeOn)
	{
		IreneAttack->CameraShakeTime += DeltaTime;
		FRotator CameraRotate = CameraComp->GetRelativeRotation();
		CameraRotate.Pitch += CameraShakeCurve[0]->GetFloatValue(IreneAttack->CameraShakeTime * 50);
		CameraComp->SetRelativeRotation(CameraRotate);
	}
	else
	{
		IreneAttack->CameraShakeTime = 0;
		CameraShakeOn = false;
		CameraComp->SetRelativeRotation(FRotator::ZeroRotator);
	}

	// 차징 사용
	//if(IsCharging)
	//{
	//	ChargingTime += DeltaTime;
	//}

	if (IreneAttack->TargetMonster != nullptr)
	{
		//if (bShowLog)
			//UE_LOG(LogTemp, Error, TEXT("Target Name: %s, Dist: %f"), *TargetMonster->GetName(), FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()));
		// 타겟몹이 죽거나 거리가 멀어지면 초기화
		const auto Mob = Cast<AMonster>(IreneAttack->TargetMonster);
		if (Mob != nullptr)
		{
			if (Mob->GetHp() <= 0 || FVector::Dist(GetActorLocation(), IreneAttack->TargetMonster->GetActorLocation()) > 700.0f)
				IreneAttack->TargetMonster = nullptr;
		}
	}

	// 카메라 회전
	if (IreneAttack->bFollowCameraTarget)
	{
		const float Dist = FVector::Dist(IreneAttack->CameraRot.Vector(), IreneAttack->TargetCameraRot.Vector());
		IreneAttack->FollowTargetCameraAlpha += GetWorld()->GetDeltaSeconds() * IreneData.TargetCameraFollowSpeed / Dist;
		if (IreneAttack->FollowTargetCameraAlpha >= 1)
		{
			IreneAttack->FollowTargetCameraAlpha = 1;
		}
		const FRotator Tar = FMath::Lerp(IreneAttack->CameraRot, IreneAttack->TargetCameraRot, IreneAttack->FollowTargetCameraAlpha);
		WorldController->SetControlRotation(Tar);
		if (IreneAttack->FollowTargetCameraAlpha >= 1)
		{
			IreneAttack->bFollowCameraTarget = false;
			IreneAttack->FollowTargetCameraAlpha = 0.0f;
			IreneAttack->CameraRot = FRotator::ZeroRotator;
			IreneAttack->TargetCameraRot = FRotator::ZeroRotator;
		}
	}
	
	IreneState->Update(DeltaTime);
}



// Called to bind functionality to input
void AIreneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 움직임 관련 키보드 입력
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

	// 움직임 외 키보드 입력
	PlayerInputComponent->BindAction("MainKeyword", IE_Pressed, IreneInput, &UIreneInputInstance::MainKeyword);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, IreneInput, &UIreneInputInstance::DodgeKeyword);
	PlayerInputComponent->BindAction("MouseCursor", IE_Pressed, IreneInput, &UIreneInputInstance::MouseCursorKeyword);

	// 마우스
	PlayerInputComponent->BindAxis("Turn", IreneInput, &UIreneInputInstance::Turn);
	PlayerInputComponent->BindAxis("LookUp", IreneInput, &UIreneInputInstance::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", IreneInput, &UIreneInputInstance::LeftButton);
	PlayerInputComponent->BindAction("RightButton", IE_Pressed, IreneInput, &UIreneInputInstance::RightButtonPressed);
	PlayerInputComponent->BindAction("RightButton", IE_Released, IreneInput, &UIreneInputInstance::RightButtonReleased);
	PlayerInputComponent->BindAxis("MouseWheel", IreneInput, &UIreneInputInstance::MouseWheel);
	PlayerInputComponent->BindAxis("RightButtonAxis", IreneInput, &UIreneInputInstance::RightButton);

	//박찬영
	//스탑워치 컨트롤
	/*PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchControl);
	PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);*/
}

#pragma region Collision
void AIreneCharacter::FindNearMonster()
{
	FAttackDataTable* table = IreneAttack->GetNameAtDataTable(GetAnimName());
	if (table != nullptr)
	{
		IreneData.Strength = table->ATTACK_DAMAGE_1;

		// 마나 사용 조건
		if (table->Main_Keyword != 0 && IreneData.CurrentMP >= table->MANA)
		{
			IreneAttack->bUseMP = true;
			IreneAttack->UseMP = table->MANA;
			IreneData.CurrentMP -= table->MANA;
		}
		// 마나 회복 조건
		else
		{
			IreneAttack->bUseMP = false;
			IreneAttack->UseMP = table->MANA;
		}
		if (table->Main_Keyword != 0 && IreneData.CurrentMP < table->MANA)
		{
			IreneAttack->bUseMP = false;
			IreneAttack->UseMP = 0;
		}

		IreneUIManager->OnMpChanged.Broadcast();
	}

	// if (TargetMonster != nullptr)
	// {
	// 	// 타겟이 캐릭터의 뒤에 있다면 추적 취소
	// 	FVector targetData = TargetMonster->GetActorLocation() - GetActorLocation();
	// 	targetData.Normalize();
	// 	if (FVector::DotProduct(GetActorForwardVector(), targetData) < 0)
	// 	{
	// 		TargetMonster = nullptr;
	// 	}
	// }

	float far = 300;
	// 가로, 높이, 세로
	FVector BoxSize = FVector(200, 50, far);
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
				// 새로운 오브젝트 충돌체 프로필 이름
				FName RayCollisionProfileName = RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
				FName EnemyProfile = "Enemy";
				FName ObjectProfile = "Object";

				// 맞췄을 때 캡슐컴포넌트를 가지고 카메라에 렌더링 되며 정상적으로 살아있는 몬스터 또는 오브젝트 찾기
				if (RayHit.Actor.IsValid() &&
					(RayCollisionProfileName == EnemyProfile || RayCollisionProfileName == ObjectProfile)
					&& RayHit.GetActor()->WasRecentlyRendered())
				{
					FName TargetCollisionProfileName;

					// 첫 몬스터 할당
					if (IreneAttack->TargetMonster == nullptr)
					{
						IreneAttack->TargetMonster = RayHit.GetActor();
						NearPosition = FindNearTarget;
					}

					TargetCollisionProfileName = IreneAttack->TargetMonster->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
					if (IreneUIManager->bShowLog)
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
								if (IreneAttack->TargetMonster == nullptr)
									IreneAttack->TargetMonster = RayHit.GetActor();
							}
							else if (TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == EnemyProfile)
							{
								NearPosition = FindNearTarget;
								if (IreneAttack->TargetMonster == nullptr)
									IreneAttack->TargetMonster = RayHit.GetActor();
							}
							else if (TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == ObjectProfile)
							{
								NearPosition = FindNearTarget;
								if (IreneAttack->TargetMonster == nullptr)
									IreneAttack->TargetMonster = RayHit.GetActor();
							}
						}
						else
						{
							NearPosition = FindNearTarget;
							if (IreneAttack->TargetMonster == nullptr)
								IreneAttack->TargetMonster = RayHit.GetActor();
						}
					}
				}
			}
		}
	}

	// 몬스터를 찾고 쳐다보기
	if (IreneAttack->TargetMonster != nullptr)
	{
		if(GetAnimName() == FName("B_Attack_1") || IreneInput->bUseRightButton)
		{
			//UE_LOG(LogTemp, Error, TEXT("Target Name: %s, Dist: %f"), *TargetMonster->GetName(), FVector::Dist(GetActorLocation(), TargetMonster->GetActorLocation()));
			float z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), IreneAttack->TargetMonster->GetActorLocation()).Yaw;
			GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, z, 0.0f));
			
			IreneAttack->bFollowCameraTarget = true;
			IreneAttack->CameraRot = WorldController->GetControlRotation();
			FRotator ForwardRotator = GetActorForwardVector().Rotation();
			//WorldController->SetControlRotation(FRotator(ForwardRotator.Pitch + WorldController->GetControlRotation().Pitch, ForwardRotator.Yaw, ForwardRotator.Roll));
			IreneAttack->TargetCameraRot = FRotator(ForwardRotator.Pitch + WorldController->GetControlRotation().Pitch, ForwardRotator.Yaw, ForwardRotator.Roll);
			
			// 몬스터가 공격범위 보다 멀리 있다면
			float TargetPos = FVector::Dist(GetActorLocation(), IreneAttack->TargetMonster->GetActorLocation()) - IreneData.AttackRange;
			if (TargetPos > IreneData.AttackRange)
			{
				// 추적 세팅
				IreneAttack->bFollowTarget = true;
				IreneAttack->PlayerPosVec = GetActorLocation();
				IreneAttack->TargetPosVec = GetActorLocation() + GetActorForwardVector() * (TargetPos);
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
	const float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (IreneData.CurrentHP > 0)
	{
		IreneData.CurrentHP -= DamageAmount - IreneData.Defenses;
		//hp 바
		IreneUIManager->OnHpChanged.Broadcast();
		IreneUIManager->HPRecoveryWaitCancel();
		if(HpRecoveryData.bIsRecovering) IreneUIManager->HpRecoveringCancel();			
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
	}
}

void AIreneCharacter::ActionEndChangeMoveState()
{
	IreneData.MoveSpeed = 1.0f;
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
			switch (IreneAttack->Attribute)
			{
			case EAttributeKeyword::e_None:
				break;
			case EAttributeKeyword::e_Fire:
				IreneUIManager->AttackSound->SetParameter("Attributes", 1.0f);
				break;
			case EAttributeKeyword::e_Water:
				IreneUIManager->AttackSound->SetParameter("Attributes", 2.0f);
				break;
			case EAttributeKeyword::e_Thunder:
				IreneUIManager->AttackSound->SetParameter("Attributes", 3.0f);
				break;
			default:
				break;
			}
			return FName("B_Attack_4");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && IreneAttack->Attribute == EAttributeKeyword::e_None)
		{
			return FName("B_Attack_5_N");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && IreneAttack->Attribute == EAttributeKeyword::e_Fire)
		{
			return FName("B_Attack_5_F");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && IreneAttack->Attribute == EAttributeKeyword::e_Water)
		{
			return FName("B_Attack_5_W");
		}
		if (IreneAnim->Montage_GetCurrentSection(IreneAnim->GetCurrentActiveMontage()) == FName("Attack5") && IreneAttack->Attribute == EAttributeKeyword::e_Thunder)
		{
			return FName("B_Attack_5_E");
		}
	}
	if (IreneInput->bUseRightButton)
	{
		if (IreneAttack->Attribute == EAttributeKeyword::e_Fire)
		{
			return FName("ActionKeyword_1_F");
		}
		if (IreneAttack->Attribute == EAttributeKeyword::e_Water)
		{
			return FName("ActionKeyword_1_W");
		}
		if (IreneAttack->Attribute == EAttributeKeyword::e_Thunder)
		{
			return FName("ActionKeyword_1_E");
		}
	}
	return FName("");
}
#pragma endregion State

#pragma region StopWatch
//스탑워치 컨트롤 함수
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
