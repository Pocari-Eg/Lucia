// Fill out your copyright notice in the Description page of Project Settings.


#include "Tornado.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "../../../PlayerSource/PlayerFSM/IreneFSM.h"
#include "../../../STgameInstance.h"
#include "Kismet/GameplayStatics.h"

ATornado::ATornado()
{


	RotationTimer = 0.0f;
	RotationTime = 0.1f;
	bIsGuidedMove = false;

}



void ATornado::SwirlCoreActive(FVector MoveDirectionVal)
{
	ASwirl::SwirlCoreActive(MoveDirectionVal);
	bIsMove = false;
	bIsGuidedMove = true;
}



void ATornado::BeginPlay()
{
	Super::BeginPlay();

	Swirl_Pull_Range->OnComponentBeginOverlap.AddDynamic(this, &ATornado::TornadoPullRangeBegin);
	Swirl_Pull_Range->OnComponentEndOverlap.AddDynamic(this, &ATornado::TornadoPullRangeEnd);
}


void ATornado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsGuidedMove) {
		auto Instance = Cast<USTGameInstance>(GetGameInstance());

		MoveDirection = GetActorForwardVector();
		SetActorLocation(GetActorLocation() + (MoveDirection * MoveSpeed * DeltaTime));
		if (GetDistanceTo(Instance->GetPlayer()) > MinDistance) {

			RotationTimer += DeltaTime;
		


				//2개의 벡터를 a to b 로 회전 하는 행렬 구하기
				FVector ForwardVec = GetActorForwardVector();
				ForwardVec.Normalize();

				FVector PlayerVec = Instance->GetPlayer()->GetActorLocation() - GetActorLocation();


				PlayerVec.Normalize();


				FQuat RotationQuat = Math::VectorA2BRotation(ForwardVec, PlayerVec);
				RotationQuat.Y = 0.0f;
				RotationQuat.X = 0.0f;
				RotationQuat.Z *= DeltaTime;
				AddActorWorldRotation(RotationQuat);
				FVector RotateVec = RotationQuat.RotateVector(ForwardVec);

				RotationTimer = 0.0f;

			}
	

	}

}

void ATornado::TornadoPullRangeBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AIreneCharacter>(OtherActor))
	{
		bIsOnDotDamage = true;

	}
}

void ATornado::TornadoPullRangeEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AIreneCharacter>(OtherActor))
	{
		bIsOnDotDamage = false;
	}
}