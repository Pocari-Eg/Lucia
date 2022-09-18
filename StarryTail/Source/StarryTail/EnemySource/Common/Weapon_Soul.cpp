// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Soul.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "../../STGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
AWeapon_Soul::AWeapon_Soul()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = CapsuleComponent;
	Mesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh>ProjectTile_MESH(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (ProjectTile_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ProjectTile_MESH.Object);
	}


	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CapsuleComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;

	IsHitGround = false;
}

void AWeapon_Soul::SetValue(FWeaponSoul* SetValue)
{

	Info.Drop_Speed = SetValue->Drop_Speed;
	Info.Get_Weapon_Gauge = SetValue->Get_Weapon_Gauge;
	Info.Soul_Radius_Curve = SetValue->Soul_Radius_Curve;
	Info.Spawn_Distance = SetValue->Spawn_Distance;
	Info.W_Soul_Distance = SetValue->W_Soul_Distance;
	Info.W_Soul_Speed = SetValue->W_Soul_Speed;

}

// Called when the game starts or when spawned
void AWeapon_Soul::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_Soul::OnBeginOverlap);

}

void AWeapon_Soul::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STARRYLOG_S(Warning);
	if (Cast<AIreneCharacter>(OtherActor))
	{
	
		Destroy();
	}
}

void AWeapon_Soul::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	STARRYLOG(Warning,TEXT("%s"),*Other->GetFName().ToString());


	if (Cast<AWeapon_Soul>(Other))
	{
	
	}
	else {
		IsHitGround = true;
	}
}

// Called every frame
void AWeapon_Soul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsMoveOn) {
	
		SetActorLocation(GetActorLocation() + (GetActorForwardVector() * Info.W_Soul_Speed*300 * DeltaTime));

		auto Instance = Cast<USTGameInstance>(GetGameInstance());

		//2개의 벡터를 a to b 로 회전 하는 행렬 구하기
		FVector ForwardVec = GetActorForwardVector();
		ForwardVec.Normalize();

		FVector PlayerVec = Instance->GetPlayer()->GetActorLocation() - GetActorLocation();

		PlayerVec.Normalize();

		RotationQuat = Math::VectorA2BRotation(ForwardVec, PlayerVec);
		FVector RotateVec = RotationQuat.RotateVector(ForwardVec);


		AddActorWorldRotation(RotationQuat * 0.025f);


		UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + (PlayerVec * GetDistanceTo(Instance->GetPlayer())), 300.0f, FLinearColor::Red, 0.1f, 3.0f);
		UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + (ForwardVec * 100), 300.0f, FLinearColor::Blue, 0.1f, 3.0f);
		UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + (RotateVec * GetDistanceTo(Instance->GetPlayer())), 300.0f, FLinearColor::Green, 0.1f, 3.0f);

	}
	else {
		auto Instance = Cast<USTGameInstance>(GetGameInstance());
		float distance = GetDistanceTo(Instance->GetPlayer());

		//if (distance <= Info.W_Soul_Distance * 100&& IsHitGround) {
		//	IsMoveOn = true;
		//}

	}
  
}

void AWeapon_Soul::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * 1.0f;
}

