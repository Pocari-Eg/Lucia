// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterAIController.h"
//UI
#include "../STGameInstance.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>
#include "../UI/HPBarWidget.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetectMonsterRange = 5.0f;

	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HpBarWidget->SetupAttachment(GetMesh());

	HpBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	HpBarWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	HpBarWidget->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBARWIDGET(TEXT("/Game/Developers/Pocari/Collections/Widget/BP_HPBar.BP_HPBar_C"));

	if (UI_HPBARWIDGET.Succeeded()) {

		HpBarWidget->SetWidgetClass(UI_HPBARWIDGET.Class);
		HpBarWidget->SetDrawSize(FVector2D(150, 50.0f));
		HpBarWidget->bAutoActivate = false;
	}
}
#pragma region Init
void AMonster::InitDebuffInfo()
{
	MonsterAttributeDebuff.FireDebuffStack = 0;
	MonsterAttributeDebuff.WaterDebuffStack = 0;
	MonsterAttributeDebuff.ThunderDebuffStack = 0;

	
	MonsterAttributeDebuff.BurnCycle = 0.2f;
	MonsterAttributeDebuff.BurnDamage = 1.0f;
	MonsterAttributeDebuff.BurnTime = 10.0f;
	MonsterAttributeDebuff.BurnCycleTimer = 0.0f;
	MonsterAttributeDebuff.BurnTimer = 0.0f;
	
	MonsterAttributeDebuff.FloodingTime = 10.0f;
	MonsterAttributeDebuff.FloodingTimer = 0.0f;
	MonsterAttributeDebuff.FloodingDebuffSpeedReductionValue = 0.5f;

	MonsterAttributeDebuff.TransitionRange = 10.0f;

	MonsterAttributeDebuff.AssembleRange = 10.0f;
	MonsterAttributeDebuff.AssembleTime = 0.3f;
	MonsterAttributeDebuff.AssembleSpeed = 100.0f;
	MonsterAttributeDebuff.AssembleTimer = 0.0f;

	MonsterAttributeDebuff.ChainRange = 10.0f;
	MonsterAttributeDebuff.ChainTime = 10.0f;
	MonsterAttributeDebuff.ChainTimer = 0.0f;

	bIsBurn = false;
	bIsFlooding = false;
	bIsShock = false;
	bIsAssemble = false;
	bIsChain = false;
}
#pragma endregion

float AMonster::GetMeleeAttackRange() const
{
	return MonsterInfo.MeleeAttackRange;
}
float AMonster::GetTraceRange() const
{
	return MonsterInfo.TraceRange;
}
TArray<EAttributeKeyword> AMonster::GetMainAttributeDef() const
{
	return MonsterInfo.MainAttributeDef;
}
UMonsterAnimInstance* AMonster::GetMonsterAnimInstance() const
{
	return MonsterAnimInstance;
}

void AMonster::OnTrueDamage(float Damage)
{
	if (bIsDead)
		return;

	CalcHp(Damage);
}
void AMonster::OnDamage(EAttributeKeyword PlayerMainAttribute, float Damage)
{
	if (bIsDead)
		return;

	CalcDamage(PlayerMainAttribute, Damage);
}
void AMonster::AddDebuffStack(EAttributeKeyword Attribute)
{
	for (auto Elem : MonsterInfo.MainAttributeDef)
	{
		if (Elem == Attribute)
			return;
	}

	switch (Attribute)
	{
	case EAttributeKeyword::e_Fire:
		MonsterAttributeDebuff.FireDebuffStack++;
		break;
	case EAttributeKeyword::e_Water:
		MonsterAttributeDebuff.WaterDebuffStack++;
		break;
	case EAttributeKeyword::e_Thunder:
		MonsterAttributeDebuff.ThunderDebuffStack++;
		break;
	}
}
#pragma region Calc
void AMonster::CalcAttributeDefType()
{
	TMap<EAttributeKeyword, float> AttributeDefMap;

	TArray<float> DefList;

	AttributeDefMap.Add(EAttributeKeyword::e_None, AttributeDef.e_None);
	AttributeDefMap.Add(EAttributeKeyword::e_Fire, AttributeDef.e_Fire);
	AttributeDefMap.Add(EAttributeKeyword::e_Water, AttributeDef.e_Water);
	AttributeDefMap.Add(EAttributeKeyword::e_Thunder, AttributeDef.e_Thunder);

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
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (STGameInstance->GetAttributeEffectMonster() == nullptr)
	{
		STGameInstance->SetAttributeEffectMonster(this);
	}

	if (STGameInstance->GetAttributeEffectMonster() == this)
	{
		if (bIsBurn)
		{
			DebuffTransition(PlayerMainAttribute, Damage);
		}
		if (bIsFlooding)
		{
			Assemble();
		}
		if (bIsShock)
		{
			Chain(PlayerMainAttribute, Damage);
		}
	}

	switch (PlayerMainAttribute)
	{
	case EAttributeKeyword::e_Fire:
		for (auto& Elem : MonsterInfo.MainAttributeDef)
		{
			if (Elem == EAttributeKeyword::e_Fire)
			{
				return;
			}
		}
		MonsterAttributeDebuff.FireDebuffStack++;
		SetDebuff(PlayerMainAttribute, Damage);
		break;
	case EAttributeKeyword::e_Water:
		for (auto& Elem : MonsterInfo.MainAttributeDef)
		{
			if (Elem == EAttributeKeyword::e_Water)
			{
				return;
			}
		}
		MonsterAttributeDebuff.WaterDebuffStack++;
		SetDebuff(PlayerMainAttribute, Damage);
		break;
	case EAttributeKeyword::e_Thunder:
		for (auto& Elem : MonsterInfo.MainAttributeDef)
		{
			if (Elem == EAttributeKeyword::e_Thunder)
			{
				return;
			}
		}
		MonsterAttributeDebuff.ThunderDebuffStack++;
		SetDebuff(PlayerMainAttribute, Damage);
		break;
	}
}
void AMonster::CalcDamage(EAttributeKeyword PlayerMainAttribute, float Damage)
{
	float Coefficient = 1.0f;
	float AttributeArmor = 100.0f;

	float NoneDef = 0.0f;
	float FireDef = 0.0f;
	float WaterDef = 0.0f;
	float ThunderDef = 0.0f;

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


	if (AttributeDef.e_None != 0)
	{
		NoneDef = Damage * (AttributeDef.e_None / 100.0f) * (AttributeArmor / 100.0f);
		
	}
	if (AttributeDef.e_Fire != 0)
	{
		FireDef = Damage * (AttributeDef.e_Fire / 100.0f) * (AttributeArmor / 100.0f);
	}
	if (AttributeDef.e_Water != 0)
	{
		WaterDef = Damage * (AttributeDef.e_Water / 100.0f) * (AttributeArmor / 100.0f);
	}
	if (AttributeDef.e_Thunder != 0)
	{
		ThunderDef = Damage * (AttributeDef.e_Thunder / 100.0f) * (AttributeArmor / 100.0f);
	}

	//그로기 Def 계산식 추가
	MonsterInfo.CurrentDef -= 20.0f;
	//
	CalcHp(Coefficient * (NoneDef - FireDef - WaterDef - ThunderDef));
}
void AMonster::CalcCurrentDebuffAttribute(EAttributeKeyword AttackedAttribute)
{
	TMap<EAttributeKeyword, int> AttributeDebuffMap;

	AttributeDebuffMap.Add(EAttributeKeyword::e_Fire, MonsterAttributeDebuff.FireDebuffStack);
	AttributeDebuffMap.Add(EAttributeKeyword::e_Water, MonsterAttributeDebuff.WaterDebuffStack);
	AttributeDebuffMap.Add(EAttributeKeyword::e_Thunder, MonsterAttributeDebuff.ThunderDebuffStack);

	AttributeDebuffMap.ValueSort([](int A, int B) {
		return A > B;
		});

	for (auto Elem : AttributeDebuffMap)
	{
		STARRYLOG(Log, TEXT("Attribute Sort : %d"), Elem.Value);
	}

	MonsterInfo.CurrentDebuffAttribute = AttributeDebuffMap.begin().Key();

	if (AttributeDebuffMap[EAttributeKeyword::e_Fire] == AttributeDebuffMap[EAttributeKeyword::e_Water])
	{
		if (AttributeDebuffMap.begin().Key() == EAttributeKeyword::e_Thunder && AttributeDebuffMap[EAttributeKeyword::e_Thunder] != AttributeDebuffMap[EAttributeKeyword::e_Fire])
			return;
		MonsterInfo.CurrentDebuffAttribute = AttackedAttribute;
	}
	else if (AttributeDebuffMap[EAttributeKeyword::e_Water] == AttributeDebuffMap[EAttributeKeyword::e_Thunder])
	{
		if (AttributeDebuffMap.begin().Key() == EAttributeKeyword::e_Fire && AttributeDebuffMap[EAttributeKeyword::e_Fire] != AttributeDebuffMap[EAttributeKeyword::e_Water])
			return;
		MonsterInfo.CurrentDebuffAttribute = AttackedAttribute;
	}
	else if (AttributeDebuffMap[EAttributeKeyword::e_Thunder] == AttributeDebuffMap[EAttributeKeyword::e_Fire])
	{
		if (AttributeDebuffMap.begin().Key() == EAttributeKeyword::e_Water && AttributeDebuffMap[EAttributeKeyword::e_Water] != AttributeDebuffMap[EAttributeKeyword::e_Thunder])
			return;
		MonsterInfo.CurrentDebuffAttribute = AttackedAttribute;
	}
}
void AMonster::CalcHp(float Damage)
{
	if (CheckPlayerIsBehindMonster())
	{
		MonsterInfo.CurrentHp -= Damage * 1.5f;
	}
	else
	{
		MonsterInfo.CurrentHp -= Damage;
	}

	if (bTestMode)
		STARRYLOG(Log, TEXT("Monster Hp : %f"), MonsterInfo.CurrentHp);

	auto MonsterAIController = Cast<AMonsterAIController>(GetController());
	if (nullptr == MonsterAIController)
	{
		STARRYLOG(Error, TEXT("Not Found MonsterAIController"));
		return;
	}

	MonsterAIController->StopMovement();

	auto HpBar = Cast<UHPBarWidget>(HpBarWidget->GetWidget());
	if (HpBar != nullptr)
	{
		HpBar->UpdateWidget((MonsterInfo.CurrentHp < KINDA_SMALL_NUMBER) ? 0.0f : MonsterInfo.CurrentHp / MonsterInfo.MaxHp);
	}

	if (MonsterInfo.CurrentHp <= 0.0f)
	{
		GetCapsuleComponent()->SetHiddenInGame(true);
		bIsDead = true;

		MonsterAIController->Death();
		return;
	}
	if (MonsterInfo.CurrentDef <= 0)
	{
		MonsterAIController->Groggy();
		MonsterInfo.CurrentDef = MonsterInfo.Def;
		return;
	}
	MonsterAIController->Attacked();
}
void AMonster::CalcBurnDamage()
{
	MonsterInfo.CurrentHp -= MonsterAttributeDebuff.BurnDamage;

	auto HpBar = Cast<UHPBarWidget>(HpBarWidget->GetWidget());
	if (HpBar != nullptr)
	{
		HpBar->UpdateWidget((MonsterInfo.CurrentHp < KINDA_SMALL_NUMBER) ? 0.0f : MonsterInfo.CurrentHp / MonsterInfo.MaxHp);
	}

	auto MonsterAIController = Cast<AMonsterAIController>(GetController());

	if (MonsterInfo.CurrentHp <= 0.0f)
	{
		GetCapsuleComponent()->SetHiddenInGame(true);

		bIsDead = true;

		MonsterAIController->Death();
		return;
	}

	if (bTestMode)
		STARRYLOG(Log, TEXT("CurrentHp : %f"), MonsterInfo.CurrentHp);
}
#pragma endregion
bool AMonster::CheckPlayerIsBehindMonster()
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	
	FVector TargetDir = STGameInstance->GetPlayer()->GetActorLocation() - GetActorLocation();
	TargetDir = TargetDir.GetSafeNormal();

	//정면으로 향하는 벡터와 플레이어로 향하는 벡터의 내적을 통해 각도를 구할 수 있다. 결과값은 Radian
	float Radian = FVector::DotProduct(GetActorForwardVector(), TargetDir);
	//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
	float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

	if (TargetAngle <= (MonsterInfo.ViewAngle * 0.5f))
	{
		return false;
	}
	else
	{
		RotationToPlayerDirection();
		return true;
	}
}
void AMonster::RotationToPlayerDirection()
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());

	FVector LookVector = STGameInstance->GetPlayer()->GetActorLocation() - GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	SetActorRotation(TargetRot);
}
TArray<FOverlapResult> AMonster::DetectMonster()
{
	TArray<FOverlapResult> OverlapResults;

	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
		OverlapResults,
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel8, // 채널 변경
		FCollisionShape::MakeSphere(MonsterAttributeDebuff.TransitionRange * 100.0f),
		CollisionQueryParam
	);

	return OverlapResults;
}
#pragma region Debuff
void AMonster::Burn()
{
	bIsFlooding = false;
	bIsShock = false;

	MonsterAttributeDebuff.BurnTimer = 0.0f;
	bIsBurn = true;
}
void AMonster::Flooding()
{
	bIsBurn = false;
	bIsShock = false;

	MonsterAttributeDebuff.FloodingTimer = 0.0f;

	MonsterInfo.MoveSpeed = MonsterInfo.MoveSpeed * MonsterAttributeDebuff.FloodingDebuffSpeedReductionValue;
	MonsterInfo.BattleWalkMoveSpeed = MonsterInfo.BattleWalkMoveSpeed * MonsterAttributeDebuff.FloodingDebuffSpeedReductionValue;

	MonsterAnimInstance->SetPlayRate(MonsterAttributeDebuff.FloodingDebuffSpeedReductionValue);
	MonsterAnimInstance->Montage_SetPlayRate(MonsterAnimInstance->GetCurrentActiveMontage(), MonsterAttributeDebuff.FloodingDebuffSpeedReductionValue);

	bIsFlooding = true;
}
void AMonster::Shock()
{
	bIsBurn = false;
	bIsFlooding = false;

	auto MonsterAIController = Cast<AMonsterAIController>(GetController());
	if (nullptr == MonsterAIController)
		STARRYLOG(Log, TEXT("MonsterAIController Not Found"));

	MonsterAIController->Shock();

	bIsShock = true;
}
void AMonster::DebuffTransition(EAttributeKeyword AttackedAttribute, float Damage)
{
	if (bTestMode)
		DrawDebugSphere(GetWorld(), GetActorLocation(), MonsterAttributeDebuff.TransitionRange * 100.0f, 16, FColor::Red, false, 0.2f);

	TArray<FOverlapResult> AnotherMonsterList = DetectMonster();

	if (AnotherMonsterList.Num() != 0)
	{
		for (auto const& AnotherMonster : AnotherMonsterList)
		{
			AMonster* Monster = Cast<AMonster>(AnotherMonster.GetActor());
			if (Monster == nullptr)
				continue;

			Monster->AddDebuffStack(AttackedAttribute);
			Monster->SetDebuff(AttackedAttribute, Damage);
			Monster->OnDamage(AttackedAttribute, Damage);
		}
	}
}
void AMonster::Assemble()
{
	if (bTestMode)
		DrawDebugSphere(GetWorld(), GetActorLocation(), MonsterAttributeDebuff.AssembleRange * 100.0f, 16, FColor::Blue, false, 0.2f);

	TArray<FOverlapResult> AnotherMonsterList = DetectMonster();

	if (AnotherMonsterList.Num() != 0)
	{
		for (auto const& AnotherMonster : AnotherMonsterList)
		{
			AMonster* Monster = Cast<AMonster>(AnotherMonster.GetActor());
			if (Monster == nullptr)
				continue;

			Monster->bIsAssemble = true;
			Monster->AssembleLocation = GetActorLocation();

			auto MonsterAIController = Cast<AMonsterAIController>(Monster->GetController());
			MonsterAIController->SetFind();
		}
	}
}
void AMonster::Chain(EAttributeKeyword PlayerMainAttribute, float Damage)
{
	if (bTestMode)
		DrawDebugSphere(GetWorld(), GetActorLocation(), MonsterAttributeDebuff.ChainRange * 100.0f, 16, FColor::Yellow, false, 0.2f);

	TArray<FOverlapResult> AnotherMonsterList = DetectMonster();
	
	switch (PlayerMainAttribute)
	{
	case EAttributeKeyword::e_Fire:
		STARRYLOG(Log, TEXT("Fire"));
		break;
	case EAttributeKeyword::e_Water:
		STARRYLOG(Log, TEXT("Water"));
		break;
	case EAttributeKeyword::e_Thunder:
		STARRYLOG(Log, TEXT("Thunder"));
		break;
	}
	if (AnotherMonsterList.Num() != 0)
	{
		for (auto const& AnotherMonster : AnotherMonsterList)
		{
			AMonster* Monster = Cast<AMonster>(AnotherMonster.GetActor());
			if (Monster == nullptr)
				continue;

			//몬스터의 속성중
			for (auto Elem : Monster->GetMainAttributeDef())
			{
				//플레이어의 공격속성과 겹치는 속성이 있으면
				if (Elem == PlayerMainAttribute)
				{
					//체인 상태
					Monster->bIsChain = true;
					Monster->OnDamage(PlayerMainAttribute, Damage);
					break;
				}
			}
		}
	}
}
void AMonster::SetDebuff(EAttributeKeyword AttackedAttribute, float Damage)
{
	CalcCurrentDebuffAttribute(AttackedAttribute);

	switch (MonsterInfo.CurrentDebuffAttribute)
	{
	case EAttributeKeyword::e_Fire:
		Burn();
		break;
	case EAttributeKeyword::e_Water:
		Flooding();
		break;
	case EAttributeKeyword::e_Thunder:
		Shock();
		break;
	}
}
#pragma endregion
// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	CalcAttributeDefType();

	MonsterInfo.DefaultMoveSpeed = MonsterInfo.MoveSpeed;
	MonsterInfo.DefaultBattleWalkMoveSpeed = MonsterInfo.BattleWalkMoveSpeed;

	MonsterInfo.CurrentHp = MonsterInfo.MaxHp;
	MonsterInfo.CurrentDef = MonsterInfo.Def;

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

	//박찬영
	//플레이어의 카메라 좌표와 현재 위젯의 좌표를 통해 위젯이 카메라를 바라보도록 
	FRotator CameraRot = UKismetMathLibrary::FindLookAtRotation(HpBarWidget->GetComponentTransform().GetLocation(),
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());

	// Yaw 값만 변환하여 위젯이 카메라를 따라옴
	HpBarWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
	//

	if (!bIsDead)
	{
		auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
		if (this->GetDistanceTo(STGameInstance->GetPlayer()) < 500.0f)
		{
			HpBarWidget->SetHiddenInGame(false);
		}
		else
		{
			HpBarWidget->SetHiddenInGame(true);
		}
	}
	else
	{
		HpBarWidget->SetHiddenInGame(true);
		return;
	}

	if (bIsBurn)
	{
		//화상 틱 시간 계산
		MonsterAttributeDebuff.BurnCycleTimer += DeltaTime;
		//화상 지속시간 계산
		MonsterAttributeDebuff.BurnTimer += DeltaTime;
		//화상 틱 시간이 설정된 시간이 됐을 때
		if (MonsterAttributeDebuff.BurnCycleTimer >= MonsterAttributeDebuff.BurnCycle)
		{
			//틱 시간 초기화
			MonsterAttributeDebuff.BurnCycleTimer = 0.0f;
			//데미지 계산 후 체력감소
			CalcBurnDamage();
		}
		//화상 지속시간이 설정된 시간이 됐을 때
		if (MonsterAttributeDebuff.BurnTimer >= MonsterAttributeDebuff.BurnTime)
		{
			//시간 초기화 및 화상 상태 해제
			MonsterAttributeDebuff.BurnTimer = 0.0f;
			bIsBurn = false;
		}
	}
	if (bIsFlooding)
	{
		//침수 지속시간 계산
		MonsterAttributeDebuff.FloodingTimer += DeltaTime;
		//침수 지속시간이 설정된 시간이 됐을 때
		if (MonsterAttributeDebuff.FloodingTimer >= MonsterAttributeDebuff.FloodingTime)
		{
			//시간 초기화
			MonsterAttributeDebuff.FloodingTimer = 0.0f;

			//이동속도를 원래대로
			MonsterInfo.MoveSpeed = MonsterInfo.DefaultMoveSpeed;
			MonsterInfo.BattleWalkMoveSpeed = MonsterInfo.DefaultBattleWalkMoveSpeed;

			//애니메이션 속도를 원래대로
			MonsterAnimInstance->SetPlayRate(1.0f);
			MonsterAnimInstance->Montage_SetPlayRate(MonsterAnimInstance->GetCurrentActiveMontage(), 1.0f);

			//침수 상태 해제
			bIsFlooding = false;
		}
	}
	if (bIsAssemble)
	{
		//중심 몬스터로 향하는 벡터
		FVector MoveDirection = AssembleLocation - GetActorLocation();
		//끌려가는 힘 계산
		FVector newLocation = GetTransform().GetLocation() + (MoveDirection * (MonsterAttributeDebuff.AssembleSpeed / 100.0f) * DeltaTime);

		RootComponent->SetWorldLocation(newLocation);

		//어셈블 지속시간 계산
		MonsterAttributeDebuff.AssembleTimer += DeltaTime;
		//시간이 됐다면
		if (MonsterAttributeDebuff.AssembleTimer >= MonsterAttributeDebuff.AssembleTime)
		{
			//시간 초기화 및 어셈블 상태 해제
			MonsterAttributeDebuff.AssembleTimer = 0.0f;
			bIsAssemble = false;
		}
	}
	if (bIsChain)
	{
		//체인 지속시간 계산
		MonsterAttributeDebuff.ChainTimer += DeltaTime;
		//시간이 됐다면
		if (MonsterAttributeDebuff.ChainTimer >= MonsterAttributeDebuff.ChainTime)
		{
			//시간 초기화 및 체인 상태 해제
			MonsterAttributeDebuff.ChainTimer = 0.0f;
			bIsChain = false;
		}
	}
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}
float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (bIsAttacking)
		bIsAttacking = false;

	if (bIsDead)
		return FinalDamage;

	/* 이름확인 옛날코드 혹시몰라서 남겨두니 지우지 말것
	if (bTestMode)
		STARRYLOG(Warning, TEXT("Morbit Attacked : %s"), *OtherActor->GetName());

	FString FindName = "CollisionCylinder";
	FString ElemName;

	bool IsFind = false;
	for (auto& Elem : OtherActor->GetComponents())
	{
		ElemName = Elem->GetName();
		if (ElemName == FindName)
		{
			IsFind = true;
			break;
		}
	}
	*/
	auto Player = Cast<AIreneCharacter>(DamageCauser);
	
	if (Player != nullptr)
	{
		CalcAttributeDebuff(Player->GetAttribute(), DamageAmount);
		CalcDamage(Player->GetAttribute(), DamageAmount);
		bIsAttacked = true;
		return FinalDamage;
	}

	return FinalDamage;
}
