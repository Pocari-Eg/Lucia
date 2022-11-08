// Fill out your copyright notice in the Description page of Project Settings.


#include "LabMagic.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ALabMagic::ALabMagic()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootPoint"));
	MagicAOECollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AREACEHCK"));
	ExplosionSignEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionSign_Particle"));
	ExplosionEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionParticle"));
	ShockEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShockParticle"));

	ActiveTrigger= CreateDefaultSubobject<UBoxComponent>(TEXT("ACTVIETRIGGER"));

	RootComponent = RootPoint;



	ExplosionSignEffectComponent->SetupAttachment(RootComponent);
	MagicAOECollision->SetupAttachment(RootComponent);
	ExplosionEffectComponent->SetupAttachment(MagicAOECollision);
	ShockEffectComponent->SetupAttachment(RootComponent);

	ActiveTrigger->SetupAttachment(RootComponent);

	ExplosionSignEffectComponent->SetAutoActivate(false);
	ExplosionEffectComponent->SetAutoActivate(false);
	ShockEffectComponent->SetAutoActivate(false);


	MagicAOECollision->SetCollisionProfileName("AOE");
	MagicAOECollision->SetGenerateOverlapEvents(false);



	ActiveTrigger->SetCollisionProfileName("Trigger");
	ActiveTrigger->SetGenerateOverlapEvents(true);

	Explosion_Wait_Time = 10.0f;
	Explosion_SignWait_Time = 10.0f;
	Explosion_Time = 10.0f;

	bIsExplosion_Wait_Timer = false;
	Explosion_Wait_Timer = 0.0f;

	bIsExplosion_SignWait_Timer = false;
	Explosion_SignWait_Timer = 0.0f;

	bIsExplosion_Timer = false;
	Explosion_Timer = 5.0f;


	SpiritRecovery_Gauge = 3.0f;
	SpiritRecovery_HP = 10.0f;

	MagicAOE_Power = 50.0f;

	MagicAOE_Time = 0.5f;

	MagicAOE_Timer=0.0f;

	MagicAOECollision->SetCapsuleHalfHeight(1.0f);
	MagicAOECollision->SetCapsuleRadius(1.0f);

}
void ALabMagic::StartExplosionSignWait()
{
	bIsExplosion_SignWait_Timer = true;
}

void ALabMagic::ExplosionSign()
{

	if (Use_SpiritPlates.Num() != 0) {
		bIsExplosion_SignWait_Timer = false;
		Explosion_SignWait_Timer = 0.0f;

		ExplosionSignEffectComponent->SetActive(true, true);
		bIsExplosion_Wait_Timer = true;

		//정령 발판 생성 및 정령 움직이기 

		int Size = Use_SpiritPlates.Num();
		auto num = FMath::RandRange(0, Size - 1);

		CurPlate = Use_SpiritPlates[num];
		auto Instance = Cast<USTGameInstance>(GetGameInstance());
		if (Instance != nullptr)
		{
			Instance->GetPlayer()->IreneInput->SpiritChangeBlock();
			Instance->GetPlayer()->SpawnPet(CurPlate);

			Use_SpiritPlates.RemoveAt(num);

			
		}
	}

}

void ALabMagic::StartExplosion()
{
	bIsExplosion_Wait_Timer = false;
	Explosion_Wait_Timer = 0.0f;

	ExplosionSignEffectComponent->Deactivate();

	MagicAOECollision->SetGenerateOverlapEvents(true);
	bIsExplosion_Timer = true;
	ExplosionEffectComponent->SetActive(true, true);
	ShockEffectComponent->SetActive(true, true);
}

void ALabMagic::EndExplosion()
{
	MagicAOECollision->SetGenerateOverlapEvents(false);
	bIsExplosion_Timer = false;
	AOEInActor.Empty();
	Explosion_Timer = 0.0f;
	if (CurPlate != nullptr)
	{
		
			CurPlate->SpiritPlateOff();
	
	}
	CurPlate = nullptr;
	MagicAOECollision->SetRelativeLocation(InitLocation);

	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	if (Instance != nullptr)
	{
		Instance->GetPlayer()->VisiblePet();

		Instance->GetPlayer()->IreneData.IsInvincibility = false;
		Instance->GetPlayer()->IreneData.IsSkipMonsterAttack = false;
		Instance->GetPlayer()->IreneInput->SetSpiritChangeEnable(true);
	}

	ExplosionEffectComponent->Deactivate();
	ShockEffectComponent->Deactivate();
	StartExplosionSignWait();
}

void ALabMagic::Explosion(float DeltaTime)
{
	//FVector ForwardVec = GetActorForwardVector();
	//ForwardVec.Normalize();
	//MagicAOECollision->SetRelativeLocation(MagicAOECollision->GetRelativeLocation() + (ForwardVec * MagicAOE_Speed * DeltaTime));


	MagicAOECollision->SetCapsuleHalfHeight(MagicAOECollision->GetScaledCapsuleHalfHeight()+ MagicAOE_Speed * DeltaTime);
	MagicAOECollision->SetCapsuleRadius(MagicAOECollision->GetScaledCapsuleRadius() + MagicAOE_Speed * DeltaTime);
}

void ALabMagic::AOEAttack()
{
	if (AOEInActor.Num() != 0)
	{
		for (int i = 0; i < AOEInActor.Num(); i++)
		{
			UGameplayStatics::ApplyDamage(AOEInActor[i], MagicAOE_Power, NULL, this, NULL);
			STARRYLOG_S(Warning);
		}
	}
	MagicAOE_Timer = 0.0f;
}

void ALabMagic::EndLabMagic()
{

	ExplosionSignEffectComponent->Deactivate();
	ExplosionEffectComponent->Deactivate();
	ShockEffectComponent->Deactivate();
	MagicAOECollision->SetCollisionProfileName("AOE");
	MagicAOECollision->SetGenerateOverlapEvents(false);

	Explosion_Wait_Time = 10.0f;
	Explosion_SignWait_Time = 10.0f;
	Explosion_Time = 10.0f;

	bIsExplosion_Wait_Timer = false;
	Explosion_Wait_Timer = 0.0f;

	bIsExplosion_SignWait_Timer = false;
	Explosion_SignWait_Timer = 0.0f;

	bIsExplosion_Timer = false;
	Explosion_Timer = 5.0f;


	SpiritRecovery_Gauge = 3.0f;
	SpiritRecovery_HP = 10.0f;

	MagicAOE_Power = 50.0f;

	MagicAOE_Time = 0.5f;

	MagicAOE_Timer = 0.0f;

	MagicAOECollision->SetCapsuleHalfHeight(1.0f);
	MagicAOECollision->SetCapsuleRadius(1.0f);

	Use_SpiritPlates = SpiritPlates;

	for (int i = 0; i < SpiritPlates.Num(); i++)
	{
		SpiritPlates[i]->SpiritPlateOff();
	}

}

// Called when the game starts or when spawned
void ALabMagic::BeginPlay()
{
	Super::BeginPlay();
	MagicAOECollision->OnComponentBeginOverlap.AddDynamic(this, &ALabMagic::OnBeginOverlap);
	ActiveTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALabMagic::ActiveLabMagic);
	if (SpiritPlates.Num() != 0)
	{
		for (int i = 0; i < SpiritPlates.Num(); i++)
		{
			SpiritPlates[i]->InitSpiritPlate(SpiritRecovery_HP, SpiritRecovery_Gauge);
		}
	}
	InitLocation = MagicAOECollision->GetRelativeLocation();
	Use_SpiritPlates = SpiritPlates;
}

void ALabMagic::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AOEInActor.Num() != 0)
	{
		for (int i = 0; i < AOEInActor.Num(); i++)
		{
			if (AOEInActor[i] == OtherActor)return;
		}
	}
	AOEInActor.Add(OtherActor);
}

void ALabMagic::ActiveLabMagic(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ActiveTrigger->SetGenerateOverlapEvents(false);
	StartExplosionSignWait();
}



// Called every frame
void ALabMagic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bIsExplosion_SignWait_Timer)
	{
		Explosion_SignWait_Timer += DeltaTime;
		if (Explosion_SignWait_Timer >= Explosion_SignWait_Time) {
			ExplosionSign();
		}
	}

	if (bIsExplosion_Wait_Timer)
	{
		Explosion_Wait_Timer += DeltaTime;
		if (Explosion_Wait_Timer >= Explosion_Wait_Time) {
			StartExplosion();
		}
	}

	if (bIsExplosion_Timer)
	{
		Explosion_Timer += DeltaTime;
		MagicAOE_Timer += DeltaTime;
		Explosion(DeltaTime);
		if (Explosion_Timer >= Explosion_Time)
		{
			EndExplosion();
		}

		if (MagicAOE_Timer >= MagicAOE_Time)
		{
			AOEAttack();
		}
		
	}
}

