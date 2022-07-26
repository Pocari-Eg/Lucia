// Fill out your copyright notice in the Description page of Project Settings.
#include "Quill.h"

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
	MeshComponent->SetRelativeScale3D(FVector(4.0f,4.0f,4.0f));
	MeshComponent->SetRelativeLocationAndRotation(FVector::ZeroVector,FRotator(0,180,0));

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
	StopTime = 1;
	BackMoveTime = 1;
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
	FVector NewLocation = GetActorLocation();
	if(!Bust && LifeTime >= StopTime + BackMoveTime)
	{
		Bust = true;
		StartBust();
	}
	if(LifeTime >= StopTime + BackMoveTime)
		CapsuleComponent->AddImpulse(GetActorForwardVector() * MoveSpeed);
	if(LifeTime >= StopTime && LifeTime < StopTime + BackMoveTime)
		NewLocation -= GetActorForwardVector() * MoveSpeed/2.5f * DeltaTime;
	LifeTime += DeltaTime;
	SetActorLocation(NewLocation);		

	if (LifeTime >= Distance / MoveSpeed + StopTime + BackMoveTime*2)
	{
		Destroy();
	}
}

void AQuill::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(Target == nullptr)
	{
		if(Cast<AMonster>(OtherActor))
		{
			UGameplayStatics::ApplyDamage(OtherActor, Strength, nullptr, this, nullptr);
			StartAttack();
		}
		else
		{
			StartAttack();
			Destroy();
		}
	}
	
	if(OtherActor == Target)
	{
		if(Cast<AMonster>(OtherActor))
		{
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
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BustParticle[0],GetActorLocation());
		break;
	case EAttributeKeyword::e_Water:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BustParticle[1],GetActorLocation());
		break;
	case EAttributeKeyword::e_Thunder:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BustParticle[2],GetActorLocation());
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

