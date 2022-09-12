// Fill out your copyright notice in the Description page of Project Settings.


#include "Homing_Projectile.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "../../STGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
AHoming_Projectile::AHoming_Projectile()
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
	Speed = 30.0f;
}

// Called when the game starts or when spawned
void AHoming_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoming_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetActorLocation(GetActorLocation()+(GetActorUpVector()* Speed * DeltaTime));

   auto Instance = Cast<USTGameInstance>(GetGameInstance());

   //2개의 벡터를 a to b 로 회전 하는 행렬 구하기
   FVector ForwardVec = GetActorUpVector();
   ForwardVec.Normalize();

   FVector PlayerVec = Instance->GetPlayer()->GetActorLocation() - GetActorLocation();

   PlayerVec.Normalize();


   STARRYLOG(Error, TEXT("%f,%f,%f"), ForwardVec.X, ForwardVec.Y, ForwardVec.Z);
   STARRYLOG(Error, TEXT("%f,%f,%f"), PlayerVec.X, PlayerVec.Y, PlayerVec.Z);

   RotationQuat=Math::VectorA2BRotation(ForwardVec, PlayerVec);
  FVector RotateVec = RotationQuat.RotateVector(ForwardVec);


  


   UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation()+(PlayerVec* GetDistanceTo(Instance->GetPlayer())), 300.0f, FLinearColor::Red, 0.1f, 3.0f);
   UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + (ForwardVec*100), 300.0f, FLinearColor::Blue, 0.1f, 3.0f);
   UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + (RotateVec * GetDistanceTo(Instance->GetPlayer())), 300.0f, FLinearColor::Green, 0.1f, 3.0f);


  
}

