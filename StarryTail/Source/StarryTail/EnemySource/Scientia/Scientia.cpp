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
#pragma region Init
void AScientia::InitMonsterInfo()
{
	MonsterInfo.Code = 1;

	MonsterInfo.MaxHp = 5000.0f;
	MonsterInfo.Atk = 50.0f;
	MonsterInfo.Def = 100.0f;

	MonsterInfo.BattleWalkMoveSpeed = 400.0f;

	MonsterInfo.DeadWaitTime = 3.0f;
	
	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
	MonsterInfo.EnemyRank = EEnemyRank::e_Boss;
}
void AScientia::InitCollision()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(140.0f);
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
void AScientia::InitScInfo()
{
	ScInfo.AttributeSettingTime = 1.0f;
}
#pragma endregion
#pragma region Get
FString AScientia::GetState()
{
	return State;
}
int AScientia::GetBarrierCount()
{
	return ScInfo.BarrierCount;
}
#pragma endregion
#pragma region Set
void AScientia::SetState(FString string)
{
	State = string;
}
#pragma endregion


void AScientia::BattleIdle()
{
	ScAnimInstance->PlayBattleIdleMontage();
	MonsterAIController->StopMovement();
}
void AScientia::BattleWalk()
{
	ScAnimInstance->PlayBattleWalkMontage();
}
bool AScientia::ScAttributeIsPlayerAttributeCounter()
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	auto PlayerAttribute = STGameInstance->GetPlayerAttribute();

	switch (ScInfo.CurrentAttribute)
	{
	case EAttributeKeyword::e_Fire:
		if (PlayerAttribute != EAttributeKeyword::e_Water)
			return false;
		break;
	case EAttributeKeyword::e_Water:
		if (PlayerAttribute != EAttributeKeyword::e_Thunder)
			return false;
		break;
	case EAttributeKeyword::e_Thunder:
		if (PlayerAttribute != EAttributeKeyword::e_Fire)
			return false;
		break;
	}

	return true;
}

void AScientia::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SetAttribute)
	{
		AttributeSettingTimer += DeltaTime;

		if (AttributeSettingTimer >= ScInfo.AttributeSettingTime)
		{
			auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());

			switch (STGameInstance->GetPlayerAttribute())
			{
			case EAttributeKeyword::e_Fire:
				ScInfo.CurrentAttribute = EAttributeKeyword::e_Thunder;
				break;
			case EAttributeKeyword::e_Water:
				ScInfo.CurrentAttribute = EAttributeKeyword::e_Fire;
				break;
			case EAttributeKeyword::e_Thunder:
				ScInfo.CurrentAttribute = EAttributeKeyword::e_Water;
				break;
			}
			MonsterAIController->SetPlayer();

			SetAttribute = true;
		}
	}
}
	// Called when the game starts or when spawned
void AScientia::BeginPlay()
{
	Super::BeginPlay();

}

void AScientia::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.BattleWalkMoveSpeed;
}

void AScientia::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ScAnimInstance = Cast<UScAnimInstance>(GetMesh()->GetAnimInstance());
}
