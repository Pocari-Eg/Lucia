// Fill out your copyright notice in the Description page of Project Settings.
#include "Quill.h"

#include "StarryTail/EnemySource/Monster.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

// Sets default values
AQuill::AQuill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

    const ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Quill(TEXT("/Engine/BasicShapes/Cone.Cone"));
	if(SM_Quill.Succeeded())
	{
		MeshComponent->SetStaticMesh(SM_Quill.Object);
	}

	const ConstructorHelpers::FObjectFinder<UMaterial>MT_Quill(TEXT("/Game/Model/Irene/Quill/MT_Quill.MT_Quill"));
	if(MT_Quill.Succeeded())
	{
		MeshComponent->SetMaterial(0,MT_Quill.Object);
	}
	
	MeshComponent->SetRelativeScale3D(FVector(0.3f,0.2f,0.5f));
	MeshComponent->SetCollisionProfileName(TEXT("PlayerAttack"));

	SetRootComponent(MeshComponent);
	CapsuleComponent->SetupAttachment(MeshComponent);
	CapsuleComponent->SetCollisionProfileName(TEXT("PlayerAttack"));
		
	LifeTime = 0;
}

// Called when the game starts or when spawned
void AQuill::BeginPlay()
{
	Super::BeginPlay();	

	auto Material = MeshComponent->GetMaterial(0);

	DynamicMaterial = UMaterialInstanceDynamic::Create(Material,NULL);
	MeshComponent->SetMaterial(0, DynamicMaterial);

	ColorTimeDelegate.BindUFunction(this, FName("SetColor"));
	GetWorld()->GetTimerManager().SetTimerForNextTick(ColorTimeDelegate);
}

// Called every frame
void AQuill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	
	LifeTime += DeltaTime;

	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorUpVector() * MoveSpeed * DeltaTime;
	LifeTime += DeltaTime;
	SetActorLocation(NewLocation);
		

	if (LifeTime >= Distance / MoveSpeed) {
		STARRYLOG(Error,TEXT("Life Destroy"));
		Destroy();

	}
}

void AQuill::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(Target == nullptr)
	{
		if(Cast<AMonster>(OtherActor))
		{
			UGameplayStatics::ApplyDamage(OtherActor, Strength, nullptr, this, nullptr);
		}
		else
		{
			Destroy();

		}
	}
	
	if(OtherActor == Target)
	{
		if(Cast<AMonster>(OtherActor))
		{
			UGameplayStatics::ApplyDamage(OtherActor, Strength, nullptr, this, nullptr);
		}
	}
}

void AQuill::SetColor()
{
	FVector Color;
	switch (Attribute)
	{
	case EAttributeKeyword::e_Fire:
		Color = FVector(1,0,0);
		break;
	case EAttributeKeyword::e_Water:
		Color = FVector(0,0,1);
		break;
	case EAttributeKeyword::e_Thunder:
		Color = FVector(1,0,1);
		break;
	default: ;
	}
	DynamicMaterial->SetVectorParameterValue(TEXT("Color"), Color);
}
