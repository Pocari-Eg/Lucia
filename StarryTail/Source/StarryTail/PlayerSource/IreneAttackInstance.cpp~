// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneAttackInstance.h"
#include "IreneCharacter.h"
#include "IreneInputInstance.h"
#include "IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneUIManager.h"

#include "DrawDebugHelpers.h"
#include "../STGameInstance.h"
#include "Kismet/GameplayStatics.h"


UIreneAttackInstance::UIreneAttackInstance()
{
	// 데이터 테이블
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_AttackDataTable(TEXT("/Game/Math/BP_AttackDataTable.BP_AttackDataTable"));
	if (DT_AttackDataTable.Succeeded())
	{
		AttackDataTable = DT_AttackDataTable.Object;
	}
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_FormDataTable(TEXT("/Game/Math/BP_FormDataTable.BP_FormDataTable"));
	if (DT_FormDataTable.Succeeded())
	{
		FormDataTable = DT_FormDataTable.Object;
	}
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_FormTimeDataTable(TEXT("/Game/Math/BP_FormTimeDataTable.BP_FormTimeDataTable"));
	if (DT_FormTimeDataTable.Succeeded())
	{
		FormTimeDataTable = DT_FormTimeDataTable.Object;
	}
	IsConsecutiveFire = false;
}

void UIreneAttackInstance::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);
	InitMemberVariable();
}
void UIreneAttackInstance::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}
void UIreneAttackInstance::InitMemberVariable()
{
	TargetMonster = nullptr;
	//초기 속성
	Attribute = EAttributeKeyword::e_None;
	// FormGauge.Add(GetNameAtFormDataTable(FName("Fire"))->F_Gauge);
	// FormGauge.Add(GetNameAtFormDataTable(FName("Water"))->F_Gauge);
	// FormGauge.Add(GetNameAtFormDataTable(FName("Electric"))->F_Gauge);
	FormGauge.Add(GetNameAtFormTimeDataTable(FName("Fire_Form"))->F_Gauge/100);
	FormGauge.Add(GetNameAtFormTimeDataTable(FName("Water_Form"))->F_Gauge/100);
	FormGauge.Add(GetNameAtFormTimeDataTable(FName("Electric_Form"))->F_Gauge/100);
	
	bFollowTarget = false;
	FollowTargetAlpha = 0.0f;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;
	bFollowCameraTarget = false;
	FollowTargetCameraAlpha = 0.0f;
	CameraRot = FRotator::ZeroRotator;
	TargetCameraRot = FRotator::ZeroRotator;

	bUseMP = false;
	UseMP = 0.0f;
}
#pragma region Attack
float UIreneAttackInstance::GetATK()
{
	return Irene->IreneData.Strength;
}
EAttributeKeyword UIreneAttackInstance::GetAttribute()
{
	return Attribute;
}
int UIreneAttackInstance::GetAttackDirection()
{
	// 0 == Right to Left
	// 1 == Left to Right
	// 2 == Down to Up
	// 3 == Up to Down
	
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack1"))
	{
		return 0;
	}
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack2"))
	{
		return 1;
	}
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack3"))
	{
		return 0;
	}
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack4"))
	{
		return 1;
	}
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack5"))
	{
		return 3;
	}

	return 0;
}
void UIreneAttackInstance::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Irene->IreneData.IsAttacking = false;
	AttackEndComboState();
}
void UIreneAttackInstance::AttackStartComboState()
{
	Irene->IreneData.CanNextCombo = true;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = FMath::Clamp<int32>(Irene->IreneData.CurrentCombo + 1, 1, Irene->IreneData.MaxCombo);
}
void UIreneAttackInstance::AttackEndComboState()
{
	int FormType = 0;
	if(Attribute == EAttributeKeyword::e_Fire)
		FormType = 0;
	else if(Attribute == EAttributeKeyword::e_Water)
		FormType = 1;
	else if(Attribute == EAttributeKeyword::e_Thunder)
		FormType = 2;

	if(FormGauge[FormType] == 0)
		Irene->IreneInput->ChangeForm(EAttributeKeyword::e_None);
	
	Irene->Weapon->SetGenerateOverlapEvents(false);
	Irene->IreneInput->bUseLeftButton = false;
	Irene->IreneInput->bUseRightButton = false;
	bUseMP = false;
	UseMP = 0.0f;
	Irene->IreneData.CanNextCombo = false;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = 0;
	Irene->IreneUIManager->AttackSoundParameter = 0.0f;
	Irene->IreneUIManager->AttackSound->SetParameter("Attributes", Irene->IreneUIManager->AttackSoundParameter);
	if (Irene->IreneState->GetStateToString().Compare(FString("Dodge")) != 0)
		Irene->ActionEndChangeMoveState();
}

void UIreneAttackInstance::AttackCheck()
{
	if (Irene->IreneAnim->GetCurrentActiveMontage())
	{
		Irene->Weapon->SetGenerateOverlapEvents(true);
		Irene->IreneUIManager->AttackSound->SoundPlay2D();

		
		Irene->FindNearMonster();
	}
}
void UIreneAttackInstance::AttackStopCheck()
{
	Irene->IsTimeStopping = false;
	Irene->Weapon->SetGenerateOverlapEvents(false);
}
void UIreneAttackInstance::DoAttack()
{
	// 나중에 카메라 쉐이크 데이터 사용할 때 사용할 것(사용한다면...)
	//WorldController->ClientStartCameraShake(CameraShakeCurve);	

	// 몬스터 추적 초기화
	bFollowTarget = false;
	FollowTargetAlpha = 0;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;

	TArray<FHitResult> MonsterList;
	FCollisionQueryParams Params(NAME_None, false, Irene);
	bool bResult = GetWorld()->SweepMultiByChannel(
		MonsterList,
		Irene->GetActorLocation(),
		Irene->GetActorLocation() + Irene->GetActorForwardVector() * Irene->IreneData.AttackRange,
		FRotationMatrix::MakeFromZ(Irene->GetActorForwardVector() * Irene->IreneData.AttackRange).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(50.0f),
		Params);

	#if ENABLE_DRAW_DEBUG
		FVector TraceVec = Irene->GetActorForwardVector() * Irene->IreneData.AttackRange;
		FVector Center = Irene->GetActorLocation() + TraceVec * 0.5f;
		float HalfHeight = Irene->IreneData.AttackRange * 0.5f + Irene->IreneData.AttackRadius;
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		DrawDebugCapsule(GetWorld(),
			Center,
			HalfHeight,
			Irene->IreneData.AttackRadius,
			CapsuleRot,
			DrawColor,
			false,
			DebugLifeTime);
	#endif

	for (FHitResult Monster : MonsterList)
	{
		if (bResult)
		{
			if (Monster.Actor.IsValid())
			{
				FDamageEvent DamageEvent;

				auto Mob = Cast<AMonster>(Monster.Actor);
				if (Mob != nullptr)
				{
					Mob->SetAttackedInfo(bUseMP, UseMP, (EAttackedDirection)GetAttackDirection());
				}
				UGameplayStatics::ApplyDamage(Monster.Actor.Get(), Irene->IreneData.Strength, nullptr, Irene, nullptr);
			}
		}
	}

	// 마나 회복
	if (bUseMP == false && UseMP == 0.0f)
	{
		if(GetAttribute() == EAttributeKeyword::e_None)
		{
			const float FormGaugeValue = GetNameAtFormTimeDataTable(FName("Fire_Form"))->F_Gauge/100;
			for(int i=0;i<3;i++)
			{
				FormGauge[i] += FormGaugeValue/(GetNameAtFormTimeDataTable(FName("Fire_Form"))->Hit_Gauge_Re/100);
				if(FormGauge[i] > FormGaugeValue)
					FormGauge[i] = FormGaugeValue;
			}
			Irene->IreneAttack->FOnFireGaugeChange.Broadcast();
			Irene->IreneAttack->FOnWaterGaugeChange.Broadcast();
			Irene->IreneAttack->FOnElectricGaugeChange.Broadcast();
		}
		Irene->IreneUIManager->OnMpChanged.Broadcast();
	}

	//속성공격 기준 몬스터 할당해제
	if (bResult)
	{
		auto STGameInstance = Cast<USTGameInstance>(Irene->GetGameInstance());
		if (STGameInstance->GetAttributeEffectMonster() != nullptr)
		{
			STGameInstance->ResetAttributeEffectMonster();
		}
	}
}
void UIreneAttackInstance::RecoveryFormGauge(const float DeltaTime)
{
	if(Attribute == EAttributeKeyword::e_None)
	{
		for(int i=0;i<3;i++)
		{
			if(i==0 && !IsFireFull())
			{
				const float RecoveryPower = GetNameAtFormTimeDataTable(FName("Fire_Form"))->Recovery_Speed;
				FormGauge[0] += DeltaTime*RecoveryPower;
			}
			if(i==1 && !IsWaterFull())
			{
				const float RecoveryPower = GetNameAtFormTimeDataTable(FName("Water_Form"))->Recovery_Speed;
				FormGauge[1] += DeltaTime*RecoveryPower;
			}
			if(i==2 && !IsElectricFull())
			{
				const float RecoveryPower = GetNameAtFormTimeDataTable(FName("Electric_Form"))->Recovery_Speed;
				FormGauge[2] += DeltaTime*RecoveryPower;
			}
		}
	}
	if(Attribute != EAttributeKeyword::e_Fire&& !IsFireFull())
	{
		const float RecoveryPower = GetNameAtFormTimeDataTable(FName("Fire_Form"))->Recovery_Speed;
		FormGauge[0] += DeltaTime*RecoveryPower;
	}
	if(Attribute != EAttributeKeyword::e_Water&& !IsWaterFull())
	{
		const float RecoveryPower = GetNameAtFormTimeDataTable(FName("Water_Form"))->Recovery_Speed;
		FormGauge[1] += DeltaTime*RecoveryPower;
	}
	if(Attribute != EAttributeKeyword::e_Thunder&& !IsElectricFull())
	{
		const float RecoveryPower = GetNameAtFormTimeDataTable(FName("Electric_Form"))->Recovery_Speed;
		FormGauge[2] += DeltaTime*RecoveryPower;
	}
	FOnFireGaugeChange.Broadcast();
	FOnWaterGaugeChange.Broadcast();
	FOnElectricGaugeChange.Broadcast();
}
void UIreneAttackInstance::DecreaseFormGauge(const float DeltaTime)
{
	if(Attribute == EAttributeKeyword::e_Fire)
	{
		const float DecreasePower = GetNameAtFormTimeDataTable(FName("Fire_Form"))->Decrease_Speed;
		FormGauge[0] -= DeltaTime*DecreasePower;
	}
	if(Attribute == EAttributeKeyword::e_Water)
	{
		const float DecreasePower = GetNameAtFormTimeDataTable(FName("Water_Form"))->Decrease_Speed;
		FormGauge[1] -= DeltaTime*DecreasePower;
	}
	if(Attribute == EAttributeKeyword::e_Thunder)
	{
		const float DecreasePower = GetNameAtFormTimeDataTable(FName("Electric_Form"))->Decrease_Speed;
		FormGauge[2] -= DeltaTime*DecreasePower;
	}
	if(Attribute == EAttributeKeyword::e_Fire && FormGauge[0] <= 0)
	{
		FormGauge[0] = 0;
		Irene->IreneInput->FireKeywordReleased();
		//Irene->IreneInput->ChangeForm(EAttributeKeyword::e_None);
	}
	if(Attribute == EAttributeKeyword::e_Water && FormGauge[1] <= 0)
	{
		FormGauge[1] = 0;
		Irene->IreneInput->WaterKeywordReleased();
		Irene->IreneInput->ChangeForm(EAttributeKeyword::e_None);
	}
	if(Attribute == EAttributeKeyword::e_Thunder && FormGauge[2] <= 0)
	{
		FormGauge[2] = 0;
		Irene->IreneInput->ElectricKeywordReleased();
		Irene->IreneInput->ChangeForm(EAttributeKeyword::e_None);
	}
	FOnFireGaugeChange.Broadcast();
	FOnWaterGaugeChange.Broadcast();
	FOnElectricGaugeChange.Broadcast();
}
#pragma endregion Attack

#pragma region FireForm
void UIreneAttackInstance::FireRecoveryWaitStart()
{
	if(!Irene->FireRecoveryData.bIsRecovering&& !IsFireFull())
	GetWorld()->GetTimerManager().SetTimer(FireRecoveryWaitTimerHandle, this, &UIreneAttackInstance::FireRecoveryWaiting, 1.0f, true, 0.0f);
}
void UIreneAttackInstance::FireRecoveryWaiting()
{
	if (IsConsecutiveFire == false)
	{
		CurFireRecoverWaitTime++;
		if (CurFireRecoverWaitTime >= Irene->FireRecoveryData.Time)FireRecoveringStart();
	}
	else
	{
		CurFireRecoverWaitTime++;
		if (CurFireRecoverWaitTime >= Irene->FireRecoveryData.Fire_Re_Time)FireRecoveringStart();
	}
}

void UIreneAttackInstance::FireRecoveryWaitCancel()
{
	CurFireRecoverWaitTime = 0;
	GetWorld()->GetTimerManager().ClearTimer(FireRecoveryWaitTimerHandle);
	IsConsecutiveFire = false;
}
void UIreneAttackInstance::FireRecoveringStart()
{
	Irene->FireRecoveryData.bIsRecovering = true;
	FireRecoveryWaitCancel();
	CurFireRecoverTime = Irene->FireRecoveryData.Speed;

	RemainingFireRecovery = Irene->FireRecoveryData.Amount;
	FOnFireGaugeChange.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(FireRecoveryTimerHandle, this, &UIreneAttackInstance::FireRecovering,1.0f , true, 0.0f);
}
void UIreneAttackInstance::FireRecovering()
{
	if (Irene->FireRecoveryData.bIsRecovering)
	{
		int CurRecoveryAmount = RemainingFireRecovery / CurFireRecoverTime;
		RemainingFireRecovery -= CurRecoveryAmount;
		if (!IsFireFull())
		{
			FormGauge[0] += CurRecoveryAmount;
			FOnFireGaugeChange.Broadcast();
			if (IsFireFull()) FireRecoveringCancel();
		}
		if (CurFireRecoverTime > 1)CurFireRecoverTime--;
		else
		{			
			GetWorld()->GetTimerManager().ClearTimer(FireRecoveryTimerHandle);
			RemainingFireRecovery = 0;
			Irene->FireRecoveryData.bIsRecovering = false;
			IsConsecutiveFire = true;
			FireRecoveryWaitStart();			
		}
	}
}
void UIreneAttackInstance::FireRecoveringCancel()
{
	GetWorld()->GetTimerManager().ClearTimer(FireRecoveryTimerHandle);
	RemainingFireRecovery = 0;
	Irene->FireRecoveryData.bIsRecovering = false;
	IsConsecutiveFire = false;
	FOnFireGaugeChange.Broadcast();
	if (IsFireFull())FormGauge[0] = GetNameAtFormDataTable(FName("Fire"))->F_Gauge;
	else
	{
		//FireRecoveryWaitStart();
	}
}
bool UIreneAttackInstance::IsFireFull()
{
	if (FormGauge[0] >= GetNameAtFormTimeDataTable(FName("Fire_Form"))->F_Gauge/100)	return true;
	else
	{
		return false;
	}
}
float UIreneAttackInstance::GetFireRecoveryRatio()
{
	return ((float)RemainingFireRecovery < KINDA_SMALL_NUMBER) ? 0.0f : (FormGauge[0] + (float)RemainingFireRecovery) / GetNameAtFormDataTable(FName("Fire"))->F_Gauge;
}
#pragma endregion FireForm
#pragma region WaterForm
void UIreneAttackInstance::WaterRecoveryWaitStart()
{
	if(!Irene->WaterRecoveryData.bIsRecovering&& !IsWaterFull())
	GetWorld()->GetTimerManager().SetTimer(WaterRecoveryWaitTimerHandle, this, &UIreneAttackInstance::WaterRecoveryWaiting, 1.0f, true, 0.0f);
}
void UIreneAttackInstance::WaterRecoveryWaiting()
{
	if (IsConsecutiveWater == false)
	{
		CurWaterRecoverWaitTime++;
		if (CurWaterRecoverWaitTime >= Irene->WaterRecoveryData.Time)WaterRecoveringStart();
	}
	else
	{
		CurWaterRecoverWaitTime++;
		if (CurWaterRecoverWaitTime >= Irene->WaterRecoveryData.Water_Re_Time)WaterRecoveringStart();
	}
}

void UIreneAttackInstance::WaterRecoveryWaitCancel()
{
	CurWaterRecoverWaitTime = 0;
	GetWorld()->GetTimerManager().ClearTimer(WaterRecoveryWaitTimerHandle);
	IsConsecutiveWater = false;
}
void UIreneAttackInstance::WaterRecoveringStart()
{
	Irene->WaterRecoveryData.bIsRecovering = true;
	WaterRecoveryWaitCancel();
	CurWaterRecoverTime = Irene->WaterRecoveryData.Speed;
	RemainingWaterRecovery = Irene->WaterRecoveryData.Amount;
	FOnWaterGaugeChange.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(WaterRecoveryTimerHandle, this, &UIreneAttackInstance::WaterRecovering,1.0f , true, 0.0f);
}
void UIreneAttackInstance::WaterRecovering()
{
	if (Irene->WaterRecoveryData.bIsRecovering)
	{
		int CurRecoveryAmount = RemainingWaterRecovery / CurWaterRecoverTime;
		RemainingWaterRecovery -= CurRecoveryAmount;
		if (!IsWaterFull())
		{
			FormGauge[1] += CurRecoveryAmount;
			FOnWaterGaugeChange.Broadcast();
			if (IsWaterFull()) WaterRecoveringCancel();
		}
		if (CurWaterRecoverTime > 1)CurWaterRecoverTime--;
		else
		{			
			GetWorld()->GetTimerManager().ClearTimer(WaterRecoveryTimerHandle);
			RemainingWaterRecovery = 0;
			Irene->WaterRecoveryData.bIsRecovering = false;
			IsConsecutiveWater = true;
			WaterRecoveryWaitStart();			
		}
	}
}
void UIreneAttackInstance::WaterRecoveringCancel()
{
	GetWorld()->GetTimerManager().ClearTimer(WaterRecoveryTimerHandle);
	RemainingWaterRecovery = 0;
	Irene->WaterRecoveryData.bIsRecovering = false;
	IsConsecutiveWater = false;
	FOnWaterGaugeChange.Broadcast();
	if (IsWaterFull())FormGauge[1] = GetNameAtFormDataTable(FName("Water"))->F_Gauge;
	else
	{
		//WaterRecoveryWaitStart();
	}
}
bool UIreneAttackInstance::IsWaterFull()
{
	if (FormGauge[1] >=  GetNameAtFormTimeDataTable(FName("Water_Form"))->F_Gauge/100)	return true;
	else
	{
		return false;
	}
}
float UIreneAttackInstance::GetWaterRecoveryRatio()
{
	return ((float)RemainingWaterRecovery < KINDA_SMALL_NUMBER) ? 0.0f : (FormGauge[1] + (float)RemainingWaterRecovery) / GetNameAtFormDataTable(FName("Water"))->F_Gauge;
}
#pragma endregion WaterForm
#pragma region ElectricForm
void UIreneAttackInstance::ElectricRecoveryWaitStart()
{
	if(!Irene->ElectricRecoveryData.bIsRecovering&& !IsElectricFull())
	GetWorld()->GetTimerManager().SetTimer(ElectricRecoveryWaitTimerHandle, this, &UIreneAttackInstance::ElectricRecoveryWaiting, 1.0f, true, 0.0f);
}
void UIreneAttackInstance::ElectricRecoveryWaiting()
{
	if (IsConsecutiveElectric == false)
	{
		CurElectricRecoverWaitTime++;
		if (CurElectricRecoverWaitTime >= Irene->ElectricRecoveryData.Time)ElectricRecoveringStart();
	}
	else
	{
		CurElectricRecoverWaitTime++;
		if (CurElectricRecoverWaitTime >= Irene->ElectricRecoveryData.Electric_Re_Time)ElectricRecoveringStart();
	}
}

void UIreneAttackInstance::ElectricRecoveryWaitCancel()
{
	CurElectricRecoverWaitTime = 0;
	GetWorld()->GetTimerManager().ClearTimer(ElectricRecoveryWaitTimerHandle);
	IsConsecutiveElectric = false;
}

void UIreneAttackInstance::ElectricRecoveringStart()
{
	Irene->ElectricRecoveryData.bIsRecovering = true;
	ElectricRecoveryWaitCancel();
	CurElectricRecoverTime = Irene->ElectricRecoveryData.Speed;
	RemainingElectricRecovery = Irene->ElectricRecoveryData.Amount;
	FOnElectricGaugeChange.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(ElectricRecoveryTimerHandle, this, &UIreneAttackInstance::ElectricRecovering,1.0f , true, 0.0f);
}
void UIreneAttackInstance::ElectricRecovering()
{
	if (Irene->ElectricRecoveryData.bIsRecovering)
	{
		int CurRecoveryAmount = RemainingElectricRecovery / CurElectricRecoverTime;
		RemainingElectricRecovery -= CurRecoveryAmount;
		if (!IsElectricFull())
		{
			FormGauge[2] += CurRecoveryAmount;
			FOnElectricGaugeChange.Broadcast();
			if (IsElectricFull()) ElectricRecoveringCancel();
		}
		if (CurElectricRecoverTime > 1)CurElectricRecoverTime--;
		else
		{			
			GetWorld()->GetTimerManager().ClearTimer(ElectricRecoveryTimerHandle);
			RemainingElectricRecovery = 0;
			Irene->ElectricRecoveryData.bIsRecovering = false;
			IsConsecutiveElectric = true;
			ElectricRecoveryWaitStart();			
		}
	}
}
void UIreneAttackInstance::ElectricRecoveringCancel()
{
	GetWorld()->GetTimerManager().ClearTimer(ElectricRecoveryTimerHandle);
	RemainingElectricRecovery = 0;
	Irene->ElectricRecoveryData.bIsRecovering = false;
	IsConsecutiveElectric = false;
	FOnElectricGaugeChange.Broadcast();
	if (IsElectricFull())FormGauge[2] = GetNameAtFormDataTable(FName("Electric"))->F_Gauge;
	else
	{
		//ElectricRecoveryWaitStart();
	}
}
bool UIreneAttackInstance::IsElectricFull()
{
	if (FormGauge[2] >= GetNameAtFormTimeDataTable(FName("Electric_Form"))->F_Gauge/100)	return true;
	else
	{
		return false;
	}
}
float UIreneAttackInstance::GetElectricRecoveryRatio()
{
	return ((float)RemainingElectricRecovery < KINDA_SMALL_NUMBER) ? 0.0f : (FormGauge[2] + (float)RemainingElectricRecovery) / GetNameAtFormDataTable(FName("Electric"))->F_Gauge;
}
#pragma endregion ElectricForm


#pragma region GetAttribueRatio
float UIreneAttackInstance::GetFireRatio()
{
	return (FormGauge[0] < KINDA_SMALL_NUMBER) ? 0.0f : FormGauge[0] / (GetNameAtFormTimeDataTable(FName("Fire_Form"))->F_Gauge/100.0f);
}
float UIreneAttackInstance::GetWaterRatio()
{
	return (FormGauge[1] < KINDA_SMALL_NUMBER) ? 0.0f : FormGauge[1] / (GetNameAtFormTimeDataTable(FName("Water_Form"))->F_Gauge/100.0f);
}
float UIreneAttackInstance::GetElectricRatio()
{
	
	return (FormGauge[2] < KINDA_SMALL_NUMBER) ? 0.0f : FormGauge[2] / (GetNameAtFormTimeDataTable(FName("Electric_Form"))->F_Gauge/100.0f);
}
#pragma endregion GetRatio