﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneInputInstance.h"
#include "IreneCharacter.h"
#include "IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneAttackInstance.h"
#include "IreneUIManager.h"

#include "Kismet/KismetMathLibrary.h"
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

	// 자동이동 방향 초기화
	MoveAutoDirection = FVector::ZeroVector;
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

	StaminaGauge = 150;
	StartWaterDodgeStamina = 0;

	bUseWaterDodge = false;
	bUseThunderDodge = false;
	ThunderDodgeTargetDir = FVector::ZeroVector;
}

#pragma region Move
void UIreneInputInstance::MoveForward()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		// 0: 전진, 2: 후진
		if (MoveKey[0] != 0 && MoveKey[0] < 3)
		{
			const FRotator Rotation = Irene->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			//Irene->SpringArmComp->CameraLagSpeed = 0;//Irene->IreneData.MaxCameraLagSpeed;
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			Irene->AddMovementInput(Direction);
		}
		if (MoveKey[2] != 0 && MoveKey[2] < 3)
		{
			const FRotator Rotation = Irene->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			//Irene->SpringArmComp->CameraLagSpeed = 0;//Irene->IreneData.MaxCameraLagSpeed;
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			Irene->AddMovementInput(Direction * -1);
		}
	}
}
void UIreneInputInstance::MoveRight()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		Irene->SpringArmComp->CameraLagSpeed = Irene->IreneData.MaxCameraLagSpeed;			

		// 1: 좌측, 3: 우측
		if (MoveKey[1] != 0 && MoveKey[1] < 3)
		{
			const FRotator Rotation = Irene->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			//Irene->SpringArmComp->CameraLagSpeed = 0;//Irene->IreneData.MaxCameraLagSpeed * 2;
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			Irene->AddMovementInput(Direction * -1);
		}
		if (MoveKey[3] != 0 && MoveKey[3] < 3)
		{
			const FRotator Rotation = Irene->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			//Irene->SpringArmComp->CameraLagSpeed = 0;//Irene->IreneData.MaxCameraLagSpeed * 2;
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			Irene->AddMovementInput(Direction);
		}
	}
}
void UIreneInputInstance::MoveStop()
{
	// 아무 키 입력이 없을 경우 정지 상태 지정
	if (Irene->IreneState->GetStateToString().Compare(FString("Idle")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
		{
			// if (Irene->IreneState->GetStateToString().Compare(FString("Sprint")) == 0)
			// {
			// 	Irene->IreneAnim->SetSprintStopAnim(true);
			// 	FTimerHandle TimerHandle;
			// 	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			// 		{
			// 			Irene->IreneAnim->SetSprintStopAnim(false);
			// 		}, 0.3f, false);
			// }
			Irene->ChangeStateAndLog(UIdleState::GetInstance());
		}
	}
	// 점프 상태 중 키입력에 따라 바닥에 도착할 경우 정지, 걷기, 달리기 상태 지정
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) == 0)
	{
		if (!Irene->GetCharacterMovement()->IsFalling())
		{
			Irene->ActionEndChangeMoveState();
			Irene->GetCharacterMovement()->GravityScale = 2;
		}
	}
}
void UIreneInputInstance::MoveAuto()
{
	// 이동 후 공격
	if (Irene->IreneAttack->GetFollowTarget())
	{
		const float TargetAlpha = Irene->IreneAttack->GetFollowTargetAlpha();
		Irene->IreneAttack->SetFollowTargetAlpha(TargetAlpha + GetWorld()->GetDeltaSeconds() * 2 * Irene->IreneData.TargetFollowSpeed);
		if (TargetAlpha >= 1)
			Irene->IreneAttack->SetFollowTargetAlpha(1);
		const FVector Target = FMath::Lerp(Irene->IreneAttack->GetPlayerPosVec(), Irene->IreneAttack->GetTargetPosVec(), Irene->IreneAttack->GetFollowTargetAlpha());
		Irene->GetCapsuleComponent()->SetRelativeLocation(Target);
		
		FString AnimName = "";
		if(Irene->IreneAnim->GetCurrentActiveMontage())
			AnimName = Irene->IreneAnim->GetCurrentActiveMontage()->GetName();
		if (FVector::Dist(Target, Irene->IreneAttack->GetTargetPosVec()) <= 50 && AnimName != FString("IreneThunderSkill_Montage"))
		{
			Irene->IreneAttack->DoAttack();
		}
	}
	// 전기 대쉬 이동
	if (bUseThunderDodge)
	{
		Irene->GetCharacterMovement()->Velocity = ThunderDodgeTargetDir*2*Irene->IreneData.ThunderDodgeSpeed;
	}	
	if (Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0)
	{
		if (MoveAutoDirection == FVector(0, 0, 0))
		{
			MoveAutoDirection += Irene->GetActorForwardVector();
			MoveAutoDirection.Normalize();
		}

		// 대쉬 도중 떨어지면 점프 상태로 강제 변화
		if (Irene->GetMovementComponent()->IsFalling())
		{
			MoveAutoDirection = FVector(0, 0, 0);
			GetWorld()->GetTimerManager().ClearTimer(MoveAutoWaitHandle);
			if (Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
			{
				Irene->IreneState->SetState(UJumpState::GetInstance());
				Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
			}
		}

		//if (Irene->IreneState->GetStateToString().Compare(FString("Dodge")) == 0)
			//Irene->AddMovementInput(MoveAutoDirection, Irene->IreneData.MoveSpeed);
	}
}

void UIreneInputInstance::StartJump()
{
	if (!Irene->GetCharacterMovement()->IsFalling() &&
		Irene->IreneState->GetStateToString().Compare(FString("Dodge")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		// // 키 입력을 바탕으로 점프 방향을 얻는다.
		// FVector Direction = FVector(0, 0, 0);
		// if (MoveKey[0] != 0)
		// {
		// 	Direction += Irene->CameraComp->GetForwardVector();
		// }
		// if (MoveKey[1] != 0)
		// {
		// 	Direction += Irene->CameraComp->GetRightVector() * -1;
		// }
		// if (MoveKey[2] != 0)
		// {
		// 	Direction += Irene->CameraComp->GetForwardVector() * -1;
		// }
		// if (MoveKey[3] != 0)
		// {
		// 	Direction += Irene->CameraComp->GetRightVector();
		// }
		// Direction.Normalize();

		Irene->GetMovementComponent()->Velocity = Irene->GetMovementComponent()->Velocity / Irene->IreneData.JumpDrag;

		bStartJump = true;
		Irene->bPressedJump = true;
		Irene->ChangeStateAndLog(UJumpState::GetInstance());
	}
}
void UIreneInputInstance::StopJump()
{
	Irene->bPressedJump = false;
}

#pragma region MoveInput
void UIreneInputInstance::MovePressedW()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		if (Irene->IreneState->GetStateToString().Compare(FString("Idle")) == 0)
		{
			Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->IreneData.RunMaxSpeed;
			Irene->ChangeStateAndLog(URunState::GetInstance());
		}
		MoveKey[0] = 1;
		if(Irene->GetCharacterMovement()->MaxWalkSpeed == 900)
			MoveKey[0] = 2;
	}
	else
		MoveKey[0] = 3;
}
void UIreneInputInstance::MovePressedA()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		if (Irene->IreneState->GetStateToString().Compare(FString("Idle")) == 0)
		{
			Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->IreneData.RunMaxSpeed;
			Irene->ChangeStateAndLog(URunState::GetInstance());
		}
		MoveKey[1] = 1;
		if(Irene->GetCharacterMovement()->MaxWalkSpeed == 900)
			MoveKey[1] = 2;
	}
	else
		MoveKey[1] = 3;
}
void UIreneInputInstance::MovePressedS()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		if (Irene->IreneState->GetStateToString().Compare(FString("Idle")) == 0)
		{
			Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->IreneData.RunMaxSpeed;
			Irene->ChangeStateAndLog(URunState::GetInstance());
		}
		MoveKey[2] = 1;
		if(Irene->GetCharacterMovement()->MaxWalkSpeed == 900)
			MoveKey[2] = 2;
	}
	else
		MoveKey[2] = 3;
}
void UIreneInputInstance::MovePressedD()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		if (Irene->IreneState->GetStateToString().Compare(FString("Idle")) == 0)
		{
			Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->IreneData.RunMaxSpeed;
			Irene->ChangeStateAndLog(URunState::GetInstance());
		}
		MoveKey[3] = 1;
		if(Irene->GetCharacterMovement()->MaxWalkSpeed == 900)
			MoveKey[3] = 2;
	}
	else
		MoveKey[3] = 3;
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
	if (Irene->WorldController->bShowMouseCursor == false &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
		Irene->AddControllerYawInput(Rate * Irene->IreneData.EDPI / 3);
}
void UIreneInputInstance::LookUp(float Rate)
{
	const float yaw = FRotator::NormalizeAxis(Irene->WorldController->GetControlRotation().Pitch) + Rate * Irene->IreneData.EDPI * Irene->WorldController->InputPitchScale;

	if (yaw < 50)
	{
		if (Irene->WorldController->bShowMouseCursor == false &&
			Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
			Irene->AddControllerPitchInput(Rate * Irene->IreneData.EDPI / 4);
	}
}

void UIreneInputInstance::LeftButton(float Rate)
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Fall")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Dodge")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		if (Rate >= 1.0 && !AttackWaitHandle.IsValid() && bUseRightButton == false)
		{
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
					if(Irene->IreneAttack->GetAttribute() != EAttributeKeyword::e_None)
					{
						//if (!(Irene->IreneAttack->FormGauge[AttributeForm]-NextTable->Gauge < NextTable->Gauge+Table->Gauge && Irene->IreneAnim->GetCurrentActiveMontage()))
							Irene->IreneData.IsComboInputOn = true;
					}
					else
						Irene->IreneData.IsComboInputOn = true;
				}
			}
			else
			{
				Irene->ChangeStateAndLog(UBasicAttackState::GetInstance());
				Irene->IreneAttack->AttackStartComboState();
				Irene->IreneAnim->PlayAttackMontage();

				Irene->IreneAnim->JumpToAttackMontageSection(Irene->IreneData.CurrentCombo);
				Irene->IreneData.IsAttacking = true;
			}
		}
	}
}
void UIreneInputInstance::RightButtonPressed()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Fall")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Dodge")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0 && !bUseLeftButton && !SkillWaitHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(SkillWaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			SkillWaitHandle.Invalidate();
		}) , 3, false);
		Irene->ChangeStateAndLog(UActionAttackState::GetInstance());
		IsCharging = true;
		ChargingTime = 0.0f;
		bUseRightButton = true;
		
		const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetActionAttackDataTableName()));
		
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		{
			if (AttackTable != nullptr && bUseRightButton)
			{
				Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;
				Irene->IreneAnim->PlaySkillAttackMontage();
			}
		}
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
		{
			if (AttackTable != nullptr && bUseRightButton)
			{
				const FVector CurrentPosVec = Irene->GetActorLocation();
				const FVector NowPosVec = Irene->GetActorLocation()+Irene->GetActorForwardVector()*400;

				Irene->GetMesh()->SetVisibility(false);
				Irene->Weapon->SetVisibility(false);
				Irene->IreneAttack->SetCurrentPosVec(CurrentPosVec);
				Irene->IreneAttack->SetNowPosVec(NowPosVec);
				Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerDodge"));

				SetStartMoveAutoTarget(CurrentPosVec, NowPosVec);
				
				Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;
				Irene->IreneAnim->PlaySkillAttackMontage();
			}
		}
	}
}
void UIreneInputInstance::RightButtonReleased()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Fall")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Dodge")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0 && !bUseLeftButton && bUseRightButton)
	{		
		const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetActionAttackDataTableName()));
		IsCharging = false;

		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
		{
			if (AttackTable != nullptr && bUseRightButton)
			{
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

void UIreneInputInstance::FireKeywordReleased()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		   Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		if(!FireStartTimer.IsValid() && Irene->IreneAttack->GetAttribute() != EAttributeKeyword::e_Fire)
			ChangeForm(EAttributeKeyword::e_Fire);
	}
}
void UIreneInputInstance::WaterKeywordReleased()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		   Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		if(!WaterStartTimer.IsValid() && Irene->IreneAttack->GetAttribute() != EAttributeKeyword::e_Water)
			ChangeForm(EAttributeKeyword::e_Water);
	}
}
void UIreneInputInstance::ElectricKeywordReleased()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		   Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{		
		if(!ElectricStartTimer.IsValid() && Irene->IreneAttack->GetAttribute() != EAttributeKeyword::e_Thunder)
			ChangeForm(EAttributeKeyword::e_Thunder);
	}
}
void UIreneInputInstance::ChangeForm(EAttributeKeyword Value)
{
	Irene->IreneAttack->SetAttribute(Value);

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
	GetWorld()->GetTimerManager().SetTimer(FireStartTimer, FTimerDelegate::CreateLambda([&]()
	{
		FireStartTimer.Invalidate();
	}) , Irene->IreneAttack->GetNameAtFormTimeDataTable(FName("Fire_Form"))->Gauge_C_Time, false);
	GetWorld()->GetTimerManager().SetTimer(WaterStartTimer, FTimerDelegate::CreateLambda([&]()
	{
		WaterStartTimer.Invalidate();
	}) , Irene->IreneAttack->GetNameAtFormTimeDataTable(FName("Water_Form"))->Gauge_C_Time, false);
	GetWorld()->GetTimerManager().SetTimer(ElectricStartTimer, FTimerDelegate::CreateLambda([&]()
	{
		ElectricStartTimer.Invalidate();
	}) , Irene->IreneAttack->GetNameAtFormTimeDataTable(FName("Electric_Form"))->Gauge_C_Time, false);
	Irene->IreneAnim->SetAttribute(Irene->IreneAttack->GetAttribute());
	Irene->FOnAttributeChange.Broadcast();
}

void UIreneInputInstance::DodgeKeyword()
{
	if (!Irene->GetMovementComponent()->IsFalling() &&
		Irene->IreneState->GetStateToString().Compare(FString("Dodge")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
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
			StartWaterDodgeStamina = StaminaGauge;
			Irene->ChangeStateAndLog(USprintState::GetInstance());
			if(WaterDodgeEffect == nullptr)
			{
				const auto PSAtk = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/Effect/VFX_Irene/PS_W_Dodge.PS_W_Dodge"));
				WaterDodgeEffect = UGameplayStatics::SpawnEmitterAttached(PSAtk, Irene->GetMesh(), TEXT("None"), Irene->GetActorLocation()+FVector(0,0,30),FRotator::ZeroRotator,FVector::OneVector,EAttachLocation::KeepWorldPosition,true,EPSCPoolMethod::None,true);
			}
		}
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder && StaminaGauge >= 37.5f && !ThunderDodgeWaitHandle.IsValid())
		{
			Irene->IreneAnim->StopAllMontages(0);
			StaminaGauge -= 37.5f;
			
			Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerDodge"));
			Irene->GetCharacterMovement()->MaxWalkSpeed = 99999999;
			bUseThunderDodge = true;
			Irene->ChangeStateAndLog(UDodgeState::GetInstance());
			const FRotator Rotation = Irene->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			
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
			
			 GetWorld()->GetTimerManager().SetTimer(ThunderDodgeWaitHandle, FTimerDelegate::CreateLambda([&]()
			 {
			 	Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
				bUseThunderDodge = false;
			 	Irene->ActionEndChangeMoveState();
			 	ThunderDodgeTargetDir = FVector::ZeroVector;
				 ThunderDodgeWaitHandle.Invalidate();
			 }), Irene->IreneData.ThunderDodgeTime, false);
		}
	}	
}
void UIreneInputInstance::WaterDodgeKeyword(float Rate)
{
	if(Rate >= 1.0f && Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water && StaminaGauge > 0 && !StaminaWaitHandle.IsValid())
	{
		Irene->IreneAnim->StopAllMontages(0);
		Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerDodge"));
		Irene->GetMesh()->SetRelativeLocation(FVector(0, 0, -180));
		Irene->GetMesh()->SetVisibility(false);
		Irene->Weapon->SetVisibility(false);
		bUseWaterDodge = true;
		StaminaGauge -= Rate/10;
		if(StartWaterDodgeStamina-75 > StaminaGauge || StaminaGauge <= 0)
		{
			GetWorld()->GetTimerManager().SetTimer(StaminaWaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				StaminaWaitHandle.Invalidate();
			}), 1, false);
		}
	}
	else
	{
		Irene->GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
		StartWaterDodgeStamina = StaminaGauge;
		if(bUseWaterDodge)
		{
			bUseWaterDodge = false;
		}
		if(WaterDodgeEffect != nullptr)
		{
			WaterDodgeEffect->DestroyComponent(true);
			WaterDodgeEffect = nullptr;
		}
		FString AnimName = "";
		if(Irene->IreneAnim->GetCurrentActiveMontage())
			AnimName = Irene->IreneAnim->GetCurrentActiveMontage()->GetName();
		if(AnimName != FString("IreneThunderSkill_Montage") && !bUseThunderDodge)
		{
			Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
			Irene->GetMesh()->SetVisibility(true);
			Irene->Weapon->SetVisibility(true);
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

void UIreneInputInstance::RecoveryStaminaGauge(float DeltaTime)
{
	StaminaGauge += DeltaTime * 5;
	if(StaminaGaugeIsFull()) StaminaGauge = 150;
}
bool UIreneInputInstance::StaminaGaugeIsFull()const
{
	return StaminaGauge >= 150 ? true :false;
}
#pragma endregion UI

#pragma region GetSet
void UIreneInputInstance::SetStartMoveAutoTarget(const FVector SetPlayerPosVec, const FVector SetTargetPosVec)
{
	Irene->IreneAttack->SetFollowTarget(true);
	Irene->IreneAttack->SetFollowTargetAlpha(0);
	Irene->IreneAttack->SetPlayerPosVec(SetPlayerPosVec);
	Irene->IreneAttack->SetTargetPosVec(SetTargetPosVec);	
}
void UIreneInputInstance::SetStopMoveAutoTarget()
{
	Irene->IreneAttack->SetFollowTarget(false);
	Irene->IreneAttack->SetFollowTargetAlpha(0);
	Irene->IreneAttack->SetPlayerPosVec(FVector::ZeroVector);
	Irene->IreneAttack->SetTargetPosVec(FVector::ZeroVector);	
}
#pragma endregion GetSet
