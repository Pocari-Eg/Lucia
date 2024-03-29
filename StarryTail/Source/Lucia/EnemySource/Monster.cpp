// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "./Morbit/Morbit.h"
#include "./Morbit/MbAIController.h"
#include "./Bouldelith/Bouldelith.h"
#include "./Bouldelith/BdAIController.h"
#include "./Bellyfish/Bellyfish.h"
#include"./Bellyfish/BellyfishAIController.h"
#include "./Bellarus/Bellarus.h"
#include"./Bellarus/BellarusAIController.h"

#include "MonsterAIController.h"
#include "MonsterProjectile.h"
//UI
#include "../STGameInstance.h"
#include "../PlayerSource/PlayerInstance/IreneAttackInstance.h"
#include "../PlayerSource/PlayerInstance/IreneInputInstance.h"
#include "../PlayerSource/PlayerFSM/IreneFSM.h"
#include "../PlayerSource/PlayerCharacterDataStruct.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "../UI/MonsterWidget.h"

//object
#include "../Object/Trigger/MonsterController.h"
#include "../Object/LabMagic.h"
// Sets default values
AMonster::AMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	InitAttackedInfo();

	KnockBackTime = 0.15f;
	ShowUITime = 5.0f;
	AttackCoolTimer = 0.0f;

	DpsTime = 2.0f;
	DpsTime = 0.0f;
	DpsDamage = 0.0f;

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
	StackWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("StackWidget"));
	StackWidget->SetupAttachment(WidgetPoint);

	StackWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	StackWidget->SetWidgetSpace(EWidgetSpace::World);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_StackWidget(TEXT("/Game/UI/BluePrint/Monster/BP_TargetWdiget.BP_TargetWdiget_C"));

	if (UI_StackWidget.Succeeded()) {

		StackWidget->SetWidgetClass(UI_StackWidget.Class);
		StackWidget->SetDrawSize(FVector2D(512.0f,512.0f));
		StackWidget->bAutoActivate = false;
		StackWidget->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	}
	bIsSpawnEnemy = false;
	InitEffect();

	bIsGroupTriggerEnemy=false;

    bShowUI = false;
	ShowUITimer = 0.0f;
	ShowUITime = 300.0f;

	bIsAttackCool = false;


	FString MonsterDataPath = TEXT("/Game/Math/MonsterDataTable.MonsterDataTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MONSTER(*MonsterDataPath);
	if (DT_MONSTER.Succeeded())
	{
		MonsterDataTable = DT_MONSTER.Object;
	}

	FString MontserSkillDataPath = TEXT("/Game/Math/MonsterSkillDataTable.MonsterSkillDataTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILL(*MontserSkillDataPath);
	if (DT_SKILL.Succeeded())
	{
		MonsterSkillDataTable = DT_SKILL.Object;
	}



	static ConstructorHelpers::FClassFinder<AShieldPoint> BP_WEAPONSOUL (TEXT("/Game/BluePrint/Monster/BP_ShieldPoint.BP_ShieldPoint_C"));

	if (BP_WEAPONSOUL.Succeeded()) {

		ShieldPointClass= BP_WEAPONSOUL.Class;
	}
	bIsDodgeOn = false;


	MonsterShield = CreateDefaultSubobject<UMonsterShield>(TEXT("SHEILD"));
	MonsterShield->SetupAttachment(GetMesh());


	ShieldCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SHEILD_COLLISION"));
	ShiledEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SHEILD_EFFECT"));
	ShiledCrackEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SHEILD_CRACK_EFFECT"));
	ShiledHitEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SHEILD_HIT_EFFECT"));

	ShieldCollision->SetupAttachment(MonsterShield);
	ShiledEffectComponent->SetupAttachment(MonsterShield);
	ShiledCrackEffectComponent->SetupAttachment(MonsterShield);
	ShiledHitEffectComponent->SetupAttachment(MonsterShield);
	ShiledCrackEffectComponent->SetAutoActivate(false);
	ShiledHitEffectComponent->SetAutoActivate(false);

	ShieldCollision->SetCollisionProfileName("Shield");

	ShieldSocketName = "RootSocket";

	MonsterInfo.CurStackCount = 0;
	MonsterInfo.StackEnableDistance = 3000.0f;
	MonsterInfo.M_AttackTraceInterver = 0.5f;

	bIsStatueStart = false;
	bIsAttacking = false;
	

	bIsMoveToFront = true;
	FrontMoveTime = 1.0f;
	FrontMoveTimer = 0.0f;

	bIsCaptin = false;


	AttackedCoolTime = 2.0f;
	AttackedCoolTimer = 0.0f;
	bIsAttackCool = false;
}
#pragma region Init

void AMonster::InitAttackedInfo()
{
	AttackedInfo.bIsUseMana = false;
	AttackedInfo.Mana = 0.0f;
	AttackedInfo.AttributeArmor = 100.0f;
}
void AMonster::InitEffect()
{
	HitEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitEffect"));
	GroggyEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GroggyEffect"));

	HitEffectComponent->SetupAttachment(GetMesh());
	GroggyEffectComponent->SetupAttachment(RootComponent);

	HitEffectComponent->bAutoActivate = false;
	GroggyEffectComponent->bAutoActivate = false;

	MonsterEffect.HitEffectRotation = FRotator(0.0f, 0.0f, 0.0f);
	MonsterEffect.HitEffectScale = FVector(1.0f, 1.0f, 1.0f);

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
	return MonsterInfo.M_Sight_Angle;
}
float AMonster::GetViewRange() const
{
	return MonsterInfo.M_Sight_Radius;
}
float AMonster::GetViewHeight() const
{
	return MonsterInfo.M_Sight_Height;
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
	return MonsterInfo.Chain_Detect_Radius;
}
float AMonster::GetHp() const
{
	return MonsterInfo.M_HP;
}
FVector AMonster::GetLocation() const
{
	return GetActorLocation() + FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
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

float AMonster::GetPatrolArea() const
{
	return MonsterInfo.PatrolArea;
}
float AMonster::GetMaxFollowTime() const
{
	return MonsterInfo.M_MaxFollowTime;
}
int AMonster::GetMaxAttacked() const
{
	return MonsterInfo.M_MaxAttacked;
}
int AMonster::GetMonsterAtkType() const
{
	return MonsterInfo.M_Atk_Type;
}
float AMonster::GetAttackCoolTime() const
{
	return MonsterInfo.M_Skill_Cool;
}
UMonsterAnimInstance* AMonster::GetMonsterAnimInstance() const
{
	return MonsterAnimInstance;
}
bool AMonster::GetIsAttackCool() const
{
	return bIsAttackCool;
}
float AMonster::GetAttackPercent() const
{
	return MonsterInfo.M_AttackPercent;
}
int AMonster::GetPlayerEnergy() const
{
	return 0;
}

EMonsterState AMonster::GetState() const
{
	return CurState;
}

float AMonster::GetSupportPatrolRadius() const
{
	return 800.0f;
}

float AMonster::GetAttackedTime() const
{
	return MonsterInfo.M_Attacked_Time;
}

EAttributeKeyword AMonster::GetAttribute() const
{
	return MonsterInfo.MonsterAttribute;
}

float AMonster::GetAttackTraceInterver() const
{
	return MonsterInfo.M_AttackTraceInterver;
}

FNormalMonsterInfo AMonster::GetMonsterInfo() const
{
	return MonsterInfo;
}

bool AMonster::GetIsAttacking() const
{
	return bIsAttacking;
}

void AMonster::SetCaptin()
{
	bIsCaptin = true;
}

float AMonster::GetMinSupportWalkTime() const
{
	return MonsterInfo.MinSupportWalkTime;
}

float AMonster::GetMaxSupportWalkTime() const
{
	return MonsterInfo.MaxSupportWalkTime;
}

float AMonster::GetAtkAngle() const
{
	return MonsterInfo.Attack1Range.M_Atk_Angle;
}
float AMonster::GetAtkRange() const
{
	return MonsterInfo.Attack1Range.M_Atk_Radius;
}
float AMonster::GetAtkHeight() const
{
	return MonsterInfo.Attack1Range.M_Atk_Angle;
}
bool AMonster::GetIsMonsterShieldActive() const
{
	return MonsterShield->GetShieldAcitve();
}
float AMonster::GetSkillRadius() const
{
	return MonsterInfo.M_Skill_Radius;
}
float AMonster::GetToPlayerDistance()
{
	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	float distance = GetDistanceTo(Instance->GetPlayer());
	return distance;
}
float AMonster::GetMoveSpeed() const
{
	return GetCharacterMovement()->MaxWalkSpeed;
}
float AMonster::GetBattleRange() const
{
	return MonsterInfo.Battle_Radius;
}
float AMonster::GetSupportRange() const
{
	return MonsterInfo.Support_Radius;
}
float AMonster::GetRotateRate()
{
	return MonsterInfo.RotationRate;
}
FAttackRange AMonster::GetAttack1Range() const
{
	return MonsterInfo.Attack1Range;
}
FAttackRange AMonster::GetAttack2Range() const
{
	return MonsterInfo.Attack2Range;
}
FAttackRange AMonster::GetAttack3Range() const
{
	return MonsterInfo.Attack3Range;
}

FAttackRange AMonster::GetAttack4Range() const
{
	return MonsterInfo.Attack4Range;
}

void AMonster::SetIsAttackCool(bool Cool)
{


	if (CurState == EMonsterState::Support)
	{
		AttackCoolTime = MonsterInfo.S_Attack_Time;
	}
	else {
		AttackCoolTime = MonsterInfo.M_Skill_Cool;
	}
	
	if (Cool == true)
	{
		AttackCoolTimer = 0.0f;
	}
	bIsAttackCool = Cool;
}

void AMonster::SetMonsterContorller(AMonsterController* Object)
{
	if (MonsterController == nullptr)
		MonsterController = Object;
}

void AMonster::SetDpsCheck(bool state)
{
	if (!bIsDpsCheck) {
		bIsDpsCheck = state;
		DpsTimer = 0.0f;
		DpsDamage = 0.0f;
	}
	else {
		bIsDpsCheck = state;
		DpsTimer = 0.0f;

		if (DpsDamage >= MonsterInfo.M_FSM_DPS)
		{
			MonsterAIController->SetBackStepKey(true);
		}
	}
}


void AMonster::InitWalkSpeed()
{
	MonsterInfo.DefaultMoveSpeed = MonsterInfo.M_MoveSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
}

int AMonster::GetCurStackCount()
{
	return MonsterInfo.CurStackCount;
}
void AMonster::AddStackCount(int Count)
{
	if (MonsterInfo.MaxStackCount > 0) {


		if (!MonsterInfo.bIsStackCheck)
		{
			auto Instance = Cast<USTGameInstance>(GetGameInstance());
			if (Instance != nullptr)Instance->InsertStackMonster(this);
		}

		MonsterInfo.StackCheckTimer = 0.0f;
		MonsterInfo.bIsStackCheck = true;

		if (MonsterInfo.CurStackCount < MonsterInfo.MaxStackCount) {
			MonsterInfo.CurStackCount += Count;


			if (MonsterInfo.CurStackCount >= MonsterInfo.MaxStackCount)MonsterInfo.CurStackCount = MonsterInfo.MaxStackCount;



			OnStackCountEvent();

			int Break_1 = MonsterInfo.MaxStackCount * 0.3;
			int Break_2 = MonsterInfo.MaxStackCount * 0.6;
			int Break_3 = MonsterInfo.MaxStackCount * 0.9;

			//if (MonsterInfo.CurStackCount >= MonsterInfo.MaxStackCount)
			//{
			//	MonsterInfo.OverStackCount = MonsterInfo.CurStackCount - MonsterInfo.MaxStackCount;
			//	MonsterInfo.CurStackCount = MonsterInfo.MaxStackCount;
			//	StackExplode();
			//}
			//else if (MonsterInfo.CurStackCount >= Break_3)
			//{
			//	MonsterShield->CalcStackDamageToShield(Break_3);

			//}
			//else if (MonsterInfo.CurStackCount >= Break_2)
			//{
			//	MonsterShield->CalcStackDamageToShield(Break_2);
			//}
			//else if (MonsterInfo.CurStackCount >= Break_1)
			//{
			//	MonsterShield->CalcStackDamageToShield(Break_1);

			//}


			if (MonsterInfo.CurStackCount >= Break_3)
			{
				MonsterShield->CalcStackDamageToShield(Break_3);

			}
			else if (MonsterInfo.CurStackCount >= Break_2)
			{
				MonsterShield->CalcStackDamageToShield(Break_2);
			}
			else if (MonsterInfo.CurStackCount >= Break_1)
			{
				MonsterShield->CalcStackDamageToShield(Break_1);

			}
		}
	}
}

void AMonster::StackExplode()
{

	if (MonsterInfo.CurStackCount >= MonsterInfo.MaxStackCount)
	{

		ExplodeStackEvent();
		SoundInstance->PlayStackExplosionSound(this->GetTransform());

	}
	else {

		InitStackCount();
		auto Instance = Cast<USTGameInstance>(GetGameInstance());
		if (Instance != nullptr)Instance->DeleteStackMonster(this);
	}
}

void AMonster::MaxStackExplode()
{

	if (GetIsMonsterShieldActive() && !IsNonShield) {
		MonsterShield->CalcDurability(-1.0f);
		OnBarrierChanged.Broadcast();

		//	MonsterInfo.CurStackCount = MonsterInfo.OverStackCount;
		  //MonsterInfo.OverStackCount = 0;
		MonsterInfo.bIsStackCheck = false;
		MonsterInfo.StackCheckTimer = 0.0f;

		/*	if (MonsterInfo.CurStackCount == 0)
			{
				InitStackCount();
			}*/

		if (!GetIsMonsterShieldActive() || !IsNonShield)
		{
			ShieldDestroyed();
			SoundInstance->PlayShieldDestroySound(GetCapsuleComponent()->GetComponentTransform());
		}

	}
	else {

	/*		if(GetIsMonsterShieldActive() && !IsNonShield)
				CalcHp(MonsterInfo.StackDamage);
			else*/
				CalcHp(GetMonsterInfo().StackDamage + GetMonsterInfo().StackDamage * 0.2f);
			//	MonsterAIController->Groggy();
			MonsterInfo.CurStackCount = MonsterInfo.OverStackCount;
			MonsterInfo.OverStackCount = 0;
			MonsterInfo.StackCheckTimer = 0.0f;

			/*	if (MonsterInfo.CurStackCount == 0)
				{
					InitStackCount();
				}*/

		
	
		
	}
	InitStackCount();

	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	if (Instance != nullptr)Instance->DeleteStackMonster(this);

}

void AMonster::InitStackCount()
{

	MonsterInfo.StackCheckTimer = 0.0f;
	MonsterInfo.bIsStackCheck = false;
	MonsterInfo.CurStackCount =0;
	MonsterInfo.OverStackCount = 0;
	OnStackCountEvent();

}

float AMonster::CalcStackDamage(int StackCount)
{

	float Count = (float)StackCount;
	float Percent= 60.0f / MonsterInfo.MaxStackCount - 1.0f;
	Percent *= 0.01f;
	Percent = 0.4f+((Count - 1.0f)*Percent);

	return Percent * MonsterInfo.StackDamage;
}

void AMonster::MoveToPlayer(float DeltaSeconds)
{

		SetActorLocation(GetActorLocation() + (GetActorForwardVector() * GetMoveSpeed() * DeltaSeconds),true);

		auto Instance = Cast<USTGameInstance>(GetGameInstance());

		//2개의 벡터를 a to b 로 회전 하는 행렬 구하기
		FVector ForwardVec = GetActorForwardVector();
		ForwardVec.Normalize();

		FVector PlayerVec = Instance->GetPlayer()->GetActorLocation() - GetActorLocation();

		PlayerVec.Normalize();

		FQuat RotationQuat = Math::VectorA2BRotation(ForwardVec, PlayerVec);

		RotationQuat *= MonsterInfo.RotationRate;

		RotationQuat.X = 0.0f;
		RotationQuat.Y = 0.0f;
		RotationQuat.W = 1.0f;
		AddActorWorldRotation(RotationQuat);
}

void AMonster::RotationPlayer(float DeltaSeconds)
{
	auto Instance = Cast<USTGameInstance>(GetGameInstance());

	//2개의 벡터를 a to b 로 회전 하는 행렬 구하기
	FVector ForwardVec = GetActorForwardVector();
	ForwardVec.Normalize();

	FVector PlayerVec = Instance->GetPlayer()->GetActorLocation() - GetActorLocation();

	PlayerVec.Normalize();

	FQuat RotationQuat = Math::VectorA2BRotation(ForwardVec, PlayerVec);

	RotationQuat *= MonsterInfo.RotationRate;

	RotationQuat.X = 0.0f;
	RotationQuat.Y = 0.0f;
	RotationQuat.W = 1.0f;
	AddActorWorldRotation(RotationQuat);
}

void AMonster::Attack()
{
	MonsterAIController->Attack();
}

void AMonster::SupportAttack()
{
}


AMonsterAIController* AMonster::GetAIController() const
{
	return MonsterAIController;
}
float AMonster::GetHpRatio()
{
	return MonsterInfo.M_HP < KINDA_SMALL_NUMBER ? 0.0f : MonsterInfo.M_HP / MonsterInfo.M_Max_HP;
}
float AMonster::GetDefRatio()
{
  return MonsterShield->GetDurabilityRatio();
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
	HitEffectComponent->SetTemplate(MonsterEffect.HitEffect);
	GroggyEffectComponent->SetTemplate(MonsterEffect.GroggyEffect);

	HitEffectComponent->SetRelativeRotation(MonsterEffect.HitEffectRotation);
	HitEffectComponent->SetRelativeScale3D(MonsterEffect.HitEffectScale);


	GroggyEffectComponent->SetRelativeRotation(MonsterEffect.GroggyEffectRotation);
	GroggyEffectComponent->SetRelativeScale3D(MonsterEffect.GroggyEffectScale);

}



#pragma region Calc


float AMonster::CalcNormalAttackDamage(float Damage)
{
	if (Cast<AMorbit>(this))
	{
		auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
		auto Player = GameInstance->GetPlayer();

		bool IsKnockback = Player->IreneState->IsKnockBackState();

		if ((GetIsMonsterShieldActive() == false || IsNonShield) && !MonsterAIController->GetIsGorggy()) {
			if (bIsDodgeOn)
			{
				PerfectDodgeOff();
			}
		}

		//MonsterAIController->Attacked(AttackedInfo.AttackedDirection, AttackedInfo.AttackedPower, AttackedInfo.bIsUseMana, IsKnockback);

	}
	if (Cast<ABellarus>(this)) {

		auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
		auto Player = GameInstance->GetPlayer();

		bool IsKnockback = Player->IreneState->IsKnockBackState();
		if ((GetIsMonsterShieldActive() == false || IsNonShield) && !MonsterAIController->GetIsGorggy()) {
			if (bIsDodgeOn)
			{
				PerfectDodgeOff();
			}
		}

	}
	if (Cast<ABellyfish>(this)) {

		auto GameInstance = Cast<USTGameInstance>(GetGameInstance());
		auto Player = GameInstance->GetPlayer();

		bool IsKnockback = Player->IreneState->IsKnockBackState();

		if ((GetIsMonsterShieldActive() == false || IsNonShield) && !MonsterAIController->GetIsGorggy()) {
			if (bIsDodgeOn)
			{
				PerfectDodgeOff();
			}
		}

	}
	if (Cast<ABouldelith>(this))
	{
		//방어력 게이지 업데이트
		OnBarrierChanged.Broadcast();

		auto BdAI = Cast<ABdAIController>(MonsterAIController);
		if (BdAI->GetBlackboardComponent()->GetValueAsBool(BdAI->B_WalkRightKey) 
			|| BdAI->GetBlackboardComponent()->GetValueAsBool(BdAI->B_WalkLeftKey))
		{
			if(bIsDpsCheck==false)
			SetDpsCheck(true);
		}

		if ((GetIsMonsterShieldActive() == false || IsNonShield) && !MonsterAIController->GetIsGorggy()) {
			if (bIsDodgeOn)
			{
				PerfectDodgeOff();
			}
		}

		//if (AttackedInfo.AttackedPower != EAttackedPower::Halved && AttackedInfo.bIsUseMana)
		//	MonsterAIController->Attacked();


	}

	MonsterAIController->StopMovement();

	float TotalDamage = 0;

	if (GetIsMonsterShieldActive() && !IsNonShield)
	{
		switch (MonsterShield->GetCurShieldState())
		{
		case 0:
			TotalDamage = Damage * 0.3;
			break;
		case 1:
			TotalDamage = Damage * 0.5;
			break;
		case 2:
			TotalDamage = Damage * 0.7;
			break;
		case 3:
			TotalDamage = Damage * 0.9;
			break;
		default:
			break;
		}
	}
	else {
		TotalDamage = Damage;
	}


	return TotalDamage;
}



void AMonster::CalcHp(float Damage)
{
		Damage = FMath::Abs(Damage);

		MonsterInfo.M_HP -= Damage;
		if (bIsDpsCheck)
		{
			DpsDamage += Damage;
		}

		if (bTestMode)
			STARRYLOG(Log, TEXT("Monster Hp : %f"), MonsterInfo.M_HP);

		/*bShowUI = true;
		ShowUITimer = 0.0f;
		MonsterWidget->SetHiddenInGame(false);*/

		OnHpChanged.Broadcast();
		if (MonsterInfo.M_HP <= 0.0f)
		{
			OnHpChanged.Broadcast();
			if (Cast<ABellarus>(this)&& Cast<ABellarusAIController>(GetAIController())->GetSecondPhaseKey()==false)
			{
				auto Bellarus = Cast<ABellarus>(this);
				STARRYLOG(Log, TEXT("!!BellarusSecondPhase!!"));
				Cast<ABellarusAIController>(GetAIController())->SetSecondPhase(true);
				Bellarus->SetSecondPhase();
				InitStackCount();
				auto Instance = Cast<USTGameInstance>(GetGameInstance());
				if (Instance != nullptr)Instance->DeleteStackMonster(this);
				OnHpChanged.Broadcast();
				return;
			}
			else {

				GetCapsuleComponent()->SetCollisionProfileName("NoCollision");


				if (MonsterController != nullptr)
				{
					if (CurState == EMonsterState::Support)
					{
						MonsterController->SupportMonsterDelete(this);
					}
					else if (CurState == EMonsterState::Battle)
					{
						MonsterController->BattleMonsterDelete();
					}
				}


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

				if (bIsGroupTriggerEnemy)
				{
					auto instnace = Cast<USTGameInstance>(GetGameInstance());
					if (instnace != nullptr)
						instnace->SubEnemyCount(GetRank());
				}


				if (bIsDodgeOn)
				{
					PerfectDodgeOff();
				}
				if (Cast<ABellyfish>(this))
				{
					auto Bellyfish = Cast<ABellyfish>(this);
					Bellyfish->DestroyMagicAttack();
				}
	

				InitStackCount();
				auto Instance = Cast<USTGameInstance>(GetGameInstance());
				if (Instance != nullptr)Instance->DeleteStackMonster(this);
				MonsterDeadEvent();
				bIsDead = true;
				SetActive();
				MonsterAIController->Death();
				PlayDeathAnim();



				return;
			}
		}
}
#pragma endregion
FMonsterDataTable* AMonster::GetMontserData(int32 num)
{
	return MonsterDataTable->FindRow<FMonsterDataTable>(FName(*(FString::FormatAsNumber(num))), FString(""));
}
FMonsterSkillDataTable* AMonster::GetMontserSkillData(int32 num)
{
	return MonsterSkillDataTable->FindRow<FMonsterSkillDataTable>(FName(*(FString::FormatAsNumber(num))), FString(""));
}

void AMonster::ShieldDestroyed()
{
	ShieldDestroyEvent();
	DropShieldPoint();
	OnBarrierChanged.Broadcast();
	MonsterAIController->SetShieldKey(false);

	PlayGroggyAnim();
	MonsterAIController->Groggy();
	bIsDodgeTime = false;
	PerfectDodgeOff();
	
	if (Cast<ABellarus>(this))
	{
		auto Bellarus = Cast<ABellarus>(this);
		Bellarus->ShieldRegening();
	}
	
}

bool AMonster::CheckPlayerIsBehindMonster()
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());

	FVector TargetDir = STGameInstance->GetPlayer()->GetActorLocation() - GetActorLocation();
	TargetDir = TargetDir.GetSafeNormal();

	//정면으로 향하는 벡터와 플레이어로 향하는 벡터의 내적을 통해 각도를 구할 수 있다. 결과값은 Radian
	float Radian = FVector::DotProduct(GetActorForwardVector(), TargetDir);
	//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
	float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

	if (TargetAngle <= (MonsterInfo.M_Sight_Angle * 0.5f))
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
		FCollisionShape::MakeSphere(DetectRange),
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
		//StackWidget->SetHiddenInGame(true);
		HitEffectComponent->SetActive(false);
		GroggyEffectComponent->SetActive(false);
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
void AMonster::StackWidgetOn()
{
	StackWidget->SetVisibility(true);
}
void AMonster::StackWidgetOff()
{
	StackWidget->SetVisibility(false);
}
void AMonster::SetSpawnEnemy()
{
	bIsSpawnEnemy = true;
	SetBattleState();
}
EEnemyRank AMonster::GetRank()
{
	return MonsterInfo.Monster_Rank;
}

void AMonster::PrintHitEffect(FVector AttackedPosition, AActor* Actor)
{
	float Distance = FVector::Distance(GetLocation(), AttackedPosition);
	FVector CompToMonsterDir = GetLocation() - AttackedPosition;
	CompToMonsterDir.Normalize();
	FVector EffectPosition = AttackedPosition + (CompToMonsterDir * (Distance / 2.0f));

	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	

	HitEffectComponent->SetTemplate(MonsterEffect.HitEffect);

	HitEffectComponent->SetWorldLocation(EffectPosition);

	HitEffectComponent->SetActive(true);
	HitEffectComponent->ForceReset();
}
void AMonster::Attacked()
{

	STARRYLOG_S(Error);
	AttackCoolTimer = 0.0f;
	SetIsAttackCool(false);
	bIsAttacking = false;
	MonsterAIController->StopMovement();
	MonsterAIController->Attacked();
	MonsterAIController->OffAttack(-1);
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
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.M_MoveSpeed;
	
}
void AMonster::PlayBattleWalkAnim()
{
	MonsterAnimInstance->PlayBattleWalkMontage();
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.BattleWalkMoveSpeed;
}
void AMonster::PlayGroggyAnim()
{
	MonsterAnimInstance->PlayGroggyMontage();
}
void AMonster::PlayDeathAnim()
{
	MonsterAnimInstance->PlayDeathMontage();

}

void AMonster::SetGroup()
{
	bIsGroupTriggerEnemy = true;

	//GetCapsuleComponent()->SetCollisionProfileName("Enemy");
	SetStatue(false);
}

void AMonster::SetStatue(bool state)
{
	
	if (Cast<ABouldelith>(this))
	{
		GetAIController()->SetStatueKey(state);
		auto bouldelith = Cast<ABouldelith>(this);
		bouldelith->SetStatueState(state);
		
	}
	else {
		GetAIController()->SetStatueKey(state);
	}

	if (state)
	{
		bIsMoveToFront = true;
		GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
		ShieldCollision->SetCollisionProfileName("NoCollision");
	}
	else {
		GetCapsuleComponent()->SetCollisionProfileName("Enemy");
		ShieldCollision->SetCollisionProfileName("Shield");
		bIsMoveToFront = false;
		PlayBattleWalkAnim();
	}
}


void AMonster::InitPerfectDodgeNotify()
{
	DodgeTimeOn.AddUObject(this, &AMonster::IsDodgeTimeOn);
	DodgeTimeOff.AddUObject(this, &AMonster::IsDodgeTimeOff);
}
void AMonster::SetBattleState()
{
	PointOn();
	MonsterAIController->SetPlayer();
	MonsterAIController->SetIsInSupportRange(false);
	PlayIdleAnim();
	MonsterAIController->SetBattleState(true);
	MonsterAIController->SetNormalState(false);
	MonsterAIController->SetSupportState(false);

	CurState = EMonsterState::Battle;

	if (GetIsMonsterShieldActive())
		MonsterAIController->SetShieldKey(true);
	else {
		MonsterAIController->SetShieldKey(false);
	}
	SetBattleEvent();

}
void AMonster::SetNormalState()
{
	PointOff();
	MonsterAIController->SetBattleState(false);
	MonsterAIController->SetNormalState(true);
	MonsterAIController->SetSupportState(false);

	if (MonsterInfo.M_Atk_Type == 1) {
		MonsterAIController->SetTraceKey(true);
	}

	CurState = EMonsterState::Normal;
}
void AMonster::SetSupportState()
{
	MonsterAIController->SetIsInBattleRange(false);
	PlayIdleAnim();
	PointOff();
	MonsterAIController->SetPlayer();
	MonsterAIController->SetBattleState(false);
	MonsterAIController->SetNormalState(false);
	MonsterAIController->SetSupportState(true);
	


	CurState = EMonsterState::Support;
	SetSupportEvent();
}

void AMonster::DropShieldPoint()
{
	USTGameInstance* Instance;
	do 
	{
		Instance = Cast<USTGameInstance>(GetGameInstance());
	} while (Instance==nullptr);


	TArray<AShieldPoint*> Souls;
	for (int i = 0; i < MonsterInfo.Spirit_Soul; i++)
	{
		Souls.Add(GetWorld()->SpawnActor<AShieldPoint>(ShieldPointClass, GetActorLocation(), FRotator::ZeroRotator));
	}
	for (int i = 0; i < MonsterInfo.Spirit_Soul; i++)
	{
		auto RanX = FMath::FRandRange(-1.0f, 1.0f);
		auto RanY = FMath::FRandRange(-1.0f, 1.0f);

		Souls[i]->SetValue(Instance->GetPlayer()->IreneAttack->GetNameAtWeaponSoulDataTable(),FVector(RanX, RanY,0.3f));
		
	}
}

void AMonster::DeathCheck()
{

	if (bIsDead)
	{
		STARRYLOG_S(Error);
		PlayDeathAnim();

	}
}


	

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	SetEffect();

	MonsterInfo.DefaultMoveSpeed = MonsterInfo.M_MoveSpeed;
	MonsterInfo.DefaultBattleWalkMoveSpeed = MonsterInfo.BattleWalkMoveSpeed;

	MonsterInfo.M_HP = MonsterInfo.M_Max_HP;



	


	if (GetActorScale3D().X > 1.0f)
	{
		SoundInstance->GetHitSound()->SetVolume(1.5f);

	}
	else {
		SoundInstance->GetHitSound()->SetVolume(1.0f);

	}

	auto HPBar = Cast<UMonsterWidget>(MonsterWidget->GetWidget());
	HPBar->BindMonster(this);

	StackWidgetOff();
	MonsterWidget->SetVisibility(false);
	OnSpawnEffectEvent();

	InitPerfectDodgeNotify();



	MonsterShield->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, ShieldSocketName);




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
	MonsterShield->InitShield(IsNonShield,ShieldCollision, ShiledEffectComponent, ShiledCrackEffectComponent, ShiledHitEffectComponent);
	MonsterAIController = Cast<AMonsterAIController>(GetController());
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

	StackWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
	WidgetPoint->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
	if (bDeadWait)
	{
	
		DeadWaitTimer += DeltaTime;
		if (DeadWaitTimer >= MonsterInfo.DeadWaitTime)
		{
			SetActorTickEnabled(false);
			StackWidget->SetHiddenInGame(true);
			if (Cast<ABellarus>(this)) {
				auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
				if (STGameInstance != nullptr)
				{
					STGameInstance->GetPlayer()->GameClearEvent();
				}

			}
			Destroy();
			
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
			bShowUI = false;
			//StackWidgetOff();
		}
	}
	else
	{
		return;
	}


	if (bIsAttacked) // 0.2
	{
		KnockBackTime += DeltaTime;
	    KnocbackLocation = GetActorLocation() + (KnockBackDir * (MonsterInfo.KnockBackPower * (0.15f - KnockBackTime)));
		SetActorLocation(KnocbackLocation,true);

		if (KnockBackTime > 0.15f)
		{
			KnockBackTime = 0.0f;
			bIsAttacked = false;
		}
	}

	if (bIsAttackedCool)
	{
		AttackedCoolTimer += DeltaTime;
		if (AttackCoolTimer >= AttackedCoolTime)
		{
			AttackCoolTimer = 0.0f;
			bIsAttackedCool = false;
		}
	}

	if (bShowUI)
	{
		ShowUITimer += DeltaTime;

		if (ShowUITimer >= ShowUITime)
		{
			ShowUITimer = 0.0f;
			MonsterWidget->SetVisibility(false);
			bShowUI = false;
		}
	}

	if (bIsAttackCool)
	{
		AttackCoolTimer+= DeltaTime;
		if (AttackCoolTimer >= AttackCoolTime)
		{
			
			AttackCoolTimer = 0.0f;
			SetIsAttackCool(false);
			GetAIController()->SetAttackCoolKey(false);
		}
	}




	if (bIsDpsCheck)
	{
		DpsTimer += DeltaTime;
		if (DpsTimer >= DpsTime)
		{
			SetDpsCheck(false);
		}
	}

	if (MonsterInfo.bIsStackCheck)
	{
		MonsterInfo.StackCheckTimer += DeltaTime;
		if (MonsterInfo.StackCheckTimer >= MonsterInfo.StackCheckTime)
		{
			InitStackCount();
			auto Instance = Cast<USTGameInstance>(GetGameInstance());
			if (Instance != nullptr)Instance->DeleteStackMonster(this);
			return;
		}

		auto Instance = Cast<USTGameInstance>(GetGameInstance());
		if (Instance != nullptr)
		{
			float distance = GetDistanceTo(Instance->GetPlayer());
			if (distance >= MonsterInfo.StackEnableDistance)
			{
				InitStackCount();
				return;
			}
		}
	}



	if (GetIsMonsterShieldActive() && !IsNonShield)
	{
		auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
		float Distance = GetDistanceTo(STGameInstance->GetPlayer());
		MonsterShield->SetOpacity(Distance);
	}

	if (bIsMoveToFront) {
		if (CurState == EMonsterState::Battle)
		{
			auto Instance = Cast<USTGameInstance>(GetGameInstance());
			if (GetDistanceTo(Instance->GetPlayer()) > GetBattleRange() &&
				!bIsAttacking && !GetAIController()->GetIsGorggy())
			{
				GetAIController()->SetIsInBattleRange(false);
			}
		}

		if (CurState == EMonsterState::Support)
		{
			auto Instance = Cast<USTGameInstance>(GetGameInstance());
			if (GetDistanceTo(Instance->GetPlayer()) < GetBattleRange() &&
				!bIsAttacking && !GetAIController()->GetIsGorggy()
				&& GetAIController()->GetIsInSupportRange() == true)
			{

				bool IsMove = SetActorLocation(GetActorLocation() + (GetActorForwardVector().RotateAngleAxis(180.0f, FVector::UpVector) * GetMoveSpeed() * DeltaTime), true);
				if (IsMove) {
					GetAIController()->SetIsInSupportRange(false);
				}
			}
			else if (GetDistanceTo(Instance->GetPlayer()) > GetSupportRange() &&
				!bIsAttacking && !GetAIController()->GetIsGorggy()
				&& GetAIController()->GetIsInSupportRange() == true)
			{
				GetAIController()->SetIsInSupportRange(false);
			}
		}

	}
	else{
		FrontMoveTimer += DeltaTime;
		if (FrontMoveTimer < FrontMoveTime) {
			SetActorLocation(GetActorLocation() + (GetActorForwardVector() * GetMoveSpeed() * DeltaTime), true);
		}
		else {
			bIsMoveToFront = true;
			if (bIsCaptin&&MonsterController!=nullptr) {
				MonsterController->SetCloseMonster();
			}

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

			if (this->MonsterInfo.Monster_Rank != EEnemyRank::e_Raid)
			{
				if (bShowUI)
				{
					ShowUITimer = 0.0f;
				}
				else {
					bShowUI = true;
					ShowUITimer = 0.0f;
					MonsterWidget->SetVisibility(true);
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

						if (Player->bIsSpiritStance == true) {
							HitStopEvent();
							Player->HitStopEvent();
						}
					}
				}
			}

			bIsAttacked = true;



			//넉백
			KnockBackDir = -(Player->GetActorLocation() - GetActorLocation());
			KnockBackDir.Normalize();
			KnockBackDir.Z = 0.0f;

			//

			auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
			if (STGameInstance->GetAttributeEffectMonster() == nullptr)
			{
				STGameInstance->SetAttributeEffectMonster(this);

				if(Cast<ABellyfish>(this))
				SoundInstance->PlayHitSound(SoundTransform, 0.0f);
				else if (Cast<ABouldelith>(this))
				SoundInstance->PlayHitSound(SoundTransform, 1.0f);
				else if(Cast<ABellarus>(this))
				SoundInstance->PlayHitSound(SoundTransform, 2.0f);
				else SoundInstance->PlayHitSound(SoundTransform, 0.0f);
			}


			//몬스터인지 아닌지
			if (MonsterController != nullptr && CurState == EMonsterState::Battle) {
				MonsterController->SupportMonsterAttack();
			}

				AttacekdTeleportTimer = 0.0f;
				if (MonsterController != nullptr) {
					if (CurState == EMonsterState::Normal) {
						MonsterController->SetBattleMonster(this);
					}
				}
				else {
					if(CurState!= EMonsterState::Battle)
					SetBattleState();
				}


								
				if (GetIsMonsterShieldActive()&& IsNonShield==false){

					MonsterShield->CalcDurability(DamageAmount);
				    OnBarrierChanged.Broadcast();
					CalcHp(CalcNormalAttackDamage(DamageAmount));	
					if (MonsterShield->GetShieldAcitve()&&IsNonShield==false)
					{
						SoundInstance->PlayShieldHitSound(GetCapsuleComponent()->GetComponentTransform());
						Player->PlayerKnockBack(Player->GetActorLocation() - GetActorLocation(), MonsterShield->GetKnockBackDistance());
					}
					else {

						if (!IsNonShield) {
							ShieldDestroyed();
							SoundInstance->PlayShieldDestroySound(GetCapsuleComponent()->GetComponentTransform());
						}
					}
				}
				else {
					CalcHp(CalcNormalAttackDamage(DamageAmount));		
			}
			//몬스터가 아니면
			
			InitAttackedInfo();

			if (MonsterAIController->GetIsAttacking() == false && (GetIsMonsterShieldActive() == false||IsNonShield) && !MonsterAIController->GetIsGorggy()) {
				if (bIsDodgeOn)
				{
					PerfectDodgeOff();
				}

				if (!bIsAttackCool) {
					STARRYLOG_S(Error);
					Attacked();
					bIsAttackCool = true;
				}
			}


	
			return FinalDamage;
		}
	}

	if (Cast<ALabMagic>(DamageCauser))
	{
		CalcHp(1);
		Attacked();
	}
	return FinalDamage;
}

void AMonster::PerfectDodgeOff()
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (STGameInstance != nullptr) {
		STGameInstance->GetPlayer()->IreneAttack->SetIsPerfectDodge(false);
		STGameInstance->GetPlayer()->IreneAttack->SetIsPerfectDodgeMonster(this);
	}
	bIsDodgeOn = false;
}

void AMonster::PerfectDodgeOn()
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (STGameInstance != nullptr) {
		STGameInstance->GetPlayer()->IreneAttack->SetIsPerfectDodge(true);
		STGameInstance->GetPlayer()->IreneAttack->SetIsPerfectDodgeMonster(this);
	}


	bIsDodgeOn = true;
}
void AMonster::InitAttack1Data()
{

	FMonsterSkillDataTable* NewData = GetMontserSkillData(MonsterInfo.M_Skill_Type_01);

	MonsterInfo.M_Skill_Range = NewData->M_Skill_Range;
	MonsterInfo.M_Skill_Radius = NewData->M_Skill_Radius;

	MonsterInfo.M_Skill_Atk = NewData->M_Skill_Atk;
	MonsterInfo.M_Skill_Time = NewData->M_Skill_Time;
	MonsterInfo.M_Skill_Set_Time = NewData->M_Skill_Set_Time;
	MonsterInfo.M_Skill_Cool = NewData->M_Skill_Cool;



}
void AMonster::InitAttack2Data()
{
	FMonsterSkillDataTable* NewData = GetMontserSkillData(MonsterInfo.M_Skill_Type_02);

	MonsterInfo.M_Skill_Range = NewData->M_Skill_Range;
	MonsterInfo.M_Skill_Radius = NewData->M_Skill_Radius;
	MonsterInfo.M_Skill_Atk = NewData->M_Skill_Atk;
	MonsterInfo.M_Skill_Time = NewData->M_Skill_Time;
	MonsterInfo.M_Skill_Set_Time = NewData->M_Skill_Set_Time;
	MonsterInfo.M_Skill_Cool = NewData->M_Skill_Cool;
}
void AMonster::InitAttack3Data()
{
	FMonsterSkillDataTable* NewData = GetMontserSkillData(MonsterInfo.M_Skill_Type_03);

	MonsterInfo.M_Skill_Range = NewData->M_Skill_Range;
	MonsterInfo.M_Skill_Radius = NewData->M_Skill_Radius;

	MonsterInfo.M_Skill_Atk = NewData->M_Skill_Atk;
	MonsterInfo.M_Skill_Time = NewData->M_Skill_Time;
	MonsterInfo.M_Skill_Set_Time = NewData->M_Skill_Set_Time;
	MonsterInfo.M_Skill_Cool = NewData->M_Skill_Cool;
}
void AMonster::InitAttack4Data()
{
	FMonsterSkillDataTable* NewData = GetMontserSkillData(MonsterInfo.M_Skill_Type_04);

	MonsterInfo.M_Skill_Range = NewData->M_Skill_Range;
	MonsterInfo.M_Skill_Radius = NewData->M_Skill_Radius;

	MonsterInfo.M_Skill_Atk = NewData->M_Skill_Atk;
	MonsterInfo.M_Skill_Time = NewData->M_Skill_Time;
	MonsterInfo.M_Skill_Set_Time = NewData->M_Skill_Set_Time;
	MonsterInfo.M_Skill_Cool = NewData->M_Skill_Cool;
}