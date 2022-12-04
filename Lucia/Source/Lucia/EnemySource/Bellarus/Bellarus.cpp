// Fill out your copyright notice in the Description page of Project Settings.


#include "Bellarus.h"
#include"../../PlayerSource/IreneCharacter.h"
#include"../../PlayerSource/PlayerInstance/IreneAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../STGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

ABellarus::ABellarus()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABellarusAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	MonsterInfo.Monster_Code = 3;
	//InitMonsterInfo();
	//InitBellarusInfo();
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


	bIsRegening = false;
	RegenTimer = 0.0f;
	RegenTime = BellarusInfo.M_NShield_Time;
	bIsInSpawnRadius = false;
	AttacekdTeleportTimer = 0.0f;

	SwirlWait = false;
	//MonsterShield->SetDurabilty(MonsterInfo.M_Shield_Def);

	SwirlWaitTime = 0.0f;
	SwirlWaitTimer = 0.0f;

	MeleeAttackCount = 0;

}
UBellarusAnimInstance* ABellarus::GetBellarusAnimInstance() const
{
	return BellarusAnimInstance;
}




void ABellarus::PlayWingLAnim()
{
	IsAttackNum = 1;
	NewSkillData = GetWingData();
	BellarusAnimInstance->PlayWingLMontage();
}

void ABellarus::Wing_L()
{


	MonsterInfo.M_Skill_Cool = NewSkillData->M_Skill_Cool;
	if (AttackCheck(NewSkillData->M_Skill_Radius, NewSkillData->M_Atk_Height, 160.0f, -(160.0f / 2.0f)))
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

void ABellarus::PlayWingRAnim()
{
	IsAttackNum = 2;
	NewSkillData = GetWingData();
	BellarusAnimInstance->PlayWingRMontage();
}

void ABellarus::Wing_R()
{
	MonsterInfo.M_Skill_Cool = NewSkillData->M_Skill_Cool;
	if (AttackCheck(NewSkillData->M_Skill_Radius, NewSkillData->M_Atk_Height, 160.0f, 160.0f /2.0f))
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

void ABellarus::PlayTailAnim()
{
	IsAttackNum = 3;
	NewSkillData = GetTailData();
	BellarusAnimInstance->PlayTailMontage();
}

void ABellarus::Tail()
{
	MonsterInfo.M_Skill_Cool = NewSkillData->M_Skill_Cool;
	if (AttackCheck(NewSkillData->M_Skill_Radius, NewSkillData->M_Atk_Height, 80.0f, 180.0f))
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

	 NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_04);
	MonsterInfo.M_Skill_Cool = NewSkillData->M_Skill_Cool;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();

	FVector RightVector = ForwardVector.RotateAngleAxis(25.0f, FVector::UpVector);
	FVector LetfVector = ForwardVector.RotateAngleAxis(-25.0f, FVector::UpVector);

	ForwardVector.Z = 0.0f;
	RightVector.Z = 0.0f;
	LetfVector.Z = 0.0f;
	// 총구 위치에 발사체를 스폰시킵니다.
    ASwirl* CenterSwirl =  GetWorld()->SpawnActor<ASwirl>(SwirlClass,
		(GetActorLocation()+(RightVector * 20))-FVector(0.0f,0.0f,GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		GetActorRotation(), SpawnParams);

	
	SwirlWait = true;

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

	m_CenterSwirl = CenterSwirl;
	m_LeftSwirl = LeftSwirl;
	RightSwirl = RightSwirl;

	m_CenterSwirl->OnSwirlDestroy.AddUObject(this, &ABellarus::SwirlDestroy);
	m_LeftSwirl->OnSwirlDestroy.AddUObject(this, &ABellarus::SwirlDestroy);
	RightSwirl->OnSwirlDestroy.AddUObject(this, &ABellarus::SwirlDestroy);

}

void ABellarus::GuidedSwirlAttack()
{
	 NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_05);
	MonsterInfo.M_Skill_Cool = NewSkillData->M_Skill_Cool;

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
	SwirlWait = true;

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

	m_RightSwirl = RightSwirl;
	m_LeftSwirl = LeftSwirl;

	m_RightSwirl->OnSwirlDestroy.AddUObject(this, &ABellarus::GuidedSwirlDestory);
	m_LeftSwirl->OnSwirlDestroy.AddUObject(this, &ABellarus::GuidedSwirlDestory);

}

void ABellarus::TornadoSwirlAttack()
{
	 NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_05);
	FMonsterSkillDataTable* TornadoData = GetMontserSkillData(MonsterInfo.M_Skill_Type_06);
	MonsterInfo.M_Skill_Cool = TornadoData->M_Skill_Cool;
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
	SwirlWait = true;


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


	m_LeftSwirl = LeftSwirl;
	RightSwirl = RightSwirl;


	m_LeftSwirl->OnSwirlDestroy.AddUObject(this, &ABellarus::TornadoSwirlDestroy);
	RightSwirl->OnSwirlDestroy.AddUObject(this, &ABellarus::TornadoSwirlDestroy);
}

void ABellarus::RunTelePort()
{
	GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
	CalcTelePort();
	Cast<ABellarusAIController>(GetAIController())->SetTelePortKey(true);
}

void ABellarus::CalcTelePort()
{
	int index = -1;
	float MaxDistance = 0;

	auto instance = Cast<USTGameInstance>(GetGameInstance());

	int size = TeleportPoint.Num();
	if (size != 0)
	{
		for (int i = 0; i < size; i++)
		{
			float curDistane = TeleportPoint[i]->GetDistanceTo(instance->GetPlayer());
			if (curDistane > MaxDistance)
			{
				MaxDistance = curDistane;
				index = i;
			}
		}
	}

	CurTeleportPoint = TeleportPoint[index];
	TeleportLocation = TeleportPoint[index]->GetActorLocation();
	TeleportLocation.Z = this->GetActorLocation().Z;
}

void ABellarus::PlayFeatherAnim()
{
	BellarusAnimInstance->PlayFeatherMontage();
}

void ABellarus::ProjectileAttack()
{
	 NewSkillData = GetMontserSkillData(14);
	if (MonsterInfo.Monster_Code == 3)
	{
		NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_05);
	}
	else if (MonsterInfo.Monster_Code == 4)
	{
		NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_07);
	}
	MonsterInfo.M_Skill_Cool = NewSkillData->M_Skill_Cool;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();

	FVector RightVector_1 = ForwardVector.RotateAngleAxis(20, FVector::UpVector);
	FVector RightVector_2 = ForwardVector.RotateAngleAxis(10, FVector::UpVector);
	FVector LetfVector_1 = ForwardVector.RotateAngleAxis(-20, FVector::UpVector);
	FVector LetfVector_2 = ForwardVector.RotateAngleAxis(-10, FVector::UpVector);


	RightVector_1.Normalize();
	RightVector_2.Normalize();
	LetfVector_1.Normalize();
	LetfVector_2.Normalize();


	// 총구 위치에 발사체를 스폰시킵니다.
	ABF_Projectile* FowardProjectile = GetWorld()->SpawnActor<ABF_Projectile>(AProjectileClass, GetActorLocation()+FVector(0.0f,0.0f, BellarusInfo.ProjectileOffest) + (ForwardVector * 100.0f), GetActorRotation(), SpawnParams);
	if (FowardProjectile)
	{
		FowardProjectile->SetProjectile(NewSkillData->M_Skill_Atk, NewSkillData->M_Skill_Time, NewSkillData->M_Skill_Radius);
	}
	ABF_Projectile* RightProjectile_1 =GetWorld()->SpawnActor<ABF_Projectile>(AProjectileClass, GetActorLocation() + FVector(0.0f, 0.0f, BellarusInfo.ProjectileOffest) +(RightVector_1*100.0f), GetActorRotation()+FRotator(0.0f,20,0.0f), SpawnParams);
	if (RightProjectile_1)
	{
		RightProjectile_1->SetProjectile(NewSkillData->M_Skill_Atk, NewSkillData->M_Skill_Time, NewSkillData->M_Skill_Radius);
	}
	ABF_Projectile* RightProjectile_2 = GetWorld()->SpawnActor<ABF_Projectile>(AProjectileClass, GetActorLocation() + FVector(0.0f, 0.0f, BellarusInfo.ProjectileOffest) + (RightVector_2 * 100.0f), GetActorRotation() + FRotator(0.0f, 10, 0.0f), SpawnParams);
	if (RightProjectile_2)
	{
		RightProjectile_2->SetProjectile(NewSkillData->M_Skill_Atk, NewSkillData->M_Skill_Time, NewSkillData->M_Skill_Radius);
	}
	ABF_Projectile* LeftProjectile_1 = GetWorld()->SpawnActor<ABF_Projectile>(AProjectileClass, GetActorLocation() + FVector(0.0f, 0.0f, BellarusInfo.ProjectileOffest) + (LetfVector_1 * 100.0f), GetActorRotation() + FRotator(0.0f, -20, 0.0f), SpawnParams);
	if (LeftProjectile_1)
	{
		LeftProjectile_1->SetProjectile(NewSkillData->M_Skill_Atk, NewSkillData->M_Skill_Time, NewSkillData->M_Skill_Radius);
	}
	ABF_Projectile* LeftProjectile_2 = GetWorld()->SpawnActor<ABF_Projectile>(AProjectileClass, GetActorLocation() + FVector(0.0f, 0.0f, BellarusInfo.ProjectileOffest) + (LetfVector_2 * 100.0f), GetActorRotation() + FRotator(0.0f, -10, 0.0f), SpawnParams);
	if (LeftProjectile_2)
	{
		LeftProjectile_2->SetProjectile(NewSkillData->M_Skill_Atk, NewSkillData->M_Skill_Time, NewSkillData->M_Skill_Radius);
	}
}

void ABellarus::PlayTelePortAnim()
{
	IsAttackNum = 4;
	BellarusAnimInstance->PlayStartTelePortMontage();
}

void ABellarus::TelePortStart()
{
	GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
	MonsterWidget->SetVisibility(false);
	StackWidget->SetVisibility(false);

	CurTeleportPoint->TelePortSignActive();

	bIsTeleporting = true;
	NewSkillData= GetMontserSkillData(15);
	if (MonsterInfo.Monster_Code == 3)
	{
		 NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_06);
	}
	else if (MonsterInfo.Monster_Code == 4)
	{
		NewSkillData= GetMontserSkillData(MonsterInfo.M_Skill_Type_08);
	}


	TelePortTime = NewSkillData->M_Skill_Set_Time;
	TelePortTimer = 0.0f;
	//GetMesh()->SetVisibility(false);


	SetActorLocation(TeleportLocation);

}

void ABellarus::TelePortEnd()
{

	NewSkillData = GetMontserSkillData(15);
	if (MonsterInfo.Monster_Code == 3)
	{
		NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_06);
	}
	else if (MonsterInfo.Monster_Code == 4)
	{
		NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_08);
	}
	MonsterInfo.M_Skill_Cool = NewSkillData->M_Skill_Cool;
	
	RotationToPlayerDirection();
	MonsterWidget->SetVisibility(true);
	StackWidget->SetVisibility(true);
	BellarusAnimInstance->PlayEndTelePortMontage();



	TelePortEndEvent();
	bIsTeleporting = false;
	TelePortTimer = 0.0f;


	GetCapsuleComponent()->SetCollisionProfileName("Enemy");

	OutSpawnRadiusTimer = 0.0f;
	AttacekdTeleportTimer = 0.0f;



}

void ABellarus::TelePortAttackCheck()
{


	auto Instance = Cast<USTGameInstance>(GetGameInstance());


	//2개의 벡터를 a to b 로 회전 하는 행렬 구하기
	//GetMesh()->SetVisibility(true);

	if (AttackCheck(NewSkillData->M_Skill_Radius, 300.0f, 360.0f, 0.0f))
	{

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

void ABellarus::ShieldRegening()
{
	bIsRegening = true;
	RegenTimer = 0.0f;
	RegenTime = BellarusInfo.M_NShield_Time;
}

void ABellarus::ShieldRegen()
{
	bIsRegening = false;
	RegenTimer = 0.0f;
	RegenTime = BellarusInfo.M_NShield_Time;

	MonsterShield->ShieldRegen();
	GetAIController()->SetShieldKey(true);
	OnBarrierChanged.Broadcast();
}

void ABellarus::PlaySwirlAnim()
{
	BellarusAnimInstance->PlaySwirlMontage();
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


bool ABellarus::ProjectileCheck()
{
	int count = 0;
	for (ASwirl* Swirl : TActorRange<ASwirl>(GetWorld()))
	{
		count++;
	}
	for (ABF_Projectile* Swirl : TActorRange<ABF_Projectile>(GetWorld()))
	{
		count++;
	}

	return count == 0 ? true : false;
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
		if (NewSkillData != nullptr && NewSkillData->M_Skill_Type == 1)
		{
			AddMeleeAttackCount();
		}
		else {
			InitMeleeAttackCount();
		}

		AttackEnd.Broadcast();
		Cast<ABellarusAIController>(GetAIController())->SetTraceTime(0.0f);
		});
	BellarusAnimInstance->AttackedEnd.AddLambda([this]() -> void {
		bIsAttacked = false;
		AttackedEnd.Broadcast();
		DeathCheck();
		});
	BellarusAnimInstance->Death.AddLambda([this]() -> void {
		if (bIsDead)
		{
			SetActorHiddenInGame(true);
			bDeadWait = true;
			SetActorEnableCollision(false);
			BellarusAnimInstance->Montage_Stop(500.f, BellarusAnimInstance->GetCurrentActiveMontage());
		}
		});
	BellarusAnimInstance->TailAttack.AddUObject(this, &ABellarus::Tail);
	BellarusAnimInstance->WingLAttack.AddUObject(this, &ABellarus::Wing_L);
	BellarusAnimInstance->WingRAttack.AddUObject(this, &ABellarus::Wing_R);
	BellarusAnimInstance->SwirlAttack.AddUObject(this, &ABellarus::SwirlAttack);
	BellarusAnimInstance->FeatherAttack.AddUObject(this, &ABellarus::ProjectileAttack);
	BellarusAnimInstance->TelePortStart.AddUObject(this, &ABellarus::TelePortStartEvent);
	BellarusAnimInstance->TelePortAttack.AddUObject(this, &ABellarus::TelePortAttackCheck);
	BellarusAnimInstance->OnGroggyEnd.AddUObject(this, &AMonster::DeathCheck);
	TeleportLocation = GetActorLocation();

	GroggyEnd.AddUObject(this, &ABellarus::RunTelePort);
	//Perfect Dodge
	BellarusAnimInstance->DodgeTimeOn.AddLambda([this]() -> void {
		DodgeTimeOn.Broadcast();
		});
	BellarusAnimInstance->DodgeTimeOff.AddLambda([this]() -> void {
		DodgeTimeOff.Broadcast();
		CurTeleportPoint->TelePortSignDeactivate();
		PerfectDodgeOff();
		});

	SetSpawnPos();
	SetBattleState();
	Cast<ABellarusAIController>(GetAIController())->SetTraceTime(0.0f);


	auto instance = Cast<USTGameInstance>(GetGameInstance());
	if (instance != nullptr)
	{
		instance->SetCurBossMonster(this);
	}
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


	BlSoundInstance = NewObject<UBlSoundInstance>(this);
	BlSoundInstance->Init();
	BellarusAnimInstance = Cast<UBellarusAnimInstance>(GetMesh()->GetAnimInstance());
	BellarusAnimInstance->Init(this);


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
float ABellarus::GetFirstJugdeRadius()
{
	return BellarusInfo.FirstJudgeRadius;
}
float ABellarus::GetSecondJugdeRadius()
{
	return BellarusInfo.SecondJudgeRadius;
}
float ABellarus::GetCalibrationRadius()
{
	return BellarusInfo.CalibrationRadius;
}
float ABellarus::GetCheckTime()
{
	return BellarusInfo.B_CheckTime;
}
FMonsterSkillDataTable* ABellarus::GetWingData()
{
	FMonsterSkillDataTable* SkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_01);
	return SkillData;
}
FMonsterSkillDataTable* ABellarus::GetTailData()
{
	FMonsterSkillDataTable* SkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_03);
	return SkillData;
}
FMonsterSkillDataTable* ABellarus::GetSwirlData()
{
	FMonsterSkillDataTable* SkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_04);

	return SkillData;
}
FMonsterSkillDataTable* ABellarus::GetFeatherData()
{
	FMonsterSkillDataTable* SkillData = GetMontserSkillData(14);
	return SkillData;
}
FMonsterSkillDataTable* ABellarus::GetTornado()
{
	FMonsterSkillDataTable* SkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_06);
	return SkillData;
}
FMonsterSkillDataTable* ABellarus::GetGuidedSwirlData()
{
	FMonsterSkillDataTable* SkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_05);
	return SkillData;
}
UBlSoundInstance* ABellarus::GetBlSound()
{
	return BlSoundInstance;
}
void ABellarus::InitMonsterInfo()
{
	MonsterInfo.Monster_Rank = EEnemyRank::e_Raid;


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
	

	MonsterInfo.M_Sight_Angle = 360.0f;
	MonsterInfo.M_Sight_Radius = 1000;
	MonsterInfo.M_Sight_Height = 1000;

	//Attack Range

	MonsterInfo.S_Attack_Time = 8.0f;
	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
	MonsterInfo.KnockBackPower = 50.0f;
	MonsterInfo.DeadWaitTime = 1.0f;

	MonsterInfo.TraceRange = 1000.0f;

	MonsterInfo.M_AttackPercent = 80.0f;

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;

	MonsterInfo.RotationRate = 0.025f;

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
	if (bIsRegening)
	{
		RegenTimer += DeltaTime;
		if (RegenTimer >= RegenTime)
		{
			ShieldRegen();
		}
	}

	//teleport
	//float distance = (GetAIController()->GetSpawnPos() - GetActorLocation()).Size();
	//if (distance < BellarusInfo.SpawnRadius)
	//{
	//	OutSpawnRadiusTimer = 0.0f;
	//}
	//else {
	//	if (!GetIsAttackCool()&&GetAIController()->GetIsBattleState()) {
	//		OutSpawnRadiusTimer += DeltaTime;
	//		if (OutSpawnRadiusTimer >= BellarusInfo.OutSpawnRadiusTime)
	//		{
	//			SetBattleState();
	//			SetTelePortLocation(GetAIController()->GetSpawnPos());
	//			Cast<ABellarusAIController>(GetAIController())->SetTelePortKey(true);
	//		}
	//	}
	//	else {
	//		OutSpawnRadiusTimer = 0.0f;
	//	}
	//}


	//	if (!GetIsAttackCool() && GetAIController()->GetIsBattleState()) {
	//		AttacekdTeleportTimer += DeltaTime;
	//		if (AttacekdTeleportTimer >= BellarusInfo.AttacekdTeleportTime)
	//		{
	//			SetBattleState();

	//			auto Instance = Cast<USTGameInstance>(GetGameInstance());
	//			SetTelePortLocation(Instance->GetPlayer()->GetActorLocation()+FVector(10.0f,10.0f,10.0f));
	//			Cast<ABellarusAIController>(GetAIController())->SetTelePortKey(true);
	//		}
	//	}
	//	else {
	//		AttacekdTeleportTimer = 0.0f;
	//	}

		if (TornadoWait)
		{
			SwirlWaitTimer += DeltaTime;
			if (SwirlWaitTimer >= SwirlWaitTime)
			{
				TornadoWait = false;
				SwirlWait = false;
			}
		}
		if (bIsDodgeTime)
		{
			DodgeCheck();
		}
}
void ABellarus::InitAnime()
{
	//애니메이션 모드 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님 인스턴스 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> FrenoAnim(TEXT("/Game/BluePrint/Monster/Bellarus/BellarusAnimBluePrint.BellarusAnimBluePrint_C"));
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
	BellarusInfo.FirstJudgeRadius = 3000.0f;
}

bool ABellarus::AttackCheck(float Radius, float Height, float Angle, float AttackAxis)
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
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Height));



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


	FVector Box = FVector(Radius, Radius, Height);
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

void ABellarus::IsDodgeTimeOn()
{
	bIsDodgeTime = true;
}

void ABellarus::IsDodgeTimeOff()
{
	bIsDodgeTime = false;
	IsAttackNum = -1;
}

void ABellarus::SwirlDestroy()
{
	STARRYLOG(Error, TEXT("SwirlDestroy"));
	m_LeftSwirl = nullptr;
	m_RightSwirl = nullptr;
	m_CenterSwirl = nullptr;

	SwirlWait = false;
}

void ABellarus::GuidedSwirlDestory()
{
	STARRYLOG(Error, TEXT("GuidedSwirlDestroy"));
	m_LeftSwirl = nullptr;
	m_RightSwirl = nullptr;

	SwirlWait = false;

}

void ABellarus::TornadoSwirlDestroy()
{

	STARRYLOG(Error, TEXT("TornadoDestroy"));
	m_LeftSwirl = nullptr;
	m_RightSwirl = nullptr;
	m_CenterSwirl = nullptr;

	FMonsterSkillDataTable* TornadoData = GetMontserSkillData(MonsterInfo.M_Skill_Type_06);
	SwirlWaitTime = TornadoData->M_Skill_Time;
	SwirlWaitTimer = 0.0f;
	TornadoWait = true;
}

void ABellarus::AddMeleeAttackCount()
{
	MeleeAttackCount++;
}

int ABellarus::GetMeleeAttackCount()
{
	return MeleeAttackCount;
}

void ABellarus::InitMeleeAttackCount()
{
	MeleeAttackCount = 0;
}

void ABellarus::SetSecondPhase()
{
	MonsterInfo.Monster_Code = 4;
	InitMonsterInfo();
	OnSecondPhaseEvent();
	PlayGroggyAnim();
	MonsterAIController->Groggy();
	MonsterShield->ShieldRegen();
	GetAIController()->SetShieldKey(true);
	OnBarrierChanged.Broadcast();
}

void ABellarus::DodgeCheck()
 {
	switch (IsAttackNum)
	{
	case 1:
		if (AttackCheck(NewSkillData->M_Skill_Radius, NewSkillData->M_Atk_Height, 160.0f, -(160.0f / 2.0f)))
		{
			
			if (bIsDodgeTime)
			{
				//STARRYLOG(Error, TEXT("Dodge On"));
				PerfectDodgeOn();
				return;
			}
			
		}
		else {
			PerfectDodgeOff();
		}
		break;
	case 2:
		if(AttackCheck(NewSkillData->M_Skill_Radius, NewSkillData->M_Atk_Height, 160.0f, 160.0f / 2.0f))
		{

			if (bIsDodgeTime)
			{
				//STARRYLOG(Error, TEXT("Dodge On"));
				PerfectDodgeOn();
				return;
			}

		}
		else {
			PerfectDodgeOff();
		}
		break;
	case 3:
		if(AttackCheck(NewSkillData->M_Skill_Radius, NewSkillData->M_Atk_Height, 80.0f, 180.0f))
		{

			if (bIsDodgeTime)
			{
				//STARRYLOG(Error, TEXT("Dodge On"));
				PerfectDodgeOn();
				return;
			}

		}
		else {
			PerfectDodgeOff();
		}
		break;
	case 4:
		if (AttackCheck(NewSkillData->M_Skill_Radius, 300.0f, 360.0f, 0.0f))
		{

			if (bIsDodgeTime)
			{
				//STARRYLOG(Error, TEXT("Dodge On"));
				PerfectDodgeOn();
				return;
			}

		}
		else {
			PerfectDodgeOff();
		}
		break;
	default:
		break;
	}
}

#pragma endregion Init