// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdBattleRun.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskBdBattleRun::UBTTaskBdBattleRun()
{
	NodeName = TEXT("BattleRun");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdBattleRun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->BattleRun();

 auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));
Bouldelith->GetAIController()->MoveToLocation(Player->GetActorLocation());


	return EBTNodeResult::InProgress;
}
void UBTTaskBdBattleRun::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	auto	Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));

	FVector LookVector = Player->GetActorLocation() - Bouldelith->GetLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Bouldelith->SetActorRotation(FMath::RInterpTo(Bouldelith->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), Bouldelith->GetRotateSpeed()));

	if (Bouldelith->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Moving)
	{
		Bouldelith->GetAIController()->MoveToLocation(Player->GetActorLocation());
	}


	Attack4Trace(Bouldelith, OwnerComp, Bouldelith->GetActorLocation());

}

void UBTTaskBdBattleRun::Attack4Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center)
{


	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();

		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));


		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetAttack4Range().M_Atk_Height));
		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

		Monster->GetAIController()->DrawRadial(Monster->GetWorld(), BottomDebugMatrix, Monster->GetAttack4Range().M_Atk_Radius, Monster->GetAttack4Range().M_Atk_Angle, FColor::Red, 10, 0.1f, false, 0, 2);
		Monster->GetAIController()->DrawRadial(Monster->GetWorld(), TopDebugMatrix, Monster->GetAttack4Range().M_Atk_Radius, Monster->GetAttack4Range().M_Atk_Angle, FColor::Red, 10, 0.1f, false, 0, 2);
	}

	FVector Box = FVector(Monster->GetAttack4Range().M_Atk_Radius, Monster->GetAttack4Range().M_Atk_Radius, Monster->GetAttack4Range().M_Atk_Height);
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

					if (TargetAngle <= (Monster->GetAttack4Range().M_Atk_Angle * 0.5f))
					{
						Monster->GetAIController()->OnAttack(4);
						auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
						Bouldelith->SetBattleRunState(false);
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
						return;
					}


				}
				else {
					return;
				}

			}
			else {

				return;
			}

		}
	}
	else {

		return;
	}

}
