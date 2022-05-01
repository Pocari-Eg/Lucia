// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "./Morbit/Morbit.h"
#include "./Morbit/MbAIController.h"
#include "./Bouldelith/Bouldelith.h"
#include "./Bouldelith/BdAIController.h"
#include "MonsterAIController.h"
//UI
#include "../STGameInstance.h"
#include "../PlayerSource/IreneAttackInstance.h"
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

	HpBarWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	HpBarWidget->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBARWIDGET(TEXT("/Game/UI/BluePrint/BP_HPBar.BP_HPBar_C"));

	if (UI_HPBARWIDGET.Succeeded()) {

		HpBarWidget->SetWidgetClass(UI_HPBARWIDGET.Class);
		HpBarWidget->SetDrawSize(FVector2D(96, 80.0f));
		HpBarWidget->bAutoActivate = false;
	}

	InitEffect();
}
#pragma region Init
void AMonster::InitMonsterAttribute()
{
	switch (MonsterInfo.Code)
	{
	case 1:
		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
		break;
	case 2:
		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_None;
		break;
	case 3:
		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Fire;
		break;
	case 4:
		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Fire;
		break;
	case 5:
		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Water;
		break;
	case 6:
		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Water;
		break;
	case 7:
		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Thunder;
		break;
	case 8:
		MonsterInfo.MonsterAttribute = EAttributeKeyword::e_Thunder;
		break;
	default:
		break;
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
	SparkEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SparkEffect"));
	TransitionEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TransitionEffect"));
	AssembleEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AssembleEffect"));
	GroggyEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GroggyEffect"));


	HitEffectComponent->SetupAttachment(GetMesh());
	LightningHitEffectComponent->SetupAttachment(GetMesh());
	BurnEffectComponent->SetupAttachment(GetMesh());
	FloodingEffectComponent->SetupAttachment(GetMesh());
	SparkEffectComponent->SetupAttachment(GetMesh());
	TransitionEffectComponent->SetupAttachment(GetMesh());
	AssembleEffectComponent->SetupAttachment(GetMesh());
	GroggyEffectComponent->SetupAttachment(RootComponent);

	HitEffectComponent->bAutoActivate = false;
	LightningHitEffectComponent->bAutoActivate = false;
	BurnEffectComponent->bAutoActivate = false;
	FloodingEffectComponent->bAutoActivate = false;
	SparkEffectComponent->bAutoActivate = false;
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
bool AMonster::GetTestMode() const
{
	return bTestMode;
}
float AMonster::GetViewAngle() const
{
	return MonsterInfo.ViewAngle;
}
float AMonster::GetViewRange() const
{
	return MonsterInfo.ViewRange;
}
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
float AMonster::GetHp() const
{
	return MonsterInfo.CurrentHp;
}
FVector AMonster::GetLocation() const
{
	return GetActorLocation() + FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}
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
#pragma endregion
void AMonster::SetAttackedInfo(bool bIsUseMana, float Mana, EAttackedDirection AttackedDirection)
{
	AttackedInfo.bIsUseMana = bIsUseMana;
	AttackedInfo.Mana = Mana;
	AttackedInfo.AttackedDirection = AttackedDirection;
}
void AMonster::SetEffect()
{
	HitEffectComponent->SetTemplate(MonsterEffect.HitEffect);
	LightningHitEffectComponent->SetTemplate(MonsterEffect.LightningHitEffect);
	BurnEffectComponent->SetTemplate(MonsterEffect.BurnEffect);
	FloodingEffectComponent->SetTemplate(MonsterEffect.FloodingEffect);
	SparkEffectComponent->SetTemplate(MonsterEffect.SparkEffect);
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

	SparkEffectComponent->SetRelativeRotation(MonsterEffect.DebuffEffectRotation);
	SparkEffectComponent->SetRelativeScale3D(MonsterEffect.DebuffEffectScale);

	TransitionEffectComponent->SetRelativeRotation(MonsterEffect.TransitionEffectRotation);
	TransitionEffectComponent->SetRelativeScale3D(MonsterEffect.TransitionEffectScale);

	AssembleEffectComponent->SetRelativeRotation(MonsterEffect.AssembleEffectRotation);
	AssembleEffectComponent->SetRelativeScale3D(MonsterEffect.AssembleEffectScale);

	GroggyEffectComponent->SetRelativeRotation(MonsterEffect.GroggyEffectRotation);
	GroggyEffectComponent->SetRelativeScale3D(MonsterEffect.GroggyEffectScale);
}

#pragma region Calc
void AMonster::CalcAttributeDebuff(EAttributeKeyword PlayerMainAttribute, float Damage)
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());

	switch (PlayerMainAttribute)
	{
	case EAttributeKeyword::e_Fire:
		if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Fire)
		{
			return;
		}
		if(MonsterAttributeDebuff.FireDebuffStack < 6)
			MonsterAttributeDebuff.FireDebuffStack++;
		SetDebuff(PlayerMainAttribute, Damage);
		break;
	case EAttributeKeyword::e_Water:
		if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Water)
		{
			return;
		}
		if(MonsterAttributeDebuff.WaterDebuffStack < 6)
			MonsterAttributeDebuff.WaterDebuffStack++;
		SetDebuff(PlayerMainAttribute, Damage);
		break;
	case EAttributeKeyword::e_Thunder:
		if (MonsterInfo.MonsterAttribute == EAttributeKeyword::e_Thunder)
		{
			return;
		}
		if(MonsterAttributeDebuff.ThunderDebuffStack < 6)
			MonsterAttributeDebuff.ThunderDebuffStack++;
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
		if (SparkEffectComponent->IsActive())
		{
			SparkEffectComponent->SetActive(false);
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
	if (Cast<AMorbit>(this))
	{
		auto Morbit = Cast<AMorbit>(this);
		auto MbAIController = Cast<AMbAIController>(Morbit->GetController());

		MbAIController->Attacked(AttackedInfo.AttackedDirection, AttackedInfo.AttackedPower, AttackedInfo.bIsUseMana);
	}
	if (Cast<ABouldelith>(this))
	{
		auto Bouldelith = Cast<ABouldelith>(this);
		auto BdAIController = Cast<ABdAIController>(Bouldelith->GetController());

		BdAIController->Attacked();
	}
	MonsterAIController->StopMovement();
	if (MonsterInfo.CurrentDef < 80)
		return MonsterInfo.ArbitraryConstValueA * (Damage) * (AttackedInfo.AttributeArmor / 100.0f);
	return MonsterInfo.ArbitraryConstValueA * (Damage / (MonsterInfo.CurrentDef / 80.0f)) * (AttackedInfo.AttributeArmor / 100.0f);
}
float AMonster::CalcBurnDamage()
{
	return MonsterAttributeDebuff.BurnDamage * 5;
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

		HitEffectComponent->SetActive(false);
		BurnEffectComponent->SetActive(false);
		FloodingEffectComponent->SetActive(false);
		SparkEffectComponent->SetActive(false);
		TransitionEffectComponent->SetActive(false);
		AssembleEffectComponent->SetActive(false);
		GroggyEffectComponent->SetActive(false);
	}
}
void AMonster::MarkerOn()
{
	auto HpBar = Cast<UHPBarWidget>(HpBarWidget->GetWidget());
	if (HpBar != nullptr)
	{
		HpBar->MarkerOn();
	}
}
void AMonster::MarkerOff()
{
	auto HpBar = Cast<UHPBarWidget>(HpBarWidget->GetWidget());
	if (HpBar != nullptr)
	{
		HpBar->MarkerOff();
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

	FloodingEffectComponent->SetActive(false);
	SparkEffectComponent->SetActive(false);
	BurnEffectComponent->SetActive(true);

	MonsterAttributeDebuff.WaterDebuffStack = 0;
	MonsterAttributeDebuff.ThunderDebuffStack = 0;

	MonsterAttributeDebuff.BurnTimer = 0.0f;
	bIsBurn = true;
}
void AMonster::Flooding()
{
	bIsBurn = false;
	bIsSpark = false;

	
	BurnEffectComponent->SetActive(false);
	SparkEffectComponent->SetActive(false);
	FloodingEffectComponent->SetActive(true);

	MonsterAttributeDebuff.FireDebuffStack = 0;
	MonsterAttributeDebuff.ThunderDebuffStack = 0;

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
void AMonster::Spark()
{
	bIsBurn = false;
	bIsFlooding = false;

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

	FloodingEffectComponent->SetActive(false);
	BurnEffectComponent->SetActive(false);
	SparkEffectComponent->SetActive(true);

	MonsterAttributeDebuff.FireDebuffStack = 0;
	MonsterAttributeDebuff.WaterDebuffStack = 0;

	MonsterAttributeDebuff.SparkTimer = 0.0f;

	bIsSpark = true;
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
		Spark();
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
void AMonster::OffShockDebuffEffect()
{
	SparkEffectComponent->SetActive(false);
}
void AMonster::OffIsAttacked()
{
	bIsAttacked = false;
}
void AMonster::PlayIdleAnim()
{
	MonsterAnimInstance->PlayIdleMontage();
}
void AMonster::PlayDetectAnim()
{
	MonsterAnimInstance->PlayDetectMontage();
}
void AMonster::PlayWalkAnim()
{
	MonsterAnimInstance->PlayWalkMontage();
}
// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

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
			CalcHp(CalcBurnDamage());
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
	if (bIsSpark)
	{
		MonsterAttributeDebuff.SparkTimer += DeltaTime;

		if (MonsterAttributeDebuff.SparkTimer >= MonsterAttributeDebuff.SparkTime)
		{
			MonsterAttributeDebuff.SparkTimer = 0.0f;

			SparkEffectComponent->SetActive(false);

			bIsSpark = false;
		}
	}
	if (bIsAttacked) // 0.2
	{
		KnockBackTime += DeltaTime;

		FVector NewLocation = GetActorLocation() + (KnockBackDir * (MonsterInfo.KnockBackPower * (0.15f - KnockBackTime)));
		

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
void AMonster::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString CompName = OtherComp->GetName();
	FString FindName = "WEAPON";
	if (CompName == FindName)
	{
		PrintHitEffect(OtherComp->GetComponentLocation());

		auto Player = Cast<AIreneCharacter>(OtherActor);
		return;
	}
}
float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (bIsAttacking)
		bIsAttacking = false;

	if (bIsDead)
		return FinalDamage;

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
					HitStopEvent();
				}
			}
		}

		bIsAttacked = true;


		switch (Player->IreneAttack->GetAttribute())
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

		if (AttackedInfo.AttributeArmor == 50)
		{
			AttackedInfo.AttackedPower = EAttackedPower::Halved;
		}
		else if (AttackedInfo.AttributeArmor == 100)
		{
			AttackedInfo.AttackedPower = EAttackedPower::Normal;
		}
		else if (AttackedInfo.AttributeArmor == 200)
		{
			AttackedInfo.AttackedPower = EAttackedPower::Critical;
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
			CalcAttributeDebuff(Player->IreneAttack->GetAttribute(), DamageAmount);
			CalcHp(CalcNormalAttackDamage(DamageAmount));
		}
		else
		{
			CalcHp(CalcNormalAttackDamage(DamageAmount));
		}
		InitAttackedInfo();
		return FinalDamage;
	}

	return FinalDamage;
}
