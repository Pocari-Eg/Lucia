// Fill out your copyright notice in the Description page of Project Settings.


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
			Irene->SpringArmComp->CameraLagSpeed = Irene->IreneData.MaxCameraLagSpeed;
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			Irene->AddMovementInput(Direction, Irene->IreneData.MoveSpeed);
		}
		if (MoveKey[2] != 0 && MoveKey[2] < 3)
		{
			const FRotator Rotation = Irene->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			Irene->SpringArmComp->CameraLagSpeed = Irene->IreneData.MaxCameraLagSpeed;
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			Irene->AddMovementInput(Direction * -1, Irene->IreneData.MoveSpeed);
		}
	}
}
void UIreneInputInstance::MoveRight()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		// 1: 좌측, 3: 우측
		if (MoveKey[1] != 0 && MoveKey[1] < 3)
		{
			const FRotator Rotation = Irene->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			Irene->SpringArmComp->CameraLagSpeed = Irene->IreneData.MaxCameraLagSpeed * 2;
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			Irene->AddMovementInput(Direction * -1, Irene->IreneData.MoveSpeed);
		}
		if (MoveKey[3] != 0 && MoveKey[3] < 3)
		{
			const FRotator Rotation = Irene->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			Irene->SpringArmComp->CameraLagSpeed = Irene->IreneData.MaxCameraLagSpeed * 2;
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			Irene->AddMovementInput(Direction, Irene->IreneData.MoveSpeed);
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
			if (Irene->IreneState->GetStateToString().Compare(FString("Sprint")) == 0)
			{
				Irene->IreneAnim->SetSprintStopAnim(true);
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
					{
						Irene->IreneAnim->SetSprintStopAnim(false);
					}, 0.3f, false);
			}
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
	if (Irene->IreneAttack->bFollowTarget)
	{
		Irene->IreneAttack->FollowTargetAlpha += GetWorld()->GetDeltaSeconds() * 2 * Irene->IreneData.TargetFollowSpeed;
		if (Irene->IreneAttack->FollowTargetAlpha >= 1)
			Irene->IreneAttack->FollowTargetAlpha = 1;
		const FVector tar = FMath::Lerp(Irene->IreneAttack->PlayerPosVec, Irene->IreneAttack->TargetPosVec, Irene->IreneAttack->FollowTargetAlpha);
		Irene->GetCapsuleComponent()->SetRelativeLocation(tar);

		if (FVector::Dist(tar, Irene->IreneAttack->TargetPosVec) <= 50)
		{
			Irene->IreneAttack->DoAttack();
		}
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
			Irene->IreneData.MoveSpeed = 1.0f;
			MoveAutoDirection = FVector(0, 0, 0);
			GetWorld()->GetTimerManager().ClearTimer(MoveAutoWaitHandle);
			if (Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
			{
				Irene->IreneState->SetState(UJumpState::GetInstance());
				//Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
			}
		}

		if (Irene->IreneState->GetStateToString().Compare(FString("Dodge")) == 0)
			Irene->AddMovementInput(MoveAutoDirection, Irene->IreneData.MoveSpeed);
	}
}

void UIreneInputInstance::StartJump()
{
	if (!Irene->GetCharacterMovement()->IsFalling() &&
		Irene->IreneState->GetStateToString().Compare(FString("Dodge")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		// 키 입력을 바탕으로 점프 방향을 얻는다.
		FVector Direction = FVector(0, 0, 0);
		if (MoveKey[0] != 0)
		{
			Direction += Irene->CameraComp->GetForwardVector();
		}
		if (MoveKey[1] != 0)
		{
			Direction += Irene->CameraComp->GetRightVector() * -1;
		}
		if (MoveKey[2] != 0)
		{
			Direction += Irene->CameraComp->GetForwardVector() * -1;
		}
		if (MoveKey[3] != 0)
		{
			Direction += Irene->CameraComp->GetRightVector();
		}
		Direction.Normalize();

		Irene->GetMovementComponent()->Velocity = Irene->GetMovementComponent()->Velocity / Irene->IreneData.JumpDrag;

		Irene->bPressedJump = true;
		bStartJump = true;
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
	}
	else
		MoveKey[3] = 3;
}

void UIreneInputInstance::MoveDoubleClickW()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		MoveKey[0] = 2;
		Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->IreneData.SprintMaxSpeed;
		Irene->ChangeStateAndLog(USprintState::GetInstance());
		Irene->IreneData.MoveSpeed = 2;
	}
	else
		MoveKey[0] = 4;
}
void UIreneInputInstance::MoveDoubleClickA()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		MoveKey[1] = 2;
		Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->IreneData.SprintMaxSpeed;
		Irene->ChangeStateAndLog(USprintState::GetInstance());
		Irene->IreneData.MoveSpeed = 2;
	}
	else
		MoveKey[1] = 4;
}
void UIreneInputInstance::MoveDoubleClickS()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		MoveKey[2] = 2;
		Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->IreneData.SprintMaxSpeed;
		Irene->ChangeStateAndLog(USprintState::GetInstance());
		Irene->IreneData.MoveSpeed = 2;
	}
	else
		MoveKey[2] = 4;
}
void UIreneInputInstance::MoveDoubleClickD()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		MoveKey[3] = 2;
		Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->IreneData.SprintMaxSpeed;
		Irene->ChangeStateAndLog(USprintState::GetInstance());
		Irene->IreneData.MoveSpeed = 2;
	}
	else
		MoveKey[3] = 4;
}

void UIreneInputInstance::MoveReleasedW()
{
	MoveKey[0] = 0;
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
	if (MoveKey[1] != 2 && MoveKey[2] != 2 && MoveKey[3] != 2)
		Irene->IreneData.MoveSpeed = 1;
}
void UIreneInputInstance::MoveReleasedA()
{
	MoveKey[1] = 0;
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
	if (MoveKey[0] != 2 && MoveKey[2] != 2 && MoveKey[3] != 2)
		Irene->IreneData.MoveSpeed = 1;
}
void UIreneInputInstance::MoveReleasedS()
{
	MoveKey[2] = 0;
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
	if (MoveKey[0] != 2 && MoveKey[1] != 2 && MoveKey[3] != 2)
		Irene->IreneData.MoveSpeed = 1;
}
void UIreneInputInstance::MoveReleasedD()
{
	MoveKey[3] = 0;
	// 다른 키 중 달리기가 없어야 걷기 속도로 움직인다.
	if (MoveKey[0] != 2 && MoveKey[1] != 2 && MoveKey[2] != 2)
		Irene->IreneData.MoveSpeed = 1;
}
#pragma endregion MoveInput

#pragma region Input
void UIreneInputInstance::Turn(float Rate)
{
	if (Irene->WorldController->bShowMouseCursor == false &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
		Irene->AddControllerYawInput(Rate * Irene->IreneData.EDPI);
}
void UIreneInputInstance::LookUp(float Rate)
{
	const float yaw = FRotator::NormalizeAxis(Irene->WorldController->GetControlRotation().Pitch) + Rate * Irene->IreneData.EDPI * Irene->WorldController->InputPitchScale;

	if (yaw < 50)
	{
		if (Irene->WorldController->bShowMouseCursor == false &&
			Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
			Irene->AddControllerPitchInput(Rate * Irene->IreneData.EDPI);
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
			}
			else
			{
				Irene->ChangeStateAndLog(UBasicAttackState::GetInstance());
				Irene->IreneAttack->AttackStartComboState();
				Irene->IreneUIManager->AttackSound->SetParameter("Attributes", 0.0f);
				Irene->IreneAnim->PlayAttackMontage();

				Irene->IreneAnim->JumpToAttackMontageSection(Irene->IreneData.CurrentCombo);
				Irene->IreneData.IsAttacking = true;
			}
		}
	}
}
void UIreneInputInstance::RightButton(float Rate)
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Jump")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Fall")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Dodge")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		const FAttackDataTable* Table = Irene->IreneAttack->GetNameAtDataTable(FName("ActionKeyword_1_F"));
		if (Table != nullptr)
		{
			if (Rate >= 1.0 && !AttackWaitHandle.IsValid() && bUseLeftButton == false && Irene->IreneData.CurrentMP >= Table->MANA)
			{
				bUseRightButton = true;
				// 마우스 오른쪽 누르고 있을 때 연속공격 지연 시간(한번에 여러번 공격 인식 안하도록 함)
				constexpr float WaitTime = 0.15f;

				GetWorld()->GetTimerManager().SetTimer(AttackWaitHandle, FTimerDelegate::CreateLambda([&]()
					{
						AttackWaitHandle.Invalidate();
					}), WaitTime, false);

				if (Irene->IreneData.IsAttacking)
				{
					if (Irene->IreneData.CanNextCombo)
					{
						if (!(Irene->IreneData.CurrentMP == Table->MANA && Irene->IreneAnim->GetCurrentActiveMontage()))
							Irene->IreneData.IsComboInputOn = true;
					}
				}
				else
				{
					Irene->ChangeStateAndLog(UActionAttackState::GetInstance());
					Irene->IreneAttack->AttackStartComboState();

					switch (Irene->IreneAttack->Attribute)
					{
					case EAttributeKeyword::e_None:
						break;
					case EAttributeKeyword::e_Fire:
						Irene->IreneUIManager->AttackSound->SetParameter("Attributes", 1.0f);
						break;
					case EAttributeKeyword::e_Water:
						Irene->IreneUIManager->AttackSound->SetParameter("Attributes", 2.0f);
						break;
					case EAttributeKeyword::e_Thunder:
						Irene->IreneUIManager->AttackSound->SetParameter("Attributes", 3.0f);
						break;
					default:
						break;
					}

					Irene->IreneAnim->PlayEffectAttackMontage();
					Irene->IreneAnim->JumpToEffectAttackMontageSection(Irene->IreneData.CurrentCombo);
					Irene->IreneData.IsAttacking = true;
				}
			}
		}
	}
}
void UIreneInputInstance::RightButtonPressed()
{
	/*
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Fall")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Dodge")) != 0 &&
		CharacterState->getStateToString().Compare(FString("BasicAttack")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		ChangeStateAndLog(AttackState::getInstance());
		IsCharging = true;
		ChargingTime = 0.0f;
	}
	*/
}
void UIreneInputInstance::RightButtonReleased()
{
	/*
	if (CharacterState->getStateToString().Compare(FString("Jump")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Fall")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Dodge")) != 0 &&
		CharacterState->getStateToString().Compare(FString("Death")) != 0)
	{
		IsCharging = false;
		if(ChargingTime > 7.0f)
		{
			CharacterDataStruct.Strength = 100;
			IreneAnim->PlayEffectAttackMontage();
		}
		else if(ChargingTime > 4.0f)
		{
			CharacterDataStruct.Strength = 60;
			IreneAnim->PlayEffectAttackMontage();
		}
		else if (ChargingTime > 1.0f)
		{
			CharacterDataStruct.Strength = 40;
			IreneAnim->PlayEffectAttackMontage();
		}
		else
		{
			CharacterDataStruct.Strength = 5;
			IreneAnim->PlayEffectAttackMontage();
		}
		ChargingTime = 0.0f;
	}*/
}

void UIreneInputInstance::MouseWheel(float Rate)
{
	Irene->SpringArmComp->TargetArmLength -= Rate * Irene->IreneData.MouseWheelSpeed;
	Irene->SpringArmComp->TargetArmLength = FMath::Clamp(Irene->SpringArmComp->TargetArmLength, Irene->IreneData.MinFollowCameraZPosition, Irene->IreneData.MaxFollowCameraZPosition);
}

void UIreneInputInstance::MainKeyword()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0)
	{
		//속상변환 차례대로 속성이 변환
		switch (Irene->IreneAttack->Attribute)
		{
		case EAttributeKeyword::e_Fire:
			Irene->IreneUIManager->PlayerHud->WaterAttributesOn();
			Irene->IreneAttack->Attribute = EAttributeKeyword::e_Water;
			break;
		case EAttributeKeyword::e_Water:
			Irene->IreneUIManager->PlayerHud->ThunderAttributesOn();
			Irene->IreneAttack->Attribute = EAttributeKeyword::e_Thunder;
			break;
		case EAttributeKeyword::e_Thunder:
			Irene->IreneUIManager->PlayerHud->FireAttributesOn();
			Irene->IreneAttack->Attribute = EAttributeKeyword::e_Fire;
			break;
		default:
			break;
		}
		Irene->FOnAttributeChange.Broadcast();
		Irene->IreneAnim->SetAttribute(Irene->IreneAttack->Attribute);
	}
}

void UIreneInputInstance::DodgeKeyword()
{
	if (!Irene->GetMovementComponent()->IsFalling() &&
		Irene->IreneState->GetStateToString().Compare(FString("Dodge")) != 0 &&
		Irene->IreneState->GetStateToString().Compare(FString("Death")) != 0)
	{
		Irene->IreneAnim->StopAllMontages(0);
		//Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerDodge"));

		constexpr float WaitTime = 0.9f; //시간을 설정
		Irene->GetCharacterMovement()->MaxWalkSpeed = Irene->IreneData.SprintMaxSpeed;
		
		FVector ForwardVec = Irene->WorldController->GetControlRotation().Vector();
		ForwardVec.Z = 0;
		ForwardVec.Normalize();
		
		if(Irene->IreneState->GetStateToString().Compare(FString("BasicAttack")) != 0)
		{
			MoveAutoDirection = FVector::ZeroVector;

			// w키나 아무방향 없으면 정면으로 이동
			if (MoveKey[0] != 0 || (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0))
			{
				MoveAutoDirection += ForwardVec;
			}
			if (MoveKey[1] != 0)
			{
				MoveAutoDirection += Irene->CameraComp->GetRightVector()*-1;
			}
			if (MoveKey[2] != 0)
			{
				MoveAutoDirection += -1 * ForwardVec;
			}
			if (MoveKey[3] != 0)
			{
				MoveAutoDirection += Irene->CameraComp->GetRightVector();
			}
			MoveAutoDirection.Normalize();
		}
		else
		{
			MoveAutoDirection = FVector::ZeroVector;
			// w키나 아무방향 없으면 정면으로 이동
			if (MoveKey[0] != 0 || (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0))
			{
				MoveAutoDirection += ForwardVec;
			}
			if (MoveKey[1] != 0)
			{
				MoveAutoDirection += Irene->CameraComp->GetRightVector()*-1;
			}
			if (MoveKey[2] != 0)
			{
				MoveAutoDirection += -1 * ForwardVec;
			}
			if (MoveKey[3] != 0)
			{
				MoveAutoDirection += Irene->CameraComp->GetRightVector();
			}
			MoveAutoDirection.Normalize();
		}

		const float z = UKismetMathLibrary::FindLookAtRotation(Irene->GetActorLocation(), Irene->GetActorLocation() + MoveAutoDirection).Yaw;
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0.0f, z, 0.0f));

		GetWorld()->GetTimerManager().SetTimer(MoveAutoWaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				// 도중에 추락 안하고 정상적으로 진행됬을 때
				if (Irene->IreneState->GetStateToString().Compare(FString("Dodge")) == 0)
				{
					Irene->ActionEndChangeMoveState();
					//Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
				}
			}), WaitTime, false);
		Irene->ChangeStateAndLog(UDodgeState::GetInstance());
	}
	if (Irene->GetMovementComponent()->IsFalling())
	{
		if (!IsFallingRoll)
		{
			IsFallingRoll = true;
			FVector ForwardVec = Irene->WorldController->GetControlRotation().Vector();
			ForwardVec.Z = 0;
			ForwardVec.Normalize();
			
			MoveAutoDirection = FVector::ZeroVector;
			// w키나 아무방향 없으면 정면으로 이동
			if (MoveKey[0] != 0 || (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0))
			{
				MoveAutoDirection += ForwardVec;
			}
			if (MoveKey[1] != 0)
			{
				MoveAutoDirection += Irene->CameraComp->GetRightVector()*-1;
			}
			if (MoveKey[2] != 0)
			{
				MoveAutoDirection += -1 * ForwardVec;
			}
			if (MoveKey[3] != 0)
			{
				MoveAutoDirection += Irene->CameraComp->GetRightVector();
			}
			MoveAutoDirection.Normalize();
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