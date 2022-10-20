// Fill out your copyright notice in the Description page of Project Settings.


#include "GuidedSwirl.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "../../../PlayerSource/PlayerFSM/IreneFSM.h"
#include "../../../STgameInstance.h"
#include "Kismet/GameplayStatics.h"

AGuidedSwirl::AGuidedSwirl()
{

	GuidedSwirlCore=CreateDefaultSubobject<UCapsuleComponent>(TEXT("GuidedCore"));

	GuidedSwirlCore->SetupAttachment(RootComponent);
	GuidedSwirlCore->SetGenerateOverlapEvents(false);
	GuidedSwirlCore->SetCollisionProfileName("NoCollision");

	RotationTimer = 0.0f;
	RotationTime = 0.1f;
	bIsGuidedMove = false;
	CollisionTimer = 0.0f;
	CollisionTime = 2.0f;
}

void AGuidedSwirl::InitSwirl(float DamageVal, float SwirlDotDamageVal, float PullForceVal, float CoreSetTimeVal, float KeepSwirlTimeVal,
	float MoveSpeedVal, float SwirlRadiusVal, float ExplosionRadiusVal, float ExplosionAtkVal)
{
	ASwirl::InitSwirl(DamageVal, SwirlDotDamageVal, PullForceVal, CoreSetTimeVal, KeepSwirlTimeVal, MoveSpeedVal, SwirlRadiusVal);

	ExplosionRadius = ExplosionRadiusVal;
	ExplosionAtk = ExplosionAtkVal;

	GuidedSwirlCore->SetCapsuleHalfHeight(SwirlRadiusVal);
	GuidedSwirlCore->SetCapsuleRadius(SwirlRadiusVal);
}

void AGuidedSwirl::SwirlCoreActive(FVector MoveDirectionVal)
{
	ASwirl::SwirlCoreActive(MoveDirectionVal);
	bIsMove = false;
	bIsGuidedMove = true;
	GuidedSwirlCore->SetGenerateOverlapEvents(true);
}

void AGuidedSwirl::GuidedSwirlBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AGuidedSwirl>(OtherActor)&& Cast<AGuidedSwirl>(OtherActor)!=this)
	{
		auto OtherSwirl = Cast<AGuidedSwirl>(OtherActor);

			FVector Direction = OtherActor->GetActorLocation() - GetActorLocation();
			Direction.Normalize();
			ExplosionLocation = Direction * MinDistance;
		
			AttackCheck(ExplosionRadius, 200.0f, 360.0f, 0.0f);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SwirlExplosionParticle, GetActorLocation() + ExplosionLocation);

			OtherSwirl->Destroy();
			Destroy();
	
	}
}

void AGuidedSwirl::BeginPlay()
{
	Super::BeginPlay();
	GuidedSwirlCore->OnComponentBeginOverlap.AddDynamic(this, &AGuidedSwirl::GuidedSwirlBegin);
}


void AGuidedSwirl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	if (CollisionTimer < CollisionTime)
	{
		CollisionTimer += DeltaTime;

		if(CollisionTimer >= CollisionTime)
			GuidedSwirlCore->SetCollisionProfileName("Pawn");

	}


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

void AGuidedSwirl::AttackCheck(float Radius, float Hegiht, float Angle, float AttackAxis)
{
	// hitcheck======================================


	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();
	FVector AttackDirection = ForwardVector.RotateAngleAxis(AttackAxis, FVector::UpVector);
	AttackDirection.Normalize();


	FVector Center = GetActorLocation()+ExplosionLocation;


	FVector Box = FVector(Radius, Radius, Hegiht);
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	bool bResult = GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeCapsule(Box),
		CollisionQueryParam
	);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			//플레이어 클래스 정보를 가져오고 PlayerController를 소유하고 있는가 확인
			//STARRYLOG(Warning, TEXT("%s"), *OverlapResult.GetActor()->GetName());
			AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore;
				bool bTraceResult;

				FVector Direction = Player->GetActorLocation() - GetActorLocation();
				Direction *= ExplosionRadius;
				bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
					GetWorld(),
					Center,
					Center+ Direction,
					ExplosionRadius,
					ETraceTypeQuery::TraceTypeQuery4,
					false,
					ActorsToIgnore,
					EDrawDebugTrace::None,
					Hits,
					true
					
				);

				
				for (int i = 0; i < Hits.Num(); ++i)
				{
					//STARRYLOG(Warning,TEXT("%s"), *Hits[i].GetActor()->GetName());
					Player = Cast<AIreneCharacter>(Hits[i].Actor);
					if (Player != nullptr)
					{
						break;
					}
				}
				if (bTraceResult && !(nullptr == Player))
				{
					//2차 탐지
					//if (Monster->GetTestMode())
						//STARRYLOG(Warning, TEXT("Attack in Player SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Center;
					TargetDir = TargetDir.GetSafeNormal();


					float Radian = FVector::DotProduct(AttackDirection, TargetDir);
					//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));
					//STARRYLOG(Error, TEXT("%f"), TargetAngle);
					if (TargetAngle <= (Angle * 0.5f))
					{
						if (nullptr == Player) {
							
						}
						bIsOnDotDamage = false;
						UGameplayStatics::ApplyDamage(Player, ExplosionAtk, NULL, this, NULL);
					}

				}

			}
		}
	}
}
