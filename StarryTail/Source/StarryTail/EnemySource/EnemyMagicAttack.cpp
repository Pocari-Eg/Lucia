// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMagicAttack.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


// Sets default values
AEnemyMagicAttack::AEnemyMagicAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 0.5f;

	//임시용 액터 탐색
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), actors);

	for (int i = 0; i < actors.Num(); i++)
	{
		Player = Cast<AIreneCharacter>(actors[i]);
		if (Player != nullptr)
		{
			break;
		}
	}

	//콜리전 설정
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = Collision;
	Collision->InitSphereRadius(40.0f);
	Collision->SetCollisionProfileName(TEXT("EnemyAttack"));

	//메쉬 설정

	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}


	//이펙트 생성
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	//해당 컴포넌트의 자식으로 지정
	OurParticleSystem->SetupAttachment(RootComponent);
	OurParticleSystem->bAutoActivate = true;
	//생성시 위치 지정
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
}

// Called when the game starts or when spawned
void AEnemyMagicAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyMagicAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//플레이어로 향하는 방향벡터
	FVector MoveDirection = Player->GetActorLocation() - GetActorLocation();
	//속도에 따라 이동
	FVector newLocation = GetTransform().GetLocation() + (MoveDirection * Speed * DeltaTime);

	RootComponent->SetWorldLocation(newLocation);
}

void AEnemyMagicAttack::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//콜리전 충돌시 실행
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyMagicAttack::OnCollisionOverlap);
}

void AEnemyMagicAttack::OnCollisionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Other = Cast<AIreneCharacter>(OtherActor);

	if (Other == nullptr)
		return;

	STARRYLOG(Warning, TEXT("Collision Detect : %s"), *Other->GetName());
	Destroy();
}
void AEnemyMagicAttack::SetParticleAsset(UParticleSystem* ParticleAsset)
{
	OurParticleSystem->SetTemplate(ParticleAsset);
}
