// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneInputInstance.h"
#include "IreneCharacter.h"
#include "IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneAttackInstance.h"
#include "IreneUIManager.h"
#include "../STGameInstance.h"

void UIreneInputInstance::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);
	InitMemberVariable();
}
void UIreneInputInstance::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}
void UIreneInputInstance::InitMemberVariable()
{
	// WASD 키 입력 초기화
	MoveKey.Add(0);
	MoveKey.Add(0);
	MoveKey.Add(0);
	MoveKey.Add(0);
	
	// 추락 중 구르기 입력 초기화
	IsFallingRoll = false;

	// 점프 및 차징 중 초기화
	bStartJump = false;
	JumpingTime = 0.0f;
	IsCharging = false;
	ChargingTime = 0.0f;

	// 마우스 입력 초기화
	bLeftButtonPressed = false;
	bRightButtonPressed = false;
	bUseLeftButton = false;
	bUseRightButton = false;

	StartWaterDodgeStamina = 0;
	
	bUseWaterDodge = false;

	ThunderSkillCount = 2;
	MaxThunderSkillCount = ThunderSkillCount;

	FireCurCoolTime = 0.0f;
	WaterCurCoolTime = 0.0f;
	ThunderCurCoolTime = 0.0f;


	CoolTimeRate = 0.2f;
	FireSkillCoolTime = 0.0f;
	WaterSkillCoolTime = 0.0f;
	ThunderSkillCoolTime = 0.0f;

	bIsFireSkillOn = true;
	bIsWaterSkillOn = true;
	bIsThunderSkillOn = true;

	bIsFireAttributeOn = true;
	bIsWaterAttributeOn = true;
	bIsThunderAttributeOn = true;

	bIsDialogOn=false;
}
void UIreneInputInstance::Begin()
{
	const TUniquePtr<FFormTimeDataTable> FireFormTimeDataTable = MakeUnique<FFormTimeDataTable>(*Irene->IreneAttack->GetNameAtFormTimeDataTable(FName("Fire_Form")));
	if(FireFormTimeDataTable != nullptr)
	{
		FireMaxCoolTime = FireFormTimeDataTable->Form_C_Time;
	}
	const TUniquePtr<FFormTimeDataTable> WaterFormTimeDataTable = MakeUnique<FFormTimeDataTable>(*Irene->IreneAttack->GetNameAtFormTimeDataTable(FName("Water_Form")));
	if(WaterFormTimeDataTable != nullptr)
	{
		WaterMaxCoolTime = WaterFormTimeDataTable->Form_C_Time;
	}
	const TUniquePtr<FFormTimeDataTable> ThunderFormTimeDataTable = MakeUnique<FFormTimeDataTable>(*Irene->IreneAttack->GetNameAtFormTimeDataTable(FName("Thunder_Form")));
	if(ThunderFormTimeDataTable != nullptr)
	{
		ThunderMaxCoolTime = ThunderFormTimeDataTable->Form_C_Time;
	}
}

#pragma region Move
void UIreneInputInstance::MoveForward()
{
	const FRotator Rotation = Irene->Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// 0: 전진, 2: 후진
	if (MoveKey[0] != 0 && MoveKey[0] < 3)
	{
		Irene->AddMovementInput(Direction);
	}
	if (MoveKey[2] != 0 && MoveKey[2] < 3)
	{
		Irene->AddMovementInput(Direction * -1);
	}
}
void UIreneInputInstance::MoveRight()
{
	const FRotator Rotation = Irene->Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// 1: 좌측, 3: 우측
	if (MoveKey[1] != 0 && MoveKey[1] < 3)
	{
		Irene->AddMovementInput(Direction * -1);
	}
	if (MoveKey[3] != 0 && MoveKey[3] < 3)
	{
		Irene->AddMovementInput(Direction);
	}
}

void UIreneInputInstance::MoveAuto(const float EndTimer)const
{
	// 자동으로 이동시키는 함수
	// 이동 후 공격
	if (Irene->IreneAttack->GetFollowTarget())
	{
		const float TargetAlpha = Irene->IreneAttack->GetFollowTargetAlpha()/EndTimer;
		Irene->IreneAttack->SetFollowTargetAlpha((TargetAlpha + GetWorld()->GetDeltaSeconds() * 2 * Irene->IreneData.TargetFollowSpeed)/EndTimer);
		if (TargetAlpha >= 1)
			Irene->IreneAttack->SetFollowTargetAlpha(1);
		const FVector Target = FMath::Lerp(Irene->IreneAttack->GetPlayerPosVec(), Irene->IreneAttack->GetTargetPosVec(), Irene->IreneAttack->GetFollowTargetAlpha());
		Irene->GetCapsuleComponent()->SetRelativeLocation(Target, true);
		//STARRYLOG(Warning,TEXT("%f   %f   %f"), Irene->IreneAttack->GetPlayerPosVec().X,Irene->IreneAttack->GetPlayerPosVec().Y,Irene->IreneAttack->GetPlayerPosVec().Z);
		//STARRYLOG(Warning,TEXT("%f   %f   %f"), Irene->IreneAttack->GetTargetPosVec().X,Irene->IreneAttack->GetTargetPosVec().Y,Irene->IreneAttack->GetTargetPosVec().Z);
		//STARRYLOG(Error,TEXT("%f   %f   %f"), Target.X,Target.Y,Target.Z);

		if(FVector::Dist(Target, Irene->IreneAttack->GetTargetPosVec()) <= 50)
		{
			FString AnimName = "";
			if(Irene->IreneAnim->GetCurrentActiveMontage())
				AnimName = Irene->IreneAnim->GetCurrentActiveMontage()->GetName();
			// 전기스킬은 다른 방식으로 공격 실행
			if (AnimName != FString("IreneThunderSkill_Montage"))
			{
				Irene->IreneAttack->DoAttack();
			}
		}
	}
}

void UIreneInputInstance::StartJump()
{
	if (CanJumpState() && ((Irene->IreneState->IsAttackState()||Irene->IreneState->IsSkillState()) && Irene->IreneAttack->GetCanDodgeJumpSkip() || (!Irene->IreneState->IsAttackState()&&!Irene->IreneState->IsSkillState()))&&!bIsDialogOn)
	{
		Irene->IreneAnim->StopAllMontages(0.01f);
		Irene->bPressedJump = true;
		Irene->ChangeStateAndLog(UJumpStartState::GetInstance());
	}
}
void UIreneInputInstance::StopJump()
{
	Irene->bPressedJump = false;
}
#pragma endregion Move

#pragma region MoveInput
void UIreneInputInstance::MovePressedKey(const int Value)
{
	if (!bIsDialogOn)
	{
		// 런 상태로 전이가 가능한 상태에서 키를 입력하면 1, 스프린트 속도에서 키를 입력하면 2, 런 상태가 불가능한 상태에서 키를 입력하면 3
		// 3은 나중에 AIreneCharacter::ActionEndChangeMoveState에서 1로 적용
		if (CanRunState())
		{
			MoveKey[Value] = 1;
			if (Irene->GetCharacterMovement()->MaxWalkSpeed == Irene->IreneData.SprintMaxSpeed)
				MoveKey[Value] = 2;
			if (Irene->IreneState->IsIdleState())
			{
				// 반대 방향키 아니면
				if (!((MoveKey[0] != 0 && MoveKey[2] != 0) || (MoveKey[1] != 0 && MoveKey[3] != 0)))
				{
					Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->IreneData.RunMaxSpeed;
					Irene->ChangeStateAndLog(URunLoopState::GetInstance());
				}
			}
		}
		else
			MoveKey[Value] = 3;
	}
}
void UIreneInputInstance::MoveW(float Rate)
{
	if(Rate >= 1)
		MovePressedKey(0);
	else
		MoveKey[0] = 0;
}
void UIreneInputInstance::MoveA(float Rate)
{
	if(Rate >= 1)
		MovePressedKey(1);
	else
		MoveKey[1] = 0;
}
void UIreneInputInstance::MoveS(float Rate)
{
	if(Rate >= 1)
		MovePressedKey(2);
	else
		MoveKey[2] = 0;
}
void UIreneInputInstance::MoveD(float Rate)
{
	if(Rate >= 1)
		MovePressedKey(3);
	else
		MoveKey[3] = 0;
}
FVector UIreneInputInstance::GetMoveKeyToDirVector()
{
	// 현재 키에 따라 방향 리턴 함수
	const FRotator Rotation = Irene->Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector LookDir = FVector::ZeroVector;
	if (MoveKey[0] != 0 && MoveKey[0] < 3)
	{
		LookDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	}
	if (MoveKey[2] != 0 && MoveKey[2] < 3)
	{
		LookDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X)*-1;
	}
	if (MoveKey[1] != 0 && MoveKey[1] < 3)
	{
		LookDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y)*-1;
	}
	if (MoveKey[3] != 0 && MoveKey[3] < 3)
	{
		LookDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	}
	if(LookDir == FVector::ZeroVector)
		LookDir = Irene->GetActorForwardVector();
	LookDir.Normalize();

	return LookDir;
}

#pragma endregion MoveInput

#pragma region Input
void UIreneInputInstance::Turn(float Rate)
{

	// 마우스 좌우 이동
	if (Irene->WorldController->bShowMouseCursor == false && !Irene->IreneState->IsDeathState())
		Irene->AddControllerYawInput(Rate * Irene->IreneData.EDPI / 2);
}
void UIreneInputInstance::LookUp(float Rate)
{
	// 마우스 상하 이동
	const float Yaw = FRotator::NormalizeAxis(Irene->WorldController->GetControlRotation().Pitch) + Rate * Irene->IreneData.EDPI * Irene->WorldController->InputPitchScale;

	// 시야각 제한
	if (Yaw < 50)
	{
		if (Irene->WorldController->bShowMouseCursor == false && !Irene->IreneState->IsDeathState())
			Irene->AddControllerPitchInput(Rate * Irene->IreneData.EDPI / 5.5f);
	}
}

void UIreneInputInstance::LeftButton(float Rate)
{
	if(Rate != 0)
		bLeftButtonPressed = true;
	else
		bLeftButtonPressed = false;
	if (CanAttackState() && !AttackWaitHandle.IsValid() && bUseRightButton == false && !bIsDialogOn)
	{
		if (Rate >= 1.0)
		{
			Irene->IreneAttack->SetAttackState();

			const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetBasicAttackDataTableName()));
			if(AttackTable != nullptr)
			{
				// 공격력 계산으로 기본적으로 ATTACK_DAMAGE_1만 사용하며 불 스킬은 UIreneInputInstance::RightButtonReleased에서 데미지 설정을 함
				Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;				
			}
			
			bUseLeftButton = true;
			// 마우스 왼쪽 누르고 있을 때 연속공격 지연 시간(한번에 여러번 공격 인식 안하도록 함)
			constexpr float WaitTime = 0.15f;

			GetWorld()->GetTimerManager().SetTimer(AttackWaitHandle, FTimerDelegate::CreateLambda([&]()
				{
					AttackWaitHandle.Invalidate();
				}), WaitTime, false);

			if (Irene->IreneData.IsAttacking)
			{
				if (Irene->IreneData.CanNextCombo)
				{
					Irene->IreneData.IsComboInputOn = true;
				}
				else
				{
					// 공격중에 NextAttackCheck노티파이와 AttackStop의 세션사이에 클릭하면 의도한 결과가 안나오니 수정필요
					Irene->IreneData.CurrentCombo += 1;
					Irene->IreneAnim->JumpToAttackMontageSection(Irene->IreneData.CurrentCombo);
				}
			}
			else
			{
				Irene->IreneAttack->AttackStartComboState();
				Irene->IreneAnim->PlayAttackMontage();

				Irene->IreneAnim->NextToAttackMontageSection(Irene->IreneData.CurrentCombo);
				Irene->IreneData.IsAttacking = true;
			}
		}
	}
}
void UIreneInputInstance::RightButton(const float DeltaTime)const
{
	if(IsCharging == true && Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire && !bIsDialogOn)
	{
		const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetActionAttackDataTableName()));

		if(AttackTable != nullptr)
		{
			if(ChargingTime > AttackTable->Charge_Time_3/100.0f)
			{
				Irene->IreneAnim->SetFireChargeCount(2);
			}
			else if(ChargingTime > AttackTable->Charge_Time_2/100.0f)
			{
				Irene->IreneAnim->SetFireChargeCount(1);
			}
			else if(ChargingTime > AttackTable->Charge_Time_1/100.0f)
			{
				Irene->IreneAnim->SetFireChargeCount(0);
			}
		}
	}
}
void UIreneInputInstance::RightButtonPressed()
{
	bRightButtonPressed = true;
	if (CanAttackState() && !bUseLeftButton && !bIsDialogOn)
	{
		IsCharging = true;
		ChargingTime = 0.0f;		

		Irene->SetActorRotation(GetMoveKeyToDirVector().Rotation());

		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire && bIsFireSkillOn)
		{
			bUseRightButton = true;
			
			//Irene->IreneAttack->SetSkillState();
			const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetActionAttackDataTableName()));
			MaxFireSkillCoolTime = static_cast<float>(AttackTable->C_Time) / 1000.0f;
			bIsFireSkillOn = false;

			if (AttackTable != nullptr && !Irene->IreneState->IsChargeState())
			{
				Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;
				Irene->ChangeStateAndLog(UCharge1State::GetInstance());
			}
		}
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water && bIsWaterSkillOn)
		{
			bUseRightButton = true;
			
			Irene->IreneAttack->SetSkillState();
			const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetActionAttackDataTableName()));
			MaxWaterSkillCoolTime = static_cast<float>(AttackTable->C_Time) / 1000.0f;
			bIsWaterSkillOn = false;

			if (AttackTable != nullptr)
			{
				Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;
				Irene->IreneAnim->PlaySkillAttackMontage();
				GetWorld()->GetTimerManager().SetTimer(WaterSkillWaitHandle, this, &UIreneInputInstance::WaterSkillWait, CoolTimeRate, true, 0.0f);
				Irene->IreneUIManager->PlayerHud->UseSkill();
			}
		}
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder && (!Irene->IreneState->IsSkillState() || Irene->IreneAttack->GetCanSkillSkip()) && bIsThunderSkillOn)
		{
			if(ThunderSkillCount > 0 && !bUseRightButton)
			{
				STARRYLOG_S(Warning);
				bUseRightButton = true;
				Irene->IreneAttack->SetSkillState();
				const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetActionAttackDataTableName()));
				MaxThunderSkillCoolTime = static_cast<float>(AttackTable->C_Time) / 1000.0f;

				if (AttackTable != nullptr && bUseRightButton)
				{
					Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;
					Irene->IreneAnim->PlaySkillAttackMontage();
					if (ThunderSkillCount > 0)
					{
						if (ThunderSkillCount == MaxThunderSkillCount)
						{
							GetWorld()->GetTimerManager().SetTimer(ThunderSkillWaitHandle, this, &UIreneInputInstance::ThunderSkillWait, CoolTimeRate, true, 0.0f);
						}
					}
					else
					{
						bIsThunderSkillOn = false;
					}
				}
				Irene->IreneUIManager->PlayerHud->UseSkill();
			}
			else
			{
				IsCharging = false;
				ChargingTime = 0.0f;
				bUseRightButton = false;
			}
		}
	}
}
void UIreneInputInstance::RightButtonReleased()
{
	bRightButtonPressed = false;
	if (CanAttackState() && !bUseLeftButton && bUseRightButton && !bIsDialogOn)
	{
		const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetActionAttackDataTableName()));

		IsCharging = false;

		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
		{
			if (AttackTable != nullptr && bUseRightButton)
			{
				GetWorld()->GetTimerManager().SetTimer(FireSkillWaitHandle, this, &UIreneInputInstance::FireSkillWait, CoolTimeRate, true, 0.0f);
				Irene->IreneUIManager->PlayerHud->UseSkill();
				Irene->ChangeStateAndLog(USkillFireStartState::GetInstance());
				if(ChargingTime > AttackTable->Charge_Time_3/100.0f)
				{
					Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_3;
					Irene->IreneAnim->PlaySkillAttackMontage(2);
				}
				else if(ChargingTime > AttackTable->Charge_Time_2/100.0f)
				{
					Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_2;
					Irene->IreneAnim->PlaySkillAttackMontage();
				}
				else if(ChargingTime > AttackTable->Charge_Time_1/100.0f)
				{
					Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;
					Irene->IreneAnim->PlaySkillAttackMontage();
				}
				else
				{
					bUseRightButton = false;
					Irene->ChangeStateAndLog(UIdleState::GetInstance());
				}
			}			
		}
		Irene->IreneAnim->SetFireChargeCount(0);
		ChargingTime = 0.0f;
	}
}

void UIreneInputInstance::MouseWheel(float Rate)
{
	if (!Irene->IreneState->IsDeathState())
	{
		// 줌인줌아웃
		Irene->SpringArmComp->TargetArmLength -= Rate * Irene->IreneData.MouseWheelSpeed;

		Irene->STGameInstance->GetPlayerBattleState() == true ?
			Irene->SpringArmComp->TargetArmLength = FMath::Clamp(Irene->SpringArmComp->TargetArmLength, Irene->IreneData.MinFollowCameraZPosition, Irene->IreneData.MaxBattleCameraZPosition):
			Irene->SpringArmComp->TargetArmLength = FMath::Clamp(Irene->SpringArmComp->TargetArmLength, Irene->IreneData.MinFollowCameraZPosition, Irene->IreneData.MaxFollowCameraZPosition);
	}
}

void UIreneInputInstance::AttributeKeywordReleased(const EAttributeKeyword Attribute)
{
	if (!bIsDialogOn)
	{
		// 속성을 변화시키는 함수
		if (!Irene->IreneState->IsAttackState() && !Irene->IreneState->IsSkillState() && !Irene->IreneState->IsDeathState() && Irene->IreneAttack->GetAttribute() != Attribute)
		{
			if (Attribute == EAttributeKeyword::e_Fire && bIsFireAttributeOn)
				ChangeForm(Attribute);
			if (Attribute == EAttributeKeyword::e_Water && bIsWaterAttributeOn)
				ChangeForm(Attribute);
			if (Attribute == EAttributeKeyword::e_Thunder && bIsThunderAttributeOn)
				ChangeForm(Attribute);
		}
	}
}

void UIreneInputInstance::FireKeywordReleased()
{
	AttributeKeywordReleased(EAttributeKeyword::e_Fire);
}
void UIreneInputInstance::WaterKeywordReleased()
{
	AttributeKeywordReleased(EAttributeKeyword::e_Water);
}
void UIreneInputInstance::ElectricKeywordReleased()
{
	AttributeKeywordReleased(EAttributeKeyword::e_Thunder);
}
void UIreneInputInstance::ChangeForm(const EAttributeKeyword Value)
{
	// 속성을 변화시키고 그에 따른 UI와 사운드 적용
	Irene->IreneAttack->SetAttribute(Value);
	Irene->IreneAnim->SetAttribute(Irene->IreneAttack->GetAttribute());
	Irene->FOnAttributeChange.Broadcast();

	// 속성 마다 소리와 무기 설정 적용
	if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
	{
		Irene->IreneUIManager->AttackSound->SetParameter("Attributes", 1.0f);
		Irene->Weapon->SetSkeletalMesh(Irene->WeaponMeshArray[0]);
		Irene->Weapon->AttachToComponent(Irene->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, Irene->WeaponSocketNameArray[0]);
	}
	else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
	{
		Irene->IreneUIManager->AttackSound->SetParameter("Attributes", 2.0f);
		Irene->Weapon->SetSkeletalMesh(Irene->WeaponMeshArray[1]);
		Irene->Weapon->AttachToComponent(Irene->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, Irene->WeaponSocketNameArray[1]);
	}
	else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
	{
		Irene->IreneUIManager->AttackSound->SetParameter("Attributes", 3.0f);
		Irene->Weapon->SetSkeletalMesh(Irene->WeaponMeshArray[2]);
		Irene->Weapon->AttachToComponent(Irene->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, Irene->WeaponSocketNameArray[2]);
	}
	// 속성 마다 변화 쿨타임 타이머 시작
 	bIsThunderAttributeOn = false;
	bIsWaterAttributeOn = false;
	bIsFireAttributeOn = false;

	ThunderCurCoolTime = 0.0f;
	FireCurCoolTime = 0.0f;
	WaterCurCoolTime = 0.0f;
	//Fire
	GetWorld()->GetTimerManager().SetTimer(FireStartTimer, this, &UIreneInputInstance::FireCoolTime, CoolTimeRate, true, 0.0f);
	//Water
	GetWorld()->GetTimerManager().SetTimer(WaterStartTimer, this, &UIreneInputInstance::WaterCoolTime, CoolTimeRate, true, 0.0f);
	//Thunder
	GetWorld()->GetTimerManager().SetTimer(ElectricStartTimer, this, &UIreneInputInstance::ThunderCoolTime, CoolTimeRate, true, 0.0f);
}

void UIreneInputInstance::DodgeKeyword()
{
	if (!Irene->GetMovementComponent()->IsFalling() && !Irene->IreneState->IsDodgeState() && !Irene->IreneState->IsDeathState() &&
	((Irene->IreneState->IsAttackState() || Irene->IreneState->IsSkillState()) && Irene->IreneAttack->GetCanDodgeJumpSkip()||(!Irene->IreneState->IsAttackState()&&!Irene->IreneState->IsSkillState()))&&!bIsDialogOn)
	{
		bUseDodgeKey = true;
		// 불닷지 & FireDodge (없앨수도 있음)
		// if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire && StaminaGauge >= 75)
		// {
		// 	Irene->IreneAnim->StopAllMontages(0);
		// 	StaminaGauge -= 75;
		// 	constexpr float WaitTime = 0.6f; //시간을 설정
		// 	FVector ForwardVec = Irene->WorldController->GetControlRotation().Vector();
		// 	ForwardVec.Z = 0;
		// 	ForwardVec.Normalize();
		// 	MoveAutoDirection = FVector::ZeroVector;
		//
		// 	// w키나 아무방향 없으면 정면으로 이동
		// 	MoveAutoDirection += ForwardVec*-1;
		// 	MoveAutoDirection.Normalize();
		// 	
		// 	const float z = UKismetMathLibrary::FindLookAtRotation(Irene->GetActorLocation(), Irene->GetActorLocation() + MoveAutoDirection).Yaw;
		// 	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, z, 0.0f));
		//
		// 	GetWorld()->GetTimerManager().SetTimer(MoveAutoWaitHandle, FTimerDelegate::CreateLambda([&]()
		// 		{
		// 			// 도중에 추락 안하고 정상적으로 진행됬을 때
		// 			if (Irene->IreneState->GetStateToString().Compare(FString("Dodge")) == 0)
		// 			{
		// 				Irene->ActionEndChangeMoveState();
		// 				Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
		// 			}
		// 		}), WaitTime, false);
		// }
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder && Irene->IreneData.CurrentStamina >= 37.5f &&
			!Irene->IreneState->IsJumpState() && !Irene->IreneState->IsDeathState())
		{
			Irene->IreneAnim->StopAllMontages(0);
			Irene->IreneData.CurrentStamina -= 37.5f;
			Irene->ChangeStateAndLog(UDodgeThunderStartState::GetInstance());

			if(!DodgeWaitHandle.IsValid())
				Irene->GetCharacterMovement()->AddImpulse(GetMoveKeyToDirVector()*Irene->IreneData.FirstThunderDodgeSpeed);
			else
				Irene->GetCharacterMovement()->AddImpulse(GetMoveKeyToDirVector()*Irene->IreneData.DoubleThunderDodgeSpeed);
			
			GetWorld()->GetTimerManager().SetTimer(ThunderDodgeWaitHandle, FTimerDelegate::CreateLambda([&]()
			 {
				 ThunderDodgeWaitHandle.Invalidate();
			 }), 0.03f, false);			
			GetWorld()->GetTimerManager().SetTimer(DodgeWaitHandle, FTimerDelegate::CreateLambda([&]()
			 {
				 DodgeWaitHandle.Invalidate();
			 }), Irene->IreneData.ThunderDodgeTime, false);
		}
	}	
}
void UIreneInputInstance::WaterDodgeKeyword(float Rate)
{
	if(Rate >= 1.0f && Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water && Irene->IreneData.CurrentStamina > 0 &&
		!StaminaWaitHandle.IsValid() && !DodgeWaitHandle.IsValid() && !Irene->IreneState->IsDeathState() && !Irene->IreneState->IsJumpState() &&
		((Irene->IreneState->IsAttackState() || Irene->IreneState->IsSkillState()) && Irene->IreneAttack->GetCanDodgeJumpSkip()||(!Irene->IreneState->IsAttackState()&&!Irene->IreneState->IsSkillState()))&&!bIsDialogOn)
	{
		Irene->IreneAnim->StopAllMontages(0.01f);
		if(!bUseWaterDodge && Irene->IreneData.CurrentStamina > 75)
		{
			StartWaterDodgeStamina = Irene->IreneData.CurrentStamina;
			Irene->ChangeStateAndLog(UDodgeWaterStartState::GetInstance());
		}
		if(StartWaterDodgeStamina != 0)
		{
			Irene->IreneAnim->StopAllMontages(0);
			bUseWaterDodge = true;
			Irene->IreneData.CurrentStamina -= Rate * GetWorld()->GetDeltaSeconds() * Irene->IreneData.Decrease_Speed;
			if(StartWaterDodgeStamina - 75 > Irene->IreneData.CurrentStamina || Irene->IreneData.CurrentStamina <= 0)
			{
				GetWorld()->GetTimerManager().SetTimer(StaminaWaitHandle, FTimerDelegate::CreateLambda([&]()
				{
					StaminaWaitHandle.Invalidate();
				}), 1, false);
			}
		}
	}
	else
	{
		StartWaterDodgeStamina = 0;
		bUseDodgeKey = false;
		// 켯다가 껏을 때
		if(bUseWaterDodge)
		{
			bUseWaterDodge = false;
			if(!DodgeWaitHandle.IsValid())
			{
				GetWorld()->GetTimerManager().SetTimer(DodgeWaitHandle, FTimerDelegate::CreateLambda([&]()
				 {
					 DodgeWaitHandle.Invalidate();
				 }), 1.0f, false);
			}
			Irene->ChangeStateAndLog(UDodgeWaterEndState::GetInstance());
		}
	}
}

void UIreneInputInstance::DialogAction()
{
		UPlayerHudWidget* PlayerHud = Irene->IreneUIManager->PlayerHud;

		switch (PlayerHud->GetDialogState())
		{
		case EDialogState::e_Set:
			PlayerHud->PlayDialog();
			break;
		case EDialogState::e_Playing:
			PlayerHud->PassDialog();
			break;
		case EDialogState::e_Complete:
			if (PlayerHud->ContinueDialog())
				PlayerHud->PlayDialog();
			else
				PlayerHud->ExitDialog();
			break;
		case EDialogState::e_Disable:
			break;
		default:
			break;
		}

}

void UIreneInputInstance::DialogSkip()
{
	if (bIsDialogOn) {
		UPlayerHudWidget* PlayerHud = Irene->IreneUIManager->PlayerHud;
		PlayerHud->SkipDialog();
	}

}

void UIreneInputInstance::MouseCursorKeyword()
{
	if (!Irene->IreneState->IsDeathState()&&!bIsDialogOn)
	{
		// 마우스 커서 숨기거나 보이게 하는 함수
		if (Irene->WorldController->bShowMouseCursor == false)
			Irene->WorldController->bShowMouseCursor = true;
		else
			Irene->WorldController->bShowMouseCursor = false;
	}
}
#pragma endregion Input

#pragma region UI
void UIreneInputInstance::PauseWidgetOn()
{
	if (Irene->IreneUIManager->GetIsPauseOnScreen())
	  	Irene->IreneUIManager->PauseWidgetOff();
	else
	{
		Irene->IreneState->SetState(UIdleState::GetInstance());
		Irene->IreneUIManager->PauseWidgetOn();
	}
	Irene->ActionEndChangeMoveState();
}

void UIreneInputInstance::RecoveryStaminaGauge(const float DeltaTime)const
{
	// 스테미나를 회복시키는 함수
	Irene->IreneData.CurrentStamina += DeltaTime * Irene->IreneData.Recovery_Speed;
	if(StaminaGaugeIsFull()) Irene->IreneData.CurrentStamina = Irene->IreneData.MaxStamina;
	Irene->IreneUIManager->OnStaminaChanged.Broadcast();
}
bool UIreneInputInstance::StaminaGaugeIsFull()const
{
	// 스테미나가 가득 찼는지 확인하는 함수
	return Irene->IreneData.CurrentStamina >= Irene->IreneData.MaxStamina ? true :false;
}
#pragma endregion UI

#pragma region CheckStateChange
bool UIreneInputInstance::CanJumpState() const
{
	if (!Irene->IreneState->IsJumpState()  && !Irene->IreneState->IsDodgeState() && !Irene->IreneState->IsDeathState() && !Irene->IreneState->IsChargeState())
			return true;
	return false;
}
bool UIreneInputInstance::CanRunState() const
{
	if (!Irene->IreneState->IsAttackState() && !Irene->IreneState->IsSkillState() && !Irene->IreneState->IsJumpState() && !Irene->IreneState->IsDeathState())
			return true;
	return false;
}
bool UIreneInputInstance::CanAttackState() const
{
	if (!Irene->IreneState->IsJumpState() && !Irene->IreneState->IsDodgeState() && !Irene->IreneState->IsDeathState())
		return true;
	return false;
}
#pragma endregion CheckStateChange

#pragma region GetSet
void UIreneInputInstance::SetStartMoveAutoTarget(const FVector SetPlayerPosVec, const FVector SetTargetPosVec)const
{
	Irene->IreneAttack->SetFollowTarget(true);
	Irene->IreneAttack->SetFollowTargetAlpha(0);
	Irene->IreneAttack->SetPlayerPosVec(SetPlayerPosVec);
	Irene->IreneAttack->SetTargetPosVec(SetTargetPosVec);	
}
void UIreneInputInstance::SetStopMoveAutoTarget()const
{
	Irene->IreneAttack->SetFollowTarget(false);
	Irene->IreneAttack->SetFollowTargetAlpha(0);
	Irene->IreneAttack->SetPlayerPosVec(FVector::ZeroVector);
	Irene->IreneAttack->SetTargetPosVec(FVector::ZeroVector);	
}
void UIreneInputInstance::FireCoolTime()
{
	if (FireCurCoolTime < FireMaxCoolTime)
	{
		FireCurCoolTime += CoolTimeRate;

	}
	else {
		bIsFireAttributeOn = true;
		FireCurCoolTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(FireStartTimer);

	}

	Irene->IreneUIManager->UpdateFireCool(FireCurCoolTime, FireMaxCoolTime);
	Irene->IreneUIManager->OnFireCoolChange.Broadcast();
}
void UIreneInputInstance::WaterCoolTime()
{
	if (WaterCurCoolTime < WaterMaxCoolTime)
	{
		WaterCurCoolTime += CoolTimeRate;

	}
	else {
		bIsWaterAttributeOn = true;
		WaterCurCoolTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(WaterStartTimer);

	}

	Irene->IreneUIManager->UpdateWaterCool(WaterCurCoolTime, WaterMaxCoolTime);
	Irene->IreneUIManager->OnWaterCoolChange.Broadcast();

}
void UIreneInputInstance::ThunderCoolTime()
{
	if (ThunderCurCoolTime < ThunderMaxCoolTime)
	{
		ThunderCurCoolTime += CoolTimeRate;;
	}
	else {
		bIsThunderAttributeOn = true;
		ThunderCurCoolTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(ElectricStartTimer);

	}
	Irene->IreneUIManager->UpdateThunderCool(ThunderCurCoolTime, ThunderMaxCoolTime);
	Irene->IreneUIManager->OnThunderCoolChange.Broadcast();

}

void UIreneInputInstance::FireSkillWait()
{
	FireSkillCoolTime += CoolTimeRate;

	if (FireSkillCoolTime > MaxFireSkillCoolTime) {
		bIsFireSkillOn = true;
		Irene->IreneUIManager->UpdateFireSkillCool(FireSkillCoolTime, MaxFireSkillCoolTime);
		Irene->IreneUIManager->OnFireSkillCoolChange.Broadcast();
		FireSkillCoolTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(FireSkillWaitHandle);
	}
	else {

		Irene->IreneUIManager->UpdateFireSkillCool(FireSkillCoolTime, MaxFireSkillCoolTime);
		Irene->IreneUIManager->OnFireSkillCoolChange.Broadcast();
	}
}
void UIreneInputInstance::WaterSkillWait()
{
	WaterSkillCoolTime += CoolTimeRate;

	if (WaterSkillCoolTime > MaxWaterSkillCoolTime) {
		bIsWaterSkillOn = true;
		Irene->IreneUIManager->UpdateWaterSkillCool(WaterSkillCoolTime, MaxWaterSkillCoolTime);
		Irene->IreneUIManager->OnWaterSkillCoolChange.Broadcast();
		WaterSkillCoolTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(WaterSkillWaitHandle);
	}
	{
		Irene->IreneUIManager->UpdateWaterSkillCool(WaterSkillCoolTime, MaxWaterSkillCoolTime);
		Irene->IreneUIManager->OnWaterSkillCoolChange.Broadcast();
	}
}
void UIreneInputInstance::ThunderSkillWait()
{
	ThunderSkillCoolTime += CoolTimeRate;
	if (ThunderSkillCoolTime > MaxThunderSkillCoolTime)
	{
		bIsThunderSkillOn = true;
		Irene->IreneUIManager->UpdateThunderSkillCool(ThunderSkillCoolTime, MaxThunderSkillCoolTime);
		Irene->IreneUIManager->OnThunderSkillCoolChange.Broadcast();
		ThunderSkillCoolTime = 0.0f;
		if (ThunderSkillCount < MaxThunderSkillCount)
		{
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(ThunderSkillWaitHandle);
		}
	}
	else
	{
		Irene->IreneUIManager->UpdateThunderSkillCool(ThunderSkillCoolTime, MaxThunderSkillCoolTime);
		Irene->IreneUIManager->OnThunderSkillCoolChange.Broadcast();
	}
}

#pragma endregion GetSet
