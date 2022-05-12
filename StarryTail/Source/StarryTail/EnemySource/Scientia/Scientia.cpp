// Fill out your copyright notice in the Description page of Project Settings.


#include "Scientia.h"
#include "ScAIController.h"
#include "../../STGameInstance.h"

AScientia::AScientia()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AScAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	InitMonsterInfo();
	InitCollision();
	InitMesh();
	InitAnime();

	bTestMode = false;

	HitEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Enemy/SFX_Hit");
	HpBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 380));
}
void AScientia::InitMonsterInfo()
{
	MonsterInfo.Code = 1;

	MonsterInfo.MaxHp = 5000.0f;
	MonsterInfo.Atk = 50.0f;
	MonsterInfo.Def = 100.0f;

	MonsterInfo.BattleWalkMoveSpeed = 400.0f;

	MonsterInfo.DeadWaitTime = 3.0f;

	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	auto Player = STGameInstance->GetPlayer();
	
	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
}
void AScientia::InitCollision()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(200.0f);
	GetCapsuleComponent()->SetCapsuleRadius(88.0f);
}
void AScientia::InitMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster/Scientia/BattleIdle/M_Sc_Battleidle"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()), FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
}
void AScientia::InitAnime()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님 인스턴스 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> BouldelithAnim(TEXT("/Game/BluePrint/Monster/Scientia/ScientiaAnimBlueprint"));
	if (BouldelithAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BouldelithAnim.Class);
	}
}
