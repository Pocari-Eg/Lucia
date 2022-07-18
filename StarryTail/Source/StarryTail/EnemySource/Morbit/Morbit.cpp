// Fill out your copyright notice in the Description page of Project Settings.

#include "Morbit.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MbAIController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMorbit::AMorbit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMbAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	InitMonsterInfo();

	InitCollision();
	InitMesh();
	InitAnime();

	bTestMode = false;

	SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));


	MonsterWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	MonsterWidget->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	TargetWidget->SetRelativeLocation(FVector(30.0f, 0.0f, 25.0f));

}
#pragma region Init
void AMorbit::InitMonsterInfo()
{
	MonsterInfo.Code = 1;

	MonsterInfo.MaxHp = 100.0f;
	MonsterInfo.Atk = 100.0f;
	MonsterInfo.Def = 100.0f;
	MonsterInfo.Barrier = 1.0f;
	MonsterInfo.DetectMonsterRange = 5.0f;

	MonsterInfo.MoveSpeed = 40.0f;
	MonsterInfo.BattleWalkMoveSpeed = 90.0f;
	MonsterInfo.ViewAngle = 150.0f;
	MonsterInfo.ViewRange = 500.0f;
	MonsterInfo.ViewHeight = 150.0f;
	MonsterInfo.MeleeAttackRange = 100.0f * GetActorScale().X;
	MonsterInfo.TraceRange = 1000.0f;

	MonsterInfo.KnockBackPower = 50.0f;
	MonsterInfo.DeadWaitTime = 3.0f;

	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
	MonsterInfo.EnemyRank = EEnemyRank::e_Common;

	MonsterInfo.Max_Ele_Shield = 0;
	MonsterInfo.Ele_Shield_Count = -1;
	MonsterInfo.bIsShieldOn = false;


	
}
void AMorbit::InitCollision()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(150.0f);
	GetCapsuleComponent()->SetCapsuleRadius(34.0f);
}
void AMorbit::InitMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster/Morbit/Morbit_Idle/M_Mb_Idle"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -150.0f), FRotator(0.0f, 270.0f, 0.0f));

	float Scale = FMath::RandRange(0.9f, 1.1f);

	GetMesh()->SetRelativeScale3D(FVector(Scale, Scale, Scale));
}
void AMorbit::InitAnime()
{
	//애니메이션 모드 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님 인스턴스 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> MorbitAnim(TEXT("/Game/BluePrint/Monster/Morbit/MorbitAnimBlueprint"));
	if (MorbitAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(MorbitAnim.Class);
	}
}

#pragma endregion
#pragma region GetValue
UMorbitAnimInstance* AMorbit::GetMorbitAnimInstance() const
{
	return MorbitAnimInstance;
}
#pragma endregion
#pragma region CalledbyBBT
void AMorbit::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.MoveSpeed;
}
void AMorbit::BattleWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.BattleWalkMoveSpeed;
}
void AMorbit::Attack()
{
	MorbitAnimInstance->PlayAttackMontage();
	MonsterAIController->StopMovement();

	bIsAttacking = true;
}
#pragma endregion
#pragma region CalledbyDelegate
void AMorbit::AttackCheck()
{
	FHitResult Hit;

	//By 성열현
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		Hit,
		GetActorLocation() + (GetActorForwardVector() * MonsterInfo.MeleeAttackRange) + FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		GetActorLocation() + (GetActorForwardVector() * MonsterInfo.MeleeAttackRange * 0.5f * 0.5f) + FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotationMatrix::MakeFromZ(GetActorForwardVector() * MonsterInfo.MeleeAttackRange).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(20.0f),
		Params);

	if (bTestMode)
	{
		FVector TraceVec = GetActorForwardVector() * MonsterInfo.MeleeAttackRange;
		FVector Center = GetActorLocation() + TraceVec * 0.5f;
		float HalfHeight = MonsterInfo.MeleeAttackRange * 0.5f * 0.5f;
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		DrawDebugCapsule(GetWorld(),
			Center,
			HalfHeight,
			20.0f,
			CapsuleRot,
			DrawColor,
			false,
			DebugLifeTime);
	}

	if (bResult)
	{
		auto Player = Cast<AIreneCharacter>(Hit.Actor);
		if (nullptr == Player)
			return;

		if (bIsSpark)
		{
			UGameplayStatics::ApplyDamage(Player, MonsterInfo.Atk * MonsterAttributeDebuff.SparkReduction / 100.0f, NULL, this, NULL);
			CalcHp(MonsterInfo.Atk * MonsterAttributeDebuff.SparkDamage / 100.0f);
		}
		else
		{
			UGameplayStatics::ApplyDamage(Player, MonsterInfo.Atk, NULL, this, NULL);
		}
	}
	//
}
#pragma endregion
// Called when the game starts or when spawned
void AMorbit::BeginPlay()
{
	Super::BeginPlay();

	MonsterAnimInstance = MorbitAnimInstance;

	if (MorbitAnimInstance == nullptr)
		return;
	//애니메이션 몽타주 종료시 호출
	MorbitAnimInstance->AttackEnd.AddLambda([this]() -> void {
		bIsAttacking = false;
		AttackEnd.Broadcast();
		});
	MorbitAnimInstance->AttackedEnd.AddLambda([this]() -> void {
		bIsAttacked = false;
		AttackedEnd.Broadcast();
		});
	MorbitAnimInstance->Death.AddLambda([this]() -> void {
		if (bIsDead)
		{
			bDeadWait = true;
			SetActorEnableCollision(false);
			MorbitAnimInstance->Montage_Stop(500.f, MorbitAnimInstance->GetCurrentActiveMontage());
		}

		});
	MorbitAnimInstance->Attack.AddUObject(this, &AMorbit::AttackCheck);

	SoundInstance->SetHitSound("event:/StarryTail/Enemy/SFX_Hit");
}

// Called every frame
void AMorbit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMorbit::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.MoveSpeed;
}

void AMorbit::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MorbitAnimInstance = Cast<UMorbitAnimInstance>(GetMesh()->GetAnimInstance());
}