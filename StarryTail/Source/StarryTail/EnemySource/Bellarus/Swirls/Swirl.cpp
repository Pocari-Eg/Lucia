// Fill out your copyright notice in the Description page of Project Settings.


#include "Swirl.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "../../../PlayerSource/PlayerFSM/IreneFSM.h"
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

	Swirl_Core->SetCollisionProfileName("NoCollision");
	Swirl_Pull_Range->SetCollisionProfileName("NoCollision");

	Swirl_Core_Effect->SetAutoActivate(false);
	Swirl_Pull_Range_Effect->SetAutoActivate(false);

	bIsOnDotDamage = false;
	SwirlKeepcheck = false;
	DotDamageTimer = 0.0f;
	DotDamageTime = 0.5f;


	KeepSwirlTimer = 0.0f;
	CoreSetTimer = 0.0f;



	bIsMove = false;
	MoveDirection = FVector(0.0f, 0.0f, 0.0f);

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

	Swirl_Pull_Range->SetCapsuleRadius(SwirlRadius* 4.0f);
	Swirl_Pull_Range->SetCapsuleHalfHeight(SwirlRadius * 4.0f);


	MinDistance = SwirlRadius;
	MaxDistance = MinDistance * 4.0f;

}

void ASwirl::SwirlCoreActive(FVector MoveDirectionVal)
{
	Swirl_Core_Effect->SetActive(true, true);
	Swirl_Core->SetGenerateOverlapEvents(true);

	MoveDirection = MoveDirectionVal;
	CoreSetTimer = 0.0f;
	bIsOnSwirlCore = true;
	Swirl_Core->SetCollisionProfileName("Trigger");
	bIsMove = true;
}

void ASwirl::SwirlPullRangeActive()
{
	Swirl_Pull_Range_Effect->SetActive(true, true);
	Swirl_Pull_Range->SetGenerateOverlapEvents(true);
	SwirlKeepcheck = true;
	Swirl_Pull_Range->SetCollisionProfileName("EnemyAttack");
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
	InitSwirl(100, 4, 0.7f, 5, 10, 300, 120);
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
			float CurDistance = GetDistanceTo(Irene);
			float CurPullPower = CalcCurPullPower(CurDistance);
			if (!Irene->IreneState->IsAttackState() && !Irene->IreneState->IsDodgeState()) {
				FVector PullDirection = GetActorLocation() - Irene->GetActorLocation();
				PullDirection.Z = 0.0f;
				Irene->SetActorLocation(Irene->GetActorLocation() + (PullDirection * CurPullPower * DeltaTime));
			}
		}

	}

	if (bIsMove)
	{
		SetActorLocation(GetActorLocation() + (MoveDirection*MoveSpeed * DeltaTime));
	}
}

float ASwirl::CalcCurPullPower(float CurDistance)
{

	if (CurDistance >= MaxDistance)
	{
		return Pull_Force * 0.0f;
	}
	else if (CurDistance <= MinDistance)
	{
		return Pull_Force * 1.0f;
	}
	else {    
		float Ratio = 1.0f-((CurDistance-MinDistance) / (MaxDistance-MinDistance));
		return Pull_Force * Ratio;
	}
	

	return 0.0f;
}

