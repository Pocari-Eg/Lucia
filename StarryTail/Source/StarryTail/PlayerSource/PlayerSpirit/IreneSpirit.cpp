// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneSpirit.h"
#include "IreneSpiritAnimInstance.h"
#include "../IreneCharacter.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../../STGameInstance.h"
#include "../PlayerFSM/IreneFSM.h"

// Sets default values
AIreneSpirit::AIreneSpirit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 콜라이더 설정
	GetCapsuleComponent()->InitCapsuleSize(25.0f, 80.0f);

	// 스켈레톤 메쉬 설정
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMesh(TEXT("/Game/Animation/Irene/Idle.Idle"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -80), FRotator(0, 270, 0));
		//GetMesh()->SetRelativeScale3D(FVector(8.5f,8.5f,8.5f));

		// 무기
		if (GetMesh()->DoesSocketExist(TEXT("hand_rSwordSocket")))
		{
			Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Sword(TEXT("/Game/Animation/Irene/Weapon/Sword.Sword"));

			if (SK_Sword.Succeeded())
			{
				WeaponMesh = SK_Sword.Object;
			}
			Weapon->SetSkeletalMesh(WeaponMesh);
			Weapon->SetupAttachment(GetMesh(), TEXT("hand_rSwordSocket"));
		}
		
		// 블루프린트 애니메이션 적용
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ConstructorHelpers::FClassFinder<UAnimInstance>CharacterAnimInstance(TEXT("/Game/Animation/Irene/Animation/BP/BP_SpiritAnimation.BP_SpiritAnimation_C"));

		if (CharacterAnimInstance.Succeeded())
			GetMesh()->SetAnimClass(CharacterAnimInstance.Class);
	}

	MeshVisibilityCoolTime = 0.35f;
	AttackCount = 0;
}

void AIreneSpirit::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	IreneSpiritAnim = Cast<UIreneSpiritAnimInstance>(GetMesh()->GetAnimInstance());

	IreneSpiritAnim->OnSpiritAttackHitCheck.AddUObject(this, &AIreneSpirit::AttackCheck);
}

// Called when the game starts or when spawned
void AIreneSpirit::BeginPlay()
{
	Super::BeginPlay();
	Irene = Cast<AIreneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	IreneSpiritAnim->Init(Irene);
}

// Called every frame
void AIreneSpirit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AIreneSpirit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIreneSpirit::DestroySpiritTimer(float Time)
{
	if(DestroyWaitHandle.IsValid())
	{
		Irene->GetWorld()->GetTimerManager().ClearTimer(DestroyWaitHandle);
		DestroyWaitHandle.Invalidate();
	}
	GetWorld()->GetTimerManager().SetTimer(DestroyWaitHandle, this, &AIreneSpirit::DestroySpirit, Time, false);
}
void AIreneSpirit::DestroySpirit()
{
	//Irene->IreneSpirit = nullptr;
	Irene->GetMesh()->SetVisibility(true,true);
	Destroy();
}

void AIreneSpirit::AttackCheck()
{
	// 노티파이 AttackHitCheck 도달 시 실행
	// TArray<FHitResult> MonsterList;
	// bool bResult = false;
	//
	// const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetBasicAttackDataTableName()));
	// Irene->IreneAttack->SetStackCount(AttackTable->Stack_Count);
	// const FVector BoxSize = FVector(50, 50, AttackTable->Attack_Distance_1);
	// 	
	// const FCollisionQueryParams Params(NAME_None, false, Irene);
	// bResult = GetWorld()->SweepMultiByChannel(
	// MonsterList,
	// GetActorLocation() + (GetActorForwardVector()*(AttackTable->Attack_Distance_1-50.0f)),
	// GetActorLocation() + (GetActorForwardVector()*(AttackTable->Attack_Distance_1-50.0f)),
	// FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
	// ECollisionChannel::ECC_GameTraceChannel1,
	// FCollisionShape::MakeBox(BoxSize),
	// Params);
	//
	// // 그리기 시작
	// #if ENABLE_DRAW_DEBUG
	// const FVector TraceVec = GetActorForwardVector();
	// const FVector Center = GetActorLocation() + (GetActorForwardVector()*(AttackTable->Attack_Distance_1-50.0f));
	// const FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	// const FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	// constexpr float DebugLifeTime = 5.0f;
	// DrawDebugBox(GetWorld(), Center, BoxSize, CapsuleRot, DrawColor, false, DebugLifeTime);
	// #endif
	//
	// Irene->IreneAttack->SendDamage(bResult, MonsterList);
}