// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"
#include "../STGameInstance.h"
#include "../EnemySource/Morbit/Morbit.h"
// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}
}


void AEnemySpawnPoint::RandomSpawn(float Radius)
{
	FVector2D random = FMath::RandPointInCircle(Radius); //�߽� ���� 300�ݰ��� �� �ȿ� ���� ����Ʈ
	UE_LOG(LogTemp, Warning, TEXT("CreateBox x : %f y : %f"), random.X, random.Y); //
	GetWorld()->SpawnActor<AMorbit>(GetActorLocation() + FVector(random, 0.0f), FRotator::ZeroRotator); // �� ���� ����
	auto instance = Cast<USTGameInstance>(GetGameInstance());
	instance->AddEnemyCount();
}
  