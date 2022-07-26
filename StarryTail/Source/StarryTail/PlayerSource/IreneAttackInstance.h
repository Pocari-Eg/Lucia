// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "../StarryTail.h"
#include "PlayerCharacterDataStruct.h"

#include "IreneAttackInstance.generated.h"

UCLASS()
class STARRYTAIL_API UIreneAttackInstance : public UObject
{
	GENERATED_BODY()
public:
	// 타겟 몬스터 또는 오브젝트
	UPROPERTY()
	AActor* SwordTargetMonster;
	// 깃펜을 보낼 수 있는 몬스터 또는 오브젝트
	UPROPERTY()
	AActor* QuillTargetMonster;	
private:
	UPROPERTY()
	class AIreneCharacter* Irene;

	EAttributeKeyword SwordAttribute;
	EAttributeKeyword QuillAttribute;

	UPROPERTY()
	TArray<UParticleSystem*> BuffParticle;
	
	UPROPERTY()
	UDataTable* AttackDataTable;
	UPROPERTY()
	UDataTable* FormTimeDataTable;

	FTimerHandle FireQuillStackTimerHandle;
	FTimerHandle WaterQuillStackTimerHandle;
	FTimerHandle ThunderQuillStackTimerHandle;

	// 타켓 추적 유무
	bool bFollowTarget;
	// 보간을 위한 수 0 ~ 1
	float FollowTargetAlpha;
	// 보간을 위한 시작 위치
	FVector PlayerPosVec;
	// 보간을 위한 목표 위치
	FVector TargetPosVec;
	// 전기 스킬 이동 전 위치
	FVector CurrentPosVec;
	// 전기 스킬 이동 후 위치
	FVector NowPosVec;
	
	// 카메라 쉐이크 시간
	float CameraShakeTime;
	// 타켓 추적 유무
	bool bFollowCameraTarget;
	// 보간을 위한 수 0 ~ 1
	float FollowTargetCameraAlpha;
	// 보간을 위한 시작 위치
	FRotator CameraRot;
	// 보간을 위한 목표 위치
	FRotator TargetCameraRot;	
	
	// 후딜 중 이동 가능 타이밍 노티파이
	bool bMoveSkip;
	// 후딜 중 닷지나 점프 가능 타이밍 노티파이
	bool bDodgeJumpSkip;
	// 후딜 중 재공격 가능 타이밍 노티파이
	bool bReAttackSkip;
	// 후딜 중 스킬 가능 타이밍 노티파이
	bool bSkillSkip;
public:
	void Init(AIreneCharacter* Value);
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();

	// 검 공격 함수
	void AttackStartComboState();
	void AttackEndComboState();
	void AttackTimeEndState();
	void AttackCheck();
	void AttackStopCheck();
	void DoAttack();

	// 깃펜 스택 함수
	void FireQuillStack(const int Value);
	void WaterQuillStack(const int Value);
	void ThunderQuillStack(const int Value);
	void ResetFireQuillStack();
	void ResetWaterQuillStack();
	void ResetThunderQuillStack();
	
	void SetAttackState()const;
	
	FAttackDataTable* GetNameAtAttackDataTable(const FName Value) const { if (Value != FName("")) return (AttackDataTable->FindRow<FAttackDataTable>(Value, "")); return nullptr; }
	FFormTimeDataTable* GetNameAtFormTimeDataTable(const FName Value) const { if (Value != FName("")) return (FormTimeDataTable->FindRow<FFormTimeDataTable>(Value, "")); return nullptr; }

#pragma region GetSet
	//공격력 반환
	float GetATK()const;

	FName GetBasicAttackDataTableName();

	//속성 반환
	UFUNCTION(BlueprintCallable)
	EAttributeKeyword GetSwordAttribute()const{return SwordAttribute;}
	UFUNCTION(BlueprintCallable)
	EAttributeKeyword GetQuillAttribute()const{return QuillAttribute;}
	bool GetFollowTarget()const {return bFollowTarget;}
	float GetFollowTargetAlpha()const {return FollowTargetAlpha;}
	FVector GetPlayerPosVec()const {return PlayerPosVec;}
	FVector GetTargetPosVec()const {return TargetPosVec;}
	FVector GetCurrentPosVec()const {return CurrentPosVec;}
	FVector GetNowPosVec()const {return NowPosVec;}
	float GetCameraShakeTime()const {return CameraShakeTime;}
	bool GetCanMoveSkip()const{return bMoveSkip;}
	bool GetCanDodgeJumpSkip()const{return bDodgeJumpSkip;}
	bool GetCanReAttackSkip()const{return bReAttackSkip;}
	bool GetCanSkillSkip()const{return bSkillSkip;}
	FName GetAttributeToFormTimeDataTableName()const;

	void SetSwordAttribute(const EAttributeKeyword Value){SwordAttribute = Value;}
	void SetQuillAttribute(const EAttributeKeyword Value){QuillAttribute = Value;}
	void SetFollowTarget(const bool Value){bFollowTarget = Value;}
	void SetFollowTargetAlpha(const float Value){FollowTargetAlpha = Value;}
	void SetPlayerPosVec(const FVector Value){PlayerPosVec = Value;}
	void SetTargetPosVec(const FVector Value){TargetPosVec = Value;}
	void SetCameraShakeTime(const float Value){CameraShakeTime = Value;}
	void SetCurrentPosVec(const FVector Value){CurrentPosVec = Value;}
	void SetNowPosVec(const FVector Value){NowPosVec = Value;}
	void SetCanMoveSkip(const bool Value){bMoveSkip = Value;}
	void SetCanDodgeJumpSkip(const bool Value){bDodgeJumpSkip = Value;}
	void SetCanReAttackSkip(const bool Value){bReAttackSkip = Value;}
	void SetCanSkillSkip(const bool Value){bSkillSkip = Value;}
#pragma endregion GetSet

private:
	UIreneAttackInstance();
};
