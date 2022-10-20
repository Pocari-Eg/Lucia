// Fill out your copyright notice in the Description page of Project Settings.


#include "TornadoSwirl.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "../../../PlayerSource/PlayerFSM/IreneFSM.h"
#include "../../../STgameInstance.h"
#include "Kismet/GameplayStatics.h"

ATornadoSwirl::ATornadoSwirl()
{

	TornadoSwirlCore=CreateDefaultSubobject<UCapsuleComponent>(TEXT("GuidedCore"));

	TornadoSwirlCore->SetupAttachment(RootComponent);
	TornadoSwirlCore->SetGenerateOverlapEvents(false);
	TornadoSwirlCore->SetCollisionProfileName("NoCollision");

	RotationTimer = 0.0f;
	RotationTime = 0.1f;
	bIsTornadoSwirlMove = false;



	static ConstructorHelpers::FClassFinder<ATornado> BP_Tornado(TEXT("/Game/BluePrint/Monster/Bellarus/BP_Tornado.BP_Tornado_C"));
	if (BP_Tornado.Succeeded() && BP_Tornado.Class != NULL) {
		ATornadoClass = BP_Tornado.Class;
	}
}

void ATornadoSwirl::InitSwirl(float DamageVal, float SwirlDotDamageVal, float PullForceVal, float CoreSetTimeVal, float KeepSwirlTimeVal,
	float MoveSpeedVal, float SwirlRadiusVal)
{
	ASwirl::InitSwirl(DamageVal, SwirlDotDamageVal, PullForceVal, CoreSetTimeVal, KeepSwirlTimeVal, MoveSpeedVal, SwirlRadiusVal);


	TornadoSwirlCore->SetCapsuleHalfHeight(SwirlRadiusVal);
	TornadoSwirlCore->SetCapsuleRadius(SwirlRadiusVal);
}

void ATornadoSwirl::SwirlCoreActive(FVector MoveDirectionVal)
{
	ASwirl::SwirlCoreActive(MoveDirectionVal);
	MoveDirection = GetActorForwardVector();
	bIsMove = false;
	bIsTornadoSwirlMove = true;
	TornadoSwirlCore->SetGenerateOverlapEvents(true);
	TornadoSwirlCore->SetCollisionProfileName("Pawn");
}

void ATornadoSwirl::TornadoSwirlBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ATornadoSwirl>(OtherActor)&& Cast<ATornadoSwirl>(OtherActor)!=this)
	{
		STARRYLOG_S(Error);
		
			FVector Direction = OtherActor->GetActorLocation() - GetActorLocation();
			Direction.Normalize();
			SpawnLocation = Direction * MinDistance;
			SpawnTornado();
			OtherActor->Destroy();
			Destroy();
	
	}
}


void ATornadoSwirl::BeginPlay()
{
	Super::BeginPlay();
	TornadoSwirlCore->OnComponentBeginOverlap.AddDynamic(this, &ATornadoSwirl::TornadoSwirlBegin);
}

void ATornadoSwirl::InitTornade(float DamageVal, float SwirlDotDamageVal, float PullForceVal, float CoreSetTimeVal, float KeepSwirlTimeVal, float MoveSpeedVal, float SwirlRadiusVal)
{

	  ToDamage = DamageVal;
	  To_Dot_Damage = SwirlDotDamageVal;
	  ToPull_Force = PullForceVal;
	  ToMoveSpeed = MoveSpeedVal;
	  ToRadius = SwirlRadiusVal;
	  ToCoreSetTime = CoreSetTimeVal;
	  ToKeepSwirlTime = KeepSwirlTimeVal;
	  ToDotDamageTime = 0.5f;
}

void ATornadoSwirl::SpawnTornado()
{

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();

	ATornado* Tornado = GetWorld()->SpawnActor<ATornado>(ATornadoClass,
		(GetActorLocation()+ SpawnLocation) + (ForwardVector * 100.0f),
		FRotator::ZeroRotator , SpawnParams);
	if (Tornado != nullptr)
	{
		Tornado->InitSwirl(ToDamage, To_Dot_Damage, ToPull_Force, ToCoreSetTime,ToKeepSwirlTime,ToMoveSpeed,ToRadius);
		Tornado->SwirlCoreActive(ForwardVector);
	}
}



void ATornadoSwirl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	


	if (bIsTornadoSwirlMove) {
		
		SetActorLocation(GetActorLocation() + (MoveDirection * MoveSpeed * DeltaTime));
		
	}



}


