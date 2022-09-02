// Fill out your copyright notice in the Description page of Project Settings.


#include "ST_Projectile.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "../../STGameInstance.h"
// Sets default values
AST_Projectile::AST_Projectile()
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
void AST_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AST_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetActorLocation(GetActorLocation()+(GetActorUpVector()* Speed * DeltaTime));

   auto Instance = Cast<USTGameInstance>(GetGameInstance());
   FVector ForwardVec = GetActorUpVector();
   ForwardVec.Normalize();

   FVector PlayerVec = Instance->GetPlayer()->GetActorLocation() - GetActorLocation();
   PlayerVec.Normalize();


   STARRYLOG(Error, TEXT("%f,%f,%f"), ForwardVec.X, ForwardVec.Y, ForwardVec.Z);
   STARRYLOG(Error, TEXT("%f,%f,%f"), PlayerVec.X, PlayerVec.Y, PlayerVec.Z);

   float dot = FVector::DotProduct(ForwardVec, PlayerVec);
   float AcosAngle = FMath::Acos(dot);
   float AngleDefree = FMath::RadiansToDegrees(AcosAngle);
 
   STARRYLOG(Error, TEXT("%f"), AngleDefree);
}

