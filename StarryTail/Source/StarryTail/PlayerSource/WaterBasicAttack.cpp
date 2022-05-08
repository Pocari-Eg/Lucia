// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterBasicAttack.h"
#include "../EnemySource/Monster.h"

// Sets default values
AWaterBasicAttack::AWaterBasicAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	const ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	if(Mesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(Mesh.Object);
		MeshComponent->SetCollisionProfileName(TEXT("PlayerAttack"));
		MeshComponent->SetGenerateOverlapEvents(true);
		MeshComponent->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));
		SetRootComponent(MeshComponent);
	}
	LifeTime = 0;
}

// Called when the game starts or when spawned
void AWaterBasicAttack::BeginPlay()
{
	Super::BeginPlay();
	Irene = Cast<AIreneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

// Called every frame
void AWaterBasicAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LifeTime+=DeltaTime;
	SetActorRelativeLocation(GetActorLocation()+GetActorForwardVector()*DeltaTime*3000);
	if(LifeTime >= 0.5f)
		Destroy();
}
void AWaterBasicAttack::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (IsValid(OtherActor))
	{
		FDamageEvent DamageEvent;

		const auto Mob = Cast<AMonster>(OtherActor);
		if (Mob != nullptr)
		{
			Mob->SetAttackedInfo(false, 0, EAttackedDirection::Right);
		}
		if(IsValid(Mob))
		{
			UGameplayStatics::ApplyDamage(Mob, Irene->IreneData.Strength, nullptr, Irene, nullptr);
			Destroy();
		}
	}
}

void AWaterBasicAttack::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);
}
void AWaterBasicAttack::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}
