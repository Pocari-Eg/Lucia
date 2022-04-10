// Fill out your copyright notice in the Description page of Project Settings.

#include "Morbit.h"
#include "../../IreneCharacter.h"
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
	InitDebuffInfo();

	bTestMode = false;
}
#pragma region Init
void AMorbit::InitMonsterInfo()
{
	MonsterInfo.Code = 1;

	MonsterInfo.MaxHp = 100.0f;
	MonsterInfo.Atk = 100.0f;
	MonsterInfo.Def = 100.0f;

	AttributeDef.e_None = 100.0f;
	AttributeDef.e_Fire = 0.0f;
	AttributeDef.e_Water = 0.0f;
	AttributeDef.e_Thunder = 0.0f;

	MonsterInfo.MoveSpeed = 40.0f;
	MonsterInfo.BattleWalkMoveSpeed = 90.0f;
	MonsterInfo.ViewAngle = 150.0f;
	MonsterInfo.ViewRange = 500.0f;
	MonsterInfo.MeleeAttackRange = 100.0f;
	MonsterInfo.TraceRange = 1000.0f;

	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
}
void AMorbit::InitCollision()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(60.0f);
	GetCapsuleComponent()->SetCapsuleRadius(34.0f);
}
void AMorbit::InitMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster/Morbit/Morbit_Idle/M_Mb_Idle"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -60.0f), FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
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
void AMorbit::InitMorbitInfo()
{
	switch (MonsterInfo.Code)
	{
	case 1:
		AttributeDef.e_None = 100.0f;
		AttributeDef.e_Fire = 0.0f;
		AttributeDef.e_Water = 0.0f;
		AttributeDef.e_Thunder = 0.0f;

		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
		break;
	case 2:
		AttributeDef.e_None = 100.0f;
		AttributeDef.e_Fire = 0.0f;
		AttributeDef.e_Water = 0.0f;
		AttributeDef.e_Thunder = 0.0f;

		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
		break;
	case 3:
		AttributeDef.e_None = 30.0f;
		AttributeDef.e_Fire = 50.0f;
		AttributeDef.e_Water = 0.0f;
		AttributeDef.e_Thunder = 2.0f;

		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Fire;
		break;
	case 4:
		AttributeDef.e_None = 0.0f;
		AttributeDef.e_Fire = 50.0f;
		AttributeDef.e_Water = 30.0f;
		AttributeDef.e_Thunder = 20.0f;

		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Fire;
		break;
	case 5:
		AttributeDef.e_None = 25.0f;
		AttributeDef.e_Fire = 15.0f;
		AttributeDef.e_Water = 0.0f;
		AttributeDef.e_Thunder = 60.0f;

		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Water;
		break;
	case 6:
		AttributeDef.e_None = 0.0f;
		AttributeDef.e_Fire = 0.0f;
		AttributeDef.e_Water = 80.0f;
		AttributeDef.e_Thunder = 20.0f;

		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Water;
		break;
	case 7:
		AttributeDef.e_None = 0.0f;
		AttributeDef.e_Fire = 10.0f;
		AttributeDef.e_Water = 30.0f;
		AttributeDef.e_Thunder = 60.0f;

		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Thunder;
		break;
	case 8:
		AttributeDef.e_None = 30.0f;
		AttributeDef.e_Fire = 0.0f;
		AttributeDef.e_Water = 0.0f;
		AttributeDef.e_Thunder = 70.0f;

		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Thunder;
		break;
	default:
		break;
	}
}
void AMorbit::InitMorbitMaterial()
{
	UMaterial* Material;
	switch (MonsterInfo.MonsterAttribute)
	{
	case EAttributeKeyword::e_None:
		Material = LoadObject<UMaterial>(NULL, TEXT("/Game/Model/Monster/Morbit/Material/M_Morbit_Master"), NULL, LOAD_None, NULL);
		if (Material != nullptr)
		{
			GetMesh()->SetMaterial(0, Material);
			GetMesh()->SetMaterial(1, Material);
		}
		break;
	}
}
void AMorbit::InitOccupationAI()
{
	auto MbAIController = Cast<AMbAIController>(GetController());

	if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_None)
	{
		MbAIController->SetMilitantAI();	
	}
	else
	{
		MbAIController->SetDefensiveAI();
	}
}
#pragma endregion
#pragma region GetValue
bool AMorbit::GetTestMode()
{
	return bTestMode;
}
float AMorbit::GetViewAngle()
{
	return MonsterInfo.ViewAngle;
}
float AMorbit::GetViewRange()
{
	return MonsterInfo.ViewRange;
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
	MonsterAnimInstance->PlayMeleeAttackMontage();

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
		GetActorLocation() + (GetActorForwardVector() * MonsterInfo.MeleeAttackRange),
		GetActorLocation() + (GetActorForwardVector() * MonsterInfo.MeleeAttackRange * 0.5f * 0.5f),
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

		UGameplayStatics::ApplyDamage(Player, MonsterInfo.Atk, NULL, this, NULL);
	}
	//
}
#pragma endregion
// Called when the game starts or when spawned
void AMorbit::BeginPlay()
{
	Super::BeginPlay();

	//InitMorbitMaterial();
}

// Called every frame
void AMorbit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMorbit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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

	MonsterAnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (MonsterAnimInstance == nullptr)
		return;
	//애니메이션 몽타주 종료시 호출
	MonsterAnimInstance->AttackEnd.AddLambda([this]() -> void {
		bIsAttacking = false;

		AttackEnd.Broadcast();
		});
	MonsterAnimInstance->Death.AddLambda([this]() -> void {
		if (bIsDead)
			SetActorHiddenInGame(true);
		});
	MonsterAnimInstance->Attack.AddUObject(this, &AMorbit::AttackCheck);
}