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

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(CapsuleComponent);
	MeshComponent->SetupAttachment(CapsuleComponent);

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

	CapsuleComponent->SetRelativeScale3D(FVector(0.3f,0.2f,0.5f));
	MeshComponent->SetRelativeLocationAndRotation(FVector::ZeroVector,FRotator(-90.0f,0.0f,0.0f));

	MeshComponent->SetCollisionProfileName(TEXT("PlayerAttack"));
	CapsuleComponent->SetCollisionProfileName(TEXT("PlayerAttack"));

	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetEnableGravity(false);
	CapsuleComponent->SetLinearDamping(0);
	
	LifeTime = 0;
	StopTime = 1;
	BackMoveTime = 1;
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
	if(LifeTime >= StopTime + BackMoveTime)
		CapsuleComponent->AddImpulse(GetActorForwardVector() * MoveSpeed);
	if(LifeTime >= StopTime && LifeTime < StopTime + BackMoveTime)
		NewLocation -= GetActorForwardVector() * MoveSpeed/2.5f * DeltaTime;
	LifeTime += DeltaTime;
	SetActorLocation(NewLocation);		

	if (LifeTime >= Distance / MoveSpeed + StopTime + BackMoveTime*2)
	{
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
