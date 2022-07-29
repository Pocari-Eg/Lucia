// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "./Morbit/Morbit.h"
#include "./Morbit/MbAIController.h"
#include "./Bouldelith/Bouldelith.h"
#include "./Bouldelith/BdAIController.h"
#include "./Scientia/Scientia.h"
#include "./Scientia/ScAIController.h"
#include "MonsterAIController.h"
//UI
#include "../STGameInstance.h"
#include "../PlayerSource/IreneAttackInstance.h"
#include "../PlayerSource/IreneFSM.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "../UI/MonsterWidget.h"

#include"../PlayerSource/Quill.h"

//object
#include "../Object/AttributeObject.h"

// Sets default values
AMonster::AMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	InitAttackedInfo();

	KnockBackTime = 0.15f;
	ShowUITime = 5.0f;

	MonsterWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MONSTERWIDGET"));
	MonsterWidget->SetupAttachment(GetMesh());

	MonsterWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	MonsterWidget->SetWidgetSpace(EWidgetSpace::World);



	static ConstructorHelpers::FClassFinder<UUserWidget> UI_MONSTERWIDGET(TEXT("/Game/UI/BluePrint/Monster/BP_MonsterWidget.BP_MonsterWidget_C"));

	if (UI_MONSTERWIDGET.Succeeded()) {

		MonsterWidget->SetWidgetClass(UI_MONSTERWIDGET.Class);
		MonsterWidget->SetDrawSize(FVector2D(100.0f,160.0f));
		MonsterWidget->bAutoActivate = false;
	}


	WidgetPoint = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WIDGETPOINT"));
	WidgetPoint->SetupAttachment(GetMesh());
	TargetWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TARGETWIDGET"));
	TargetWidget->SetupAttachment(WidgetPoint);

	TargetWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	TargetWidget->SetWidgetSpace(EWidgetSpace::World);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_TARGETWIDGET(TEXT("/Game/UI/BluePrint/Monster/BP_TargetWdiget.BP_TargetWdiget_C"));

	if (UI_TARGETWIDGET.Succeeded()) {

		TargetWidget->SetWidgetClass(UI_TARGETWIDGET.Class);
		TargetWidget->SetDrawSize(FVector2D(50.0f,50.0f));
		TargetWidget->bAutoActivate = false;
	}
	bIsSpawnEnemy = false;
	bIsObject = true;
	InitEffect();


	MonsterInfo.ManaShieldDec = 30;

    bShowUI = false;
	ShowUITimer = 0.0f;
	ShowUITime = 300.0f;


	//quill
	MonsterInfo.Quill_CurStack = 0;
	MonsterInfo.Quill_MaxStack = 3;
}
#pragma region Init
void AMonster::InitMonsterAttribute()
{
	switch (MonsterInfo.M_Atk_Type)
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
void AMonster::InitAttackedInfo()
{
	AttackedInfo.bIsUseMana = false;
	AttackedInfo.Mana = 0.0f;
	AttackedInfo.AttributeArmor = 100.0f;
}
void AMonster::InitEffect()
{
	HitEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitEffect"));
	BurnEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BurnEffect"));
	FloodingEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FloodingEffect"));
	SparkEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SparkEffect"));
	GroggyEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GroggyEffect"));
	ManaShiledEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ManaSheildEffect"));

	HitEffectComponent->SetupAttachment(GetMesh());
	BurnEffectComponent->SetupAttachment(GetMesh());
	FloodingEffectComponent->SetupAttachment(GetMesh());
	SparkEffectComponent->SetupAttachment(GetMesh());
	GroggyEffectComponent->SetupAttachment(RootComponent);
	ManaShiledEffectComponent->SetupAttachment(GetMesh());

	HitEffectComponent->bAutoActivate = false;
	BurnEffectComponent->bAutoActivate = false;
	FloodingEffectComponent->bAutoActivate = false;
	SparkEffectComponent->bAutoActivate = false;
	GroggyEffectComponent->bAutoActivate = false;
	ManaShiledEffectComponent->bAutoActivate = false;

	MonsterEffect.HitEffectRotation = FRotator(0.0f, 0.0f, 0.0f);
	MonsterEffect.HitEffectScale = FVector(1.0f, 1.0f, 1.0f);

	MonsterEffect.DebuffEffectRotation = FRotator(0.0f, 0.0f, 0.0f);
	MonsterEffect.DebuffEffectScale = FVector(1.0f, 1.0f, 1.0f);

	MonsterEffect.GroggyEffectRotation = FRotator(0.0f, 0.0f, 0.0f);
	MonsterEffect.GroggyEffectScale = FVector(1.0f, 1.0f, 1.0f);

	MonsterEffect.ManaShieldEffectRotation = FRotator(0.0f, 0.0f, 0.0f);
	MonsterEffect.ManaShieldEffectScale = FVector(1.0f, 1.0f, 1.0f);
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
float AMonster::GetViewHeight() const
{
	return MonsterInfo.ViewHeight;
}
float AMonster::GetMeleeAttackRange() const
{
	return MonsterInfo.MeleeAttackRange;
}
float AMonster::GetTraceRange() const
{
	return MonsterInfo.TraceRange;
}
float AMonster::GetBattleWalkSpeed() const
{
	return MonsterInfo.BattleWalkMoveSpeed;
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
bool AMonster::GetIsBattleState() const
{
	return bIsBattleState;
}
EAttributeKeyword AMonster::GetBarrierAttribute() const
{
	if (!MonsterInfo.bIsShieldOn)
	{
		return EAttributeKeyword::e_None;
	 }
	else {

		return MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].Type;
	}
}
int AMonster::GetCurQuillStack() const
{
	return MonsterInfo.Quill_CurStack;
}
void AMonster::SetCurQuillStack(const int Value)
{
	MonsterInfo.Quill_CurStack = Value;
	
	auto widget = Cast<UMonsterWidget>(MonsterWidget->GetWidget());
	if (widget != nullptr) {
		widget->SetQuillStackCount(MonsterInfo.Quill_CurStack);
	}

}
AMonsterAIController* AMonster::GetAIController() const
{
	return MonsterAIController;
}
float AMonster::GetHpRatio()
{
	return MonsterInfo.CurrentHp < KINDA_SMALL_NUMBER ? 0.0f : MonsterInfo.CurrentHp / MonsterInfo.M_Max_HP;
}
float AMonster::GetDefRatio()
{

		if (!MonsterInfo.bIsShieldOn)return 0.0f;
		else
		{
			return MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF < KINDA_SMALL_NUMBER ? 0.0f :
				MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF / MaxBarrier;
		}

}
void AMonster::ChangeAttributeDelegate()
{
	AttributeChange.Broadcast();
}
#pragma endregion
void AMonster::SetSpawnPos()
{
	MonsterAIController->SetSpawnPos(GetLocation());
}
void AMonster::SetAttackedInfo(bool bIsUseMana, float Mana, EAttackedDirection AttackedDirection)
{
	AttackedInfo.bIsUseMana = bIsUseMana;
	AttackedInfo.Mana = Mana;
	AttackedInfo.AttackedDirection = AttackedDirection;
}
void AMonster::SetIsBattleState(bool Value)
{
	bIsBattleState = Value;

	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	if (Instance != nullptr) {
		bIsBattleState == true ? Instance->AddDetectedMonster() : Instance->SubDetectedMonster();
	}
}
void AMonster::SetEffect()
{
	HitEffectComponent->SetTemplate(MonsterEffect.NoneHitEffect);
	BurnEffectComponent->SetTemplate(MonsterEffect.BurnEffect);
	FloodingEffectComponent->SetTemplate(MonsterEffect.FloodingEffect);
	SparkEffectComponent->SetTemplate(MonsterEffect.SparkEffect);
	GroggyEffectComponent->SetTemplate(MonsterEffect.GroggyEffect);

	HitEffectComponent->SetRelativeRotation(MonsterEffect.HitEffectRotation);
	HitEffectComponent->SetRelativeScale3D(MonsterEffect.HitEffectScale);

	BurnEffectComponent->SetRelativeRotation(MonsterEffect.DebuffEffectRotation);
	BurnEffectComponent->SetRelativeScale3D(MonsterEffect.DebuffEffectScale);

	FloodingEffectComponent->SetRelativeRotation(MonsterEffect.DebuffEffectRotation);
	FloodingEffectComponent->SetRelativeScale3D(MonsterEffect.DebuffEffectScale);

	SparkEffectComponent->SetRelativeRotation(MonsterEffect.DebuffEffectRotation);
	SparkEffectComponent->SetRelativeScale3D(MonsterEffect.DebuffEffectScale);

	GroggyEffectComponent->SetRelativeRotation(MonsterEffect.GroggyEffectRotation);
	GroggyEffectComponent->SetRelativeScale3D(MonsterEffect.GroggyEffectScale);

	ManaShiledEffectComponent->SetRelativeRotation(MonsterEffect.ManaShieldEffectRotation);
	ManaShiledEffectComponent->SetRelativeScale3D(MonsterEffect.ManaShieldEffectScale);
	
}

void AMonster::SetManaShieldEffct()
{
	switch (MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].Type)
	{
	case EAttributeKeyword::e_Fire:
		ManaShiledEffectComponent->SetTemplate(MonsterEffect.FireManaShieldEffect);
		break;
	case EAttributeKeyword::e_Water:
		ManaShiledEffectComponent->SetTemplate(MonsterEffect.WaterManaShieldEffect);
		break;
	case EAttributeKeyword::e_Thunder:
		ManaShiledEffectComponent->SetTemplate(MonsterEffect.ThunderManaShieldEffect);
		break;
	case EAttributeKeyword::e_None:
		ManaShiledEffectComponent->SetTemplate(MonsterEffect.NoneManaShieldEffect);
		break;
	}
}

#pragma region Calc

float AMonster::CalcNormalAttackDamage(float Damage)
{
	if (Cast<AMorbit>(this))
	{
		auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
		auto Player = GameInstance->GetPlayer();

		bool IsKnockback = Player->IreneState->IsKnockBackState();

		auto Morbit = Cast<AMorbit>(this);
		auto MbAIController = Cast<AMbAIController>(Morbit->GetController());

		MbAIController->Attacked(AttackedInfo.AttackedDirection, AttackedInfo.AttackedPower, AttackedInfo.bIsUseMana, IsKnockback);

	}
	if (Cast<AScientia>(this)) {

		auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
		auto Player = GameInstance->GetPlayer();

		bool IsKnockback = Player->IreneState->IsKnockBackState();

		auto Scientia = Cast<AScientia>(this);
		auto  ScAIController = Cast<AScAIController>(Scientia->GetController());

		ScAIController->Attacked();

	}
	if (Cast<ABouldelith>(this))
	{
		
		auto Bouldelith = Cast<ABouldelith>(this);
		auto BdAIController = Cast<ABdAIController>(Bouldelith->GetController());

		//방어력 게이지 업데이트
		OnBarrierChanged.Broadcast();

		if(AttackedInfo.AttackedPower != EAttackedPower::Halved && AttackedInfo.bIsUseMana)
			BdAIController->Attacked();
	}

	MonsterAIController->StopMovement();
	

	return Damage;
}

void AMonster::CalcManaShield(float Damage, EAttributeKeyword AttackAttribute)
{
	auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
	//속성 배리어
	if (MonsterInfo.bIsShieldOn)
	{
		switch (MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].Type)
		{
		case EAttributeKeyword::e_Fire:
			if (AttackAttribute == EAttributeKeyword::e_Water)
			{
				MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF -= Damage;


				OnBarrierChanged.Broadcast();
				if (MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF <= 0)
				{
					SoundInstance->PlayShieldCrashSound();
					MonsterInfo.Ele_Shield_Count -= 1;

					if (MonsterInfo.Ele_Shield_Count < 0)
					{
						MonsterInfo.bIsShieldOn = false;
						ManaShiledEffectComponent->SetActive(false);
						ManaShiledEffectComponent->SetVisibility(false);
						OnBarrierChanged.Broadcast();

						/*HitEffectComponent->SetActive(true);
						HitEffectComponent->ForceReset();*/
					

					}
					else {

						MaxBarrier = MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF;
						OnBarrierChanged.Broadcast();
						SetManaShieldEffct();
					}
				}

			}
			break;
		case EAttributeKeyword::e_Water:
			if (AttackAttribute == EAttributeKeyword::e_Thunder)
			{
				MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF -= Damage;
				OnBarrierChanged.Broadcast();
				if (MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF <= 0)
				{
					SoundInstance->PlayShieldCrashSound();
					MonsterInfo.Ele_Shield_Count -= 1;

					if (MonsterInfo.Ele_Shield_Count < 0)
					{
						MonsterInfo.bIsShieldOn = false;
						ManaShiledEffectComponent->SetActive(false);
						ManaShiledEffectComponent->SetVisibility(false);
						OnBarrierChanged.Broadcast();
						
					}
					else {

						MaxBarrier = MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF;
						OnBarrierChanged.Broadcast();
						SetManaShieldEffct();
					}
				}
			}
			break;
		case EAttributeKeyword::e_Thunder:
			if (AttackAttribute == EAttributeKeyword::e_Fire)
			{
				MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF -= Damage;
				OnBarrierChanged.Broadcast();
				if (MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF <= 0)
				{
					SoundInstance->PlayShieldCrashSound();
					MonsterInfo.Ele_Shield_Count -= 1;
					if (MonsterInfo.Ele_Shield_Count < 0)
					{
						MonsterInfo.bIsShieldOn = false;
						OnBarrierChanged.Broadcast();
						ManaShiledEffectComponent->SetActive(false);
						ManaShiledEffectComponent->SetVisibility(false);
					}
					else {

						MaxBarrier = MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF;
						OnBarrierChanged.Broadcast();
						SetManaShieldEffct();
					}
				}
			}
			break;
		case EAttributeKeyword::e_None:
				MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF -= Damage;
				OnBarrierChanged.Broadcast();
				if (MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF <= 0)
				{
					SoundInstance->PlayShieldCrashSound();
					MonsterInfo.Ele_Shield_Count -= 1;
					if (MonsterInfo.Ele_Shield_Count < 0)
					{
						MonsterInfo.bIsShieldOn = false;
						OnBarrierChanged.Broadcast();
						ManaShiledEffectComponent->SetActive(false);
						ManaShiledEffectComponent->SetVisibility(false);
					}
					else {

						MaxBarrier = MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF;
						OnBarrierChanged.Broadcast();
						SetManaShieldEffct();
					}
				}
			break;
		default:
			break;
		}

	}
}
void AMonster::CalcQuillStack(EAttributeKeyword AttackAttribute)
{

	auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
	//속성 배리어
	if (MonsterInfo.bIsShieldOn)
	{
		switch (MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].Type)
		{
		case EAttributeKeyword::e_Fire:
			if (AttackAttribute == EAttributeKeyword::e_Water)
			{
				SetCurQuillStack(MonsterInfo.Quill_CurStack + 1);

				if (MonsterInfo.Quill_CurStack == MonsterInfo.Quill_MaxStack)
				{
					GameInstance->GetPlayer()->IreneAttack->WaterQuillStack(MonsterInfo.Quill_MaxStack);
					MonsterInfo.Quill_CurStack = 0;
					CalcManaShield(MonsterInfo.Quill_MaxStackDamage, AttackAttribute);
				}
			}
			break;
		case EAttributeKeyword::e_Water:
			if (AttackAttribute == EAttributeKeyword::e_Thunder)
			{
				SetCurQuillStack(MonsterInfo.Quill_CurStack + 1);

				if (MonsterInfo.Quill_CurStack == MonsterInfo.Quill_MaxStack)
				{
					GameInstance->GetPlayer()->IreneAttack->ThunderQuillStack(MonsterInfo.Quill_MaxStack);
					MonsterInfo.Quill_CurStack = 0;
					CalcManaShield(MonsterInfo.Quill_MaxStackDamage, AttackAttribute);
				}
			}
			break;
		case EAttributeKeyword::e_Thunder:
			if (AttackAttribute == EAttributeKeyword::e_Fire)
			{
				SetCurQuillStack(MonsterInfo.Quill_CurStack + 1);
				
			

				if (MonsterInfo.Quill_CurStack == MonsterInfo.Quill_MaxStack)
				{
					GameInstance->GetPlayer()->IreneAttack->FireQuillStack(MonsterInfo.Quill_MaxStack);
					MonsterInfo.Quill_CurStack = 0;
					CalcManaShield(MonsterInfo.Quill_MaxStackDamage, AttackAttribute);
				}
			}
			break;
		case EAttributeKeyword::e_None:
			
			SetCurQuillStack(MonsterInfo.Quill_CurStack + 1);
			//
			if (MonsterInfo.Quill_CurStack == MonsterInfo.Quill_MaxStack)
			{
				
						switch (AttackAttribute)
						{
						case EAttributeKeyword::e_Fire:
							GameInstance->GetPlayer()->IreneAttack->FireQuillStack(MonsterInfo.Quill_MaxStack);
							break;
						case EAttributeKeyword::e_Water:
							GameInstance->GetPlayer()->IreneAttack->WaterQuillStack(MonsterInfo.Quill_MaxStack);
							break;
						case EAttributeKeyword::e_Thunder:
							GameInstance->GetPlayer()->IreneAttack->ThunderQuillStack(MonsterInfo.Quill_MaxStack);
							break;
						default:
							break;
						}

				MonsterInfo.Quill_CurStack = 0;
				CalcManaShield(MonsterInfo.Quill_MaxStackDamage, AttackAttribute);
			}
			break;
		}

	}
}
void AMonster::CalcHp(float Damage)
{
		Damage = FMath::Abs(Damage);

		//if (!Cast<AScientia>(this))
		//{
		//	if (CheckPlayerIsBehindMonster() && !bIsBattleState)
		//	{
		//		RotationToPlayerDirection();
		//		MonsterInfo.CurrentHp -= Damage * 1.5f;
		//	}
		//	else
		//	{
		//		MonsterInfo.CurrentHp -= Damage;
		//	}
		//}
		//else
		//{
		//	MonsterInfo.CurrentHp -= Damage;
		//}
		MonsterInfo.CurrentHp -= Damage;


		if (bTestMode)
			STARRYLOG(Log, TEXT("Monster Hp : %f"), MonsterInfo.CurrentHp);

		/*bShowUI = true;
		ShowUITimer = 0.0f;
		MonsterWidget->SetHiddenInGame(false);*/

		OnHpChanged.Broadcast();

		if (MonsterInfo.CurrentHp <= 0.0f)
		{
			MonsterDeadEvent();
			bIsDead = true;
			SetActive();

			MonsterAIController->Death();
			PlayDeathAnim();


			if (bIsSpawnEnemy) {
				auto instnace = Cast<USTGameInstance>(GetGameInstance());
				if (instnace != nullptr)
					instnace->SubEnemyCount(GetRank());
			}
			if (bIsBattleState)
			{
				auto instnace = Cast<USTGameInstance>(GetGameInstance());
				if (instnace != nullptr)
					instnace->SubDetectedMonster();
			}
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
TArray<FOverlapResult> AMonster::DetectPlayer(float DetectRange)
{
	TArray<FOverlapResult> OverlapResults;

	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
		OverlapResults,
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5, // 채널 변경
		FCollisionShape::MakeSphere(DetectRange * 100.0f),
		CollisionQueryParam
	);

	return OverlapResults;
}
FVector AMonster::AngleToDir(float angle)
{
	float radian = FMath::DegreesToRadians(angle);
	FVector Dir = FVector(FMath::Cos(radian), FMath::Sin(radian), 0.f);

	return Dir;
}
void AMonster::SetActive()
{
	if (bIsDead)
	{
		
		MonsterWidget->SetHiddenInGame(true);
		TargetWidget->SetHiddenInGame(true);
		HitEffectComponent->SetActive(false);
		BurnEffectComponent->SetActive(false);
		FloodingEffectComponent->SetActive(false);
		SparkEffectComponent->SetActive(false);
		GroggyEffectComponent->SetActive(false);
		ManaShiledEffectComponent->SetActive(false);
	}
}
void AMonster::MarkerOn()
{
	auto HpBar = Cast<UMonsterWidget>(MonsterWidget->GetWidget());
	if (HpBar != nullptr)
	{
		HpBar->MarkerOn();
	}
}
void AMonster::MarkerOff()
{
	auto HpBar = Cast<UMonsterWidget>(MonsterWidget->GetWidget());
	if (HpBar != nullptr)
	{
		HpBar->MarkerOff();
	}
}
void AMonster::TargetWidgetOn()
{
	TargetWidget->SetVisibility(true);
}
void AMonster::TargetWidgetOff()
{
	TargetWidget->SetVisibility(false);
}
void AMonster::SetSpawnEnemy()
{
	bIsSpawnEnemy = true;
}
EEnemyRank AMonster::GetRank()
{
	return MonsterInfo.M_Type;
}

void AMonster::PrintHitEffect(FVector AttackedPosition, AActor* Actor)
{
	float Distance = FVector::Distance(GetLocation(), AttackedPosition);
	FVector CompToMonsterDir = GetLocation() - AttackedPosition;
	CompToMonsterDir.Normalize();
	FVector EffectPosition = AttackedPosition + (CompToMonsterDir * (Distance / 2.0f));

	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	
	switch (STGameInstance->GetPlayerAttribute())
	{
	case EAttributeKeyword::e_Fire:
		HitEffectComponent->SetTemplate(MonsterEffect.FireHitEffect);
		break;
	case EAttributeKeyword::e_Water:
		EffectPosition = AttackedPosition + (CompToMonsterDir * (Distance / 10.0f));
		HitEffectComponent->SetTemplate(MonsterEffect.WaterHitEffect);
		break;
	case EAttributeKeyword::e_Thunder:
		HitEffectComponent->SetTemplate(MonsterEffect.ThunderHitEffect);
		break;
	case EAttributeKeyword::e_None:
		HitEffectComponent->SetTemplate(MonsterEffect.NoneHitEffect);
		break;
	}
	HitEffectComponent->SetWorldLocation(EffectPosition);

	HitEffectComponent->SetActive(true);
	HitEffectComponent->ForceReset();
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
void AMonster::PlayGroggyAnim()
{
	MonsterAnimInstance->PlayGroggyMontage();
}
void AMonster::PlayDeathAnim()
{
	MonsterAnimInstance->PlayDeathMontage();
}
void AMonster::InitManaShield()
{
	MonsterInfo.Max_Ele_Shield = MonsterInfo.Ele_Shield.Num();
	if (MonsterInfo.Max_Ele_Shield > 0) {
		MonsterInfo.Ele_Shield_Count = MonsterInfo.Max_Ele_Shield - 1;
		MonsterInfo.bIsShieldOn = true;
		MaxBarrier = MonsterInfo.Ele_Shield[MonsterInfo.Ele_Shield_Count].DEF;
		OnBarrierChanged.Broadcast();

		SetManaShieldEffct();
		
		ManaShiledEffectComponent->SetActive(true);
		ManaShiledEffectComponent->SetVisibility(false);
	}
	OnBarrierChanged.Broadcast();
}
// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	SetEffect();

	MonsterInfo.DefaultMoveSpeed = MonsterInfo.M_MoveSpeed;
	MonsterInfo.DefaultBattleWalkMoveSpeed = MonsterInfo.BattleWalkMoveSpeed;

	MonsterInfo.CurrentHp = MonsterInfo.M_Max_HP;
	MonsterAIController = Cast<AMonsterAIController>(GetController());


	


	if (GetActorScale3D().X > 1.0f)
	{
		SoundInstance->GetHitSound()->SetVolume(1.5f);

	}
	else {
		SoundInstance->GetHitSound()->SetVolume(1.0f);

	}

	auto HPBar = Cast<UMonsterWidget>(MonsterWidget->GetWidget());
	HPBar->BindMonster(this);

	TargetWidgetOff();
	MonsterWidget->SetVisibility(false);
	OnSpawnEffectEvent();

}
void AMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}
void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnOverlapBegin);
	//사운드 세팅
	SoundInstance = NewObject<UMonsterSoundInstance>(this);
	SoundInstance->Init();
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//박찬영
	//플레이어의 카메라 좌표와 현재 위젯의 좌표를 통해 위젯이 카메라를 바라보도록 
	FRotator CameraRot = UKismetMathLibrary::FindLookAtRotation(MonsterWidget->GetComponentTransform().GetLocation(),
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());

	// Yaw 값만 변환하여 위젯이 카메라를 따라옴
	MonsterWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
	//

	TargetWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
	WidgetPoint->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
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
		if (this->GetDistanceTo(STGameInstance->GetPlayer()) > 3000.0f)
		{
			ShowUITimer = 0.0f;
			MonsterWidget->SetVisibility(false);
			ManaShiledEffectComponent->SetVisibility(false);
			bShowUI = false;
			TargetWidgetOff();
		}
	}
	else
	{
		return;
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
			MonsterWidget->SetVisibility(false);
			ManaShiledEffectComponent->SetVisibility(false);
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
		PrintHitEffect(OtherComp->GetComponentLocation(), OtherActor);
		return;
	}
}
float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	/*if (Cast<AScientia>(this))
	{
		auto Scientia = Cast<AScientia>(this);

		if (Scientia->GetIsRush())
			return FinalDamage;
	}*/

	if (bIsAttacking)
		bIsAttacking = false;

	if (bIsDead)
		return FinalDamage;
	
	if (Cast<AIreneCharacter>(DamageCauser))
	{
		auto Player = Cast<AIreneCharacter>(DamageCauser);
		if (Player->bIsRadialBlurOn)
		{
			Player->RadialBlurEvent();
			Player->bIsRadialBlurOn = false;
		}

		if (Player != nullptr)
		{

			if (this->MonsterInfo.M_Type != EEnemyRank::e_Raid)
			{
				if (bShowUI)
				{
					ShowUITimer = 0.0f;
				}
				else {
					bShowUI = true;
					ShowUITimer = 0.0f;
					MonsterWidget->SetVisibility(true);
					if (MonsterInfo.bIsShieldOn) {
						ManaShiledEffectComponent->SetVisibility(true);
					}
				}
			}

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

						PrintHitEffect(Component->GetComponentLocation(), DamageCauser);
						HitStopEvent();
					}
				}
			}

			bIsAttacked = true;



			if (AttackedInfo.AttributeArmor == 10)
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
				SoundInstance->PlayHitSound(SoundTransform);
			}



			//몬스터인지 아닌지
			if (bIsObject) {
								
				if (MonsterInfo.bIsShieldOn)
				{
					CalcManaShield(MonsterInfo.ManaShieldDec,Player->GetSwordAttribute());
				}
				else {
					CalcHp(CalcNormalAttackDamage(DamageAmount));
				}
			
			}
			//몬스터가 아니면
			else {

				OffIsAttacked();
				if (Cast<AAttributeObject>(this))
				{
					HitCheck(Player);
				}
			}
			InitAttackedInfo();
			return FinalDamage;
		}
	}
	if (Cast<AQuill>(DamageCauser))
	{
		auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
		EAttributeKeyword AttackAttribute;
		if (STGameInstance != nullptr)
		{
			AttackAttribute = STGameInstance->GetPlayer()->GetQuillAttribute();
		}
		if (this->MonsterInfo.M_Type != EEnemyRank::e_Raid)
		{
			if (bShowUI)
			{
				ShowUITimer = 0.0f;
			}
			else {
				bShowUI = true;
				ShowUITimer = 0.0f;
				MonsterWidget->SetVisibility(true);
				if (MonsterInfo.bIsShieldOn) {
					ManaShiledEffectComponent->SetVisibility(true);
				}
			}
		}

		if (MonsterInfo.bIsShieldOn)
		{
			CalcManaShield(DamageAmount, AttackAttribute);
			CalcQuillStack(AttackAttribute);
		}
		else {
			CalcHp(DamageAmount);

			MonsterInfo.Quill_CurStack++;
			//임시  UI
			auto widget = Cast<UMonsterWidget>(MonsterWidget->GetWidget());
			if (widget != nullptr) {
				widget->SetQuillStackCount(MonsterInfo.Quill_CurStack);
			}
			//
			if (MonsterInfo.Quill_CurStack == MonsterInfo.Quill_MaxStack)
			{
				auto Quill = Cast<AQuill>(DamageCauser);

				{
					if (STGameInstance != nullptr)
					{
						switch (Quill->Attribute)
						{
						case EAttributeKeyword::e_Fire:
							STGameInstance->GetPlayer()->IreneAttack->FireQuillStack(MonsterInfo.Quill_MaxStack);
							break;
						case EAttributeKeyword::e_Water:
							STGameInstance->GetPlayer()->IreneAttack->WaterQuillStack(MonsterInfo.Quill_MaxStack);
							break;
						case EAttributeKeyword::e_Thunder:
							STGameInstance->GetPlayer()->IreneAttack->ThunderQuillStack(MonsterInfo.Quill_MaxStack);
							break;
						default:
							break;
						}
					}
				}


				MonsterInfo.Quill_CurStack = 0;
				CalcHp(MonsterInfo.Quill_MaxStackDamage);
			}
		}

		DamageCauser->Destroy();
		
	}
	return FinalDamage;
}
