// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"
#include "../STGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../EnemySource/Morbit/Morbit.h"
// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}
	OldRadius = 0.0f;
}

void AEnemySpawnPoint::RandomSpawn()
{
	FVector2D random = FMath::RandPointInCircle(Radius); //중심 기준 300반경의 원 안에 랜덤 포인트
	STARRYLOG(Warning, TEXT("MonsterSpawn x : %f y : %f"), random.X, random.Y); //
}


void AEnemySpawnPoint::RandomSpawn(float radius)
{
	FVector2D random = FMath::RandPointInCircle(radius); //중심 기준 300반경의 원 안에 랜덤 포인트
	UE_LOG(LogTemp, Warning, TEXT("CreateBox x : %f y : %f"), random.X, random.Y); //
	GetWorld()->SpawnActor<AMorbit>(GetActorLocation() + FVector(random, 0.0f), FRotator::ZeroRotator); // 새 엑터 생성
	auto instance = Cast<USTGameInstance>(GetGameInstance());
	instance->AddEnemyCount();
}

void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawSpawnArea();
}
  
void AEnemySpawnPoint::DrawSpawnArea()
{
	//현재 Radius에 변화가 생기면 영역을 다시 그림
	if (OldRadius != Radius)
	{
		FlushPersistentDebugLines(GetWorld());
#if ENABLE_DRAW_DEBUG
		DrawDebugCircle(GetWorld(), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 50.f), 
			Radius, 40, FColor::Green, true, -1.0f, 0, 2.0f, FVector(1.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f), true);
#endif
		OldRadius = Radius;

	}


}