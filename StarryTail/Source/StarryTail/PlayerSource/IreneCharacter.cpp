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
#include "WaterBasicAttack.h"
#include "Curves/CurveVector.h"

#pragma region Setting
// Sets default values
AIreneCharacter::AIreneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레톤 메쉬 설정
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Animation/Irene/Idle.Idle"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -80), FRotator(0, 270, 0));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
		GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
		GetCapsuleComponent()->SetGenerateOverlapEvents(true);
		//무기
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

		// 블루프린트 애니메이션 적용
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Animation/Irene/Animation/BP/BP_IreneAnimation.BP_IreneAnimation_C"));

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

	// 컨트롤러 받아오기
	WorldController = GetWorld()->GetFirstPlayerController();
	Weapon->SetSkeletalMesh(WeaponMeshArray[1]);
	Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketNameArray[1]);
	
	//김재섭
	 STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (nullptr == STGameInstance)
	{
		STARRYLOG(Error, TEXT("GameInstance is Not STGameInstance"));
	}
	else
	{
		STGameInstance->SetPlayer(this);
	}

	//스탑워치 생성 
	//StopWatch = GetWorld()->SpawnActor<AStopWatch>(FVector::ZeroVector, FRotator::ZeroRotator);
	//StopWatch->InitStopWatch();

	// 애니메이션 속성 초기화
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
					IreneAnim->NextToAttackMontageSection(IreneData.CurrentCombo);
				if (IreneInput->bUseRightButton)
					IreneAnim->NextToEffectAttackMontageSection(IreneData.CurrentCombo);
			}
		});
	IreneAnim->OnAttackHitCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackCheck);
	IreneAnim->OnAttackStopCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackStopCheck);
	IreneAnim->OnFootStep.AddUObject(IreneUIManager, &UIreneUIManager::FootStepSound);
	IreneAnim->OnRadialBlur.AddUObject(this, &AIreneCharacter::OnRadialBlur);
}

void AIreneCharacter::TargetReset()const
{
	if (IreneAttack->TargetMonster != nullptr)
	{
		// 타겟몹이 죽거나 거리가 멀어지면 초기화
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
	//DoCameraLagCurve(DeltaTime);
	TargetReset();
	IreneInput->RightButton(DeltaTime);
	IreneInput->RecoveryStaminaGauge(DeltaTime);
	IreneState->Update(DeltaTime);
	//STARRYLOG(Error,TEXT("%s"),*IreneState->GetStateToString());
}

// Called to bind functionality to input
void AIreneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 움직임 관련 키보드 입력
	PlayerInputComponent->BindAction("Jump", IE_Pressed, IreneInput, &UIreneInputInstance::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, IreneInput, &UIreneInputInstance::StopJump);

	PlayerInputComponent->BindAction("MoveW", IE_Pressed, IreneInput, &UIreneInputInstance::MovePressedW).bExecuteWhenPaused=true;
	PlayerInputComponent->BindAction("MoveA", IE_Pressed, IreneInput, &UIreneInputInstance::MovePressedA).bExecuteWhenPaused=true;
	PlayerInputComponent->BindAction("MoveS", IE_Pressed, IreneInput, &UIreneInputInstance::MovePressedS).bExecuteWhenPaused=true;
	PlayerInputComponent->BindAction("MoveD", IE_Pressed, IreneInput, &UIreneInputInstance::MovePressedD).bExecuteWhenPaused=true;
	PlayerInputComponent->BindAction("MoveW", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedW).bExecuteWhenPaused=true;
	PlayerInputComponent->BindAction("MoveA", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedA).bExecuteWhenPaused=true;
	PlayerInputComponent->BindAction("MoveS", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedS).bExecuteWhenPaused=true;
	PlayerInputComponent->BindAction("MoveD", IE_Released, IreneInput, &UIreneInputInstance::MoveReleasedD).bExecuteWhenPaused=true;

	// 움직임 외 키보드 입력
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, IreneInput, &UIreneInputInstance::DodgeKeyword);
	PlayerInputComponent->BindAxis("WaterDodge", IreneInput, &UIreneInputInstance::WaterDodgeKeyword);
	PlayerInputComponent->BindAction("MouseCursor", IE_Pressed, IreneInput, &UIreneInputInstance::MouseCursorKeyword);
	PlayerInputComponent->BindAction("FireKeyword", IE_Released, IreneInput, &UIreneInputInstance::FireKeywordReleased);
	PlayerInputComponent->BindAction("WaterKeyword", IE_Released, IreneInput, &UIreneInputInstance::WaterKeywordReleased);
	PlayerInputComponent->BindAction("ElectricKeyword", IE_Released, IreneInput, &UIreneInputInstance::ElectricKeywordReleased);
	
	// 마우스
	PlayerInputComponent->BindAxis("Turn", IreneInput, &UIreneInputInstance::Turn);
	PlayerInputComponent->BindAxis("LookUp", IreneInput, &UIreneInputInstance::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", IreneInput, &UIreneInputInstance::LeftButton);
	PlayerInputComponent->BindAction("RightButton", IE_Pressed, IreneInput, &UIreneInputInstance::RightButtonPressed);
	PlayerInputComponent->BindAction("RightButton", IE_Released, IreneInput, &UIreneInputInstance::RightButtonReleased);
	PlayerInputComponent->BindAxis("MouseWheel", IreneInput, &UIreneInputInstance::MouseWheel);

	// 그 외
	PlayerInputComponent->BindAction("Pause", IE_Pressed, IreneInput, &UIreneInputInstance::PauseWidgetOn);
	PlayerInputComponent->BindAction("Action", IE_Pressed, IreneInput, &UIreneInputInstance::DialogAction);
	//박찬영
	//스탑워치 컨트롤
	/*PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchControl);
	PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);*/
}

#pragma region Collision
void AIreneCharacter::FindNearMonster()
{
	if(IreneAttack->TargetMonster!=nullptr && IreneState->IsFirstAttack())
	{
		// 기존 타겟팅 취소
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
		// 공격력 계산
		IreneData.Strength = Table->ATTACK_DAMAGE_1;
	}

	// 몹 추적 박스 크기
	float Far = 300;
	if(IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		Far = 500;
	// 넓이, 높이, 거리
	const FVector BoxSize = FVector(300, 50, Far);

	// 리스트에 모든 충돌 결과 담는다.
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

	// 몬스터를 찾고 쳐다보기
	if (IreneAttack->TargetMonster != nullptr)
	{		
		if(IreneState->IsFirstAttack() || IreneInput->bUseRightButton)
		{
			const auto Mon=Cast<AMonster>(IreneAttack->TargetMonster);
			Mon->MarkerOn();
			const float Z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), IreneAttack->TargetMonster->GetActorLocation()).Yaw;
			GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, Z, 0.0f));

			// 다가가야하는 거리 계산
			const auto CharacterRadius = GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorScale().X;
			const auto MonsterRadius = Mon->GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorScale().X;			
			const float TargetPos = FVector::Dist(GetActorLocation(), Mon->GetLocation());

			// 몬스터가 공격범위 보다 멀리 있다면
			if (TargetPos - (CharacterRadius + MonsterRadius) > IreneData.AttackRange && IreneAttack->GetAttribute() != EAttributeKeyword::e_Water)
			{
				// 추적 세팅
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
	// 최대거리
	float NearPosition = Far;
	
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
				const FName RayCollisionProfileName = RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
				const FName EnemyProfile = "Enemy";
				const FName ObjectProfile = "Object";

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
						IreneAnim->SetTargetMonster(RayHit.GetActor());
						IreneAnim->SetIsHaveTargetMonster(true);
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
		IreneAnim->SetTargetMonster(RayHit.GetActor());
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
			// FindNearMonster() 이후 다가갈 때 충돌하면 멈추고 공격
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

	//STARRYLOG(Error,TEXT("%s"),*Other->GetName());
	if(IreneAttack->GetFollowTarget())
	{
		if(Cast<AMonster>(Other))
		{
			// FindNearMonster() 이후 다가갈 때 충돌하면 멈추고 공격
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
			}
			else
			{
				if(!IreneState->IsChargeState())
					ChangeStateAndLog(UHit1State::GetInstance());
			}
		}
		if (IreneAttack->TargetMonster == nullptr)
		{
			// 공격한 몬스터를 타겟 몬스터로 지정
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
	IreneState->ChangeState(NewState);
	//STARRYLOG(Error,TEXT("%s"), *IreneState->GetStateToString());
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
void AIreneCharacter::OnRadialBlur()
{
	bIsRadialBlurOn = true;
}
void AIreneCharacter::LastAttackCameraShake(const float DeltaTime)
{
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
#pragma endregion HitFeel

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
