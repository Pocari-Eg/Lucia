// Fill out your copyright notice in the Description page of Project Settings.


#include "Bellyfish.h"
#include"../../PlayerSource/IreneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../STGameInstance.h"
#include "Kismet/GameplayStatics.h"


ABellyfish::ABellyfish()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABellyfishAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;



	InitMonsterInfo();

	InitCollision();
	InitMesh();
	InitAnime();

	Magic_CircleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Magic_CircleEffect"));
	Magic_CircleComponent->SetupAttachment(GetMesh());
	Magic_CircleComponent->bAutoActivate = false;
	Magic_CircleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));

	bTestMode = false;

	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));

	MonsterWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	MonsterWidget->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	TargetWidget->SetRelativeLocation(FVector(30.0f, 0.0f, 25.0f));

	IsSkillSet = false;
	IsSkillAttack = false;
	IsCloseOtherAttack = false;

	static ConstructorHelpers::FClassFinder<ABF_MagicAttack> BP_MAGICATTACK(TEXT("/Game/BluePrint/Monster/Bellyfish/BP_BF_MagicAttack.BP_BF_MagicAttack_C")); 
	if (BP_MAGICATTACK.Succeeded() && BP_MAGICATTACK.Class != NULL) {
		MagicAttackClass=BP_MAGICATTACK.Class;
	}

	SkillSetTimer = 0.0f;
	SkillAttackTimer = 0.0f;
	IntersectionTimer = 0.0f;

	Info.M_MaxFlyDistance = 100.0f;
	Info.M_RushAtk = 100.0f;

	DodgeTimePercent = 10.0f;

	 bIsRush = false;
	 bIsPlayerRushHit = false;
}
UBellyfishAnimInstance* ABellyfish::GetBellyfishAnimInstance() const
{
	return BellyfishAnimInstance;
}

void ABellyfish::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
}

void ABellyfish::Attack()
{
	//어택 준비 애니메이션 출력
	BellyfishAnimInstance->PlayAttackSignMontage();
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	Info.AttackPosition = STGameInstance->GetPlayer()->GetActorLocation();
	Info.AttackPosition.Z = Info.AttackPosition.Z - 80.0f;

	if (IntersectionCheck())
	{
		IsCloseOtherAttack = true;
	}
	else {
		Skill_Setting();
	}
}

void ABellyfish::RushAttack()
{
	BellyfishAnimInstance->PlayRushMontage();
	GetCharacterMovement()->MaxWalkSpeed = Info.RushSpeed;
	bIsRush = true;
}

void ABellyfish::Skill_Setting()
{
	Info.DodgeTime = MonsterInfo.M_Skill_Set_Time - (MonsterInfo.M_Skill_Set_Time / 100.0f) * DodgeTimePercent;
	PerfectDodgeDir.Add((uint8)EDodgeDirection::Right);
	PerfectDodgeDir.Add((uint8)EDodgeDirection::Left);
	PerfectDodgeDir.Add((uint8)EDodgeDirection::Front);
	PerfectDodgeDir.Add((uint8)EDodgeDirection::Back);
	STARRYLOG(Error, TEXT("%f"), Info.DodgeTime);

	IsSkillSet = true;
	Magic_CircleComponent->SetActive(true);
	Magic_CircleComponent->SetVisibility(true);
	MagicAttack = GetWorld()->SpawnActor<ABF_MagicAttack>(MagicAttackClass, Info.AttackPosition, FRotator::ZeroRotator);
	MagicAttack->SetMagicAttack(MonsterInfo.M_Skill_Radius,MonsterInfo.M_Skill_Atk);


}

void ABellyfish::Skill_Set()
{

	IsSkillSet = false;
	Magic_CircleComponent->SetActive(false);
	Magic_CircleComponent->SetVisibility(false);
    SkillSetTimer = 0.0;
	//스킬셋 애니메이션 해제

	Skill_Attack();
	PerfectDodgeDir.Empty();
	BellyfishAnimInstance->PlayAttackMontage();
}

void ABellyfish::PlayRunAnim()
{
	BellyfishAnimInstance->PlayRunMontage();
}

void ABellyfish::Skill_Attack()
{
	
	IsSkillAttack = true;
	MagicAttack->EndIndicator();
	MagicAttack->SetActiveAttack();

}

void ABellyfish::Skill_AttackEnd()
{
	IsSkillAttack = false;
	SkillAttackTimer = 0.0f;
	MagicAttack->Destroy();
	AttackEnd.Broadcast();
}

bool ABellyfish::IntersectionCheck()
{
	float DetectRadius = MonsterInfo.M_Skill_Radius * 1.5f;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	bool bResult = GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
		OverlapResults,
		Info.AttackPosition,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel14,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);
	DrawDebugSphere(GetWorld(), Info.AttackPosition, DetectRadius, 16, FColor::Red, false, 0.2f);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			ABF_MagicAttack* OtherAttack = Cast<ABF_MagicAttack>(OverlapResult.GetActor());

			float Distance = (Info.AttackPosition - OtherAttack->GetActorLocation()).Size();
			if (Distance <= DetectRadius)
			{
				return true;
			}

		}
	}
	else {
		return false;
	}


	return false;
}



void ABellyfish::BeginPlay()
{
	Super::BeginPlay();

	MonsterAnimInstance = BellyfishAnimInstance;

	if (BellyfishAnimInstance == nullptr)
		return;
	//애니메이션 몽타주 종료시 호출
	BellyfishAnimInstance->AttackEnd.AddLambda([this]() -> void {
		bIsAttacking = false;
		AttackEnd.Broadcast();
		STARRYLOG_S(Error);
		});
	BellyfishAnimInstance->AttackedEnd.AddLambda([this]() -> void {
		bIsAttacked = false;
		AttackedEnd.Broadcast();
		});
	BellyfishAnimInstance->Death.AddLambda([this]() -> void {
		if (bIsDead)
		{
			bDeadWait = true;
			SetActorEnableCollision(false);
			BellyfishAnimInstance->Montage_Stop(500.f, BellyfishAnimInstance->GetCurrentActiveMontage());
		}
		});
	BellyfishAnimInstance->Attack.AddUObject(this, &ABellyfish::Attack);

	BellyfishAnimInstance->RushEnd.AddLambda([this]() -> void {
		RushEnd.Broadcast();
		bIsRush = false;
		bIsPlayerRushHit = false;
		bIsWallRushHit = false;
	});


	Magic_CircleComponent->SetTemplate(Magic_Circle);
	SoundInstance->SetHitSound("event:/StarryTail/Enemy/SFX_Hit");



}

void ABellyfish::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABellyfish::OnHit);
}

void ABellyfish::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BellyfishAnimInstance = Cast<UBellyfishAnimInstance>(GetMesh()->GetAnimInstance());
}

#pragma region Init
float ABellyfish::GetFlyDistance()
{
	return Info.M_Fly_Distance;
}
float ABellyfish::GetRunDistance()
{
	return Info.M_Run_Distance;
}
float ABellyfish::GetAttackedTime()
{
	return Info.M_Attacked_Time;
}
float ABellyfish::GetRushTime()
{
	return Info.M_Run_Time;
}
float ABellyfish::GetRushTestRange()
{
	return RushTestRange;
}
float ABellyfish::GetRushSpeed()
{
	return Info.RushSpeed;
}
float ABellyfish::GetMaxFlyDistance()
{
	return Info.M_MaxFlyDistance;
}
void ABellyfish::SetFlyDistance(float Distance)
{
	Info.M_Fly_Distance = Distance;
}
void ABellyfish::InitMonsterInfo()
{
	MonsterInfo.M_Type = EEnemyRank::e_Common;
	MonsterInfo.M_Atk_Type = 2;
	MonsterInfo.M_Max_HP = 150.0f;
	MonsterInfo.M_MoveSpeed = 40.0f;
	MonsterInfo.Chain_Detect_Radius = 450.0f;
	MonsterInfo.M_Player_Energy = 100;

	MonsterInfo.M_Skill_Code = 1;
	MonsterInfo.M_Skill_Range = 1;
	MonsterInfo.M_Skill_Radius = 150.0f;
	MonsterInfo.M_Skill_Atk = 100.0f;
	MonsterInfo.M_Skill_Time = 0.2f;
	MonsterInfo.M_Skill_Set_Time = 1.0f;
	MonsterInfo.M_Skill_Cool = 3.0f;


	MonsterInfo.PatrolArea = 600.0f;
	MonsterInfo.M_MaxFollowTime = 5.0f;
	MonsterInfo.BattleWalkMoveSpeed = 90.0f;
	

	MonsterInfo.M_Sight_Angle = 150.0f;
	MonsterInfo.M_Sight_Radius = 500.0f;
	MonsterInfo.M_Sight_Height = 150.0f;

	MonsterInfo.M_Atk_Angle = 110.0f;
	MonsterInfo.M_Atk_Radius = 400.0f;
	MonsterInfo.M_Atk_Height = 250.0f;

	
	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
	

	MonsterInfo.Max_Ele_Shield = 0;
	MonsterInfo.Ele_Shield_Count = -1;
	MonsterInfo.bIsShieldOn = false;

	
	MonsterInfo.KnockBackPower = 50.0f;
	MonsterInfo.DeadWaitTime = 1.0f;

	
	MonsterInfo.MeleeAttackRange = 100.0f * GetActorScale().X;
	MonsterInfo.TraceRange = 1000.0f;

	MonsterInfo.M_MaxAttacked = 3;

	Info.M_Run_Distance = 450.0f;
	Info.M_Run_Time = 3.0f;
	Info.M_Attacked_Time = 0.5f;
	MonsterInfo.M_AttackPercent = 80.0f;
}

void ABellyfish::InitCollision()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(110);
	GetCapsuleComponent()->SetCapsuleRadius(50.0f);
}

void ABellyfish::InitMesh()
{
	//메쉬 변경 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/MonsterDummy/Bellyfish/Mesh/M_VS_Idle.M_VS_Idle"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, 270.0f, 0.0f));

	float Scale = FMath::RandRange(0.9f, 1.1f);

	GetMesh()->SetRelativeScale3D(FVector(Scale, Scale, Scale));
}
void ABellyfish::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

	if (bIsRush)
	{
		if (!bIsPlayerRushHit)
		{
			if (Cast<AIreneCharacter>(OtherActor))
			{
				auto Player = Cast<AIreneCharacter>(OtherActor);
				UGameplayStatics::ApplyDamage(Player, (Info.M_RushAtk), NULL, this, NULL);
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
					CalcHp(Info.M_RushAtk);
					if (!bIsDead)
					{
						auto BellyfishAIController = Cast<ABellyfishAIController>(MonsterAIController);
						//BellyfishAIController->WallGroggy();
						MonsterAnimInstance->PlayGroggyMontage();
					}
					bIsWallRushHit = true;
				}
			}
		}
	}
}
// Called every frame
void ABellyfish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead == false) {

		if (IsCloseOtherAttack)
		{
			IntersectionTimer += DeltaTime;
			if (IntersectionTimer >= 1.0f)
			{
				IntersectionTimer = 0.0f;
				IsCloseOtherAttack = false;
				Skill_Setting();
			}
		}

		if (IsSkillSet)
		{
		
			SkillSetTimer += DeltaTime;
			float Ratio = SkillSetTimer < KINDA_SMALL_NUMBER ? 0.0f : SkillSetTimer / MonsterInfo.M_Skill_Set_Time;
			Ratio = (Ratio * 0.5);
			MagicAttack->PlayIndicator(Ratio);
			if (SkillSetTimer >= Info.DodgeTime&& SkillSetTimer< MonsterInfo.M_Skill_Set_Time)
			{
				auto Instance = Cast<USTGameInstance>(GetGameInstance());
			
				if(MagicAttack->GetInPlayer() == true)
				{
					Instance->GetPlayer()->IreneAttack->SetIsPerfectDodge(true, PerfectDodgeDir);
					Instance->GetPlayer()->IreneAttack->SetIsPerfectDodgeMonster(this);
				}
				else {
					Instance->GetPlayer()->IreneAttack->SetIsPerfectDodge(false, PerfectDodgeDir);
					Instance->GetPlayer()->IreneAttack->SetIsPerfectDodgeMonster(this);
				}
				
			}
			if (SkillSetTimer >= MonsterInfo.M_Skill_Set_Time)
			{
				auto Instance = Cast<USTGameInstance>(GetGameInstance());
				Instance->GetPlayer()->IreneAttack->SetIsPerfectDodge(false, PerfectDodgeDir);
				Skill_Set();
			}
		}
		if (IsSkillAttack)
		{


			SkillAttackTimer += DeltaTime;
			if (SkillAttackTimer >= MonsterInfo.M_Skill_Time)
			{
				Skill_AttackEnd();
			}
		}
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + Info.M_Fly_Distance));
	}
	else {
		if (MagicAttack != nullptr) {
			MagicAttack->Destroy();
		}
	}
}
void ABellyfish::InitAnime()
{
	//애니메이션 모드 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님 인스턴스 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> FrenoAnim(TEXT("/Game/BluePrint/Monster/Bellyfish/BellyfishAnimBluePrint.BellyfishAnimBluePrint_C"));
	if (FrenoAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(FrenoAnim.Class);
	}
}
#pragma endregion Init