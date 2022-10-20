// Fill out your copyright notice in the Description page of Project Settings.


#include "GuidedSwirl.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "../../PlayerSource/PlayerFSM/IreneFSM.h"
#include "../../STgameInstance.h"
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
	DestroyTimer = 0.0f;
	bIsDestroy = false;
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
		FVector Direction =  OtherActor->GetActorLocation()- GetActorLocation();
		Direction.Normalize();

		
		ExplosionLocation = Direction * MinDistance;

		bIsDestroy = true;
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
		


				//2���� ���͸� a to b �� ȸ�� �ϴ� ��� ���ϱ�
				FVector ForwardVec = GetActorForwardVector();
				ForwardVec.Normalize();

				FVector PlayerVec = Instance->GetPlayer()->GetActorLocation() - GetActorLocation();


				PlayerVec.Normalize();


				FQuat RotationQuat = Math::VectorA2BRotation(ForwardVec, PlayerVec);
				RotationQuat.Y = 0.0f;
				RotationQuat.X = 0.0f;
				RotationQuat.Z *= DeltaTime*0.7f;
				AddActorWorldRotation(RotationQuat);
				FVector RotateVec = RotationQuat.RotateVector(ForwardVec);

				RotationTimer = 0.0f;

			}
	

	}

	if (bIsDestroy)
	{
		DestroyTimer += DeltaTime;
		if (DestroyTimer >= 0.1)
		{
			AttackCheck(ExplosionRadius, 200.0f, 360.0f, 0.0f);

			Destroy();
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
	bool bResult = GetWorld()->OverlapMultiByChannel( // ������ Collision FCollisionShape�� �浹�� ���� ���� 
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
			//�÷��̾� Ŭ���� ������ �������� PlayerController�� �����ϰ� �ִ°� Ȯ��
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
					//2�� Ž��
					//if (Monster->GetTestMode())
						//STARRYLOG(Warning, TEXT("Attack in Player SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Center;
					TargetDir = TargetDir.GetSafeNormal();


					float Radian = FVector::DotProduct(AttackDirection, TargetDir);
					//���� ������� Cos{^-1}(A dot B / |A||B|)�̱� ������ ��ũ�ڻ��� �Լ��� ������ְ� Degree�� ��ȯ���ش�.
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
