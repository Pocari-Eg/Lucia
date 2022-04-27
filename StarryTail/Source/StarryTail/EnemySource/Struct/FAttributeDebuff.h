// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../StarryTail.h"
#include "FAttributeDebuff.generated.h"


USTRUCT(Atomic, BluePrintType)
struct FAttributeDebuff
{
	GENERATED_USTRUCT_BODY()
public:
	//화상 디버프 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BurnCycle; // 화상 데미지 받는 틱
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BurnDamage; // 화상 데미지 계산 상수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BurnTime; // 화상 지속시간
	float BurnCycleTimer; // 화상 데미지 틱 계산시 틱 함수에서 증가하는 값
	float BurnTimer; // 화상 지속시간 계산시 틱 함수에서 증가하는 값

	//침수 디버프 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FloodingTime; // 침수상태 지속시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FloodingDebuffSpeedReductionValue; // 속도 감속 수치
	float FloodingTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SparkReduction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SparkDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SparkTime;
	float SparkTimer;
	
	/*
	//감전 디버프 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShockTime;
	float ShockTimer;

	
	//범위 디버프 중첩 효과 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TransitionRange;

	//Assemble 효과 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AssembleRange; // Assemble 효과 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AssembleTime; // Assemble 효과 수행 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AssembleSpeed; // Assemble 효과 끌려가는 힘
	float AssembleTimer; // 지속시간 재는 변수

	//Chain 효과 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ChainRange; // Chain 효과 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ChainSpeed; // Chain 효과 전이속도
	*/
public:
	//원소별 디버프 중첩 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int FireDebuffStack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int WaterDebuffStack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int ThunderDebuffStack;
};


