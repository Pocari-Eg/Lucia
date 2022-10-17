// Fill out your copyright notice in the Description page of Project Settings.


#include "Bellarus.h"
#include"../../PlayerSource/IreneCharacter.h"
#include"../../PlayerSource/PlayerInstance/IreneAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../STGameInstance.h"
#include "Kismet/GameplayStatics.h"


ABellarus::ABellarus()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABellarusAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	MonsterInfo.Monster_Code = 1;
	InitMonsterInfo();
	InitCollision();
	InitMesh();
	InitAnime();


	bTestMode = false;

	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));

	MonsterWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	MonsterWidget->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	StackWidget->SetRelativeLocation(FVector(30.0f, 0.0f, 25.0f));

	

	


	DodgeTimePercent = 10.0f;


}
UBellarusAnimInstance* ABellarus::GetBellarusAnimInstance() const
{
	return BellarusAnimInstance;
}


void ABellarus::Attack()
{
	//어택 준비 애니메이션 출력

	InitAttack1Data();
	BellarusAnimInstance->PlayAttackMontage();

	
}




void ABellarus::BeginPlay()
{
	Super::BeginPlay();



	MonsterShield->InitShieldEffect(MonsterInfo.MaxStackCount);

	MonsterAnimInstance = BellarusAnimInstance;

	if (BellarusAnimInstance == nullptr)
		return;
	//애니메이션 몽타주 종료시 호출
	BellarusAnimInstance->AttackEnd.AddLambda([this]() -> void {
		bIsAttacking = false;
		AttackEnd.Broadcast();
		});
	BellarusAnimInstance->AttackedEnd.AddLambda([this]() -> void {
		bIsAttacked = false;
		AttackedEnd.Broadcast();
		});
	BellarusAnimInstance->Death.AddLambda([this]() -> void {
		if (bIsDead)
		{
			bDeadWait = true;
			SetActorEnableCollision(false);
			BellarusAnimInstance->Montage_Stop(500.f, BellarusAnimInstance->GetCurrentActiveMontage());
		}
		});
	BellarusAnimInstance->Attack.AddUObject(this, &ABellarus::Attack);

	
	SetNormalState();
}

void ABellarus::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
	
}

void ABellarus::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	

	BellarusAnimInstance = Cast<UBellarusAnimInstance>(GetMesh()->GetAnimInstance());
}

#pragma region Init
float ABellarus::GetFlyDistance()
{
	//return Info.M_Fly_Distance;
	return 1;
}
float ABellarus::GetMaxFlyDistance()
{
	//return Info.M_Fly_Distance;
	return 1;
}

void ABellarus::SetFlyDistance(float Distance)
{
	//Info.M_Fly_Distance = Distance;
}
void ABellarus::InitMonsterInfo()
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


	MonsterInfo.M_Attacked_Time = 0.5f;
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

	MonsterInfo.S_Attack_Time = 8.0f;
	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;

	
	MonsterInfo.KnockBackPower = 50.0f;
	MonsterInfo.DeadWaitTime = 1.0f;

	MonsterInfo.TraceRange = 1000.0f;

	MonsterInfo.M_AttackPercent = 80.0f;

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
}

void ABellarus::InitCollision()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(110);
	GetCapsuleComponent()->SetCapsuleRadius(50.0f);
}

void ABellarus::InitMesh()
{
	//메쉬 변경 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster/Bellyfish/Mesh/M_b_idle.M_b_idle"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, 270.0f, 0.0f));

	float Scale = FMath::RandRange(0.9f, 1.1f);

	GetMesh()->SetRelativeScale3D(FVector(Scale, Scale, Scale));
}


void ABellarus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}
void ABellarus::InitAnime()
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