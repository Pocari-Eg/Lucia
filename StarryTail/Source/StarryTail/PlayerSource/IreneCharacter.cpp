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

#pragma region Setting
AIreneCharacter::AIreneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// ?????? ????
	GetCapsuleComponent()->InitCapsuleSize(25.0f, 80.0f);
	
	// ???? ????
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComp->TargetArmLength = IreneData.FollowCameraZPosition;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 70));
	SpringArmComp->CameraLagSpeed = 0.0f;
	SpringArmComp->SetupAttachment(GetCapsuleComponent());

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->FieldOfView = IreneData.FieldOfView;

	// ??????? ??? ????
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Animation/Irene/Idle.Idle"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -80), FRotator(0, 270, 0));
		//GetMesh()->SetRelativeScale3D(FVector(8.5f,8.5f,8.5f));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
		GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
		GetCapsuleComponent()->SetGenerateOverlapEvents(true);
		
		// ????
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
		
		// ????????? ??????? ????
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Animation/Irene/Animation/BP/BP_IreneAnimation.BP_IreneAnimation_C"));

		if (CharacterAnimInstance.Succeeded())
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
	}
	// ??? ?????????
	ConstructorHelpers::FClassFinder<AIreneSpirit>BP_IreneSpirit(TEXT("/Game/BluePrint/Irene/IreneSpirit.IreneSpirit_C"));
	if(BP_IreneSpirit.Succeeded())
		IreneSpiritOrigin = BP_IreneSpirit.Class;

	// ?? ????
	PetSpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("PetSprintArm"));
	PetSpringArmComp->TargetArmLength = 0;
	PetSpringArmComp->bEnableCameraLag = true;
	PetSpringArmComp->SetRelativeLocation(FVector(0, 45, 30));
	PetSpringArmComp->CameraLagSpeed = 3.0f;
	PetSpringArmComp->SetupAttachment(GetCapsuleComponent());

	PetMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PetMesh"));
	PetMesh->SetupAttachment(PetSpringArmComp);
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>PetStatic(TEXT("/Game/Animation/Fairy/Fairy_Fly2.Fairy_Fly2"));
	if(PetStatic.Succeeded())
		PetMesh->SetSkeletalMesh(PetStatic.Object);
	PetMesh->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 270, 0));
	PetMesh->SetWorldScale3D(FVector(2.5f,2.5f,2.5f));
	
	// ???? ????? ¨¨??
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
	
	// ??? ???? ??????
	const ConstructorHelpers::FObjectFinder<UCurveVector>SkillCameraData(TEXT("/Game/Math/SkillCamera.SkillCamera"));
	if(SkillCameraData.Succeeded())
	{
		SkillCamera = SkillCameraData.Object;
	}
	
	// ???? ????? ©¦???? ??? ???? ?????? ????
	bUseControllerRotationYaw = false;
	SpringArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1050.0f, 0.0f);

	// ?? ??? ??????
	GetCharacterMovement()->MaxWalkSpeed = IreneData.RunMaxSpeed;

	// ?¡À???? ???? ?? ?? ???? ????
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// PlayerCharacterDataStruct.h?? ?????? ????
	IreneData.CurrentHP = IreneData.MaxHP;
	IreneData.CurrentEnergy = 0;
	IreneData.CurrentGauge = 100;
	
	// IreneCharacter.h?? ???? ????
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

	// ?????? ??????
	WorldController = GetWorld()->GetFirstPlayerController();
	
	STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (STGameInstance != nullptr)
		STGameInstance->SetPlayer(this);

	// ?????? ???? 
	//StopWatch = GetWorld()->SpawnActor<AStopWatch>(FVector::ZeroVector, FRotator::ZeroRotator);
	//StopWatch->InitStopWatch();

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
	
	IreneSound= NewObject<UIreneSoundInstance>(this);
	IreneSound->Init(this);

	IreneUIManager = NewObject<UIreneUIManager>(this);
	IreneUIManager->Init(this);
	
	IreneAnim->OnAttackHitCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackCheck);
	IreneAnim->OnAttackStopCheck.AddUObject(IreneAttack, &UIreneAttackInstance::AttackStopCheck);
	IreneAnim->OnFootStep.AddUObject(IreneSound, &UIreneSoundInstance::PlayWalkSound);
	IreneAnim->OnRadialBlur.AddUObject(this, &AIreneCharacter::OnRadialBlur);
}

void AIreneCharacter::TargetReset()const
{
	// ????? ????? ???? ??????? ???
	if (IreneAttack->SwordTargetMonster != nullptr)
	{
		// ?????? ???? ???????? ???? ????? ??????? ????
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
}
#pragma endregion Setting

void AIreneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LastAttackCameraShake(DeltaTime);
	//DoCameraLagCurve(DeltaTime);
	IreneInput->SkillCameraMoveLoop(DeltaTime);
	TargetReset();
	IreneState->Update(DeltaTime);


	if (bIsKnockBack)
	{
		KonckBackTimer += DeltaTime;
		FVector KnocbackLocation = GetActorLocation() + (KnockBackDir * (KonckBackPower * (0.15f - KonckBackTimer)));
		SetActorLocation(KnocbackLocation);

		if (KonckBackTimer > KnockBackTime)
		{
			KonckBackTimer = 0.0f;
			bIsKnockBack = false;
		}
	}
}

void AIreneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// ?????? ???? ????? ???
	PlayerInputComponent->BindAxis("MoveW", IreneInput, &UIreneInputInstance::MoveW).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("MoveA", IreneInput, &UIreneInputInstance::MoveA).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("MoveS", IreneInput, &UIreneInputInstance::MoveS).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("MoveD", IreneInput, &UIreneInputInstance::MoveD).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("ThunderDeBuffKey", IE_Pressed, IreneInput, &UIreneInputInstance::ThunderDeBuffKey);

	// ?????? ?? ????? ???
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, IreneInput, &UIreneInputInstance::DodgeKeyword);
	PlayerInputComponent->BindAction("MouseCursor", IE_Pressed, IreneInput, &UIreneInputInstance::MouseCursorKeyword);
	PlayerInputComponent->BindAction("WeaponChange", IE_Pressed, IreneInput, &UIreneInputInstance::SpiritChangeKeyword);
	
	// ???²J
	PlayerInputComponent->BindAxis("Turn", IreneInput, &UIreneInputInstance::Turn);
	PlayerInputComponent->BindAxis("LookUp", IreneInput, &UIreneInputInstance::LookUp);
	PlayerInputComponent->BindAxis("LeftButton", IreneInput, &UIreneInputInstance::LeftButton);
	PlayerInputComponent->BindAxis("RightButton", IreneInput, &UIreneInputInstance::RightButton);
	PlayerInputComponent->BindAxis("MouseWheel", IreneInput, &UIreneInputInstance::MouseWheel);
	
	// ?? ??
	PlayerInputComponent->BindAction("Pause", IE_Pressed, IreneInput, &UIreneInputInstance::PauseWidgetOn).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Action", IE_Pressed, IreneInput, &UIreneInputInstance::DialogAction);
	PlayerInputComponent->BindAction("DialogSkip", IE_Pressed, IreneInput, &UIreneInputInstance::DialogSkip);

	PlayerInputComponent->BindAction("TestSkillCamera", IE_Pressed, IreneInput, &UIreneInputInstance::SkillCameraMoveStart);

	// ?????? ?????
	//PlayerInputComponent->BindAction("WatchControl", IE_Pressed, this, &AIreneCharacter::WatchControl);
	//PlayerInputComponent->BindAction("WatchReset", IE_Pressed, this, &AIreneCharacter::WatchReset);
}

#pragma region Collision
void AIreneCharacter::FindNearMonster()const
{
	// ???? ????? ????? ??? ??????? ???? ??? ??????? ??? ??????? ???	
	if(IreneAttack->SwordTargetMonster!=nullptr && IreneState->IsFirstAttack())
	{
		// ???? ????? ???
		const auto Mon=Cast<AMonster>(IreneAttack->SwordTargetMonster);
		Mon->MarkerOff();		
		IreneAnim->SetIsHaveTargetMonster(false);
		IreneAttack->SwordTargetMonster = nullptr;
	}

	// ?? ???? ??? ????, ????, ???
	// ?¡À???? ????? ??????? ????? ????? ??????? ?????? ???
	//const FVector BoxSize = FVector(200, 50, 150);
	//auto HitMonsterList = IreneAttack->StartPositionFindNearMonster(BoxSize,GetActorLocation(),GetActorForwardVector());

	// ???? ????? ??????? ????? ????? ??????? ?????? ???	
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

	// ??????? ??? ?úô ??? ??¢¥?.
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
	DrawDebugBox(GetWorld(), Center, BoxSize, CapsuleRot, DrawColor, false, 0.1f);
#endif
	
	return MakeTuple(MonsterList, Params, bResult);
}
void AIreneCharacter::NearMonsterAnalysis(const TArray<FHitResult> MonsterList, const FCollisionQueryParams Params, const bool bResult, const float Far)const
{
	// ???? ?úô? ?? ???? ????? ?úô? ????? ??????? ???
	// ?????
	float CurNearPosition = Far;
	FName TargetCollisionProfileName;

	for (FHitResult Monster : MonsterList)
	{
		// ????? ©¦???? ?????? ????? ????
		if(FVector::Dist(CameraComp->GetComponentLocation(),Monster.GetActor()->GetActorLocation())<=FVector::Dist(CameraComp->GetComponentLocation(),GetActorLocation()))
		{
			continue;
		}
		if (bResult)
		{
			//STARRYLOG(Warning,TEXT("%s"), *Monster.GetActor()->GetName());
			// ?????????? ???????? ???(???)
			FHitResult RayHit;
			bool bLayResult = GetWorld()->LineTraceSingleByChannel(
				RayHit,
				GetActorLocation(),
				Monster.GetActor()->GetActorLocation(),
				ECollisionChannel::ECC_GameTraceChannel8,
				Params);

			// ???? ????? ©§??????????? ?????? ????? ???
			if (bLayResult && RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>() != nullptr)
			{
				// ©¦????? ??? ???? ????? ???
				float FindNearTarget = FVector::Dist(GetActorLocation(), RayHit.GetActor()->GetActorLocation());
				// ???? ??????? ?úô? ?????? ???
				// ???¥ï? ??????? ?úô? ?????? ???
				const FName RayCollisionProfileName = RayHit.GetActor()->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
				const FName EnemyProfile = "Enemy";
				const FName ObjectProfile = "Object";	
				// ?????? ?? ©§??????????? ?????? ???? ?????? ??? ?????????? ?????? ???? ??? ??????? ???
				if (RayHit.Actor.IsValid() &&
					(RayCollisionProfileName == EnemyProfile || RayCollisionProfileName == ObjectProfile)
					&& RayHit.GetActor()->WasRecentlyRendered())
				{
					// ? ???? ???
					if (IreneAttack->SwordTargetMonster == nullptr)
					{
						IreneAttack->SwordTargetMonster = RayHit.GetActor();
						IreneAnim->SetTargetMonster(RayHit.GetActor());
						IreneAnim->SetIsHaveTargetMonster(true);
						CurNearPosition = FindNearTarget;							
					}
					TargetCollisionProfileName = IreneAttack->SwordTargetMonster->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();

					// ???? ??? ????????? ?¡À???? ????? ???? ???? ????? ??¢¥?.
					if (CurNearPosition >= FindNearTarget)
					{
						// ???? ??????? ???? ????? ????
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
	// ???? ????? ????? ??? ????? ??????? ???
	if (IreneAttack->SwordTargetMonster == RayHit.GetActor())
	{
		NearPosition = FindNearTarget;
		IreneAttack->SwordTargetMonster = RayHit.GetActor();
		IreneAnim->SetTargetMonster(RayHit.GetActor());
		IreneAnim->SetIsHaveTargetMonster(true);

		auto Mon=Cast<AMonster>(IreneAttack->SwordTargetMonster);
		Mon->MarkerOn();
		// ???? ???? ???UI ???? ?? ???? ?????? ???? ???UI ???????
		// Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
		// Mon->StackWidgetOff();
		// IreneAttack->QuillTargetMonster = RayHit.GetActor();
		// Mon=Cast<AMonster>(IreneAttack->QuillTargetMonster);
		// Mon->StackWidgetOn();
		
		// ????? ??? ??????
		//const float Z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), IreneAttack->SwordTargetMonster->GetActorLocation()).Yaw;
		//GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, Z, 0.0f));
	}
}

void AIreneCharacter::FollowTargetPosition()
{
	// ????? ??? ??????
	if (IreneAttack->PerfectDodgeMonster != nullptr)
	{
		// ???? ????? ????
		if(IreneState->IsFirstAttack() || IreneInput->bLeftButtonPressed)
		{
			const auto Mon=Cast<AMonster>(IreneAttack->PerfectDodgeMonster);
			Mon->MarkerOn();
			const float Z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), IreneAttack->PerfectDodgeMonster->GetActorLocation()).Yaw;
			GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, Z, 0.0f));

			// ?????????? ??? ???
			const auto CharacterRadius = GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorScale().X;
			const auto MonsterRadius = Mon->GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorScale().X;			
			const float TargetPos = FVector::Dist(GetActorLocation(), Mon->GetLocation());
			CustomTimeDilation = 1.0f/0.4f;
			// ????? ??????? ???? ??? ????
			if (TargetPos - (CharacterRadius + MonsterRadius) > IreneData.AttackRange)
			{
				// ???? ????
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
			SetHP(DamageAmount);
			IreneAttack->SetDamageBeforeTableName(IreneAttack->GetBasicAttackDataTableName().ToString());
			
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
			if (Cast<AMonsterProjectile>(DamageCauser))
				return FinalDamage;


			// ?????? ????? ??? ????? ????
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
	// ?????? ??? ???? ?úô?? ??? ????? ?????? ???? ??????? ??? ???
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

void AIreneCharacter::SetUseCameraLag(UCurveFloat* Curve)
{
	UseLagCurve = Curve;
}

void AIreneCharacter::PlayerKnokcBack(FVector In_KnockBackDir, float In_KnockBackPower)
{
	if (!bIsKnockBack) {
		KnockBackDir = In_KnockBackDir;
		KnockBackDir.Normalize();
		KnockBackDir.Z = 0.0f;

		KonckBackPower = In_KnockBackPower;
		KnockBackTime = 0.15f;
		KonckBackTimer = 0.0f;
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

void AIreneCharacter::PlayFadeOutAnimation()
{
	PlayFadeOutEvent();
}
#pragma endregion Battle

#pragma region StopWatch
//?????? ????? ???
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
