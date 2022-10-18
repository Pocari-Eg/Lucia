// Fill out your copyright notice in the Description page of Project Settings.


#include "Swirl.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ASwirl::ASwirl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootPoint"));
	RootComponent = RootPoint;

	Swirl_Core = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Core"));
	Swirl_Pull_Range = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PullRange"));
	Swirl_Core_Effect= CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Core_Effect"));
	Swirl_Pull_Range_Effect=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PullRange_Effect"));

	Swirl_Core->SetupAttachment(RootComponent);
	Swirl_Pull_Range->SetupAttachment(RootComponent);

	Swirl_Core_Effect->SetupAttachment(Swirl_Core);
	Swirl_Pull_Range_Effect->SetupAttachment(Swirl_Pull_Range);

	Swirl_Core->SetGenerateOverlapEvents(false);
	Swirl_Pull_Range->SetGenerateOverlapEvents(false);

	Swirl_Core->SetCollisionProfileName("Trigger");
	Swirl_Pull_Range->SetCollisionProfileName("Trigger");

	Swirl_Core_Effect->SetAutoActivate(false);
	Swirl_Pull_Range_Effect->SetAutoActivate(false);

	bIsOnDotDamage = false;
	SwirlKeepcheck = false;
	DotDamageTimer = 0.0f;
	DotDamageTime = 0.5f;


	KeepSwirlTimer = 0.0f;
	CoreSetTimer = 0.0f;
}

void ASwirl::InitSwirl(float DamageVal, float SwirlDotDamageVal,float PullForceVal, float CoreSetTimeVal,float KeepSwirlTimeVal ,float MoveSpeedVal,float SwirlRadiusVal)
{
	Damage = DamageVal;
	Pull_Force = PullForceVal;
	CoreSetTime = CoreSetTimeVal;
	MoveSpeed = MoveSpeedVal;
	Swirl_Dot_Damage = SwirlDotDamageVal;
	SwirlRadius = SwirlRadiusVal;
	KeepSwirlTime = KeepSwirlTimeVal;

	Swirl_Core->SetCapsuleRadius(SwirlRadius);
	Swirl_Core->SetCapsuleHalfHeight(SwirlRadius);

	Swirl_Pull_Range->SetCapsuleRadius(SwirlRadius*1.8f);
	Swirl_Pull_Range->SetCapsuleHalfHeight(SwirlRadius * 1.8f);

}

void ASwirl::SwirlCoreActive()
{
	Swirl_Core_Effect->SetActive(true, true);
	Swirl_Core->SetGenerateOverlapEvents(true);


	CoreSetTimer = 0.0f;
	bIsOnSwirlCore = true;
}

void ASwirl::SwirlPullRangeActive()
{
	Swirl_Pull_Range_Effect->SetActive(true, true);
	Swirl_Pull_Range->SetGenerateOverlapEvents(true);
	SwirlKeepcheck = true;
}

void ASwirl::SwirlDestroy()
{
}

bool ASwirl::GetbIsOnDotDamage()
{
	return bIsOnDotDamage;
}

// Called when the game starts or when spawned
void ASwirl::BeginPlay()
{
	Super::BeginPlay();
	Swirl_Core->OnComponentBeginOverlap.AddDynamic(this, &ASwirl::SwirlCoreBegin);
	Swirl_Core->OnComponentEndOverlap.AddDynamic(this, &ASwirl::SwirlCoreEnd);

	Swirl_Pull_Range->OnComponentBeginOverlap.AddDynamic(this, &ASwirl::SwirlPullRangeBegin);
	Swirl_Pull_Range->OnComponentEndOverlap.AddDynamic(this, &ASwirl::SwirlPullRangeEnd);
	InitSwirl(100, 4, 50.0f, 5, 10, 20, 200);
	SwirlCoreActive();
}

void ASwirl::SwirlCoreBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AIreneCharacter>(OtherActor))
	{
		Irene = Cast<AIreneCharacter>(OtherActor);
		
		UGameplayStatics::ApplyDamage(Irene, Damage, NULL, this, NULL);
		bIsOnDotDamage = true;
	}
}

void ASwirl::SwirlCoreEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AIreneCharacter>(OtherActor))
	{
		bIsOnDotDamage = false;
		Irene = nullptr;
	}
	
	
}

void ASwirl::SwirlPullRangeBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AIreneCharacter>(OtherActor))
	{
		Irene = Cast<AIreneCharacter>(OtherActor);
		bIsOnCorePull = true;
	}
}

void ASwirl::SwirlPullRangeEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AIreneCharacter>(OtherActor))
	{
		Irene = nullptr;
		bIsOnCorePull = false;
	}
}

// Called every frame
void ASwirl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOnDotDamage)
	{
		DotDamageTimer += DeltaTime;
		if (DotDamageTimer >= DotDamageTime)
		{
			UGameplayStatics::ApplyDamage(Irene, Swirl_Dot_Damage, NULL, this, NULL);
			DotDamageTimer = 0.0f;
		}
	}

	if (bIsOnSwirlCore)
	{
		CoreSetTimer += DeltaTime;
		if (CoreSetTimer >= CoreSetTime)
		{
			bIsOnSwirlCore = false;
			CoreSetTimer = 0.0f;
			SwirlPullRangeActive();
		}
	}

	if (SwirlKeepcheck)
	{
		KeepSwirlTimer += DeltaTime;
		if (KeepSwirlTimer >= KeepSwirlTime)
		{
			Destroy();
		}

	}
	if (bIsOnCorePull)
	{
		if (Irene != nullptr)
		{
			STARRYLOG_S(Error);
			FVector PullDirection = GetActorLocation() - Irene->GetActorLocation();
			PullDirection.Z = 0.0f;
			Irene->SetActorLocation(GetActorLocation() + (PullDirection * Pull_Force* DeltaTime));
		}

	}
}

