// Fill out your copyright notice in the Description page of Project Settings.


#include "Bouldelith.h"
#include"../../STGameInstance.h"
#include "BdAIController.h"

ABouldelith::ABouldelith()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABdAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	MonsterInfo.Monster_Code = 2;


	InitMonsterInfo();
	InitAttack1Data();
	InitBouldelithInfo();
	InitCollision();
	InitMesh();
	InitAnime();

	bTestMode = false;
	
	MonsterWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 460.0f));
	MonsterWidget->SetRelativeScale3D(FVector(0.5, 0.5f, 0.5f));

	IsAttackNum = 0;

	FindRimitTime = 5.0f;
	FindRimitTimer = 0.0f;
	RotateSpeed = 1.0f;

	StateChangeParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("StateChangeParticle"));
	StateChangeParticle->SetupAttachment(GetMesh());
	StateChangeParticle->SetAutoActivate(false);
}
#pragma region Init
void ABouldelith::InitMonsterInfo()
{
	MonsterInfo.Monster_Rank = EEnemyRank::e_Common;

	MonsterInfo.Monster_Code = 2;

	FMonsterDataTable* NewData = GetMontserData(MonsterInfo.Monster_Code);

	MonsterInfo.M_Atk_Type = NewData->M_Atk_Type;
	MonsterInfo.M_Max_HP = NewData->M_Max_HP;
	MonsterInfo.M_HP = MonsterInfo.M_Max_HP;
	MonsterInfo.M_MoveSpeed = NewData->M_MoveSpeed;
	MonsterInfo.M_Skill_Type_01 = NewData->M_Skill_Type_01;
	MonsterInfo.M_Skill_Type_02 = NewData->M_Skill_Type_02;
	MonsterInfo.M_Skill_Type_03 = NewData->M_Skill_Type_03;
	MonsterInfo.M_Skill_Type_04 = NewData->M_Skill_Type_04;
	MonsterInfo.Spirit_Soul = NewData->Spirit_Soul;


	MonsterInfo.M_Attacked_Time = 0.5f;
	MonsterInfo.PatrolArea = 600.0f;
	MonsterInfo.M_MaxFollowTime = 5.0f;
	MonsterInfo.BattleWalkMoveSpeed = 90.0f;


	MonsterInfo.M_Sight_Angle = 150.0f;
	MonsterInfo.M_Sight_Radius = 600.0f;
	MonsterInfo.M_Sight_Height = 300.0f;

	////Attack Range

	FMonsterSkillDataTable* NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_01);
	MonsterInfo.Attack1Range.M_Atk_Angle = NewSkillData->M_Atk_Angle;
	MonsterInfo.Attack1Range.M_Atk_Height = NewSkillData->M_Atk_Height;
	MonsterInfo.Attack1Range.M_Atk_Radius = NewSkillData->M_Atk_Radius;

	NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_02);
	MonsterInfo.Attack2Range.M_Atk_Angle = NewSkillData->M_Atk_Angle;
	MonsterInfo.Attack2Range.M_Atk_Height = NewSkillData->M_Atk_Height;
	MonsterInfo.Attack2Range.M_Atk_Radius = NewSkillData->M_Atk_Radius;

	NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_03);
	MonsterInfo.Attack3Range.M_Atk_Angle = NewSkillData->M_Atk_Angle;
	MonsterInfo.Attack3Range.M_Atk_Height = NewSkillData->M_Atk_Height;
	MonsterInfo.Attack3Range.M_Atk_Radius = NewSkillData->M_Atk_Radius;



	NewSkillData = GetMontserSkillData(MonsterInfo.M_Skill_Type_04);
	MonsterInfo.Attack4Range.M_Atk_Angle = NewSkillData->M_Atk_Angle;
	MonsterInfo.Attack4Range.M_Atk_Height = NewSkillData->M_Atk_Height;
	MonsterInfo.Attack4Range.M_Atk_Radius = NewSkillData->M_Atk_Radius;

	MonsterInfo.S_Attack_Time = 8.0f;
	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;



	MonsterInfo.KnockBackPower = 50.0f;
	MonsterInfo.DeadWaitTime = 1.0f;

	MonsterInfo.TraceRange = 1000.0f;

	MonsterInfo.M_AttackPercent = 80.0f;

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;


	MonsterInfo.M_FSM_DPS = 40.0f;

}
void ABouldelith::InitBouldelithInfo()
{
	BouldelithInfo.AnotherMonsterStateCheckRange = 1000.0f;
	BouldelithInfo.DefaultBattleRunSpeed = MonsterInfo.M_MoveSpeed*1.5f;
	BouldelithInfo.BackstepCoolTime = 10.0f;
	BouldelithInfo.BrokenAnimePlayRate = 1.3f;
	BouldelithInfo.M_PlayerMaxDistance = 2000.0f;


	BouldelithInfo.Attack3_Distance = 1000.0f;


	BouldelithInfo.BattleDistance = 2200.0f;
}
void ABouldelith::InitCollision()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(200.0f);
	GetCapsuleComponent()->SetCapsuleRadius(88.0f);
}
void ABouldelith::InitMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster/Bouldelith/Idle/M_Bd_Idle"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()), FRotator(0.0f, 270.0f, 0.0f));
	
	float Scale = FMath::RandRange(0.9f, 1.1f);
	
	GetMesh()->SetRelativeScale3D(FVector(Scale, Scale, Scale));
}
void ABouldelith::InitAnime()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님 인스턴스 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> BouldelithAnim(TEXT("/Game/BluePrint/Monster/Bouldelith/BouldelithAnim"));
	if (BouldelithAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BouldelithAnim.Class);
	}
}
void ABouldelith::IsDodgeTimeOn()
{
	bIsDodgeTime = true;
}

void ABouldelith::IsDodgeTimeOff()
{
	bIsDodgeTime = false;
}

#pragma endregion
void ABouldelith::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
}
void ABouldelith::BattleIdle()
{
	BdAnimInstance->PlayBattleIdleMontage();
	MonsterAIController->StopMovement();
}
void ABouldelith::BattleWalk()
{
	BdAnimInstance->PlayBattleWalkMontage();
	MonsterAIController->StopMovement();
}
#pragma region Attack
void ABouldelith::Attack1()
{
	InitAttack1Data();

	BdAnimInstance->PlayAttack1Montage();
	IsAttackNum = 1;
	
	MonsterAIController->StopMovement();
}
void ABouldelith::Attack2()
{
	InitAttack2Data();

	
	BdAnimInstance->PlayAttack2Montage();
	IsAttackNum = 2;
	MonsterAIController->StopMovement();
}

void ABouldelith::Attack3()
{
	InitAttack3Data();
	IsAttackNum = 3;
	BdAnimInstance->PlayAttack3Montage();
	MonsterAIController->StopMovement();
	bIsRush = true;

}
void ABouldelith::Attack4()
{
	InitAttack4Data();
	IsAttackNum = 4;
	BdAnimInstance->PlayAttack4Montage();
	MonsterAIController->StopMovement();
}
void ABouldelith::Attack5()
{
	BdAnimInstance->PlayAttack1ComboMontage();
	IsAttackNum = 5;
	MonsterAIController->StopMovement();
}
void ABouldelith::LeftAttackCheck()
{
	// hitcheck======================================

	if (bTestMode)
	{
		FTransform BottomLine = GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation()-FVector(0.0f,0.0f,120.0f));

		
		FRotator Rotation = FRotator::ZeroRotator;
		Rotation = GetActorRotation() + FRotator(0.0f, -50.0f, 0.0f);
		Rotation.Pitch = 0;
		BottomLine.SetRotation(FQuat(Rotation));


		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, 250.0f));



		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();
		if (bIsDodgeTime) {
			GetAIController()->DrawRadial(GetWorld(), BottomDebugMatrix, 500.0f, 200.0f, FColor::Green, 10, 0.1f, false, 0, 2);
			GetAIController()->DrawRadial(GetWorld(), TopDebugMatrix, 500.0f, 200.0f, FColor::Green, 10, 0.1f, false, 0, 2);
		}
		else {
			GetAIController()->DrawRadial(GetWorld(), BottomDebugMatrix, 500.0f, 200.0f, FColor::Red, 10, 0.5f, false, 0, 2);
			GetAIController()->DrawRadial(GetWorld(), TopDebugMatrix, 500.0f, 200.0f, FColor::Red, 10, 0.5f, false, 0, 2);
		}
	}

	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();
	FVector AttackDirection = ForwardVector.RotateAngleAxis(-50.0f, FVector::UpVector);
	AttackDirection.Normalize();


	FVector Center = GetLocation();


	FVector Box = FVector(500.0f, 500.0f, 300.0f);
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
				if (GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						GetWorld(),
						GetLocation(), // SphereTrace 시작 위치
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
						GetWorld(),
						GetLocation(),
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
				for (int i = 0; i < Hits.Num();++i)
				{
					//STARRYLOG(Warning,TEXT("%s"), *Hits[i].GetActor()->GetName());
					Player = Cast<AIreneCharacter>(Hits[i].Actor);
					if (Player!=nullptr	)
					{
						break;	
					}
				}
				if (bTraceResult && !(nullptr == Player))
				{
					//2차 탐지
					//if (Monster->GetTestMode())
						//STARRYLOG(Warning, TEXT("Attack in Player SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - GetLocation();
					TargetDir = TargetDir.GetSafeNormal();

					
					float Radian = FVector::DotProduct(AttackDirection, TargetDir);
					//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));
					//STARRYLOG(Error, TEXT("%f"), TargetAngle);
					if (TargetAngle <= (200.0f * 0.5f))
					{
						if (nullptr == Player) {
							return;
						}



						if (bIsDodgeTime)
						{
							//STARRYLOG(Error, TEXT("Dodge On"));
							PerfectDodgeOn();
							return;
						}
						else {

						
							bIsDodgeTime = false;
							PerfectDodgeOff();
							UGameplayStatics::ApplyDamage(Player, MonsterInfo.M_Skill_Atk, NULL, this, NULL);
							return;
						}
					}
				
                 }

			}
		}
	}
	BouldelithInfo.AttackFailedStack++;

	PerfectDodgeOff();
}

void ABouldelith::RightAttackCheck()
{

	// hitcheck======================================

	if (bTestMode)
	{
		FTransform BottomLine = GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, 120.0f));


		FRotator Rotation = FRotator::ZeroRotator;
		Rotation = GetActorRotation() + FRotator(0.0f, 50.0f, 0.0f);
		Rotation.Pitch = 0;
		BottomLine.SetRotation(FQuat(Rotation));


		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, 250.0f));



		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();
		if (bIsDodgeTime) {
			GetAIController()->DrawRadial(GetWorld(), BottomDebugMatrix, 500.0f, 200.0f, FColor::Green, 10, 0.1f, false, 0, 2);
			GetAIController()->DrawRadial(GetWorld(), TopDebugMatrix, 500.0f, 200.0f, FColor::Green, 10, 0.1f, false, 0, 2);
		}
		else {
			GetAIController()->DrawRadial(GetWorld(), BottomDebugMatrix, 500.0f, 200.0f, FColor::Red, 10, 0.5f, false, 0, 2);
			GetAIController()->DrawRadial(GetWorld(), TopDebugMatrix, 500.0f, 200.0f, FColor::Red, 10, 0.5f, false, 0, 2);
		}
	}

	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();
	FVector AttackDirection = ForwardVector.RotateAngleAxis(50.0f, FVector::UpVector);
	AttackDirection.Normalize();


	FVector Center = GetLocation();


	FVector Box = FVector(500.0f, 500.0f, 300.0f);
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
				if (GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						GetWorld(),
						GetLocation(), // SphereTrace 시작 위치
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
						GetWorld(),
						GetLocation(),
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
					//STARRYLOG(Warning, TEXT("%s"), *Hits[i].GetActor()->GetName());
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

					FVector TargetDir = Player->GetActorLocation() - GetLocation();
					TargetDir = TargetDir.GetSafeNormal();


					float Radian = FVector::DotProduct(AttackDirection, TargetDir);
					//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));
					//STARRYLOG(Error, TEXT("%f"), TargetAngle);
					if (TargetAngle <= (200.0f * 0.5f))
					{
						if (nullptr == Player) {
							return;
						}



						if (bIsDodgeTime)
						{
							//STARRYLOG(Error, TEXT("Dodge On"));
							PerfectDodgeOn();
							return;
						}
						else {

							PerfectDodgeOff();
							bIsDodgeTime = false;
							UGameplayStatics::ApplyDamage(Player, MonsterInfo.M_Skill_Atk , NULL, this, NULL);
							return;
						}
					}

				}

			}
		}
	}
	BouldelithInfo.AttackFailedStack++;
	PerfectDodgeOff();

}

void ABouldelith::AttackCheck3()
{

	FHitResult Hit;

	//By 성열현
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		Hit,
		GetActorLocation() + (GetActorForwardVector() + GetMeleeAttackRange()) + FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2.0f),
		GetActorLocation() + (GetActorForwardVector() + GetMeleeAttackRange()) + FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2.0f),
		FRotationMatrix::MakeFromZ(GetActorForwardVector() ).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(GetCapsuleComponent()->GetScaledCapsuleRadius() * 1.5f),
		Params);

	if (bTestMode)
	{
		FVector TraceVec = GetActorForwardVector() + GetMeleeAttackRange();
		FVector Center = GetLocation() + TraceVec * 0.5f + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		float HalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 0.1f;

		DrawDebugCapsule(GetWorld(),
			Center,
			HalfHeight,
			GetCapsuleComponent()->GetScaledCapsuleRadius()*1.5f,
			CapsuleRot,
			DrawColor,
			false,
			DebugLifeTime);
	}

	if (bResult)
	{
		auto Player = Cast<AIreneCharacter>(Hit.Actor);
		if (nullptr == Player)
			return;
		if (bIsDodgeTime)
		{
			PerfectDodgeOn();
			return;
		}
	}

	PerfectDodgeOff();
}

void ABouldelith::AttackCheck4()
{

	// hitcheck======================================

	if (bTestMode)
	{
		FTransform BottomLine = GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, 120.0f));
		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, 250.0f));



		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

		if (bIsDodgeTime) {
			GetAIController()->DrawRadial(GetWorld(), BottomDebugMatrix, 500.0f, 360.0f, FColor::Green, 10, 0.1f, false, 0, 2);
			GetAIController()->DrawRadial(GetWorld(), TopDebugMatrix, 500.0f, 360.0f, FColor::Green, 10, 0.1f, false, 0, 2);
		}
		else {
			GetAIController()->DrawRadial(GetWorld(), BottomDebugMatrix, 500.0f, 360.0f, FColor::Red, 10, 0.5f, false, 0, 2);
			GetAIController()->DrawRadial(GetWorld(), TopDebugMatrix, 500.0f, 360.0f, FColor::Red, 10, 0.5f, false, 0, 2);
		}
	}

	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.Normalize();
	
	FVector Center = GetLocation();
	

	FVector Box = FVector(500.0f, 500.0f, 300.0f);
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
			STARRYLOG(Warning, TEXT("%s"), *OverlapResult.GetActor()->GetName());
			AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore;
				bool bTraceResult;
				if (GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						GetWorld(),
						GetLocation(), // SphereTrace 시작 위치
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
						GetWorld(),
						GetLocation(),
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
					STARRYLOG(Warning, TEXT("%s"), *Hits[i].GetActor()->GetName());
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

					FVector TargetDir = Player->GetActorLocation() - GetLocation();
					TargetDir = TargetDir.GetSafeNormal();


					float Radian = FVector::DotProduct(ForwardVector, TargetDir);
					//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));
					STARRYLOG(Error, TEXT("%f"), TargetAngle);
					if (TargetAngle <= (360.0f * 0.5f))
					{
						if (nullptr == Player) {
							return;
						}

						if (bIsDodgeTime)
						{
							STARRYLOG(Error, TEXT("Dodge On"));
							PerfectDodgeOn();
							return;
						}
						else {

							
							bIsDodgeTime = false;
							PerfectDodgeOff();
							UGameplayStatics::ApplyDamage(Player, (MonsterInfo.M_Skill_Atk), NULL, this, NULL);
							return;
						}
					}

				}

			}
		}
	}
	PerfectDodgeOff();
	
}
void ABouldelith::DodgeCheck()
{

	switch (IsAttackNum)
	{
	case 1:
		RightAttackCheck();
		break;
	case 2:
		LeftAttackCheck();
		break;
	case 3:
		AttackCheck3();
		break;
	case 4:
		AttackCheck4();
		break;
	case 5:
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region Backstep
void ABouldelith::Backstep()
{
	MonsterAIController->StopMovement();
	BdAnimInstance->PlayBackstepMontage();
}
bool ABouldelith::GetIsUseBackstep()
{
	return bIsUseBackstep;
}
void ABouldelith::SetIsUseBackstep(bool Value)
{
	bIsUseBackstep = Value;
}

void ABouldelith::SetBattleRunState(bool State)
{
	auto AIController = Cast<ABdAIController>(GetAIController());
	if (AIController != nullptr)
	{
		AIController->SetBattleRunKey(State);


	}
}

void ABouldelith::SetStatueState(bool State)
{
	auto AIController = Cast<ABdAIController>(GetAIController());
	if (AIController != nullptr)
	{
		AIController->SetStatueKey(State);
	}

	if (!State)
	{
		StateChangeParticle->SetActive(true, true);
	}

}

float ABouldelith::GetPlayerMaxDistance() const
{
	return BouldelithInfo.M_PlayerMaxDistance;
}

float ABouldelith::GetAttack3Distance() const
{
	return	BouldelithInfo.Attack3_Distance;
}

float ABouldelith::GetRotateSpeed() const
{
	return RotateSpeed;
}

#pragma endregion

UBdAnimInstance* ABouldelith::GetBouldelithAnimInstance() const
{
	return BdAnimInstance;
}
float ABouldelith::GetAnotherMonsterStateCheckRange()
{
	return BouldelithInfo.AnotherMonsterStateCheckRange;
}
#pragma region BattleRun
void ABouldelith::BattleRun()
{
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.BattleWalkMoveSpeed;


	BdAnimInstance->PlayBattleRunMontage();
}
void ABouldelith::AddBattleRunSpeed(float Value)
{
	BouldelithInfo.CurrentBattleRunSpeed += Value;
	GetCharacterMovement()->MaxWalkSpeed = BouldelithInfo.CurrentBattleRunSpeed;
}
void ABouldelith::UpgradeBattleRunAnim()
{
	BdAnimInstance->UpgradeBattleRun();
}
float ABouldelith::GetBattleRunSpeed()
{
	return BouldelithInfo.CurrentBattleRunSpeed;
}
void ABouldelith::ResetBattleRunSpeed()
{
	BouldelithInfo.CurrentBattleRunSpeed = BouldelithInfo.DefaultBattleRunSpeed;
}
void ABouldelith::SetIsChangeBattleRunStateToAttackedState(bool Value)
{
	bIsChangeBattleRunStateToAttackedState = Value;
}
bool ABouldelith::GetIsChangeBattleRunStateToAttackedState()
{
	return bIsChangeBattleRunStateToAttackedState;
}
#pragma endregion
#pragma region Patrol
TArray<ABouldelithPatrolTarget*> ABouldelith::GetPatrolList()
{
	return PatrolList;
}
ABouldelithPatrolTarget* ABouldelith::GetUsePatrol()
{
	return UsePatrol;
}
void ABouldelith::SetUsePatrol(ABouldelithPatrolTarget* PatrolTarget)
{
	UsePatrol = PatrolTarget;
}
#pragma endregion
int ABouldelith::GetAttackFailedStack()
{
	return BouldelithInfo.AttackFailedStack;
}
void ABouldelith::ResetAttackFailedStack()
{
	BouldelithInfo.AttackFailedStack = 0;
}
float ABouldelith::GetHpPercent()
{
	return (MonsterInfo.M_HP / MonsterInfo.M_Max_HP) * 100.0f;
}
void ABouldelith::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bIsRush)
	{
		if (!bIsPlayerRushHit)
		{
			if (Cast<AIreneCharacter>(OtherActor))
			{
				auto Player = Cast<AIreneCharacter>(OtherActor);

				
				UGameplayStatics::ApplyDamage(Player, (MonsterInfo.M_Skill_Atk), NULL, this, NULL);
				
				bIsPlayerRushHit = true;
				PerfectDodgeOff();
			}
		}
	/*	if (!bIsWallRushHit)
		{
			if (Cast<UStaticMeshComponent>(OtherComponent))
			{
				auto MeshComponent = Cast<UStaticMeshComponent>(OtherComponent);
				FString FindName = "Wall";
				FString CompCollisionName = MeshComponent->GetCollisionProfileName().ToString();

				if (FindName == CompCollisionName)
				{
					CalcHp(MonsterInfo.M_Skill_Atk);
					if (!bIsDead)
					{
						auto BdAIController = Cast<ABdAIController>(MonsterAIController);
						BdAIController->WallGroggy();
						MonsterAnimInstance->PlayGroggyMontage();
					}
					bIsWallRushHit = true;
					PerfectDodgeOff();
				}
			}
		}*/
	}
}
void ABouldelith::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsUseBackstep)
	{
		BackstepCoolTimer += DeltaTime;

		if (BackstepCoolTimer >= BouldelithInfo.BackstepCoolTime)
		{
			bIsUseBackstep = false;
			BackstepCoolTimer = 0.0f;
		}
	}

	if (bIsDodgeTime)
	{
		DodgeCheck();
	}

	if (CurState == EMontserState::Support || MonsterAIController->GetIsTraceState() == true)
	{
		if (MonsterAIController->GetIsFindPlayer() == false)
		{
			FindRimitTimer += DeltaTime;
			if (FindRimitTimer >= FindRimitTime)
			{
				MonsterAIController->SetBattleState(false);
				MonsterAIController->SetNormalState(true);
				MonsterAIController->SetSupportState(false);
				MonsterAIController->SetTraceKey(false);

				CurState = EMontserState::Normal;
				FindRimitTimer = 0.0f;
			}
		}
		else {

			FindRimitTimer = 0.0f;
		}
	}



}
void ABouldelith::BeginPlay()
{
	Super::BeginPlay();

	BdAnimInstance->BackstepEnd.AddLambda([this]() -> void {
		BackstepEnd.Broadcast();
		});
	BdAnimInstance->Attack1End.AddLambda([this]() -> void {
		Attack1End.Broadcast();
		});
	BdAnimInstance->Attack2End.AddLambda([this]() -> void {
		Attack2End.Broadcast();
		});
	BdAnimInstance->Attack3End.AddLambda([this]() -> void {
		Attack3End.Broadcast();
		bIsRush = false;
		bIsPlayerRushHit = false;
		bIsWallRushHit = false;
		});
	BdAnimInstance->Attack4End.AddLambda([this]() -> void {
		Attack4End.Broadcast();

		});
	BdAnimInstance->AttackedEnd.AddLambda([this]() -> void {
		bIsAttacked = false;
		AttackedEnd.Broadcast();
		});
	BdAnimInstance->Death.AddLambda([this]() -> void {
		if (bIsDead)
		{
			bDeadWait = true;
			SetActorEnableCollision(false);
			BdAnimInstance->Montage_Stop(500.0f, BdAnimInstance->GetCurrentActiveMontage());
		}
		});
	BdAnimInstance->Attack1.AddUObject(this, &ABouldelith::RightAttackCheck);
	BdAnimInstance->Attack2.AddUObject(this, &ABouldelith::LeftAttackCheck);
	BdAnimInstance->Attack4.AddUObject(this, &ABouldelith::AttackCheck4);

	BdAnimInstance->Right.AddLambda([this]() -> void {
		InitAttack1Data();
		IsAttackNum = 1;
		});

	BdAnimInstance->Left.AddLambda([this]() -> void {
		InitAttack2Data();
		IsAttackNum = 2;
		});

	SoundInstance->SetHitSound("event:/StarryTail/Enemy/SFX_Hit");


	//Perfect Dodge
	BdAnimInstance->DodgeTimeOn.AddLambda([this]() -> void {
		DodgeTimeOn.Broadcast();
		});
	BdAnimInstance->DodgeTimeOff.AddLambda([this]() -> void {
		DodgeTimeOff.Broadcast();
		PerfectDodgeOff();
		});



	MonsterAnimInstance = BdAnimInstance;
	auto BdAIController = Cast<ABdAIController>(MonsterAIController);
	if (BdAIController != nullptr)
	{
		SetStatueState(true);
		BdAnimInstance->StopAllMontages(0.0f);

		if (WalkPoint != nullptr)
			BdAIController->SetWalkPoint(WalkPoint->GetActorLocation());
	}

	MonsterShield->InitShieldEffect(MonsterInfo.MaxStackCount);
	
}
void ABouldelith::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABouldelith::OnHit);
}
void ABouldelith::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	

	BdAnimInstance = Cast<UBdAnimInstance>(GetMesh()->GetAnimInstance());
}