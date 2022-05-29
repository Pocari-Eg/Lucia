// Fill out your copyright notice in the Description page of Project Settings.


#include "Feather.h"
#include "../../STGameInstance.h"

AFeather::AFeather()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitCollision();
	InitMesh();

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(Collision);
	ProjectileMovementComponent->MaxSpeed = MoveSpeed;
	// ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	InitialLifeSpan = 3.0f;
}
void AFeather::InitCollision()
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = Collision;
	Collision->InitSphereRadius(20.f);
	Collision->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
	Collision->BodyInstance.SetCollisionProfileName(TEXT("Feather"));
}
void AFeather::InitMesh()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));
	
	if (SphereVisualAsset.Succeeded())
	{
		Mesh->SetStaticMesh(SphereVisualAsset.Object);
	}

	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetWorldScale3D(FVector(0.3f));
}
void AFeather::SetMoveDir(FVector Direction)
{
	ProjectileMovementComponent->Velocity = (Direction * MoveSpeed);
}

void AFeather::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AFeather::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (Cast<AIreneCharacter>(Other))
	{
		auto Player = Cast<AIreneCharacter>(Other);
		UGameplayStatics::ApplyDamage(Player, Damage, NULL, this, NULL);
		Destroy();
	}
}

