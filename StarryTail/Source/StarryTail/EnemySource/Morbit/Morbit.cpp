// Fill out your copyright notice in the Description page of Project Settings.

#include "Morbit.h"
#include "../../IreneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../EnemyAnimInstance.h"
#include "MbAIController.h"

// Sets default values
AMorbit::AMorbit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMbAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	InitMorbitInfo();

	InitCollision();
	InitMesh();
	InitAnime();

	bTestMode = false;
}

void AMorbit::InitMorbitInfo()
{	
	MorbitInfo.Name = FName(TEXT("M_Mb"));
	MorbitInfo.Hp = 100.0f;
	MorbitInfo.Atk = 100.0f;
	MorbitInfo.Def = 100.0f;

	AttributeDef.Normal = 80.0f;
	AttributeDef.Pyro = 15.0f;
	AttributeDef.Hydro = 0.0f;
	AttributeDef.Electro = 5.0f;

	MorbitInfo.MoveSpeed = 100.0f;
	MorbitInfo.BattleWalkMoveSpeed = 150.0f;
	MorbitInfo.ViewAngle = 120.0f;
	MorbitInfo.ViewRange = 200.0f;
}
void AMorbit::InitCollision()
{
	Collision = GetCapsuleComponent();
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(53.0f);
	GetCapsuleComponent()->SetCapsuleRadius(34.0f);
}
void AMorbit::InitMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster_Walk/Dummy_Walk.Dummy_Walk"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -55.0f), FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(50.0f, 50.0f, 50.0f));
}
void AMorbit::InitAnime()
{
	//애니메이션 모드 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님 인스턴스 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> MorbitAnim(TEXT("/Game/Animation/EnemyAnimBlueprint"));
	if (MorbitAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(MorbitAnim.Class);
	}
}
//error code

void AMorbit::CalcAttributeDefType()
{
	TMap<EAttributeKeyword, float> AttributeDefMap;

	TArray<float> DefList;

	AttributeDefMap.Add(EAttributeKeyword::e_None, AttributeDef.Normal);
	AttributeDefMap.Add(EAttributeKeyword::e_Fire, AttributeDef.Pyro);
	AttributeDefMap.Add(EAttributeKeyword::e_Water, AttributeDef.Hydro);
	AttributeDefMap.Add(EAttributeKeyword::e_Thunder, AttributeDef.Electro);
	
	AttributeDefMap.ValueSort([](float A, float B) {
		return A > B;
		});
	for (auto& Elem : AttributeDefMap)
	{
		//log
		if (bTestMode)
		{
			STARRYLOG(Warning, TEXT("AttributeDef : %f"), Elem.Value);
		}
		DefList.Add(Elem.Value);
	}
	MorbitInfo.MainAttributeDef.Add(AttributeDefMap.begin().Key());

	for (auto Elem : DefList)
	{
		//속성 방어력이 같은지
		if (DefList[0] == Elem)
		{
			//같은 요소가 있다면 등록된 맵을 돌면서 모든 Value값을 체크
			for (auto& Map : AttributeDefMap)
			{
				if (Map.Value == Elem)
				{
					//log
					if (bTestMode)
					{
						switch (Map.Key)
						{
						case EAttributeKeyword::e_None:
							STARRYLOG(Log, TEXT("MainAttributeDef : Normal"));
							break;
						case EAttributeKeyword::e_Fire:
							STARRYLOG(Log, TEXT("MainAttributeDef : Pyro"));
							break;
						case EAttributeKeyword::e_Water:
							STARRYLOG(Log, TEXT("MainAttributeDef : Hydro"));
							break;
						case EAttributeKeyword::e_Thunder:
							STARRYLOG(Log, TEXT("MainAttributeDef : Electro"));
							break;
						}
					}
					if (Map.Key == AttributeDefMap.begin().Key())
						continue;
					MorbitInfo.MainAttributeDef.Add(Map.Key);
				}
			}
			//모든 Value값을 체크했기 때문에 실행종료
			DefList.Empty();
			AttributeDefMap.Empty();
			return;
		}
	}

	DefList.Empty();
	AttributeDefMap.Empty();
}

bool AMorbit::GetTestMode()
{
	return bTestMode;
}
float AMorbit::GetViewAngle()
{
	return MorbitInfo.ViewAngle;
}
float AMorbit::GetViewRange()
{
	return MorbitInfo.ViewRange;
}

void AMorbit::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = MorbitInfo.MoveSpeed;
}
void AMorbit::BattleWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = MorbitInfo.BattleWalkMoveSpeed;
}
void AMorbit::BattleIdle()
{
	
}
void AMorbit::Attack()
{
	if (bIsAttacking)
		return;

	MorbitAnimInstance->PlayMeleeAttackMontage();

	bIsAttacking = true;
}


// Called when the game starts or when spawned
void AMorbit::BeginPlay()
{
	Super::BeginPlay();

	CalcAttributeDefType();
}

// Called every frame
void AMorbit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMorbit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMorbit::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = MorbitInfo.MoveSpeed;
}

void AMorbit::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MorbitAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	//애니메이션 몽타주 종료시 호출
	if(bIsAttacking)
		MorbitAnimInstance->OnMontageEnded.AddDynamic(this, &AMorbit::OnAttackMontageEnded);
	if (bIsAttacked)
		MorbitAnimInstance->OnMontageEnded.AddDynamic(this, &AMorbit::OnAttackedMontageEnded);
	//피격시 호출
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AMorbit::OnAttacked);
}

void AMorbit::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;

	AttackEnd.Broadcast();
}
void AMorbit::OnAttackedMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacked = false;
	
	AttackedEnd.Broadcast();
}
void AMorbit::OnAttacked(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//액터 이름 확인
	if(bTestMode)
		STARRYLOG(Warning, TEXT("Morbit Attacked : %s"), *OtherActor->GetName());

	auto Player = Cast<AIreneCharacter>(OtherActor);
	if (nullptr == Player)
	{
		STARRYLOG(Warning, TEXT("Not Attacked by Player"));
		return;
	}

	auto MbAIController = Cast<AMbAIController>(GetController());
	if (nullptr == MbAIController)
	{
		STARRYLOG(Warning, TEXT("Failed Load MbAIController"));
		return;
	}

	MbAIController->Attacked(Player);

	bIsAttacked = true;
	// CalcDamage(Player->GetAttribute(), Player->GetATK());
}