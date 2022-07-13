// Fill out your copyright notice in the Description page of Project Settings.


#include "Scientia.h"
#include "ScAIController.h"
#include "Kismet/GameplayStatics.h"
#include "../../PlayerSource/IreneUIManager.h"
#include "../../STGameInstance.h"
AScientia::AScientia()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AScAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	static ConstructorHelpers::FClassFinder<AFeather> FeatherBlueprint(TEXT("Blueprint'/Game/BluePrint/Monster/BP_Feather'"));
	static ConstructorHelpers::FClassFinder<APiece> PieceBlueprint(TEXT("Blueprint'/Game/BluePrint/Monster/BP_Piece'"));
	InitMonsterInfo();
	InitCollision();
	InitMesh();
	InitAnime();

	bTestMode = false;
	bIsCanChange = true;
	ScInfo.BarrierCount = 3;

	HitEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Enemy/SFX_Hit");
	MonsterWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 380));

	if (FeatherBlueprint.Succeeded())
	{
		FeatherBP = FeatherBlueprint.Class;
	}
	if (PieceBlueprint.Succeeded())
	{
		PieceBP = PieceBlueprint.Class;
	}
}
void AScientia::InitMonsterInfo()
{
	MonsterInfo.Code = 1;

	MonsterInfo.MaxHp = 5000.0f;
	MonsterInfo.Atk = 100.0f;
	MonsterInfo.Def = 100.0f;

	MonsterInfo.BattleWalkMoveSpeed = 400.0f;

	MonsterInfo.DeadWaitTime = 3.0f;
	
	MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
	MonsterInfo.EnemyRank = EEnemyRank::e_Raid;

	
}
void AScientia::InitCollision()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(200.0f);
	GetCapsuleComponent()->SetCapsuleRadius(88.0f);
}
void AScientia::InitMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Animation/Monster/Scientia/BattleIdle/M_Sc_Battleidle"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()), FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
}
void AScientia::InitAnime()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님 인스턴스 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> BouldelithAnim(TEXT("/Game/BluePrint/Monster/Scientia/ScientiaAnimBlueprint"));
	if (BouldelithAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BouldelithAnim.Class);
	}
}
void AScientia::InitScInfo()
{
	ScInfo.AttributeSettingTime = 1.0f;
}
#pragma endregion
#pragma region Get
FString AScientia::GetState()
{
	return ScInfo.State;
}
int AScientia::GetBarrierCount()
{
	return ScInfo.BarrierCount;
}
int AScientia::GetFeatherCount()
{
	return ScInfo.FeatherCount;
}
float AScientia::GetHpPercent()
{
	return (MonsterInfo.CurrentHp / MonsterInfo.MaxHp) * 100.0f;
}
float AScientia::GetFireDefPercent()
{
	return ScInfo.FireBarrier < KINDA_SMALL_NUMBER ? 0.0f : ScInfo.FireBarrier / MaxFireDef;
}
float AScientia::GetWaterDefPercent()
{
	return ScInfo.WaterBarrier < KINDA_SMALL_NUMBER ? 0.0f : ScInfo.WaterBarrier / MaxWaterDef;
}
float AScientia::GetThunderDefPercent()
{
	return ScInfo.ThunderBarrier < KINDA_SMALL_NUMBER ? 0.0f : ScInfo.ThunderBarrier / MaxThunderDef;
}
float AScientia::GetAttack2Speed()
{
	return ScInfo.Attack2Speed;
}
float AScientia::GetAttack3Speed()
{
	return ScInfo.Attack3Speed;
}
float AScientia::GetAttack4Speed()
{
	return ScInfo.Attack4Speed;
}
float AScientia::GetDodgeSpeed()
{
	return ScInfo.DodgeSpeed;
}
float AScientia::GetRushTime()
{
	return ScInfo.RushTime;
}
int AScientia::GetClawSuccessedCount()
{
	return ScInfo.ClawSuccessedCount;
}
bool AScientia::GetIsCanChange()
{
	return bIsCanChange;
}
bool AScientia::GetIsRush()
{
	return bIsRush;
}
#pragma endregion
#pragma region Set
void AScientia::SetState(FString string)
{
	ScInfo.State = string;
}
void AScientia::SetAttribute(EAttributeKeyword Attribute)
{
	MonsterInfo.MonsterAttribute = Attribute;
	ScInfo.CurrentAttribute = Attribute;

	if (Attribute == EAttributeKeyword::e_None)
	{
		MonsterAttributeDebuff.BurnDamage *= 2;
	}
}
FScientiaInfo AScientia::GetScInfo()
{
	return ScInfo;
}
#pragma endregion
#pragma region Attack1
void AScientia::Attack1()
{
	if (ScInfo.FeatherCount == 0)
	{
		ScAnimInstance->PlayFeatherLMontage();
	}
	else if (ScInfo.FeatherCount == 1)
	{
		ScAnimInstance->PlayFeatherRMontage();
	}
	else if (ScInfo.FeatherCount == 2)
	{
		ScAnimInstance->PlayFeatherMMontage();
	}

	MonsterAIController->StopMovement();
}
void AScientia::Feather()
{
	FVector BaseDir;
	FVector RightDir;
	FVector LeftDir;

	float Angle = 0;

	if (ScInfo.FeatherCount == 0)
	{
		Angle = 20;
	}
	else if (ScInfo.FeatherCount == 1)
	{
		Angle = -20;

	}
	else if (ScInfo.FeatherCount == 2)
	{
		Angle = 0;
	}

	auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
	auto PlayerLocation = GameInstance->GetPlayer()->GetActorLocation();
	BaseDir = AngleToDir(GetActorRotation().Euler().Z + Angle);
	RightDir = AngleToDir(GetActorRotation().Euler().Z + Angle + 30);
	LeftDir = AngleToDir(GetActorRotation().Euler().Z + Angle - 30);

	auto BaseFeather = GetWorld()->SpawnActor<AFeather>(FeatherBP, GetActorLocation() + FVector(0, 0, 150), GetActorRotation());
	BaseFeather->SetMoveDir((PlayerLocation - BaseFeather->GetActorLocation()).GetSafeNormal() + BaseDir);
	BaseFeather->SetDamage(MonsterInfo.Atk * ScInfo.Attack1Value);

	for (int i = 15; i <= 30; i += 10)
	{
		RightDir = AngleToDir(GetActorRotation().Euler().Z + Angle + i);
		LeftDir = AngleToDir(GetActorRotation().Euler().Z + Angle - i);

		auto RightFeather = GetWorld()->SpawnActor<AFeather>(FeatherBP, GetActorLocation() + FVector(0, 0, 150), GetActorRotation());
		RightFeather->SetMoveDir((PlayerLocation - RightFeather->GetActorLocation()).GetSafeNormal() + RightDir);
		RightFeather->SetDamage(MonsterInfo.Atk * ScInfo.Attack1Value);
		RightFeather->RotatorRight(i / 2);

		auto LeftFeather = GetWorld()->SpawnActor<AFeather>(FeatherBP, GetActorLocation() + FVector(0, 0, 150), GetActorRotation());
		LeftFeather->SetMoveDir((PlayerLocation - LeftFeather->GetActorLocation()).GetSafeNormal() + LeftDir);
		LeftFeather->SetDamage(MonsterInfo.Atk * ScInfo.Attack1Value);
		LeftFeather->RotatorLeft(i / 2);
	}
	/*
	auto RightFeather = GetWorld()->SpawnActor<AFeather>(FeatherBP, GetActorLocation() + FVector(0, 0, 150), GetActorRotation());
	RightFeather->SetMoveDir((PlayerLocation - RightFeather->GetActorLocation()).GetSafeNormal() + RightDir);
	RightFeather->SetDamage(MonsterInfo.Atk * ScInfo.Attack1Value);
	RightFeather->RotatorRight();
	auto LeftFeather = GetWorld()->SpawnActor<AFeather>(FeatherBP, GetActorLocation() + FVector(0, 0, 150), GetActorRotation());
	LeftFeather->SetMoveDir((PlayerLocation - LeftFeather->GetActorLocation()).GetSafeNormal() + LeftDir);
	LeftFeather->SetDamage(MonsterInfo.Atk * ScInfo.Attack1Value);
	LeftFeather->RotatorLeft();
	*/
}
void AScientia::AddFeatherCount()
{
	AddFeatherEnd.Broadcast();
	ScInfo.FeatherCount++;
}
void AScientia::ResetFeatherCount()
{
	ScInfo.FeatherCount = 0;
}
#pragma endregion
#pragma region Attack2
void AScientia::Attack2()
{
	ScAnimInstance->PlayClawMontage();
}
void AScientia::ResetClawSuccessedCount()
{
	ScInfo.ClawSuccessedCount = 0;
}
#pragma endregion
#pragma region Attack3
void AScientia::Attack3()
{
	ScAnimInstance->PlayRushMontage();
	GetCharacterMovement()->MaxWalkSpeed = ScInfo.Attack3Speed;
}
#pragma endregion
void AScientia::Attack4()
{
	ScAnimInstance->PlayDropMontage();
	MonsterAIController->StopMovement();
	bIsDrop = true;
}
void AScientia::PlayAttackedBAnimation()
{
	ScAnimInstance->PlayAttackedBAnimation();
}
void AScientia::PlayAttackedFAnimation()
{
	ScAnimInstance->PlayAttackedFAnimation();
}
void AScientia::BattleIdle()
{
	ScAnimInstance->PlayBattleIdleMontage();
	MonsterAIController->StopMovement();
}
void AScientia::BattleWalk()
{
	ScAnimInstance->PlayBattleWalkMontage();
}
void AScientia::Change()
{
	ScAnimInstance->PlayChangeMontage();
	ChangeTimer = 0.0f;
}
void AScientia::Dodge()
{
	ScAnimInstance->PlayDodgeMontage();
}
void AScientia::Crushed()
{
	ScAnimInstance->PlayCrushedMontage();
	ScInfo.BarrierCount--;
}
#pragma region Barrier
void AScientia::ChangeAttribute()
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	auto PlayerAttribute = STGameInstance->GetPlayerAttribute();

	if (ScInfo.BarrierCount == 3)
	{
		switch (PlayerAttribute)
		{
		case EAttributeKeyword::e_Fire:
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Water;
			break;
		case EAttributeKeyword::e_Water:
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Thunder;
			break;
		case EAttributeKeyword::e_Thunder:
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Fire;
			break;
		}
	}
	else if (ScInfo.BarrierCount == 2)
	{
		switch (PlayerAttribute)
		{
		case EAttributeKeyword::e_Fire:
			if (ScInfo.WaterBarrier <= 0)
			{
				MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Fire;
				break;
			}
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Water;
			break;
		case EAttributeKeyword::e_Water:
			if (ScInfo.ThunderBarrier <= 0)
			{
				MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Water;
				break;
			}
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Thunder;
			break;
		case EAttributeKeyword::e_Thunder:
			if (ScInfo.FireBarrier <= 0)
			{
				MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Thunder;
				break;
			}
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Fire;
			break;
		}
	}
	else if (ScInfo.BarrierCount == 1)
	{
		if (!ScInfo.bIsFireBarrierCrushed)
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Fire;
		else if (!ScInfo.bIsWaterBarrierCrushed)
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Water;
		else if (!ScInfo.bIsThunderBarrierCrushed)
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Thunder;
	}
	if (PlayerAttribute == EAttributeKeyword::e_None)
	{
		int Random = FMath::RandRange(0, 2);

		switch (Random)
		{
		case 0:
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Fire;
			break; 
		case 1:
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Water;
			break;
		case 2:
			MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Thunder;
			break;
		}
	}
	

	ScInfo.CurrentAttribute = MonsterInfo.MonsterAttribute;

	ChangeAttributeDelegate();
	// ChangeModel
}
void AScientia::CalcCurrentBarrier(float Value)
{
	switch (MonsterInfo.MonsterAttribute)
	{
	case EAttributeKeyword::e_Fire:
		ScInfo.FireBarrier -= Value;
		OnFireBarrierChanged.Broadcast();
		break;
	case EAttributeKeyword::e_Water:
		ScInfo.WaterBarrier -= Value;
		OnWaterBarrierChanged.Broadcast();
		break;
	case EAttributeKeyword::e_Thunder:
		ScInfo.ThunderBarrier -= Value;
		OnThunderBarrierChanged.Broadcast();
		break;
	}
}
bool AScientia::IsBarrierCrushed()
{
	switch (MonsterInfo.MonsterAttribute)
	{
	case EAttributeKeyword::e_Fire:
		if (ScInfo.FireBarrier <= 0 && !ScInfo.bIsFireBarrierCrushed)
		{
			ScInfo.bIsFireBarrierCrushed = true;
			OnCrushBarrier.Broadcast();
			return true;
		}
		break;
	case EAttributeKeyword::e_Water:
		if (ScInfo.WaterBarrier <= 0 && !ScInfo.bIsWaterBarrierCrushed)
		{
			ScInfo.bIsWaterBarrierCrushed = true;
			OnCrushBarrier.Broadcast();
			return true;
		}
		break;
	case EAttributeKeyword::e_Thunder:
		if (ScInfo.ThunderBarrier <= 0 && !ScInfo.bIsThunderBarrierCrushed)
		{
			ScInfo.bIsThunderBarrierCrushed = true;
			OnCrushBarrier.Broadcast();
			return true;
		}
		break;
	}
	return false;
}
#pragma endregion 
void AScientia::RushEnd()
{
	bIsRush = false;
	bIsPlayerRushHit = false;
	GetCapsuleComponent()->SetCollisionProfileName("Enemy");
}
void AScientia::Turn()
{
	ScAnimInstance->PlayTurnMontage();
	GetCapsuleComponent()->SetCollisionProfileName("Enemy");
	bIsRush = false;
}
void AScientia::PlayStuckAnim()
{
	ScAnimInstance->PlayStuckMontage();
}
void AScientia::PlayFeatherPreAnim()
{
	ScAnimInstance->PlayFeatherPreMontage();
}
void AScientia::PlayClawPreAnim()
{
	ScAnimInstance->PlayClawPreMontage();
}
bool AScientia::ScAttributeIsPlayerAttributeCounter()
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	auto PlayerAttribute = STGameInstance->GetPlayerAttribute();

	switch (MonsterInfo.MonsterAttribute)
	{
	case EAttributeKeyword::e_Fire:
		if (PlayerAttribute != EAttributeKeyword::e_Water)
			return false;
		break;
	case EAttributeKeyword::e_Water:
		if (PlayerAttribute != EAttributeKeyword::e_Thunder)
			return false;
		break;
	case EAttributeKeyword::e_Thunder:
		if (PlayerAttribute != EAttributeKeyword::e_Fire)
			return false;
		break;
	}

	return true;
}
bool AScientia::PlayerAttributeIsScAttributeCounter()
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	auto PlayerAttribute = STGameInstance->GetPlayerAttribute();

	switch (MonsterInfo.MonsterAttribute)
	{
	case EAttributeKeyword::e_Fire:
		if (PlayerAttribute == EAttributeKeyword::e_Water)
			return true;
		break;
	case EAttributeKeyword::e_Water:
		if (PlayerAttribute == EAttributeKeyword::e_Thunder)
			return true;
		break;
	case EAttributeKeyword::e_Thunder:
		if (PlayerAttribute == EAttributeKeyword::e_Fire)
			return true;
	}
	return false;
}
void AScientia::SetMaxBarrierValue()
{
	MaxFireDef = ScInfo.FireBarrier;
	MaxWaterDef = ScInfo.WaterBarrier;
	MaxThunderDef = ScInfo.ThunderBarrier;
}
void AScientia::SpawnPiece()
{
	int Random = FMath::RandRange(0, 3);

	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	auto Player = Cast<AIreneCharacter>(STGameInstance->GetPlayer());

	FVector DropLocation = Player->GetActorLocation();
	auto ChassPiece = GetWorld()->SpawnActor<APiece>(PieceBP, DropLocation + FVector(0, 0, 1060), FRotator::ZeroRotator);
	switch (Random)
	{
	case 0:
		ChassPiece->SetAttribute(EAttributeKeyword::e_Fire);
		break;
	case 1:
		ChassPiece->SetAttribute(EAttributeKeyword::e_Water);
		break;
	case 2:
		ChassPiece->SetAttribute(EAttributeKeyword::e_Thunder);
		break;
	}
	ChassPiece->SetEffect();
	ChassPiece->SetDamage(MonsterInfo.Atk * ScInfo.Attack2Value);
}
void AScientia::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bIsClaw)
	{
		if (!bIsPlayerClawHit)
		{
			if (Cast<AIreneCharacter>(OtherActor))
			{
				auto Player = Cast<AIreneCharacter>(OtherActor);

				ScInfo.ClawSuccessedCount++;

				if (bIsSpark)
				{
					UGameplayStatics::ApplyDamage(Player, (MonsterInfo.Atk * ScInfo.Attack4Value) * MonsterAttributeDebuff.SparkReduction / 100.0f, NULL, this, NULL);
					CalcHp(MonsterInfo.Atk * MonsterAttributeDebuff.SparkDamage / 100.0f);
				}
				else
				{
					UGameplayStatics::ApplyDamage(Player, (MonsterInfo.Atk * ScInfo.Attack4Value), NULL, this, NULL);
				}
				bIsPlayerClawHit = true;
			}
		}
	}
	if (bIsRush)
	{
		if (!bIsPlayerRushHit)
		{
			if (Cast<AIreneCharacter>(OtherActor))
			{
				auto Player = Cast<AIreneCharacter>(OtherActor);

				GetMovementComponent()->Velocity = FVector(7000, 7000, 0);
				GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);

				if (bIsSpark)
				{
					UGameplayStatics::ApplyDamage(Player, (MonsterInfo.Atk * ScInfo.Attack3Value) * MonsterAttributeDebuff.SparkReduction / 100.0f, NULL, this, NULL);
					CalcHp(MonsterInfo.Atk * MonsterAttributeDebuff.SparkDamage / 100.0f);
				}
				else
				{
					UGameplayStatics::ApplyDamage(Player, (MonsterInfo.Atk * ScInfo.Attack3Value), NULL, this, NULL);
				}
				bIsPlayerRushHit = true;
			}
		}
	}
}
void AScientia::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsSetAttribute)
	{
		AttributeSettingTimer += DeltaTime;

		if (AttributeSettingTimer >= ScInfo.AttributeSettingTime)
		{
			auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());

			switch (STGameInstance->GetPlayerAttribute())
			{
			case EAttributeKeyword::e_Fire:
				MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Water;
				break;
			case EAttributeKeyword::e_Water:
				MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Thunder;
				break;
			case EAttributeKeyword::e_Thunder:
				MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Fire;
				break;
			}
			ScInfo.CurrentAttribute = MonsterInfo.MonsterAttribute;
			MonsterAIController->SetPlayer();

			IsSetAttribute = true;
		}
	}
	if (!bIsCanChange)
	{
		ChangeTimer += DeltaTime;
		if (ChangeTimer >= ScInfo.ChangeCoolTime)
		{
			bIsCanChange = true;
		}
	}
	if (bIsDrop)
	{
		ScInfo.DropTimer += DeltaTime;

		if (ScInfo.DropTimer >= ScInfo.DropTime)
		{
			if (ScInfo.DropCount == 10)
				ScInfo.DropTimer = 0.0f;

			SpawnPiece();
			
			ScInfo.DropTimer = 0.0f;
			ScInfo.DropCount++;

			if (ScInfo.DropCount == 10)
			{
				ScInfo.DropTimer = 0.0f;
				ScInfo.DropCount = 0;
				bIsDrop = false;
			}
		}
	}
}
// Called when the game starts or when spawned
void AScientia::BeginPlay()
{
	Super::BeginPlay();

	MonsterAnimInstance = ScAnimInstance;

	ScAnimInstance->Attack1End.AddLambda([this]() -> void {
		Attack1End.Broadcast();
		});
	ScAnimInstance->ClawPreStart.AddLambda([this]() -> void {
		ClawPreStart.Broadcast();
		});
	ScAnimInstance->ClawPreEnd.AddLambda([this]() -> void {
		ClawPreEnd.Broadcast();
		});
	ScAnimInstance->ClawFEnd.AddLambda([this]() -> void {
		ClawFEnd.Broadcast();
		bIsClaw = false;
		bIsPlayerClawHit = false;
		});
	ScAnimInstance->ClawBEnd.AddLambda([this]() -> void {
		ClawBEnd.Broadcast();
		});
	ScAnimInstance->DropEnd.AddLambda([this]() -> void {
		DropEnd.Broadcast();
		});
	ScAnimInstance->ClawStart.AddLambda([this]() -> void {
		ClawStart.Broadcast();
		bIsClaw = true;
		});
	ScAnimInstance->RushStart.AddLambda([this]() -> void {
		bIsRush = true;
		GetMovementComponent()->Velocity = FVector(5000, 5000, 0);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
		RushStart.Broadcast();
		});
	ScAnimInstance->TurnEnd.AddLambda([this]() -> void {
		TurnEnd.Broadcast();
		Attack3();
		bIsRush = true;
		bIsPlayerRushHit = false;
		});
	ScAnimInstance->ChangeEnd.AddLambda([this]() -> void {
		ChangeEnd.Broadcast();
		bIsCanChange = false;
		});
	ScAnimInstance->DodgeEnd.AddLambda([this]() -> void {
		DodgeEnd.Broadcast();
		});
	ScAnimInstance->CrushedEnd.AddLambda([this]() -> void {
		//Change Texture
		CrushedEnd.Broadcast();
		});
	ScAnimInstance->Death.AddLambda([this]() -> void {
		if (bIsDead)
		{
			bDeadWait = true;
			SetActorEnableCollision(false);
			ScAnimInstance->Montage_Stop(500.f, ScAnimInstance->GetCurrentActiveMontage());
		}
		});
	ScAnimInstance->Change.AddUObject(this, &AScientia::ChangeAttribute);
	ScAnimInstance->Feather.AddUObject(this, &AScientia::Feather);
	ScAnimInstance->AddFeather.AddUObject(this, &AScientia::AddFeatherCount);

	
	auto Irene = Cast<AIreneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Irene != nullptr) {
		Irene->IreneUIManager->PlayerHud->Scientiabind(this);
	}
	
}

void AScientia::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.BattleWalkMoveSpeed;

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AScientia::OnHit);
}

void AScientia::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ScAnimInstance = Cast<UScAnimInstance>(GetMesh()->GetAnimInstance());
}
