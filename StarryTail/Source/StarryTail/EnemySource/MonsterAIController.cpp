// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "../STGameInstance.h"

const FName AMonsterAIController::SpawnPosKey = (TEXT("SpawnPos"));
const FName AMonsterAIController::PatrolPosKey = (TEXT("PatrolPos"));

const FName AMonsterAIController::IsFindKey = (TEXT("bIsFind"));
const FName AMonsterAIController::PlayerKey = (TEXT("Player"));
const FName AMonsterAIController::TraceRangeKey = (TEXT("TraceRange"));

const FName AMonsterAIController::MeleeAttackRangeKey = (TEXT("MeleeAttackRange"));
const FName AMonsterAIController::IsInAttackAreaKey = (TEXT("bIsInAttackArea"));
const FName AMonsterAIController::IsAttackingKey = (TEXT("bIsAttacking"));
const FName AMonsterAIController::IsAttackCoolKey = (TEXT("bIsAttackCool"));

const FName AMonsterAIController::IsAttackedKey = (TEXT("bIsAttacked"));
const FName AMonsterAIController::IsGroggyKey = (TEXT("bIsGroggy"));

const FName AMonsterAIController::IsDeadKey = (TEXT("bIsDead"));

const FName AMonsterAIController::ReturnKey = (TEXT("bReturn"));

//state
const FName AMonsterAIController::NormalStateKey = (TEXT("NormalState"));
const FName AMonsterAIController::BattleStateKey = (TEXT("BattleState"));

const FName AMonsterAIController::SupportStateKey = (TEXT("SupportState"));

const FName AMonsterAIController::Attack1Key = (TEXT("Attack1Active"));
const FName AMonsterAIController::Attack2Key = (TEXT("Attack2Active"));
const FName AMonsterAIController::Attack3Key = (TEXT("Attack3Active"));
const FName AMonsterAIController::Attack4Key = (TEXT("Attack4Active"));

const FName AMonsterAIController::B_IdleKey = (TEXT("B_IdleState"));

const FName AMonsterAIController::BattleMonsterKey = (TEXT("BattleMonster"));
const FName AMonsterAIController::IsShieldOnKey = (TEXT("bIsShieldOn"));

AMonsterAIController::AMonsterAIController()
{

}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}
void AMonsterAIController::Groggy()
{
	SetPlayer();

	Blackboard->SetValueAsBool(IsAttackedKey, true);
	Blackboard->SetValueAsBool(IsGroggyKey, true);
}
void AMonsterAIController::Death()
{
	Blackboard->SetValueAsBool(IsDeadKey, true);
}

void AMonsterAIController::SetPlayer()
{
	if (Blackboard->GetValueAsObject(PlayerKey) != nullptr)
		return;

	auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (GameInstance == nullptr)
	{
		STARRYLOG(Error, TEXT("Not Found STGameInstance"));
	}
	auto Monster = Cast<AMonster>(GetPawn());
	Monster->SetIsBattleState(true);
	Blackboard->SetValueAsObject(PlayerKey, GameInstance->GetPlayer());
}
void AMonsterAIController::SetFind()
{
	auto Monster = Cast<AMonster>(GetPawn());
	Monster->GetMonsterAnimInstance()->PlayWalktoTraceMontage();
	Blackboard->SetValueAsBool(IsFindKey, true);
	SetPlayer();
}
void AMonsterAIController::SetSpawnPos(FVector Position)
{
	Blackboard->SetValueAsVector(SpawnPosKey, Position);
}

void AMonsterAIController::SetInAttackArea(bool Set)
{
	Blackboard->SetValueAsBool(IsInAttackAreaKey, Set);
}

void AMonsterAIController::SetAttackCoolKey(bool Set)
{
	Blackboard->SetValueAsBool(IsAttackCoolKey, Set);
}

void AMonsterAIController::SetNormalState(bool State)
{
	Blackboard->SetValueAsBool(NormalStateKey, State);
   
}

void AMonsterAIController::SetBattleState(bool State)
{
	Blackboard->SetValueAsBool(BattleStateKey, State);
	if (State) {
		SetPlayer();
	}
}

void AMonsterAIController::SetAttackedState(bool State)
{
	Blackboard->SetValueAsBool(IsAttackedKey, State);
}

void AMonsterAIController::SetSupportState(bool State)
{
	Blackboard->SetValueAsBool(SupportStateKey, State);
}

void AMonsterAIController::SetShieldKey(bool State)
{
	Blackboard->SetValueAsBool(IsShieldOnKey, State);

}

void AMonsterAIController::OnAttack(int i)
{
	switch (i)
	{
	case 1:
		Blackboard->SetValueAsBool(Attack1Key, true);
		Blackboard->SetValueAsBool(Attack2Key, false);
		Blackboard->SetValueAsBool(Attack3Key, false);
		Blackboard->SetValueAsBool(Attack4Key, false);
		break;
	case 2:
		Blackboard->SetValueAsBool(Attack1Key, false);
		Blackboard->SetValueAsBool(Attack2Key, true);
		Blackboard->SetValueAsBool(Attack3Key, false);
		Blackboard->SetValueAsBool(Attack4Key, false);
		break;
	case 3:
		Blackboard->SetValueAsBool(Attack1Key, false);
		Blackboard->SetValueAsBool(Attack2Key, false);
		Blackboard->SetValueAsBool(Attack3Key, true);
		Blackboard->SetValueAsBool(Attack4Key, false);
		break;
	case 4:
		Blackboard->SetValueAsBool(Attack1Key, false);
		Blackboard->SetValueAsBool(Attack2Key, false);
		Blackboard->SetValueAsBool(Attack3Key, false);
		Blackboard->SetValueAsBool(Attack4Key, true);
	default:
		break;
	}
}

void AMonsterAIController::OffAttack(int i)
{
	switch (i)
	{
	case 1:
		Blackboard->SetValueAsBool(Attack1Key, false);
		break;
	case 2:
		Blackboard->SetValueAsBool(Attack2Key, false);
		break;
	case 3:
		Blackboard->SetValueAsBool(Attack3Key, false);
		break;
	case 4:
		Blackboard->SetValueAsBool(Attack4Key, false);
		break;
	default:
		break;
	}
}

void AMonsterAIController::SetBattleMonster(AActor* Monster)
{
	Blackboard->SetValueAsObject(BattleMonsterKey, Monster);
}

void AMonsterAIController::InitBattleMonster()
{
	Blackboard->SetValueAsObject(BattleMonsterKey, nullptr);

}


bool AMonsterAIController::GetIsAttacking()
{
	return Blackboard->GetValueAsBool(IsAttackingKey);
}

ULineBatchComponent* AMonsterAIController::GetDebugLineBatcher(const UWorld* InWorld, bool bPersistentLines, float LifeTime, bool bDepthIsForeground)
{
	return (InWorld ? (bDepthIsForeground ? InWorld->ForegroundLineBatcher : ((bPersistentLines || (LifeTime > 0.f)) ? InWorld->PersistentLineBatcher : InWorld->LineBatcher)) : NULL);
}

float AMonsterAIController::GetDebugLineLifeTime(ULineBatchComponent* LineBatcher, float LifeTime, bool bPersistent)
{
	return bPersistent ? -1.0f : ((LifeTime > 0.f) ? LifeTime : LineBatcher->DefaultLifeTime);
}

void AMonsterAIController::DrawRadial(const UWorld* _InWorld, const FMatrix& _TransformMatrix, float _Radius, float _Angle, const FColor& _Color, int32 _Segments, float _LifeTime, bool _bPersistentLines, uint8 _DepthPriority, float _Thickness)
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
