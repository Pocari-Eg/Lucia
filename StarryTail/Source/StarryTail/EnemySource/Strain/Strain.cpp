// Fill out your copyright notice in the Description page of Project Settings.


#include "Strain.h"
#include"../../PlayerSource/IreneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../STGameInstance.h"
#include "Kismet/GameplayStatics.h"


AStrain::AStrain()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AStrainAIController::StaticClass();
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
    SkillSetTimer = 0.0f;
	SkillAttackTimer = 0.0f;
	IntersectionTimer = 0.0f;
	static ConstructorHelpers::FClassFinder<AST_MagicAttack> BP_MAGICATTACK(TEXT("/Game/BluePrint/Monster/Strain/BP_ST_MagicAttack.BP_ST_MagicAttack_C")); 
	if (BP_MAGICATTACK.Succeeded() && BP_MAGICATTACK.Class != NULL) {
		MagicAttackClass=BP_MAGICATTACK.Class;
	}


	M_MaxFlyDistance = 100.0f;
	DodgeTimePercent = 10.0f;
}
UStrainAnimInstance* AStrain::GetStrainAnimInstance() const
{
	return StrainAnimInstance;
}

void AStrain::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
}

void AStrain::Attack()
{
	//어택 준비 애니메이션 출력
	StrainAnimInstance->PlayAttackSignMontage();
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	AttackPosition = STGameInstance->GetPlayer()->GetActorLocation();
	AttackPosition.Z = AttackPosition.Z - 80.0f;

	if (IntersectionCheck())
	{
		IsCloseOtherAttack = true;
	}
	else {
		Skill_Setting();
	}
}

void AStrain::Skill_Setting()
{
	DodgeTime = MonsterInfo.M_Skill_Set_Time - (MonsterInfo.M_Skill_Set_Time / 100.0f) * DodgeTimePercent;

	STARRYLOG(Error, TEXT("%f"), DodgeTime);

	IsSkillSet = true;
	Magic_CircleComponent->SetActive(true);
	Magic_CircleComponent->SetVisibility(true);
	MagicAttack = GetWorld()->SpawnActor<AST_MagicAttack>(MagicAttackClass, AttackPosition, FRotator::ZeroRotator);
	MagicAttack->SetMagicAttack(MonsterInfo.M_Skill_Radius,MonsterInfo.M_Skill_Atk);


}

void AStrain::Skill_Set()
{

	IsSkillSet = false;
	Magic_CircleComponent->SetActive(false);
	Magic_CircleComponent->SetVisibility(false);
	SkillSetTimer = 0.0;
	//스킬셋 애니메이션 해제

	Skill_Attack();
	StrainAnimInstance->PlayAttackMontage();
}

void AStrain::PlayRunAnim()
{
	StrainAnimInstance->PlayRunMontage();
}

void AStrain::Skill_Attack()
{
	
	IsSkillAttack = true;
	MagicAttack->EndIndicator();
	MagicAttack->SetActiveAttack();

}

void AStrain::Skill_AttackEnd()
{
	IsSkillAttack = false;
	SkillAttackTimer = 0.0f;
	MagicAttack->Destroy();
	AttackEnd.Broadcast();
}

bool AStrain::IntersectionCheck()
{
	float DetectRadius = MonsterInfo.M_Skill_Radius * 1.5f;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	bool bResult = GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
		OverlapResults,
		AttackPosition,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel14,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);
	DrawDebugSphere(GetWorld(), AttackPosition, DetectRadius, 16, FColor::Red, false, 0.2f);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			AST_MagicAttack* OtherAttack = Cast<AST_MagicAttack>(OverlapResult.GetActor());

			float Distance = (AttackPosition - OtherAttack->GetActorLocation()).Size();
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


void AStrain::BeginPlay()
{
	Super::BeginPlay();

	MonsterAnimInstance = StrainAnimInstance;

	if (StrainAnimInstance == nullptr)
		return;
	//애니메이션 몽타주 종료시 호출
	StrainAnimInstance->AttackEnd.AddLambda([this]() -> void {
		bIsAttacking = false;
		AttackEnd.Broadcast();
		STARRYLOG_S(Error);
		});
	StrainAnimInstance->AttackedEnd.AddLambda([this]() -> void {
		bIsAttacked = false;
		AttackedEnd.Broadcast();
		});
	StrainAnimInstance->Death.AddLambda([this]() -> void {
		if (bIsDead)
		{
			bDeadWait = true;
			SetActorEnableCollision(false);
			StrainAnimInstance->Montage_Stop(500.f, StrainAnimInstance->GetCurrentActiveMontage());
			
		
		}

		});
	StrainAnimInstance->Attack.AddUObject(this, &AStrain::Attack);


	Magic_CircleComponent->SetTemplate(Magic_Circle);
	SoundInstance->SetHitSound("event:/StarryTail/Enemy/SFX_Hit");



}

void AStrain::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
}

void AStrain::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	StrainAnimInstance = Cast<UStrainAnimInstance>(GetMesh()->GetAnimInstance());
}

#pragma region Init
float AStrain::GetFlyDistance()
{
	return M_Fly_Distance;
}
void AStrain::SetFlyDistance(float Distance)
{
	M_Fly_Distance = Distance;
}
void AStrain::InitMonsterInfo()
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

	M_Run_Distance = 450.0f;
	M_Run_Time = 3.0f;
	M_Attacked_Time = 0.5f;
	MonsterInfo.M_AttackPercent = 80.0f;
}

void AStrain::InitCollision()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(110);
	GetCapsuleComponent()->SetCapsuleRadius(50.0f);
}

void AStrain::InitMesh()
{
	//메쉬 변경 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/MonsterDummy/Strain/Mesh/M_Bk_Idle1.M_Bk_Idle1"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, 270.0f, 0.0f));

	float Scale = FMath::RandRange(0.9f, 1.1f);

	GetMesh()->SetRelativeScale3D(FVector(Scale, Scale, Scale));
}
// Called every frame
void AStrain::Tick(float DeltaTime)
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
			if (SkillSetTimer >= DodgeTime)
			{
				auto Instance = Cast<USTGameInstance>(GetGameInstance());
				Instance->GetPlayer()->IreneAttack->SetIsPerfectDodge(true);
			}
			if (SkillSetTimer >= MonsterInfo.M_Skill_Set_Time)
			{
				auto Instance = Cast<USTGameInstance>(GetGameInstance());
				Instance->GetPlayer()->IreneAttack->SetIsPerfectDodge(false);
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
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + M_Fly_Distance));
	}
	else {
		if (MagicAttack != nullptr) {
			MagicAttack->Destroy();
		}
	}
}
void AStrain::InitAnime()
{
	//애니메이션 모드 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님 인스턴스 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> FrenoAnim(TEXT("/Game/BluePrint/Monster/Strain/StrainAnimBluePrint.StrainAnimBluePrint_C"));
	if (FrenoAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(FrenoAnim.Class);
	}
}
#pragma endregion Init