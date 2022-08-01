// Fill out your copyright notice in the Description page of Project Settings.


#include "Ferno.h"
#include"../../PlayerSource/IreneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AFerno::AFerno()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AFernoAIController::StaticClass();
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
UFernoAnimInstance* AFerno::GetFernoAnimInstance() const
{
	return FernoAnimInstance;
}

void AFerno::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
}

void AFerno::RangeAttack()
{

	STARRYLOG(Error, TEXT("Ferno Fire"));
}


void AFerno::BeginPlay()
{
	Super::BeginPlay();

	MonsterAnimInstance = FernoAnimInstance;

	if (FernoAnimInstance == nullptr)
		return;
	//애니메이션 몽타주 종료시 호출
	FernoAnimInstance->AttackEnd.AddLambda([this]() -> void {
		bIsAttacking = false;
		AttackEnd.Broadcast();

		STARRYLOG_S(Error);
		});
	FernoAnimInstance->AttackedEnd.AddLambda([this]() -> void {
		bIsAttacked = false;
		AttackedEnd.Broadcast();
		});
	FernoAnimInstance->Death.AddLambda([this]() -> void {
		if (bIsDead)
		{
			bDeadWait = true;
			SetActorEnableCollision(false);
			FernoAnimInstance->Montage_Stop(500.f, FernoAnimInstance->GetCurrentActiveMontage());
		}

		});
	FernoAnimInstance->Attack.AddUObject(this, &AFerno::RangeAttack);

	SoundInstance->SetHitSound("event:/StarryTail/Enemy/SFX_Hit");
}

void AFerno::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
}

void AFerno::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	FernoAnimInstance = Cast<UFernoAnimInstance>(GetMesh()->GetAnimInstance());
}

#pragma region Init
void AFerno::InitMonsterInfo()
{
	MonsterInfo.M_Type = EEnemyRank::e_Common;
	MonsterInfo.M_Atk_Type = 2;
	MonsterInfo.M_Max_HP = 150.0f;
	MonsterInfo.M_MoveSpeed = 40.0f;
	
	

	MonsterInfo.PatrolArea = 600.0f;
	MonsterInfo.M_MaxFollowTime = 5.0f;

	
	MonsterInfo.BattleWalkMoveSpeed = 90.0f;


	MonsterInfo.M_Sight_Angle = 150.0f;
	MonsterInfo.M_Sight_Radius = 500.0f;
	MonsterInfo.M_Sight_Height = 150.0f;

	MonsterInfo.M_Atk_Angle = 175.0f;
	MonsterInfo.M_Atk_Radius = 400.0f;
	MonsterInfo.M_Atk_Height = 110.0f;

	
	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
	

	MonsterInfo.Max_Ele_Shield = 0;
	MonsterInfo.Ele_Shield_Count = -1;
	MonsterInfo.bIsShieldOn = false;

	MonsterInfo.Atk = 100.0f;

	MonsterInfo.KnockBackPower = 50.0f;
	MonsterInfo.DeadWaitTime = 3.0f;

	MonsterInfo.DetectMonsterRange = 5.0f;
	MonsterInfo.MeleeAttackRange = 100.0f * GetActorScale().X;
	MonsterInfo.TraceRange = 1000.0f;

	MonsterInfo.M_MaxAttacked = 3;
}

void AFerno::InitCollision()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(150.0f);
	GetCapsuleComponent()->SetCapsuleRadius(34.0f);
}

void AFerno::InitMesh()
{
	//메쉬 변경 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster/Morbit/Morbit_Idle/M_Mb_Idle"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -150.0f), FRotator(0.0f, 270.0f, 0.0f));

	float Scale = FMath::RandRange(0.9f, 1.1f);

	GetMesh()->SetRelativeScale3D(FVector(Scale, Scale, Scale));
}
// Called every frame
void AFerno::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AFerno::InitAnime()
{
	//애니메이션 모드 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님 인스턴스 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> FrenoAnim(TEXT("/Game/BluePrint/Monster/Ferno/FernoAnimBluePrint.FernoAnimBluePrint_C"));
	if (FrenoAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(FrenoAnim.Class);
	}
}
#pragma endregion Init