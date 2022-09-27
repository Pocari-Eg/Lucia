// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceBdAttackTrace.h"
#include "../../MonsterAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

#include "../../BTService/BTServiceMobDetectPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
UBTServiceBdAttackTrace::UBTServiceBdAttackTrace()
{
	NodeName = TEXT("ATTACKBDTRACE");
	Interval = 0.1f;
}
void UBTServiceBdAttackTrace::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackCoolKey) == false&&
		OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackingKey) == false) {
		auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
		if (nullptr == Monster)
			return;



		FVector Center = Monster->GetLocation();
			if (Monster->GetState() == EMontserState::Battle) {

			
				if (Attack2Trace(Monster, OwnerComp, Center))
					{

				

							auto ran = FMath::RandRange(1, 100);
							STARRYLOG(Error, TEXT("Percent : %d"), ran);
							if (ran <= 50)
							{
								Monster->GetAIController()->OnAttack(2);
								return;
							}

					}
					else {
					if (Attack1Trace(Monster, OwnerComp, Center)) {
						auto ran = FMath::RandRange(1, 100);
						if (ran <= 50)
						{
							Monster->GetAIController()->OnAttack(1);
							return;
						}

						return;
					}
					}
	
	
	     	}


		

		


	/*	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackCoolKey) == false) {

			if (bIsAttack1In)
			{
				bIsAttack3In = false;
			}
			else if (bIsAttack2In)
			{
				Monster->GetAIController()->OnAttack(3);
			}
			else if (bIsAttack3In)
			{
				bIsAttack1In = false;
			}
			
			
		}*/
	}
}

bool UBTServiceBdAttackTrace::Attack1Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center)
{
	bIsAttack1In = false;

	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();

		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	
		
		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetAtkHeight()));
		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

		Monster->GetAIController()->DrawRadial(Monster->GetWorld(), BottomDebugMatrix, Monster->GetAttack1Range().M_Atk_Radius, Monster->GetAttack1Range().M_Atk_Angle, FColor::Red, 10, 0.1f, false, 0, 2);
		Monster->GetAIController()->DrawRadial(Monster->GetWorld(), TopDebugMatrix, Monster->GetAttack1Range().M_Atk_Radius, Monster->GetAttack1Range().M_Atk_Angle, FColor::Red, 10, 0.1f, false, 0, 2);
	}

	FVector Box = FVector(Monster->GetAttack1Range().M_Atk_Radius, Monster->GetAttack1Range().M_Atk_Radius, Monster->GetAttack1Range().M_Atk_Height);
	//�𸣺� �ֺ� ���� 200 �ȿ� �ִ� ���� Ž��, EnemyDetect Ʈ���̽� ä�� ���
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = Monster->GetWorld()->OverlapMultiByChannel( // ������ Collision FCollisionShape�� �浹�� ���� ���� 
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
				//if (Monster->GetTestMode())
					//STARRYLOG(Warning, TEXT("Detect Player in DetectSphere"));

				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore; // ������ ���� ����?
				bool bTraceResult;

				// https://blog.daum.net/peace-day/22
				// TraceTypeQuery�� �ݸ��� �������� Ʈ���̽� �������� 1���� ���������� �ο���
				if (Monster->GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						Monster->GetWorld(),
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
					//2�� Ž��
					//if (Monster->GetTestMode())
						//STARRYLOG(Warning, TEXT("Attack in Player SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit�� �������� ���ϴ� ���Ϳ� �÷��̾�� ���ϴ� ������ ������ ���� ������ ���� �� �ִ�. ������� Radian
					float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
					//���� ������� Cos{^-1}(A dot B / |A||B|)�̱� ������ ��ũ�ڻ��� �Լ��� ������ְ� Degree�� ��ȯ���ش�.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					if (TargetAngle <= (Monster->GetAttack1Range().M_Atk_Angle * 0.5f))
					{
						bIsAttack1In = true;
						return true;
					}
					else {
						return false;
					}

				}
				else {
					return false;
				}

			}
			else {
			
				return false;
			}

		}
	}
	else {

		return false;
	}

	return false;
}

bool UBTServiceBdAttackTrace::Attack2Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center)
{
	bIsAttack2In = false;

	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetAtkHeight()));

		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

		Monster->GetAIController()->DrawRadial(Monster->GetWorld(), BottomDebugMatrix, Monster->GetAttack2Range().M_Atk_Radius, Monster->GetAttack2Range().M_Atk_Angle, FColor::Blue, 10, 0.1f, false, 0, 2);
		Monster->GetAIController()->DrawRadial(Monster->GetWorld(), TopDebugMatrix, Monster->GetAttack2Range().M_Atk_Radius, Monster->GetAttack2Range().M_Atk_Angle, FColor::Blue, 10, 0.1f, false, 0, 2);
	}


	FVector Box = FVector(Monster->GetAttack2Range().M_Atk_Radius, Monster->GetAttack2Range().M_Atk_Radius, Monster->GetAttack2Range().M_Atk_Height);
	//�𸣺� �ֺ� ���� 200 �ȿ� �ִ� ���� Ž��, EnemyDetect Ʈ���̽� ä�� ���
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = Monster->GetWorld()->OverlapMultiByChannel( // ������ Collision FCollisionShape�� �浹�� ���� ���� 
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
				//if (Monster->GetTestMode())
					//STARRYLOG(Warning, TEXT("Detect Player in DetectSphere"));

				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore; // ������ ���� ����?
				bool bTraceResult;

				// https://blog.daum.net/peace-day/22
				// TraceTypeQuery�� �ݸ��� �������� Ʈ���̽� �������� 1���� ���������� �ο���
				if (Monster->GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						Monster->GetWorld(),
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
					//2�� Ž��
					//if (Monster->GetTestMode())
						//STARRYLOG(Warning, TEXT("Attack in Player SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit�� �������� ���ϴ� ���Ϳ� �÷��̾�� ���ϴ� ������ ������ ���� ������ ���� �� �ִ�. ������� Radian
					float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
					//���� ������� Cos{^-1}(A dot B / |A||B|)�̱� ������ ��ũ�ڻ��� �Լ��� ������ְ� Degree�� ��ȯ���ش�.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					if (TargetAngle <= (Monster->GetAttack2Range().M_Atk_Angle * 0.5f))
					{
					
							bIsAttack2In = true;
							return true;
					
					}
					else {
						return false;
					}

				}
				else {
				
					return false;
				}

			}
			else {

				return false;
			}

		}
	}
	else {

		return false;
	}


	return false;
}

bool UBTServiceBdAttackTrace::Attack3Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center)
{

	bIsAttack3In = false;
	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetAtkHeight()));

		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

		Monster->GetAIController()->DrawRadial(Monster->GetWorld(), BottomDebugMatrix, Monster->GetAttack3Range().M_Atk_Radius, Monster->GetAttack3Range().M_Atk_Angle, FColor::Yellow, 10, 0.1f, false, 0, 2);
		Monster->GetAIController()->DrawRadial(Monster->GetWorld(), TopDebugMatrix, Monster->GetAttack3Range().M_Atk_Radius, Monster->GetAttack3Range().M_Atk_Angle, FColor::Yellow, 10, 0.1f, false, 0, 2);
	}

	FVector Box = FVector(Monster->GetAttack3Range().M_Atk_Radius, Monster->GetAttack3Range().M_Atk_Radius, Monster->GetAttack3Range().M_Atk_Height);
	//�𸣺� �ֺ� ���� 200 �ȿ� �ִ� ���� Ž��, EnemyDetect Ʈ���̽� ä�� ���
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = Monster->GetWorld()->OverlapMultiByChannel( // ������ Collision FCollisionShape�� �浹�� ���� ���� 
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

				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore; // ������ ���� ����?
				bool bTraceResult;

				// https://blog.daum.net/peace-day/22
				// TraceTypeQuery�� �ݸ��� �������� Ʈ���̽� �������� 1���� ���������� �ο���
				if (Monster->GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						Monster->GetWorld(),
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
					//2�� Ž��
					//if (Monster->GetTestMode())
						//STARRYLOG(Warning, TEXT("Attack in Player SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit�� �������� ���ϴ� ���Ϳ� �÷��̾�� ���ϴ� ������ ������ ���� ������ ���� �� �ִ�. ������� Radian
					float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
					//���� ������� Cos{^-1}(A dot B / |A||B|)�̱� ������ ��ũ�ڻ��� �Լ��� ������ְ� Degree�� ��ȯ���ش�.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					if (TargetAngle <= (Monster->GetAttack3Range().M_Atk_Angle * 0.5f))
					{
					bIsAttack3In = true;
					return true;					
					}
					else {
						//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
						//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
						return false;
					}

				}
				else {
					//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
					//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
					return false;
				}

			}
			else {
				//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
				//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
				return false;
			}

		}
	}
	else {
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, false);
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
		return false;
	}
	return false;
}

