// Fill out your copyright notice in the Description page of Project Settings.


#include "BF_Projectile.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "../../STGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
ABF_Projectile::ABF_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = CapsuleComponent;
	Mesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh>ProjectTile_MESH(TEXT("/Game/Effect/VFX_Monster/Scientia/PS_FeatherAtk/SM_Feather.SM_Feather"));
	if (ProjectTile_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ProjectTile_MESH.Object);
	}

	CapsuleComponent->SetWorldRotation(FRotator(270.0f, 0.0f, 0.0f));
	CapsuleComponent->SetCollisionProfileName("Projectile");
	Speed = 30.0f;
	bIsFire = false;
	MoveDistance = 0.0f;

}

void ABF_Projectile::SetProjectile(float SetDamage, float SetSpeed, float SetDistance)
{
	Damage = SetDamage;
	Speed = SetSpeed;
	MaxMoveDistance = SetDistance;
	bIsFire = true;
}

// Called when the game starts or when spawned
void ABF_Projectile::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->OnComponentHit.AddDynamic(this, &ABF_Projectile::OnHit);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ABF_Projectile::OnBeginOverlap);
}

void ABF_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

void ABF_Projectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AIreneCharacter>(OtherActor))
	{
		STARRYLOG_S(Warning);
		auto Player = Cast<AIreneCharacter>(OtherActor);
		UGameplayStatics::ApplyDamage(Player, Damage, NULL, this, NULL);
		Destroy();
	}
	else {
		Destroy();
	}
}

// Called every frame
void ABF_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//2개의 벡터를 a to b 로 회전 하는 행렬 구하기


	if (bIsFire) {
		FVector ForwardVec = GetActorUpVector();
		ForwardVec.Normalize();
		SetActorLocation(GetActorLocation() + (ForwardVec * Speed * DeltaTime));

		MoveDistance += (Speed * DeltaTime);

		if (MoveDistance >= MaxMoveDistance)
		{
			Destroy();
		}
	}




	

}

