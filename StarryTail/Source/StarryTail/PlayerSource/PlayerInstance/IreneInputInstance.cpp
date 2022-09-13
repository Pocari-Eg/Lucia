// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneInputInstance.h"

#include "GeomTools.h"
#include "../IreneCharacter.h"
#include "../PlayerFSM/IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneAttackInstance.h"
#include "IreneUIManager.h"
#include "MovieSceneTracksComponentTypes.h"
#include "../../STGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

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

	bLeftButtonPressed = false;
	bRightButtonPressed = false;
	bUseLeftButton = true;
	bUseRightButton = true;
	
	bReAttack = false;
	
	// 추락 중 구르기 입력 초기화
	IsFallingRoll = false;
	
	FireCurCoolTime = 0.0f;
	WaterCurCoolTime = 0.0f;
	ThunderCurCoolTime = 0.0f;
	
	bIsFireAttributeOn = true;
	bIsWaterAttributeOn = true;
	bIsThunderAttributeOn = true;

	bIsSkillOn = false;
	
	TempAttribute = EAttributeKeyword::e_None;
	
	CoolTimeRate = 0.008f;
	SlowScale = 0.4f;
	bIsDialogOn = false;
}
void UIreneInputInstance::Begin()
{
	const TUniquePtr<FElementDataTable> FireFormTimeDataTable = MakeUnique<FElementDataTable>(*Irene->IreneAttack->GetNameAtElementDataTable(FName("Fire_Ele")));
	if(FireFormTimeDataTable != nullptr)
		FireMaxCoolTime = FireFormTimeDataTable->Ele_C_Time;
	const TUniquePtr<FElementDataTable> WaterFormTimeDataTable = MakeUnique<FElementDataTable>(*Irene->IreneAttack->GetNameAtElementDataTable(FName("Water_Ele")));
	if(WaterFormTimeDataTable != nullptr)
		WaterMaxCoolTime = WaterFormTimeDataTable->Ele_C_Time;
	const TUniquePtr<FElementDataTable> ThunderFormTimeDataTable = MakeUnique<FElementDataTable>(*Irene->IreneAttack->GetNameAtElementDataTable(FName("Thunder_Ele")));
	if(ThunderFormTimeDataTable != nullptr)
		ThunderMaxCoolTime = ThunderFormTimeDataTable->Ele_C_Time;
}

#pragma region Move
void UIreneInputInstance::MoveForward()
{
	const FRotator Rotation = Irene->Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// 0: 전진, 2: 후진
	if (MoveKey[0] != 0 && MoveKey[0] < 3)
		Irene->AddMovementInput(Direction);
	if (MoveKey[2] != 0 && MoveKey[2] < 3)
		Irene->AddMovementInput(Direction * -1);
}
void UIreneInputInstance::MoveRight()
{
	const FRotator Rotation = Irene->Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// 1: 좌측, 3: 우측
	if (MoveKey[1] != 0 && MoveKey[1] < 3)
		Irene->AddMovementInput(Direction * -1);
	if (MoveKey[3] != 0 && MoveKey[3] < 3)
		Irene->AddMovementInput(Direction);
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
	}
}
#pragma endregion Move

#pragma region MoveInput
void UIreneInputInstance::MovePressedKey(const int Value)
{
	if (!bIsDialogOn && Irene->IreneAttack->GetThunderSustainTime() <= 0)
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
	if (MoveKey[0] != 0 && MoveKey[0] <= 3)
		LookDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	if (MoveKey[2] != 0 && MoveKey[2] <= 3)
		LookDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X)*-1;
	if (MoveKey[1] != 0 && MoveKey[1] <= 3)
		LookDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y)*-1;
	if (MoveKey[3] != 0 && MoveKey[3] <= 3)
		LookDir += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if(LookDir == FVector::ZeroVector)
		LookDir = Irene->GetActorForwardVector();
	LookDir.Normalize();

	return LookDir;
}
int UIreneInputInstance::GetMoveKeyToDirNumber()
{
	int LookDir = 0;
	auto Temp = MoveKey;
	
	if(Temp[0] != 0 && Temp[2] != 0)
	{
		Temp[0] = 0;
		Temp[2] = 0;
	}
	if(Temp[1] != 0 && Temp[3] != 0)
	{
		Temp[1] = 0;
		Temp[3] = 0;
	}
	
	if (Temp[0] != 0 && Temp[1] == 0 && Temp[3] == 0)
		LookDir = 0;
	else if(Temp[0] != 0 && Temp[1] == 0 && Temp[3] != 0)
		LookDir = 1;
	else if(Temp[0] == 0 && Temp[1] == 0 && Temp[3] != 0)
		LookDir = 2;
	else if(Temp[2] != 0 && Temp[1] == 0 && Temp[3] != 0)
		LookDir = 3;
	else if(Temp[2] != 0 && Temp[1] == 0 && Temp[3] == 0)
		LookDir = 4;
	else if(Temp[2] != 0 && Temp[1] != 0 && Temp[3] == 0)
		LookDir = 5;
	else if(Temp[2] == 0 && Temp[1] != 0 && Temp[3] == 0)
		LookDir = 6;
	else if(Temp[0] != 0 && Temp[1] != 0 && Temp[3] == 0)
		LookDir = 7;

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
	if(Rate > 0)
		bLeftButtonPressed = true;
	else
		bLeftButtonPressed = false;
	if (CanAttackState() && !AttackWaitHandle.IsValid() && !bIsDialogOn)
	{
		if (Rate >= 1.0)
		{
			Irene->IreneAttack->SetAttackState();

			const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(Irene->IreneAttack->GetBasicAttackDataTableName()));
			// 공격력 계산으로 기본적으로 ATTACK_DAMAGE_1만 사용함
			if(AttackTable != nullptr)
				Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;				
			
			// 마우스 왼쪽 누르고 있을 때 연속공격 지연 시간(짧은 시간에 여러번 공격 인식 안하도록 함)
			constexpr float WaitTime = 0.15f;
			GetWorld()->GetTimerManager().SetTimer(AttackWaitHandle, FTimerDelegate::CreateLambda([&]()
				{
					AttackWaitHandle.Invalidate();
				}), WaitTime*UGameplayStatics::GetGlobalTimeDilation(this), false);

			if (Irene->IreneData.IsAttacking)
			{
				if(bNextAttack)
				{
					if (Irene->IreneData.CanNextCombo)
						Irene->IreneData.IsComboInputOn = true;
				}
				if(bJumpAttack)
				{
					Irene->IreneAttack->AttackStartComboState();
					Irene->IreneAnim->JumpToAttackMontageSection(Irene->IreneData.CurrentCombo);
				}
				if(bReAttack)
				{
					Irene->ChangeStateAndLog(UBasicAttack1State::GetInstance());
					Irene->IreneData.IsAttacking = true;
					Irene->IreneData.CurrentCombo = 0;
					Irene->IreneAttack->AttackStartComboState();
					if(Irene->IreneAnim->GetCurrentActiveMontage() == nullptr)
						Irene->IreneAnim->PlayAttackMontage();
					else
						Irene->IreneAnim->Montage_JumpToSection(FName("Attack1"), Irene->IreneAnim->GetCurrentActiveMontage());
				}
			}
			else
			{
				Irene->IreneAttack->AttackStartComboState();
				Irene->IreneAnim->PlayAttackMontage();
				Irene->IreneAnim->NextToAttackMontageSection(Irene->IreneData.CurrentCombo);
				Irene->IreneData.IsAttacking = true;
				if(PerfectDodgeTimerHandle.IsValid())
				{
					Irene->IreneAnim->SetDodgeDir(0);
					Irene->FollowTargetPosition();
					PerfectDodgeAttackEnd();
				}
			}
		}
	}
}
void UIreneInputInstance::RightButton(float Rate)
{
	// UI작성 시 주석 모두 제거
	if(Rate > 0)
		bRightButtonPressed = true;
	else
		bRightButtonPressed = false;
	if ((CanSkillState()||Irene->IreneAttack->GetCanSkillSkip()) && !SkillWaitHandle.IsValid() && !bIsDialogOn)
	{
		if (Rate >= 1.0)
		{
			Irene->IreneAttack->SetSkillState();

			const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable("B_Attack_1"));
			// 공격력 계산으로 기본적으로 ATTACK_DAMAGE_1만 사용함
			if(AttackTable != nullptr)
				Irene->IreneData.Strength = AttackTable->ATTACK_DAMAGE_1;				
			
			// 마우스 오른쪽 누르고 있을 때 연속공격 지연 시간(짧은 시간에 여러번 공격 인식 안하도록 함)
			constexpr float WaitTime = 0.15f;
			GetWorld()->GetTimerManager().SetTimer(SkillWaitHandle, FTimerDelegate::CreateLambda([&]()
				{
					SkillWaitHandle.Invalidate();
				}), WaitTime*UGameplayStatics::GetGlobalTimeDilation(this), false);			

			GetWorld()->GetTimerManager().SetTimer(SkillWaitHandle, this, &UIreneInputInstance::SkillWait, CoolTimeRate, true, 0.0f);

			//Irene->IreneUIManager->PlayerHud->UseSkill();
			Irene->ChangeStateAndLog(USkillStartState::GetInstance());
			Irene->IreneAnim->PlaySkillAttackMontage();
			Irene->IreneData.IsAttacking = true;
			if(PerfectDodgeTimerHandle.IsValid())
			{
				Irene->IreneAnim->SetDodgeDir(0);
				Irene->FollowTargetPosition();
				PerfectDodgeAttackEnd();
			}
		}
	}
}
void UIreneInputInstance::SkillWait()
{
	// UI작성 시 주석 모두 제거
	SkillCoolTime += CoolTimeRate;
	
	if (SkillCoolTime > MaxSkillCoolTime)
	{
		bIsSkillOn = true;
		//Irene->IreneUIManager->UpdateSkillCool(SkillCoolTime, MaxSkillCoolTime);
		//Irene->IreneUIManager->OnSkillCoolChange.Broadcast();
		SkillCoolTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(SkillWaitHandle);
	}
	//else
	//{
		//Irene->IreneUIManager->UpdateSkillCool(SkillCoolTime, MaxSkillCoolTime);
		//Irene->IreneUIManager->OnSkillCoolChange.Broadcast();
	//}
}

void UIreneInputInstance::MouseWheel(float Rate)
{
	if (!Irene->IreneState->IsDeathState())
	{
		// 줌인줌아웃
		Irene->SpringArmComp->TargetArmLength -= Rate * Irene->IreneData.MouseWheelSpeed;

		Irene->STGameInstance->GetPlayerBattleState() == true ?
			Irene->SpringArmComp->TargetArmLength = FMath::Clamp(Irene->SpringArmComp->TargetArmLength, Irene->IreneData.MinFollowCameraZPosition, Irene->IreneData.BattleCameraZPosition) :
			Irene->SpringArmComp->TargetArmLength = FMath::Clamp(Irene->SpringArmComp->TargetArmLength, Irene->IreneData.MinFollowCameraZPosition, Irene->IreneData.MaxFollowCameraZPosition);
	}
}

void UIreneInputInstance::DodgeKeyword()
{
	if (!Irene->GetMovementComponent()->IsFalling() && !Irene->IreneState->IsDeathState() && !DodgeWaitHandle.IsValid() && !PerfectDodgeTimerHandle.IsValid() &&
		Irene->IreneState->GetStateToString().Compare(FString("Dodge_Start"))!=0 &&
		(Irene->IreneAttack->GetCanDodgeJumpSkip()||!Irene->IreneState->IsAttackState()) && !bIsDialogOn)
	{
		const TUniquePtr<FAttackDataTable> AttackDataTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(FName("Dodge")));

		Irene->IreneAnim->StopAllMontages(0);
		
		Irene->SetActorRelativeRotation(GetMoveKeyToDirVector().Rotation());
		Irene->IreneData.IsInvincibility = true;

		if(Irene->IreneAttack->GetIsPerfectDodge() && CalcPerfectDodgeDir(GetMoveKeyToDirVector()))
			PerfectDodge();
		
		Irene->ChangeStateAndLog(UDodgeStartState::GetInstance());

		constexpr float InvincibilityTime = 0.3f;
		GetWorld()->GetTimerManager().SetTimer(DodgeInvincibilityTimerHandle, FTimerDelegate::CreateLambda([&]()
		 {
			if(!PerfectDodgeInvincibilityTimerHandle.IsValid())
			{
				Irene->IreneData.IsInvincibility = false;
			}
			 DodgeInvincibilityTimerHandle.Invalidate();
		 }), InvincibilityTime * UGameplayStatics::GetGlobalTimeDilation(this), false);
		
		GetWorld()->GetTimerManager().SetTimer(DodgeWaitHandle, FTimerDelegate::CreateLambda([&]()
		 {
			 DodgeWaitHandle.Invalidate();
		 }), AttackDataTable->C_Time*UGameplayStatics::GetGlobalTimeDilation(this), false);
	}
}
void UIreneInputInstance::PerfectDodge()
{
	constexpr float Time = 2.5f;
	constexpr float InvincibilityTime = 1.0f;
	GetWorld()->GetTimerManager().SetTimer(PerfectDodgeTimerHandle, FTimerDelegate::CreateLambda([&]()
		 {
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(),1);
			Irene->IreneAttack->SetIsPerfectDodge(false,PerfectDodgeDir);
			Irene->CustomTimeDilation = 1;
			Irene->IreneAnim->SetDodgeDir(0);
			PerfectDodgeTimeEnd();
			 PerfectDodgeTimerHandle.Invalidate();
		 }), SlowScale * Time * UGameplayStatics::GetGlobalTimeDilation(this), false);
	GetWorld()->GetTimerManager().SetTimer(PerfectDodgeInvincibilityTimerHandle, FTimerDelegate::CreateLambda([&]()
	 {
		Irene->IreneData.IsInvincibility = false;
		 PerfectDodgeInvincibilityTimerHandle.Invalidate();
	 }), InvincibilityTime * UGameplayStatics::GetGlobalTimeDilation(this), false);
	PerfectDodgeStart();
	Irene->IreneAnim->SetDodgeDir(10);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(),SlowScale);
}

bool UIreneInputInstance::CalcPerfectDodgeDir(FVector DodgeDirection)
{
	if (PerfectDodgeDir.Num() == 0)
	{
		return false;
	}
	
	EDodgeDirection Dodge = EDodgeDirection::Front;
	FVector ViewVector = Irene->CameraComp->GetForwardVector();
	ViewVector.Normalize();
	ViewVector = FVector::CrossProduct(FVector::UpVector, ViewVector);
	float Angle = FVector::DotProduct(ViewVector, DodgeDirection);
	Angle = FMath::RoundToFloat(Angle);


	if (Angle != 0)
	{
		if (Angle > 0)
		{
			STARRYLOG(Error, TEXT("Right"), Angle);
			Dodge = EDodgeDirection::Right;
		}
		else {
			STARRYLOG(Error, TEXT("Left"), Angle);
			Dodge = EDodgeDirection::Left;
		}
	}

	ViewVector = Irene->CameraComp->GetForwardVector();
	ViewVector.Normalize();
	Angle = FVector::DotProduct(ViewVector, DodgeDirection);
	Angle = FMath::RoundToFloat(Angle);

	if (Angle != 0)
	{
		if (Angle > 0)
		{
			STARRYLOG(Error, TEXT("Front"), Angle);
			Dodge = EDodgeDirection::Front;
		}
		else {
			STARRYLOG(Error, TEXT("Back"), Angle);
			Dodge = EDodgeDirection::Back;
		}
	}
	uint8 DodgeResult = (uint8)Dodge;
	for (int i = 0; i < PerfectDodgeDir.Num(); i++)
	{
		if (PerfectDodgeDir[i] == DodgeResult)
		{
			PerfectDodgeDir.Empty();
			return true;
		}
	}
	PerfectDodgeDir.Empty();

	return false;
}
void UIreneInputInstance::PerfectDodgeStart()
{
	Irene->PerfectDodgeStart();
}
void UIreneInputInstance::PerfectDodgeTimeEnd()
{
	Irene->PerfectDodgeTimeEnd();
}
void UIreneInputInstance::PerfectDodgeAttackEnd()
{
	Irene->PerfectDodgeAttackEnd();
}

void UIreneInputInstance::DialogAction()
{
	UPlayerHudWidget* PlayerHud = Irene->IreneUIManager->PlayerHud;

	switch (PlayerHud->GetDialogState())
	{
	case EDialogState::e_Set:
		PlayerHud->PlayDialog();
		// 노말다이얼로그 추가되면 주석 해제하면 되는데 불 차징 많이 하고 다이얼로그 띄우면 에러 발생함
		// Irene->IreneAnim->StopAllMontages(0);
		// Irene->IreneAttack->SetUseSkillSkip(true);
		// Irene->SetIreneDialog();
		// if(Irene->IreneState->IsChargeState())
		// {
		// 	Irene->IreneInput->bUseLeftButton = false;
		// 	Irene->IreneInput->bUseRightButton = false;
		// }
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
	if (bIsDialogOn)
	{
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
#pragma endregion UI

#pragma region CheckStateChange
bool UIreneInputInstance::CanRunState() const
{
	if (!Irene->IreneState->IsAttackState() && !Irene->IreneState->IsJumpState() && !Irene->IreneState->IsDeathState())
			return true;
	return false;
}
bool UIreneInputInstance::CanAttackState() const
{
	if(Irene->IreneState->GetStateToString().Compare(FString("Dodge_End"))==0)
		return true;
	if (!Irene->IreneState->IsJumpState() && !Irene->IreneState->IsDodgeState() && !Irene->IreneState->IsDeathState())
		return true;
	return false;
}
bool UIreneInputInstance::CanSkillState() const
{
	if(Irene->IreneState->GetStateToString().Compare(FString("Dodge_End"))==0)
		return true;
	if (!Irene->IreneState->IsJumpState() && !Irene->IreneState->IsDodgeState() && !Irene->IreneState->IsAttackState() && !Irene->IreneState->IsSkillState() && !Irene->IreneState->IsDeathState())
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
		FireCurCoolTime += CoolTimeRate;
	else
	{
		bIsFireAttributeOn = true;
		FireCurCoolTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(AttributeChangeFireTimer);
	}
	Irene->IreneUIManager->UpdateFireCool(FireCurCoolTime, FireMaxCoolTime);
	Irene->IreneUIManager->OnFireCoolChange.Broadcast();
}
void UIreneInputInstance::WaterCoolTime()
{
	if (WaterCurCoolTime < WaterMaxCoolTime)
		WaterCurCoolTime += CoolTimeRate;
	else
	{
		bIsWaterAttributeOn = true;
		WaterCurCoolTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(AttributeChangeWaterTimer);
	}
	Irene->IreneUIManager->UpdateWaterCool(WaterCurCoolTime, WaterMaxCoolTime);
	Irene->IreneUIManager->OnWaterCoolChange.Broadcast();
}
void UIreneInputInstance::ThunderCoolTime()
{
	if (ThunderCurCoolTime < ThunderMaxCoolTime)
		ThunderCurCoolTime += CoolTimeRate;
	else
	{
		bIsThunderAttributeOn = true;
		ThunderCurCoolTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(AttributeChangeElectricTimer);
	}
	Irene->IreneUIManager->UpdateThunderCool(ThunderCurCoolTime, ThunderMaxCoolTime);
	Irene->IreneUIManager->OnThunderCoolChange.Broadcast();
}
#pragma endregion GetSet
