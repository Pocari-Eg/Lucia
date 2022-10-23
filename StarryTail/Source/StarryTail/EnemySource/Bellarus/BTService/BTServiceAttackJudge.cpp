// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceAttackJudge.h"
#include "../../MonsterAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Bellarus.h"
#include "../../BTService/BTServiceMobDetectPlayer.h"
#include "../../../STGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
UBTServiceAttackJudge::UBTServiceAttackJudge()
{
	NodeName = TEXT("AttackJudge");
	Interval = 0.1f;
	AttackCheckTimer = 0.0f;
	InFirstJudge = false;
}
void UBTServiceAttackJudge::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

		auto Bellarus = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());
		if (nullptr == Bellarus)
			return;



		FVector Center = Bellarus->GetLocation();

		Center -= FVector(0.0f, 0.0f, Bellarus->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		
		InFirstJudge = AttackJudge(Bellarus, Center, Bellarus->GetFirstJugdeRadius(),FColor::Green);
		InSecondJudge = AttackJudge(Bellarus, Center, Bellarus->GetSecondJugdeRadius(), FColor::Blue);
		InCalibration = AttackJudge(Bellarus, Center, Bellarus->GetCalibrationRadius(), FColor::Red);

		AttackCheckTimer += Interval;
		if (AttackCheckTimer >= 1.0f)
		{
			AttackCheckTimer = 0.0f;


			//쉴드 있을때
			if (Cast<ABellarusAIController>(Bellarus->GetAIController())->GetIsShieldOn()) {
				if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackCoolKey) == false &&
					OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackingKey) == false) {
					if (InFirstJudge)
					{
						MeleeAttck(Bellarus, Center);
					}
					else {

						if (InCalibration)
						{
							auto ran = FMath::RandRange(1, 100);
							if (ran <= 80)
							{
								MeleeAttck(Bellarus, Center);
							}

						}
						else {

							if (InSecondJudge)
							{

								ShieldFristRangeAttackCheck(Bellarus, Center);

							}

						}
					}
				}
			}
			else {
				//쉴드 없을때


				//체크가 true일떄
				if (Cast<ABellarusAIController>(Bellarus->GetAIController())->GetCheckKey())
				{
					if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackCoolKey) == false &&
						OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackingKey) == false) {
						if (InFirstJudge)
						{
							MeleeAttck(Bellarus, Center);
						}
					}
				}
				else {
					//기본
						if (InFirstJudge)
						{

							auto ran = FMath::RandRange(1, 100);
							if (ran <= 70)
							{
								Cast<ABellarusAIController>(Bellarus->GetAIController())->SetCheckKey(true);
								return;
							}

							ran = FMath::RandRange(1, 100);
							if (ran <= 40)
							{
								if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackCoolKey) == false &&
									OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackingKey) == false) {
									MeleeAttck(Bellarus, Center);
								}
							}
						}
						else {
							if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackCoolKey) == false &&
								OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackingKey) == false) {

								if (InCalibration)
								{
									auto ran = FMath::RandRange(1, 100);
									if (ran <= 80)
									{
										MeleeAttck(Bellarus, Center);
									}

								}
								else {

									if (InSecondJudge)
									{

										ShieldFristRangeAttackCheck(Bellarus, Center);

									}

								}
							}
						}
					
				}
			}
			
		    
		}
	
}

bool UBTServiceAttackJudge::AttackJudge(AMonster* Monster, FVector Center,float Radius, FColor Color)
{

	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();

		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	
		
		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, 300.0f));
		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

		Monster->GetAIController()->DrawRadial(Monster->GetWorld(), BottomDebugMatrix, Radius,360.0f, Color, 10, 0.1f, false, 0, 2);
		Monster->GetAIController()->DrawRadial(Monster->GetWorld(), TopDebugMatrix, Radius, 360.0f, Color, 10, 0.1f, false, 0, 2);
	}

	FVector Box = FVector(Radius, Radius, Monster->GetAttack1Range().M_Atk_Height);
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

					if (TargetAngle <= (360.0f * 0.5f))
					{
						return true;
					}
				}
			}	
		}
	}
	

	return false;
}

bool UBTServiceAttackJudge::AttackCheck(AMonster* Monster, FVector Center, float Radius, float Height, float Angle, float AttackAxis, FColor Color)
{
	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));


		FRotator Rotation = FRotator::ZeroRotator;
		Rotation = Monster->GetActorRotation() + FRotator(0.0f, AttackAxis, 0.0f);
		Rotation.Pitch = 0;
		BottomLine.SetRotation(FQuat(Rotation));


		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Height));



		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();


		Monster->GetAIController()->DrawRadial(GetWorld(), BottomDebugMatrix, Radius, Angle, Color, 10, 0.5f, false, 0, 2);
		Monster->GetAIController()->DrawRadial(GetWorld(), TopDebugMatrix, Radius, Angle, Color, 10, 0.5f, false, 0, 2);
	
	}

	FVector ForwardVector = Monster->GetActorForwardVector();
	ForwardVector.Normalize();
	FVector AttackDirection = ForwardVector.RotateAngleAxis(AttackAxis, FVector::UpVector);
	AttackDirection.Normalize();




	FVector Box = FVector(Radius, Radius, Height);
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);

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

					FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
					TargetDir = TargetDir.GetSafeNormal();


					float Radian = FVector::DotProduct(AttackDirection, TargetDir);
					//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));
					//STARRYLOG(Error, TEXT("%f"), TargetAngle);
					if (TargetAngle <= (Angle * 0.5f))
					{
						if (nullptr == Player) {
							return false;
						}

						return true;
					}

				}

			}
		}
	}

	return false;
}

void UBTServiceAttackJudge::MeleeAttck(class ABellarus* Bellarus, FVector Center)
{

	InTail = AttackCheck(Bellarus, Center, Bellarus->GetTailData()->M_Atk_Radius, Bellarus->GetTailData()->M_Atk_Height, Bellarus->GetTailData()->M_Atk_Angle, 180.0f, FColor::Yellow);
	InWing_L = AttackCheck(Bellarus, Center, Bellarus->GetWingData()->M_Atk_Radius, Bellarus->GetWingData()->M_Atk_Height, Bellarus->GetWingData()->M_Atk_Angle, -(Bellarus->GetWingData()->M_Atk_Angle / 2.0f), FColor::Yellow);
	InWing_R = AttackCheck(Bellarus, Center, Bellarus->GetWingData()->M_Atk_Radius, Bellarus->GetWingData()->M_Atk_Height, Bellarus->GetWingData()->M_Atk_Angle, Bellarus->GetWingData()->M_Atk_Angle / 2.0f, FColor::Yellow);


	if (InTail)
	{
		Bellarus->SetBattleState();

		if (InWing_L) {

			auto ran = FMath::RandRange(1, 100);
			if (ran <= 30)
			{
				Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingLKey(true);
			}
			else {
				Cast<ABellarusAIController>(Bellarus->GetAIController())->SetTailKey(true);
			}

		}
		else if (InWing_R) {
			auto ran = FMath::RandRange(1, 100);
			if (ran <= 30)
			{
				Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingRKey(true);
			}
			else {
				Cast<ABellarusAIController>(Bellarus->GetAIController())->SetTailKey(true);
			}
		}
		else {
			Cast<ABellarusAIController>(Bellarus->GetAIController())->SetTailKey(true);
		}
	}
	else if (InWing_L) {
		Bellarus->SetBattleState();
		Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingLKey(true);

	}
	else if (InWing_R) {
		Bellarus->SetBattleState();
		Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingRKey(true);
	}
	else {

		FVector FrontVector = Bellarus->GetActorForwardVector();
		FrontVector.Normalize();

		auto Instance = Cast<USTGameInstance>(Bellarus->GetGameInstance());
		FVector PlayerVector = Instance->GetPlayer()->GetActorLocation() - Bellarus->GetActorLocation();
		PlayerVector.Normalize();

		PlayerVector.Z = 0.0f;
		FrontVector.Z = 0.0f;

		float dot = FVector::DotProduct(FrontVector, PlayerVector);
		float AcosAngle = FMath::Acos(dot);
		float AngleDegree = FMath::RadiansToDegrees(AcosAngle);

		if (AngleDegree > 90)
		{
			auto ran = FMath::RandRange(1, 100);
			if (ran <= 80)
			{
				Bellarus->SetBattleState();
				Cast<ABellarusAIController>(Bellarus->GetAIController())->SetTailKey(true);
				return;
			}

			ran = FMath::RandRange(1, 100);
			if (ran <= 50)
			{
				Bellarus->SetBattleState();
				ran = FMath::RandRange(1, 100);

				if (ran <= 50)
				{

					Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingLKey(true);

				}
				else {

					Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingRKey(true);
				}

				return;
			}


		}
		else {
			auto ran = FMath::RandRange(1, 100);
			if (ran <= 50)
			{
				Bellarus->SetBattleState();
				ran = FMath::RandRange(1, 100);

				if (ran <= 50)
				{

					Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingLKey(true);

				}
				else {

					Cast<ABellarusAIController>(Bellarus->GetAIController())->SetWingRKey(true);
				}

				return;
			}
		}
	}
}

void UBTServiceAttackJudge::ShieldFristRangeAttackCheck(ABellarus* Bellarus, FVector Center)
{

	bool InSwirlAttack = AttackCheck(Bellarus, Center, Bellarus->GetSwirlData()->M_Atk_Radius, Bellarus->GetSwirlData()->M_Atk_Height, Bellarus->GetSwirlData()->M_Atk_Angle, 0.0f,  FColor::Purple);
	bool InFeatherAttack = AttackCheck(Bellarus, Center, Bellarus->GetFeatherData()->M_Atk_Radius, Bellarus->GetFeatherData()->M_Atk_Height, Bellarus->GetFeatherData()->M_Atk_Angle, 0.0f, FColor::Purple);


	if (InSwirlAttack)
	{

		if (Bellarus->GetToPlayerDistance() > Bellarus->GetSwirlData()->M_Atk_Radius * 0.95f && InFeatherAttack)
		{
			auto ran = FMath::RandRange(1, 100);
			if (ran <= 70) {
				Bellarus->SetBattleState();
				Cast<ABellarusAIController>(Bellarus->GetAIController())->SetSwirlKey(true);
				return;
			}
			ran = FMath::RandRange(1, 100);
			if (ran <= 50) {
				Bellarus->SetBattleState();
				Cast<ABellarusAIController>(Bellarus->GetAIController())->SetFeatherKey(true);
				return;
			}
		}
		else {
			Bellarus->SetBattleState();
			Cast<ABellarusAIController>(Bellarus->GetAIController())->SetSwirlKey(true);
		}

	}
	else {
		if (InFeatherAttack)
		{
			Bellarus->SetBattleState();
			Cast<ABellarusAIController>(Bellarus->GetAIController())->SetFeatherKey(true);
		}
	}


}


