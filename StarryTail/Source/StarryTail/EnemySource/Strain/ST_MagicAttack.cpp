// Fill out your copyright notice in the Description page of Project Settings.


#include "ST_MagicAttack.h"
#include"../../PlayerSource/IreneCharacter.h"
// Sets default values
AST_MagicAttack::AST_MagicAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Circum = CreateDefaultSubobject<UDecalComponent>(TEXT("CIRCUM"));
	Area = CreateDefaultSubobject<UDecalComponent>(TEXT("Area"));
	AttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Attack"));
	RootComponent = Root;

	Circum->SetupAttachment(RootComponent);
	Area->SetupAttachment(RootComponent);
	AttackCollision->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> MAT_Circle(TEXT("/Game/UI/Indicator/CircleMaterial.CircleMaterial"));
	if (MAT_Circle.Succeeded())
	{
		IndicatorMat = MAT_Circle.Object;
	}

	Circum->SetRelativeLocation(FVector::ZeroVector);
	Area->SetRelativeLocation(FVector::ZeroVector);
	AttackCollision->SetRelativeLocation(FVector(1000.0f,0.0f, 0.0f));
	Root->SetWorldRotation(FRotator(90.0f, 0.0f, 0.0f));

	AttackCollision->SetCollisionProfileName("EnemyAttack");
	AttackCollision->SetGenerateOverlapEvents(false);

	Circum->DecalSize.X = 5.0f;
	Area->DecalSize.X = 5.0f;

	SkillEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SkillEffect"));
	SkillEffectComponent->SetupAttachment(Root);
	SkillEffectComponent->bAutoActivate = false;
	SkillEffectComponent->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));
}

void AST_MagicAttack::SetMagicAttack(float Radius, float DamageVal)
{
	Circum->DecalSize.Set(5, Radius * 2.0f, Radius * 2.0f);
	Area->DecalSize.Set(5, Radius * 2.0f, Radius * 2.0f);
	AttackCollision->SetSphereRadius(Radius* 2.0f);
	Damage = DamageVal;
}

void AST_MagicAttack::PlayIndicator(float Val)
{
	AreaInstance->SetScalarParameterValue("AreaValue", Val);
}

void AST_MagicAttack::EndIndicator()
{
	Circum->SetVisibility(false);
	Area->SetVisibility(false);

}

void AST_MagicAttack::SetActiveAttack()
{
	AttackCollision->SetGenerateOverlapEvents(true);
	AttackCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	SkillEffectComponent->SetActive(true);
	SkillEffectComponent->SetVisibility(true);
}

// Called when the game starts or when spawned
void AST_MagicAttack::BeginPlay()
{
	Super::BeginPlay();
	CircumInstance = Circum->CreateDynamicMaterialInstance();
	AreaInstance = Area->CreateDynamicMaterialInstance();
	CircumInstance->SetScalarParameterValue("Circum1Area0", 1.0f);
	AreaInstance->SetScalarParameterValue("Circum1Area0", 0.0f);

	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &AST_MagicAttack::OnBeginOverlap);

	SkillEffectComponent->SetTemplate(SkillEffect);
}

void AST_MagicAttack::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene != nullptr)
	{
		STARRYLOG(Error, TEXT("Magic Player Hit"));
		UGameplayStatics::ApplyDamage(Irene, Damage, NULL, this, NULL);
		AttackCollision->SetGenerateOverlapEvents(false);
	}

}

// Called every frame
void AST_MagicAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

