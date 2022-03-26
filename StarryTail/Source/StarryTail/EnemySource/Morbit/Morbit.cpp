// Fill out your copyright notice in the Description page of Project Settings.

#include "Morbit.h"
#include "../../IreneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MbAIController.h"

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
	MonsterInfo.Hp = 100.0f;
	MonsterInfo.Atk = 100.0f;
	MonsterInfo.Def = 100.0f;

	AttributeDef.Normal = 80.0f;
	AttributeDef.Pyro = 15.0f;
	AttributeDef.Hydro = 0.0f;
	AttributeDef.Electro = 5.0f;

	MonsterInfo.MoveSpeed = 100.0f;
	MonsterInfo.BattleWalkMoveSpeed = 150.0f;
	MonsterInfo.ViewAngle = 120.0f;
	MonsterInfo.ViewRange = 200.0f;
	MonsterInfo.MeleeAttackRange = 100.0f;
	MonsterInfo.TraceRange = 1000.0f;

	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
}
void AMorbit::InitCollision()
{
	Collision = GetCapsuleComponent();
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(40.0f);
	GetCapsuleComponent()->SetCapsuleRadius(34.0f);
}
void AMorbit::InitMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster/Morbit/Morbit_Idle/M_Mb_Idle"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -35.0f), FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
}
void AMorbit::InitAnime()
{
	//�ִϸ��̼� ��� ����
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// �ִ� �ν��Ͻ� ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> MorbitAnim(TEXT("/Game/BluePrint/Monster/MorbitAnimation/MorbitAnimBlueprint"));
	if (MorbitAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(MorbitAnim.Class);
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
	if (bIsAttacking)
		return;

	MonsterAnimInstance->PlayMeleeAttackMontage();

	bIsAttacking = true;
}
#pragma endregion

// Called when the game starts or when spawned
void AMorbit::BeginPlay()
{
	Super::BeginPlay();

	// switch(MonsterInfo.MonsterAttribute)
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
	//�ִϸ��̼� ��Ÿ�� ����� ȣ��
	MonsterAnimInstance->AttackEnd.AddLambda([this]() -> void {
		bIsAttacking = false;

		AttackEnd.Broadcast();
		});
	MonsterAnimInstance->Death.AddLambda([this]() -> void {
		if (bIsDead)
			Death.Broadcast();
		});
}