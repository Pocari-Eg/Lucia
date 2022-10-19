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


	MonsterInfo.Monster_Code = 3;
	InitMonsterInfo();
	InitBellarusInfo();
	InitCollision();
	InitMesh();
	InitAnime();


	bTestMode = false;

	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));

	MonsterWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	MonsterWidget->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	StackWidget->SetRelativeLocation(FVector(30.0f, 0.0f, 25.0f));


	static ConstructorHelpers::FClassFinder<ASwirl> BP_Swirl(TEXT("/Game/BluePrint/Monster/Bellarus/BP_Swirl.BP_Swirl_C"));
	if (BP_Swirl.Succeeded() && BP_Swirl.Class != NULL) {
		SwirlClass = BP_Swirl.Class;
	}

}
UBellarusAnimInstance* ABellarus::GetBellarusAnimInstance() const
{
	return BellarusAnimInstance;
}


void ABellarus::Attack()
{
	//어택 준비 애니메이션 출력

	//InitAttack1Data();
	BellarusAnimInstance->PlayAttackMontage();

	
}




void ABellarus::BasicSwirlAttack()
{
	STARRYLOG_S(Error);

	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_04);


	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();

	FVector RightVector = ForwardVector.RotateAngleAxis(75.0f, FVector::UpVector);
	FVector LetfVector = ForwardVector.RotateAngleAxis(-75.0f, FVector::UpVector);

	ForwardVector.Z = 0.0f;
	RightVector.Z = 0.0f;
	LetfVector.Z = 0.0f;
	// 총구 위치에 발사체를 스폰시킵니다.
    ASwirl* CenterSwirl =  GetWorld()->SpawnActor<ASwirl>(SwirlClass,
		(GetActorLocation()+(RightVector * 20))-FVector(0.0f,0.0f,GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		GetActorRotation(), SpawnParams);


	if (CenterSwirl!=nullptr)
	{
		CenterSwirl->InitSwirl(NewSkillData->M_Skill_Atk, BellarusInfo.Swirl_DOT_Damage, BellarusInfo.Swirl_Pull_Force, NewSkillData->M_Skill_Set_Time, NewSkillData->M_Skill_Time, BellarusInfo.Swirl_MoveSpeed, 120.0f);
		CenterSwirl->SwirlCoreActive(RightVector);

	}

	ASwirl* RightSwirl = GetWorld()->SpawnActor<ASwirl>(SwirlClass,
		(GetActorLocation() + (ForwardVector * 20)) - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		GetActorRotation(), SpawnParams);
	if (RightSwirl != nullptr)
	{
		RightSwirl->InitSwirl(NewSkillData->M_Skill_Atk, BellarusInfo.Swirl_DOT_Damage, BellarusInfo.Swirl_Pull_Force, NewSkillData->M_Skill_Set_Time, NewSkillData->M_Skill_Time, BellarusInfo.Swirl_MoveSpeed, 120.0f);
		RightSwirl->SwirlCoreActive(ForwardVector);
	}

	ASwirl* LeftSwirl = GetWorld()->SpawnActor<ASwirl>(SwirlClass,
		(GetActorLocation() + (LetfVector * 20)) - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		GetActorRotation(), SpawnParams);
	if (LeftSwirl != nullptr)
	{
		LeftSwirl->InitSwirl(NewSkillData->M_Skill_Atk, BellarusInfo.Swirl_DOT_Damage, BellarusInfo.Swirl_Pull_Force, NewSkillData->M_Skill_Set_Time, NewSkillData->M_Skill_Time, BellarusInfo.Swirl_MoveSpeed, 120.0f);
		LeftSwirl->SwirlCoreActive(LetfVector);
	}
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
	BellarusAnimInstance->Attack.AddUObject(this, &ABellarus::BasicSwirlAttack);

	
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
	MonsterInfo.M_Skill_Type_04 = NewData->M_Skill_Type_04;
	MonsterInfo.M_Skill_Type_05 = NewData->M_Skill_Type_05;
	MonsterInfo.M_Skill_Type_06 = NewData->M_Skill_Type_06;
	MonsterInfo.M_Skill_Type_07 = NewData->M_Skill_Type_07;
	MonsterInfo.M_Skill_Type_08 = NewData->M_Skill_Type_08;

	MonsterInfo.Spirit_Soul = NewData->Spirit_Soul;
	MonsterShield->SetDurabilty(NewData->M_Shield_Def);

	MonsterInfo.M_Attacked_Time = 0.5f;
	MonsterInfo.PatrolArea = 600.0f;
	MonsterInfo.M_MaxFollowTime = 5.0f;
	MonsterInfo.BattleWalkMoveSpeed = 90.0f;
	

	MonsterInfo.M_Sight_Angle = 150.0f;
	MonsterInfo.M_Sight_Radius = 500.0f;
	MonsterInfo.M_Sight_Height = 150.0f;

	//Attack Range

	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_01);


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
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster/Bellarus/mesh/M_Bl_Idle.M_Bl_Idle"));
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
	static ConstructorHelpers::FClassFinder<UAnimInstance> FrenoAnim(TEXT("/Game/BluePrint/Monster/Bellarus/BellyfishAnimBluePrint.BellyfishAnimBluePrint_C"));
	if (FrenoAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(FrenoAnim.Class);
	}
}

void ABellarus::InitBellarusInfo()
{
	BellarusInfo.Swirl_MoveSpeed = 300.0f;
	BellarusInfo.Swirl_Pull_Force = 0.7f;
	BellarusInfo.Swirl_DOT_Damage = 30.0f;

}

#pragma endregion Init