// Fill out your copyright notice in the Description page of Project Settings.


#include "Bouldelith.h"
#include "BdAIController.h"

ABouldelith::ABouldelith()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABdAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	InitMonsterInfo();
	InitCollision();
	InitMesh();
	InitAnime();

	bTestMode = false;

	HitEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Enemy/SFX_Hit");
	HpBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 380));
}
#pragma region Init
void ABouldelith::InitMonsterInfo()
{
	MonsterInfo.Code = 1;

	MonsterInfo.MaxHp = 1000.0f;
	MonsterInfo.Atk = 250.0f;
	MonsterInfo.Def = 250.0f;
	MonsterInfo.Barrier = 100.0f;
	MonsterInfo.DetectMonsterRange = 10.0f;

	MonsterInfo.MoveSpeed = 200.0f;
	MonsterInfo.BattleWalkMoveSpeed = 200.0f;
	MonsterInfo.ViewAngle = 180.0f;
	MonsterInfo.ViewRange = 1000.0f;
	MonsterInfo.ViewHeight = 200.0f;
	MonsterInfo.MeleeAttackRange = 100.0f;
	MonsterInfo.TraceRange = 1000.0f;

	MonsterInfo.KnockBackPower = 10.0f;
	MonsterInfo.DeadWaitTime = 3.0f;

	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
}
void ABouldelith::InitCollision()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(200.0f);
	GetCapsuleComponent()->SetCapsuleRadius(88.0f);
}
void ABouldelith::InitMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster/Bouldelith/Idle/M_Bd_Idle"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()), FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
}
void ABouldelith::InitAnime()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님 인스턴스 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> BouldelithAnim(TEXT("/Game/BluePrint/Monster/Bouldelith/BouldelithAnimBlueprint"));
	if (BouldelithAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BouldelithAnim.Class);
	}
}
#pragma endregion

void ABouldelith::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.MoveSpeed;
}
void ABouldelith::BattleRun()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultBattleRunSpeed;
	CurrentBattleRunSpeed = DefaultBattleRunSpeed;

	BdAnimInstance->PlayBattleRunMontage();
}

UBdAnimInstance* ABouldelith::GetBouldelithAnimInstance() const
{
	return BdAnimInstance;
}
void ABouldelith::AddBattleRunSpeed(float Value)
{
	CurrentBattleRunSpeed += Value;
}
float ABouldelith::GetBattleRunSpeed()
{
	return CurrentBattleRunSpeed;
}
void ABouldelith::ResetBattleRunSpeed()
{
	CurrentBattleRunSpeed = DefaultBattleRunSpeed;
}
TArray<ABouldelithPatrolTarget*> ABouldelith::GetPatrolList()
{
	return PatrolList;
}
ABouldelithPatrolTarget* ABouldelith::GetUsePatrol()
{
	return UsePatrol;
}
void ABouldelith::SetUsePatrol(ABouldelithPatrolTarget* PatrolTarget)
{
	UsePatrol = PatrolTarget;
}
void ABouldelith::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MonsterAnimInstance = BdAnimInstance;
}
void ABouldelith::BeginPlay()
{
	Super::BeginPlay();
}
void ABouldelith::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.MoveSpeed;
}
void ABouldelith::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BdAnimInstance = Cast<UBdAnimInstance>(GetMesh()->GetAnimInstance());
}