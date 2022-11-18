// Fill out your copyright notice in the Description page of Project Settings.


#include "BF_MagicAttack.h"
#include"../../PlayerSource/IreneCharacter.h"
// Sets default values
ABF_MagicAttack::ABF_MagicAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Circum = CreateDefaultSubobject<UDecalComponent>(TEXT("CIRCUM"));
	Area = CreateDefaultSubobject<UDecalComponent>(TEXT("Area"));
	AttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Attack"));
	IntersectionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("INTERSECTION"));
	PlayerCheckCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PLAYERCHECK"));

	RootComponent = Root;

	Circum->SetupAttachment(RootComponent);
	Area->SetupAttachment(RootComponent);
	AttackCollision->SetupAttachment(RootComponent);
	PlayerCheckCollision-> SetupAttachment(RootComponent);
	IntersectionCollision->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> MAT_Circle(TEXT("/Game/UI/Indicator/CircleMaterial.CircleMaterial"));
	if (MAT_Circle.Succeeded())
	{
		IndicatorMat = MAT_Circle.Object;
	}

	Circum->SetRelativeLocation(FVector::ZeroVector);
	Area->SetRelativeLocation(FVector::ZeroVector);
	AttackCollision->SetRelativeLocation(FVector(1000.0f,0.0f, 0.0f));
	PlayerCheckCollision->SetRelativeLocation(FVector(1000.0f, 0.0f, 0.0f));

	IntersectionCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Root->SetWorldRotation(FRotator(90.0f, 0.0f, 0.0f));

	AttackCollision->SetCollisionProfileName("EnemyAttack");
	AttackCollision->SetGenerateOverlapEvents(false);


	PlayerCheckCollision->SetCollisionProfileName("EnemyAttack");
	PlayerCheckCollision->SetGenerateOverlapEvents(true);

	IntersectionCollision->SetCollisionProfileName("Intersection");
	IntersectionCollision->SetGenerateOverlapEvents(true);

	Circum->DecalSize.X = 5.0f;
	Area->DecalSize.X = 5.0f;

	SkillEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SkillEffect"));
	SkillEffectComponent->SetupAttachment(Root);
	SkillEffectComponent->bAutoActivate = false;
	SkillEffectComponent->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));

	bIsInPlayer = false;
}

void ABF_MagicAttack::SetMagicAttack(float Radius, float DamageVal)
{
	Circum->DecalSize.Set(10, Radius , Radius );
	Area->DecalSize.Set(10, Radius , Radius );
	AttackCollision->SetSphereRadius(Radius);
	PlayerCheckCollision->SetSphereRadius(Radius);
	IntersectionCollision->SetSphereRadius(Radius);
	Damage = DamageVal;

	PlayerCheckCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

void ABF_MagicAttack::PlayIndicator(float Val)
{
	if(AreaInstance!=nullptr)
	AreaInstance->SetScalarParameterValue("AreaValue", Val);
}

void ABF_MagicAttack::EndIndicator()
{
	Circum->SetVisibility(false);
	Area->SetVisibility(false);

}
void ABF_MagicAttack::SetActiveAttack()
{
	PlayerCheckCollision->SetGenerateOverlapEvents(false);
	AttackCollision->SetGenerateOverlapEvents(true);
	AttackCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	SkillEffectComponent->SetActive(true);
	SkillEffectComponent->SetVisibility(true);
}

bool ABF_MagicAttack::GetInPlayer()
{
	return bIsInPlayer;
}

// Called when the game starts or when spawned
void ABF_MagicAttack::BeginPlay()
{
	Super::BeginPlay();
	CircumInstance = Circum->CreateDynamicMaterialInstance();
	AreaInstance = Area->CreateDynamicMaterialInstance();
	CircumInstance->SetScalarParameterValue("Circum1Area0", 1.0f);
	AreaInstance->SetScalarParameterValue("Circum1Area0", 0.0f);

	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ABF_MagicAttack::OnBeginOverlap);
	PlayerCheckCollision->OnComponentBeginOverlap.AddDynamic(this, &ABF_MagicAttack::OnPlayerInOverlap);
	PlayerCheckCollision->OnComponentEndOverlap.AddDynamic(this, &ABF_MagicAttack::OnPlayerOutOverlap);
	SkillEffectComponent->SetTemplate(SkillEffect);
}

void ABF_MagicAttack::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene != nullptr)
	{
		STARRYLOG(Error, TEXT("Magic Player Hit"));
		UGameplayStatics::ApplyDamage(Irene, Damage, NULL, this, NULL);
		AttackCollision->SetGenerateOverlapEvents(false);
	}

}

void ABF_MagicAttack::OnPlayerInOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene != nullptr)
	{
		bIsInPlayer = true;
	}
}

void ABF_MagicAttack::OnPlayerOutOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//나간 물체가 플레이어라면 
	if (OtherComp->GetCollisionProfileName() == "Player")
	{
		bIsInPlayer = false;
	}
}

// Called every frame
void ABF_MagicAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

