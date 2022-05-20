// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneInputInstance.h"
#include "IreneCharacter.h"
#include "IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneAttackInstance.h"
#include "IreneUIManager.h"

#include "DrawDebugHelpers.h"

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
	bUseLeftButton = false;
	bUseRightButton = false;

	StartWaterDodgeStamina = 0;

	bUseWaterDodge = false;
	ThunderDodgeTargetDir = FVector::ZeroVector;

	ThunderSkillCount = 2;
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

void UIreneInputInstance::MoveAuto()const
{
	// 이동 후 공격
	if (Irene->IreneAttack->GetFollowTarget())
	{
		const float TargetAlpha = Irene->IreneAttack->GetFollowTargetAlpha();
		Irene->IreneAttack->SetFollowTargetAlpha(TargetAlpha + GetWorld()->GetDeltaSeconds() * 2 * Irene->IreneData.TargetFollowSpeed);
		if (TargetAlpha >= 1)
			Irene->IreneAttack->SetFollowTargetAlpha(1);
		const FVector Target = FMath::Lerp(Irene->IreneAttack->GetPlayerPosVec(), Irene->IreneAttack->GetTargetPosVec(), Irene->IreneAttack->GetFollowTargetAlpha());
		Irene->GetCapsuleComponent()->SetRelativeLocation(Target, true);
		
		FString AnimName = "";
		if(Irene->IreneAnim->GetCurrentActiveMontage())
			AnimName = Irene->IreneAnim->GetCurrentActiveMontage()->GetName();
		if (FVector::Dist(Target, Irene->IreneAttack->GetTargetPosVec()) <= 50 && AnimName != FString("IreneThunderSkill_Montage"))
		{
			Irene->IreneAttack->DoAttack();
		}
	}
}

void UIreneInputInstance::StartJump()
{
	if (CanJumpState())
	{
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
	if (CanRunState())
	{
		MoveKey[Value] = 1;
		if(Irene->GetCharacterMovement()->MaxWalkSpeed == Irene->IreneData.SprintMaxSpeed)
			MoveKey[Value] = 2;
		if (Irene->IreneState->IsIdleState())
		{
			Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->IreneData.RunMaxSpeed;
			Irene->ChangeStateAndLog(URunLoopState::GetInstance());
		}		
	}
	else
		MoveKey[Value] = 3;
}

void UIreneInputInstance::MovePressedW()
{
	MovePressedKey(0);
}
void UIreneInputInstance::MovePressedA()
{
	MovePressedKey(1);
}
void UIreneInputInstance::MovePressedS()
{
	MovePressedKey(2);
}
void UIreneInputInstance::MovePressedD()
{
	MovePressedKey(3);
}

void UIreneInputInstance::MoveReleasedW()
{
	MoveKey[0] = 0;
}
void UIreneInputInstance::MoveReleasedA()
{
	MoveKey[1] = 0;
}
void UIreneInputInstance::MoveReleasedS()
{
	MoveKey[2] = 0;
}
void UIreneInputInstance::MoveReleasedD()
{
	MoveKey[3] = 0;
}
#pragma endregion MoveInput

#pragma region Input
void UIreneInputInstance::Turn(float Rate)
{
	if (Irene->WorldController->bShowMouseCursor == false && !Irene->IreneState->IsDeathState())
		Irene->AddControllerYawInput(Rate * Irene->IreneData.EDPI / 2);
}
void UIreneInputInstance::LookUp(float Rate)
{
	const float Yaw = FRotator::NormalizeAxis(Irene->WorldController->GetControlRotation().Pitch) + Rate * Irene->IreneData.EDPI * Irene->WorldController->InputPitchScale;

	if (Yaw < 50)
	{
		if (Irene->WorldController->bShowMouseCursor == false && !Irene->IreneState->IsDeathState())
			Irene->AddControllerPitchInput(Rate * Irene->IreneData.EDPI / 4.5f);
	}
}

void UIreneInputInstance::LeftButton(float Rate)
{
	if (CanAttackState() && !AttackWaitHandle.IsValid() && bUseRightButton == false)
	{
		if (Rate >= 1.0)
		{
			Irene->IreneAttack->SetAttackState();

			const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetBasicAttackDataTableName()));
			if(!AttackTable)
			{
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
					Irene->IreneData.CurrentCombo += 1;
					Irene->IreneAnim->JumpToAttackMontageSection(Irene->IreneData.CurrentCombo);
				}
			}
			else
			{
				Irene->IreneAttack->AttackStartComboState();
				Irene->IreneAnim->PlayAttackMontage();

				Irene->IreneAnim->NextToAttackMontageSection(Irene->IreneData.CurrentCombo);
				Irene->IreneAnim->JumpToAttackMontageSection(Irene->IreneData.CurrentCombo);
				Irene->IreneData.IsAttacking = true;
			}
		}
	}
}
void UIreneInputInstance::RightButtonPressed()
{
	if (CanAttackState() && !bUseLeftButton && !SkillWaitHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(SkillWaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			SkillWaitHandle.Invalidate();
		}) , 3, false);

		IsCharging = true;
		ChargingTime = 0.0f;
		bUseRightButton = true;
		
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
		{
			Irene->IreneAttack->SetSkillState();
			const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetActionAttackDataTableName()));

			if (AttackTable != nullptr && bUseRightButton)
			{
				Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;
				Irene->ChangeStateAndLog(UCharge1State::GetInstance());
			}
		}
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		{
			Irene->IreneAttack->SetSkillState();
			const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetActionAttackDataTableName()));

			if (AttackTable != nullptr && bUseRightButton)
			{
				Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;
				Irene->IreneAnim->PlaySkillAttackMontage();
			}
		}
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
		{
			if(ThunderSkillCount > 0)
			{
				Irene->IreneAttack->SetSkillState();
				const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetActionAttackDataTableName()));

				if (AttackTable != nullptr && bUseRightButton)
				{
					ThunderSkillCount--;
					Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;
					Irene->IreneAnim->PlaySkillAttackMontage();
					if(ThunderSkillCount < 2 && !ThunderSkillWaitHandle.IsValid())
					{
						GetWorld()->GetTimerManager().SetTimer(ThunderSkillWaitHandle, FTimerDelegate::CreateLambda([&]()
						{
							ThunderSkillCount++;
							if(ThunderSkillCount == 2)
							{
								GetWorld()->GetTimerManager().ClearTimer(ThunderSkillWaitHandle);
								ThunderSkillWaitHandle.Invalidate();
							}
						}) , 10, true);					
					}
				}
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
	if (CanAttackState() && !bUseLeftButton && bUseRightButton)
	{
		const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetActionAttackDataTableName()));

		IsCharging = false;

		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
		{
			if (AttackTable != nullptr && bUseRightButton)
			{
				Irene->ChangeStateAndLog(USkillFireStartState::GetInstance());
				if(ChargingTime > AttackTable->Charge_Time_3/100.0f)
				{
					Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_3;
					Irene->IreneAnim->PlaySkillAttackMontage();
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
		ChargingTime = 0.0f;
	}
}

void UIreneInputInstance::MouseWheel(float Rate)
{
	Irene->SpringArmComp->TargetArmLength -= Rate * Irene->IreneData.MouseWheelSpeed;
	Irene->SpringArmComp->TargetArmLength = FMath::Clamp(Irene->SpringArmComp->TargetArmLength, Irene->IreneData.MinFollowCameraZPosition, Irene->IreneData.MaxFollowCameraZPosition);
}

void UIreneInputInstance::AttributeKeywordReleased(const EAttributeKeyword Attribute)
{
	if (!Irene->IreneState->IsAttackState() && !Irene->IreneState->IsSkillState() && !Irene->IreneState->IsDeathState() && Irene->IreneAttack->GetAttribute() != Attribute)
	{
		if(Attribute == EAttributeKeyword::e_Fire && !FireStartTimer.IsValid())
			ChangeForm(Attribute);
		if(Attribute == EAttributeKeyword::e_Water && !WaterStartTimer.IsValid())
			ChangeForm(Attribute);
		if(Attribute == EAttributeKeyword::e_Thunder && !ElectricStartTimer.IsValid())
			ChangeForm(Attribute);
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
	GetWorld()->GetTimerManager().SetTimer(FireStartTimer, FTimerDelegate::CreateLambda([&]()
	{
		FireStartTimer.Invalidate();
	}) , 10, false);
	GetWorld()->GetTimerManager().SetTimer(WaterStartTimer, FTimerDelegate::CreateLambda([&]()
	{
		WaterStartTimer.Invalidate();
	}) , 10, false);
	GetWorld()->GetTimerManager().SetTimer(ElectricStartTimer, FTimerDelegate::CreateLambda([&]()
	{
		ElectricStartTimer.Invalidate();
	}) , 10, false);	
}

void UIreneInputInstance::DodgeKeyword()
{
	if (!Irene->GetMovementComponent()->IsFalling() && !Irene->IreneState->IsDodgeState() && !Irene->IreneState->IsDeathState())
	{
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
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		{
			StartWaterDodgeStamina = Irene->IreneData.CurrentStamina;
			Irene->ChangeStateAndLog(UDodgeWaterStartState::GetInstance());
			if(WaterDodgeEffect == nullptr)
			{
				const auto PSAtk = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/Effect/VFX_Irene/PS_W_Dodge.PS_W_Dodge"));
				WaterDodgeEffect = UGameplayStatics::SpawnEmitterAttached(PSAtk, Irene->GetMesh(), TEXT("None"), Irene->GetActorLocation()+FVector(0,0,-70),FRotator::ZeroRotator,FVector::OneVector,EAttachLocation::KeepWorldPosition,true,EPSCPoolMethod::None,true);
			}
		}
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder && Irene->IreneData.CurrentStamina >= 37.5f)
		{
			Irene->IreneAnim->StopAllMontages(0);
			Irene->IreneData.CurrentStamina -= 37.5f;
			Irene->ChangeStateAndLog(UDodgeThunderStartState::GetInstance());

			const FRotator Rotation = Irene->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			ThunderDodgeTargetDir = FVector::ZeroVector;

			if (MoveKey[0] != 0 && MoveKey[0] < 3)
			{
				ThunderDodgeTargetDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			}
			if (MoveKey[2] != 0 && MoveKey[2] < 3)
			{
				ThunderDodgeTargetDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X)*-1;
			}
			if (MoveKey[1] != 0 && MoveKey[1] < 3)
			{
				ThunderDodgeTargetDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y)*-1;
			}
			if (MoveKey[3] != 0 && MoveKey[3] < 3)
			{
				ThunderDodgeTargetDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			}
			if(ThunderDodgeTargetDir == FVector::ZeroVector)
				ThunderDodgeTargetDir = Irene->GetActorForwardVector();
			ThunderDodgeTargetDir.Normalize();

			FVector Target;
			if(!ThunderDodgeWaitHandle.IsValid())
				Target = Irene->GetActorLocation() + ThunderDodgeTargetDir*Irene->IreneData.FirstThunderDodgeSpeed;
			else
				Target = Irene->GetActorLocation() + ThunderDodgeTargetDir*Irene->IreneData.DoubleThunderDodgeSpeed;
			Irene->SetActorRelativeLocation(Target,true,nullptr,ETeleportType::TeleportPhysics);
			ThunderDodgeTargetDir = FVector::ZeroVector;
			Irene->ActionEndChangeMoveState();

			 GetWorld()->GetTimerManager().SetTimer(ThunderDodgeWaitHandle, FTimerDelegate::CreateLambda([&]()
			 {
				 ThunderDodgeWaitHandle.Invalidate();
			 }), Irene->IreneData.ThunderDodgeTime, false);
		}
	}	
}
void UIreneInputInstance::WaterDodgeKeyword(float Rate)
{
	if(Rate >= 1.0f && Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water && Irene->IreneData.CurrentStamina > 0 && !StaminaWaitHandle.IsValid())
	{
		Irene->IreneAnim->StopAllMontages(0);
		bUseWaterDodge = true;
		Irene->IreneData.CurrentStamina -= Rate/5;
		if(StartWaterDodgeStamina-75 > Irene->IreneData.CurrentStamina || Irene->IreneData.CurrentStamina <= 0)
		{
			GetWorld()->GetTimerManager().SetTimer(StaminaWaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				StaminaWaitHandle.Invalidate();
			}), 1, false);
		}
	}
	else
	{
		StartWaterDodgeStamina = Irene->IreneData.CurrentStamina;
		if(bUseWaterDodge)
		{
			bUseWaterDodge = false;
			Irene->ChangeStateAndLog(UDodgeWaterEndState::GetInstance());
		}
		if(WaterDodgeEffect != nullptr)
		{
			WaterDodgeEffect->DestroyComponent(true);
			WaterDodgeEffect = nullptr;
		}
	}
}

void UIreneInputInstance::MouseCursorKeyword()
{
	if (Irene->WorldController->bShowMouseCursor == false)
		Irene->WorldController->bShowMouseCursor = true;
	else
		Irene->WorldController->bShowMouseCursor = false;
}
#pragma endregion Input

#pragma region UI
void UIreneInputInstance::PauseWidgetOn()
{
	for (int i = 0; i < MoveKey.Num(); i++)
	{
		MoveKey[i] = 0;
	}
	Irene->IreneState->SetState(UIdleState::GetInstance());
	Irene->IreneUIManager->PauseWidgetOn();
}

void UIreneInputInstance::RecoveryStaminaGauge(const float DeltaTime)const
{
	Irene->IreneData.CurrentStamina += DeltaTime * 5;
	if(StaminaGaugeIsFull()) Irene->IreneData.CurrentStamina = Irene->IreneData.MaxStamina;
	Irene->IreneUIManager->OnStaminaChanged.Broadcast();
}
bool UIreneInputInstance::StaminaGaugeIsFull()const
{
	return Irene->IreneData.CurrentStamina >= Irene->IreneData.MaxStamina ? true :false;
}
#pragma endregion UI

#pragma region CheckStateChange
bool UIreneInputInstance::CanJumpState() const
{
	if (!Irene->GetCharacterMovement()->IsFalling() && !Irene->IreneState->IsAttackState() && !Irene->IreneState->IsSkillState() && !Irene->IreneState->IsDodgeState() && !Irene->IreneState->IsDeathState())
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
#pragma endregion GetSet
