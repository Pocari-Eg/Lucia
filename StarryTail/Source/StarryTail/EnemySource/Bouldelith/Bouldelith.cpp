// Fill out your copyright notice in the Description page of Project Settings.


#include "Bouldelith.h"
#include "BdAIController.h"

ABouldelith::ABouldelith()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABdAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	InitMonsterInfo();
	InitBouldelithInfo();
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
	MonsterInfo.DetectMonsterRange = 5.0f;

	MonsterInfo.MoveSpeed = 200.0f;
	MonsterInfo.BattleWalkMoveSpeed = 200.0f;
	MonsterInfo.ViewAngle = 180.0f;
	MonsterInfo.ViewRange = 1000.0f;
	MonsterInfo.ViewHeight = 200.0f;
	MonsterInfo.MeleeAttackRange = 300.0f;
	MonsterInfo.TraceRange = 3000.0f;

	MonsterInfo.KnockBackPower = 10.0f;
	MonsterInfo.DeadWaitTime = 3.0f;

	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
	MonsterInfo.EnemyRank = EEnemyRank::e_Unique;
}
void ABouldelith::InitBouldelithInfo()
{
	BouldelithInfo.AnotherMonsterStateCheckRange = 1000.0f;
	BouldelithInfo.DefaultBattleRunSpeed = 450.0f;
	BouldelithInfo.BackstepCoolTime = 10.0f;
	BouldelithInfo.BrokenAnimePlayRate = 1.3f;
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
void ABouldelith::BattleIdle()
{
	BdAnimInstance->PlayBattleIdleMontage();
	MonsterAIController->StopMovement();
}
void ABouldelith::BattleWalk()
{
	BdAnimInstance->PlayBattleWalkMontage();
	MonsterAIController->StopMovement();
}
#pragma region Attack
void ABouldelith::Attack1()
{
	int Random = FMath::RandRange(0, 9);

	if (Random < 3)
	{
		BdAnimInstance->PlayAttack1ComboMontage();
	}
	else
	{
		BdAnimInstance->PlayAttack1Montage();
	}
	MonsterAIController->StopMovement();
}
void ABouldelith::Attack2()
{
	int Random = FMath::RandRange(0, 9);

	if (Random < 3)
	{
		BdAnimInstance->PlayAttack2ComboMontage();
	}
	{
		BdAnimInstance->PlayAttack2Montage();
	}
	MonsterAIController->StopMovement();
}
void ABouldelith::Attack3()
{
	BdAnimInstance->PlayAttack3Montage();
	MonsterAIController->StopMovement();
	bIsRush = true;
}
void ABouldelith::Attack4()
{
	BdAnimInstance->PlayAttack4Montage();
	MonsterAIController->StopMovement();
}
void ABouldelith::AttackCheck1()
{
	FHitResult Hit;

	//By 성열현
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		Hit,
		GetActorLocation() + (GetActorForwardVector() * MonsterInfo.MeleeAttackRange) + FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2.0f),
		GetActorLocation() + (GetActorForwardVector() * MonsterInfo.MeleeAttackRange * 0.5f * 0.5f) + FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2.0f),
		FRotationMatrix::MakeFromZ(GetActorForwardVector() * MonsterInfo.MeleeAttackRange).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(150.0f),
		Params);

	if (bTestMode)
	{
		FVector TraceVec = GetActorForwardVector() * MonsterInfo.MeleeAttackRange;
		FVector Center = GetLocation() + TraceVec * 0.5f + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		float HalfHeight = MonsterInfo.MeleeAttackRange * 0.5f * 0.5f;
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		DrawDebugCapsule(GetWorld(),
			Center,
			HalfHeight,
			150.0f,
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
	else
	{
		BouldelithInfo.AttackFailedStack++;
	}
}
void ABouldelith::AttackCheck4()
{
	TArray<FOverlapResult> OverlapResults = DetectPlayer(10);
	if (OverlapResults.Num() != 0)
	{
		for (auto const& Result : OverlapResults)
		{
			auto Player = Cast<AIreneCharacter>(Result.Actor);

			if (!Player->GetMovementComponent()->IsFalling())
			{
				if (bIsSpark)
				{
					UGameplayStatics::ApplyDamage(Player, (MonsterInfo.Atk * 2) * MonsterAttributeDebuff.SparkReduction / 100.0f, NULL, this, NULL);
					CalcHp(MonsterInfo.Atk * MonsterAttributeDebuff.SparkDamage / 100.0f);
				}
				else
				{
					UGameplayStatics::ApplyDamage(Player, (MonsterInfo.Atk * 2), NULL, this, NULL);
				}
			}
		}
	}
}
#pragma endregion

#pragma region Backstep
void ABouldelith::Backstep()
{
	MonsterAIController->StopMovement();
	BdAnimInstance->PlayBackstepMontage();
}
bool ABouldelith::GetIsUseBackstep()
{
	return bIsUseBackstep;
}
void ABouldelith::SetIsUseBackstep(bool Value)
{
	bIsUseBackstep = Value;
}
#pragma endregion

UBdAnimInstance* ABouldelith::GetBouldelithAnimInstance() const
{
	return BdAnimInstance;
}
float ABouldelith::GetAnotherMonsterStateCheckRange()
{
	return BouldelithInfo.AnotherMonsterStateCheckRange;
}
#pragma region BattleRun
void ABouldelith::BattleRun()
{
	GetCharacterMovement()->MaxWalkSpeed = BouldelithInfo.DefaultBattleRunSpeed;
	BouldelithInfo.CurrentBattleRunSpeed = BouldelithInfo.DefaultBattleRunSpeed;

	BdAnimInstance->PlayBattleRunMontage();
}
void ABouldelith::AddBattleRunSpeed(float Value)
{
	BouldelithInfo.CurrentBattleRunSpeed += Value;
	GetCharacterMovement()->MaxWalkSpeed = BouldelithInfo.CurrentBattleRunSpeed;
}
void ABouldelith::UpgradeBattleRunAnim()
{
	BdAnimInstance->UpgradeBattleRun();
}
float ABouldelith::GetBattleRunSpeed()
{
	return BouldelithInfo.CurrentBattleRunSpeed;
}
void ABouldelith::ResetBattleRunSpeed()
{
	BouldelithInfo.CurrentBattleRunSpeed = BouldelithInfo.DefaultBattleRunSpeed;
}
void ABouldelith::SetIsChangeBattleRunStateToAttackedState(bool Value)
{
	bIsChangeBattleRunStateToAttackedState = Value;
}
bool ABouldelith::GetIsChangeBattleRunStateToAttackedState()
{
	return bIsChangeBattleRunStateToAttackedState;
}
#pragma endregion
#pragma region Patrol
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
#pragma endregion
int ABouldelith::GetAttackFailedStack()
{
	return BouldelithInfo.AttackFailedStack;
}
void ABouldelith::ResetAttackFailedStack()
{
	BouldelithInfo.AttackFailedStack = 0;
}
float ABouldelith::GetHpPercent()
{
	return (MonsterInfo.CurrentHp / MonsterInfo.MaxHp) * 100.0f;
}
void ABouldelith::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bIsRush)
	{
		if (!bIsPlayerRushHit)
		{
			if (Cast<AIreneCharacter>(OtherActor))
			{
				auto Player = Cast<AIreneCharacter>(OtherActor);

				if (bIsSpark)
				{
					UGameplayStatics::ApplyDamage(Player, (MonsterInfo.Atk * 3) * MonsterAttributeDebuff.SparkReduction / 100.0f, NULL, this, NULL);
					CalcHp(MonsterInfo.Atk * MonsterAttributeDebuff.SparkDamage / 100.0f);
				}
				else
				{
					UGameplayStatics::ApplyDamage(Player, (MonsterInfo.Atk * 3), NULL, this, NULL);
				}
				bIsPlayerRushHit = true;
			}
		}
		if (!bIsWallRushHit)
		{
			if (Cast<UStaticMeshComponent>(OtherComponent))
			{
				auto MeshComponent = Cast<UStaticMeshComponent>(OtherComponent);
				FString FindName = "Wall";
				FString CompCollisionName = MeshComponent->GetCollisionProfileName().ToString();

				if (FindName == CompCollisionName)
				{
					CalcHp(MonsterInfo.Atk * 3);
					if (!bIsDead)
					{
						auto BdAIController = Cast<ABdAIController>(MonsterAIController);
						BdAIController->WallGroggy();
						MonsterAnimInstance->PlayGroggyMontage();
					}
					bIsWallRushHit = true;
				}
			}
		}
	}
}
void ABouldelith::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsUseBackstep)
	{
		BackstepCoolTimer += DeltaTime;

		if (BackstepCoolTimer >= BouldelithInfo.BackstepCoolTime)
		{
			bIsUseBackstep = false;
			BackstepCoolTimer = 0.0f;
		}
	}
	if (!bIsBroken)
	{
		if (bIsDead)
			return;

		if (GetHpPercent() <= 40)
		{
			auto BdAIController = Cast<ABdAIController>(MonsterAIController);
			BdAIController->Broken();
			BdAnimInstance->PlayBrokenMontage();
			MonsterInfo.DefaultAnimePlayRate = BouldelithInfo.BrokenAnimePlayRate;
			BdAnimInstance->SetPlayRate(MonsterInfo.DefaultAnimePlayRate);
			bIsBroken = true;
		}
	}
}
void ABouldelith::BeginPlay()
{
	Super::BeginPlay();

	MonsterAnimInstance = BdAnimInstance;

	BdAnimInstance->BackstepEnd.AddLambda([this]() -> void {
		BackstepEnd.Broadcast();
		});
	BdAnimInstance->Attack1End.AddLambda([this]() -> void {
		Attack1End.Broadcast();
		});
	BdAnimInstance->Attack2End.AddLambda([this]() -> void {
		Attack2End.Broadcast();
		});
	BdAnimInstance->Attack3End.AddLambda([this]() -> void {
		Attack3End.Broadcast();
		bIsRush = false;
		bIsPlayerRushHit = false;
		bIsWallRushHit = false;
		});
	BdAnimInstance->Attack4End.AddLambda([this]() -> void {
		Attack4End.Broadcast();

		});
	BdAnimInstance->AttackedEnd.AddLambda([this]() -> void {
		bIsAttacked = false;
		AttackedEnd.Broadcast();
		});
	BdAnimInstance->Death.AddLambda([this]() -> void {
		if (bIsDead)
		{
			bDeadWait = true;
			SetActorEnableCollision(false);
			BdAnimInstance->Montage_Stop(500.0f, BdAnimInstance->GetCurrentActiveMontage());
		}
		});
	BdAnimInstance->Attack.AddUObject(this, &ABouldelith::AttackCheck1);
	BdAnimInstance->Attack4.AddUObject(this, &ABouldelith::AttackCheck4);
}
void ABouldelith::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.MoveSpeed;

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABouldelith::OnHit);
}
void ABouldelith::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BdAnimInstance = Cast<UBdAnimInstance>(GetMesh()->GetAnimInstance());
}