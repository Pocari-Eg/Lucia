// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "./EnemySource/EnemyAnimInstance.h"
#include "./EnemySource/EnemyController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "StarryTail.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsAttacking = false;

	AIControllerClass = AEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemeyMesh(TEXT("/Game/Animation/Monster_Walk/Dummy_Walk.Dummy_Walk"));
	if (EnemeyMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(EnemeyMesh.Object);
	}
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(53.0f);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -55.0f), FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(50.0f, 50.0f, 50.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);


	static ConstructorHelpers::FClassFinder<UAnimInstance> EnemyAnim(TEXT("/Game/Animation/EnemyAnimBlueprint"));
	if (EnemyAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(EnemyAnim.Class);
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	EnemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	EnemyAnimInstance->OnMontageEnded.AddDynamic(this, &AEnemy::OnAttackMontageEnded);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::SetEnemyType(EEnemyType EnemyType)
{
	CurrentEnemyType = EnemyType;

	switch (CurrentEnemyType)
	{
	case EEnemyType::DEFAULT:
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
		break;
	}
}
void AEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	SetEnemyType(EEnemyType::DEFAULT);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}
void AEnemy::RangedAttack()
{
	if (bIsAttacking) return;

	EnemyAnimInstance->PlayRangedAttackMontage();
	++AEnemyController::RangedAttackCount;

	bIsAttacking = true;
}
void AEnemy::MeleeAttack()
{
	if (bIsAttacking) return;

	EnemyAnimInstance->PlayMeleeAttackMontage();
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		Params);

	if (HitResult.Actor.IsValid())
	{
		STARRYLOG(Warning, TEXT("Melee Attack Hit Actor Name : %s"), *HitResult.Actor->GetName());
	}

	bIsAttacking = true;
}
void AEnemy::RushAttack()
{
	if (bIsAttacking) return;

	EnemyAnimInstance->PlayRushAttackMontage();

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		Params);

	if (HitResult.Actor.IsValid())
	{
		STARRYLOG(Warning, TEXT("Rush Attack Hit Actor Name : %s"), *HitResult.Actor->GetName());
	}

	bIsAttacking = true;
}
void AEnemy::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;

	OnAttackEnd.Broadcast();
}


