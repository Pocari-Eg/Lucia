// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "ScAIController.h"
#include "Scientia.h"

// Sets default values
APiece::APiece()
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
}
void APiece::StartDrop()
{
	MoveDir = -FVector::UpVector;
	ProjectileMovementComponent->Velocity = (MoveDir * MoveSpeed);
}
void APiece::SetAttribute(EAttributeKeyword Attribute)
{
	PieceAttribute = Attribute;
}
void APiece::SetEffect()
{
	switch (PieceAttribute)
	{
	case EAttributeKeyword::e_Fire:
		DropEffect = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DropFireEffect, GetActorLocation() + FVector(0, 0, -1000));
		break;
	case EAttributeKeyword::e_Water:
		DropEffect = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DropWaterEffect, GetActorLocation() + FVector(0, 0, -1000));
		break;
	case EAttributeKeyword::e_Thunder:
		DropEffect = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DropThunderEffect, GetActorLocation() + FVector(0, 0, -1000));
		break;
	}
}
void APiece::SetDamage(float Value)
{
	Damage = Value;
}
EAttributeKeyword APiece::GetAttribute()
{
	return PieceAttribute;
}
void APiece::InitCollision()
{
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = Collision;
	Collision->SetCapsuleHalfHeight(100);
	Collision->SetCapsuleRadius(30);
	Collision->BodyInstance.SetCollisionProfileName(TEXT("Piece"));
}
void APiece::InitMesh()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));

	if (SphereVisualAsset.Succeeded())
	{
		Mesh->SetStaticMesh(SphereVisualAsset.Object);
	}

	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetWorldScale3D(FVector(1.0f));
}

void APiece::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsDrop)
	{
		WaitTimer += DeltaTime;

		if (WaitTimer >= WaitTime)
		{
			StartDrop();
			bIsDrop = true;
		}
	}
}
void APiece::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (Cast<AIreneCharacter>(Other))
	{
		auto Player = Cast<AIreneCharacter>(Other);
		UGameplayStatics::ApplyDamage(Player, Damage, NULL, this, NULL);
	}
	else if (Cast<AScientia>(Other))
	{
		auto Scientia = Cast<AScientia>(Other);
		auto ScAIController = Cast<AScAIController>(Scientia->GetController());
		UGameplayStatics::ApplyDamage(Scientia, Damage, NULL, this, NULL);
		ScAIController->Attacked();
	}
	Destroy();
}

