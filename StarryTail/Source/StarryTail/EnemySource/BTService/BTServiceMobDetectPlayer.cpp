// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceMobDetectPlayer.h"
#include "../Monster.h"
#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTServiceMobDetectPlayer::UBTServiceMobDetectPlayer()
{
	NodeName = TEXT("DetectPlayer");
	Interval = 1.0f;
}
void UBTServiceMobDetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return;

	UWorld* World = Monster->GetWorld();
	FVector Center = Monster->GetLocation() + (-Monster->GetActorForwardVector() * Monster->GetCapsuleComponent()->GetScaledCapsuleRadius());

	FVector CenterBottom = Center;
	CenterBottom.Z -= 85.0f;

	FVector CenterTop = CenterBottom;
	CenterTop.Z += 150.0f;

	FVector Box = FVector(Monster->GetViewRange(), Monster->GetViewRange(), Monster->GetViewHeight());
	//�𸣺� �ֺ� ���� 200 �ȿ� �ִ� ���� Ž��, EnemyDetect Ʈ���̽� ä�� ���
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = World->OverlapMultiByChannel( // ������ Collision FCollisionShape�� �浹�� ���� ���� 
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeCapsule(Box),
		CollisionQueryParam
	);






	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			//�÷��̾� Ŭ���� ������ �������� PlayerController�� �����ϰ� �ִ°� Ȯ��
			AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				//1�� Ž��
				if(Monster->GetTestMode())
					STARRYLOG(Warning, TEXT("Detect Player in DetectSphere"));

				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore; // ������ ���� ����?
				bool bTraceResult;

				// https://blog.daum.net/peace-day/22
				// TraceTypeQuery�� �ݸ��� �������� Ʈ���̽� �������� 1���� ���������� �ο���
				if (Monster->GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						World,
						Monster->GetLocation(), // SphereTrace ���� ��ġ
						Player->GetActorLocation(), // SphereTrace ���� ��ġ
						5.0f,
						ETraceTypeQuery::TraceTypeQuery4,
						false,
						ActorsToIgnore,
						EDrawDebugTrace::ForDuration, // ������ ���ڰ����� �ð� ���� ����
						Hits,
						true,
						FLinearColor::Red,
						FLinearColor::Green,
						1.0f
					);
				}
				else
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						World,
						Monster->GetLocation(),
						Player->GetActorLocation(),
						5.0f,
						ETraceTypeQuery::TraceTypeQuery4,
						false,
						ActorsToIgnore,
						EDrawDebugTrace::None,
						Hits,
						true
					);
				}	
				
				for (int i = 0; i < Hits.Num(); i++)
				{
					Player = Cast<AIreneCharacter>(Hits[i].GetActor());
					if (Player != nullptr)
					{
						break;
					}
				}

				if (bTraceResult && !(nullptr == Player))
				{
					//2�� Ž��
					if (Monster->GetTestMode())
						STARRYLOG(Warning, TEXT("Detect Player in SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit�� �������� ���ϴ� ���Ϳ� �÷��̾�� ���ϴ� ������ ������ ���� ������ ���� �� �ִ�. ������� Radian
					float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
					//���� ������� Cos{^-1}(A dot B / |A||B|)�̱� ������ ��ũ�ڻ��� �Լ��� ������ְ� Degree�� ��ȯ���ش�.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					if (TargetAngle <= (Monster->GetViewAngle() * 0.5f))
					{
						//3�� Ž��
						if (Monster->GetTestMode())
							STARRYLOG(Warning, TEXT("Detect Player in MorbitFOV"));
						//���� ������ ����

						
						Monster->GetAIController()->SetFind();
						//���� Ž��
						TArray<FOverlapResult> AnotherMonsterList = Monster->DetectMonster(Monster->GetDetectMonsterRange());
						if (AnotherMonsterList.Num() != 0)
						{
							for (auto const& AnotherMonster : AnotherMonsterList)
							{
								auto Mob = Cast<AMonster>(AnotherMonster.GetActor());
								if (Mob == nullptr)
									continue;

								auto AnotherMonsterAIController = Cast<AMonsterAIController>(Mob->GetController());
								if (AnotherMonsterAIController == nullptr)
									continue;

								AnotherMonsterAIController->SetFind();
							}
						}

						return;
					}
					else {
						OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);
					}
				}
				else {
					OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);
				}
			}
			else {
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);
			}
		}
	}
	else {
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);
    }

	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, 220.0f));
		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetViewHeight()));

		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();


		DrawRadial(World, BottomDebugMatrix, Monster->GetViewRange(), Monster->GetViewAngle(), FColor::Blue,10,0.2f,false,0,2);
		DrawRadial(World, TopDebugMatrix, Monster->GetViewRange(), Monster->GetViewAngle(), FColor::Blue, 10, 0.2f, false, 0, 2);
	}

}


ULineBatchComponent* GetDebugLineBatcher(const UWorld* InWorld, bool bPersistentLines, float LifeTime, bool bDepthIsForeground)
{
	return (InWorld ? (bDepthIsForeground ? InWorld->ForegroundLineBatcher : ((bPersistentLines || (LifeTime > 0.f)) ? InWorld->PersistentLineBatcher : InWorld->LineBatcher)) : NULL);
}
// internal
static float GetDebugLineLifeTime(ULineBatchComponent* LineBatcher, float LifeTime, bool bPersistent)
{
	return bPersistent ? -1.0f : ((LifeTime > 0.f) ? LifeTime : LineBatcher->DefaultLifeTime);
}

 void DrawRadial(const UWorld* _InWorld, const FMatrix& _TransformMatrix, float _Radius, float _Angle, const FColor& _Color, int32 _Segments, float _LifeTime, bool _bPersistentLines, uint8 _DepthPriority, float _Thickness)
{
	// no debug line drawing on dedicated server
	if (GEngine->GetNetMode(_InWorld) != NM_DedicatedServer)
	{
		ULineBatchComponent* const LineBatcher = GetDebugLineBatcher(_InWorld, _bPersistentLines, _LifeTime, (_DepthPriority == SDPG_Foreground));
		if (LineBatcher != NULL)
		{
			const float LineLifeTime = GetDebugLineLifeTime(LineBatcher, _LifeTime, _bPersistentLines);

			// Need at least 4 segments
			float Segments = FMath::Max(_Segments, 4);
			const float AngleStep = FMath::DegreesToRadians(_Angle) / float(Segments);

			const FVector Center = _TransformMatrix.GetOrigin();
			const FVector AxisY = _TransformMatrix.GetScaledAxis(EAxis::Y);
			const FVector AxisX = _TransformMatrix.GetScaledAxis(EAxis::X);

			TArray<FBatchedLine> Lines;
			Lines.Empty(Segments);

			float StartAngle = FMath::DegreesToRadians(90.0f - _Angle / 2.0f);
			float EndAngle = FMath::DegreesToRadians(_Angle);

			float Angle = StartAngle;
			while (Segments--)
			{
				const FVector Vertex1 = Center + _Radius * (AxisY * FMath::Cos(Angle) + AxisX * FMath::Sin(Angle));
				Angle += AngleStep;
				const FVector Vertex2 = Center + _Radius * (AxisY * FMath::Cos(Angle) + AxisX * FMath::Sin(Angle));
				Lines.Add(FBatchedLine(Vertex1, Vertex2, _Color, LineLifeTime, _Thickness, _DepthPriority));
			}
			FVector FirsetVertex = Lines[0].Start;
			FVector LastVertext = Lines.Last().End;

			Lines.Add(FBatchedLine(Center, FirsetVertex, _Color, LineLifeTime, _Thickness, _DepthPriority));
			Lines.Add(FBatchedLine(Center, LastVertext, _Color, LineLifeTime, _Thickness, _DepthPriority));

			LineBatcher->DrawLines(Lines);
		}
	}
}
