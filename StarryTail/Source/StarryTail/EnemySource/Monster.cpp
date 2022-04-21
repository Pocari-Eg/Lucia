// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "./Morbit/Morbit.h"
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

	MonsterInfo.DetectMonsterRange = 5.0f;
	MonsterInfo.ArbitraryConstValueA = 2.5f;
	MonsterInfo.ArbitraryConstValueB = 1.0f;
	MonsterInfo.ArbitraryConstValueC = 1.0f;

	InitAttackedInfo();

	KnockBackTime = 0.15f;
	ShowUITime = 5.0f;

	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HpBarWidget->SetupAttachment(GetMesh());

	HpBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	HpBarWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	HpBarWidget->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBARWIDGET(TEXT("/Game/UI/BluePrint/BP_HPBar.BP_HPBar_C"));
	static ConstructorHelpers::FClassFinder<AChainLightning> ChainBlueprint(TEXT("Blueprint'/Game/BluePrint/Monster/BP_ChainLightning'"));

	if (UI_HPBARWIDGET.Succeeded()) {

		HpBarWidget->SetWidgetClass(UI_HPBARWIDGET.Class);
		HpBarWidget->SetDrawSize(FVector2D(96, 80.0f));
		HpBarWidget->bAutoActivate = false;
	}
	if (ChainBlueprint.Succeeded())
	{
		ChainBP = ChainBlueprint.Class;
	}
}
#pragma region Init
void AMonster::MarkerOnOff()
{
	auto HpBar = Cast<UHPBarWidget>(HpBarWidget->GetWidget());
	if (HpBar != nullptr)
	{
		HpBar->MarkerOnOff();
	}
}
void AMonster::InitDebuffInfo()
{
	MonsterAttributeDebuff.FireDebuffStack = 0;
	MonsterAttributeDebuff.WaterDebuffStack = 0;
	MonsterAttributeDebuff.ThunderDebuffStack = 0;


	MonsterAttributeDebuff.BurnCycle = 0.5f;
	MonsterAttributeDebuff.BurnDamage = 1.0f;
	MonsterAttributeDebuff.BurnTime = 10.0f;
	MonsterAttributeDebuff.BurnCycleTimer = 0.0f;
	MonsterAttributeDebuff.BurnTimer = 0.0f;

	MonsterAttributeDebuff.FloodingTime = 5.0f;
	MonsterAttributeDebuff.FloodingTimer = 0.0f;
	MonsterAttributeDebuff.FloodingDebuffSpeedReductionValue = 0.5f;

	MonsterAttributeDebuff.ShockTime = 2.0f;

	MonsterAttributeDebuff.TransitionRange = 2.0f;

	MonsterAttributeDebuff.AssembleRange = 5.0f;
	MonsterAttributeDebuff.AssembleTime = 0.3f;
	MonsterAttributeDebuff.AssembleSpeed = 500.0f;
	MonsterAttributeDebuff.AssembleTimer = 0.0f;

	MonsterAttributeDebuff.ChainRange = 10.0f;
	MonsterAttributeDebuff.ChainSpeed = 2500.0f;

	bIsBurn = false;
	bIsFlooding = false;
	bIsShock = false;
	bIsAssemble = false;
	bIsChain = false;
}
void AMonster::InitAttackedInfo()
{
	AttackedInfo.bIsUseMana = false;
	AttackedInfo.Mana = 0.0f;
	AttackedInfo.AttributeArmor = 100.0f;
}
void AMonster::InitEffect()
{
	HitEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitEffect"));
	LightningHitEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LightningHitEffect"));
	BurnEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BurnEffect"));
	FloodingEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FloodingEffect"));
	ShockEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShockEffect"));
	TransitionEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TransitionEffect"));
	AssembleEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AssembleEffect"));
	GroggyEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GroggyEffect"));


	HitEffectComponent->SetupAttachment(GetMesh());
	LightningHitEffectComponent->SetupAttachment(GetMesh());
	BurnEffectComponent->SetupAttachment(GetMesh());
	FloodingEffectComponent->SetupAttachment(GetMesh());
	ShockEffectComponent->SetupAttachment(GetMesh());
	TransitionEffectComponent->SetupAttachment(GetMesh());
	AssembleEffectComponent->SetupAttachment(GetMesh());
	GroggyEffectComponent->SetupAttachment(RootComponent);

	HitEffectComponent->bAutoActivate = false;
	LightningHitEffectComponent->bAutoActivate = false;
	BurnEffectComponent->bAutoActivate = false;
	FloodingEffectComponent->bAutoActivate = false;
	ShockEffectComponent->bAutoActivate = false;
	TransitionEffectComponent->bAutoActivate = false;
	AssembleEffectComponent->bAutoActivate = false;
	GroggyEffectComponent->bAutoActivate = false;

	MonsterEffect.HitEffectRotation = FRotator(0.0f, 0.0f, 0.0f);
	MonsterEffect.HitEffectScale = FVector(1.0f, 1.0f, 1.0f);

	MonsterEffect.LightningHitEffectRotation = FRotator(0.0f, 0.0f, 0.0f);
	MonsterEffect.LightningHitEffectScale = FVector(1.0f, 1.0f, 1.0f);

	MonsterEffect.DebuffEffectRotation = FRotator(0.0f, 0.0f, 0.0f);
	MonsterEffect.DebuffEffectScale = FVector(1.0f, 1.0f, 1.0f);

	MonsterEffect.TransitionEffectRotation = FRotator(0.0f, 0.0f, 0.0f);
	MonsterEffect.TransitionEffectScale = FVector(1.0f, 1.0f, 1.0f);

	MonsterEffect.AssembleEffectRotation = FRotator(0.0f, 0.0f, 0.0f);
	MonsterEffect.AssembleEffectScale = FVector(1.0f, 1.0f, 1.0f);

	MonsterEffect.GroggyEffectRotation = FRotator(0.0f, 0.0f, 0.0f);
	MonsterEffect.GroggyEffectScale = FVector(1.0f, 1.0f, 1.0f);
}
#pragma endregion

#pragma region Get
float AMonster::GetMeleeAttackRange() const
{
	return MonsterInfo.MeleeAttackRange;
}
float AMonster::GetTraceRange() const
{
	return MonsterInfo.TraceRange;
}
float AMonster::GetDetectMonsterRange() const
{
	return MonsterInfo.DetectMonsterRange;
}
FVector AMonster::GetLocation() const
{
	return GetActorLocation() + FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}
/*
TArray<EAttributeKeyword> AMonster::GetMainAttributeDef() const
{
	return MonsterInfo.MainAttributeDef;
}
*/
EAttributeKeyword AMonster::GetAttribute() const
{
	return MonsterInfo.MonsterAttribute;
}
float AMonster::GetDistanceToPlayer() const
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	FVector ActorMeshLocation = GetActorLocation() + FVector(0, 0, -150);
	return (ActorMeshLocation - STGameInstance->GetPlayer()->GetActorLocation()).Size();
}
UMonsterAnimInstance* AMonster::GetMonsterAnimInstance() const
{
	return MonsterAnimInstance;
}
#pragma endregion
void AMonster::SetAttackedInfo(bool bIsUseMana, float Mana)
{
	AttackedInfo.bIsUseMana = bIsUseMana;
	AttackedInfo.Mana = Mana;
}
void AMonster::SetEffect()
{
	HitEffectComponent->SetTemplate(MonsterEffect.HitEffect);
	LightningHitEffectComponent->SetTemplate(MonsterEffect.LightningHitEffect);
	BurnEffectComponent->SetTemplate(MonsterEffect.BurnEffect);
	FloodingEffectComponent->SetTemplate(MonsterEffect.FloodingEffect);
	ShockEffectComponent->SetTemplate(MonsterEffect.ShockEffect);
	TransitionEffectComponent->SetTemplate(MonsterEffect.TransitionEffect);
	AssembleEffectComponent->SetTemplate(MonsterEffect.AssembleEffect);
	GroggyEffectComponent->SetTemplate(MonsterEffect.GroggyEffect);

	HitEffectComponent->SetRelativeRotation(MonsterEffect.HitEffectRotation);
	HitEffectComponent->SetRelativeScale3D(MonsterEffect.HitEffectScale);

	LightningHitEffectComponent->SetRelativeRotation(MonsterEffect.LightningHitEffectRotation);
	LightningHitEffectComponent->SetRelativeScale3D(MonsterEffect.LightningHitEffectScale);

	BurnEffectComponent->SetRelativeRotation(MonsterEffect.DebuffEffectRotation);
	BurnEffectComponent->SetRelativeScale3D(MonsterEffect.DebuffEffectScale);

	FloodingEffectComponent->SetRelativeRotation(MonsterEffect.DebuffEffectRotation);
	FloodingEffectComponent->SetRelativeScale3D(MonsterEffect.DebuffEffectScale);

	ShockEffectComponent->SetRelativeRotation(MonsterEffect.DebuffEffectRotation);
	ShockEffectComponent->SetRelativeScale3D(MonsterEffect.DebuffEffectScale);

	TransitionEffectComponent->SetRelativeRotation(MonsterEffect.TransitionEffectRotation);
	TransitionEffectComponent->SetRelativeScale3D(MonsterEffect.TransitionEffectScale);

	AssembleEffectComponent->SetRelativeRotation(MonsterEffect.AssembleEffectRotation);
	AssembleEffectComponent->SetRelativeScale3D(MonsterEffect.AssembleEffectScale);

	GroggyEffectComponent->SetRelativeRotation(MonsterEffect.GroggyEffectRotation);
	GroggyEffectComponent->SetRelativeScale3D(MonsterEffect.GroggyEffectScale);
}
void AMonster::OnTrueDamage(float Damage)
{
	if (bIsDead)
		return;

	CalcHp(Damage);
}
void AMonster::OnDamage(float Damage)
{
	if (bIsDead)
		return;

	CalcHp(CalcManaAttackDamage(Damage));
}
void AMonster::AddDebuffStack(EAttributeKeyword Attribute)
{
	/* 20220414 수정
	for (auto Elem : MonsterInfo.MainAttributeDef)
	{
		if (Elem == Attribute)
			return;
	}
	*/
	/* 20220421 수정
	if (MonsterInfo.MonsterAttribute == Attribute)
	{
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
	*/
}
#pragma region Calc
void AMonster::CalcAttributeDefType()
{
	/*
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
	*/
}
void AMonster::CalcAttributeDebuff(EAttributeKeyword PlayerMainAttribute, float Damage)
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());

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
		/* 20220414 속성방어력삭제
		for (auto& Elem : MonsterInfo.MainAttributeDef)
		{
			if (Elem == EAttributeKeyword::e_Fire)
			{
				return;
			}
		}
		*/
		if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Fire)
		{
			return;
		}
		SetDebuff(PlayerMainAttribute, Damage);
		break;
	case EAttributeKeyword::e_Water:
		/* 20220414 속성방어력삭제
		for (auto& Elem : MonsterInfo.MainAttributeDef)
		{
			if (Elem == EAttributeKeyword::e_Water)
			{
				return;
			}
		}
		*/
		if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Water)
		{
			return;
		}
		SetDebuff(PlayerMainAttribute, Damage);
		break;
	case EAttributeKeyword::e_Thunder:
		/* 20220414 속성방어력삭제
		for (auto& Elem : MonsterInfo.MainAttributeDef)
		{
			if (Elem == EAttributeKeyword::e_Thunder)
			{
				return;
			}
		}
		*/
		if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Thunder)
		{
			return;
		}
		SetDebuff(PlayerMainAttribute, Damage);
		break;
	}
}
void AMonster::CalcDef()
{
	auto Morbit = Cast<AMorbit>(this);
	if (Morbit != nullptr)
	{
		MonsterInfo.CurrentDef -= ((AttackedInfo.Mana * MonsterInfo.ArbitraryConstValueB) / 2.5f);
	}


	if (MonsterInfo.CurrentDef <= 0)
	{
		if (ShockEffectComponent->IsActive())
		{
			ShockEffectComponent->SetActive(false);
			bIsShock = false;
		}
		GroggyEffectComponent->SetActive(true);
		MonsterAIController->Groggy();
		bIsGroggy = true;
	}

	//방어력 게이지 업데이트
	auto HpBar = Cast<UHPBarWidget>(HpBarWidget->GetWidget());
	if (HpBar != nullptr)
	{
		HpBar->UpdateDefWidget((MonsterInfo.CurrentDef < KINDA_SMALL_NUMBER) ? 0.0f : MonsterInfo.CurrentDef / MonsterInfo.Def);
	}
	//
}
float AMonster::CalcNormalAttackDamage(float Damage)
{
	MonsterAIController->Attacked();
	MonsterAIController->StopMovement();
	if ((MonsterInfo.CurrentDef / 10.0f) < 1)
		return MonsterInfo.ArbitraryConstValueA * (Damage) * (AttackedInfo.AttributeArmor / 100.0f);
	return MonsterInfo.ArbitraryConstValueA * (Damage / (MonsterInfo.CurrentDef / 10.0f)) * (AttackedInfo.AttributeArmor / 100.0f);
}
float AMonster::CalcManaAttackDamage(float Damage)
{
	float NoneDef = 0.0f;
	float FireDef = 0.0f;
	float WaterDef = 0.0f;
	float ThunderDef = 0.0f;

	if (AttributeDef.e_None != 0)
	{
		NoneDef = Damage * (AttributeDef.e_None / 100.0f) * (AttackedInfo.AttributeArmor / 100.0f);
	}
	if (AttributeDef.e_Fire != 0)
	{
		FireDef = Damage * (AttributeDef.e_Fire / 100.0f) * (AttackedInfo.AttributeArmor / 100.0f);
	}
	if (AttributeDef.e_Water != 0)
	{
		WaterDef = Damage * (AttributeDef.e_Water / 100.0f) * (AttackedInfo.AttributeArmor / 100.0f);
	}
	if (AttributeDef.e_Thunder != 0)
	{
		ThunderDef = Damage * (AttributeDef.e_Thunder / 100.0f) * (AttackedInfo.AttributeArmor / 100.0f);
	}
	MonsterAIController->Attacked();
	MonsterAIController->StopMovement();

	return MonsterInfo.ArbitraryConstValueA * (NoneDef - FireDef - WaterDef - ThunderDef);
}
float AMonster::CalcBurnDamage(float Damage)
{
	float NoneDef = 0.0f;
	float FireDef = 0.0f;
	float WaterDef = 0.0f;
	float ThunderDef = 0.0f;

	if (AttributeDef.e_None != 0)
	{
		NoneDef = Damage * (AttributeDef.e_None / 100.0f) * (AttackedInfo.AttributeArmor / 100.0f);
	}
	if (AttributeDef.e_Fire != 0)
	{
		FireDef = Damage * (AttributeDef.e_Fire / 100.0f) * (AttackedInfo.AttributeArmor / 100.0f);
	}
	if (AttributeDef.e_Water != 0)
	{
		WaterDef = Damage * (AttributeDef.e_Water / 100.0f) * (AttackedInfo.AttributeArmor / 100.0f);
	}
	if (AttributeDef.e_Thunder != 0)
	{
		ThunderDef = Damage * (AttributeDef.e_Thunder / 100.0f) * (AttackedInfo.AttributeArmor / 100.0f);
	}

	return MonsterInfo.ArbitraryConstValueA * (NoneDef - FireDef - WaterDef - ThunderDef);
}
void AMonster::CalcCurrentDebuffAttribute(EAttributeKeyword AttackedAttribute)
{
	/* 20220421 수정
	TMap<EAttributeKeyword, int> AttributeDebuffMap;

	AttributeDebuffMap.Add(EAttributeKeyword::e_Fire, MonsterAttributeDebuff.FireDebuffStack);
	AttributeDebuffMap.Add(EAttributeKeyword::e_Water, MonsterAttributeDebuff.WaterDebuffStack);
	AttributeDebuffMap.Add(EAttributeKeyword::e_Thunder, MonsterAttributeDebuff.ThunderDebuffStack);

	AttributeDebuffMap.ValueSort([](int A, int B) {
		return A > B;
		});

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
	*/
}
void AMonster::CalcHp(float Damage)
{
	Damage = FMath::Abs(Damage);

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

	bShowUI = true;
	ShowUITimer = 0.0f;
	HpBarWidget->SetHiddenInGame(false);

	auto HpBar = Cast<UHPBarWidget>(HpBarWidget->GetWidget());
	if (HpBar != nullptr)
	{
		HpBar->UpdateHpWidget((MonsterInfo.CurrentHp < KINDA_SMALL_NUMBER) ? 0.0f : MonsterInfo.CurrentHp / MonsterInfo.MaxHp);
	}

	if (MonsterInfo.CurrentHp <= 0.0f)
	{
		MonsterDeadEvent();
		bIsDead = true;
		SetActive();

		MonsterAIController->Death();
		return;
	}
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
void AMonster::ResetDef()
{
	MonsterInfo.CurrentDef = MonsterInfo.Def;
	bIsGroggy = false;
	GroggyEffectComponent->SetActive(false);

	HpBarWidget->ToggleActive();
	auto HpBar = Cast<UHPBarWidget>(HpBarWidget->GetWidget());
	if (HpBar != nullptr)
	{
		HpBar->UpdateDefWidget((MonsterInfo.CurrentDef < KINDA_SMALL_NUMBER) ? 0.0f : MonsterInfo.CurrentDef / MonsterInfo.Def);
	}
}
void AMonster::OffShockDebuffEffect()
{
	ShockEffectComponent->SetActive(false);
}
TArray<FOverlapResult> AMonster::DetectMonster(float DetectRange)
{
	TArray<FOverlapResult> OverlapResults;

	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
		OverlapResults,
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel8, // 채널 변경
		FCollisionShape::MakeSphere(DetectRange * 100.0f),
		CollisionQueryParam
	);

	return OverlapResults;
}
void AMonster::SetActive()
{
	if (bIsDead)
	{
		HpBarWidget->SetHiddenInGame(true);
		SetActorEnableCollision(false);

		HitEffectComponent->SetActive(false);
		BurnEffectComponent->SetActive(false);
		FloodingEffectComponent->SetActive(false);
		ShockEffectComponent->SetActive(false);
		TransitionEffectComponent->SetActive(false);
		AssembleEffectComponent->SetActive(false);
		GroggyEffectComponent->SetActive(false);
	}
}
#pragma region Debuff
void AMonster::Burn()
{
	if (bIsFlooding)
	{
		//이동속도를 원래대로
		MonsterInfo.MoveSpeed = MonsterInfo.DefaultMoveSpeed;
		MonsterInfo.BattleWalkMoveSpeed = MonsterInfo.DefaultBattleWalkMoveSpeed;

		//애니메이션 속도를 원래대로
		MonsterAnimInstance->SetPlayRate(1.0f);
		MonsterAnimInstance->Montage_SetPlayRate(MonsterAnimInstance->GetCurrentActiveMontage(), 1.0f);
		bIsFlooding = false;
	}

	if (MonsterAnimInstance->GetShockIsPlaying())
	{
		MonsterAIController->ShockCancel();
		bIsShock = false;
	}
	FloodingEffectComponent->SetActive(false);
	ShockEffectComponent->SetActive(false);
	BurnEffectComponent->SetActive(true);

	MonsterAttributeDebuff.BurnTimer = 0.0f;
	bIsBurn = true;
}
void AMonster::Flooding()
{
	bIsBurn = false;

	if (MonsterAnimInstance->GetShockIsPlaying())
	{
		MonsterAIController->ShockCancel();
		bIsShock = false;
	}
	BurnEffectComponent->SetActive(false);
	ShockEffectComponent->SetActive(false);
	FloodingEffectComponent->SetActive(true);

	MonsterAttributeDebuff.FloodingTimer = 0.0f;

	if (!bIsFlooding)
	{
		MonsterInfo.MoveSpeed = MonsterInfo.MoveSpeed * MonsterAttributeDebuff.FloodingDebuffSpeedReductionValue;
		MonsterInfo.BattleWalkMoveSpeed = MonsterInfo.BattleWalkMoveSpeed * MonsterAttributeDebuff.FloodingDebuffSpeedReductionValue;

		MonsterAnimInstance->SetPlayRate(MonsterAttributeDebuff.FloodingDebuffSpeedReductionValue);
		MonsterAnimInstance->Montage_SetPlayRate(MonsterAnimInstance->GetCurrentActiveMontage(), MonsterAttributeDebuff.FloodingDebuffSpeedReductionValue);
	}
	bIsFlooding = true;
}
void AMonster::Shock()
{
	bIsBurn = false;
	if (bIsFlooding)
	{
		//이동속도를 원래대로
		MonsterInfo.MoveSpeed = MonsterInfo.DefaultMoveSpeed;
		MonsterInfo.BattleWalkMoveSpeed = MonsterInfo.DefaultBattleWalkMoveSpeed;

		//애니메이션 속도를 원래대로
		MonsterAnimInstance->SetPlayRate(1.0f);
		MonsterAnimInstance->Montage_SetPlayRate(MonsterAnimInstance->GetCurrentActiveMontage(), 1.0f);
		bIsFlooding = false;
	}

	BurnEffectComponent->SetActive(false);
	FloodingEffectComponent->SetActive(false);

	if (!bIsGroggy)
	{
		ShockEffectComponent->SetActive(true);
		MonsterAIController->Shock();

		MonsterAttributeDebuff.ShockTimer = 0.0f;
		bIsShock = true;
	}
}
void AMonster::DebuffTransition(EAttributeKeyword AttackedAttribute, float Damage)
{
	if (bTestMode)
		DrawDebugSphere(GetWorld(), GetActorLocation(), MonsterAttributeDebuff.TransitionRange * 100.0f, 16, FColor::Red, false, 0.2f);

	TransitionEffectComponent->SetActive(true);
	TransitionEffectComponent->ForceReset();

	TArray<FOverlapResult> AnotherMonsterList = DetectMonster(MonsterAttributeDebuff.TransitionRange);

	if (AnotherMonsterList.Num() != 0)
	{
		for (auto const& AnotherMonster : AnotherMonsterList)
		{
			AMonster* Monster = Cast<AMonster>(AnotherMonster.GetActor());
			if (Monster == nullptr)
				continue;

			// Monster->AddDebuffStack(AttackedAttribute);
			Monster->SetDebuff(AttackedAttribute, Damage);
			Monster->OnDamage(Damage);
		}
	}
}
void AMonster::Assemble()
{
	if (bTestMode)
		DrawDebugSphere(GetWorld(), GetActorLocation(), MonsterAttributeDebuff.AssembleRange * 100.0f, 16, FColor::Blue, false, 0.2f);

	AssembleEffectComponent->SetActive(true);
	AssembleEffectComponent->ForceReset();

	TArray<FOverlapResult> AnotherMonsterList = DetectMonster(MonsterAttributeDebuff.AssembleRange);

	if (AnotherMonsterList.Num() != 0)
	{
		for (auto const& AnotherMonster : AnotherMonsterList)
		{
			AMonster* Monster = Cast<AMonster>(AnotherMonster.GetActor());
			if (Monster == nullptr)
				continue;

			Monster->bIsAssemble = true;
			Monster->AssembleLocation = GetActorLocation();

			MonsterAIController->SetFind();
		}
	}
}
void AMonster::Chain(EAttributeKeyword PlayerMainAttribute, float Damage)
{
	if (bTestMode)
		DrawDebugSphere(GetWorld(), GetActorLocation(), MonsterAttributeDebuff.ChainRange * 100.0f, 16, FColor::Yellow, false, 0.2f);

	TArray<FOverlapResult> AnotherMonsterList = DetectMonster(MonsterAttributeDebuff.ChainRange);

	if (AnotherMonsterList.Num() != 0)
	{
		auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());

		for (auto const& AnotherMonster : AnotherMonsterList)
		{
			AMonster* Monster = Cast<AMonster>(AnotherMonster.GetActor());
			if (Monster == nullptr)
				continue;

			if (Monster->GetAttribute() == MonsterInfo.MonsterAttribute)
			{
				if (STGameInstance->GetChainMonsterList().Num() < 2)
					STGameInstance->AddChainMonster(Monster);
			}
			/*
			//몬스터의 속성중
			for (auto Elem : Monster->GetMainAttributeDef())
			{
				//플레이어의 공격속성과 겹치는 속성이 있으면
				if (Elem == PlayerMainAttribute)
				{
					//체인 상태
					Monster->bIsChain = true;
					Monster->OnDamage(Damage);
					break;
				}
			}
			*/
		}
		if (STGameInstance->GetChainMonsterList().Num() != 0)
		{
			if (ChainBP == nullptr)
			{
				STARRYLOG(Log, TEXT("Failed Load"));
				return;
			}

			auto ChainLightning = GetWorld()->SpawnActor<AChainLightning>(ChainBP, GetActorLocation(), GetActorRotation());
			ChainLightning->Init();
			ChainLightning->SetMoveSpeed(MonsterAttributeDebuff.ChainSpeed);
			ChainLightning->SetDamage(Damage);
			/*
			auto ChainLightning = GetWorld()->SpawnActor<AChainLightning>(GetActorLocation(), FRotator::ZeroRotator);
			ChainLightning->Init();
			ChainLightning->SetMoveSpeed(MonsterAttributeDebuff.ChainSpeed);
			ChainLightning->SetDamage(Damage);
			*/
		}
	}
}
void AMonster::SetDebuff(EAttributeKeyword AttackedAttribute, float Damage)
{
	switch (AttackedAttribute)
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
void AMonster::PrintHitEffect(FVector AttackedPosition)
{
	float Distance = FVector::Distance(GetActorLocation(), AttackedPosition + FVector(0.0f, 0.0f, -150.0f));
	FVector CompToMonsterDir = GetActorLocation() - (AttackedPosition + FVector(0.0f, 0.0f, -150.0f));
	CompToMonsterDir.Normalize();
	FVector EffectPosition = (AttackedPosition + FVector(0.0f, 0.0f, -150.0f)) + (CompToMonsterDir * (Distance / 2.0f));

	HitEffectComponent->SetWorldLocation(EffectPosition);

	HitEffectComponent->SetActive(true);
	HitEffectComponent->ForceReset();
}
void AMonster::PrintLightningHitEffect()
{
	LightningHitEffectComponent->SetActive(true);
	LightningHitEffectComponent->ForceReset();
}
void AMonster::OffIsAttacked()
{
	bIsAttacked = false;
}
// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	CalcAttributeDefType();
	SetEffect();

	MonsterInfo.DefaultMoveSpeed = MonsterInfo.MoveSpeed;
	MonsterInfo.DefaultBattleWalkMoveSpeed = MonsterInfo.BattleWalkMoveSpeed;

	MonsterInfo.CurrentHp = MonsterInfo.MaxHp;
	MonsterInfo.CurrentDef = MonsterInfo.Def;

	MonsterAIController = Cast<AMonsterAIController>(GetController());

	//방어력 게이지 최대치 설정
	auto HpBar = Cast<UHPBarWidget>(HpBarWidget->GetWidget());
	if (HpBar != nullptr)
	{
		HpBar->UpdateDefWidget(1.0f);
	}

	//사운드 세팅
	HitSound = new SoundManager(HitEvent, GetWorld());

	if (GetActorScale3D().X > 1.0f)
	{
		HitSound->SetVolume(1.5f);

	}
	else {
		HitSound->SetVolume(1.0f);

	}

}
void AMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}
void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnOverlapBegin);
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

	if (bDeadWait)
	{
		DeadWaitTimer += DeltaTime;
		if (DeadWaitTimer >= MonsterInfo.DeadWaitTime)
		{
			SetActorTickEnabled(false);
			SetActorHiddenInGame(true);
		}
		return;
	}

	if (!bIsDead)
	{
		auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
		if (this->GetDistanceTo(STGameInstance->GetPlayer()) < 500.0f)
		{
			bShowUI = true;
			ShowUITimer = 0.0f;
			HpBarWidget->SetHiddenInGame(false);
		}
	}
	else
	{
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
			CalcHp(CalcBurnDamage(MonsterAttributeDebuff.BurnDamage) / 100.0f);
		}
		//화상 지속시간이 설정된 시간이 됐을 때
		if (MonsterAttributeDebuff.BurnTimer >= MonsterAttributeDebuff.BurnTime)
		{
			//시간 초기화 및 화상 상태 해제
			MonsterAttributeDebuff.BurnTimer = 0.0f;
			BurnEffectComponent->SetActive(false);
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

			FloodingEffectComponent->SetActive(false);
			//침수 상태 해제
			bIsFlooding = false;
		}
	}
	if (bIsShock)
	{
		MonsterAttributeDebuff.ShockTimer += DeltaTime;

		if (MonsterAttributeDebuff.ShockTimer >= MonsterAttributeDebuff.ShockTime)
		{
			MonsterAttributeDebuff.ShockTimer = 0.0f;
			ShockEffectComponent->SetActive(false);
			bIsShock = false;
		}
	}
	if (bIsAssemble)
	{
		//중심 몬스터로 향하는 벡터
		FVector MoveDirection = AssembleLocation - GetActorLocation();
		//끌려가는 힘 계산
		FVector NewLocation = GetTransform().GetLocation() + (MoveDirection * (MonsterAttributeDebuff.AssembleSpeed / 100.0f) * DeltaTime);

		SetActorLocation(NewLocation);

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

	if (bIsAttacked) // 0.2
	{
		KnockBackTime += DeltaTime;

		FVector NewLocation = GetActorLocation() + (KnockBackDir * (MonsterInfo.KnockBackPower * (0.8f)) * (DeltaTime * 3));

		SetActorLocation(NewLocation);

		if (KnockBackTime > 0.15f)
		{
			KnockBackTime = 0.0f;
			bIsAttacked = false;
		}
	}
	if (bShowUI)
	{
		ShowUITimer += DeltaTime;

		if (ShowUITimer >= ShowUITime)
		{
			ShowUITimer = 0.0f;
			HpBarWidget->SetHiddenInGame(true);
			bShowUI = false;
		}
	}
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AMonster::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString CompName = OtherComp->GetName();
	FString FindName = "WEAPON";
	if (CompName == FindName)
	{
		PrintHitEffect(OtherComp->GetComponentLocation());

		auto Player = Cast<AIreneCharacter>(OtherActor);
		Player->HitStopEvent();
		HitStopEvent();
		return;
	}

	auto ChainLightningComp = Cast<USphereComponent>(OtherComp);
	if (ChainLightningComp != nullptr)
	{
		FString CompProfileName = ChainLightningComp->GetCollisionProfileName().ToString();
		FindName = "ChainLightning";
		if (CompProfileName == FindName)
		{
			auto ChainLightning = Cast<AChainLightning>(OtherActor);
			auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
			if (STGameInstance->GetChainMonsterList().Num() != 0)
			{
				for (auto& Elem : STGameInstance->GetChainMonsterList())
				{
					if (Elem == this)
					{
						OnDamage(ChainLightning->GetDamage());
						PrintLightningHitEffect();
						LightningHitEffectComponent->SetActive(true);
						LightningHitEffectComponent->ForceReset();
					}
				}
			}
		}
	}
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
		SoundTransform = Player->GetTransform();

		if (!bIsAttacked)
		{
			FString FindName = "WEAPON";
			FString ElemName;

			for (auto& Elem : Player->GetComponents())
			{
				ElemName = Elem->GetName();
				if (ElemName == FindName)
				{
					auto Component = Cast<UPrimitiveComponent>(Elem);

					PrintHitEffect(Component->GetComponentLocation());
					Player->HitStopEvent();
				}
			}
		}

		bIsAttacked = true;

		switch (Player->GetAttribute())
		{
		case EAttributeKeyword::e_Fire:
			if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Water)
			{
				AttackedInfo.AttributeArmor = 50.0f;
			}
			else if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Thunder)
			{
				AttackedInfo.AttributeArmor = 200.0f;
			}
			break;
		case EAttributeKeyword::e_Water:
			if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Fire)
			{
				AttackedInfo.AttributeArmor = 200.0f;
			}
			else if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Thunder)
			{
				AttackedInfo.AttributeArmor = 50.0f;
			}
			break;
		case EAttributeKeyword::e_Thunder:
			if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Fire)
			{
				AttackedInfo.AttributeArmor = 50.0f;
			}
			else if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Water)
			{
				AttackedInfo.AttributeArmor = 200.0f;
			}
		}

		//넉백
		KnockBackDir = -(Player->GetActorLocation() - GetActorLocation());
		KnockBackDir.Normalize();
		KnockBackDir.Z = 0.0f;

		//

		auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
		if (STGameInstance->GetAttributeEffectMonster() == nullptr)
		{
			STGameInstance->SetAttributeEffectMonster(this);
			HitSound->SoundPlay3D(SoundTransform);
		}

		if (AttackedInfo.bIsUseMana)
		{
			CalcDef();
			CalcAttributeDebuff(Player->GetAttribute(), DamageAmount);
			CalcHp(CalcNormalAttackDamage(DamageAmount) / 3.0);
		}
		else
		{
			CalcHp(CalcNormalAttackDamage(DamageAmount) / 1.5);
		}
		InitAttackedInfo();
		return FinalDamage;
	}

	return FinalDamage;
}
