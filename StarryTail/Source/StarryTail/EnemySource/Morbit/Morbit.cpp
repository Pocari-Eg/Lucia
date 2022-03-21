// Fill out your copyright notice in the Description page of Project Settings.

#include "Morbit.h"
#include "../../IreneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../EnemyAnimInstance.h"
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

	bTestMode = false;
}
#pragma region Init
void AMorbit::InitMonsterInfo()
{	
	MonsterInfo.Name = FName(TEXT("M_Mb"));
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
}
void AMorbit::InitCollision()
{
	Collision = GetCapsuleComponent();
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(53.0f);
	GetCapsuleComponent()->SetCapsuleRadius(34.0f);
}
void AMorbit::InitMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster_Walk/Dummy_Walk.Dummy_Walk"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -55.0f), FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(50.0f, 50.0f, 50.0f));
}
void AMorbit::InitAnime()
{
	//애니메이션 모드 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님 인스턴스 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> MorbitAnim(TEXT("/Game/Animation/EnemyAnimBlueprint"));
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
void AMorbit::BattleIdle()
{
	
}
void AMorbit::Attack()
{
	if (bIsAttacking)
		return;

	MonsterAnimInstance->PlayMeleeAttackMontage();

	bIsAttacking = true;
}
#pragma endregion
#pragma region CalledbyDelegate
void AMorbit::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;

	AttackEnd.Broadcast();
}
void AMorbit::OnAttackedMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacked = false;

	AttackedEnd.Broadcast();
}
void AMorbit::OnAttacked(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//액터 이름 확인
	if (bTestMode)
		STARRYLOG(Warning, TEXT("Morbit Attacked : %s"), *OtherActor->GetName());

	FString FindName = "CollisionCylinder";
	FString ElemName;

	bool IsFind = false;
	for (auto& Elem : OtherActor->GetComponents())
	{
		ElemName = Elem->GetName();
		if (ElemName == FindName)
		{
			IsFind = true;
			break;
		}
	}

	if (!IsFind)
	{
		STARRYLOG(Warning, TEXT("Not Attacked by Player"));
		return;
	}
	

	auto Player = Cast<AIreneCharacter>(OtherActor);
	if (nullptr == Player)
	{
		STARRYLOG(Warning, TEXT("Not Attacked by Player"));
		return;
	}
	STARRYLOG(Log, TEXT("Find Player"));

	auto MbAIController = Cast<AMbAIController>(GetController());
	if (nullptr == MbAIController)
	{
		STARRYLOG(Warning, TEXT("Failed Load MbAIController"));
		return;
	}

	MbAIController->Attacked(Player);

	bIsAttacked = true;
	// CalcDamage(Player->GetAttribute(), Player->GetATK());
}
#pragma endregion

// Called when the game starts or when spawned
void AMorbit::BeginPlay()
{
	Super::BeginPlay();

	CalcAttributeDefType();
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
	MonsterAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	//애니메이션 몽타주 종료시 호출
	if(bIsAttacking)
		MonsterAnimInstance->OnMontageEnded.AddDynamic(this, &AMorbit::OnAttackMontageEnded);
	if (bIsAttacked)
		MonsterAnimInstance->OnMontageEnded.AddDynamic(this, &AMorbit::OnAttackedMontageEnded);
	//피격시 호출
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AMorbit::OnAttacked);
}