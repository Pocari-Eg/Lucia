// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceAttackTrace.h"
#include "../MonsterAIController.h"
#include "../Bellyfish/BellyfishAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

#include "../OldBTService/BTServiceMobDetectPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
UBTServiceAttackTrace::UBTServiceAttackTrace()
{
	NodeName = TEXT("ATTACKTRACE");
	Interval = 0.1f;
}
void UBTServiceAttackTrace::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return;

	FVector Center = Monster->GetLocation() + (-Monster->GetActorForwardVector() * Monster->GetCapsuleComponent()->GetScaledCapsuleRadius());

	FVector CenterBottom = Center;
	CenterBottom.Z -= 85.0f;

	FVector CenterTop = CenterBottom;
	CenterTop.Z += 150.0f;

	
	Attack1Trace(Monster, OwnerComp, Center, CenterBottom, CenterTop);
	Attack2Trace(Monster, OwnerComp, Center, CenterBottom, CenterTop);
	Attack3Trace(Monster, OwnerComp, Center, CenterBottom, CenterTop);
}

void UBTServiceAttackTrace::Attack1Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center, FVector CenterBottom, FVector CenterTop)
{
	FVector Box = FVector(Monster->GetAttack1Range().M_Atk_Angle, Monster->GetAttack1Range().M_Atk_Radius, Monster->GetAttack1Range().M_Atk_Height);
	//모르빗 주변 범위 200 안에 있는 액터 탐지, EnemyDetect 트레이스 채널 사용
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = Monster->GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
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
			//플레이어 클래스 정보를 가져오고 PlayerController를 소유하고 있는가 확인
			AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				//1차 탐지
				//if (Monster->GetTestMode())
					//STARRYLOG(Warning, TEXT("Detect Player in DetectSphere"));

				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore; // 무시할 액터 유형?
				bool bTraceResult;

				// https://blog.daum.net/peace-day/22
				// TraceTypeQuery는 콜리전 프리셋의 트레이스 유형에서 1부터 순차적으로 부여됨
				if (Monster->GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						Monster->GetWorld(),
						Monster->GetLocation(), // SphereTrace 시작 위치
						Player->GetActorLocation(), // SphereTrace 종료 위치
						5.0f,
						ETraceTypeQuery::TraceTypeQuery4,
						false,
						ActorsToIgnore,
						EDrawDebugTrace::ForDuration, // 마지막 인자값으로 시간 조절 가능
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
						Monster->GetWorld(),
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
					//2차 탐지
					//if (Monster->GetTestMode())
						//STARRYLOG(Warning, TEXT("Attack in Player SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit의 정면으로 향하는 벡터와 플레이어로 향하는 벡터의 내적을 통해 각도를 구할 수 있다. 결과값은 Radian
					float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
					//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					if (TargetAngle <= (Monster->GetAtkAngle() * 0.5f))
					{
						//3차 탐지
						
						//Monster->GetAIController()->SetInAttackArea(true);
						return;
					}
					else if (Monster->GetDistanceToPlayer() <= 100.0f)
					{
						//Monster->GetAIController()->SetInAttackArea(true);
						return;
					}
					else {
						//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
						//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
					}

				}
				else {
					//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
					//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
				}

			}
			else {
				//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
				//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
			}

		}
	}
	else {
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
	}

	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, 220.0f));
		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetAtkHeight()));

		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

		DrawRadial(Monster->GetWorld(), BottomDebugMatrix, Monster->GetAttack1Range().M_Atk_Radius, Monster->GetAttack1Range().M_Atk_Angle, FColor::Red, 10, 0.1f, false, 0, 2);
		DrawRadial(Monster->GetWorld(), TopDebugMatrix, Monster->GetAttack1Range().M_Atk_Radius, Monster->GetAttack1Range().M_Atk_Angle, FColor::Red, 10, 0.1f, false, 0, 2);
	}

}

void UBTServiceAttackTrace::Attack2Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center, FVector CenterBottom, FVector CenterTop)
{
	FVector Box = FVector(Monster->GetAttack2Range().M_Atk_Angle, Monster->GetAttack2Range().M_Atk_Radius, Monster->GetAttack2Range().M_Atk_Height);
	//모르빗 주변 범위 200 안에 있는 액터 탐지, EnemyDetect 트레이스 채널 사용
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = Monster->GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
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
			//플레이어 클래스 정보를 가져오고 PlayerController를 소유하고 있는가 확인
			AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				//1차 탐지
				//if (Monster->GetTestMode())
					//STARRYLOG(Warning, TEXT("Detect Player in DetectSphere"));

				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore; // 무시할 액터 유형?
				bool bTraceResult;

				// https://blog.daum.net/peace-day/22
				// TraceTypeQuery는 콜리전 프리셋의 트레이스 유형에서 1부터 순차적으로 부여됨
				if (Monster->GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						Monster->GetWorld(),
						Monster->GetLocation(), // SphereTrace 시작 위치
						Player->GetActorLocation(), // SphereTrace 종료 위치
						5.0f,
						ETraceTypeQuery::TraceTypeQuery4,
						false,
						ActorsToIgnore,
						EDrawDebugTrace::ForDuration, // 마지막 인자값으로 시간 조절 가능
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
						Monster->GetWorld(),
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
					//2차 탐지
	

					FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit의 정면으로 향하는 벡터와 플레이어로 향하는 벡터의 내적을 통해 각도를 구할 수 있다. 결과값은 Radian
					float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
					//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					if (TargetAngle <= (Monster->GetAtkAngle() * 0.5f))
					{
						//3차 탐지
			
					//	Monster->GetAIController()->SetInAttackArea(true);
						return;
					}
					else if (Monster->GetDistanceToPlayer() <= 100.0f)
					{
					//	Monster->GetAIController()->SetInAttackArea(true);
						return;
					}
					else {
						//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
						//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
					}

				}
				else {
					//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
					//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
				}

			}
			else {
				//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
				//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
			}

		}
	}
	else {
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
	}

	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, 220.0f));
		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetAtkHeight()));

		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

		DrawRadial(Monster->GetWorld(), BottomDebugMatrix, Monster->GetAttack2Range().M_Atk_Radius, Monster->GetAttack2Range().M_Atk_Angle, FColor::Blue, 10, 0.1f, false, 0, 2);
		DrawRadial(Monster->GetWorld(), TopDebugMatrix, Monster->GetAttack2Range().M_Atk_Radius, Monster->GetAttack2Range().M_Atk_Angle, FColor::Blue, 10, 0.1f, false, 0, 2);
	}

}

void UBTServiceAttackTrace::Attack3Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center, FVector CenterBottom, FVector CenterTop)
{
	FVector Box = FVector(Monster->GetAttack3Range().M_Atk_Angle, Monster->GetAttack3Range().M_Atk_Radius, Monster->GetAttack3Range().M_Atk_Height);
	//모르빗 주변 범위 200 안에 있는 액터 탐지, EnemyDetect 트레이스 채널 사용
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = Monster->GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
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
			//플레이어 클래스 정보를 가져오고 PlayerController를 소유하고 있는가 확인
			AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				//1차 탐지

				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore; // 무시할 액터 유형?
				bool bTraceResult;

				// https://blog.daum.net/peace-day/22
				// TraceTypeQuery는 콜리전 프리셋의 트레이스 유형에서 1부터 순차적으로 부여됨
				if (Monster->GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						Monster->GetWorld(),
						Monster->GetLocation(), // SphereTrace 시작 위치
						Player->GetActorLocation(), // SphereTrace 종료 위치
						5.0f,
						ETraceTypeQuery::TraceTypeQuery4,
						false,
						ActorsToIgnore,
						EDrawDebugTrace::ForDuration, // 마지막 인자값으로 시간 조절 가능
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
						Monster->GetWorld(),
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
					//2차 탐지
	

					FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit의 정면으로 향하는 벡터와 플레이어로 향하는 벡터의 내적을 통해 각도를 구할 수 있다. 결과값은 Radian
					float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
					//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					if (TargetAngle <= (Monster->GetAtkAngle() * 0.5f))
					{
						//3차 탐지
						
						//Monster->GetAIController()->SetInAttackArea(true);
						return;
					}
					else if (Monster->GetDistanceToPlayer() <= 100.0f)
					{
						//Monster->GetAIController()->SetInAttackArea(true);
						return;
					}
					else {
						//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
						//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
					}

				}
				else {
					//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
					//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
				}

			}
			else {
			   //OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
				//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
			}

		}
	}
	else {
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
	}

	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, 220.0f));
		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetAtkHeight()));

		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

		DrawRadial(Monster->GetWorld(), BottomDebugMatrix, Monster->GetAttack3Range().M_Atk_Radius, Monster->GetAttack3Range().M_Atk_Angle, FColor::Yellow, 10, 0.1f, false, 0, 2);
		DrawRadial(Monster->GetWorld(), TopDebugMatrix, Monster->GetAttack3Range().M_Atk_Radius, Monster->GetAttack3Range().M_Atk_Angle, FColor::Yellow, 10, 0.1f, false, 0, 2);
	}

}

