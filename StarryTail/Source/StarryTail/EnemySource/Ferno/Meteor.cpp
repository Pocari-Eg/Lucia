// Fill out your copyright notice in the Description page of Project Settings.


#include "Meteor.h"
#include"../../PlayerSource/IreneCharacter.h"

// Sets default values
AMeteor::AMeteor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 구체를 단순 콜리전 표현으로 사용합니다.
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    // 구체의 콜리전 반경을 설정합니다.
    CollisionComponent->InitSphereRadius(0.5);
    // 루트 컴포넌트를 콜리전 컴포넌트로 설정합니다.
    RootComponent = CollisionComponent;




    // 이 컴포넌트를 사용하여 프로젝타일의 무브먼트를 구동시킵니다.
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
    ProjectileMovementComponent->InitialSpeed = 3;
    ProjectileMovementComponent->MaxSpeed = 3;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = false;
    ProjectileMovementComponent->Bounciness = 0.0f;

    DestroyTimer = 0.0f;
    bIsHit = false;
}

// Called when the game starts or when spawned
void AMeteor::BeginPlay()
{
	Super::BeginPlay();
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMeteor::OnBeginOverlap);
}

// Called every frame
void AMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (bIsHit)
    {
        DestroyTimer += DeltaTime;
        if (DestroyTimer >= 1.0f)
        {
            Destroy();
        }
    }
}

void AMeteor::FireInDirection(const FVector& ShootDirection,const float Speed,const float SetDamageValue)
{
    SetSpeed(Speed);
    SetDamage(SetDamageValue);
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AMeteor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    auto Irene = Cast<AIreneCharacter>(OtherActor);
    if (Irene != nullptr)
    {
        UGameplayStatics::ApplyDamage(Irene, Damage, NULL, this, NULL);
        STARRYLOG(Error, TEXT("Meteor Player Hit"));
        Destroy();
    }
    CollisionComponent->SetGenerateOverlapEvents(false);
}

void AMeteor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    bIsHit = true;
    CollisionComponent->SetGenerateOverlapEvents(false);
}

void AMeteor::SetDamage(float SetDamage)
{
    this->Damage = SetDamage;
}

void AMeteor::SetSpeed(float Speed)
{
    ProjectileMovementComponent->InitialSpeed = Speed;
    ProjectileMovementComponent->MaxSpeed = Speed;
}

