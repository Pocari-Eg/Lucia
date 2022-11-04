#pragma once

#include "IreneCharacter.h"
#include "DrawDebugHelpers.h"
#include "../STGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "../StarryTailGameMode.h"
#include "PlayerInstance/IreneUIManager.h"
#include "PlayerFSM/IreneFSM.h"
#include "PlayerInstance/IreneAnimInstance.h"
#include "PlayerInstance/IreneAttackInstance.h"
#include "PlayerInstance/IreneInputInstance.h"
#include ".././EnemySource/MonsterProjectile.h"
#include "Curves/CurveVector.h"
#include "../EnemySource/Bouldelith/Bouldelith.h"
#include "../EnemySource/Morbit/Morbit.h"
#include "PlayerSpirit/IreneSpirit.h"
#include "PlayerSpirit/IreneSpiritAnimInstance.h"
#include "HeliosInstance/HeliosAnimInstance.h"
#include "../Object/ShieldSpirit.h"
#include "../Object/LabMagic.h"
#include "../EnemySource/Bellarus/Swirls/Swirl.h"

#pragma region Setting
AIreneCharacter::AIreneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 콜라이더 설정
	GetCapsuleComponent()->InitCapsuleSize(25.0f, 80.0f);
	
	// 카메라 설정
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComp->TargetArmLength = IreneData.FollowCameraZPosition;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 70));
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
		//GetMesh()->SetRelativeScale3D(FVector(8.5f,8.5f,8.5f));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
		GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
		GetCapsuleComponent()->SetGenerateOverlapEvents(true);
		
		// 무기
		if (GetMesh()->DoesSocketExist(TEXT("hand_rSwordSocket")))
		{
			Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Sword(TEXT("/Game/Animation/Irene/Weapon/Sword.Sword"));

			if (SK_Sword.Succeeded())
			{
				WeaponMesh = SK_Sword.Object;
			}
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
	// 잔상 원본 세팅
	ConstructorHelpers::FClassFinder<AIreneSpirit>BP_IreneSpirit(TEXT("/Game/BluePrint/Irene/IreneSpirit.IreneSpirit_C"));
	if(BP_IreneSpirit.Succeeded())
		IreneSpiritOrigin = BP_IreneSpirit.Class;

	// 궁극기 쉴드 이펙트
	ShieldParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShieldEffect"));
	ShieldParticleSystemComponent->SetupAttachment(GetMesh());
	const ConstructorHelpers::FObjectFinder<UParticleSystem>Shield(TEXT("/Game/Effect/VFX_Monster/Shield/Palyer/PS_Shield_Player.PS_Shield_Player"));
	if(Shield.Succeeded())
	{
		ShieldParticleSystemComponent->Template = Shield.Object;
		ShieldParticleSystemComponent->SetAutoActivate(false);
		ShieldParticleSystemComponent->Activate(false);
	}
	
	// 펫 세팅
	PetSpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("PetSprintArm"));
	PetSpringArmComp->TargetArmLength = 0;
	PetSpringArmComp->bEnableCameraLag = true;
	PetSpringArmComp->SetRelativeLocation(FVector(0, 45, 30));
	PetSpringArmComp->CameraLagSpeed = 3.0f;
	PetSpringArmComp->SetupAttachment(GetCapsuleComponent());

	PetMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PetMesh"));
	PetMesh->SetupAttachment(PetSpringArmComp);
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>PetStatic(TEXT("/Game/Animation/Irene/Helios/PC_s_idle.PC_s_idle"));
	if(PetStatic.Succeeded())
	{
		PetMesh->SetSkeletalMesh(PetStatic.Object);
		PetMesh->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 270, 0));

		// 블루프린트 애니메이션 적용
		PetMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>HeliosAnimInstance(TEXT("/Game/Animation/Irene/Helios/BP/BP_HeliosAnimation.BP_HeliosAnimation_C"));

		if (HeliosAnimInstance.Succeeded())
			PetMesh->SetAnimClass(HeliosAnimInstance.Class);
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
	
	// 스킬 카메라 움직임
	const ConstructorHelpers::FObjectFinder<UCurveVector>SkillCameraData(TEXT("/Game/Math/SkillCamera.SkillCamera"));
	if(SkillCameraData.Succeeded())
	{
		SkillCamera = SkillCameraData.Object;
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
	IreneData.CurrentShield = 0;
	IreneData.CurrentEnergy = 0;
	IreneData.CurrentGauge = 100;
	
	// IreneCharacter.h의 변수 초기화
	HpRecoveryData.bIsRecovering = false;
	HpRecoveryData.Amount = 300;
	HpRecoveryData.HP_Re_Time = 4;
	HpRecoveryData.Speed = 5;
	HpRecoveryData.Time = 10;
	WorldController = nullptr;
	CameraShakeOn = false;
	bIsRadialBlurOn = false;
	bInputStop = false;
	bIsSpiritStance = false;

	bIsKnockBack = false;

}

void AIreneCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Ingame 전투위젯 생성
	if (InGame_C != nullptr)
	{
		makeIngameWidget = CreateWidget<UUserWidget>(GetWorld(), InGame_C);
		makeIngameWidget->AddToViewport();
	}

	// 컨트롤러 받아오기
	WorldController = GetWorld()->GetFirstPlayerController();
	
	STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (STGameInstance != nullptr)
		STGameInstance->SetPlayer(this);

	// 스탑워치 생성 
	//StopWatch = GetWorld()->SpawnActor<AStopWatch>(FVector::ZeroVector, FRotator::ZeroRotator);
	//StopWatch->InitStopWatch();

	IreneUIManager->Begin();
	IreneInput->Begin();
	
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
	
	IreneSound= NewObject<UIreneSoundInstance>(this);
	IreneSound->Init(this);

	IreneUIManager = NewObject<UIreneUIManager>(this);
	IreneUIManager->Init(this);

	PetAnim = Cast<UHeliosAnimInstance>(PetMesh->GetAnimInstance());
	
	IreneAnim->OnAttackHitCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackCheck);
	IreneAnim->OnAttackStopCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackStopCheck);
	IreneAnim->OnFootStep.AddUObject(IreneSound, &UIreneSoundInstance::PlayWalkSound);
	IreneAnim->OnRadialBlur.AddUObject(this, &AIreneCharacter::OnRadialBlur);
}

void AIreneCharacter::TargetReset()const
{
	// 타겟을 조건에 따라 초기화하는 함수
	if (IreneAttack->SwordTargetMonster != nullptr && !IreneState->IsUltimateAttackState())
	{
		// 타겟몹이 죽거나 렌더링이 안거나 거리가 멀어지면 초기화
		const auto Mob = Cast<AMonster>(IreneAttack->SwordTargetMonster);
		if (Mob != nullptr)
		{
			if (Mob->GetHp() <= 0 || !IreneAttack->SwordTargetMonster->WasRecentlyRendered() || FVector::Dist(GetActorLocation(), IreneAttack->SwordTargetMonster->GetActorLocation()) > 1500.0f)
			{
				const auto Mon=Cast<AMonster>(IreneAttack->SwordTargetMonster);
				Mon->MarkerOff();
				IreneAnim->SetIsHaveTargetMonster(false);
				IreneAnim->SetTargetMonster(nullptr);
				IreneAttack->SwordTargetMonster = nullptr;
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
	IreneState->Update(DeltaTime);

	if(IreneInput->GetCameraStop())
	{
		SpringArmComp->CameraLagSpeed = 0.0001f;
	}

	if(bIsSpiritStance)
	{
		IreneData.CurrentGauge -= DeltaTime*(1/0.8f);
		if(IreneData.CurrentGauge <= 0)
		{
			IreneData.CurrentGauge = 0;
			IreneInput->SpiritChangeMaxTime();
		}
	}
	
	if (bIsKnockBack)
	{
		KnockBackTimer += DeltaTime;
		const FVector KnockBackLocation = GetActorLocation() + (KnockBackDir * (KnockBackPower * (0.15f - KnockBackTimer)));
		SetActorLocation(KnockBackLocation);

		if (KnockBackTimer > KnockBackTime)
		{
			KnockBackTimer = 0.0f;
			bIsKnockBack = false;
		}
	}	
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
	PlayerInputComponent->BindAction("WeaponChange", IE_Pressed, IreneInput, &UIreneInputInstance::SpiritChangeKeyword);
	PlayerInputComponent->BindAction("BreakAttack", IE_Pressed, IreneInput, &UIreneInputInstance::BreakAttackKeyword);
	PlayerInputComponent->BindAction("UltimateAttack", IE_Pressed, IreneInput, &UIreneInputInstance::UltimateAttackKeyword);

	// 마우스
	PlayerInputComponent->BindAxis("Turn", IreneInput, &UIreneInputInstance::Turn);
	PlayerInputComponent->BindAxis("LookUp", IreneInput, &UIreneInputInstance::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", IreneInput, &UIreneInputInstance::LeftButton);
	PlayerInputComponent->BindAxis("RightButton", IreneInput, &UIreneInputInstance::RightButton);
	PlayerInputComponent->BindAxis("MouseWheel", IreneInput, &UIreneInputInstance::MouseWheel);
	
	// 그 외
	PlayerInputComponent->BindAction("Pause", IE_Pressed, IreneInput, &UIreneInputInstance::PauseWidgetOn).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Action", IE_Pressed, IreneInput, &UIreneInputInstance::DialogAction);
	PlayerInputComponent->BindAction("DialogAction", IE_Pressed, IreneInput, &UIreneInputInstance::DialogPlaying);

	PlayerInputComponent->BindAction("DialogSkip", IE_Pressed, IreneInput, &UIreneInputInstance::DialogSkip);

	PlayerInputComponent->BindAction("TestSkillCamera", IE_Pressed, IreneInput, &UIreneInputInstance::SkillCameraMoveStart);

	// 스탑워치 컨트롤
	//PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchControl);
	//PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);
}

#pragma region Collision
void AIreneCharacter::FindNearMonster()const
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
	NearMonsterAnalysis(HitMonsterList.Get<0>(), HitMonsterList.Get<1>(), HitMonsterList.Get<2>(), AllPosition.Get<0>().Z);
	
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
	DrawDebugBox(GetWorld(), Center, BoxSize, CapsuleRot, DrawColor, false, 5.1f);
#endif
	
	return MakeTuple(MonsterList, Params, bResult);
}
void AIreneCharacter::NearMonsterAnalysis(const TArray<FHitResult> MonsterList, const FCollisionQueryParams Params, const bool bResult, const float Far,const bool UltimateAttack)const
{
	// 여러 충돌체 중 가장 가까운 충돌체 하나를 리턴하는 함수
	// 최대거리
	float CurNearPosition = Far;
	FName TargetCollisionProfileName;

	for (FHitResult Monster : MonsterList)
	{
		// 카메라와 캐릭터 사이의 몬스터는 제외
		if(FVector::Dist(CameraComp->GetComponentLocation(),Monster.GetActor()->GetActorLocation())<=FVector::Dist(CameraComp->GetComponentLocation(),GetActorLocation()))
		{
			continue;
		}
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
					//auto RayMonster = Cast<AMonster>(Monster.Actor);

					//if(GetActorLocation().Z - GetCapsuleComponent()->GetScaledCapsuleHalfHeight() < RayMonster->GetLocation().Z - 5 ||
					//	GetActorLocation().Z - GetCapsuleComponent()->GetScaledCapsuleHalfHeight() > RayMonster->GetLocation().Z + 5)
					//	continue;
					
					// 첫 몬스터 할당
					if (IreneAttack->SwordTargetMonster == nullptr)
					{
						IreneAttack->SwordTargetMonster = RayHit.GetActor();
						IreneAnim->SetTargetMonster(RayHit.GetActor());
						IreneAnim->SetIsHaveTargetMonster(true);
						CurNearPosition = FindNearTarget;		
					}
					TargetCollisionProfileName = IreneAttack->SwordTargetMonster->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();

					// 궁극기 처리
					if(UltimateAttack)
					{
						auto Mon=Cast<AMonster>(Monster.Actor);
						if(Mon != nullptr)
						{
							if(Mon->GetCurStackCount() == 6)
							{
								if(Mon->GetIsMonsterShieldActive())
									Mon->StackExplode();
								else
									UGameplayStatics::ApplyDamage(Monster.Actor.Get(),
										Mon->GetMonsterInfo().StackDamage + Mon->GetMonsterInfo().StackDamage * 0.2f,nullptr, STGameInstance->GetPlayer(), nullptr);
							}
							Mon->AddStackCount(6);
						}
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
								SetAttackNearMonster(RayHit,CurNearPosition,FindNearTarget);
							}
							else
							{
								SetAttackNearMonster(RayHit,CurNearPosition,FindNearTarget);
							}
						}
						else
						{
							SetAttackNearMonster(RayHit,CurNearPosition,FindNearTarget);							
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
		// Mon->StackWidgetOff();
		// IreneAttack->QuillTargetMonster = RayHit.GetActor();
		// Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
		// Mon->StackWidgetOn();
		
		// 몬스터를 찾고 쳐다보기
		//const float Z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), IreneAttack->SwordTargetMonster->GetActorLocation()).Yaw;
		//GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, Z, 0.0f));
	}
}

void AIreneCharacter::FollowTargetPosition()
{
	// 몬스터를 찾고 쳐다보기
	if (IreneAttack->PerfectDodgeMonster != nullptr)
	{
		// 몹을 따라가는 조건
		const auto Mon=Cast<AMonster>(IreneAttack->PerfectDodgeMonster);
		Mon->MarkerOn();
		const float Z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), IreneAttack->PerfectDodgeMonster->GetActorLocation()).Yaw;
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, Z, 0.0f));

		// 다가가야하는 거리 계산
		const auto CharacterRadius = GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorScale().X;
		const auto MonsterRadius = Mon->GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorScale().X;			
		const float TargetPos = FVector::Dist(GetActorLocation(), Mon->GetLocation());
		//CustomTimeDilation = 1.0f/0.4f;
		// 몬스터가 공격범위 보다 멀리 있다면
		if (TargetPos - (CharacterRadius + MonsterRadius) > IreneData.AttackRange)
		{
			// 추적 세팅
			IreneInput->SetStartMoveAutoTarget(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * TargetPos);
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
void AIreneCharacter::NotifyHit(UPrimitiveComponent *MyComp, AActor *Other, UPrimitiveComponent *OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult &Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
}

float AIreneCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(!IreneData.IsInvincibility || !IreneData.IsSkipMonsterAttack)
	{
		if (IreneData.CurrentHP > 0)
		{
			IreneData.CurrentShield	-= DamageAmount;
			if(IreneData.CurrentShield > 0)
			{
				DamageAmount = 0;
			}
			else
			{
				DamageAmount = -IreneData.CurrentShield;
				IreneData.CurrentShield = 0;
				ShieldParticleSystemComponent->Deactivate();
				PetAnim->SetShield(false);
			}
			
			SetHP(DamageAmount);
			IreneAttack->SetDamageBeforeTableName(IreneAttack->GetBasicAttackDataTableName().ToString());
			
			if (IreneData.CurrentHP <= 0)
			{
				IreneAnim->StopAllMontages(0);
				ChangeStateAndLog(UDeathState::GetInstance());
				LevelRestartEvent();
			}
			else
			{
				bool DotDamage = false;
				if(Cast<ASwirl>(DamageCauser) != nullptr)
					DotDamage = Cast<ASwirl>(DamageCauser)->GetbIsOnDotDamage();

				if(!IreneState->IsJumpState() && !Cast<ALabMagic>(DamageCauser)&& !DotDamage && !IreneState->IsUltimateAttackState())
				{
					IreneAnim->StopAllMontages(0);
					ChangeStateAndLog(UHit2State::GetInstance());
				}
			}
		}
		if (IreneAttack->SwordTargetMonster == nullptr)
		{
			if (Cast<AMonsterProjectile>(DamageCauser)|| Cast<ALabMagic>(DamageCauser)|| Cast<ASwirl>(DamageCauser))
				return FinalDamage;

			// 공격한 몬스터를 타겟 몬스터로 지정
			IreneAttack->SwordTargetMonster = DamageCauser;
			IreneAnim->SetTargetMonster(IreneAttack->SwordTargetMonster);
			IreneAnim->SetIsHaveTargetMonster(true);
			auto Mon=Cast<AMonster>(IreneAttack->SwordTargetMonster);
			Mon->MarkerOn();
			//Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
			//Mon->StackWidgetOff();
			//IreneAttack->QuillTargetMonster = DamageCauser;
			//Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
			//Mon->StackWidgetOn();
		}
	}
	return FinalDamage;
}
void AIreneCharacter::SetHP(float DamageAmount)
{	
	IreneData.CurrentHP -= DamageAmount;	
	IreneUIManager->OnHpChanged.Broadcast();
	if(IreneData.CurrentHP <= 0 && !IreneState->IsDeathState() && bIsSpiritStance)
	{
		ChangeStateAndLog(UDeathState::GetInstance());
		LevelRestartEvent();
	}
}

#pragma endregion Collision

#pragma region State
void AIreneCharacter::ChangeStateAndLog(IState* NewState)const
{
	if(!IreneState->IsDeathState())
	{
		IreneState->ChangeState(NewState);
		//STARRYLOG(Error,TEXT("%s:   %f"), *IreneState->GetStateToString(),GetWorld()->RealTimeSeconds);
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
	else if (GetCharacterMovement()->MaxWalkSpeed >= IreneData.SprintMaxSpeed * IreneData.WaterDeBuffSpeed)
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

#pragma region Battle
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
		}
	}
}
void AIreneCharacter::SetUseShakeCurve(UCurveVector* Curve)
{
	UseShakeCurve = Curve;
}

void AIreneCharacter::SetUseCameraLag(UCurveFloat* Curve)
{
	UseLagCurve = Curve;
}

void AIreneCharacter::PlayerKnockBack(FVector In_KnockBackDir, float In_KnockBackPower)
{
	if (!bIsKnockBack && !IreneSpirit)
	{
		KnockBackDir = In_KnockBackDir;
		KnockBackDir.Normalize();
		KnockBackDir.Z = 0.0f;

		KnockBackPower = In_KnockBackPower;
		KnockBackTime = 0.15f;
		KnockBackTimer = 0.0f;
		bIsKnockBack = true;
	}
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

void AIreneCharacter::SpawnPet(ASpiritPlate* Target)
{
	AShieldSpirit* NewPet = GetWorld()->SpawnActor<AShieldSpirit>(AShieldSpirit::StaticClass(),GetActorLocation()+PetSpringArmComp->GetRelativeLocation() , FRotator::ZeroRotator);
	NewPet->SetSpiritPlate(Target);
	PetMesh->SetVisibility(false);
}

void AIreneCharacter::VisiblePet()
{
	PetMesh->SetVisibility(true);

}

void AIreneCharacter::PlayFadeOutAnimation()
{
	PlayFadeOutEvent();
}
#pragma endregion Battle

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
