// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterAIController.h"


// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetectMonsterRange = 5.0f;
}
#pragma region Init
void AMonster::InitDebuffInfo()
{
	BurnStack = 0;
	BurnCycle = 0.2f;
	BurnDamage = 1.0f;
	BurnTime = 10.0f;
	BurnCycleTimer = 0.0f;
	BurnTimer = 0.0f;
	
	FloodingStack = 0;
	FloodingTime = 10.0f;
	FloodingTimer = 0.0f;
	DefaultMoveSpeed = MonsterInfo.MoveSpeed;
	DefaultBattleWalkMoveSpeed = MonsterInfo.BattleWalkMoveSpeed;
	DefaultAnimeSpeed = 1.0f;

	ExplosionRange = 10.0f;
	ExplosionDamage = 50.0f;

	AssembleRange = 10.0f;
	AssembleTime = 0.3f;
	AssembleSpeed = 100.0f;
	AssembleTimer = 0.0f;

	ChainRange = 10.0f;
	ChainTime = 10.0f;
	ChainTimer = 0.0f;

	bIsBurn = false;
	bIsFlooding = false;
	bIsShock = false;
	bIsAssemble = false;
	bIsChain = false;
}
#pragma endregion

float AMonster::GetMeleeAttackRange()
{
	return MonsterInfo.MeleeAttackRange;
}
float AMonster::GetTraceRange()
{
	return MonsterInfo.TraceRange;
}
void AMonster::OnTrueDamage(float Damage)
{
	CalcHp(Damage);
}
void AMonster::OnDamage(EAttributeKeyword PlayerMainAttribute, float Damage)
{
	CalcDamage(PlayerMainAttribute, Damage);

	auto MonsterAIController = Cast<AMonsterAIController>(GetController());
	if (nullptr == MonsterAIController)
		STARRYLOG(Log, TEXT("Not Found MonsterAIController"));
	if (MonsterInfo.Def <= 0)
	{
		MonsterAIController->Groggy();
		return;
	}
	MonsterAIController->Attacked();
}

#pragma region Calc
void AMonster::CalcAttributeDefType()
{
	TMap<EAttributeKeyword, float> AttributeDefMap;

	TArray<float> DefList;

	AttributeDefMap.Add(EAttributeKeyword::e_None, AttributeDef.Normal);
	AttributeDefMap.Add(EAttributeKeyword::e_Fire, AttributeDef.Pyro);
	AttributeDefMap.Add(EAttributeKeyword::e_Water, AttributeDef.Hydro);
	AttributeDefMap.Add(EAttributeKeyword::e_Thunder, AttributeDef.Electro);

	AttributeDefMap.ValueSort([](float A, float B) {
		return A > B;
		});
	for (auto& Elem : AttributeDefMap)
	{
		//log
		if (bTestMode)
		{
			STARRYLOG(Warning, TEXT("AttributeDef : %f"), Elem.Value);
		}
		DefList.Add(Elem.Value);
	}
	MonsterInfo.MainAttributeDef.Add(AttributeDefMap.begin().Key());

	for (auto Elem : DefList)
	{
		//속성 방어력이 같은지
		if (DefList[0] == Elem)
		{
			//같은 요소가 있다면 등록된 맵을 돌면서 모든 Value값을 체크
			for (auto& Map : AttributeDefMap)
			{
				if (Map.Value == Elem)
				{
					//log
					if (bTestMode)
					{
						switch (Map.Key)
						{
						case EAttributeKeyword::e_None:
							STARRYLOG(Log, TEXT("MainAttributeDef : Normal"));
							break;
						case EAttributeKeyword::e_Fire:
							STARRYLOG(Log, TEXT("MainAttributeDef : Pyro"));
							break;
						case EAttributeKeyword::e_Water:
							STARRYLOG(Log, TEXT("MainAttributeDef : Hydro"));
							break;
						case EAttributeKeyword::e_Thunder:
							STARRYLOG(Log, TEXT("MainAttributeDef : Electro"));
							break;
						}
					}
					if (Map.Key == AttributeDefMap.begin().Key())
						continue;
					MonsterInfo.MainAttributeDef.Add(Map.Key);
				}
			}
			//모든 Value값을 체크했기 때문에 실행종료
			DefList.Empty();
			AttributeDefMap.Empty();
			return;
		}
	}

	DefList.Empty();
	AttributeDefMap.Empty();
}
void AMonster::CalcAttributeDebuff(EAttributeKeyword PlayerMainAttribute, float Damage)
{
	switch (PlayerMainAttribute)
	{
	case EAttributeKeyword::e_Fire:
		for (auto& Elem : MonsterInfo.MainAttributeDef)
		{
			if (Elem == EAttributeKeyword::e_Water)
				return;
		}
		if (bTestMode)
		{
			STARRYLOG(Log, TEXT("Player MainAttribute : Pyro"));
			STARRYLOG(Log, TEXT("Hydro is not in Monster MainAttribute"));
			STARRYLOG(Log, TEXT("Explosion effect is triggered"));
		}
		Explosion();
		break;
	case EAttributeKeyword::e_Water:
		for (auto& Elem : MonsterInfo.MainAttributeDef)
		{
			if (Elem == EAttributeKeyword::e_Thunder)
				return;
		}
		if (bTestMode)
		{
			STARRYLOG(Log, TEXT("Player MainAttribute : Water"));
			STARRYLOG(Log, TEXT("Electro is not in Monster MainAttribute"));
			STARRYLOG(Log, TEXT("Assemble effect is triggered"));
		}
		Assemble(PlayerMainAttribute, Damage);
		break;
	case EAttributeKeyword::e_Thunder:
		for (auto& Elem : MonsterInfo.MainAttributeDef)
		{
			if (Elem == EAttributeKeyword::e_Fire)
				return;
		}
		if (bTestMode)
		{
			STARRYLOG(Log, TEXT("Player MainAttribute : Electro"));
			STARRYLOG(Log, TEXT("Pyro is not in Monster MainAttribute"));
			STARRYLOG(Log, TEXT("Chain effect is triggered"));
		}
		Chain(PlayerMainAttribute, Damage);
	}
	/*
	switch (PlayerSubAttribute)
	{
	case EAttributeKeyword::e_Fire:
		if (MonsterInfo.MainAttributeDef.Num() > 1)
			return;
		if (MonsterInfo.MainAttributeDef[0] == EAttributeKeyword::e_Thunder)
			Burn();
		break;
	case EAttributeKeyword::e_Water:
		if (MonsterInfo.MainAttributeDef.Num() > 1)
			return;
		if (MonsterInfo.MainAttributeDef[0] == EAttributeKeyword::e_Fire)
			Flooding();
		break;
	case EAttributeKeyword::e_Thunder:
		if (MonsterInfo.MainAttributeDef.Num() > 1)
			return;
		if (MonsterInfo.MainAttributeDef[0] == EAttributeKeyword::e_Water)
			Shock();
	}
	*/
}
void AMonster::CalcDamage(EAttributeKeyword PlayerMainAttribute, float Damage)
{
	float Coefficient = 1.0f;
	float AttributeArmor = 100.0f;

	float NormalDef = 0.0f;
	float PyroDef = 0.0f;
	float HydroDef = 0.0f;
	float ElectroDef = 0.0f;

	switch (PlayerMainAttribute)
	{
	case EAttributeKeyword::e_Fire:
		if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Water)
		{
			AttributeArmor = 50.0f;
		}
		else if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Thunder)
		{
			AttributeArmor = 200.0f;
		}
		break;
	case EAttributeKeyword::e_Water:
		if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Fire)
		{
			AttributeArmor = 50.0f;
		}
		else if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Thunder)
		{
			AttributeArmor = 200.0f;
		}
		break;
	case EAttributeKeyword::e_Thunder:
		if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Fire)
		{
			AttributeArmor = 200.0f;
		}
		else if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Water)
		{
			AttributeArmor = 50.0f;
		}
	}


	if (AttributeDef.Normal != 0)
	{
		NormalDef = Damage * (AttributeDef.Normal / 100.0f) * (AttributeArmor / 100.0f);
		
	}
	if (AttributeDef.Pyro != 0)
	{
		PyroDef = Damage * (AttributeDef.Pyro / 100.0f) * (AttributeArmor / 100.0f);
	}
	if (AttributeDef.Hydro != 0)
	{
		HydroDef = Damage * (AttributeDef.Hydro / 100.0f) * (AttributeArmor / 100.0f);
	}
	if (AttributeDef.Electro != 0)
	{
		ElectroDef = Damage * (AttributeDef.Electro / 100.0f) * (AttributeArmor / 100.0f);
	}

	//그로기 Def 계산식 추가
	//
	CalcHp(Coefficient * (NormalDef - PyroDef - HydroDef - ElectroDef));
}
#pragma endregion
TArray<FOverlapResult> AMonster::DetectMonster()
{
	TArray<FOverlapResult> OverlapResults;

	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
		OverlapResults,
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel8, // 채널 변경
		FCollisionShape::MakeSphere(ExplosionRange * 100.0f),
		CollisionQueryParam
	);

	return OverlapResults;
}
void AMonster::CalcHp(float Damage)
{
	MonsterInfo.Hp -= Damage;

	STARRYLOG(Log, TEXT("Monster Hp : %f"), MonsterInfo.Hp);
	if (MonsterInfo.Hp <= 0.0f)
	{
		Destroy();
	}
}
#pragma region Debuff
void AMonster::Burn()
{
	BurnStack++;
	BurnTimer = 0.0f;
	bIsBurn = true;
}
void AMonster::Flooding()
{
	FloodingStack++;
	FloodingTimer = 0.0f;

	MonsterInfo.MoveSpeed = (DefaultMoveSpeed * (1.0f - ((float)FloodingStack / 10.0f)));
	MonsterInfo.BattleWalkMoveSpeed = (DefaultBattleWalkMoveSpeed * (1.0f - ((float)FloodingStack / 10.0f)));
	// 애니메이션 속도 조절 추가 필요
	bIsFlooding = true;
}
void AMonster::Shock()
{
	auto MonsterAIController = Cast<AMonsterAIController>(GetController());
	if (nullptr == MonsterAIController)
		STARRYLOG(Log, TEXT("MonsterAIController Not Found"));

	MonsterAIController->Shock();

	// 애니메이션 및 이펙트 설정 추가
	bIsShock = true;
}
void AMonster::Explosion()
{
	TArray<FOverlapResult> AnotherMonsterList = DetectMonster();

	if (AnotherMonsterList.Num() != 0)
	{
		for (auto const& AnotherMonster : AnotherMonsterList)
		{
			AMonster* Monster = Cast<AMonster>(AnotherMonster.GetActor());
			if (Monster == nullptr)
				continue;

			Monster->OnTrueDamage(ExplosionDamage);
		}
	}
}
void AMonster::Assemble(EAttributeKeyword PlayerMainAttribute, float Damage)
{
	TArray<FOverlapResult> AnotherMonsterList = DetectMonster();

	if (AnotherMonsterList.Num() != 0)
	{
		for (auto const& AnotherMonster : AnotherMonsterList)
		{
			AMonster* Monster = Cast<AMonster>(AnotherMonster.GetActor());
			if (Monster == nullptr)
				continue;

			Monster->OnDamage(PlayerMainAttribute, Damage);
			Monster->bIsAssemble = true;
			Monster->AssembleLocation = GetActorLocation();
		}
	}
}
void AMonster::Chain(EAttributeKeyword PlayerMainAttribute, float Damage)
{
	TArray<FOverlapResult> AnotherMonsterList = DetectMonster();

	if (AnotherMonsterList.Num() != 0)
	{
		for (auto const& AnotherMonster : AnotherMonsterList)
		{
			AMonster* Monster = Cast<AMonster>(AnotherMonster.GetActor());
			if (Monster == nullptr)
				continue;

			for (auto const& MonsterMainAttributeDef : Monster->MonsterInfo.MainAttributeDef)
			{
				if (MonsterMainAttributeDef == EAttributeKeyword::e_Fire)
					return;
			}
			Monster->OnDamage(PlayerMainAttribute, Damage);
			Monster->bIsChain = true;
		}
	}
}
void AMonster::OnShockMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsShock = false;

	ShockEnd.Broadcast();
}
#pragma endregion
// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}
void AMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}
void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsBurn)
	{
		BurnCycleTimer += DeltaTime;
		BurnTimer += DeltaTime;
		if (BurnCycleTimer >= BurnCycle)
		{
			BurnStack = 0;
			BurnCycleTimer = 0.0f;
			CalcHp(BurnDamage);
		}
		if (BurnTimer >= BurnTime)
		{
			BurnTimer = 0.0f;
			bIsBurn = false;
		}
	}
	if (bIsFlooding)
	{
		FloodingTimer += DeltaTime;
		if (FloodingTimer >= FloodingTime)
		{
			FloodingStack = 0;
			FloodingTimer = 0.0f;

			MonsterInfo.MoveSpeed = DefaultMoveSpeed;
			MonsterInfo.BattleWalkMoveSpeed = DefaultBattleWalkMoveSpeed;
			// 애니메이션 속도 초기화 필요 ?? = DefaultAnimeSpeed;

			bIsFlooding = false;
		}
	}
	if (bIsAssemble)
	{
		FVector MoveDirection = AssembleLocation - GetActorLocation();
		
		FVector newLocation = GetTransform().GetLocation() + (MoveDirection * (AssembleSpeed / 100.0f) * DeltaTime);

		RootComponent->SetWorldLocation(newLocation);

		AssembleTimer += DeltaTime;
		if (AssembleTimer >= AssembleTime)
		{
			AssembleTimer = 0.0f;
			bIsAssemble = false;
		}
	}
	if (bIsChain)
	{
		ChainTimer += DeltaTime;
		if (ChainTimer >= ChainTime)
		{
			ChainTimer = 0.0f;
			bIsChain = false;
		}
	}
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}
