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
#include "../StarryTailGameMode.h"
#include "IreneUIManager.h"
#include "IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneAttackInstance.h"
#include "IreneInputInstance.h"
#include ".././EnemySource/Scientia/Feather.h"
#include ".././EnemySource/Scientia/Piece.h"
#include "Curves/CurveVector.h"
#include "../EnemySource/Bouldelith/Bouldelith.h"
#include "../EnemySource/Morbit/Morbit.h"

#pragma region Setting
AIreneCharacter::AIreneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 콜라이더 설정
	GetCapsuleComponent()->InitCapsuleSize(25.0f, 80.0f);

	// 쉴드 설정
	ShieldComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Shield(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if(SM_Shield.Succeeded())
	{
		ShieldComp->SetStaticMesh(SM_Shield.Object);
	}
	const ConstructorHelpers::FObjectFinder<UMaterial>MT_Shield(TEXT("/Game/Model/Irene/Material/MT_Shield.MT_Shield"));
	if(MT_Shield.Succeeded())
	{
		ShieldComp->SetMaterial(0,MT_Shield.Object);
	}
	ShieldComp->SetupAttachment(GetCapsuleComponent());
	ShieldComp->SetCollisionProfileName(TEXT("NoCollision"));
	ShieldComp->SetGenerateOverlapEvents(false);
	ShieldComp->SetVisibility(false);
	
	// 카메라 설정
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComp->TargetArmLength = IreneData.FollowCameraZPosition;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 53));
	SpringArmComp->CameraLagSpeed = 0.0f;
	SpringArmComp->SetupAttachment(GetCapsuleComponent());

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->FieldOfView = IreneData.FieldOfView;

	// 스켈레톤 메쉬 설정
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Animation/Irene/Idle.Idle"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -80), FRotator(0, 270, 0));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
		GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
		GetCapsuleComponent()->SetGenerateOverlapEvents(true);
		// 무기
		if (GetMesh()->DoesSocketExist(TEXT("hand_rSwordSocket")))
		{
			Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Sword(TEXT("/Game/Animation/Irene/Weapon/Sword.Sword"));

			if (SK_Sword.Succeeded())
				WeaponMesh=SK_Sword.Object;

			Weapon->SetSkeletalMesh(WeaponMesh);
			Weapon->SetupAttachment(GetMesh(), TEXT("hand_rSwordSocket"));
			Weapon->SetCollisionProfileName(TEXT("PlayerAttack"));
			Weapon->SetGenerateOverlapEvents(false);
			Weapon->SetVisibility(false);
		}
		
		// 블루프린트 애니메이션 적용
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Animation/Irene/Animation/BP/BP_IreneAnimation.BP_IreneAnimation_C"));

		if (CharacterAnimInstance.Succeeded())
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
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
	
	// 카메라 회전과 캐릭터 회전 연동 안되도록 설정
	bUseControllerRotationYaw = false;
	SpringArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1050.0f, 0.0f);

	// 기본 최대 이동속도
	GetCharacterMovement()->MaxWalkSpeed = IreneData.RunMaxSpeed;

	// 플레이어 스폰 시 기본 제어 설정
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// PlayerCharacterDataStruct.h의 변수들 초기화
	IreneData.CurrentHP = IreneData.MaxHP;
	
	// IreneCharacter.h의 변수 초기화
	HpRecoveryData.bIsRecovering = false;
	HpRecoveryData.Amount = 300;
	HpRecoveryData.HP_Re_Time = 4;
	HpRecoveryData.Speed = 5;
	HpRecoveryData.Time = 10;
	WorldController = nullptr;
	CameraShakeOn = false;
	bIsRadialBlurOn = false;
}

void AIreneCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 컨트롤러 받아오기
	WorldController = GetWorld()->GetFirstPlayerController();
	
	STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (STGameInstance != nullptr)
		STGameInstance->SetPlayer(this);

	// 스탑워치 생성 
	//StopWatch = GetWorld()->SpawnActor<AStopWatch>(FVector::ZeroVector, FRotator::ZeroRotator);
	//StopWatch->InitStopWatch();

	// 애니메이션 속성 초기화
	IreneAnim->SetAttribute(IreneAttack->GetSwordAttribute());
	
	IreneUIManager->Begin();
	IreneInput->Begin();
	
	FOnSwordAttributeChange.Broadcast();

	InitComplete();
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
	
	IreneAnim->OnNextAttackCheck.AddLambda([this]()->void
		{
			if (IreneData.IsComboInputOn)
			{
				IreneAttack->AttackStartComboState();
				IreneAnim->NextToAttackMontageSection(IreneData.CurrentCombo);
			}
		});
	IreneAnim->OnAttackHitCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackCheck);
	IreneAnim->OnAttackStopCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackStopCheck);
	IreneAnim->OnFootStep.AddUObject(IreneUIManager, &UIreneUIManager::FootStepSound);
	IreneAnim->OnRadialBlur.AddUObject(this, &AIreneCharacter::OnRadialBlur);
}

void AIreneCharacter::TargetReset()const
{
	// 타겟을 조건에 따라 초기화하는 함수
	if (IreneAttack->SwordTargetMonster != nullptr)
	{
		// 타겟몹이 죽거나 렌더링이 안거나 거리가 멀어지면 초기화
		const auto Mob = Cast<AMonster>(IreneAttack->SwordTargetMonster);
		if (Mob != nullptr)
		{
			if (Mob->GetHp() <= 0 || !IreneAttack->SwordTargetMonster->WasRecentlyRendered() || FVector::Dist(GetActorLocation(), IreneAttack->SwordTargetMonster->GetActorLocation()) > 700.0f)
			{
				const auto Mon=Cast<AMonster>(IreneAttack->SwordTargetMonster);
				Mon->MarkerOff();
				IreneAnim->SetIsHaveTargetMonster(false);
				IreneAnim->SetTargetMonster(nullptr);
				IreneAttack->SwordTargetMonster = nullptr;				
			}			
		}
	}
	if (IreneAttack->QuillTargetMonster != nullptr)
	{
		// 타겟몹이 죽거나 렌더링이 안거나 거리가 멀어지면 초기화
		const auto Mob = Cast<AMonster>(IreneAttack->QuillTargetMonster);
		if (Mob != nullptr)
		{
			if (Mob->GetHp() <= 0 || !IreneAttack->QuillTargetMonster->WasRecentlyRendered() || FVector::Dist(GetActorLocation(), IreneAttack->QuillTargetMonster->GetActorLocation()) > 1000.0f)
			{
				const auto Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
				Mon->TargetWidgetOff();
				IreneAttack->QuillTargetMonster = nullptr;
			}			
		}
	}
}
#pragma endregion Setting

void AIreneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LastAttackCameraShake(DeltaTime);
	//DoCameraLagCurve(DeltaTime);
	TargetReset();
	FindCanThrowQuillMonster(DeltaTime);	
	IreneState->Update(DeltaTime);
}

void AIreneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 움직임 관련 키보드 입력
	PlayerInputComponent->BindAxis("MoveW", IreneInput, &UIreneInputInstance::MoveW).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("MoveA", IreneInput, &UIreneInputInstance::MoveA).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("MoveS", IreneInput, &UIreneInputInstance::MoveS).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("MoveD", IreneInput, &UIreneInputInstance::MoveD).bExecuteWhenPaused = true;
	
	// 움직임 외 키보드 입력
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, IreneInput, &UIreneInputInstance::DodgeKeyword);
	PlayerInputComponent->BindAction("MouseCursor", IE_Pressed, IreneInput, &UIreneInputInstance::MouseCursorKeyword);
	PlayerInputComponent->BindAction("FireKeyword", IE_Released, IreneInput, &UIreneInputInstance::FireKeywordReleased);
	PlayerInputComponent->BindAction("WaterKeyword", IE_Released, IreneInput, &UIreneInputInstance::WaterKeywordReleased);
	PlayerInputComponent->BindAction("ElectricKeyword", IE_Released, IreneInput, &UIreneInputInstance::ElectricKeywordReleased);
	PlayerInputComponent->BindAction("QuillAttributeChange", IE_Released, IreneInput, &UIreneInputInstance::QuillAttributeChangeReleased);

	// 마우스
	PlayerInputComponent->BindAxis("Turn", IreneInput, &UIreneInputInstance::Turn);
	PlayerInputComponent->BindAxis("LookUp", IreneInput, &UIreneInputInstance::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", IreneInput, &UIreneInputInstance::LeftButton);
	PlayerInputComponent->BindAction("RightButton", IE_Pressed, IreneInput, &UIreneInputInstance::RightButtonPressed);
	PlayerInputComponent->BindAxis("MouseWheel", IreneInput, &UIreneInputInstance::MouseWheel);
	
	// 그 외
	PlayerInputComponent->BindAction("Pause", IE_Pressed, IreneInput, &UIreneInputInstance::PauseWidgetOn).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Action", IE_Pressed, IreneInput, &UIreneInputInstance::DialogAction);
	PlayerInputComponent->BindAction("DialogSkip", IE_Pressed, IreneInput, &UIreneInputInstance::DialogSkip);

	// 스탑워치 컨트롤
	//PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchControl);
	//PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);
}

#pragma region Collision
void AIreneCharacter::FindNearMonster()
{
	// 가장 가까운 몬스터를 찾고 공격범위 보다 멀면 다가가게 하고 공격하는 함수	
	if(IreneAttack->SwordTargetMonster!=nullptr && IreneState->IsFirstAttack())
	{
		// 기존 타겟팅 취소
		const auto Mon=Cast<AMonster>(IreneAttack->SwordTargetMonster);
		Mon->MarkerOff();		
		IreneAnim->SetIsHaveTargetMonster(false);
		IreneAttack->SwordTargetMonster = nullptr;
	}

	// 몹 추적 박스 넓이, 높이, 거리
	// 플레이어 위치를 기반으로 박스를 만들어서 몬스터들을 탐지하는 방법
	//const FVector BoxSize = FVector(200, 50, 150);
	//auto HitMonsterList = IreneAttack->StartPositionFindNearMonster(BoxSize,GetActorLocation(),GetActorForwardVector());

	// 카메라 위치를 기반으로 박스를 만들어서 몬스터들을 탐지하는 방법	
	auto AllPosition = SetCameraStartTargetPosition(FVector(200,200,500),CameraComp->GetComponentLocation());
	auto HitMonsterList = StartPositionFindNearMonster(AllPosition.Get<0>(),AllPosition.Get<1>(),AllPosition.Get<2>());	
	NearMonsterAnalysis(HitMonsterList.Get<0>(), HitMonsterList.Get<1>(), HitMonsterList.Get<2>(), AllPosition.Get<0>().Z, false);
	
	IreneAttack->DoAttack();
}
TTuple<FVector, FVector, FVector> AIreneCharacter::SetCameraStartTargetPosition(const FVector BoxSize, const FVector StartPosition) const
{
	const int BoxFarSize = BoxSize.Z;
	FVector Length = GetControlRotation().Quaternion() * FVector::ForwardVector;
	Length.Normalize();
	const FVector TargetPos = GetActorLocation()+(Length) * BoxFarSize;	
	const FVector CameraPos = StartPosition;
	const FVector ReturnBoxSize = FVector(BoxSize.X, BoxSize.Y, FVector::Dist(TargetPos,CameraPos)/2);
	return MakeTuple(ReturnBoxSize, CameraPos, TargetPos);
}

TTuple<TArray<FHitResult>, FCollisionQueryParams, bool> AIreneCharacter::StartPositionFindNearMonster(const FVector BoxSize, const FVector StartPosition, const FVector TargetPosition, const float LifeTime)const
{
	const FVector Center = (TargetPosition + StartPosition) /2;

	// 리스트에 모든 충돌 결과 담는다.
	TArray<FHitResult> MonsterList;
	const FCollisionQueryParams Params(NAME_None, false, this);
	const bool bResult = GetWorld()->SweepMultiByChannel(
		MonsterList,
		Center,
		Center,
		FRotationMatrix::MakeFromZ(CameraComp->GetForwardVector()).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel8,
		FCollisionShape::MakeBox(BoxSize),
		Params);

#if ENABLE_DRAW_DEBUG
	const FVector TraceVec = CameraComp->GetForwardVector();
	const FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	const FColor DrawColor = bResult ? FColor::Magenta : FColor::Blue;
	const float DebugLifeTime = LifeTime;
	DrawDebugBox(GetWorld(), Center, BoxSize, CapsuleRot, DrawColor, false, DebugLifeTime*2);
#endif
	
	return MakeTuple(MonsterList, Params, bResult);
}
void AIreneCharacter::NearMonsterAnalysis(const TArray<FHitResult> MonsterList, const FCollisionQueryParams Params, const bool bResult, const float Far, const bool QuillTarget)const
{
	// 여러 충돌체 중 가장 가까운 충돌체 하나를 리턴하는 함수
	// 최대거리
	float CurNearPosition = Far;
	FName TargetCollisionProfileName;

	for (FHitResult Monster : MonsterList)
	{
		if (bResult)
		{
			//STARRYLOG(Warning,TEXT("%s"), *Monster.GetActor()->GetName());
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
				// 캐릭터와 타겟 사이 최소거리 찾기
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
					if(!QuillTarget)
					{
						// 첫 몬스터 할당
						if (IreneAttack->SwordTargetMonster == nullptr)
						{
							IreneAttack->SwordTargetMonster = RayHit.GetActor();
							IreneAnim->SetTargetMonster(RayHit.GetActor());
							IreneAnim->SetIsHaveTargetMonster(true);
							CurNearPosition = FindNearTarget;							
						}
						TargetCollisionProfileName = IreneAttack->SwordTargetMonster->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
					}
					else
					{
						// 첫 몬스터 할당
						if (IreneAttack->QuillTargetMonster == nullptr)
						{
							IreneAttack->QuillTargetMonster = RayHit.GetActor();
							CurNearPosition = FindNearTarget;
						}
						TargetCollisionProfileName = IreneAttack->QuillTargetMonster->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
						//STARRYLOG(Warning, TEXT("Name: %s, Dist: %f"), *RayHit.GetActor()->GetName(), FindNearTarget);
					}

					// 몬스터 또는 오브젝트와 플레이어간 거리가 가장 작은 액터를 찾는다.
					if (CurNearPosition >= FindNearTarget)
					{
						// 만약 최단거리가 같은 액터가 있다면
						if (CurNearPosition == FindNearTarget)
						{
							if ((TargetCollisionProfileName == EnemyProfile && RayCollisionProfileName == EnemyProfile)||
								(TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == EnemyProfile)||
								(TargetCollisionProfileName == ObjectProfile && RayCollisionProfileName == ObjectProfile))
							{
								if(!QuillTarget)
									SetAttackNearMonster(RayHit,CurNearPosition,FindNearTarget);
								else
									SetQuillNearMonster(RayHit,CurNearPosition,FindNearTarget);
							}
							else
							{
								if(!QuillTarget)
									SetAttackNearMonster(RayHit,CurNearPosition,FindNearTarget);
								else
									SetQuillNearMonster(RayHit,CurNearPosition,FindNearTarget);
							}
						}
						else
						{
							if(!QuillTarget)
								SetAttackNearMonster(RayHit,CurNearPosition,FindNearTarget);
							else
							{
								const auto Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
								Mon->TargetWidgetOff();
								IreneAttack->QuillTargetMonster = nullptr;
								SetQuillNearMonster(RayHit,CurNearPosition,FindNearTarget);
							}
						}
					}
				}
			}
		}
	}
}

void AIreneCharacter::SetAttackNearMonster(const FHitResult RayHit, float& NearPosition, const float FindNearTarget)const
{
	// 가장 가까운 몬스터를 타겟 몬스터로 지정하는 함수
	if (IreneAttack->SwordTargetMonster == RayHit.GetActor())
	{
		NearPosition = FindNearTarget;
		IreneAttack->SwordTargetMonster = RayHit.GetActor();
		IreneAnim->SetTargetMonster(RayHit.GetActor());
		IreneAnim->SetIsHaveTargetMonster(true);

		auto Mon=Cast<AMonster>(IreneAttack->SwordTargetMonster);
		Mon->MarkerOn();
		// 기존 깃펜 타겟UI 끄고 검 공격 타겟에게 깃펜 타겟UI 보여주기
		// Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
		// Mon->TargetWidgetOff();
		// IreneAttack->QuillTargetMonster = RayHit.GetActor();
		// Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
		// Mon->TargetWidgetOn();
		
		// 몬스터를 찾고 쳐다보기
		//const float Z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), IreneAttack->SwordTargetMonster->GetActorLocation()).Yaw;
		//GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, Z, 0.0f));
	}
}
void AIreneCharacter::SetQuillNearMonster(const FHitResult RayHit, float& NearPosition, const float FindNearTarget)const
{
	// 가장 가까운 몬스터를 타겟 몬스터로 지정하는 함수
	NearPosition = FindNearTarget;
	IreneAttack->QuillTargetMonster = RayHit.GetActor();
	// 깃펜 UI 표시하기
	const auto Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
	Mon->TargetWidgetOn();
}

void AIreneCharacter::FindCanThrowQuillMonster(const float DeltaTime)const
{
	// 매 프레임 가장 가까운 몬스터를 깃펜 타겟 몬스터로 지정하는 함수
	auto AllPosition = SetCameraStartTargetPosition(FVector(400,200,700),CameraComp->GetComponentLocation());
	auto HitMonsterList = StartPositionFindNearMonster(AllPosition.Get<0>(),AllPosition.Get<1>(),AllPosition.Get<2>(),DeltaTime);	
	NearMonsterAnalysis(HitMonsterList.Get<0>(), HitMonsterList.Get<1>(), HitMonsterList.Get<2>(), AllPosition.Get<0>().Z, true);
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

	if(!IreneData.IsInvincibility || !IreneData.IsSkipMonsterAttack)
	{
		if (IreneData.CurrentHP > 0)
		{
			SetHP(DamageAmount);
			
			if (IreneData.CurrentHP <= 0)
			{
				ChangeStateAndLog(UDeathState::GetInstance());
				LevelRestartEvent();
			}
			else
			{
				const auto Monster = Cast<AMonster>(DamageCauser);
				if(Monster)
				{
					switch (Monster->GetAttribute())
					{
					case EAttributeKeyword::e_Fire:
						IreneAttack->SetFireDeBuffStack(IreneAttack->GetFireDeBuffStack()+1, DamageAmount);
						break;
					case EAttributeKeyword::e_Water:
						IreneAttack->SetWaterDeBuffStack(IreneAttack->GetWaterDeBuffStack()+1);
						break;
					case EAttributeKeyword::e_Thunder:
						IreneAttack->SetThunderDeBuffStack(IreneAttack->GetThunderDeBuffStack()+1);
						break;
					case EAttributeKeyword::e_None:
						break;
					}
				}

				if(!IreneState->IsAttackState() && !IreneState->IsJumpState())
				{
					ChangeStateAndLog(UHit2State::GetInstance());
				}
			}
		}
		if (IreneAttack->SwordTargetMonster == nullptr)
		{
			if (Cast<AFeather>(DamageCauser))
				return FinalDamage;
			if (Cast<APiece>(DamageCauser))
				return FinalDamage;

			// 공격한 몬스터를 타겟 몬스터로 지정
			IreneAttack->SwordTargetMonster = DamageCauser;
			IreneAnim->SetTargetMonster(IreneAttack->SwordTargetMonster);
			IreneAnim->SetIsHaveTargetMonster(true);
			auto Mon=Cast<AMonster>(IreneAttack->SwordTargetMonster);
			Mon->MarkerOn();
			//Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
			//Mon->TargetWidgetOff();
			//IreneAttack->QuillTargetMonster = DamageCauser;
			//Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
			//Mon->TargetWidgetOn();
		}
	}
	return FinalDamage;
}
void AIreneCharacter::SetHP(float DamageAmount)
{
	if(IreneData.Shield > 0)
	{
		const float CurShield = IreneData.Shield;
		IreneData.Shield -= DamageAmount;
		if(IreneData.Shield <= 0)
		{
			IreneAttack->ResetWaterQuillStack();
		}
		DamageAmount -= CurShield;
		if(DamageAmount > 0)
			IreneData.CurrentHP -= DamageAmount;
	}
	else
	{
		IreneData.CurrentHP -= DamageAmount;
	}
	IreneUIManager->OnHpChanged.Broadcast();
}

#pragma endregion Collision

#pragma region State
void AIreneCharacter::ChangeStateAndLog(IState* NewState)const
{
	if(!IreneState->IsDeathState())
	{
		IreneState->ChangeState(NewState);
		//STARRYLOG(Error,TEXT("%s"), *IreneState->GetStateToString());
		IreneAnim->SetIreneStateAnim(IreneState->GetState());
	}
}

void AIreneCharacter::ActionEndChangeMoveState(bool RunToSprint)const
{
	// 현재 키 입력에 따라 상태를 전이하는 함수
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
	else if (GetCharacterMovement()->MaxWalkSpeed >= IreneData.SprintMaxSpeed)
	{
		ChangeStateAndLog(USprintLoopState::GetInstance());
	}
	else
	{
		if(RunToSprint)
			ChangeStateAndLog(USprintLoopState::GetInstance());
		else
			ChangeStateAndLog(URunLoopState::GetInstance());
	}
}
#pragma endregion State

#pragma region HitFeel
float AIreneCharacter::BattleCameraRotation(UPARAM(ref) float& Angle)
{
	const FVector IreneForward = GetCapsuleComponent()->GetForwardVector();
	const FVector CameraForward = -1.0f*(CameraComp->GetForwardVector());
	const FVector CameraUp = CameraComp->GetUpVector();

    FRotator Rot(0.0f, Angle,0.0f);

	const FVector IreneRight = Rot.RotateVector(IreneForward);
	Rot = FRotator(0.0f, -Angle, 0.0f);
	const FVector IreneLeft = Rot.RotateVector(IreneForward);	
	
	const float RightAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(CameraForward, IreneRight)));
	const float LeftAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(CameraForward, IreneLeft)));

	bool bIsLeftClose = false;

	if (LeftAngle <= RightAngle)bIsLeftClose = true;

	bool bIsLeftRotation = false;
	if (bIsLeftClose)
	{
		const FVector Cross = FVector::CrossProduct(CameraForward, IreneLeft);

		const float Dot = FVector::DotProduct(CameraUp, Cross);

		if (Dot > 0)bIsLeftRotation = true;
		else bIsLeftRotation = false;
	}
	else {
		const FVector Cross = FVector::CrossProduct(CameraForward, IreneRight);

		const float Dot = FVector::DotProduct(CameraUp, Cross);

		if (Dot > 0)bIsLeftRotation = true;
		else bIsLeftRotation = false;
	}

	if (bIsLeftClose)
	{
		if (bIsLeftRotation)
		{
			return (LeftAngle / 2.5f);
		}
		else {
			return (-1.0f* (LeftAngle / 2.5f));
		}

	}
	else {
		if (bIsLeftRotation)
		{
			return (RightAngle / 2.5f);
		}
		else {
			return (-1.0f * (RightAngle / 2.5f));
		}
	}
}
void AIreneCharacter::OnRadialBlur()
{
	bIsRadialBlurOn = true;
}
void AIreneCharacter::LastAttackCameraShake(const float DeltaTime)
{
	// 공격을 해서 몹과 충돌을 하면 함수가 실행되며 카메라 쉐이크를 하는 함수
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
void AIreneCharacter::PlayFadeInAnimation()
{
	IreneUIManager->PlayHUDAnimation();
}
void AIreneCharacter::SetIreneDialog()
{
	ChangeStateAndLog(UIdleState::GetInstance());
}
void AIreneCharacter::SetBattleCamera()
{
	IreneData.BattleCameraZPosition = IreneData.MaxBattleCameraZPosition;
}
void AIreneCharacter::SetRaidBattleCamera()
{
	IreneData.BattleCameraZPosition = IreneData.MaxRaidCameraZPosition;
}

void AIreneCharacter::SetFirstLevel(bool isFirst)
{
	IreneUIManager->PlayerHud->bIsFirstLevel = isFirst;
}

void AIreneCharacter::PlayFadeOutAnimation()
{
	PlayFadeOutEvent();
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
