// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneAttackInstance.h"
#include "../IreneCharacter.h"
#include "../PlayerFSM/IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneUIManager.h"
#include "IreneInputInstance.h"

#include "DrawDebugHelpers.h"
#include "../../STGameInstance.h"
#include "Kismet/GameplayStatics.h"



UIreneAttackInstance::UIreneAttackInstance()
{
	// 데이터 테이블
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_AttackDataTable(TEXT("/Game/Math/DT_AttackDataTable.DT_AttackDataTable"));
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_QuillDataTable(TEXT("/Game/Math/DT_QuillDataTable.DT_QuillDataTable"));
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_ChargeDataTable(TEXT("/Game/Math/DT_ChargeDataTable.DT_ChargeDataTable"));
	const ConstructorHelpers::FObjectFinder<UDataTable>DT_ElementDataTable(TEXT("/Game/Math/DT_ElementDataTable.DT_ElementDataTable"));
	if (DT_AttackDataTable.Succeeded() && DT_QuillDataTable.Succeeded() && DT_ChargeDataTable.Succeeded() && DT_ElementDataTable.Succeeded())
	{
		AttackDataTable = DT_AttackDataTable.Object;
		QuillDataTable = DT_QuillDataTable.Object;
		ChargeDataTable = DT_ChargeDataTable.Object;
		ElementDataTable = DT_ElementDataTable.Object;
	}
	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_FireBuff(TEXT("/Game/Effect/VFX_Irene/Feather/Buff/Ps_Buff_f.Ps_Buff_F"));
	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_WaterBuff(TEXT("/Game/Effect/VFX_Irene/Feather/Buff/Ps_Buff_w.Ps_Buff_W"));
	const ConstructorHelpers::FObjectFinder<UParticleSystem>PS_ThunderBuff(TEXT("/Game/Effect/VFX_Irene/Feather/Buff/Ps_Buff_t.Ps_Buff_T"));
	if (PS_FireBuff.Succeeded() && PS_WaterBuff.Succeeded() && PS_ThunderBuff.Succeeded())
	{
		BuffParticle.Add(PS_FireBuff.Object);
		BuffParticle.Add(PS_WaterBuff.Object);
		BuffParticle.Add(PS_ThunderBuff.Object);
	}
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
void UIreneAttackInstance::SetIsPerfectDodge(const bool Value, const TArray<uint8> PerfectDodgeDir,  AActor* Monster)
{
	IsPerfectDodge = Value;
	Irene->IreneInput->SetIsPerfectDodge(PerfectDodgeDir);
	PerfectDodgeMonster = Monster;
}
void UIreneAttackInstance::InitMemberVariable()
{
	SwordTargetMonster = nullptr;
	//초기 속성
	QuillAttribute = EAttributeKeyword::e_Fire;

	FireDeBuffStack = 0;
	WaterDeBuffStack = 0;
	ThunderDeBuffStack = 0;
	FireMonsterDamageAmount = 0;
	ThunderSustainTime = 0;
	
	bFollowTarget = false;
	FollowTargetAlpha = 0.0f;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;
	bFollowCameraTarget = false;
	FollowTargetCameraAlpha = 0.0f;
	CameraRot = FRotator::ZeroRotator;
	TargetCameraRot = FRotator::ZeroRotator;

	bMoveSkip = false;
	bDodgeJumpSkip = false;
	bReAttackSkip = false;
}
#pragma region Attack
float UIreneAttackInstance::GetATK()const
{
	return Irene->IreneData.Strength;
}

FName UIreneAttackInstance::GetBasicAttackDataTableName()
{
	// 기본공격 데이터 테이블 이름 받기 위한 조합 계산 함수
	FString AttributeName = "B_Attack_1";
	if (Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack1"))
	{
		AttributeName = "B_Attack_1";
	}
	else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack2"))
	{
		AttributeName = "B_Attack_2";
	}
	else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack3"))
	{
		AttributeName = "B_Attack_3";
	}
	return FName(AttributeName);
}

void UIreneAttackInstance::AttackStartComboState()
{
	// 노티파이 NextAttackCheck 도달 시 실행
	Irene->IreneData.CanNextCombo = true;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = FMath::Clamp<int32>(Irene->IreneData.CurrentCombo + 1, 1, Irene->IreneData.MaxCombo);
}
void UIreneAttackInstance::AttackEndComboState()
{
	Irene->IreneData.IsAttacking = false;
	Irene->Weapon->SetGenerateOverlapEvents(false);
	Irene->IreneData.CanNextCombo = false;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = 0;
}
void UIreneAttackInstance::AttackTimeEndState()
{
	// 몽타주가 완전히 끝남
	Irene->IreneData.IsAttacking = false;
	Irene->Weapon->SetGenerateOverlapEvents(false);
	Irene->IreneData.CanNextCombo = false;
	Irene->IreneData.IsComboInputOn = false;
	Irene->IreneData.CurrentCombo = 0;
	if (!Irene->IreneState->IsDodgeState() && !Irene->IreneState->IsJumpState() && !Irene->IreneState->IsIdleState())
	{
		Irene->ChangeStateAndLog(UBattleIdleState::GetInstance());
	}	
}

void UIreneAttackInstance::AttackCheck()
{
	// 노티파이 AttackHitCheck 도달 시 실행
	if (Irene->IreneAnim->GetCurrentActiveMontage())
	{
		Irene->Weapon->SetGenerateOverlapEvents(true);
		Irene->IreneUIManager->AttackSound->SoundPlay2D();
		Irene->IreneUIManager->AttackVoiceSound->SoundPlay2D();
		if(Irene->IreneAnim->GetCurrentActiveMontage())
			Irene->FindNearMonster();
	}
}
void UIreneAttackInstance::AttackStopCheck()
{
	// 노티파이 AttackStopCheck 도달 시 실행
	Irene->IsTimeStopping = false;
	Irene->Weapon->SetGenerateOverlapEvents(false);
}
void UIreneAttackInstance::DoAttack()
{
	// 실제로 공격을 하는 함수로 위에는 속성에 따른 콜라이더 사용과 아래에는 콜라이더를 보여주는 역할을 하는 코드가 있는 함수
	
	auto STGameInstance = Cast<USTGameInstance>(Irene->GetGameInstance());
	//if (STGameInstance->GetPlayerBattleState())
	//{
	//	Irene->CameraOutEvent();
	//}

	// 몬스터 추적 초기화
	bFollowTarget = false;
	FollowTargetAlpha = 0;
	PlayerPosVec = FVector::ZeroVector;
	TargetPosVec = FVector::ZeroVector;
	bool bResult = false;

	const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetBasicAttackDataTableName()));
	
	TArray<FHitResult> MonsterList;
	FCollisionQueryParams Params(NAME_None, false, Irene);
	bResult = GetWorld()->SweepMultiByChannel(
	MonsterList,
	Irene->GetActorLocation() + (Irene->GetActorForwardVector()*(AttackTable->Attack_Distance_1-50.0f)),
	Irene->GetActorLocation() + (Irene->GetActorForwardVector()*(AttackTable->Attack_Distance_1-50.0f)),
	FRotationMatrix::MakeFromZ(Irene->GetActorForwardVector()).ToQuat(),
	ECollisionChannel::ECC_GameTraceChannel1,
	FCollisionShape::MakeBox(FVector(200, 50, AttackTable->Attack_Distance_1)),
	Params);
	
	// 그리기 시작
	#if ENABLE_DRAW_DEBUG
		FVector TraceVec = Irene->GetActorForwardVector();
		FVector Center = Irene->GetActorLocation() + (Irene->GetActorForwardVector()*(AttackTable->Attack_Distance_1-50.0f));
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;
		DrawDebugBox(GetWorld(), Center, FVector(200, 50, AttackTable->Attack_Distance_1), CapsuleRot, DrawColor, false, DebugLifeTime);
	#endif

	// 모든 충돌된 액터에 데미지 전송
	for (FHitResult Monster : MonsterList)
	{
		if (bResult)
		{
			if (Monster.Actor.IsValid())
			{
				FDamageEvent DamageEvent;

				auto Mob = Cast<AMonster>(Monster.Actor);
				if (Mob != nullptr)
					Mob->SetAttackedInfo(true, 0, EAttackedDirection::Down);
				UGameplayStatics::ApplyDamage(Monster.Actor.Get(), Irene->IreneData.Strength, nullptr, Irene, nullptr);
			}
		}
	}
	// 충돌한 액터가 있으면 카메라 쉐이크 시작
	if (bResult)
		Irene->CameraShakeOn = true;
	
	//속성공격 기준 몬스터 할당해제
	if (bResult)
		//auto STGameInstance = Cast<USTGameInstance>(Irene->GetGameInstance());
		if (STGameInstance->GetAttributeEffectMonster() != nullptr)
			STGameInstance->ResetAttributeEffectMonster();
}
void UIreneAttackInstance::SetFireQuillStack(const int Value)
{
	if(Value == 0)
		return;
	switch (Value)
	{
	case 1:
		Irene->IreneData.FireQuillStackDmg = 1.2f;
		break;
	case 2:
		Irene->IreneData.FireQuillStackDmg = 1.5f;
		break;
	case 3:
		Irene->IreneData.FireQuillStackDmg = 2.0f;
		break;
	default: break;
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BuffParticle[0],Irene->GetActorLocation());
	GetWorld()->GetTimerManager().SetTimer(FireQuillStackTimerHandle, this, &UIreneAttackInstance::ResetFireQuillStack, 5.0f, false);
}
void UIreneAttackInstance::SetWaterQuillStack(const int Value)
{
	if(Value == 0)
		return;
	switch (Value)
	{
	case 1:
		Irene->IreneData.Shield = 100;
		break;
	case 2:
		Irene->IreneData.Shield = 200;
		break;
	case 3:
		Irene->IreneData.Shield = 300;
		break;
	default: break;
	}
	Irene->ShieldComp->SetVisibility(true);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BuffParticle[1],Irene->GetActorLocation());
	GetWorld()->GetTimerManager().SetTimer(WaterQuillStackTimerHandle, this, &UIreneAttackInstance::ResetWaterQuillStack, 120.0f, false);
}
void UIreneAttackInstance::SetThunderQuillStack(const int Value)
{
	if(Value == 0)
		return;
	switch (Value)
	{
	case 1:
		Irene->IreneData.ThunderQuillStackSpeed = 1.05f;
		break;
	case 2:
		Irene->IreneData.ThunderQuillStackSpeed = 1.10f;
		break;
	case 3:
		Irene->IreneData.ThunderQuillStackSpeed = 1.20f;
		break;
	default: break;
	}
	if(Irene->GetCharacterMovement()->MaxWalkSpeed == Irene->IreneData.RunMaxSpeed ||
		Irene->GetCharacterMovement()->MaxWalkSpeed == Irene->IreneData.SprintMaxSpeed)
	Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->GetCharacterMovement()->MaxWalkSpeed * Irene->IreneData.ThunderQuillStackSpeed;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BuffParticle[2],Irene->GetActorLocation());
	GetWorld()->GetTimerManager().SetTimer(ThunderQuillStackTimerHandle, this, &UIreneAttackInstance::ResetThunderQuillStack, 10.0f, false);
}
void UIreneAttackInstance::ResetFireQuillStack()
{
	GetWorld()->GetTimerManager().ClearTimer(FireQuillStackTimerHandle);	
	Irene->IreneData.FireQuillStackDmg = 1.0f;
}
void UIreneAttackInstance::ResetWaterQuillStack()
{
	GetWorld()->GetTimerManager().ClearTimer(WaterQuillStackTimerHandle);	
	Irene->ShieldComp->SetVisibility(false);
	Irene->IreneData.Shield = 0;
}
void UIreneAttackInstance::ResetThunderQuillStack()
{
	GetWorld()->GetTimerManager().ClearTimer(ThunderQuillStackTimerHandle);
	if(Irene->GetCharacterMovement()->MaxWalkSpeed == Irene->IreneData.RunMaxSpeed * Irene->IreneData.ThunderQuillStackSpeed ||
		Irene->GetCharacterMovement()->MaxWalkSpeed == Irene->IreneData.SprintMaxSpeed * Irene->IreneData.ThunderQuillStackSpeed)
			Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->GetCharacterMovement()->MaxWalkSpeed / Irene->IreneData.ThunderQuillStackSpeed;
	Irene->IreneData.ThunderQuillStackSpeed = 1.0f;
}

void UIreneAttackInstance::SetFireDeBuffStack(const int Value, const float DamageAmount)
{
	FireDeBuffStack = Value;
	FireMonsterDamageAmount = DamageAmount;
	if(!FireDeBuffTickTimerHandle.IsValid())
		GetWorld()->GetTimerManager().SetTimer(FireDeBuffTickTimerHandle, this, &UIreneAttackInstance::LoopFireDeBuff, 5.0f, true);
	GetWorld()->GetTimerManager().SetTimer(FireDeBuffStackTimerHandle, this, &UIreneAttackInstance::ResetFireDeBuffStack, 120.0f, false);
}
void UIreneAttackInstance::SetWaterDeBuffStack(const int Value)
{
	WaterDeBuffStack = Value;
	switch (Value)
	{
	case 1:
		Irene->IreneData.WaterDeBuffSpeed = 0.9f;
		break;
	case 2:
		Irene->IreneData.WaterDeBuffSpeed = 0.85f;
		break;
	case 3:
		Irene->IreneData.WaterDeBuffSpeed = 0.7f;
		break;
	default: break;
	}
	GetWorld()->GetTimerManager().SetTimer(WaterDeBuffStackTimerHandle, this, &UIreneAttackInstance::ResetWaterDeBuffStack, 120.0f, false);
}
void UIreneAttackInstance::SetThunderDeBuffStack(const int Value)
{
	if(!ThunderDeBuffTickTimerHandle.IsValid() || ThunderDeBuffStackTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ThunderDeBuffTickTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(ThunderDeBuffStackTimerHandle);
		ThunderDeBuffStack = Value;
		ThunderSustainTime = ThunderDeBuffStack*10;
		GetWorld()->GetTimerManager().SetTimer(ThunderDeBuffTickTimerHandle, this, &UIreneAttackInstance::OverSustainTime, ThunderSustainTime, false);
	}
}
void UIreneAttackInstance::LoopFireDeBuff()const
{
	if(FireMonsterDamageAmount != 0)
		Irene->SetHP(FireMonsterDamageAmount/2);
}
void UIreneAttackInstance::ResetFireDeBuffStack()
{
	GetWorld()->GetTimerManager().ClearTimer(FireDeBuffTickTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(FireDeBuffStackTimerHandle);
	FireDeBuffStack = 0;
	FireMonsterDamageAmount = 0;
}
void UIreneAttackInstance::ResetWaterDeBuffStack()
{
	GetWorld()->GetTimerManager().ClearTimer(WaterDeBuffStackTimerHandle);
	WaterDeBuffStack = 0;
	Irene->IreneData.WaterDeBuffSpeed = 1;
}
void UIreneAttackInstance::ResetThunderDeBuffStack()
{
	GetWorld()->GetTimerManager().ClearTimer(ThunderDeBuffStackTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(ThunderDeBuffTickTimerHandle);
	ThunderDeBuffStack = 0;
	ThunderSustainTime = 0;
}
void UIreneAttackInstance::OverSustainTime()
{
	ThunderSustainTime = 0;
	GetWorld()->GetTimerManager().SetTimer(ThunderDeBuffStackTimerHandle, this, &UIreneAttackInstance::ResetThunderDeBuffStack, 30.0f, false);
}
#pragma endregion Attack

#pragma region State
void UIreneAttackInstance::SetAttackState()const
{
	// 현재 상태를 이용하여 다음 기본공격 상태로 전이 할 수 있는지 확인하는 함수
	if (Irene->IreneAnim->GetCurrentActiveMontage() == nullptr
	&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_1")) != 0 && Irene->IreneState->GetStateToString().Compare(FString("B_Attack_3")) != 0)
	{
		Irene->ChangeStateAndLog(UBasicAttack1State::GetInstance());
	}
	else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack2")
	&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_2")) != 0)
	{
		Irene->ChangeStateAndLog(UBasicAttack2State::GetInstance());
	}
	else if(Irene->IreneAnim->Montage_GetCurrentSection(Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack3")
	&& Irene->IreneState->GetStateToString().Compare(FString("B_Attack_3")) != 0)
	{
		Irene->ChangeStateAndLog(UBasicAttack3State::GetInstance());
	}
}
#pragma endregion State

#pragma region GetSet
FName UIreneAttackInstance::GetAttributeToFormTimeDataTableName() const
{
	// 현재 속성에 따라 FormTimeDataTable에서 사용하는 Name 리턴하는 함수
	switch (QuillAttribute)
	{
	case EAttributeKeyword::e_Fire: return FName("Fire_Form");
	case EAttributeKeyword::e_Water: return FName("Water_Form");
	case EAttributeKeyword::e_Thunder: return FName("Thunder_Form");
	default: return FName("Error GetAttributeToFormTimeDataTableName");
	}
}
#pragma endregion GetSet