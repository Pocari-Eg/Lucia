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

	ProjectileFirePos = CreateDefaultSubobject<UBoxComponent>(TEXT("FIREPOS"));
	ProjectileFirePos->SetupAttachment(GetMesh());

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

	 RushFlyOn=false;
}
UBellyfishAnimInstance* ABellyfish::GetBellyfishAnimInstance() const
{
	return BellyfishAnimInstance;
}


void ABellyfish::Attack()
{
	//어택 준비 애니메이션 출력

	InitAttack1Data();

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
	InitAttack3Data();
	if (RushRouteCheck())
	{
		RushFlyOn = true;
		BellyfishAnimInstance->PlayRushMontage();

	}
	else {

	 RushEnd.Broadcast();
	}
	
	
}

void ABellyfish::PlayFireAnim()
{
	InitAttack2Data();
	BellyfishAnimInstance->PlayFireMontage();
}

void ABellyfish::ProjectileAttack()
{
	STARRYLOG(Error, TEXT("Bellyfish Projectile Fire"));

	// 프로젝타일 발사를 시도합니다.
	if (ProjectileClass)
	{
		// 카메라 트랜스폼을 구합니다
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			// 총구 위치에 발사체를 스폰시킵니다.
			ABF_Projectile* Projectile = World->SpawnActor<ABF_Projectile>(ProjectileClass, ProjectileFirePos->GetComponentToWorld().GetLocation(), GetActorRotation(), SpawnParams);
			if (Projectile)
			{
				Projectile->SetProjectile(MonsterInfo.M_Skill_Atk, MonsterInfo.M_Skill_Time, MonsterInfo.M_Skill_Radius);
			}
		}
	}
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

bool ABellyfish::RushRouteCheck()
{

	FHitResult Hit;
	//By 성열현
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		Hit,
		GetActorLocation()-FVector(100.0f, 100.0f,0.0f),
		GetActorLocation()+GetActorForwardVector()*MonsterInfo.M_Skill_Radius,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel15,
		FCollisionShape::MakeSphere(50.0f),
		Params);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * MonsterInfo.M_Skill_Radius;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = MonsterInfo.M_Skill_Radius* 0.5f + 50.0f;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		50.0f,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	if (bResult)
	{
		STARRYLOG(Error,TEXT("%s"),*Hit.Actor->GetName())
		if (Cast<AIreneCharacter>(Hit.Actor))
		{
			return true;
		}
		else {
			return false;
		}
	}

	return true;
}

void ABellyfish::RushEndFunc()
{

	BellyfishAnimInstance->JumeToRushEnd();
}



void ABellyfish::BeginPlay()
{
	Super::BeginPlay();


	InitMonsterInfo();
	InitAttack3Data();


	MonsterAnimInstance = BellyfishAnimInstance;

	if (BellyfishAnimInstance == nullptr)
		return;
	//애니메이션 몽타주 종료시 호출
	BellyfishAnimInstance->AttackEnd.AddLambda([this]() -> void {
		bIsAttacking = false;
		AttackEnd.Broadcast();
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

		bIsRush = false;
		bIsPlayerRushHit = false;
		bIsWallRushHit = false;
		RushFlyOff = true;
		GetCapsuleComponent()->SetCollisionProfileName("Enemy");
	});

	BellyfishAnimInstance->RushStart.AddLambda([this]() -> void {
		RushStart.Broadcast();
		RushFlyOn = false;
		bIsRush = true;
		GetCapsuleComponent()->SetCollisionProfileName("RushCheck");
	});

	BellyfishAnimInstance->Fire.AddUObject(this, &ABellyfish::ProjectileAttack);

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

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABellyfish::OnBeginOverlap);
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
	return MonsterInfo.M_Skill_Radius;
}
float ABellyfish::GetRushSpeed()
{
	return MonsterInfo.M_Skill_Time;
}
float ABellyfish::GetMaxFlyDistance()
{
	return Info.M_MaxFlyDistance;
}

float ABellyfish::GetSkillSetTime()
{
	return MonsterInfo.M_Skill_Set_Time;
}

void ABellyfish::SetFlyDistance(float Distance)
{
	Info.M_Fly_Distance = Distance;
}
void ABellyfish::InitMonsterInfo()
{
	MonsterInfo.Monster_Rank = EEnemyRank::e_Common;
	
	 FMonsterDataTable* NewData =  GetMontserData(MonsterInfo.Monster_Code);

	MonsterInfo.M_Atk_Type = NewData->M_Atk_Type;
	MonsterInfo.M_Max_HP = NewData->M_Max_HP;
	MonsterInfo.M_HP = MonsterInfo.M_Max_HP;
	MonsterInfo.M_MoveSpeed = NewData->M_MoveSpeed;
	MonsterInfo.M_Skill_Type_01 = NewData->M_Skill_Type_01;
	MonsterInfo.M_Skill_Type_02 = NewData->M_Skill_Type_02;
	MonsterInfo.M_Skill_Type_03 = NewData->M_Skill_Type_03;
	MonsterInfo.Weapon_Soul = NewData->Weapon_Soul;


	MonsterInfo.Monster_Rank = EEnemyRank::e_Common;
	MonsterInfo.PatrolArea = 600.0f;
	MonsterInfo.M_MaxFollowTime = 5.0f;
	MonsterInfo.BattleWalkMoveSpeed = 90.0f;
	

	MonsterInfo.M_Sight_Angle = 150.0f;
	MonsterInfo.M_Sight_Radius = 500.0f;
	MonsterInfo.M_Sight_Height = 150.0f;

	//Attack Range

	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_01);
	MonsterInfo.Attack1Range.M_Atk_Angle = NewSkillData->M_Atk_Angle;
	MonsterInfo.Attack1Range.M_Atk_Height = NewSkillData->M_Atk_Height;
	MonsterInfo.Attack1Range.M_Atk_Radius = NewSkillData->M_Atk_Radius;

	NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_02);
	MonsterInfo.Attack2Range.M_Atk_Angle = NewSkillData->M_Atk_Angle;
	MonsterInfo.Attack2Range.M_Atk_Height = NewSkillData->M_Atk_Height;
	MonsterInfo.Attack2Range.M_Atk_Radius = NewSkillData->M_Atk_Radius;

	NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_03);
	MonsterInfo.Attack3Range.M_Atk_Angle = NewSkillData->M_Atk_Angle;
	MonsterInfo.Attack3Range.M_Atk_Height = NewSkillData->M_Atk_Height;
	MonsterInfo.Attack3Range.M_Atk_Radius = NewSkillData->M_Atk_Radius;
	//

	MonsterInfo.S_Attack_Time = 8.0f;
	
	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;

	MonsterInfo.Chain_Detect_Radius = 450.0f;

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

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
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
		STARRYLOG_S(Warning);
		RushEnd.Broadcast();
	}
}

void ABellyfish::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsRush)
	{
		if (!bIsPlayerRushHit)
		{
			if (Cast<AIreneCharacter>(OtherActor))
			{
				STARRYLOG_S(Warning);
				auto Player = Cast<AIreneCharacter>(OtherActor);
				UGameplayStatics::ApplyDamage(Player, MonsterInfo.M_Skill_Atk, NULL, this, NULL);
				bIsPlayerRushHit = true;
				RushEnd.Broadcast();
			}
			else {
				STARRYLOG_S(Warning);
				bIsPlayerRushHit = false;
				RushEnd.Broadcast();
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

	if (RushFlyOn== true)
	{
		Info.M_MaxFlyDistance += (DeltaTime*100.0f);
	}
	if (RushFlyOff==true)
	{
		Info.M_MaxFlyDistance -= (DeltaTime * 100.0f);
		if (Info.M_MaxFlyDistance <= 100.0f)
		{
			Info.M_MaxFlyDistance = 100.0f;
			RushFlyOff = false;
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
void ABellyfish::InitAttack1Data()
{

	FMonsterSkillDataTable* NewData = GetMontserSkillData(MonsterInfo.M_Skill_Type_01);

	MonsterInfo.M_Skill_Range = NewData->M_Skill_Range;
	MonsterInfo.M_Skill_Radius = NewData->M_Skill_Radius;
	
	MonsterInfo.M_Skill_Atk = NewData->M_Skill_Atk;
	MonsterInfo.M_Skill_Time = NewData->M_Skill_Time;
	MonsterInfo.M_Skill_Set_Time = NewData->M_Skill_Set_Time;
	MonsterInfo.M_Skill_Cool = NewData->M_Skill_Cool;



}
void ABellyfish::InitAttack2Data()
{
	FMonsterSkillDataTable* NewData = GetMontserSkillData(MonsterInfo.M_Skill_Type_02);

	MonsterInfo.M_Skill_Range = NewData->M_Skill_Range;
	MonsterInfo.M_Skill_Radius = NewData->M_Skill_Radius;

	MonsterInfo.M_Skill_Atk = NewData->M_Skill_Atk;
	MonsterInfo.M_Skill_Time = NewData->M_Skill_Time;
	MonsterInfo.M_Skill_Set_Time = NewData->M_Skill_Set_Time;
	MonsterInfo.M_Skill_Cool = NewData->M_Skill_Cool;
}
void ABellyfish::InitAttack3Data()
{
	FMonsterSkillDataTable* NewData = GetMontserSkillData(MonsterInfo.M_Skill_Type_03);

	MonsterInfo.M_Skill_Range = NewData->M_Skill_Range;
	MonsterInfo.M_Skill_Radius = NewData->M_Skill_Radius;

	MonsterInfo.M_Skill_Atk = NewData->M_Skill_Atk;
	MonsterInfo.M_Skill_Time = NewData->M_Skill_Time;
	MonsterInfo.M_Skill_Set_Time = NewData->M_Skill_Set_Time;
	MonsterInfo.M_Skill_Cool = NewData->M_Skill_Cool;
}
#pragma endregion Init