// Fill out your copyright notice in the Description page of Project Settings.
#include "Quill.h"

#include "PhysXInterfaceWrapperCore.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "StarryTail/EnemySource/Monster.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

// Sets default values
AQuill::AQuill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(CapsuleComponent);
	MeshComponent->SetupAttachment(CapsuleComponent);

	const ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Quill(TEXT("/Game/Effect/VFX_Irene/Feather/Feather/Mash/Sm_Feather.Sm_Feather"));
	if(SM_Quill.Succeeded())
	{
		MeshComponent->SetStaticMesh(SM_Quill.Object);
	}
	const ConstructorHelpers::FObjectFinder<UMaterialInstance>MT_Quill(TEXT("/Game/Model/Irene/Material/MI_Irene_Pen.MI_Irene_Pen"));
	if(MT_Quill.Succeeded())
	{
		MeshComponent->SetMaterial(0,MT_Quill.Object);
	}

	CapsuleComponent->SetCapsuleRadius(15);
	CapsuleComponent->SetCapsuleHalfHeight(15);
	MeshComponent->SetRelativeScale3D(FVector(10.0f,10.0f,10.0f));
	MeshComponent->SetRelativeLocationAndRotation(FVector::ZeroVector,FRotator(0,180,90));

	MeshComponent->SetCollisionProfileName(TEXT("PlayerAttack"));
	CapsuleComponent->SetCollisionProfileName(TEXT("PlayerAttack"));

	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetEnableGravity(false);
	CapsuleComponent->SetLinearDamping(0);

	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_FireBust(TEXT("/Game/Effect/VFX_Irene/Feather/Bust/PS_Feather_Ex_Fire.PS_Feather_Ex_Fire"));
	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_WaterBust(TEXT("/Game/Effect/VFX_Irene/Feather/Bust/PS_Feather_Ex_Water.PS_Feather_Ex_Water"));
	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_ThunderBust(TEXT("/Game/Effect/VFX_Irene/Feather/Bust/PS_Feather_Ex_Tunder.PS_Feather_Ex_Tunder"));
	if(PS_FireBust.Succeeded() && PS_WaterBust.Succeeded() && PS_ThunderBust.Succeeded())
	{
		BustParticle.Add(PS_FireBust.Object);
		BustParticle.Add(PS_WaterBust.Object);
		BustParticle.Add(PS_ThunderBust.Object);
	}	
	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_FireAttack(TEXT("/Game/Effect/VFX_Irene/Feather/Attact/Ps_Feather_At_F.Ps_Feather_At_F"));
	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_WaterAttack(TEXT("/Game/Effect/VFX_Irene/Feather/Attact/Ps_Feather_At_W.Ps_Feather_At_W"));
	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_ThunderAttack(TEXT("/Game/Effect/VFX_Irene/Feather/Attact/Ps_Feather_At_T.Ps_Feather_At_T"));
	if(PS_FireAttack.Succeeded() && PS_WaterAttack.Succeeded() && PS_ThunderAttack.Succeeded())
	{
		AttackParticle.Add(PS_FireAttack.Object);
		AttackParticle.Add(PS_WaterAttack.Object);
		AttackParticle.Add(PS_ThunderAttack.Object);
	}

	Bust = false;
	LifeTime = 0;
	AutoPossessAI = EAutoPossessAI::Spawned;
}

void AQuill::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);
}
void AQuill::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}

// Called when the game starts or when spawned
void AQuill::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQuill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	
	LifeTime += DeltaTime;
	
	if(!Bust)
	{
		Bust = true;
		TargetLocation = Irene->GetActorLocation()+Irene->GetActorForwardVector()*Distance;
		StartBust();
	}
	
	MoveTarget();
	LookAtTarget();

	if (LifeTime >= 0.7f)
	{
		Destroy();
	}
}

void AQuill::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if(Target == nullptr || OtherActor == Target)
	{
		const auto Monster = Cast<AMonster>(OtherActor);
		if(Monster)
		{
			if(Monster->GetIsManaShieldActive())
				Irene->IreneData.CurrentEnergy+=10;
			if(Irene->IreneData.CurrentEnergy > Irene->IreneData.MaxScrollEnergy)
				Irene->IreneData.CurrentEnergy = Irene->IreneData.MaxScrollEnergy;
			UGameplayStatics::ApplyDamage(OtherActor, Strength, nullptr, this, nullptr);
			StartAttack();
		}		
	}
}

void AQuill::StartBust()
{
	switch (Attribute)
	{
	case EAttributeKeyword::e_Fire:
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BustParticle[0],GetActorLocation());
		break;
	case EAttributeKeyword::e_Water:
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BustParticle[1],GetActorLocation());
		break;
	case EAttributeKeyword::e_Thunder:
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BustParticle[2],GetActorLocation());
		break;
		default: break;
	}
}
void AQuill::StartAttack()
{
	switch (Attribute)
	{
	case EAttributeKeyword::e_Fire:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),AttackParticle[0],GetActorLocation());
		break;
	case EAttributeKeyword::e_Water:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),AttackParticle[1],GetActorLocation());
		break;
	case EAttributeKeyword::e_Thunder:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),AttackParticle[2],GetActorLocation());
		break;
	default: break;
	}
}

void AQuill::LookAtTarget()
{
	if(Target != nullptr)
	{
		const auto TargetMonster = Cast<AMonster>(Target);
		if(TargetMonster->GetHp() > 0)
		{
			const FVector BonePosition = TargetMonster->GetMesh()->GetSocketLocation(TEXT("Bip001-Head"));
			const FVector MorbitBonePosition = TargetMonster->GetMesh()->GetSocketLocation(TEXT("Bone004"));

			FRotator Z = FRotator::ZeroRotator;
			if(BonePosition != TargetMonster->GetMesh()->GetComponentLocation())
				Z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),BonePosition);
			else
				Z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),MorbitBonePosition);
			SetActorRotation(FRotator(Z.Pitch,Z.Yaw,0));
		}
	}
	else
	{
		FRotator Z = FRotator::ZeroRotator;
		Z = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),TargetLocation);
		SetActorRotation(FRotator(Z.Pitch,Z.Yaw,0));
	}
}
void AQuill::MoveTarget()
{
	//float Y = FMath::Sin(FMath::DegreesToRadians(LifeTime));
	const float Y2 = (LifeTime*LifeTime+2)/10+10;

	if(IsRightPos)
		SetActorLocation(GetActorLocation()+GetActorForwardVector()*30+GetActorRightVector()*Y2);
	else
		SetActorLocation(GetActorLocation()+GetActorForwardVector()*30+GetActorRightVector()*-Y2);
}

