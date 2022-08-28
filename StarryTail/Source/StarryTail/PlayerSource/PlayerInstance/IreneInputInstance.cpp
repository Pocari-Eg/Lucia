// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneInputInstance.h"

#include "GeomTools.h"
#include "../IreneCharacter.h"
#include "../PlayerFSM/IreneFSM.h"
#include "IreneAnimInstance.h"
#include "IreneAttackInstance.h"
#include "IreneUIManager.h"
#include "MovieSceneTracksComponentTypes.h"
#include "../Quill.h"
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
	
	// 추락 중 구르기 입력 초기화
	IsFallingRoll = false;
	RightButtonChargeTime = 0;
	
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
	FireQuillMaxCoolTime = 1.5f;
	WaterQuillMaxCoolTime = 1.5f;
	ThunderQuillMaxCoolTime = 1.5f;

	TempAttribute = EAttributeKeyword::e_None;

	bIsLockOn = false;
	LockOnTime = 0;
	
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
void UIreneInputInstance::ThunderDeBuffKey()
{
	if (!bIsDialogOn)
	{
		if(Irene->IreneAttack->GetThunderSustainTime() > 0)
		{
			if(Irene->IreneAttack->GetThunderSustainTime() - 1.5f <= 0)
				Irene->IreneAttack->ResetThunderDeBuffStack();
			else
				Irene->IreneAttack->SetThunderSustainTime(Irene->IreneAttack->GetThunderSustainTime() - 1.5f);
		}
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
	if(!bIsLockOn)
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
				if(PerfectDodgeTimerHandle.IsValid())
				{
					Irene->FollowTargetPosition();
					PerfectDodgeAttackEnd();
				}
			}
		}
	}
}
void UIreneInputInstance::RightButtonReleased()
{
	if(RightButtonChargeTime > 0)
	{
		const TUniquePtr<FChargeDataTable> ChargeDataTable = MakeUnique<FChargeDataTable>(*Irene->IreneAttack->GetNameAtChargeDataTable());
		if(RightButtonChargeTime > ChargeDataTable->Charge_Time_0)
		{
			QuillSpawn(FVector(-10,-55,55),false);
			QuillSpawn(FVector(-10,55,55),true);
			QuillSpawn(FVector(-10,-55,20),false);
			QuillSpawn(FVector(-10,55,20),true);
			if(RightButtonChargeTime > ChargeDataTable->Charge_Time_1)
			{
				QuillSpawn(FVector(-10,-75,85),false);
			}
			if(RightButtonChargeTime > ChargeDataTable->Charge_Time_2)
			{
				QuillSpawn(FVector(-10,75,85),true);
			}
			if(RightButtonChargeTime > ChargeDataTable->Charge_Time_3)
			{
				QuillSpawn(FVector(-10,-75,10),false);
			}
			if(RightButtonChargeTime > ChargeDataTable->Charge_Time_4)
			{
				QuillSpawn(FVector(-10,75,-10),true);
			}
		}
		GetWorld()->GetTimerManager().SetTimer(QuillWaitHandle, FTimerDelegate::CreateLambda([&]
		{
			GetWorld()->GetTimerManager().ClearTimer(QuillWaitHandle);
		}), ChargeDataTable->Quill_C_Time*UGameplayStatics::GetGlobalTimeDilation(this), false);
		RightButtonChargeTime = 0;
	}
}
void UIreneInputInstance::RightButton(float Rate)
{
	if(!QuillWaitHandle.IsValid() && Rate > 0)
		RightButtonChargeTime += GetWorld()->GetDeltaSeconds();
}

void UIreneInputInstance::MouseWheel(float Rate)
{
	if (!Irene->IreneState->IsDeathState())
	{
		// 줌인줌아웃
		Irene->SpringArmComp->TargetArmLength -= Rate * Irene->IreneData.MouseWheelSpeed;

		if(!bIsLockOn)
		Irene->STGameInstance->GetPlayerBattleState() == true ?
			Irene->SpringArmComp->TargetArmLength = FMath::Clamp(Irene->SpringArmComp->TargetArmLength, Irene->IreneData.MinFollowCameraZPosition, Irene->IreneData.BattleCameraZPosition) :
			Irene->SpringArmComp->TargetArmLength = FMath::Clamp(Irene->SpringArmComp->TargetArmLength, Irene->IreneData.MinFollowCameraZPosition, Irene->IreneData.MaxFollowCameraZPosition);
		else
			Irene->STGameInstance->GetPlayerBattleState() == true ?
			Irene->SpringArmComp->TargetArmLength = FMath::Clamp(Irene->SpringArmComp->TargetArmLength, 700.0f, Irene->IreneData.BattleCameraZPosition+100) :
			Irene->SpringArmComp->TargetArmLength = FMath::Clamp(Irene->SpringArmComp->TargetArmLength, 700.0f, 800.0f);
	}
}

void UIreneInputInstance::QuillSpawn(FVector Vector, bool IsRightPos)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Irene;
	const FVector SpawnLocation = Irene->GetActorLocation() + Irene->GetActorForwardVector()*Vector.X + Irene->GetActorRightVector()*Vector.Y + Irene->GetActorUpVector()*Vector.Z;

	TUniquePtr<FQuillDataTable> ElementTimeDataTable;
	switch (Irene->GetQuillAttribute())
	{
	case EAttributeKeyword::e_Fire:
		ElementTimeDataTable = MakeUnique<FQuillDataTable>(*Irene->IreneAttack->GetNameAtQuillDataTable(FName("FireQuill")));
		break;
	case EAttributeKeyword::e_Water:
		ElementTimeDataTable = MakeUnique<FQuillDataTable>(*Irene->IreneAttack->GetNameAtQuillDataTable(FName("WaterQuill")));
		break;
	case EAttributeKeyword::e_Thunder:
		ElementTimeDataTable = MakeUnique<FQuillDataTable>(*Irene->IreneAttack->GetNameAtQuillDataTable(FName("ThunderQuill")));
		break;
	default:
		ElementTimeDataTable = MakeUnique<FQuillDataTable>(*Irene->IreneAttack->GetNameAtQuillDataTable(FName("FireQuill")));
		break;
	}
	const auto SpawnedActor = GetWorld()->SpawnActor<AQuill>(AQuill::StaticClass(), SpawnLocation,Irene->GetActorRotation(),SpawnParams);
	SpawnedActor->Init(Irene);
	SpawnedActor->Attribute = Irene->GetQuillAttribute();
	SpawnedActor->MoveSpeed = ElementTimeDataTable->Quill_Speed;
	SpawnedActor->Distance = ElementTimeDataTable->Quill_Distance;
	SpawnedActor->Strength = ElementTimeDataTable->Quill_Dmg;
	SpawnedActor->IsRightPos = IsRightPos;
	
	if(Irene->IreneAttack->QuillTargetMonster != nullptr)
		SpawnedActor->Target = Irene->IreneAttack->QuillTargetMonster;
	else 
		SpawnedActor->Target = nullptr;
}
void UIreneInputInstance::QuillLockOn()
{
	if(Irene->IreneAttack->QuillTargetMonster)
	{
		if(bIsLockOn)
		{
			Irene->SpringArmComp->bInheritPitch = true;
			Irene->WorldController->SetControlRotation(FRotator(-20,Irene->WorldController->GetControlRotation().Yaw,Irene->WorldController->GetControlRotation().Roll));
			bIsLockOn = false;
		}
		else
		{
			Irene->SpringArmComp->bInheritPitch = false;
			Irene->SpringArmComp->SetRelativeRotation(FRotator(-20,Irene->SpringArmComp->GetRelativeRotation().Yaw,Irene->SpringArmComp->GetRelativeRotation().Roll));
			bIsLockOn = true;
			LockOnTime = 0;
			GetWorld()->GetTimerManager().SetTimer(LockOnTimerHandle, this, &UIreneInputInstance::LockOnTimer, GetWorld()->GetDeltaSeconds()*UGameplayStatics::GetGlobalTimeDilation(this), true, 0.0f);
		}
	}
}
void UIreneInputInstance::QuillLockOnSort()
{
	if(Irene->IreneAttack->QuillTargetMonster)
	{
		Irene->ActorAngleMap.Reset();
		auto AllPosition = Irene->SetCameraStartTargetPosition(FVector(500,400,1500),Irene->CameraComp->GetComponentLocation());
		auto HitMonsterList = Irene->StartPositionFindNearMonster(AllPosition.Get<0>(),AllPosition.Get<1>(),AllPosition.Get<2>(),GetWorld()->GetDeltaSeconds());
		for (FHitResult Monster : HitMonsterList.Get<0>())
		{
			// 맞춘 액터가 캡슐오브젝트를 가지고 있는지 확인
			if (Monster.GetActor()->FindComponentByClass<UCapsuleComponent>() != nullptr)
			{
				// 기존 오브젝트 충돌체 프로필 이름
				// 새로운 오브젝트 충돌체 프로필 이름
				const FName RayCollisionProfileName = Monster.GetActor()->FindComponentByClass<UCapsuleComponent>()->GetCollisionProfileName();
				const FName EnemyProfile = "Enemy";
				const FName ObjectProfile = "Object";	
				// 맞췄을 때 캡슐컴포넌트를 가지고 카메라에 렌더링 되며 정상적으로 살아있는 몬스터 또는 오브젝트 찾기
				if (Monster.Actor.IsValid() &&
					(RayCollisionProfileName == EnemyProfile || RayCollisionProfileName == ObjectProfile)
					&& Monster.GetActor()->WasRecentlyRendered())
				{
					FVector Dir = Monster.GetActor()->GetActorLocation()-Irene->CameraComp->GetComponentLocation();
					Dir.Normalize();
					float Dot = FVector::DotProduct(Irene->CameraComp->GetRightVector(),Dir);
					float AcosAngle = FMath::Acos(Dot);
					float Angle = FMath::RadiansToDegrees(AcosAngle);
					Irene->ActorAngleMap.Add(Monster.GetActor(),Angle);					
				}
			}
		}
		Irene->ActorAngleMap.ValueSort([](const float A, const float B){return A<B;});
	}
}

void UIreneInputInstance::QuillLeftLockOn()
{
	QuillLockOnSort();
	TTuple<AActor*, float>LeftMonster = MakeTuple(nullptr,0.0f);
	bool FindCurrentQuillTarget = false;
	for (const auto MonsterAngle : Irene->ActorAngleMap)
	{
		LeftMonster = MonsterAngle;
		if(FindCurrentQuillTarget == true)
			break;
		if(MonsterAngle.Key == Irene->IreneAttack->QuillTargetMonster)
			FindCurrentQuillTarget = true;
	}
	if(LeftMonster.Key)
		ChangeLockOnTarget(LeftMonster.Key);
}
void UIreneInputInstance::QuillRightLockOn()
{
	QuillLockOnSort();
	TTuple<AActor*, float>RightMonster = MakeTuple(nullptr,0.0f);
	for (const auto MonsterAngle : Irene->ActorAngleMap)
	{
		if(MonsterAngle.Key == Irene->IreneAttack->QuillTargetMonster)
			break;
		RightMonster = MonsterAngle;
	}
	if(RightMonster.Key)
		ChangeLockOnTarget(RightMonster.Key);
}
void UIreneInputInstance::QuillLockOnTargetDead()
{
	QuillLockOnSort();
	TTuple<AActor*, float>NearMonster = MakeTuple(nullptr,10000.0f);
	for (const auto MonsterAngle : Irene->ActorAngleMap)
	{
		float Dist = FVector::Dist(MonsterAngle.Key->GetActorLocation(),Irene->IreneAttack->QuillTargetMonster->GetActorLocation());
		if(Dist < NearMonster.Value)
			NearMonster = MakeTuple(MonsterAngle.Key,Dist);
	}
	if(NearMonster.Key)
		ChangeLockOnTarget(NearMonster.Key);
	else
	{
		const auto Mon=Cast<AMonster>(Irene->IreneAttack->QuillTargetMonster);
		if(Mon != nullptr)
		{
			Mon->TargetWidgetOff();
			Irene->IreneAttack->QuillTargetMonster = nullptr;
			bIsLockOn = false;
			Irene->SpringArmComp->bInheritPitch = true;
			Irene->SpringArmComp->SetRelativeRotation(FRotator::ZeroRotator);
		}
	}
}
void UIreneInputInstance::ChangeLockOnTarget(AActor* Target)
{
	if(Target == Irene->IreneAttack->QuillTargetMonster)
		return;
	auto Mon=Cast<AMonster>(Irene->IreneAttack->QuillTargetMonster);
	if(Mon != nullptr)
	{
		Mon->TargetWidgetOff();
		Irene->IreneAttack->QuillTargetMonster = nullptr;
	}
	Mon = Cast<AMonster>(Target);
	if(Mon != nullptr)
	{
		Mon->TargetWidgetOn();
		Irene->IreneAttack->QuillTargetMonster = Target;
		LockOnTime = 0;
		GetWorld()->GetTimerManager().SetTimer(LockOnTimerHandle, this, &UIreneInputInstance::LockOnTimer, GetWorld()->GetDeltaSeconds()*UGameplayStatics::GetGlobalTimeDilation(this), true, 0.0f);
	}
}
void UIreneInputInstance::LockOnTimer()
{
	LockOnTime+=GetWorld()->GetDeltaSeconds();
	FVector Dir = Irene->IreneAttack->QuillTargetMonster->GetActorLocation() - Irene->GetActorLocation();
	Dir.Normalize();
	float Dist = FVector::Dist(Irene->IreneAttack->QuillTargetMonster->GetActorLocation(), Irene->GetActorLocation());
	const FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(Irene->CameraComp->GetComponentLocation(),Dir*(Dist/2));
	const FRotator Interp = FMath::RInterpTo(Irene->WorldController->GetControlRotation(),LookAt,GetWorld()->GetDeltaSeconds(),10.0f);
	const FRotator Controll = FRotator(Irene->WorldController->GetControlRotation().Pitch,Interp.Yaw,Irene->WorldController->GetControlRotation().Roll);
	Irene->WorldController->SetControlRotation(Controll);
	if(LockOnTime > 0.5f)
	{
		LockOnTime = 0;
		GetWorld()->GetTimerManager().ClearTimer(LockOnTimerHandle);
	}
}

int UIreneInputInstance::QuillAttributeChangeStackAction()
{
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
	return TargetMonsterStack;
}

void UIreneInputInstance::QuillLeftAttributeChangeReleased()
{
	// 깃펜 속성 변경
	EAttributeKeyword Value = EAttributeKeyword::e_Fire;
	const int TargetMonsterStack = QuillAttributeChangeStackAction();
	switch (Irene->GetQuillAttribute())
	{
	case EAttributeKeyword::e_Fire:	
		Irene->IreneAttack->SetFireQuillStack(TargetMonsterStack);
		Value = EAttributeKeyword::e_Thunder;
		break;
	case EAttributeKeyword::e_Water:
		Irene->IreneAttack->SetWaterQuillStack(TargetMonsterStack);
		Value = EAttributeKeyword::e_Fire;
		break;
	case EAttributeKeyword::e_Thunder:
		Irene->IreneAttack->SetThunderQuillStack(TargetMonsterStack);
		Value = EAttributeKeyword::e_Water;
		break;
	default: ;
	}
	Irene->IreneAttack->SetQuillAttribute(Value);
	Irene->FOnQuillAttributeChange.Broadcast();
}
void UIreneInputInstance::QuillRightAttributeChangeReleased()
{
	// 깃펜 속성 변경
	EAttributeKeyword Value = EAttributeKeyword::e_Fire;
	const int TargetMonsterStack = QuillAttributeChangeStackAction();
	switch (Irene->GetQuillAttribute())
	{
	case EAttributeKeyword::e_Fire:	
		Irene->IreneAttack->SetFireQuillStack(TargetMonsterStack);
		Value = EAttributeKeyword::e_Water;
		break;
	case EAttributeKeyword::e_Water:
		Irene->IreneAttack->SetWaterQuillStack(TargetMonsterStack);
		Value = EAttributeKeyword::e_Thunder;
		break;
	case EAttributeKeyword::e_Thunder:
		Irene->IreneAttack->SetThunderQuillStack(TargetMonsterStack);
		Value = EAttributeKeyword::e_Fire;
		break;
	default: ;
	}
	Irene->IreneAttack->SetQuillAttribute(Value);
	Irene->FOnQuillAttributeChange.Broadcast();
}

void UIreneInputInstance::DodgeKeyword()
{
	if (!Irene->GetMovementComponent()->IsFalling() && !Irene->IreneState->IsDeathState() && !DodgeWaitHandle.IsValid() &&
		Irene->IreneState->GetStateToString().Compare(FString("Dodge_Start"))!=0 &&
		(Irene->IreneAttack->GetCanDodgeJumpSkip()||!Irene->IreneState->IsAttackState()) && !bIsDialogOn)
	{
		const TUniquePtr<FAttackDataTable> AttackDataTable = MakeUnique<FAttackDataTable>(*Irene->IreneAttack->GetNameAtAttackDataTable(FName("Dodge")));
	
		Irene->IreneAnim->StopAllMontages(0);
		
		Irene->SetActorRelativeRotation(GetMoveKeyToDirVector().Rotation());

		if(Irene->IreneAttack->GetIsPerfectDodge() && !PerfectDodgeTimerHandle.IsValid() && CalcPerfectDodgeDir(GetMoveKeyToDirVector()))
			PerfectDodge();

		Irene->ChangeStateAndLog(UDodgeStartState::GetInstance());
		//Irene->GetCharacterMovement()->AddImpulse(GetMoveKeyToDirVector()*AttackDataTable->Attack_Distance_1);		
		//Irene->IreneAnim->SetDodgeDir(GetMoveKeyToDirNumber());
		
		GetWorld()->GetTimerManager().SetTimer(DodgeWaitHandle, FTimerDelegate::CreateLambda([&]()
		 {
			 DodgeWaitHandle.Invalidate();
		 }), AttackDataTable->C_Time*UGameplayStatics::GetGlobalTimeDilation(this), false);
	}
}
void UIreneInputInstance::PerfectDodge()
{
	constexpr float Time = 2.5f;
	constexpr float InvincibilityTime = 1.5f;
	GetWorld()->GetTimerManager().SetTimer(PerfectDodgeTimerHandle, FTimerDelegate::CreateLambda([&]()
		 {
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(),1);
			Irene->IreneAttack->SetIsPerfectDodge(false,PerfectDodgeDir);
			Irene->CustomTimeDilation = 1;
			PerfectDodgeTimeEnd();
			 PerfectDodgeTimerHandle.Invalidate();
		 }), SlowScale * Time * UGameplayStatics::GetGlobalTimeDilation(this), false);
	GetWorld()->GetTimerManager().SetTimer(PerfectDodgeInvincibilityTimerHandle, FTimerDelegate::CreateLambda([&]()
	 {
		Irene->IreneData.IsInvincibility = false;
		 PerfectDodgeInvincibilityTimerHandle.Invalidate();
	 }), InvincibilityTime * UGameplayStatics::GetGlobalTimeDilation(this), false);
	PerfectDodgeStart();
	Irene->IreneData.IsInvincibility = true;
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
