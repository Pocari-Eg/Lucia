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

	static ConstructorHelpers::FClassFinder<AGuidedSwirl> BP_GuidedSwirl(TEXT("/Game/BluePrint/Monster/Bellarus/BP_GuidedSwirl.BP_GuidedSwirl_C"));
	if (BP_GuidedSwirl.Succeeded() && BP_GuidedSwirl.Class != NULL) {
		GuidedSwirlClass = BP_GuidedSwirl.Class;
	}
	static ConstructorHelpers::FClassFinder<ATornadoSwirl> BP_TornadoSwirl(TEXT("/Game/BluePrint/Monster/Bellarus/BP_TornadoSwirl.BP_TornadoSwirl_C"));
	if (BP_TornadoSwirl.Succeeded() && BP_TornadoSwirl.Class != NULL) {
		ATornadoSwirlClass = BP_TornadoSwirl.Class;
	}

	static ConstructorHelpers::FClassFinder<ABF_Projectile> BP_BL_Projectile(TEXT("/Game/BluePrint/Monster/Bellarus/BP_BL_Projectile.BP_BL_Projectile_C"));
	if (BP_BL_Projectile.Succeeded() && BP_BL_Projectile.Class != NULL) {
		AProjectileClass = BP_BL_Projectile.Class;
	}



	bIsTeleporting = false;
	TelePortTimer = 0.0f;

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

void ABellarus::Wing_L()
{

	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_01);

	if (AttackCheck(NewSkillData->M_Skill_Radius, NewSkillData->M_Atk_Height, NewSkillData->M_Atk_Angle, -80.0f))
	{
		auto Instance = Cast<USTGameInstance>(GetGameInstance());

		if (Instance != nullptr) {
			if (bIsDodgeTime)
			{
				//STARRYLOG(Error, TEXT("Dodge On"));
				PerfectDodgeOn();
				return;
			}
			else {


				bIsDodgeTime = false;
				PerfectDodgeOff();
				UGameplayStatics::ApplyDamage(Instance->GetPlayer(), NewSkillData->M_Skill_Atk, NULL, this, NULL);
				return;
			}
		}
	}
	else {
		PerfectDodgeOff();
	}


	
}

void ABellarus::Wing_R()
{
	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_01);

	if (AttackCheck(NewSkillData->M_Skill_Radius, NewSkillData->M_Atk_Height, NewSkillData->M_Atk_Angle, 80.0f))
	{
		auto Instance = Cast<USTGameInstance>(GetGameInstance());

		if (Instance != nullptr) {
			if (bIsDodgeTime)
			{
				//STARRYLOG(Error, TEXT("Dodge On"));
				PerfectDodgeOn();
				return;
			}
			else {


				bIsDodgeTime = false;
				PerfectDodgeOff();
				UGameplayStatics::ApplyDamage(Instance->GetPlayer(), NewSkillData->M_Skill_Atk, NULL, this, NULL);
				return;
			}
		}
	}
	else {
		PerfectDodgeOff();
	}


}

void ABellarus::Tail()
{
	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_03);

	if (AttackCheck(NewSkillData->M_Skill_Radius, NewSkillData->M_Atk_Height, NewSkillData->M_Atk_Angle, 180.0f))
	{
		auto Instance = Cast<USTGameInstance>(GetGameInstance());

		if (Instance != nullptr) {
			if (bIsDodgeTime)
			{
				//STARRYLOG(Error, TEXT("Dodge On"));
				PerfectDodgeOn();
				return;
			}
			else {


				bIsDodgeTime = false;
				PerfectDodgeOff();
				UGameplayStatics::ApplyDamage(Instance->GetPlayer(), NewSkillData->M_Skill_Atk, NULL, this, NULL);
				return;
			}
		}
	}
	else {
		PerfectDodgeOff();
	}
}




void ABellarus::BasicSwirlAttack()
{

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

void ABellarus::GuidedSwirlAttack()
{
	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_05);


	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();

	FVector RightVector = ForwardVector.RotateAngleAxis(45, FVector::UpVector);
	FVector LetfVector = ForwardVector.RotateAngleAxis(-45, FVector::UpVector);

	ForwardVector.Z = 0.0f;
	RightVector.Z = 0.0f;
	LetfVector.Z = 0.0f;
	// 총구 위치에 발사체를 스폰시킵니다.

	AGuidedSwirl* RightSwirl = GetWorld()->SpawnActor<AGuidedSwirl>(GuidedSwirlClass,
		(GetActorLocation() + (RightVector * 40)) - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		GetActorRotation()+FRotator(0.0f,45.0f,0.0f), SpawnParams);
	if (RightSwirl != nullptr)
	{
		RightSwirl->InitSwirl(NewSkillData->M_Skill_Atk, BellarusInfo.Swirl_DOT_Damage, BellarusInfo.Swirl_Pull_Force, NewSkillData->M_Skill_Set_Time,
			NewSkillData->M_Skill_Time, BellarusInfo.Swirl_MoveSpeed, 120.0f, BellarusInfo.Swirl_Explosion_Radius, BellarusInfo.Swirl_Explosion_Damage);
		RightSwirl->SwirlCoreActive(ForwardVector);
	}

	AGuidedSwirl* LeftSwirl = GetWorld()->SpawnActor<AGuidedSwirl>(GuidedSwirlClass,
		(GetActorLocation() + (LetfVector * 40)) - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		GetActorRotation() + FRotator(0.0f, -45.0f, 0.0f), SpawnParams);
	if (LeftSwirl != nullptr)
	{
		LeftSwirl->InitSwirl(NewSkillData->M_Skill_Atk, BellarusInfo.Swirl_DOT_Damage, BellarusInfo.Swirl_Pull_Force, NewSkillData->M_Skill_Set_Time, 
			NewSkillData->M_Skill_Time, BellarusInfo.Swirl_MoveSpeed, 120.0f,BellarusInfo.Swirl_Explosion_Radius, BellarusInfo.Swirl_Explosion_Damage);
		LeftSwirl->SwirlCoreActive(ForwardVector);
	}

}

void ABellarus::TornadoSwirlAttack()
{
	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_05);
	FMonsterSkillDataTable* TornadoData = GetMontserSkillData(MonsterInfo.M_Skill_Type_06);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();

	FVector RightVector = ForwardVector.RotateAngleAxis(45, FVector::UpVector);
	FVector LetfVector = ForwardVector.RotateAngleAxis(-45, FVector::UpVector);

	ForwardVector.Z = 0.0f;
	RightVector.Z = 0.0f;
	LetfVector.Z = 0.0f;
	// 총구 위치에 발사체를 스폰시킵니다.

	ATornadoSwirl* RightSwirl = GetWorld()->SpawnActor<ATornadoSwirl>(ATornadoSwirlClass,
		(GetActorLocation() + (RightVector * 500.0f)) - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		GetActorRotation() + FRotator(0.0f, -45.0f, 0.0f), SpawnParams);
	if (RightSwirl != nullptr)
	{
		RightSwirl->InitSwirl(NewSkillData->M_Skill_Atk, BellarusInfo.Swirl_DOT_Damage, BellarusInfo.Swirl_Pull_Force, NewSkillData->M_Skill_Set_Time,
			NewSkillData->M_Skill_Time, BellarusInfo.Swirl_MoveSpeed, 120.0f);
		RightSwirl->SwirlCoreActive(ForwardVector);

		
		RightSwirl->InitTornade(TornadoData->M_Skill_Atk, BellarusInfo.Tornado_DOT_Damage, BellarusInfo.Tornado_Pull_Force, TornadoData->M_Skill_Set_Time,
			TornadoData->M_Skill_Time, BellarusInfo.Swirl_MoveSpeed, 240.0f);
	}

	ATornadoSwirl* LeftSwirl = GetWorld()->SpawnActor<ATornadoSwirl>(ATornadoSwirlClass,
		(GetActorLocation() + (LetfVector * 500.0f)) - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		GetActorRotation() + FRotator(0.0f, 45.0f, 0.0f), SpawnParams);
	if (LeftSwirl != nullptr)
	{
		LeftSwirl->InitSwirl(NewSkillData->M_Skill_Atk, BellarusInfo.Swirl_DOT_Damage, BellarusInfo.Swirl_Pull_Force, NewSkillData->M_Skill_Set_Time,
			NewSkillData->M_Skill_Time, BellarusInfo.Swirl_MoveSpeed, 120.0f);
		LeftSwirl->SwirlCoreActive(ForwardVector);
		LeftSwirl->InitTornade(TornadoData->M_Skill_Atk, BellarusInfo.Tornado_DOT_Damage, BellarusInfo.Tornado_Pull_Force, TornadoData->M_Skill_Set_Time,
			TornadoData->M_Skill_Time, BellarusInfo.Swirl_MoveSpeed, 240.0f);
	}
}

void ABellarus::ProjectileAttack()
{

	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(14);


	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();

	FVector RightVector_1 = ForwardVector.RotateAngleAxis(80, FVector::UpVector);
	FVector RightVector_2 = ForwardVector.RotateAngleAxis(40, FVector::UpVector);
	FVector LetfVector_1 = ForwardVector.RotateAngleAxis(-80, FVector::UpVector);
	FVector LetfVector_2 = ForwardVector.RotateAngleAxis(-40, FVector::UpVector);


	RightVector_1.Normalize();
	RightVector_2.Normalize();
	LetfVector_1.Normalize();
	LetfVector_2.Normalize();


	// 총구 위치에 발사체를 스폰시킵니다.
	ABF_Projectile* FowardProjectile = GetWorld()->SpawnActor<ABF_Projectile>(AProjectileClass, GetActorLocation() + (ForwardVector * 100.0f), GetActorRotation(), SpawnParams);
	if (FowardProjectile)
	{
		FowardProjectile->SetProjectile(NewSkillData->M_Skill_Atk, NewSkillData->M_Skill_Time, NewSkillData->M_Skill_Radius);
	}
	ABF_Projectile* RightProjectile_1 =GetWorld()->SpawnActor<ABF_Projectile>(AProjectileClass, GetActorLocation()+(RightVector_1*100.0f), GetActorRotation()+FRotator(0.0f,80.0f,0.0f), SpawnParams);
	if (RightProjectile_1)
	{
		RightProjectile_1->SetProjectile(NewSkillData->M_Skill_Atk, NewSkillData->M_Skill_Time, NewSkillData->M_Skill_Radius);
	}
	ABF_Projectile* RightProjectile_2 = GetWorld()->SpawnActor<ABF_Projectile>(AProjectileClass, GetActorLocation() + (RightVector_2 * 100.0f), GetActorRotation() + FRotator(0.0f, 40.0f, 0.0f), SpawnParams);
	if (RightProjectile_2)
	{
		RightProjectile_2->SetProjectile(NewSkillData->M_Skill_Atk, NewSkillData->M_Skill_Time, NewSkillData->M_Skill_Radius);
	}
	ABF_Projectile* LeftProjectile_1 = GetWorld()->SpawnActor<ABF_Projectile>(AProjectileClass, GetActorLocation() + (LetfVector_1 * 100.0f), GetActorRotation() + FRotator(0.0f, -80.0f, 0.0f), SpawnParams);
	if (LeftProjectile_1)
	{
		LeftProjectile_1->SetProjectile(NewSkillData->M_Skill_Atk, NewSkillData->M_Skill_Time, NewSkillData->M_Skill_Radius);
	}
	ABF_Projectile* LeftProjectile_2 = GetWorld()->SpawnActor<ABF_Projectile>(AProjectileClass, GetActorLocation() + (LetfVector_2 * 100.0f), GetActorRotation() + FRotator(0.0f, -40.0f, 0.0f), SpawnParams);
	if (LeftProjectile_2)
	{
		LeftProjectile_2->SetProjectile(NewSkillData->M_Skill_Atk, NewSkillData->M_Skill_Time, NewSkillData->M_Skill_Radius);
	}
}

void ABellarus::TelePortStart()
{
	bIsTeleporting = true;
	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(15);
	TelePortTime = NewSkillData->M_Skill_Set_Time;
	TelePortTimer = 0.0f;
	GetMesh()->SetVisibility(false);
	GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
	SetActorLocation(TeleportLocation);


}

void ABellarus::TelePortEnd()
{
	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(15);

	bIsTeleporting = false;
	TelePortTimer = 0.0f;
	GetMesh()->SetVisibility(true);
	GetCapsuleComponent()->SetCollisionProfileName("Enemy");

	if (AttackCheck(NewSkillData->M_Skill_Radius, 300.0f, 360.0f, 0.0f))
	{
		auto Instance = Cast<USTGameInstance>(GetGameInstance());

		if (Instance != nullptr) {
			if (bIsDodgeTime)
			{
				//STARRYLOG(Error, TEXT("Dodge On"));
				PerfectDodgeOn();
				return;
			}
			else {


				bIsDodgeTime = false;
				PerfectDodgeOff();
				UGameplayStatics::ApplyDamage(Instance->GetPlayer(), NewSkillData->M_Skill_Atk, NULL, this, NULL);
				return;
			}
		}
	}

	else {

	  PerfectDodgeOff();

	}


}

void ABellarus::SwirlAttack()
{
	switch (SwirlAttackType)
	{
	case 0:
		BasicSwirlAttack();
		break;
	case 1:
		GuidedSwirlAttack();
		break;
	case 2:
		TornadoSwirlAttack();
		break;
	default:
		BasicSwirlAttack();
		break;
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
	BellarusAnimInstance->Attack.AddUObject(this, &ABellarus::TelePortStart);

	TeleportLocation = GetActorLocation();

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

	if (bIsTeleporting)
	{
		TelePortTimer += DeltaTime;
		if (TelePortTimer >= TelePortTime)
		{
			TelePortEnd();
		}
	}


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
	BellarusInfo.Swirl_Explosion_Radius = 400.0f;
	BellarusInfo.Swirl_Explosion_Damage = 400.0f;

	BellarusInfo.Tornado_DOT_Damage = 50.0f;
	BellarusInfo.Tornado_Pull_Force = 4;
}

bool ABellarus::AttackCheck(float Radius, float Hegiht, float Angle, float AttackAxis)
{
	// hitcheck======================================

	if (bTestMode)
	{
		FTransform BottomLine = GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f,GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));


		FRotator Rotation = FRotator::ZeroRotator;
		Rotation = GetActorRotation() + FRotator(0.0f, AttackAxis, 0.0f);
		Rotation.Pitch = 0;
		BottomLine.SetRotation(FQuat(Rotation));


		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Hegiht));



		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();
		if (bIsDodgeTime) {
			GetAIController()->DrawRadial(GetWorld(), BottomDebugMatrix, Radius, Angle, FColor::Green, 10, 0.1f, false, 0, 2);
			GetAIController()->DrawRadial(GetWorld(), TopDebugMatrix, Radius, Angle, FColor::Green, 10, 0.1f, false, 0, 2);
		}
		else {
			GetAIController()->DrawRadial(GetWorld(), BottomDebugMatrix, Radius, Angle, FColor::Red, 10, 0.5f, false, 0, 2);
			GetAIController()->DrawRadial(GetWorld(), TopDebugMatrix, Radius, Angle, FColor::Red, 10, 0.5f, false, 0, 2);
		}
	}

	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();
	FVector AttackDirection = ForwardVector.RotateAngleAxis(AttackAxis, FVector::UpVector);
	AttackDirection.Normalize();


	FVector Center = GetLocation();


	FVector Box = FVector(Radius, Radius, Hegiht);
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	bool bResult = GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeCapsule(Box),
		CollisionQueryParam
	);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			//플레이어 클래스 정보를 가져오고 PlayerController를 소유하고 있는가 확인
			//STARRYLOG(Warning, TEXT("%s"), *OverlapResult.GetActor()->GetName());
			AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore;
				bool bTraceResult;
				if (GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						GetWorld(),
						GetLocation(), // SphereTrace 시작 위치
						Player->GetActorLocation(), // SphereTrace 종료 위치
						5.0f,
						ETraceTypeQuery::TraceTypeQuery4,
						false,
						ActorsToIgnore,
						EDrawDebugTrace::ForDuration, // 마지막 인자값으로 시간 조절 가능
						Hits,
						true,
						FLinearColor::Red,
						FLinearColor::Green,
						1.0f
					);
				}
				else
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						GetWorld(),
						GetLocation(),
						Player->GetActorLocation(),
						5.0f,
						ETraceTypeQuery::TraceTypeQuery4,
						false,
						ActorsToIgnore,
						EDrawDebugTrace::None,
						Hits,
						true
					);
				}
				for (int i = 0; i < Hits.Num(); ++i)
				{
					//STARRYLOG(Warning,TEXT("%s"), *Hits[i].GetActor()->GetName());
					Player = Cast<AIreneCharacter>(Hits[i].Actor);
					if (Player != nullptr)
					{
						break;
					}
				}
				if (bTraceResult && !(nullptr == Player))
				{
					//2차 탐지
					//if (Monster->GetTestMode())
						//STARRYLOG(Warning, TEXT("Attack in Player SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - GetLocation();
					TargetDir = TargetDir.GetSafeNormal();


					float Radian = FVector::DotProduct(AttackDirection, TargetDir);
					//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));
					//STARRYLOG(Error, TEXT("%f"), TargetAngle);
					if (TargetAngle <= (Angle * 0.5f))
					{
						if (nullptr == Player) {
							return false;
						}

						return true;
					}

				}

			}
		}
	}

	return false;
}

#pragma endregion Init