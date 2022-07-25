// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneInputInstance.h"

#include "GeomTools.h"
#include "IreneCharacter.h"
#include "IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneAttackInstance.h"
#include "IreneUIManager.h"
#include "MovieSceneTracksComponentTypes.h"
#include "Quill.h"
#include "../STGameInstance.h"
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
	
	// 추락 중 구르기 입력 초기화
	IsFallingRoll = false;

	StartWaterDodgeStamina = 0;

	FireCurCoolTime = 0.0f;
	WaterCurCoolTime = 0.0f;
	ThunderCurCoolTime = 0.0f;
	FireQuillCurCoolTime = 0.0f;
	WaterQuillCurCoolTime = 0.0f;
	ThunderQuillCurCoolTime = 0.0f;
	
	bIsFireAttributeOn = true;
	bIsWaterAttributeOn = true;
	bIsThunderAttributeOn = true;
	bIsFireQuillOn = true;
	bIsWaterQuillOn = true;
	bIsThunderQuillOn = true;
	
	MaxFireQuillCount = 3;
	MaxWaterQuillCount = 3;
	MaxThunderQuillCount = 3;
	FireQuillCount = MaxFireQuillCount;
	WaterQuillCount = MaxWaterQuillCount;
	ThunderQuillCount = MaxThunderQuillCount;
	FireQuillMaxCoolTime = 3.0f;
	WaterQuillMaxCoolTime = 3.0f;
	ThunderQuillMaxCoolTime = 3.0f;

	CoolTimeRate = 0.008f;
	bIsDialogOn = false;
}
void UIreneInputInstance::Begin()
{
	const TUniquePtr<FFormTimeDataTable> FireFormTimeDataTable = MakeUnique<FFormTimeDataTable>(*Irene->IreneAttack->GetNameAtFormTimeDataTable(FName("Fire_Form")));
	if(FireFormTimeDataTable != nullptr)
		FireMaxCoolTime = FireFormTimeDataTable->Form_C_Time;
	const TUniquePtr<FFormTimeDataTable> WaterFormTimeDataTable = MakeUnique<FFormTimeDataTable>(*Irene->IreneAttack->GetNameAtFormTimeDataTable(FName("Water_Form")));
	if(WaterFormTimeDataTable != nullptr)
		WaterMaxCoolTime = WaterFormTimeDataTable->Form_C_Time;
	const TUniquePtr<FFormTimeDataTable> ThunderFormTimeDataTable = MakeUnique<FFormTimeDataTable>(*Irene->IreneAttack->GetNameAtFormTimeDataTable(FName("Thunder_Form")));
	if(ThunderFormTimeDataTable != nullptr)
		ThunderMaxCoolTime = ThunderFormTimeDataTable->Form_C_Time;
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
	bLeftButtonPressed = true;
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
				}), WaitTime, false);

			if (Irene->IreneData.IsAttacking)
			{
				if (Irene->IreneData.CanNextCombo)
					Irene->IreneData.IsComboInputOn = true;
				else
				{
					if(Irene->IreneData.CurrentCombo < 3)
					{
						Irene->IreneData.CurrentCombo += 1;
						Irene->IreneAnim->JumpToAttackMontageSection(Irene->IreneData.CurrentCombo);
					}
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
void UIreneInputInstance::RightButtonPressed()
{
	int CurrentAttributeQuillCount = 0;
	switch (Irene->IreneAttack->GetQuillAttribute())
	{
	case EAttributeKeyword::e_Fire:
		CurrentAttributeQuillCount = FireQuillCount;
		break;
	case EAttributeKeyword::e_Water:
		CurrentAttributeQuillCount = WaterQuillCount;
		break;
	case EAttributeKeyword::e_Thunder:
		CurrentAttributeQuillCount = ThunderQuillCount;
		break;
	default: ;
	}
	if(CurrentAttributeQuillCount > 0)
	{
		switch (Irene->IreneAttack->GetQuillAttribute())
		{
		case EAttributeKeyword::e_Fire:
			FireQuillCurCoolTime = 0;
			GetWorld()->GetTimerManager().SetTimer(FireQuillWaitHandle, this, &UIreneInputInstance::FireQuillWait, CoolTimeRate, true, 0.0f);
			break;
		case EAttributeKeyword::e_Water:
			WaterQuillCurCoolTime = 0;
			GetWorld()->GetTimerManager().SetTimer(WaterQuillWaitHandle, this, &UIreneInputInstance::WaterQuillWait, CoolTimeRate, true, 0.0f);
			break;
		case EAttributeKeyword::e_Thunder:
			ThunderQuillCurCoolTime = 0;
			GetWorld()->GetTimerManager().SetTimer(ThunderQuillWaitHandle, this, &UIreneInputInstance::ThunderQuillWait, CoolTimeRate, true, 0.0f);
			break;
		default: ;
		}
		Irene->IreneUIManager->PlayerHud->UseQuill();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Irene;

		FRotator Rotator;
		FVector SpawnLocation;

		constexpr float Degree = 30;
		const float L = sin(FMath::DegreesToRadians(Degree));
		float X = FMath::FRandRange(-1,1);
		float Y = FMath::FRandRange(-L,L);
		if(X > 0 && Y > 0)
		{
			// 1사분면
			TArray<FVector2D> PolygonArray;
			PolygonArray.Add(FVector2D(0,0));
			PolygonArray.Add(FVector2D(1,0));
			PolygonArray.Add(FVector2D(1,L));
			if(!FGeomTools2D::IsPointInPolygon(FVector2D(X,Y),PolygonArray))
			{
				X = 1-X;
				Y = L-Y;
			}
		}
		else if(X > 0 && Y <= 0)
		{
			// 4사분면
			TArray<FVector2D> PolygonArray;
			PolygonArray.Add(FVector2D(0,0));
			PolygonArray.Add(FVector2D(1,0));
			PolygonArray.Add(FVector2D(1,-L));
			if(!FGeomTools2D::IsPointInPolygon(FVector2D(X,Y),PolygonArray))
			{
				X = 1-X;
				Y = -L-Y;
			}
		}
		else if(X <= 0 && Y > 0)
		{
			// 2사분면
			TArray<FVector2D> PolygonArray;
			PolygonArray.Add(FVector2D(0,0));
			PolygonArray.Add(FVector2D(-1,0));
			PolygonArray.Add(FVector2D(-1,L));
			if(!FGeomTools2D::IsPointInPolygon(FVector2D(X,Y),PolygonArray))
			{
				X = -1-X;
				Y = L-Y;
			}
		}
		else if(X <= 0 && Y <= 0)
		{
			// 3사분면
			TArray<FVector2D> PolygonArray;
			PolygonArray.Add(FVector2D(0,0));
			PolygonArray.Add(FVector2D(-1,0));
			PolygonArray.Add(FVector2D(-1,-L));
			if(!FGeomTools2D::IsPointInPolygon(FVector2D(X,Y),PolygonArray))
			{
				X = -1-X;
				Y = -L-Y;
			}
		}
		
		if(Irene->IreneAttack->SwordTargetMonster != nullptr || Irene->IreneAttack->QuillTargetMonster != nullptr)
		{
			const AMonster* TargetMonster = nullptr;
			if(Irene->IreneAttack->SwordTargetMonster != nullptr)
				TargetMonster = Cast<AMonster>(Irene->IreneAttack->SwordTargetMonster);
			else if(Irene->IreneAttack->SwordTargetMonster == nullptr && Irene->IreneAttack->QuillTargetMonster != nullptr)
				TargetMonster = Cast<AMonster>(Irene->IreneAttack->QuillTargetMonster);
			
			SpawnLocation = Irene->GetActorLocation() + Irene->GetActorRightVector()*X*50 + Irene->GetActorUpVector()*Y*50 + Irene->GetActorUpVector()*70;
			const FRotator Z = UKismetMathLibrary::FindLookAtRotation(SpawnLocation,TargetMonster->GetRootComponent()->GetSocketLocation(TEXT("Bip001-Head")));
			Rotator = FRotator(Z.Pitch,Z.Yaw,0);
		}
		else
		{			
			SpawnLocation = Irene->GetActorLocation() + Irene->GetActorRightVector()*X*50 + Irene->GetActorUpVector()*Y*50 + Irene->GetActorUpVector()*70;
			const FRotator Z = UKismetMathLibrary::FindLookAtRotation(SpawnLocation,Irene->GetActorLocation() + Irene->GetActorForwardVector()*1500);
			Rotator = FRotator(Z.Pitch,Z.Yaw,0);
		}
		const auto SpawnedActor = GetWorld()->SpawnActor<AQuill>(AQuill::StaticClass(), SpawnLocation,Rotator,SpawnParams);
		SpawnedActor->Attribute = Irene->IreneAttack->GetQuillAttribute();
		SpawnedActor->MoveSpeed = 1000;
		SpawnedActor->Distance = 2500;
		SpawnedActor->Strength = 100;

		if(Irene->IreneAttack->SwordTargetMonster != nullptr)
			SpawnedActor->Target = Irene->IreneAttack->SwordTargetMonster;
		else if(Irene->IreneAttack->SwordTargetMonster == nullptr && Irene->IreneAttack->QuillTargetMonster != nullptr)
			SpawnedActor->Target = Irene->IreneAttack->QuillTargetMonster;
		else 
			SpawnedActor->Target = nullptr;
	}
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

void UIreneInputInstance::AttributeKeywordReleased(const EAttributeKeyword Attribute)
{
	if (!bIsDialogOn)
	{
		// 속성을 변화시키는 함수
		if (!Irene->IreneState->IsDodgeState() && !Irene->IreneState->IsAttackState() && !Irene->IreneState->IsDeathState() && Irene->IreneAttack->GetSwordAttribute() != Attribute)
		{
			if (Attribute == EAttributeKeyword::e_Fire && bIsFireAttributeOn)
			{
				if(Irene->IreneAttack->GetQuillAttribute() == EAttributeKeyword::e_Fire)
					Irene->IreneAttack->SetQuillAttribute(EAttributeKeyword::e_Water);
			}
			else if (Attribute == EAttributeKeyword::e_Water && bIsWaterAttributeOn)
			{
				if(Irene->IreneAttack->GetQuillAttribute() == EAttributeKeyword::e_Water)
					Irene->IreneAttack->SetQuillAttribute(EAttributeKeyword::e_Thunder);
			}
			else if (Attribute == EAttributeKeyword::e_Thunder && bIsThunderAttributeOn)
			{
				if(Irene->IreneAttack->GetQuillAttribute() == EAttributeKeyword::e_Thunder)
					Irene->IreneAttack->SetQuillAttribute(EAttributeKeyword::e_Fire);
			}
			ChangeForm(Attribute);
			Irene->FOnQuillAttributeChange.Broadcast();
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
void UIreneInputInstance::QuillAttributeChangeReleased()
{
	// 깃펜 속성 변경
	EAttributeKeyword Value = EAttributeKeyword::e_Fire;
	int TargetMonsterStack = 0;
	if(Irene->IreneAttack->SwordTargetMonster != nullptr)
	{
		const auto Monster = Cast<AMonster>(Irene->IreneAttack->SwordTargetMonster);
		TargetMonsterStack = Monster->GetCurQuillStack();
		Monster->SetCurQuillStack(0);
	}
	else if(Irene->IreneAttack->QuillTargetMonster != nullptr)
	{
		const auto Monster = Cast<AMonster>(Irene->IreneAttack->QuillTargetMonster);
		TargetMonsterStack = Monster->GetCurQuillStack();
		Monster->SetCurQuillStack(0);
	}
	switch (Irene->IreneAttack->GetQuillAttribute())
	{
	case EAttributeKeyword::e_Fire:	
		Irene->IreneAttack->FireQuillStack(TargetMonsterStack);
		Value = EAttributeKeyword::e_Water;
		if(Irene->IreneAttack->GetSwordAttribute() == EAttributeKeyword::e_Water)
			Value = EAttributeKeyword::e_Thunder;
		break;
	case EAttributeKeyword::e_Water:
		Irene->IreneAttack->WaterQuillStack(TargetMonsterStack);
		Value = EAttributeKeyword::e_Thunder;
		if(Irene->IreneAttack->GetSwordAttribute() == EAttributeKeyword::e_Thunder)
			Value = EAttributeKeyword::e_Fire;
		break;
	case EAttributeKeyword::e_Thunder:
		Irene->IreneAttack->ThunderQuillStack(TargetMonsterStack);
		Value = EAttributeKeyword::e_Fire;
		if(Irene->IreneAttack->GetSwordAttribute() == EAttributeKeyword::e_Fire)
			Value = EAttributeKeyword::e_Water;
		break;
	default: ;
	}
	Irene->IreneAttack->SetQuillAttribute(Value);
	Irene->FOnQuillAttributeChange.Broadcast();
}

void UIreneInputInstance::ChangeForm(const EAttributeKeyword Value)
{
	if(Irene->Weapon->IsVisible())
		Irene->WeaponVisible(false);
	// 속성을 변화시키고 그에 따른 UI와 사운드 적용
	Irene->IreneAttack->SetSwordAttribute(Value);
	Irene->IreneAnim->SetAttribute(Irene->IreneAttack->GetSwordAttribute());
	Irene->FOnSwordAttributeChange.Broadcast();

	// 속성 마다 소리와 무기 설정 적용
	if(Irene->IreneAttack->GetSwordAttribute() == EAttributeKeyword::e_Fire)
	{
		Irene->IreneUIManager->AttackSound->SetParameter("Attributes", 1.0f);
		Irene->IreneUIManager->AttackVoiceSound->SetParameter("Attributes", 1.0f);
	}
	else if(Irene->IreneAttack->GetSwordAttribute() == EAttributeKeyword::e_Water)
	{
		Irene->IreneUIManager->AttackSound->SetParameter("Attributes", 2.0f);
		Irene->IreneUIManager->AttackVoiceSound->SetParameter("Attributes", 2.0f);
	}
	else if(Irene->IreneAttack->GetSwordAttribute() == EAttributeKeyword::e_Thunder)
	{
		Irene->IreneUIManager->AttackSound->SetParameter("Attributes", 3.0f);
		Irene->IreneUIManager->AttackVoiceSound->SetParameter("Attributes", 3.0f);
	}
	// 속성 마다 변화 쿨타임 타이머 시작
 	bIsThunderAttributeOn = false;
	bIsWaterAttributeOn = false;
	bIsFireAttributeOn = false;

	ThunderCurCoolTime = 0.0f;
	FireCurCoolTime = 0.0f;
	WaterCurCoolTime = 0.0f;
	//Fire
	GetWorld()->GetTimerManager().SetTimer(AttributeChangeFireTimer, this, &UIreneInputInstance::FireCoolTime, CoolTimeRate, true, 0.0f);
	//Water
	GetWorld()->GetTimerManager().SetTimer(AttributeChangeWaterTimer, this, &UIreneInputInstance::WaterCoolTime, CoolTimeRate, true, 0.0f);
	//Thunder
	GetWorld()->GetTimerManager().SetTimer(AttributeChangeElectricTimer, this, &UIreneInputInstance::ThunderCoolTime, CoolTimeRate, true, 0.0f);
}

void UIreneInputInstance::DodgeKeyword()
{
	if (!Irene->GetMovementComponent()->IsFalling() && !Irene->IreneState->IsDeathState() && !DodgeWaitHandle.IsValid() &&
	Irene->IreneState->IsAttackState() && Irene->IreneAttack->GetCanDodgeJumpSkip()||(!Irene->IreneState->IsAttackState()&&!bIsDialogOn))
	{
		if(Irene->IreneData.CurrentStamina >= 30)
		{
			Irene->IreneAnim->StopAllMontages(0);
			Irene->IreneData.CurrentStamina -= 30;
			Irene->ChangeStateAndLog(UDodgeStartState::GetInstance());
			Irene->GetCharacterMovement()->AddImpulse(GetMoveKeyToDirVector()*800000);			
			Irene->SetActorRelativeRotation(GetMoveKeyToDirVector().Rotation());
			
			GetWorld()->GetTimerManager().SetTimer(DodgeWaitHandle, FTimerDelegate::CreateLambda([&]()
			 {
				 DodgeWaitHandle.Invalidate();
			 }), 0.03f, false);
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

void UIreneInputInstance::FireQuillWait()
{
	FireQuillCurCoolTime += CoolTimeRate;
	if (FireQuillCurCoolTime > FireQuillMaxCoolTime)
	{
		bIsFireQuillOn = true;
		Irene->IreneUIManager->UpdateFireQuillCool(FireQuillCurCoolTime, FireQuillMaxCoolTime);
		Irene->IreneUIManager->OnFireQuillCoolChange.Broadcast();
		FireQuillCurCoolTime = 0.0f;
		if (FireQuillCount >= MaxFireQuillCount)
			GetWorld()->GetTimerManager().ClearTimer(FireQuillWaitHandle);
	}
	else
	{
		Irene->IreneUIManager->UpdateFireQuillCool(FireQuillCurCoolTime, FireQuillMaxCoolTime);
		Irene->IreneUIManager->OnFireQuillCoolChange.Broadcast();
	}
}
void UIreneInputInstance::WaterQuillWait()
{
	WaterQuillCurCoolTime += CoolTimeRate;
	if (WaterQuillCurCoolTime > WaterQuillMaxCoolTime)
	{
		bIsWaterQuillOn = true;
		Irene->IreneUIManager->UpdateWaterQuillCool(WaterQuillCurCoolTime, WaterQuillMaxCoolTime);
		Irene->IreneUIManager->OnWaterQuillCoolChange.Broadcast();
		WaterQuillCurCoolTime = 0.0f;
		if (WaterQuillCount >= MaxWaterQuillCount)
			GetWorld()->GetTimerManager().ClearTimer(WaterQuillWaitHandle);
	}
	else
	{
		Irene->IreneUIManager->UpdateWaterQuillCool(WaterQuillCurCoolTime, WaterQuillMaxCoolTime);
		Irene->IreneUIManager->OnWaterQuillCoolChange.Broadcast();
	}
}
void UIreneInputInstance::ThunderQuillWait()
{
	ThunderQuillCurCoolTime += CoolTimeRate;
	if (ThunderQuillCurCoolTime > ThunderQuillMaxCoolTime)
	{
		bIsThunderQuillOn = true;
		Irene->IreneUIManager->UpdateThunderQuillCool(ThunderQuillCurCoolTime, ThunderQuillMaxCoolTime);
		Irene->IreneUIManager->OnThunderQuillCoolChange.Broadcast();
		ThunderQuillCurCoolTime = 0.0f;
		if (ThunderQuillCount >= MaxThunderQuillCount)
			GetWorld()->GetTimerManager().ClearTimer(ThunderQuillWaitHandle);
	}
	else
	{
		Irene->IreneUIManager->UpdateThunderQuillCool(ThunderQuillCurCoolTime, ThunderQuillMaxCoolTime);
		Irene->IreneUIManager->OnThunderQuillCoolChange.Broadcast();
	}
}
#pragma endregion GetSet
