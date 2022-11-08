// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldPoint.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "../../STGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
AShieldPoint::AShieldPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	RootComponent = CapsuleComponent;
	Particle->SetupAttachment(RootComponent);



	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CapsuleComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;

	IsHitGround = false;

	Timer = 0.0f;
}

void AShieldPoint::SetValue(FWeaponSoul* SetValue,FVector ShootDirection)
{
	Info.Move_Speed = SetValue->Drop_Speed;
	Info.Get_Distance_Gauge = SetValue->Get_Distance_Gauge;
	Info.Get_Ultimate_Guage = SetValue->Get_Ultimate_Guage;
	Info.Get_MaxUltimate_Guage = SetValue->Get_MaxUltimate_Guage;
	Info.Drop_Distance = SetValue->Drop_Distance;
	Info.Drop_Speed = SetValue->Drop_Speed;

	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	float distance = GetDistanceTo(Instance->GetPlayer());

	ProjectileMovementComponent->Velocity = ShootDirection * Info.Drop_Speed;
	//if (distance <= Info.Get_Distance_Gauge)
	//{
	//	IsMoveOn = true;
	//}
	//else {
	//	ProjectileMovementComponent->Velocity = ShootDirection * Info.Drop_Speed;

	//}


}

// Called when the game starts or when spawned
void AShieldPoint::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AShieldPoint::OnBeginOverlap);

}

void AShieldPoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AIreneCharacter>(OtherActor))
	{
		auto Irene = Cast<AIreneCharacter>(OtherActor);
		Irene->IreneAttack->SetUltimateGauge(Info.Get_Ultimate_Guage);
		Destroy();
	}
}

void AShieldPoint::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<AShieldPoint>(Other))
	{
	
	}
	else {
		IsHitGround = true;
		
	}
}

// Called every frame
void AShieldPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsMoveOn) {
	
		SetActorLocation(GetActorLocation() + (GetActorForwardVector() * Info.Move_Speed * DeltaTime));

		auto Instance = Cast<USTGameInstance>(GetGameInstance());

		//2개의 벡터를 a to b 로 회전 하는 행렬 구하기
		FVector ForwardVec = GetActorForwardVector();
		ForwardVec.Normalize();

		FVector PlayerVec = Instance->GetPlayer()->GetActorLocation() - GetActorLocation();
		PlayerVec.Z += 30.0F;
		PlayerVec.Normalize();
		
		RotationQuat = Math::VectorA2BRotation(ForwardVec, PlayerVec);
		FVector RotateVec = RotationQuat.RotateVector(ForwardVec);


		AddActorWorldRotation(RotationQuat * 0.025f);

		Info.Move_Speed += Accelation;
		//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + (PlayerVec * GetDistanceTo(Instance->GetPlayer())), 300.0f, FLinearColor::Red, 0.1f, 3.0f);
		//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + (ForwardVec * 100), 300.0f, FLinearColor::Blue, 0.1f, 3.0f);
		//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + (RotateVec * GetDistanceTo(Instance->GetPlayer())), 300.0f, FLinearColor::Green, 0.1f, 3.0f);

	}


	if (IsHitGround) {
		Timer += DeltaTime;
		if (Timer >= WaitTime) {

			auto Instance = Cast<USTGameInstance>(GetGameInstance());
				float distance = GetDistanceTo(Instance->GetPlayer());

				if (distance <= Info.Get_Distance_Gauge) {
					IsHitGround = false;
					IsMoveOn = true;
					ProjectileMovementComponent->bSimulationEnabled = false;
				}
			
		}

		if (Timer >= 10.0f) {

			Destroy();

		}
	}
  
}